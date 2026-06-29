---
layout: lecture
pretty_table: true
collection: csc231

title: "Code optimization"
toc:
  - name: Debugging
  - name: Performance realities
---
# Code optimization

{% details Relevant Reading %}

{% enddetails %}
:class: tip

This lecture will cover contents from [Chapter 12](https://diveintosystems.org/book/C12-CodeOpt/index.html) of the book. 

```


## Debugging

{% details Defects and Infections %}



{% enddetails %}
- A systematic approach to debugging. 
  - The programmer creates a defect 
  - The defect causes an infection 
  - The infection propagates 
  - The infection causes a failure
- Not every defect causes a failure!
- Testing can only show the presence of errors - not their absence. 
  - In other words, if you pass every tests, it means that your program has yet to fail. 
  It does not mean that your program is correct. 


{% details Explicit debugging %}



{% enddetails %}
- Stating the problem
  - Describe the problem aloud or in writing
  - A.k.a. `Rubber duck` or `teddy bear` method
- Often a comprehensive problem description is sufficient to solve the failure


{% details Scientific and brute force %}



{% enddetails %}
:::::{tab-set} 
::::{tab-item} Bad Fib

- A bad implementation of Fibonacci sequence

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=bad_fib.c"></script>

- Specification defined the first Fibonacci number as 1. 
- Compile and run the following `bad_fib.c` program:
- `fib(1)` returns an incorrect result. Why?

```bash
$ gcc -o bad_fib bad_fib.c
$ ./bad_fib
```
 
::::
::::{tab-item} Scientific debugging

- Before debugging, you need to construct a hypothesis as to the defect.
  - Propose a possible defect and why it explains the failure conditions
- `Ockham’s Razor`: given several hypotheses, pick the simplest/closest to current work

{% include figure.liquid path="assets/img/courses/csc231/06-optimization/01.png" width="50%" zoomable=true alt="Scientific debugging" %}

- Make predictions based on your hypothesis
  - What do you expect to happen under new conditions
  - What data could confirm or refute your hypothesis
- How can I collect that data?
  - What experiments?
  - What collection mechanism?
- Does the data refute the hypothesis?
  - Refine the hypothesis based on the new inputs
::::
::::{tab-item} SD: Bad Fib!
- Constructing a hypothesis: 
  - `while (n 1)`: did we mess up the loop in fib?
  - `int f`: did we forget to initialize `f`?
- Propose a new condition or conditions
  - What will logically happen if your hypothesis is correct?
  - What data can be 
  - fib(1) failed		// Hypothesis
    - Loop check is incorrect: Change to n >= 1 and run again.
    - f is uninitialized: Change to int f = 1;
- Experiment
  - Only change one condition at a time. 
  - fib(1) failed		// Hypothesis
    - Change to `n >= 1`: ???
    - Change to `int f = 1`: Works.  Sometimes a prediction can be a fix.
::::
::::{tab-item} Brute force

- Strict compilation flags: `-Wall`, `-Werror`. 
- Include optimization flags (**capital letter o**): `-O3` or `-O0`. 

```bash
$ gcc -Wall -Werror -O3 -o bad_fib bad_fib.c
```
 
- Use `valgrind`, memory analyzer. 

```bash
$ gcc -Wall -Werror -o bad_fib bad_fib.c
$ valgrind ./bad_fib
```
::::
::::{tab-item} Observation

- What is the observed result?
  - Factual observation, such as `Calling fib(1) will return 1.`
  - The conclusion will interpret the observation(s)
- Don’t interfere.
  - Sometimes `printf()` can interfere
  - Like quantum physics, sometimes observations are part of the experiment
- Proceed systematically.
  - Update the conditions incrementally so each observation relates to a specific change
- Do NOT ever proceed past first bug.
::::
:::::



{% details Learn from your mistakes (bugs) %}



{% enddetails %}
- Common failures and insights
  - Why did the code fail?
  - What are my common defects?
- Assertions and invariants
  - Add checks for expected behavior
  - Extend checks to detect the fixed failure
- Testing
  - Every successful set of conditions is added to the test suite

{% details Quick and dirty %}



{% enddetails %}
- Not every problem needs scientific debugging
- Set a time limit: (for example)
  - 0 minutes – -Wall, valgrind
  - 1 – 10 minutes – Informal Debugging
  - 10 – 60 minutes – Scientific Debugging
  - 60 minutes – Take a break / Ask for help
``` 



## Performance realities

{% details Overview %}



{% enddetails %}
- There’s more to performance than asymptotic complexity.
- Constant factors matter too!
  - Easily see 10:1 performance range depending on how code is written
  - Must optimize at multiple levels: algorithm, data representations, procedures, and loops
- Must understand system to optimize performance
  - How programs are compiled and executed
  - How modern processors + memory systems operate
  - How to measure program performance and identify bottlenecks
  - How to improve performance without destroying code modularity and generality.


{% details Leveraging cache blocks %}



{% enddetails %}
- Create the following two files called `matrix_mult.c` and `block_matrix_mult.c`

:::::{tab-set} 
::::{tab-item} matrix_mult.c

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=matrix_mult.c"></script>

::::
::::{tab-item} block_matrix_mult.c

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=block_matrix_mult.c"></script>

::::
:::::

- The difference between `matrix_mult.c` and `block_matrix_mult.c`lays with 
how the loops are broken up to align with cache size. 

:::::{tab-set} 
::::{tab-item} Cache blocks
- Check the size of cache blocks 

```bash
$ getconf -a | grep CACHE
```

{% include figure.liquid path="assets/img/courses/csc231/06-optimization/02.png" width="50%" zoomable=true alt="Cache size" %}

- We focus on cache blocks for optimization:
  - If calculations can be performed using smaller matrices of
  A, B, and C (blocks) that all fit in cache, we can further
  minimize the amount of cache misses per calculation. 

{% include figure.liquid path="assets/img/courses/csc231/06-optimization/03.png" width="50%" zoomable=true alt="Block division" %}

- 3 blocks are needed (for A, B, and C). 
- Each block has dimension B, so the total block size is $B^2$
- Therefore: $3B^{2} < cache_size$
- Based on the information above: B = 8 (so that `8 * 8 = 64` fits
in cache line).
- `3 * 8 * 8 < 32768`.
::::
::::{tab-item} Without cache

- Compile and run `matrix_mult.c`. 

```bash
$ gcc -o mm matrix_mult.c
$ ./mm 512
$ ./mm 1024
$ ./mm 2048
```

{% include figure.liquid path="assets/img/courses/csc231/06-optimization/04.png" width="50%" zoomable=true alt="Matrix with block optimization" %}

::::
::::{tab-item} With cache

- Compile and run `block_matrix_mult.c`. 

```bash
$ gcc -o bmm block_matrix_mult.c
$ ./bmm 512
$ ./bmm 1024
$ ./bmm 2048
```

{% include figure.liquid path="assets/img/courses/csc231/06-optimization/05.png" width="50%" zoomable=true alt="Matrix with block and compiler optimization" %}

::::
:::::



{% details General optimization: you or your compiler should do it. %}



{% enddetails %}
- Reduce code motion
- Reduction in strength

:::::{tab-set}
::::{tab-item} Reduce code motion
- Reduce frequency with which computation performed
  - Need to produce same results
  - Move code out of loop. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=block_matrix_mult_2.c"></script>
::::
::::{tab-item} Reduction in strength
- Replace costly operation with simpler ones (multiply to addition). 
- Recognize sequence of products.

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=block_matrix_mult_3.c"></script>
::::
::::{tab-item} Scripting

- Create the following file to automate the installations. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=eval.sh"></script>

```bash
$ chmod 755 eval.sh
$ ./eval.sh block_matrix_mult
$ ./eval.sh block_matrix_mult_2
$ ./eval.sh block_matrix_mult_3
```
::::
::::{tab-item} Outcome

{% include figure.liquid path="assets/img/courses/csc231/06-optimization/06.png" width="50%" zoomable=true alt="Other optimizations" %}

::::
:::::


{% details Intrinsic programming %}



{% enddetails %}
- A function whose implementation is handled specially by the compiler. 
- Languages: C, C++, Rust
  - HotSpot JVM for Java's JRE also has some intrinsic built-in (no direct access from programmers)
- Compilers for C/C++, Intel, and GCC implement intrinsics mapping directly to 
x86_64's single instructions, multiple data (SIMD) instructions. 
  - Streaming SIMD Extensions (SSE), SSE2, SSE3, AVX, AVX2, ...
  - [Vectorization: registers](https://cvw.cac.cornell.edu/vector/hw_registers)

:::::{tab-set}
::::{tab-item} Example: AVX/AVX2

- Addition 16 YMM registers to perform a single instruction on multiple data elements 
(SIMD).
- Each YMM register can hold and carry out the math operations on:
  - 8 32-bit single-precision floating point numbers (or integer), or
  - 4 64-bit double-precision floating point numbers (or long).

::::
::::{tab-item} Intrinsic Code

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=intrinsic_sum.c"></script>

```bash
$ gcc -mavx2 -o imm intrinsic_sum.c 
$ ./imm 1024
$ ./imm 2048
$ ./imm 4096
$ ./imm 8192
$ ./imm 16384
$ ./imm 32678
$ ./imm 33554432
```

::::
::::{tab-item} Outcome

{% include figure.liquid path="assets/img/courses/csc231/06-optimization/intrinsic_sum.png" width="50%" zoomable=true alt="Other optimizations" %}

::::
:::::



{% details General optimization: when your compiler can't. %}



{% enddetails %}
- Operate under fundamental constraint
 - Must not cause any change in program behavior
 - Often prevents optimizations that affect only "edge case" behavior
- Behavior obvious to the programmer is not obvious to compiler
  - e.g., Data range may be more limited than types suggest (short vs. int)
- Most analysis is only within a procedure
  - Whole-program analysis is usually too expensive
  - Sometimes compiler does inter-procedural analysis within a file (new GCC)
- Most analysis is based only on static information
  - Compiler has difficulty anticipating run-time inputs
- When in doubt, the compiler must be conservative

```
