---
layout: lecture
pretty_table: true
collection: csc466

title: "Introduction to OpenMP"
toc:
  - name: OpenMP overview
  - name: Write, compile, and run an OpenMP program
  - name: Trapezoid
---

# Introduction to OpenMP

## OpenMP overview

{% details Target hardware and software %}


- Target hardware is similar to thread programming
- Provide wrappers for `threads` and `fork/join` model of parallelism.   
  - Program originally runs in sequential mode. 
  - When parallelism is activated, multiple `threads` are `forked` from the 
  original proces/thread (`master` thread). 
  - Once the parallel tasks are done, `threads` are `joined` back to the original 
  process and return to sequential execution.  

{% include figure.liquid path="assets/img/courses/csc466/05-intro-openmp/fork-join.jpeg" width="50%" zoomable=true alt="Fork/join model for threads" %}

- The threads have access to all data in the `master` thread. This is `shared` data. 
- The threads also have their own private memory stack. 

{% enddetails %}
{% details Basic requirements %}


- Source code (C) needs to include `#include <omp.h>`   
- Compiling task need to have `-fopenmp` flag.  
- Specify the environment variable **OMP_NUM_THREADS**.   

{% enddetails %}
## Write, compile, and run an OpenMP program

{% details OMP directives %}


- OpenMP must be told when to parallelize.    
- For C/C++, `pragma` is used to annotate

~~~c
#pragma omp somedirective clause(value, othervalue)
  parallel statement;
~~~


- or

~~~c
#pragma omp somedirective clause(value, othervalue)
{
  parallel statement 1;
  parallel statement 2;
  ...
}
~~~

{% enddetails %}
{% details Hands-on: create hello_omp.c %}


- Log into `molly`
- Inside your `csc466` directory, create a file called `hello_omp.c` 
with the following contents: 

```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/hello_openmp.c"
```

- Compile and run:

~~~bash
gcc -o hello_omp hello_omp.c -fopenmp
export OMP_NUM_THREADS=4
./hello_omp
export OMP_NUM_THREADS=8
./hello_omp
~~~

- Line 1: Include `omp.h` to have libraries that support OpenMP. 
- Line 7: Declare the beginning of the `parallel` region. **Pay attention to how the curly bracket
is setup, comparing to the other curly  brackets.**
- Line 10: `omp_get_thread_num` gets the ID assigned to the thread and then assign
it to a variable named `tid` of type `int`.
- Line 15: `omp_get_num_threads` gets the value assigned to `OMP_NUM_THREADS` and return it to 
a variable named `nthreads` of type `int`. 

{% enddetails %}
{% details What's important? %}


- `tid` and `nthreads`.    
- They allow us to coordinate the parallel workloads.   
- Specify the environment variable **OMP_NUM_THREADS**. 

~~~bash
export OMP_NUM_THREADS=4
~~~

{% enddetails %}
## Trapezoid

{% details Overview %}


- Problem: estimate the integral of $y=x^2$ on $[2,8]$ using trapezoidal rule. 
four threads.     
- With 4 threads: `nthreads=4`. 
  - How to decide which thread will handle which segment?
  - How to get all results back together?    

{% include figure.liquid path="assets/img/courses/csc466/05-intro-openmp/06.png" width="50%" zoomable=true alt="Trapezoidal" %}

{% enddetails %}
{% details Implementation %}


- Inside your `csc466` directory, create a file called `trapezoid.c` 
with the following contents: 

```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/trapezoid_openmp_1.c"
```

- Compile and run `trapezoid.c`. 

{% enddetails %}
{% details A bit more detailed %}


- Modify the `trapezoid.c` so that it looks like below. 

```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/trapezoid_openmp_2.c"
```

{% enddetails %}
{% details Challenge 1: %}


Alternate the `trapezoid.c` code so that the parallel region will 
invokes a function to calculate the partial sum. 

```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/trapezoid_openmp_template.c"

{% details tip Solution %}


```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/trapezoid_openmp_3.c"
```

{% enddetails %}
{% enddetails %}
{% details Challenge 2: %}


- Write a program called `sum_series_1.c` that takes a single integer `N` as a command
line argument and calculate the sum of the first `N` non-negative integers.  
- Speed up the summation portion by using OpenMP.  
- Assume N is divisible by the number of threads. 

{% details tip Solution %}


```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/sum_series_1.c"
```

{% enddetails %}
{% enddetails %}
{% details Challenge 3: %}


- Write a program called `sum_series_2.c` that takes a single integer `N` as a command
line argument and calculate the sum of the first `N` non-negative integers.  
- Speed up the summation portion by using OpenMP.  
- There is no assumtion that N is divisible by the number of threads. 

{% details tip Solution %}


```c linenums="1"
--8<-- "docs/csc466/lectures/data/openmp/sum_series_2.c"
```

{% enddetails %}
{% enddetails %}
{% details Include timing %}


- Inside your `csc466` directory, create a file called `trapezoid_time.c` 
with the following contents: 

```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/trapezoid_openmp_time.c"
```

- How's the run time?

{% enddetails %}
