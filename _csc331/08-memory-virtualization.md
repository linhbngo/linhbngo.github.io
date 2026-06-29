---
layout: lecture
pretty_table: true
collection: csc331

title: "Memory virtualization"
toc:
  - name: In the beginning ...
  - name: Multiprogramming and time sharing
  - name: Address space
  - name: "Hands on: Where the stack grows?"
  - name: "Hands on: where the heap grows?"
  - name: What is address space, really?
  - name: Goals of memory virtualization
---

## In the beginning ...

- Users didn't expect much. 
- To be honest, most, if not all, users are also developers ...

{% details Early systems %}


- Computers run **one job** at a time. 
- The OS was preloaded into memory and consisted of a set of routines. 
- There was one running program that uses the rest of memory. 

{% include figure.liquid path="assets/img/courses/csc331/memory-virtualization/01.png" width="50%" zoomable=true %}

{% enddetails %}

{% details Multiprogramming and time sharing %}

- Demands for
    - Utilization
    - Efficiency
    - Interactivity
- Multiple processes ready to run at a given time. 
- The OS switches between them. 
- One approach is to run one process at a time and still give it full access to all memory 
(just like the early days ...).
- This requires switching processes from memory.


{% enddetails %}


## Multiprogramming and time sharing

{% details Recall: Running one process at a time with full memory access %}

- This solution does not scale as memory grows. 

| System event | Size    | Latency | 
| ------------ | ------- | ------- |  
| CPU          |         | <1ns    |  
| L1 cache     | 32KB    | 1ns     |  
| L2 cache     | 256KB   | 4ns     |  
| L3 cache     | >8MB    | 40ns    |  
| DDR RAM      | 4GB-1TB | 80ns    |  

{% enddetails %}
{% details What we want to do %}

- Leave processes in memory and let OS implement an efficient time sharing/switching 
mechanism. 
- A new demand: **protection** (through isolation)

{% include figure.liquid path="assets/img/courses/csc331/memory-virtualization/02.png" width="50%" zoomable=true %}

{% enddetails %}

## Address space

- Provide users (programmers) with an **easy-to-use** abstarction of physical memory. 
- The running program's **view of memory in the system**. 
- Contains all memory states of the running program:
    - `Stack` to keep track of where it is in the function call chain 
    (stack frames), allocate local variables, and pass parameters and 
    return values to and from routines. 
    - `Heap` is used for dynamically allocated, user-managed memory 
    (i.g., malloc()). 
    - `BSS` (block started by symbols) contains all global variables and static 
    variables that are initialized to zero or do not have explicit initialization 
    in source code.
    - `Data` contains the global variables and static variables that are initialized 
    by the programmer.
    - `Code` (binary) of the program.

<div class="grid cards" markdown>

-   __Address high to low__

    {% include figure.liquid path="assets/img/courses/csc331/memory-virtualization/03.png" width="50%" zoomable=true %}

-   __Address low to high__ 

    {% include figure.liquid path="assets/img/courses/csc331/memory-virtualization/04.png" width="50%" zoomable=true %}
    *Image taken from [Geeksforgeeks](https://www.geeksforgeeks.org/memory-layout-of-c-program/)*
</div>
 

## Hands on: Where the stack grows?

- Create `stacktest.c` inside the `user` directory, rebuild xv6.  

{% details stacktest.c %}

```c
// user/stacktest.c
#include "kernel/types.h"
#include "user/user.h"

void f2() {
  int a = 5, b = 6;
  printf("In f2: &a = 0x%lx, &b = 0x%lx\n", (uint64)&a, (uint64)&b);
}

void f1() {
  int x = 3, y = 4;
  int arr[5];
  printf("In f1: &x = 0x%lx, &y = 0x%lx\n", (uint64)&x, (uint64)&y);
  printf("Address of arr       = 0x%lx\n", (uint64)arr);
  printf("Address of arr[0]    = 0x%lx\n", (uint64)&arr[0]);
  printf("Address of arr[1]    = 0x%lx\n", (uint64)&arr[1]);  f2();
}

int main() {
  int m = 1, n = 2;
  printf("In main: &m = 0x%lx, &n = 0x%lx\n", (uint64)&m, (uint64)&n);
  f1();
  exit(0);
}

```

{% enddetails %}
- Run `stacktest`. 

```bash
stacktest

{% details Observe and discuss output %}


{% include figure.liquid path="assets/img/courses/csc331/memory-virtualization/05.png" width="50%" zoomable=true %}

{% enddetails %}
---

## Hands on: where the heap grows?


- Create `arraytest.c` inside the `user` directory, rebuild xv6.  

{% details arraytest.c %}


```c
// user/arraytest.c
#include "kernel/types.h"
#include "user/user.h"

int main() {
int arr[10];
printf("[Stack]  &arr[0]     = 0x%lx\n", (uint64)&arr[0]);

int *h1 = (int *)sbrk(10 * sizeof(int));
int *h2 = (int *)sbrk(10 * sizeof(int));
int *h3 = (int *)sbrk(10 * sizeof(int));

printf("[Heap]   h1          = 0x%016lx\n", (uint64)h1);
printf("[Heap]   h2          = 0x%016lx\n", (uint64)h2);
printf("[Heap]   h3          = 0x%016lx\n", (uint64)h3);
exit(0);
}
```

{% enddetails %}
- Run `arraytest`. 

```bash
arraytest
```

{% details Observe and discuss output %}


{% include figure.liquid path="assets/img/courses/csc331/memory-virtualization/06.png" width="50%" zoomable=true %}

{% enddetails %}
{% details How the heap grows %}

{% details success Acknowledgement %}

This section is developed based on Ellis Weaverkreider's question in Fall 2025

{% enddetails %}
- xv6's explicitly write code in such a way that stack space is created immediately after the 
creation of EFL segments (text/bss/data). 

{% details info uvmalloc %}

- Function implemented in `vm.c`

```c
uint64 uvmalloc(pagetable_t pagetable, uint64 oldsz, uint64 newsz, int xperm)
```

{% enddetails %}
{% details info Stack: exec.c/kexec() %}

- [Source code](https://github.com/mit-pdos/xv6-riscv/blob/riscv/kernel/exec.c)
- ELF and Program Data is loaded. 
- Empty page for security
- Page is reserved for stack

{% enddetails %}
{% details info Heap: sysproc.c/sys_sbrk() %}

- [Source code](https://github.com/mit-pdos/xv6-riscv/blob/riscv/kernel/sysproc.c)
- Starting from top of program size (`myproc() -> sz`)
- Allocate additional memory for heap and move program size to that location. 

{% enddetails %}
{% details info Linux comparison %}

- [Source code](https://github.com/torvalds/linux/blob/master/arch/riscv/include/asm/processor.h)
    - [TASK_SIZE_64](https://github.com/torvalds/linux/blob/bf40f4b87761e2ec16efc8e49b9ca0d81f4115d8/arch/riscv/include/asm/pgtable.h#L1055)
- When user stack is created:
    - [Source code](https://github.com/torvalds/linux/blob/master/fs/binfmt_elf.c)

```c
/* Do this so that we can load the interpreter, if need be.  We will
change some of these later */
retval = setup_arg_pages(bprm, randomize_stack_top(STACK_TOP), executable_stack);
```

{% enddetails %}
{% enddetails %}

## What is address space, really?

- The **abstraction of physical memory** that the OS is providing to the 
running program. 
- How can the OS build this abstraction of a private, potentially large 
address space for multiple running processes on top of a single physical memory?
  - This is called **memory virtualization**.

## Goals of memory virtualization

- `Transparency`: The program should not be aware that memory is virtualized 
(did you feel anything different when programming?). The program should perceive 
the memory space as its own private physical memory. 
- `Efficiency`: The virtualization process should be as efficient as possible
  - `Time`: not making processes run more slowly
  - `Space`: not using too much memory for supporting data structures
- `Protection`: Protection enable the property of isolation: each process should be running 
in its own isolated memory space, safe against other processes. 

