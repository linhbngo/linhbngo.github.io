---
layout: lecture
pretty_table: true
collection: csc331
course: CSC 331: Operating Systems
title: "Semaphores"
toc:
  - name: What have we learned so far?
  - name: Edsger Dijkstra
  - name: Semaphore
  - name: Semaphore as lock (binary semaphore)
  - name: Semaphore as condition variable
  - name: Semaphore: producer/consumer I
  - name: Semaphore: producer/consumer II
  - name: Semaphore: producer/consumer III
  - name: The dining philosophers
  - name: Solutions
---

# Semaphores

---

## What have we learned so far?

- Both lock and condition variables are needed to solve more complex 
concurrency problems. 
- Can we do better?

---

## Edsger Dijkstra

- Dijkstra, Edsger W. *"The structure of the "THE" multiprogramming system."* 
In The origin of concurrent programming, pp. 139-152. Springer, New York, NY, 1968.
- Dijkstra, Edsger W. *"Information streams sharing a finite buffer."* In Inf. Proc. 
Letters, vol. 1, pp. 179-180. 1972.
- Together with colleagues, developed semaphore as a single primitive for all things 
related to synchronization. 

---

## Semaphore

- Is an object with an integer value that can be manipulated with two routines:
    - [sem_wait()](https://man7.org/linux/man-pages/man3/sem_wait.3.html)
    - [sem_post()](https://www.man7.org/linux/man-pages/man3/sem_post.3.html)    
    - They are **atomic operations**
- Needs to be initialized to some value. 
    - [sem_init()](http://man7.org/linux/man-pages/man3/sem_init.3.html)

{% details note Details %}

More importantly, how do we use `sem_wait()` and `sem_post()` to facilitate 
synchronization for concurrency?

{% enddetails %}
{% details sem_wait() %}


```c
int sem_wait(sem_t *s) {
    // try to decrement the value of semaphore s by one
    // if s is greater than zero, derement proceeds and return
    // else blocks (sleep) until it can decrement (s > 0) or interrupted via signal
}
```
- `sem_wait()` either return right away or it will cause the caller to wait.

{% enddetails %}
{% details sem_post() %}


```c
int sem_post(sem_t *sem){
    // increments (unlocks) the semaphore pointed to by sem.
    // If the semaphore's value consequently becomes greater than zero,
    // then another process or thread blocked in a sem_wait call will
    // be woken up and proceed to lock the semaphore.
    // else, the value of the semaphore is left unchanged. 
}
```

{% enddetails %}
---

## Semaphore as lock (binary semaphore)

```c
sem_t m;
sem_init (&m, 0, X); // initilize semaphore to X. What should X be?

sem_wait(&m);
    // critical section here
sem_post(&m);

{% details Code tracing %}

{% include figure.liquid path="assets/img/courses/csc331/semaphores/03.png" width="50%" zoomable=true %}

{% enddetails %}
---

## Semaphore as condition variable

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

{% details Code tracking %}

{% include figure.liquid path="assets/img/courses/csc331/semaphores/04.png" width="50%" zoomable=true %}

{% enddetails %}
---

## Semaphore: producer/consumer I

- What is the risk if MAX > 1 and there are multiple producers/consumers?
    - Race condition: two producers produce at the same time or two consumers
  consume at the same time. 
- What is currently missing from this implementation?
    - Mutual exclusion

{% include figure.liquid path="assets/img/courses/csc331/semaphores/05.png" width="50%" zoomable=true %}

---

## Semaphore: producer/consumer II

- Mutual exclusion is added, incorrectly. 
    - Consumer runs first, then wait on `full` (but still holding `mutex`). 
    - Producer sees negative mutex, decreases it further, then goes to sleep. 

{% include figure.liquid path="assets/img/courses/csc331/semaphores/06.png" width="50%" zoomable=true %}

---

## Semaphore: producer/consumer III

- Mutual exclusion is added, correctly. 
    - `full` and `empty` are for producers and consumers to wait on one another. 
    - `mutex` for producers and consumers to wait among each group. 

{% include figure.liquid path="assets/img/courses/csc331/semaphores/07.png" width="50%" zoomable=true %}

---

## The dining philosophers

- It’s Dijkstra again. 
    - There are five philosophers seating around a table. 
    - Between each pair of philosophers there is a single fork (five forks total).
    - Philosophers alternate between thinking and eating (need fork). 
    - Two forks are needed to eat (one to the left and one to the right). 
    - How to schedule fork grabbing pattern so that no one starves?

{% include figure.liquid path="assets/img/courses/csc331/semaphores/08.png" width="50%" zoomable=true %}

---

## Solutions

- Which one works?

{% include figure.liquid path="assets/img/courses/csc331/semaphores/09.png" width="50%" zoomable=true %}

