---
layout: lecture
pretty_table: true
collection: csc466
course: CSC 466: Distributed and Parallel Computing
title: "Reduction"
toc:
  - name: Reduction
  - name: Reduction operators
  - name: Midterm Exam
---

# Reduction

## Reduction

{% details Motivation %}

- Let's review `sum_series_openmp_for.c`:

    ```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/sum_series_openmp_for.c"
    ```

- We used a shared data array for partial sums from the threads, this is to 
prevent data races. 

- Another solution: `reduction` clause. 

    ```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/sum_series.c"
    ```             

{% enddetails %}
{% details More reduction %}


- Can be done over `section`

    ```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/function_sections.c"
    ```   

- Can be done without `for`

    ```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/reduction_rand.c"
    ``` 

{% enddetails %}
{% details Hands-on %}

- Implement the parallel dot product for Lab 1 using reduction

{% enddetails %}
## Reduction operators

{% details Built-in reductions %}

- Arithmetic reductions: `+`, `*`, `max`, `min`.
    - `-` is deprecated as of OpenMP 5.2
- Logical reductions: `&`, `&&`, `|`, `||`, `^`

{% enddetails %}
{% details Custom reductions %}


- Formula:

```c
#pragma omp declare reduction (identifier : typelist : combiner) initializer (initializer expression)
```
- **This is all written on a single line!!!**
- To write this over multiple lines, a `\` is needed
- `initializer (initializer expression)` is optional

```c
#pragma omp declare reduction ( \
    identifier : typelist : combiner) \
    initializer (initializer expression)
```

- Example code for sum series:

    ```c linenums="1"
    --8<-- "docs/csc466/lectures/data/openmp/sum_series_custom.c"
    ```

{% enddetails %}
## Midterm Exam

- Midterm review: Monday March 03
    - Quiz retaking: Monday March 03
- Midterm exam: Wednesday March 05
- Debrief/In-class Assignment: Friday March 07
