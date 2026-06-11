---
layout: lecture
pretty_table: true
collection: csc331

title: "Memory virtualization mechanism: address translation"
toc:
  - name: The questions
  - name: Initial assumptions
  - name: Initial assumptions
  - name: External fragmentation
---

# Memory virtualization mechanism: address translation

---

## The questions

{% details Question: Details %}


- How can we build an efficient virtualization of memory?
- How do we provide the flexibility needed by applications?
- How do we maintain control over which memory locations an 
application can access?

{% enddetails %}
{% details General technique %}


- Hardware-based address translation (address translation)
    - HW transforms **virtual address** from memory access into **physical address**. 
- The OS gets involved to ensure correct translations take place and manage memory 
to keep track of and maintain control over free and used memory locations.

{% enddetails %}
---


## Initial assumptions

{% details info Details %}

- User’s address space must be place **contiguously in physical memory**.
- The size of the address space is **less than the size of physical memory**. 
- Each address space is **exactly the same size**.

{% enddetails %}
{% include figure.liquid path="assets/img/courses/csc331/address-translation/03.png" width="50%" zoomable=true %}


{% details Early attempt: dynamic relocation %}


- Hardware-based
- Aka base and bounds
- Two hw registers within each CPU:
- Base register
- Bounds (Limit) register

~~~
physical address = virtual address + base
0 <= virtual address <= bound
~~~


{% details note What happen after boot? %}

{% include figure.liquid path="assets/img/courses/csc331/address-translation/04.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note What happen during process run? %}

{% include figure.liquid path="assets/img/courses/csc331/address-translation/05.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Summary: Details %}


- Pros:
    - Highly efficient through simple translation mechanisms
    - Provides protection
- Cons:
    - Wastage through **internal fragmentation** due to space inside
    the allocated (contiguous) memory units are not fully utilized. 

{% enddetails %}
{% enddetails %}
---

## Initial assumptions

- ~~User’s address space must be place **contiguously in physical memory**.~~
- ~~The size of the address space is **less than the size of physical memory**.~~
- ~~Each address space is **exactly the same size**.~~

*How do we support a large address space with (potentially) a lot of free space
between the stack and the heap?*

{% details Segmentation: generalized base/bounds %}

- Original: One base/bound pair for one address space.
- Segmentation: One base/bound pair per logical segment of an address space:
    - Code
    - Stack
    - Heap

{% include figure.liquid path="assets/img/courses/csc331/address-translation/06.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Example: Details %}


- Note: $32K=2^{15}=32768$

| Segment | Virtual segment base | Virtual segment bound | Physical segment base | Physical segment bound | Size |  
| ------- | -------------------- | --------------------- | ----------------------| ---------------------- | ---- |
| Code    | 0KB                  | 2KB                   |  32KB                 |  34KB                  | 2KB  |
| Heap    | 4KB                  | 6KB (can grow up)     |  34KB                 |  36KB                  | 2KB  |
| Stack   | 16KB                 | 14KB (can grow down)  |  28KB                 |  26KB                  | 2KB  |

- Reference is made to virtual address 100 (code segment)
    - This is called the `offset`
    - `physical address` = `physical segment base` + `offset` = 32K (32768) + 100 = 32868
- Reference is made to virtual address 4200 (heap segment)
    - What is the correct `offset`: 
    - `offset` = `virtual address` - `virtual segment base` = 4200 - 4096 = 104
    - `physical address` = `physical segment base` + `offset` = 34K (34816) + 104 = 34920
- Reference is made to virtual address 7000?
    - Look likes heap segment
    - Is it heap segment?
    - `offset` = `virtual address` - `virtual segment base` = 7000 - 4096 = 2904
    - `physical address` = `physical segment base` + `offset` = 34K (34816) + 2904 = 37720
    - This falls into physical addresses that are markedas **not in use**. 
    - **Segmentation Fault**: AKA segmentation violation
    - Illegal virtual address

{% enddetails %}
{% details Summary: Details %}


- Pros:
    - Efficient saving of physical memory (avoid internal fragmentation)
    - Enable the creation of segments with various sizes
- Cons:
    - **External fragmentation** 

{% enddetails %}
---

## External fragmentation:

{% details Compacting %}


- Computationally expensive

{% include figure.liquid path="assets/img/courses/csc331/address-translation/07.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Algorithmic allocation %}


- A data structure that keeps track of free memory regions:
    - Best-fit
    - Worst-fit
    - First-fit
    - Next-fit
    - Buddy algorithm
- Does not address the core of the issue, only minimize it as much as possible. New solution is needed!
{% enddetails %}
