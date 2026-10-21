---
layout: lecture
pretty_table: true
collection: csc331
title: "Thread Programming: Learning to Think Concurrently"
toc:
  - name: "Creating threads and passing arguments"
  - name: "Waiting for threads with join"
  - name: "What exactly do threads share?"
  - name: "Shared-state experiment"
  - name: "Thread-safe by construction"
---

## Creating threads and passing arguments

{% details info The basic pthread pattern %}

A POSIX thread begins execution in a function with this general form:

```c
void *worker(void *arg)
```

`pthread_create()` needs:

```c
pthread_create(
    &thread_id,     // where pthread stores the new thread identifier
    NULL,           // default thread attributes
    worker,         // function where execution begins
    argument        // one pointer passed to worker()
);
```

The argument is a `void *`.

That means we can pass almost anything, as long as we understand what the
pointer points to and how long that object remains alive.

{% enddetails %}


{% details example Give each thread an identity %}

Create `thread_ids.c`:

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *worker(void *arg) {
    int id = *(int *)arg;
    printf("Hello from worker %d\n", id);
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s number-of-threads\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    pthread_t threads[n];
    int ids[n];

    for (int i = 0; i < n; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
```

Compile:

```bash
gcc -Wall -Wall -pthread thread_ids.c -o thread_ids
```

Run several times:

```bash
./thread_ids 4
./thread_ids 4
./thread_ids 8
```

{% details question %}

1. Are the workers always printed in numerical order?
2. Does thread 0 necessarily execute first because it was created first?
3. What does `pthread_create()` actually guarantee?
4. What does it **not** guarantee?

{% enddetails %}

{% enddetails %}


{% details danger An argument-passing scenario %}

Why are we wasting an array for `ids[n]`?

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *worker(void *arg) {
    int id = *(int *)arg;
    printf("Hello from worker %d\n", id);
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s number-of-threads\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    pthread_t threads[n];

    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, worker, &i);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
```

```c
for (int i = 0; i < n; i++) {
    pthread_create(&threads[i], NULL, worker, &i);
}
```

{% details question %}

- What object is shared?
- Which threads access it?
- Which accesses change it?
- Does the programmer control the ordering of those accesses?

{% enddetails %}

{% enddetails %}


## Waiting for threads with join

{% details info Thread creation is not thread completion %}

Consider:

```c
pthread_create(&t, NULL, worker, NULL);
printf("main is finished\n");
```

- Creating the thread means that this thread is now eligible to execute.
- It does **not** guarantee that the execution of this thread complete before returning.
    - `pthread_join()` ensures that thhe caller does not continue past the join until `t` has finished.

```c
pthread_join(t, NULL);
```

{% enddetails %}


{% details example Remove the join %}

Create `join_demo.c`:

```c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *worker(void *arg) {
    for (int i = 0; i < 5; i++) {
        printf("worker: %d\n", i);
        usleep(100000);
    }
    return NULL;
}

int main(void) {
    pthread_t t;

    pthread_create(&t, NULL, worker, NULL);
    printf("main: I created the worker\n");

    // Try the program first without this line.
    pthread_join(t, NULL);
    printf("main: worker has finished\n");

    return 0;
}
```

Compile and run. Then comment out:

```c
pthread_join(t, NULL);
```

{% details question %}

- Explain the outputs after several runs?

{% enddetails %}
{% enddetails %}


{% details example Returning a result from a thread %}

A thread may return a pointer:

```c
void *square(void *arg) {
    int x = *(int *)arg;
    int *answer = malloc(sizeof(int));
    *answer = x * x;
    return answer;
}
```

The parent can retrieve it through `pthread_join()`:

```c
int value = 12;
pthread_t t;

pthread_create(&t, NULL, square, &value);

void *result;
pthread_join(t, &result);

printf("%d squared = %d\n", value, *(int *)result);

free(result);
```

This is often cleaner than having every worker modify one global result.

{% enddetails %}


## What exactly do threads share?

{% details info Process resources versus thread execution state %}

Threads in the same process share:

- code;
- global variables;
- heap;
- open files;
- process address space.

Each thread has its own:

- program counter;
- register state;
- stack;
- execution history.

{% enddetails %}


{% details example Global, heap, and stack addresses %}

Create `addresses.c`:

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int global_value = 10;

typedef struct {
    int id;
    int *heap_value;
} worker_arg;

void *worker(void *arg) {
    worker_arg *a = arg;

    int local_value = 100 + a->id;
    printf ("thread %d: &global=%p heap=%p &local=%p\n", a->id,
        (void *)&global_value,
        (void *)a->heap_value,
        (void *)&local_value
    );

    return NULL;
}

int main(void) {
    pthread_t t[2];
    worker_arg args[2];

    int *heap_value = malloc(sizeof(int));
    *heap_value = 42;

    for (int i = 0; i < 2; i++) {
        args[i].id = i;
        args[i].heap_value = heap_value;
        pthread_create(&t[i], NULL, worker, &args[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(t[i], NULL);
    }

    free(heap_value);
    return 0;
}
```

{% details success Observations %}

- For both threads:
    - `&global_value` should be the same;
    - `heap_value` should be the same;
    - `&local_value` should be different.

So a local variable can be naturally private simply because each thread
has a different stack.

{% enddetails %}
{% enddetails %}

## Shared-state experiment

{% details danger The innocent-looking counter %}

Create `counter.c`:

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long counter = 0;

typedef struct {
    long loops;
} arg_t;

void *worker(void *arg) {
    arg_t *a = arg;

    for (long i = 0; i < a->loops; i++) {
        counter++;
    }

    return NULL;
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);
    long loops = atol(argv[2]);

    pthread_t threads[n];
    arg_t arg = {.loops = loops};

    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, worker, &arg);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("expected: %ld\n", (long)n * loops);
    printf("actual:   %ld\n", counter);

    return 0;
}
```

Compile with optimization disabled:

```bash
gcc -Wall -Wextra -O0 -pthread counter.c -o counter
```

Try:

```bash
./counter 1 1000000
./counter 2 1000000
./counter 4 1000000
./counter 8 1000000
```

Run each one several times.

{% enddetails %}


{% details question But `counter++` is one line! %}

One line of C does not imply one indivisible machine operation.

Conceptually:

```c
counter++;
```

requires something like:

```text
load counter into a register
add 1
store register back to counter
```

Imagine:

```text
counter = 10
```

Then:

| Thread A | Thread B | counter |
| --- | --- | ---: |
| load 10 |  | 10 |
|  | load 10 | 10 |
| add -> 11 |  | 10 |
|  | add -> 11 | 10 |
| store 11 |  | 11 |
|  | store 11 | 11 |

- Two increments occurred but the final value increased by only one. As a result, one update was **lost**.
- We will give this problem its formal name in the next lecture.

{% enddetails %}


{% details example Look below the C statement %}

Generate assembly code from compiling

```bash
gcc -O0 -S counter.c -o counter.s
```

Search for accesses to `counter` or inspect the executable:

```bash
objdump -d counter | less
```

*The exact assembly depends on the machine and compiler.*

{% enddetails %}


{% details danger A bank account with no bank rules %}

Consider:

```c
int balance = 100;

void withdraw(int amount) {
    if (balance >= amount) {
        balance = balance - amount;
    }
}
```

Two threads concurrently execute:

```c
withdraw(80);
```

{% details question Could both withdrawals succeed? %}

One possible execution:

```text
T1: check balance >= 80      // sees 100: yes
T2: check balance >= 80      // sees 100: yes
T1: compute 100 - 80
T2: compute 100 - 80
T1: balance = 20
T2: balance = 20
```

{% enddetails %}

{% enddetails %}


{% details info A useful way to inspect concurrent code %}

When you see shared state, ask four questions:

1. **What data is shared?**
2. **Who reads it?**
3. **Who writes it?**
4. **Does correctness depend on two or more operations staying together?**

Suspicious patterns include:

```c
x++;
```

```c
x = x + value;
```

```c
if (condition)
    change_shared_state();
```

```c
if (queue_not_empty())
    remove_item();
```

```c
if (slot_is_free())
    claim_slot();
```

- The fourth question is especially important.
    - A correct concurrent program often needs several ordinary instructions to behave as though they were one conceptual action.

{% enddetails %}


## Thread-safe by construction

{% details success Avoid sharing whenever possible %}

- Not every parallel program needs workers to modify the same data.
- Suppose we want the sum of an array.

Bad conceptual design:

```text
every worker repeatedly updates one global total
```

Better design:

```text
worker 0 computes partial[0]
worker 1 computes partial[1]
worker 2 computes partial[2]
worker 3 computes partial[3]

main joins workers
main adds partial results
```

- During the parallel phase, each thread owns a separate result slot and no two workers write the same location.

{% enddetails %}


{% details example Parallel sum without locks %}

Create `parallel_sum.c`:

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    const int *array;
    long begin;
    long end;
    long result;
} work_t;

void *sum_range(void *arg)
{
    work_t *work = arg;

    long total = 0;

    for (long i = work->begin; i < work->end; i++) {
        total += work->array[i];
    }

    // Each worker writes only to its own work_t structure.
    work->result = total;

    return NULL;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s array-size threads\n", argv[0]);
        return 1;
    }

    long n = atol(argv[1]);
    int thread_count = atoi(argv[2]);

    int *array = malloc(sizeof(int) * n);
    pthread_t *threads = malloc(sizeof(pthread_t) * thread_count);
    work_t *work = malloc(sizeof(work_t) * thread_count);

    for (long i = 0; i < n; i++) {
        array[i] = 1;
    }

    long chunk = (n + thread_count - 1) / thread_count;

    for (int t = 0; t < thread_count; t++) {
        long begin = t * chunk;
        long end = begin + chunk;

        if (end > n) {
            end = n;
        }

        work[t].id = t;
        work[t].array = array;
        work[t].begin = begin;
        work[t].end = end;
        work[t].result = 0;

        pthread_create(&threads[t], NULL, sum_range, &work[t]);
    }

    long total = 0;

    for (int t = 0; t < thread_count; t++) {
        pthread_join(threads[t], NULL);

        printf(
            "thread %d: [%ld, %ld) -> %ld\n",
            work[t].id,
            work[t].begin,
            work[t].end,
            work[t].result
        );

        total += work[t].result;
    }

    printf("total = %ld\n", total);

    free(work);
    free(threads);
    free(array);

    return 0;
}
```

Compile:

```bash
gcc -Wall -Wextra -O0 -pthread parallel_sum.c -o parallel_sum
```

Try:

```bash
./parallel_sum 100 1
./parallel_sum 100 2
./parallel_sum 100 4
./parallel_sum 100 7
```

### Why is this safe without a lock?

All threads read the shared array.

But:

```c
work[t].result
```

has exactly one writer. The main thread reads the results only **after joining** the workers.

{% enddetails %}


{% details challenge Transform an array %}

We want to compute:

```c
output[i] = input[i] * input[i];
```

for an array of `N` values.

Start with:

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 40

int input[N];
int output[N];

typedef struct {
    int id;
    int begin;
    int end;
} work_t;

void *square_range(void *arg)
{
    work_t *work = arg;

    for (int i = work->begin; i < work->end; i++) {
        output[i] = input[i] * input[i];

        printf(
            "thread %d computed output[%d]\n",
            work->id,
            i
        );
    }

    return NULL;
}
```

Write `main()` so that:

1. `input[i] = i`;
2. four worker threads are created;
3. each thread receives a non-overlapping quarter of the array;
4. main joins all four workers;
5. main verifies every output value.

Do **not** use:

- mutexes;
- semaphores;
- condition variables;
- sleeps.

{% details challenge Additional Follow-up %}

Change the partitioning from contiguous chunks:

```text
T0: 0..9
T1: 10..19
T2: 20..29
T3: 30..39
```

to interleaved work:

```text
T0: 0, 4, 8,  ...
T1: 1, 5, 9,  ...
T2: 2, 6, 10, ...
T3: 3, 7, 11, ...
```

{% enddetails %}


{% details question %}
- Which version is easier to reason about?
- Which might have better memory locality?
{% enddetails %}



{% enddetails %}
