---
layout: lecture
pretty_table: true
collection: csc331

title: "Semaphores"
toc:
  - name: Semaphore
  - name: "Producer/Consumer"
  - name: The Dining Philosophers
---

## Semaphore

{% details info What have we learned so far? %}

- Both lock and condition variables are needed to solve more complex 
concurrency problems. 
- Can we do better?

{% enddetails %}


{% details The structure of the "THE" multiprogramming system %}

- Dijkstra, Edsger W. In **The origin of concurrent programming**, pp. 139-152. Springer, New York, NY, 1968.
    - [PDF](https://dl.acm.org/doi/pdf/10.1145/363095.363143)
- Together with colleagues, developed semaphore as a single primitive for all things 
related to synchronization. 
    - Technical details are described in the Appendix of the article
    - This is written whil Dijkstra was at Technological Universtiy, Eindhoven, The Netherlands
    - Processs Q performs operation `P(sem)` means `prolaag` : try to decrease
        - If resulting `sem` is **non-negative**, Q can process. 
        - Else, Q stops and gets on a wait list associated with `sem`. 
    - Process R performs operation `V(sem)` means `verhogen`: try to increase
        - If resulting value of `sem` is positive, nothing happens. 
        - Else, one of the processes on the associated wait list is woken up to execute. 

{% details info Corollary 1 %}
If the semaphore value is **non-positive**, its absolute value equals the number of processes booked on its waiting list. 
{% enddetails %}

{% details info Corollary 2 %}
- The `P` operation represents the potential delay. 
- The `V` operation represents the removal of a barrier.
{% enddetails %}

{% enddetails %}

{% details info Semaphore %}

{% details note Overview %}

- Is an object with an integer value that can be manipulated with two routines:
    - [sem_wait()](https://man7.org/linux/man-pages/man3/sem_wait.3.html)
    - [sem_post()](https://www.man7.org/linux/man-pages/man3/sem_post.3.html)    
    - They are **atomic operations**
- Needs to be initialized to some value. 
    - [sem_init()](http://man7.org/linux/man-pages/man3/sem_init.3.html)


{% details question %}

More importantly, how do we use `sem_wait()` and `sem_post()` to facilitate 
synchronization for concurrency?

{% enddetails %}

{% enddetails %}


{% details Semaphore as lock (binary semaphore) %}

<div class="code-pair" style="--code-frame-height: 16rem">
<div class="code-frame">
<div class="code-frame-title">Thread trace</div>
<div class="code-frame-body" markdown="block">

| Value | Thread 0 | State | Thread 1 | State |
| --- | --- | --- | --- | --- |
| 1 |  | Running |  | Ready |
| 1 | call sem_wait() | Running |  | Ready |
| 0 | sem_wait() returns | Running |  | Ready |
| 0 | (crit sect: begin) | Running |  | Ready |
| 0 | Interrupt; Switch→T1 | Ready |  | Running |
| 0 |  | Ready | call sem_wait() | Running |
| -1 |  | Ready | decrement sem | Running |
| -1 |  | Ready | (sem&lt;0)→sleep | Sleeping |
| -1 |  | Running | Switch→T0 | Sleeping |
| -1 | (crit sect: end) | Running |  | Sleeping |
| -1 | call sem_post() | Running |  | Sleeping |
| 0 | increment sem | Running |  | Sleeping |
| 0 | wake(T1) | Running |  | Ready |
| 0 | sem_post() returns | Running |  | Ready |
| 0 | Interrupt; Switch→T1 | Ready |  | Running |
| 0 |  | Ready | sem_wait() returns | Running |
| 0 |  | Ready | (crit sect) | Running |
| 0 |  | Ready | call sem_post() | Running |
| 1 |  | Ready | sem_post() returns | Running |

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">Code</div>
<div class="code-frame-body" markdown="block">

```c
sem_t m;
sem_init (&m, 0, X); // initilize semaphore to X. What should X be?

sem_wait(&m);
    // critical section here
sem_post(&m);
```

</div>
</div>
</div>


{% enddetails %}


{% details Semaphore as condition variable %}

<div class="code-pair" style="--code-frame-height: 16rem">
<div class="code-frame">
<div class="code-frame-title">Thread trace: parent waiting for child (case 1)</div>
<div class="code-frame-body" markdown="block">

| Value | Parent | State | Child | State |
| --- | --- | --- | --- | --- |
| 0 | create(Child) | Running | (Child exists; is runnable) | Ready |
| 0 | call sem_wait() | Running |  | Ready |
| -1 | decrement sem | Running |  | Ready |
| -1 | (sem&lt;0)→sleep | Sleeping |  | Ready |
| -1 | Switch→Child | Sleeping | child runs | Running |
| -1 |  | Sleeping | call sem_post() | Running |
| 0 |  | Sleeping | increment sem | Running |
| 0 |  | Ready | wake(Parent) | Running |
| 0 |  | Ready | sem_post() returns | Running |
| 0 |  | Ready | Interrupt; Switch→Parent | Ready |
| 0 | sem_wait() returns | Running |  | Ready |

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">Code</div>
<div class="code-frame-body" markdown="block">

```c
sem_t s;

void *child(void *arg) {
    printf("child\n");
    sem_post(&s); //signal here: child is done
    return NULL;
}

int main(int argc, char *argv[]) {
    sem_init(&s, 0, X); // initialize semaphore to X. What should X be?
    printf("parent: begin \n");
    pthread_t c;
    Pthread_create(&c, NULL, child, NULL);
    sem_wait(&s); // wait here for hchild
    printf("parent: end\n");
    return 0;
}
```

</div>
</div>
</div>

<div class="code-pair" style="--code-frame-height: 16rem">
<div class="code-frame">
<div class="code-frame-title">Thread trace: parent waiting for child (case 2)</div>
<div class="code-frame-body" markdown="block">

| Value | Parent | State | Child | State |
| --- | --- | --- | --- | --- |
| 0 | create(Child) | Running | (Child exists; is runnable) | Ready |
| 0 | Interrupt; Switch→Child | Ready | child runs | Running |
| 0 |  | Ready | call sem_post() | Running |
| 1 |  | Ready | increment sem | Running |
| 1 |  | Ready | wake(nobody) | Running |
| 1 |  | Ready | sem_post() returns | Running |
| 1 | parent runs | Running | Interrupt; Switch→Parent | Ready |
| 1 | call sem_wait() | Running |  | Ready |
| 0 | decrement sem | Running |  | Ready |
| 0 | (sem&ge;0)→awake | Running |  | Ready |
| 0 | sem_wait() returns | Running |  | Ready |

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">Code</div>
<div class="code-frame-body" markdown="block">

```c
sem_t s;

void *child(void *arg) {
    printf("child\n");
    sem_post(&s); //signal here: child is done
    return NULL;
}

int main(int argc, char *argv[]) {
    sem_init(&s, 0, X); // initialize semaphore to X. What should X be?
    printf("parent: begin \n");
    pthread_t c;
    Pthread_create(&c, NULL, child, NULL);
    sem_wait(&s); // wait here for hchild
    printf("parent: end\n");
    return 0;
}
```

</div>
</div>
</div>


{% enddetails %}


{% enddetails %}

## Producer/Consumer

{% details warning Semaphore: producer/consumer I %}

- What is the risk if MAX > 1 and there are multiple producers/consumers?
    - Race condition: two producers produce at the same time or two consumers
  consume at the same time. 

{% details question What is currently missing from this implemntation? %}
Mutual exclusion
{% enddetails %}

<div class="code-pair" style="--code-frame-height: 32rem">
<div class="code-frame">
<div class="code-frame-title">Buffer</div>
<div class="code-frame-body" markdown="block">

```c
int buffer[MAX];
int fill = 0;
int use = 0;

void put(int value) {
    buffer[fill] = value;       // Line F1
    fill = (fill + 1) % MAX;    // Line F2
}

int get() {
    int tmp = buffer[use];       // Line G1
    use = (use + 1) % MAX;       // Line G2
    return tmp;
}
```

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">Producer and consumer</div>
<div class="code-frame-body" markdown="block">

```c
sem_t empty;
sem_t full;

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&empty);        // Line P1
        put(i);                  // Line P2
        sem_post(&full);         // Line P3
    }
}

void *consumer(void *arg) {
    int i, tmp = 0;
    while (tmp != -1) {
        sem_wait(&full);         // Line C1
        tmp = get();             // Line C2
        sem_post(&empty);        // Line C3
        printf("%d\n", tmp);
    }
}

int main(int argc, char *argv[]) {
    // ...
    sem_init(&empty, 0, MAX); // MAX buffers are empty to begin with...
    sem_init(&full, 0, 0);    // ... and 0 are full
    // ...
}
```

</div>
</div>
</div>

{% enddetails %}


{% details warning Semaphore: producer/consumer II %}

- Mutual exclusion is added, incorrectly. 
    - Consumer runs first, then wait on `full` (but still holding `mutex`). 
    - Producer sees negative mutex, decreases it further, then goes to sleep. 

<div class="code-pair" style="--code-frame-height: 35rem">
<div class="code-frame">
<div class="code-frame-title">Buffer</div>
<div class="code-frame-body" markdown="block">

```c
int buffer[MAX];
int fill = 0;
int use = 0;

void put(int value) {
    buffer[fill] = value;       // Line F1
    fill = (fill + 1) % MAX;    // Line F2
}

int get() {
    int tmp = buffer[use];       // Line G1
    use = (use + 1) % MAX;       // Line G2
    return tmp;
}
```

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">Producer and consumer</div>
<div class="code-frame-body" markdown="block">

```c
sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&mutex);        // Line P0 (NEW LINE)
        sem_wait(&empty);        // Line P1
        put(i);                  // Line P2
        sem_post(&full);         // Line P3
        sem_post(&mutex);        // Line P4 (NEW LINE)
    }
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&mutex);        // Line C0 (NEW LINE)
        sem_wait(&full);         // Line C1
        int tmp = get();         // Line C2
        sem_post(&empty);        // Line C3
        sem_post(&mutex);        // Line C4 (NEW LINE)
        printf("%d\n", tmp);
    }
}

int main(int argc, char *argv[]) {
    // ...
    sem_init(&empty, 0, MAX); // MAX buffers are empty to begin with...
    sem_init(&full, 0, 0);    // ... and 0 are full
    sem_init(&mutex, 0, 1);   // mutex=1 because it is a lock (NEW LINE)
    // ...
}
```

</div>
</div>
</div>

{% enddetails %}

{% details success Semaphore: producer/consumer III %}

- Mutual exclusion is added, correctly. 
    - `full` and `empty` are for producers and consumers to wait on one another. 
    - `mutex` for producers and consumers to wait among each group. 

<div class="code-pair" style="--code-frame-height: 35rem">
<div class="code-frame">
<div class="code-frame-title">Buffer</div>
<div class="code-frame-body" markdown="block">

```c
int buffer[MAX];
int fill = 0;
int use = 0;

void put(int value) {
    buffer[fill] = value;       // Line F1
    fill = (fill + 1) % MAX;    // Line F2
}

int get() {
    int tmp = buffer[use];       // Line G1
    use = (use + 1) % MAX;       // Line G2
    return tmp;
}
```

</div>
</div>
<div class="code-frame">
<div class="code-frame-title">Producer and consumer</div>
<div class="code-frame-body" markdown="block">

```c
sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&empty);        // Line P1
        sem_wait(&mutex);        // Line P1.5 (MOVED MUTEX HERE...)
        put(i);                  // Line P2
        sem_post(&mutex);        // Line P2.5 (... AND HERE)
        sem_post(&full);         // Line P3
    }
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&full);         // Line C1
        sem_wait(&mutex);        // Line C1.5 (MOVED MUTEX HERE...)
        int tmp = get();         // Line C2
        sem_post(&mutex);        // Line C2.5 (... AND HERE)
        sem_post(&empty);        // Line C3
        printf("%d\n", tmp);
    }
}

int main(int argc, char *argv[]) {
    // ...
    sem_init(&empty, 0, MAX); // MAX buffers are empty to begin with...
    sem_init(&full, 0, 0);    // ... and 0 are full
    sem_init(&mutex, 0, 1);   // mutex=1 because it is a lock
    // ...
}
```

</div>
</div>
</div>


{% enddetails %}

## The Dining Philosophers

{% details Problem Definition %}

- There are five philosophers seating around a table. 
- Between each pair of philosophers there is a single fork (five forks total).
- Philosophers alternate between thinking and eating (need fork). 
- Two forks are needed to eat (one to the left and one to the right). 
- How to schedule fork grabbing pattern so that no one starves?


{% include figure.liquid path="assets/img/courses/csc331/semaphores/08.png" max-width="50%" zoomable=true %}

{% enddetails %}

{% details success Solutions %}

- Which one works?

```c
int left(int p) { return p; }
int right(int p) { return (p + 1) % 5; }
```

<div class="code-pair" style="--code-frame-height: 16rem">
<div class="code-frame">

<div class="code-frame-title">Version 1</div>
<div class="code-frame-body" markdown="block">

```c
void getforks() {
    sem_wait(forks[right(p)]);
    sem_wait(forks[right(p)]);
}

void putforks() {
    sem_post(forks[left(p)]);
    sem_post(forks[right(p)]);
}
```
</div>
</div>

<div class="code-frame">
<div class="code-frame-title">Version 2</div>
<div class="code-frame-body" markdown="block">

```c
void getforks() {
    sem_wait(forks[left(p)]);
    sem_wait(forks[right(p)]);
}

void putforks() {
    sem_post(forks[left(p)]);
    sem_post(forks[right(p)]);
}
```

</div>
</div>

</div>

{% enddetails %}