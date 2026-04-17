---
layout: lecture
pretty_table: true
collection: csc466

title: "Threads programming"
toc:
  - name: Thread overview
  - name: Thread parallelization
---
# Threads programming

## Thread overview

{% details Target hardware %}


- Single computing node, multiple sockets, multiple cores.

    - Dell PowerEdge M600 Blade Server. 

    {% include figure.liquid path="assets/img/courses/csc466/04-threads/01.jpg" width="50%" zoomable=true alt="Multi-socket motherboards" %}

    - Intel Sandy Bridge CPU. 

    {% include figure.liquid path="assets/img/courses/csc466/04-threads/02.jpg" width="50%" zoomable=true alt="Intel Sandy Bridge CPU" %}

- In summary
    - Node with multiple sockets.
    - Each socker support CPUs with multiple cores. 
    - Each core is an independent CPU. 
    - Each core has access to all the memory on the node. 

{% enddetails %}
{% details Thread: An abstraction for running multiple processes %}


- A normal process is a running program with a single point of execution, i.e, a 
single PC (program counter).
- A multi-threaded program has multiple points of execution, i.e., multiple PCs.
- Each thread is very much like a separate process, except for one difference:
    - All threads of the same process share the same address space and thus can access the same data.

{% include figure.liquid path="assets/img/courses/csc466/04-threads/threads.png" width="50%" zoomable=true alt="Threads memory model" %}

{% enddetails %}
{% details POXIS threads (pthreads) %}


- Standardized C language thread programming API.
- `pthreads` specifies the interface of using threads, but not how threads are implemented in OS.
- Different implementations include:
    - kernel-level threads,
    - user-level threads, or
    - hybrid
- [pthread_create](http://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [pthread_join](http://man7.org/linux/man-pages/man3/pthread_join.3.html)

{% enddetails %}
{% details Say hello to my little threads ... %}


- Launch your `csc466env` environment and go to `127.0.0.1:18088`

    - You only need to launch the head node for this topic for thread programming.

    ```bash
    docker compose up -d head
    ```

- Click on the top-left three dashes, select `File` then `Open Folder`

{% details info File/Open Folder %}

{% include figure.liquid path="assets/img/courses/csc466/04-threads/code-server-01.png" width="50%" zoomable=true %}

{% enddetails %}
- Make sure that you have `/home/student` in the box then press `OK`

{% details info /home/student %}

{% include figure.liquid path="assets/img/courses/csc466/04-threads/code-server-02.png" width="50%" zoomable=true %}

{% enddetails %}
- Use the terminal or the icons (see the red box) to create a new folder and 
new files (in the future)

{% details info Create new folder/file %}

{% include figure.liquid path="assets/img/courses/csc466/04-threads/code-server-03.png" width="50%" zoomable=true %}

{% enddetails %}
- Create `thread_hello.c` with the following contents:


```c linenums="1"
--8<-- "docs/csc466/lectures/data/thread/hello_thread.c"
```

- Compile and run `thread_hello.c`:

```bash
gcc -o thread_hello thread_hello.c -lpthread
./thread_hello 1
./thread_hello 2 
./thread_hello 4
``` 

{% enddetails %}
## Thread parallelization

{% details Sum of values in an array %}


- Create `thread_sum.c` with the following contents:

```c linenums="1"
--8<-- "docs/csc466/lectures/data/thread/thread_sum.c"
```

- Compile and run `thread_sum.c`:

```bash
gcc -o thread_sum thread_sum.c -lpthread
./thread_sum 16 4
./thread_sum 256 4
./thread_sum 1000000 4
``` 


{% enddetails %}
{% details Global variable: does it work? %}


- Create `thread_global_nolock.c` with the following contents:

```c linenums="1"
--8<-- "docs/csc466/lectures/data/thread/thread_global_nolock.c"
```

- Compile and run `thread_global_nolock.c`:
  - Compare the outcome with `thread_sum`

```bash
gcc -o thread_global_nolock thread_global_nolock.c -lpthread
./thread_global_nolock 16 4
./thread_global_nolock 2000 4
./thread_global_nolock 90000 4
./thread_sum 90000 4
``` 

{% enddetails %}
{% details What is the problem? %}


- Two concurrent threads manipulated a shared resource (the `sum` variable) 
without any synchronization.
  - Outcome depends on the order in which accesses take place -- this is called a 
  **race condition**.
- We need to ensure that only one thread at a time can manipulate the shared resource so 
that we can reason about program behavior, in a sane way 
  - We need **synchronization**.
- What is shared/not shared in a multithreaded program?

{% include figure.liquid path="assets/img/courses/csc466/04-threads/shared-not-shared.png" width="50%" zoomable=true alt="Multi-socket motherboards" %}

{% enddetails %}
{% details Key definitions %}


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
{% details Requirements for critical section handling %}


- `Mutual Exclusion`: if one thread is in the CS, then no other is
- `Progress`: threads waiting for access to CS are not prevented from entering by 
threads not in the CS; threads do not wait indefinitely.
- `Bounded Waiting` (no starvation): all waiting threads are guaranteed to eventually 
get access to the CS.
- `Performance`: The overhead of entering and exiting the CS is small compared to the work 
done within it.

{% enddetails %}
{% details Lock: Definition %}


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
    ...

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
{% details Global variable: correction at a cost %}


- Create `thread_global_lock.c` with the following contents:

```c linenums="1"
--8<-- "docs/csc466/lectures/data/thread/thread_global_lock.c"
```

- Compile and run `thread_global_lock.c`:
  - Compare the outcome with `thread_sum`
  - Compare the runtime with `thread_sum` and `thread_global_nolock` with a lower input value

```bash
gcc -o thread_global_lock thread_global_lock.c -lpthread
./thread_global_lock 90000 4
./thread_global_nolock 90000 4
./thread_sum 90000 4
./thread_global_lock 2000 4
./thread_global_nolock 2000 4
./thread_sum 2000 4
``` 



{% enddetails %}
