---
layout: lecture
pretty_table: true
collection: csc331

title: "Memory virtualization mechanism: paging and tlb"
toc:
  - name: What is paging?
  - name: Page Table
  - name: Multi-level page tablescco
  - name: Translation Lookaside Buffer
  - name: Demand paging
  - name: Matrix multiplication
---

# Memory virtualization mechanism: paging and tlb

---

## What is paging?

{% details Overview %}


- Divide contents into fixed-size units, called pages.
    - Each page has a page number
    - Locate contents in pages by an offset (10th word on page 185)
    - There is a table to tell you which content is on which page
- Physical memory is viewed as an array of fixed-size slots called page frames.
    - Each frame can contain a single virtual memory page

{% include figure.liquid path="assets/img/courses/csc331/paging/01.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% details After allocation %}


- For allocation management, the OS keeps a list of free (fixed-size) pages.
    - This is much simpler than trying to maintain a list of variable-size memory regions
- Virtual pages are numbered, which preserve the order of the virtual address space. 
This allows us to allocate page frame for the virtual pages across the entire available 
physical memory space. 

{% include figure.liquid path="assets/img/courses/csc331/paging/02.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% details What data structure is needed? %}


- Page Table: Mapping from virtual page number to physical page frame
    - VP0 - PF3
    - VP1 - PF7
    - VP2 - PF5
    - VP3 - PF2
- Each process has its own page table

{% include figure.liquid path="assets/img/courses/csc331/paging/02.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% details Address translation with paging %}


- To translate a virtual address, we need:
    - Virtual page number (VPN)
    - The offset within the page

{% include figure.liquid path="assets/img/courses/csc331/paging/01.png" max-width="50%" zoomable=true %}

- For the 64-bit virtual address space, 6 bytes are needed ($2^6=64$)
    - There are four pages (2 bytes for VPN)
    - Each page stores 16 bytes (4 bytes to describe offset of these 16 bytes). 

{% include figure.liquid path="assets/img/courses/csc331/paging/03.png" max-width="50%" zoomable=true %}

- The physical memory has 128 bit, so the physical address will be 7 bytes. 
    - The 2-byte VPN (virtual page number) will be translated to a corresponding 
    3-byte PFN (page frame number). 
    - The offset remains the same (virtual page has the same size as page frame). 

{% include figure.liquid path="assets/img/courses/csc331/paging/04.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% details New questions! %}


- What are the typical contents of the page table?
- How big are the page tables?
- Where are the page tables stored?
- Does paging slow down the system?

{% enddetails %}
---

## Page Table

{% details Contents of a page table entry (PTE) for 32-bit x86 %}


- `PFN`: 20 bits for physical page frame number (page size 4K)
- `P`: present bit, whether this page is on memory or on disk (swapped)
- `R/W`: read/write bit, whether writes are allowed to this page
- `U/S`: user/supervisor bit, whether user-mode processes can access this page
- `A`: access bit, whether this page has been accessed
- `D`: dirty bit, whether this page has been modified
- `PWT, PCD, PAT, G`: [how hardware caching works for this page](https://xem.github.io/minix86/manual/intel-x86-and-64-manual-vol3/o_fe12b1e2a880e0ce-425.html)

{% include figure.liquid path="assets/img/courses/csc331/paging/05.png" max-width="50%" zoomable=true %}


{% enddetails %}
{% details Size of page table 32-bit x86 %}


- Typical page size is 4KB (run `getconf PAGESIZE` in your VM to observe this)
- Size of address space: 4GB
- Number of pages in address space: 4GB / 4KB = 1M
- Number of PTE in page table: 1M
- How many bits for VPN: 20
- How many bits for offset: 12
- Each PTE is 4 bytes, therefore the size of a page table is 4B * 1M = 4MB per process
- Assume 100 processes running, we have 400MB of all page tables 
- **This is too big**

{% enddetails %}
{% details How can we reduce the size of the page table? %}

- Bigger pages. 
- Hybrid: Page + Base/Bound
- Multi-level page tables

{% enddetails %}
{% details Bigger pages %}


- Let the page size be 16K instead of 4K
    - 4GB address space
    - Number of pages in address space: 4GB / 16KB = 256K
    - Number of PTE in page table: 256K
    - How many bits for VPN: 18
    - How many bits for offset: 14
    - Each PTE is 4 bytes in size
    - Total size of page table is 256K * 4B= 1M
- Smaller by a factor of 4
- Problem:
    - For small processes, we waste the remaining space of a page.
    - This is internal fragmentation

{% enddetails %}
{% details Hybrid %}


- Separate page tables for stack, heap, and code.
- For each page table, use base/bound register to keep the physical address 
of the page table.
- Use two bits in the virtual address to indicate which segment it is in.
- No need to have PTEs for unused paged.
- Problem: Bring back all issues of segmentation
    - Free space management
    - External fragmentation

{% enddetails %}
---

## Multi-level page tablescco

{% details Overview %}

- Chop up the page table into page-sized units.
- If an entire page of page-table entries is invalid, don’t allocate that page 
of the page table at all (reduce memory space).
- A new structure called **page directory** is needed to keep track of pages' validity

{% enddetails %}
{% details Multi-level page tables %}

- Two-level table
- One entry per page of page table (Page Directory Entry - PDE)
- A PDE has a valid bit and a page frame number (PFN)
- If the PDE is valid, it means that at least one of the the pages of the page table that 
the entry points to (via the PFN) is valid. 
- If the PDE is not valid, the rest of the PDE is not defined. 

{% include figure.liquid path="assets/img/courses/csc331/paging/06.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% details Advantages %}


- Only allocates page-table space in proportion to the amount of address 
spaces being used.
- If carefully constructed, each portion of the page table fits neatly within 
the page, making it easier to manage memory (think pointer to memory space versus 
contiguous memory location).

{% enddetails %}
{% details Cost %}


- `Space` versus `Time`: To reduce space, increased access translation steps are needed: 
one for the page directory and one for the PTE itself. 
- Complexity: Page table lookup is more complex to implement than a simple linear 
page-table look up. 
- Each level of multi-level page tables requires one additional memory access:
    - One to get PTE. 
    - One to get the actual data. 
    - [Linux can go up to 4 level of page tables](https://github.com/torvalds/linux/blob/master/arch/x86/mm/pgtable.c)
- Hardware to the rescue!
    - Translation Look Aside Buffer (aka TLB, aka address translation cache, aka cache)

{% enddetails %}
---

## Translation Lookaside Buffer

{% details Overview %}

- Part of the memory management unit (MMU)
- Small, fully associative hardware cache of recently used translations
    - small, so it’s fast by laws of physics
    - fully associative, i.e., all entries looked up in parallel, so it’s fast
    - hardware, so it’s fast
    - It is so fast that the lookup can be done in a single CPU cycle.
- A successful lookup in TLB is called a TLB hit, otherwise it is a TLB miss

{% enddetails %}
{% details What is in TLB? %}


- Lookup entries: VPN -PFN plus some other bits
- A TLB typically has 32, 64, or 128 entries

{% include figure.liquid path="assets/img/courses/csc331/paging/07.png" max-width="50%" zoomable=true %}


{% enddetails %}
{% details First issue with TLB %}


- Context switch invalidates all entries in TLB. Why?
    - Because the VPN stored in a TLB entry is for **current** process, which becomes 
    meaningless when switched to another process.
    - Could lead to wrong translation if not careful.
- Possible solutions:
  - Simply flush the the TLB on context switch, i.e., set all valid bits to 0.
      - Safe, but inefficient.
      - Think of two Processes A and B that frequently context switch between 
      each other. 
  - Add Address Space Identifier (ASID) to TLB entry
      - It’s basically PID, but shorter (e.g., 8 bits instead of 32 bits)
      - Avoids wrong translation without having to flush all entries

{% enddetails %}
{% details Second issue with TLB %}


- Replacement policy
- When TLB is full, and we want to add a new entry to it, we will have to 
evict an existing entry.
- Which one to evict?

{% enddetails %}
{% details TLB and locality %}


- Processes only use a handful of pages at a time.
- A TLB with 64 entries can map 64 * 4K = 192KB of memory, which usually. 
covers most of the frequently accessed memory by a process within certain time span.
- In reality, TLB hit rates (hit / (hit + miss)) are typically very high (99%). 
- Caching is an important idea, use it when possible.

{% enddetails %}
{% details Hands on: memory access %}


- Create two vertical terminal panels on the Code browser.
- In the left panel, create `memory_access_v1.c` with the following contents:

```c
#include <stdlib.h>
#define N 50000000

int main(int argc, char *argv[]) {
  int i;
  int *A = (int *)malloc(N*sizeof(int));
  if (!A) return 1;
  for(i = 0; i < 10000; i++)
    A[i] = 0;
  return 0;
}
```

- In the right panel, create `memory_access_v2.c` with the following contents:

```c
#include <stdlib.h>
#define N 50000000

int main(int argc, char *argv[]) {
  int i;
  int *A = (int *)malloc(N*sizeof(int));
  if (!A) return 1;
  for(i = 0; i < N; i += 5000)
    A[i] = 0;
  return 0;
}
```


**Questions**

- Which is faster?
- Why?

{% details Solution: Details %}

- In the left panel, compile and timed run `memory_access_v1.c`:

```bash
gcc -o memory_access_v1 memory_access_v1.c
time ./memory_access_v1
```    

- In the right panel, compile and timed run `memory_access_v2.c`. 

```bash
gcc -o memory_access_v2 memory_access_v2.c
time ./memory_access_v2
```  

{% include figure.liquid path="assets/img/courses/csc331/paging/08.png" max-width="50%" zoomable=true %}


{% enddetails %}
{% enddetails %}
## Demand paging

{% details Overview %}

- In an ideal world, we have an infinite amount of RAM …
- In reality:
    - Many processes use memory, and in combination exceeds the size of physical memory.
    - One process’ memory usage can be larger the size of physical memory. 
    - OS supports a mechanism to offload exceed memory demands to hard disks to store 
    pages that are not being accessed. 
    - From the perspective of processes, everything is still within a large virtual 
    address space. 
- This mechanism is called demand paging. 

{% enddetails %}
{% details Demand paging %}


- Swap space: a reserved space on hard disk for moving pages back and forth
    - Linux/Unix: a separate disk partition 
    - Windows: a binary file called `pagefile.sys`
- Initially, pages are allocated in physical memory.
- As memory fills up, more allocations require existing pages to be evicted. 
- Evicted pages go to disk (into swap space).
- Present bit (`P`) indicates whether the page is in memory or on disk. 
- `P` = 0 (on disk), then the remaining bits in PTE store the disk address of the page. 
- When the page is loaded into memory, P is set to 1, and the appropriate PTE contents 
are updated. 

{% include figure.liquid path="assets/img/courses/csc331/paging/05.png" max-width="50%" zoomable=true %}


{% enddetails %}
{% details Demand paging control flow %}


- If the page is in memory, keep going. 
- If the page is to be evicted, the OS sets `P` to 0, moves the page to swap space, 
and stores the location of the page in the swap space in the PTE. 
- When a process access the page, the 0 value of P will cause a system trap called 
page fault. 
- The trap run the OS `page_fault_handler`, which locates the page in the swap file. 
- The trap reads the page into a physical frame, and updates PTE to points to this frame. 
- The trap returns to the process, and the page will be available for the process. 

{% enddetails %}
{% details Dirty bit %}


- If the page has been not been modified (`dirty` == 0) since it was loaded from swap, 
nothing will need to be written to disk when the page is evicted again. 
- If the page has been modified (dirty == 1), it must be rewritten to disk when it 
is evicted. 
- This mechanism is invented by Corbato. (Who is Corbato?). 
- Issue:
    - When we have to evict a page to disk, which one should we choose?


{% enddetails %}
{% details Replacement algorithms %}


- Reduce fault/miss rate by selecting the best victim to evict. 
- Unrealistic assumption: we know the **whole** memory reference trace of the 
program, including the **future** ones at any point in time. 
- Algorithm 1: evict the one that will never be used again.  
    - Does not always work. 
- Algorithm 2: evict the page whose next access is furthest in the future. 
    - Belady's algorithm ("A study of replacement algorithm for a virtual-storage computer", IBM Systems Journal, 5(2), 1966).
    - Caveat: we don't know the future. 
    - Belady's algorithm serves as the benchmark to see **how close** other algorithms are to 
    being perfect!


{% enddetails %}
{% details We predict the future based on patterns ... %}


- `Locality`: the patterns in computer programs’ behaviors. 
- `Spatial locality`: If an address A is accessed, then addresses A - 1 and A + 1 
are also likely to be accessed. 
- `Temporal locality`: if an address is accessed at time T, then it is also likely to 
be accessed again in the future T + Δt.
- This is not a set-in-stone rule, but in general, it is a good heuristic to remember 
when designing computing systems. 

{% enddetails %}
{% details Example policies %}


- FIFO: 
    - Good: oldest page is unlikely to be used again.
    - Bad: oldest page is likely to be used again.
- Random:
    - Based purely on luck. 
    - TLB replacement is usually random. 
- LRU:
    - Least recently used. 
    - Close to optimal. 
    - Not very easy to implement. 

{% enddetails %}
## Matrix multiplication

{% details Question: Details %}

- Which approach is faster?
- Why?

{% include figure.liquid path="assets/img/courses/csc331/paging/09.png" max-width="50%" zoomable=true %}


{% enddetails %}
{% details Hands on: matrix multiplication %}


- In the left panel, create `matrix_compare.c` with 
the following contents:

<script src="https://gist.github.com/linhbngo/d2f3a0b28b73a3f48c751410c6c91fd6.js?file=matrix_compare.c"></script>


{% details Questions %}


- Which matrix multiplication function (`matrix_mul_v1` or `matrix_mul_v2`) represents
which multiplication approach from the question?
- Compile and run `matrix_compare.c`:

```bash
gcc -o matrix_compare matrix_compare.c
./matrix_compare 1000
./matrix_compare 1500
./matrix_compare 2000
```

{% include figure.liquid path="assets/img/courses/csc331/paging/10.png" max-width="50%" zoomable=true %}


{% include figure.liquid path="assets/img/courses/csc331/paging/11.png" max-width="50%" zoomable=true %}


{% enddetails %}
{% enddetails %}
