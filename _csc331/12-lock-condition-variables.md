---
layout: lecture
pretty_table: true
collection: csc331

title: "Lock and Condition Variables"
toc:
  - name: Overview
  - name: Lock
  - name: "First attempt: controlling interrupts"
  - name: "Scenario: one thread waiting on another"
  - name: "The producer/consumer (bounded buffer) problem"
---

## Overview

{% details Recall the problem from intro-to-os %}

<script src="https://gist.github.com/linhbngo/d2f3a0b28b73a3f48c751410c6c91fd6.js?file=threads.c"></script>

{% include figure.liquid path="assets/img/courses/csc331/lock/01.png" max-width="50%" zoomable=true %}

- Two concurrent threads manipulated a shared resource (the counter variable) 
without any synchronization.
    - Outcome depends on the order in which accesses take place -- this is called a 
    **race condition**.
- We need to ensure that only one thread at a time can manipulate the shared resource so 
that we can reason about program behavior, in a sane way 
    - We need **synchronization**.

{% enddetails %}

{% details What is shared/not shared in a multithreaded program? %}

{% include figure.liquid path="assets/img/courses/csc331/lock/02.png" max-width="50%" zoomable=true %}

{% enddetails %}

{% details info Key definitions %}

- A **critical section** (CS) is a segment of code that accesses a shared resource, 
usually a variable or data structure.
- A **race condition** (**data race**) arises if multiple threads of execution enter 
the critical section at roughly the same time; both attempt to update the shared data 
structure, leading to a surprising and undesirable outcome. 
- An **indeterminate** program consists of one or more race conditions. The outcome 
is thus not deterministic. 
- To avoid these problem, threads should use some kind of mutual exclusion primitives. 
Doing so guarantees that only a single thread ever enters a critical section, thus 
avoiding races and resulting in deterministic program outputs.

{% enddetails %}

{% details Requirements for Critical Section Handling %}

- `Mutual Exclusion`: if one thread is in the CS, then no other is
- `Progress`: threads waiting for access to CS are not prevented from entering by 
threads not in the CS; threads do not wait indefinitely.
- `Bounded Waiting` (no starvation): all waiting threads are guaranteed to eventually 
get access to the CS.
- `Performance`: The overhead of entering and exiting the CS is small compared to the work 
done within it.

{% enddetails %}


## Lock

{% details Definition %}

- `Atomic instruction`: A machine instruction that can be executed in a single clock cycle. 
- Programmers annotate source code with **locks** around a critical section, ensuring that it 
behaves like a single atomic instruction. 
- What is a **lock**?
    - Is declared as a lock variable. 
    - The lock variable holds the state of the lock. 
    - The states are either:
        - Available (unlocked or free): No thread holds the lock
        - Acquired (locked or held): Exactly one thread holds the lock and presumably is in a 
        critical section.
    - The lock variable can also hold additional information (often hidden from users):
        - Which thread is holding the lock
        - A queue for ordering lock acquisition
        - ...

{% enddetails %}

{% details Semantic of locking: lock() and unlock() %}

- A thread calls `lock()` when it tries to acquire the lock:
    - If no other thread is holding the lock, the thread will acquire the lock and enter the 
    critical section (becomes owner of the lock).
    - If another thread is holding the lock, the call will not return. 
- Once the lock owner is finished, it calls unlock() and the lock becomes available. 
    - If there is no waiting thread, the lock becomes free.
    - If there are some waiting threads, one of them will acquire the lock and enter the critical 
    section. 
- Lock in `pthread`: https://linux.die.net/man/3/pthread_mutex_lock 

{% enddetails %}

{% details question How do we build a lock? %}

- How do we build an efficient lock?
- What hardware support is needed?
- What OS support is needed? 

{% enddetails %}


{% details solution Criteria of a good lock %}

- Mutual exclusion
- Fairness
- Performance

{% enddetails %}

## First attempt: controlling interrupts

{% details Overview %}

- One of the earliest solutions for single processor systems. 
    - `lock()` will disable interrupts. 
    - `unlock()` will enable interrupts. 
- Advantages
    - Simplicity
- Disadvantages
    - Allow user programs to perform privileged operations
    - Disable interrupts carries significant implication in preventing OS from 
    performing interventions. 
    - Do not work on multi-processors (since another thread can still enter the 
    critical section via different computing core).
    - Prevent non-locking interrupts to take place. For example, disk I/O interrupts.
    - Inefficient. It is difficult to implement code that mask/unmask interrupts. 

{% enddetails %}

{% details info We need CPU hardware support %}

- Simple principle: Load and Store a **lock** flag
- Correctness: 
    - Interrupts can still lead to inconsistency issues
- Performance:
    - The waiting threads need to keep checking the condition of the flag (spin-waiting)

```c
typedef struct __lock_t (
    int flag; 
) lock_t;

void init (lock_t *mutex) {
    // 0: lock is available, 1: lock is held
    mutex->flag = 0;
}

void lock (lock_t *mutext) {
    while (mutex->flag == 1) // TEST the flag
        ; // spin-wait (do nothing)
    mutex->flag = 1; //now SET it!
}

void unlock (lock_t *mutext) {
    mutext->flag = 0;
}
```

{% enddetails %}

{% details Spin lock with Test-and-Set %}

- Hardware support for locking begins in early 1960.
- `TestAndSet` can be performed atomically by hardware. 

{% details info How does it work? %}
- Lock is free:
    - flag is 0
    - TestAndSet returns the old value of flag (break the loop) but also set 
    the value of the flag (acquire the lock).
- Lock is not free:
  - flag is 1 
  - TestAndSet keeps setting the lock but also spinning inside the while loop until the 
  lock is released. 

<div class="code-pair" style="--code-frame-height: 14rem">
<div class="code-frame">
<div class="code-frame-title">First attempt: a simple flag</div>
<div class="code-frame-body" markdown="block">

```c
typedef struct __lock_t { int flag; } lock_t;

void init(lock_t *mutex) {
    // 0 -> lock is available, 1 -> held
    mutex->flag = 0;
}

void lock(lock_t *mutex) {
    while (mutex->flag == 1) // TEST the flag
        ; // spin-wait (do nothing)
    mutex->flag = 1;         // now SET it!
}

void unlock(lock_t *mutex) {
    mutex->flag = 0;
}
```

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">Spin lock using test-and-set</div>
<div class="code-frame-body" markdown="block">

```c
typedef struct __lock_t {
    int flag;
} lock_t;

void init(lock_t *lock) {
    // 0: lock is available, 1: lock is held
    lock->flag = 0;
}

void lock(lock_t *lock) {
    while (TestAndSet(&lock->flag, 1) == 1)
        ; // spin-wait (do nothing)
}

void unlock(lock_t *lock) {
    lock->flag = 0;
}
```

</div>
</div>
</div>

{% enddetails %}

{% details info Evaluating the basic spin lock %}

- Correctness: Yes
- Fairness: No - can lead to starvation
- Performance: 
    - TestAndSet requires CPU cycle (even as an atomic operation)

{% enddetails %}

{% enddetails %}

## Scenario: one thread waiting on another

{% details info Code for Scenario %}

```c
void *child(void *arg) {
    printf("child\n");
    // how to indicate we are done?
    // ...
    return NULL;
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    pthread_t c;
    Pthread_create(&c, NULL, child, NULL); // create child
    // how to wait for child?
    // ...
    printf("parent: end\n");
    return 0;
}
```

{% enddetails %}


{% details solution A lock-based solution %}

- How to implement a lock-based solution? 

```c
volatile int done = 0;

void *child(void *arg) {
    printf("child\n");
    done = 1;
    return NULL;
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    pthread_t c;
    Pthread_create(&c, NULL, child, NULL); // create child
    while (done == 0)
        ; // spin
    printf("parent: end\n");
    return 0;
}
```

{% details question What is the issue? %}
- Cycle burning by `parent` while *spinning*.
{% enddetails %}


{% enddetails %}

{% details info How to wait for a condition? %}

- Condition Variable: an explicit queue that threads can put themselves 
on when some state of execution (condition) is not as desired (waiting 
on the condition).
- When the state is changed, the condition variable can wake up one (or 
more) of the waiting threads to continue. 
- [pthread_cond_wait](https://linux.die.net/man/3/pthread_cond_wait)
- [pthread_cond_signal](https://linux.die.net/man/3/pthread_cond_signal)

{% enddetails %}

{% details Lock and conditional variable %}

```c
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit() {
    Pthread_mutex_lock(&m);
    done = 1;
    Pthread_cond_signal(&c);
    Pthread_mutex_unlock(&m);
}

void *child(void *arg) {
    printf("child\n");
    thr_exit();
    return NULL;
}

void thr_join() {
    Pthread_mutex_lock(&m);
    while (done == 0)
        Pthread_cond_wait(&c, &m);
    Pthread_mutex_unlock(&m);
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    pthread_t p;
    Pthread_create(&p, NULL, child, NULL);
    thr_join();
    printf("parent: end\n");
    return 0;
}
```

{% details Screenshot %}
{% include figure.liquid path="assets/img/courses/csc331/lock/09.png" max-width="50%" zoomable=true %}
{% enddetails %}

{% enddetails %}


{% details question Do we really need both? %}

- Infinite sleep for parent thread. 
- Why?

<div class="code-pair" style="--code-frame-height: 16rem">
<div class="code-frame">
<div class="code-frame-title">Lock and condition variable</div>
<div class="code-frame-body" markdown="block">

```c
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit() {
    Pthread_mutex_lock(&m);
    done = 1;
    Pthread_cond_signal(&c);
    Pthread_mutex_unlock(&m);
}

void *child(void *arg) {
    printf("child\n");
    thr_exit();
    return NULL;
}

void thr_join() {
    Pthread_mutex_lock(&m);
    while (done == 0)
        Pthread_cond_wait(&c, &m);
    Pthread_mutex_unlock(&m);
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    pthread_t p;
    Pthread_create(&p, NULL, child, NULL);
    thr_join();
    printf("parent: end\n");
    return 0;
}
```

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">Condition variable only</div>
<div class="code-frame-body" markdown="block">

```c
void thr_exit() {
    done = 1;
    Pthread_cond_signal(&c);
}

void thr_join() {
    if (done == 0)
        Pthread_cond_wait(&c);
}
```

</div>
</div>
</div>

{% details Screenshot %}
{% include figure.liquid path="assets/img/courses/csc331/lock/10.png" max-width="50%" zoomable=true %}
{% enddetails %}

{% enddetails %}


## The producer/consumer (bounded buffer) problem

{% details info Problem Statement %}

- Proposed in 1972 by Edsger W. Dijkstra
- Imagine one or more producer threads and one or more consumer 
threads. 
    - Producers generate data items and place them in a buffer; 
    - Consumers grab said items from the buffer and consume them 
    in some way.
- Occurs in many real systems
    - Multi-threaded web servers
    - Linux pipe
- Generalization: many producers/consumers running concurrently. 
- Requirement:
    - Only place data in buffer when count is 0 (available space on buffer)
    - Only grab data from buffer when count is 1 (buffer is full)

{% enddetails %}


{%d details warning Vanilla (not thread-safe) %}

<div class="code-pair" style="--code-frame-height: 16rem">
<div class="code-frame">
<div class="code-frame-title">put and get</div>
<div class="code-frame-body" markdown="block">

```c
int buffer;
int count = 0; // initially, empty

void put(int value) {
    assert(count == 0);
    count = 1;
    buffer = value;
}

int get() {
    assert(count == 1);
    count = 0;
    return buffer;
}
```

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">producer and consumer</div>
<div class="code-frame-body" markdown="block">

```c
void *producer(void *arg) {
    int i;
    int loops = (int) arg;
    for (i = 0; i < loops; i++) {
        put(i);
    }
}

void *consumer(void *arg) {
    int i;
    while (1) {
        int tmp = get();
        printf("%d\n", tmp);
    }
}
```

</div>
</div>
</div>

{% enddetails %}

{% details First implementation %}

- Start with 1 CV and 1 lock.
- Work with 1 producer and 1 consumer. 
- What happens if we have more consumers?

<div class="code-pair" style="--code-frame-height: 16rem">
<div class="code-frame">
<div class="code-frame-title">put and get</div>
<div class="code-frame-body" markdown="block">

```c
int buffer;
int count = 0; // initially, empty

void put(int value) {
    assert(count == 0);
    count = 1;
    buffer = value;
}

int get() {
    assert(count == 1);
    count = 0;
    return buffer;
}
```

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">producer and consumer</div>
<div class="code-frame-body" markdown="block">

```c
int loops; // must initialize somewhere...
cond_t cond;
mutex_t mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Pthread_mutex_lock(&mutex);           // p1
        if (count == 1)                        // p2
            Pthread_cond_wait(&cond, &mutex);  // p3
        put(i);                                // p4
        Pthread_cond_signal(&cond);            // p5
        Pthread_mutex_unlock(&mutex);          // p6
    }
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Pthread_mutex_lock(&mutex);           // c1
        if (count == 0)                        // c2
            Pthread_cond_wait(&cond, &mutex);  // c3
        int tmp = get();                       // c4
        Pthread_cond_signal(&cond);            // c5
        Pthread_mutex_unlock(&mutex);          // c6
        printf("%d\n", tmp);
    }
}
```

</div>
</div>
</div>

{% enddetails %}


{% details danger First implementation (broken) %}

<div class="code-pair" style="--code-frame-height: 16rem">
<div class="code-frame">
<div class="code-frame-title">Thread trace</div>
<div class="code-frame-body" markdown="block">

| T<sub>c1</sub> | State | T<sub>c2</sub> | State | T<sub>p</sub> | State | Count | Comment |
| --- | --- | --- | --- | --- | --- | --- | --- |
| c1 | Running |  | Ready |  | Ready | 0 |  |
| c2 | Running |  | Ready |  | Ready | 0 |  |
| c3 | Sleep |  | Ready |  | Ready | 0 | Nothing to get |
|  | Sleep |  | Ready | p1 | Running | 0 |  |
|  | Sleep |  | Ready | p2 | Running | 0 |  |
|  | Sleep |  | Ready | p4 | Running | 1 | Buffer now full |
|  | Ready |  | Ready | p5 | Running | 1 | T<sub>c1</sub> awoken |
|  | Ready |  | Ready | p6 | Running | 1 |  |
|  | Ready |  | Ready | p1 | Running | 1 |  |
|  | Ready |  | Ready | p2 | Running | 1 |  |
|  | Ready |  | Ready | p3 | Sleep | 1 | Buffer full; sleep |
|  | Ready | c1 | Running |  | Sleep | 1 | T<sub>c2</sub> sneaks in ... |
|  | Ready | c2 | Running |  | Sleep | 1 |  |
|  | Ready | c4 | Running |  | Sleep | 0 | ... and grabs data |
|  | Ready | c5 | Running |  | Ready | 0 | T<sub>p</sub> awoken |
|  | Ready | c6 | Running |  | Ready | 0 |  |
| c4 | Running |  | Ready |  | Ready | 0 | Oh oh! No data |

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">Code</div>
<div class="code-frame-body" markdown="block">

```c
int loops; // must initialize somewhere...
cond_t cond;
mutex_t mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Pthread_mutex_lock(&mutex);           // p1
        if (count == 1)                        // p2
            Pthread_cond_wait(&cond, &mutex);  // p3
        put(i);                                // p4
        Pthread_cond_signal(&cond);            // p5
        Pthread_mutex_unlock(&mutex);          // p6
    }
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Pthread_mutex_lock(&mutex);           // c1
        if (count == 0)                        // c2
            Pthread_cond_wait(&cond, &mutex);  // c3
        int tmp = get();                       // c4
        Pthread_cond_signal(&cond);            // c5
        Pthread_mutex_unlock(&mutex);          // c6
        printf("%d\n", tmp);
    }
}
```

</div>
</div>
</div>

{% details question Why? %}

- After the producer wakes  a consumer, the state of bound buffer 
changed for the consumer due to the other consumer. 
- Signaling a state only wakes them up (implying a state changes) 
but does not guarantee maintaining a desired state. 
- This is called Mesa semantics
    - "Experience with Processes and Monitors in Mesa" by B.W. Lampson, 
    D.R. Redell. Communications of the ACM. 23:2, pages 105-117, 
    February 1980
    - Virtually all computing systems are built using Mesa semantics.
- Hoare semantics
    - Stronger guarantee that the woken thread will run immediately upon 
  being woken. 

{% enddetails %}

{% enddetails %}


{% details warning Second implementation (slightly less broken) %}

<div class="code-pair" style="--code-frame-height: 16rem">
<div class="code-frame">
<div class="code-frame-title">Thread trace</div>
<div class="code-frame-body" markdown="block">

| T<sub>c1</sub> | State | T<sub>c2</sub> | State | T<sub>p</sub> | State | Count | Comment |
| --- | --- | --- | --- | --- | --- | --- | --- |
| c1 | Running |  | Ready |  | Ready | 0 |  |
| c2 | Running |  | Ready |  | Ready | 0 |  |
| c3 | Sleep |  | Ready |  | Ready | 0 | Nothing to get |
|  | Sleep | c1 | Running |  | Ready | 0 |  |
|  | Sleep | c2 | Running |  | Ready | 0 |  |
|  | Sleep | c3 | Sleep |  | Ready | 0 | Nothing to get |
|  | Sleep |  | Sleep | p1 | Running | 0 |  |
|  | Sleep |  | Sleep | p2 | Running | 0 |  |
|  | Sleep |  | Sleep | p4 | Running | 1 | Buffer now full |
|  | Ready |  | Sleep | p5 | Running | 1 | T<sub>c1</sub> awoken |
|  | Ready |  | Sleep | p6 | Running | 1 |  |
|  | Ready |  | Sleep | p1 | Running | 1 |  |
|  | Ready |  | Sleep | p2 | Running | 1 |  |
|  | Ready |  | Sleep | p3 | Sleep | 1 | Must sleep (full) |
| c2 | Running |  | Sleep |  | Sleep | 1 | Recheck condition |
| c4 | Running |  | Sleep |  | Sleep | 0 | T<sub>c1</sub> grabs data |
| c5 | Running |  | Ready |  | Sleep | 0 | Oops! Woke T<sub>c2</sub> |
| c6 | Running |  | Ready |  | Sleep | 0 |  |
| c1 | Running |  | Ready |  | Sleep | 0 |  |
| c2 | Running |  | Ready |  | Sleep | 0 |  |
| c3 | Sleep |  | Ready |  | Sleep | 0 | Nothing to get |
|  | Sleep | c2 | Running |  | Sleep | 0 |  |
|  | Sleep | c3 | Sleep |  | Sleep | 0 | Everyone asleep... |

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">Code</div>
<div class="code-frame-body" markdown="block">

```c
int loops;
cond_t cond;
mutex_t mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Pthread_mutex_lock(&mutex);           // p1
        while (count == 1)                     // p2
            Pthread_cond_wait(&cond, &mutex);  // p3
        put(i);                                // p4
        Pthread_cond_signal(&cond);            // p5
        Pthread_mutex_unlock(&mutex);          // p6
    }
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Pthread_mutex_lock(&mutex);           // c1
        while (count == 0)                     // c2
            Pthread_cond_wait(&cond, &mutex);  // c3
        int tmp = get();                       // c4
        Pthread_cond_signal(&cond);            // c5
        Pthread_mutex_unlock(&mutex);          // c6
        printf("%d\n", tmp);
    }
}
```

</div>
</div>
</div>

{% enddetails %}



{% details success Third implementation (finally work) %}

- Consumer only wake producer and vice versa
- Two condition variables are needed. 
- Not yet generalized. 

```c
cond_t empty, fill;
mutex_t mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Pthread_mutex_lock(&mutex);
        while (count == 1)
            Pthread_cond_wait(&empty, &mutex);
        put(i);
        Pthread_cond_signal(&fill);
        Pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Pthread_mutex_lock(&mutex);
        while (count == 0)
            Pthread_cond_wait(&fill, &mutex);
        int tmp = get();
        Pthread_cond_signal(&empty);
        Pthread_mutex_unlock(&mutex);
        printf("%d\n", tmp);
    }
}
```

{% enddetails %}


{% details info A generalized solution %}

<div class="code-pair" style="--code-frame-height: 16rem">
<div class="code-frame">
<div class="code-frame-title">bounded buffer</div>
<div class="code-frame-body" markdown="block">

```c
int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value) {
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

int get() {
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}
```

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">producer and consumer</div>
<div class="code-frame-body" markdown="block">

```c
cond_t empty, fill;
mutex_t mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Pthread_mutex_lock(&mutex);            // p1
        while (count == MAX)                    // p2
            Pthread_cond_wait(&empty, &mutex);  // p3
        put(i);                                 // p4
        Pthread_cond_signal(&fill);             // p5
        Pthread_mutex_unlock(&mutex);           // p6
    }
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Pthread_mutex_lock(&mutex);            // c1
        while (count == 0)                      // c2
            Pthread_cond_wait(&fill, &mutex);   // c3
        int tmp = get();                        // c4
        Pthread_cond_signal(&empty);            // c5
        Pthread_mutex_unlock(&mutex);           // c6
        printf("%d\n", tmp);
    }
}
```

</div>
</div>
</div>

{% enddetails %}

