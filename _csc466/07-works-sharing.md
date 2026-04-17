---
layout: lecture
pretty_table: true
collection: csc466

title: "Work Sharing and Thread Data Management"
toc:
  - name: Work sharing
  - name: Shared and Private Data
---

# Work Sharing and Thread Data Management

## Work sharing

{% details Overview %}


- OpenMP utilizes **work sharing constructs** to facilitate dividing 
parallelizable work among a number of threads. 
- The work sharing constructs are:
  - **for**: divide loop iterations among threads. 
  - **sections**: divide sections of codes among themselves. 
  - **single**: the section is executed by a single thread. 
  - **task**: for offloading

{% enddetails %}
{% details Work sharing construct: sections %}


- Used when parallelize predetermined number of independent work units. 
- Within a primary `sections` construct, there can be multiple `section`
construct. 
- A `section` can be executed by any available thread in the current 
team, including having multiple sections done by the same thread. 

- Inside `csc466`, create a file named `hello_sections.c` with the
following contents:

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=hello_sections.c"></script>

{% include figure.liquid path="assets/img/courses/csc466/06-work-sharing/work_01.png" width="50%" zoomable=true alt="Compile and run hello_sections.c" %}

{% enddetails %}
{% details Challenge: section %}

Given the following functions: $y=x^{4} + 15x^{3} + 10x^{2} + 2x$ develop an 
OpenMP program called `poly_openmp.c` with `sections`/`section` directives. Each
section should handle the calculations for one term of the polynomial. 

{% details tip Solution %}

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=poly_openmp.c"></script>

{% enddetails %}
{% enddetails %}
{% details Work sharing construct: single %}


- Limits the execution of a block to a single thread. 
- All other threads will skip the execution of this block **but** wait until the block is finished
before moving on. 
- To enable proceed without waiting, a **nowait** clause can be added. 
- Inside `csc466`, create the following files: 

`hello_sections_nosingle.c`:
```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/hello_sections_nosingle.c"
```

`hello_sections_single.c`: 

```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/hello_sections_single.c"
```

`hello_sections_single_nowait.c`: 

```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/hello_sections_nowait.c"
```

- Compile and run the above files:

{% include figure.liquid path="assets/img/courses/csc466/06-work-sharing/work_02.png" width="50%" zoomable=true alt="Compile and run singles" %}

{% enddetails %}
## Shared and Private Data

{% details Overview %}

- Data declared outside of a parallel region will be shared among all threads.  
- Data declared inside of a parallel region will be private to individual thread. 
- Inside `csc466`, create a file named `counter_openmp.c` with the
following contents:

```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/counter_openmp.c"
```

{% include figure.liquid path="assets/img/courses/csc466/06-work-sharing/work_03.png" width="50%" zoomable=true alt="shared and private data" %}

{% enddetails %}
{% details Shared and Private %}

- Shared variables: accessible and modifiable by all threads
- Private variables: each thread gets its own copy (uninitialized by default)
- Firstprivate: each thread getss an initialized copy of a variable. 
- Lastprivate save the last computed value of a variable after parallel execution

```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/shared_private.c"

{% details Explain the reason why the value of j is the way it is %}

- What happens if you set j to 0 outside the `#pragma omp parallel` section?

{% enddetails %}
{% details Run and explain the results of the last variable %}


```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/first_last.c"
```

{% enddetails %}
{% enddetails %}
