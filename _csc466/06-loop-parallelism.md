---
layout: lecture
pretty_table: true
collection: csc466

title: "OpenMP: parallel regions and loop parallelism"
toc:
  - name: Loop parallelism
  - name: Loop Schedule
  - name: Nested Loops
  - name: Hands-on
---
# OpenMP: parallel regions and loop parallelism

## Loop parallelism

{% details Overview %}


- Very common type of parallelism in scientific code     
- OpenMP paralell:
  - Example of OpenMP `worksharing` constructs

{% enddetails %}
{% details OpenMP for: template %}


- Manual approach (we have seen this before)
  - In previous trapezoid example, we calculate the division of iteration manually.  

```c
#pragma omp parallel
{
  int threadnum = omp_get_thread_num(),
    numthreads = omp_get_num_threads();
  int low = N*threadnum/numthreads,
    high = N*(threadnum+1)/numthreads;
  for (int i=low; i<high; i++)
    // do something with i
}
```

- An alternative is to use `parallel for` pragma 

```c
#pragma omp parallel
#pragma omp for
for (int i=0; i<N; i++) {
  // do something with i
}
```

{% enddetails %}
{% details OpenMP for: visualization %}


```c
#pragma omp parallel
{
  code1()
  #pragma omp for
    for (int i=0; i<N; i++) {
      code2()
    }
  code3()
}

{% details info Execution flow %}

{% include figure.liquid path="assets/img/courses/csc466/06-loop-parallelism/parallel-do.jpeg" width="50%" zoomable=true %}

- The `do` and `for` pragmas do not create a team of threads: 
    - they take the team of threads that is active, and divide the loop iterations over them. 
- This means that the `omp for` or `omp do` directives need to be inside a parallel region.

{% enddetails %}
{% enddetails %}
{% details Limitation %}


- OpenMP needs to be able to determine in advance how 
many iterations there will be. 
- The loop can not contains `break`, `return`, `exit` statements, 
or `goto` to a label outside the loop.
- The `continue` (for C/C++) statement is allowed.
- The index update has to be an increment (or decrement) by 
a fixed amount.
- The loop index variable is automatically `private`, and 
no changes to it inside the loop are allowed.

{% enddetails %}
## Loop Schedule

{% details Overview %}

- Strategy in assigning the work portions to individual threads
    - Static
    - Dynamic

{% include figure.liquid path="assets/img/courses/csc466/06-loop-parallelism/scheduling.jpeg" width="50%" zoomable=true %}

```c
#pragma omp for schedule(...)
```

The schedules can be setup in a more fine-grained manner

{% include figure.liquid path="assets/img/courses/csc466/06-loop-parallelism/schedules.jpeg" width="50%" zoomable=true %}


{% enddetails %}
{% details Static %}

- Do we specify chunk size?

- Create a file named `for.c`, compile and run

{% details info pragma for %}

```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/for.c"
```

```bash
gcc -o for for.c -fopenmp
./for 20 4
```

{% enddetails %}
{% details info pragma for, schedule static, chunk size 2 %}


- Create a file named `for_static.c`, compile and run

```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/for_static.c"
```

```bash
gcc -o for_static for_static.c -fopenmp
./for 20 4
```

{% enddetails %}
{% details Questions %}

- What happens when number of work partitions is not divisible by number of thread?
- What happens when number of work partitions is not divisible by chunk size?

{% enddetails %}
{% enddetails %}
{% details Dynamic %}


- Create a file named `for_dynamic.c`, compile and run

  ```c linenums="1"
      --8<-- "docs/csc466/lectures/data/openmp/for_dynamic.c"
  ```

  ```bash
  gcc -o for_dynamic for_dynamic.c -fopenmp
  ./for 20 4
  ```

- What is the difference?

{% details info pragma for, schedule static, workload simulation by sleep %}


- Create a file named `for_static_rand.c`, compile and run

```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/for_static_rand.c"
```

```bash
gcc -o for_static_rand for_static_rand.c -fopenmp
./for 20 4
```

{% enddetails %}
{% details info pragma for, schedule dynamic, workload simulation by sleep %}


- Create a file named `for_dynamic_rand.c`, compile and run

```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/for_dynamic_rand.c"
```

```bash
gcc -o for_dynamic_rand for_dynamic_rand.c -fopenmp
./for 20 4
```

{% enddetails %}
{% details info 32 portions, 4 threads %}

{% include figure.liquid path="assets/img/courses/csc466/06-loop-parallelism/dynamic_static_32_4.png" width="50%" zoomable=true %}    

{% enddetails %}
{% details info 128 portions, 4 threads %}

{% include figure.liquid path="assets/img/courses/csc466/06-loop-parallelism/dynamic_static_128_4.png" width="50%" zoomable=true %}    


{% enddetails %}
{% enddetails %}
{% details Guided %}

- Similar to dynamic, but the chunk size can change as the program runs. 
- This is to help with load balancing. 

{% enddetails %}
## Nested Loops

{% details Collapsing nested loops %}


{% details info Nested loops without collapse %}

- Create a file named `nested_loops.c`, compile and run

```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/nested_loops.c"
```

```bash
gcc -o nested_loop nested_loop.c -fopenmp
./for 2 4
```

- How many printf statements are there in total?
- How many threads contribute to the execution of these statements?

{% enddetails %}
{% details info Nested loops with collapse %}

- Create a file named `nested_loops.c`, compile and run

```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/nested_loops_collapse.c"
```

```bash
gcc -o nested_loops_collapse nested_loops_collapse.c -fopenmp
./for 2 4
```

- How many printf statements are there in total?
- How many threads contribute to the execution of these statements?

{% enddetails %}
{% enddetails %}
{% details Requirements for collapsing %}

- Only possible for perfectly nested loops
    - There must be no statements before or after the two loops. 

{% enddetails %}
{% details Hands-on: Collapsing a nested loop %}

- Given the following outputs of an OpenMP program done with collapsed nested loop, 
reconstruct the source code

{% include figure.liquid path="assets/img/courses/csc466/06-loop-parallelism/collapse_3.png" width="50%" zoomable=true %}

{% details Solution %}

```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/collapse_3.c"
```


{% enddetails %}
{% enddetails %}
## Hands-on:

{% details Sum series implementation example %}


- Create a file named `sum_series_for.c` using the code below:  

```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/sum_series_openmp_for.c"
```

{% enddetails %}
{% details Improving sum series implementation %}


- In the **EXPLORER** window, right-click on `openmp` and select `New File`.
- Type `sum_series_for_2.c` as the file name and hits Enter. 

```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/sum_series_openmp_for_2.c"
```
- Is this implementation faster? Why?

{% enddetails %}
{% details Trapezoids %}

- Reimplement the trapezoid example using `#pragma parallel for`

{% enddetails %}
