---
layout: lecture
pretty_table: true
collection: csc231

title: "Memory hierarchy and cache memories"
toc:
  - name: "Memory abstraction: writing and reading memory"
  - name: The CPU-Memory gap
  - name: Memory hierarchies
  - name: Caching
  - name: Write cache friendly code
---
# Memory hierarchy and cache memories


{% details Relevant Reading %}

{% enddetails %}
:class: tip

This lecture will cover contents from [Chapter 11](https://diveintosystems.org/book/C11-MemHierarchy/index.html) of the book. 

```

## Memory abstraction: writing and reading memory

{% details Overview %}



{% enddetails %}
- Write:
  - Transfer data from CPU to memory: `movq 8(%rsp), %rax`
  - `Store` operation
- Read:
  - Trasnfer data from memory to CPU: `movq %rax, 8(%rbp)`
  - `Load` operation
- Physical representation of this abstraction:

{% include figure.liquid path="assets/img/courses/csc231/05-memory/01.png" max-width="50%" zoomable=true %}



{% details Random-Access Memory (RAM) %}


{% enddetails %}
- Key features:
  - RAM is traditionally packaged as a chip, or embedded as part of processor chip
  - Basic storage unit is normally a cell (one bit per cell).
  - Multiple RAM chips form a memory.
- RAM comes in two varieties:
  - SRAM (Static RAM): transistors only
  - DRAM (Dynamic RAM): transistor and capacitor
  - Both are volatile: memory goes away without power. 

:::::{tab-set}
::::{tab-item} SRAM/DRAM
:::{list-table}
:header-rows: 1
* - 
  - SRAM
  - DRAM
* - Transitor per bit
  - 6 or 8
  - 1
* - Access time
  - 1x
  - 10x
* - Need refressh
  - No
  - Yes
* - Need EDC
  - Maybe
  - Yes
* - Cost
  - 100x
  - 1x
* - Applications
  - Cache memories
  - Main memories, frame buffers
:::
::::
:::::

*EDC: Error Detection and Correction*

- Trends: 
  - SRAM scales with semiconductor technology
    - Reaching its limits
  - DRAM scaling limited by need for minimum capacitance
    - Aspect ratio limits how deep can make capacitor
    - Also reaching its limits



{% details Enhanced DRAMs %}


{% enddetails %}
- Operation of DRAM cell has not changed since its invention
  - Commercialized by Intel in 1970. 
- DRAM cores with better interface logic and faster I/O :
  - Synchronous DRAM (SDRAM)
    - Uses a conventional clock signal instead of asynchronous control
  - Double data-rate synchronous DRAM (DDR SDRAM)
    - Double edge clocking sends two bits per cycle per pin
    - Different types distinguished by size of small prefetch buffer:
      - DDR (2 bits), DDR2 (4 bits), DDR3 (8 bits), DDR4 (16 bits)
    - By 2010, standard for most server and desktop systems
  - Intel Core i7 supports DDR3 and DDR4 SDRAM
```

## The CPU-Memory gap


{% details Locality %}



{% enddetails %}
{% include figure.liquid path="assets/img/courses/csc231/05-memory/02.png" max-width="50%" zoomable=true alt="CPU memory gap" %}

- The key to bridging this gap is a fundamental property of computer programs known as **locality**:
  - Principle of Locality: Programs tend to use data and instructions with addresses near or equal 
  to those they have used recently
  - `Temporal locality`:  Recently referenced items are likely to be referenced again in the near future
  - `Spatial locality`:  Items with nearby addresses tend to be referenced close together in time

```c
sum = 0;
for (i = 0; i < n; i++)
  sum += a[i];
return sum;
```

- Data references
  - Reference array elements in succession (stride-1 reference pattern): `spatial`
  - Reference variable `sum` each iteration: `temporal`
- Instruction references
  - Reference instructions in sequence: `spatial`
  - Cycle through loop repeatedly: `temporal`


{% details Qualitative estimates of locality %}



{% enddetails %}
- Being able to look at code and get a qualitative sense of its locality is among the 
key skills for a professional programmer.
- Example: array layout in memory is row-major order

{% include figure.liquid path="assets/img/courses/csc231/05-memory/03.png" max-width="50%" zoomable=true alt="Array layout in memory" %}

:::::{tab-set}

::::{tab-item} Exercise 1

Does this function have good locality with respect to array `a`?

```c
int sum_array_rows(int a[M][N]) {
  int i, j, sum = 0;
  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      sum += a[i][j];
  return sum;
}
```

:::{admonition} Answer


Yes

:::
::::
 
::::{tab-item} Exercise 2

Does this function have good locality with respect to array `a`?

```c
int sum_array_rows(int a[M][N]) {
  int i, j, sum = 0;
  for (j = 0; j < N; j++)
    for (i = 0; i < M; i++)
      sum += a[i][j];
  return sum;
}
```

:::{admonition} Answer


Yes

:::

::::
:::::


{% details Hands-on: performance measurement of locality %}



{% enddetails %}
- In your home directory, create a directory called `05-memory` and change into this 
directory.
- Create a file named `sum.c` with the following contents:

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=sum.c"></script>

- Compile and run several times. 
- Observe the performance difference. 

:::::{tab-set}
::::{tab-item} Compile and run
```bash
$ gcc -Og -o sum sum.c
$ ./sum
$ ./sum
$ ./sum
$ ./sum
```
::::
::::{tab-item} Result
{% include figure.liquid path="assets/img/courses/csc231/05-memory/04.png" max-width="50%" zoomable=true alt="Differences in performance due to access pattern" %}
::::

```


## Memory hierarchies

{% details Overview %}



{% enddetails %}
- Some fundamental and enduring properties of hardware and software:
  - Fast storage technologies cost more per byte, have less capacity, 
  and require more power (heat!). 
  - The gap between CPU and main memory speed is widening.
  - Well-written programs tend to exhibit good locality.
- These fundamental properties complement each other beautifully.
- They suggest an approach for organizing memory and storage systems 
known as a memory hierarchy.

{% include figure.liquid path="assets/img/courses/csc231/05-memory/05.png" max-width="50%" zoomable=true alt="Memory hierarchy" %}
```

## Caching

{% details Overview %}


{% enddetails %}
- Cache: A smaller, faster storage device that acts as a staging area for a subset of the data in a larger, 
slower device.
- Fundamental idea of a memory hierarchy:
  - For each `k`, the faster, smaller device at level `k` serves as a cache for the larger, 
  slower device at level `k+1`.
- Why do memory hierarchies work?
  - Because of locality, programs tend to access the data at level `k` more often than they access the 
  data at level `k+1`. 
  - Thus, the storage at level k+1 can be slower, and thus larger and cheaper per bit.
- Big Idea (Ideal):  The memory hierarchy creates a large pool
of storage that costs as much as the cheap 
storage near the bottom, but that serves data to programs at the rate of the fast storage near the top.


{% details General concepts %}



{% enddetails %}
:::::{tab-set}
::::{tab-item} Cache
{% include figure.liquid path="assets/img/courses/csc231/05-memory/06.png" max-width="50%" zoomable=true alt="Cache concepts" %}
::::
::::{tab-item} Cache hits
{% include figure.liquid path="assets/img/courses/csc231/05-memory/07.png" max-width="50%" zoomable=true alt="Cache hits" %}
::::
::::{tab-item} Cache misses
{% include figure.liquid path="assets/img/courses/csc231/05-memory/08.png" max-width="50%" zoomable=true alt="Cache misses" %}

- Cold (compulsory) miss
  - Cold misses occur because the cache starts empty and this is the first reference to the block.
- Capacity miss
  - Occurs when the set of active cache blocks (working set) is larger than the cache.
- Conflict miss
  - Most caches limit blocks at level `k+1` to a small subset (sometimes a singleton) of the 
  block positions at level `k`.
    - E.g. Block i at level `k+1` must be placed in block (`i mod 4`) at level `k`.
  - Conflict misses occur when the level `k` cache is large enough, but multiple data objects all map 
  to the same level `k` block.
    - E.g. Referencing blocks 0, 8, 0, 8, 0, 8, ... would miss every time.

::::
::::{tab-item} Cache types

| Cache Type            | What is cached       | Where is it cached  | Latency (cycles) | Managed By       |
| --------------------- | -------------------- | ------------------- | ---------------- | ---------------- | 
| Register              | 4-6 byte words       | CPU core            | 0                | Compiler         |
| TLB                   | Address translations | On-chip TLB         | 0                | Hardware MMU     |
| L1 cache              | 64-byte blocks       | On-chip L1          | 4                | Hardware         |
| L2 cache              | 64-byte blocks       | On-chip L2          | 10               | Hardware         |
| Virtual memory        | 4-KB pages           | Main memory         | 100              | Hardware + OS    |
| Buffer cache          | Part of files        | Main memory         | 100              | OS               |
| Disk cache            | Disk sectors         | Disk controller     | 100,000          | Disk firmware    |
| Network buffer cache  | Part of files        | Local disk          | 10,000,000       | NFS client       |
| Browser cache         | Web pages            | Local disk          | 10,000,000       | Web browser      |
| Web cache             | Web pages            | Remote server disks | 1,000,000,000    | Web proxy server |

::::

{% details Cache memories %}



{% enddetails %}
- Small, fast SRAM-based memories managed automatically in hardware.
- Hold frequently accessed blocks of main memory.
- CPU looks first for data in cache.

:::::{tab-set}
::::{tab-item} L2/L3
{% include figure.liquid path="assets/img/courses/csc231/05-memory/09.png" max-width="50%" zoomable=true alt="Example of L2 and L3 cache" %}
::::
::::{tab-item} L1/L2/L3
{% include figure.liquid path="assets/img/courses/csc231/05-memory/10.png" max-width="50%" zoomable=true alt="Example of L1, L2, and L3 cache" %}
::::

{% details Cache performance metrics %}



{% enddetails %}
- Miss Rate
  - Fraction of memory references not found in cache `(misses / accesses) = 1 – hit rate`
  - Typical numbers (in percentages):
    - 3-10% for L1
    - can be quite small (e.g., < 1%) for L2, depending on size, etc.
- Hit Time
  - Time to deliver a line in the cache to the processor
    - includes time to determine whether the line is in the cache
  - Typical numbers:
    - 4 clock cycle for L1
    - 10 clock cycles for L2
- Miss Penalty
  - Additional time required because of a miss
    - typically 50-200 cycles for main memory (Trend: increasing!)



{% details What those numbers mean? %}



{% enddetails %}
- Huge difference between a hit and a miss
  - Could be 100x, if just L1 and main memory
- Would you believe 99% hits is twice as good as 97%?
  - Consider this simplified example: 
    - cache hit time of 1 cycle
    - miss penalty of 100 cycles
  - Average access time:
    - 97% hits:  1 cycle + 0.03 x 100 cycles = 4 cycles
    - 99% hits:  1 cycle + 0.01 x 100 cycles = 2 cycles
- This is why `miss rate` is used instead of `hit rate`.

```

## Write cache friendly code

{% details Overview %}



{% enddetails %}
- Make the common case go fast
  - Focus on the inner loops of the core functions
- Minimize the misses in the inner loops
  - Repeated references to variables are good (temporal locality)
  - Stride-1 reference patterns are good (spatial locality)
- Key idea: our qualitative notion of locality is quantified through
our understanding of cache memories. 


{% details Matrix multiplication example %}



{% enddetails %}
- Multiply N x N matrices
- Matrix elements are doubles (8 bytes)
- $O(N^{3})$ total operations
- N reads per source element
- N values summed per destination but may be able to hold in register 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=mm.c"></script>

{% include figure.liquid path="assets/img/courses/csc231/05-memory/15.png" max-width="50%" zoomable=true alt="Index increment directions in matrix multiplication" %}


{% details Various matrix multiplication performance analysis %}



{% enddetails %}
:::::{tab-set}
::::{tab-item} Case 1
```c
/* ijk */
for (i=0; i<n; i++)  {
  for (j=0; j<n; j++) {
    sum = 0.0;
    for (k=0; k<n; k++) 
      sum += a[i][k] * b[k][j];
    c[i][j] = sum;
  }
} 
```

- Miss rate for inner loop iterations:
- Block size = 32 bytes (4 doubles)
  - A = 8 / 32 = 0.25
  - B = 1
  - C = 0
  - Average miss per iteration = 1.25
  
{% include figure.liquid path="assets/img/courses/csc231/05-memory/16.png" max-width="50%" zoomable=true alt="Miss rate 1" %}
::::
::::{tab-item} Case 2
```c
/* kij */
for (k=0; k<n; k++)  {
  for (i=0; i<n; i++) {
    r = a[i][k];
    for (j=0; j<n; j++) 
      c[i][j] += r * b[k][j];
  }
} 
```

- Miss rate for inner loop iterations:
- Block size = 32 bytes (4 doubles)
  - A = 0
  - B = 8 / 32 = 0.25
  - C = 8 / 32 = 0.25
  - Average miss per iteration = 0.5

{% include figure.liquid path="assets/img/courses/csc231/05-memory/17.png" max-width="50%" zoomable=true alt="Miss rate 2" %}
::::
::::{tab-item} Case 3
```c
/* jki */
for (j=0; j<n; j++)  {
  for (k=0; k<n; k++) {
    r = b[k][j];
    for (i=0; i<n; i++) 
      c[i][j] += a[i][k] * r;
  }
} 
```

- Miss rate for inner loop iterations:
- Block size = 32 bytes (4 doubles)
  - A = 1
  - B = 0
  - C = 1
  - Average miss per iteration = 2

{% include figure.liquid path="assets/img/courses/csc231/05-memory/18.png" max-width="50%" zoomable=true alt="Miss rate 3" %}
::::

{% details The memory mountain %}



{% enddetails %}
- This is the cover of the book. 
- Y-axis: Read throughput (read bandwidth)
  - Number of bytes read from memory per second (MB/s)
- Memory mountain: Measured read throughput as a function of spatial and temporal locality.
- Compact way to characterize memory system performance. 

{% include figure.liquid path="assets/img/courses/csc231/05-memory/19.png" max-width="50%" zoomable=true alt="memory mountain" %}
```

