---
layout: lecture
pretty_table: true
collection: csc331

title: "Introduction to concurrency using threads"
toc:
  - name: Review: process calls fork()
  - name: Review: process context switch
  - name: Example: web server
  - name: Thread: a new abstraction for running processes
  - name: Thread: state of a single thread
  - name: Example: web server using thread
  - name: API: POSIX threads (pthreads)
  - name: Hands on: say hello to my little threads ...
  - name: The problem with threads
  - name: Challenge
---

# Introduction to concurrency using threads

---

## Review: process calls fork()

- New PCB (process control block) and address space.
- New address space is a copy of the entire contents of the parent's 
address space (up to fork).
- Resources (file pointers) that point to parent’s resources.
- **In general, time consuming.**

---

## Review: process context switch

- Save A's registers to A's kernel stack.
- Save A's registers to A's PCB.
- Restore B's registers from B's PCB.
- Switch to B's kernel stack.
- Restore B's registers from B's kernel stack.
- **In general, time consuming.**

---

## Example: web server

- A process listens to requests.
- When a new request comes in, a child process is created to 
handle this request.
- Multiple requests can be handled at the same time by 
different child processes.
- What is the problem?

```c
while (1) {
	  int sock = accept();
  if (0 == fork()) {
    handle_request();
    close(sock);
    exit(0);
  }
}
```

---

## Thread: a new abstraction for running processes

- A normal process is a running program with a single point of execution, 
i.e, a single PC (program counter).
- A **multi-threaded** program has **multiple points of execution**, i.e., multiple PCs.
- Each thread is very much like a separate process, except for one difference:
    - All threads of the same process share the same address space and thus can 
    access the same data. 

{% include figure.liquid path="assets/img/courses/csc331/10-concurrency/01.png" width="50%" zoomable=true %}

---

## Thread: state of a single thread

- Each thread has its own PC.
- Each thread has its own private set of registers for computation.
- Context switching is still needed. 
- Threads use Thread Control Blocks (TCP) to store their execution states.
- Context switching is similar to that of processes, except for:
    - Thread context-switching keep the same address space (i.e., no need to switch out the page table).

---

## Example: web server using thread

```c
int global_counter = 0;
web_server() {
  while (1) {
    int sock = accept();
    thread_create(handle_request, sock);
  }
}

handle_request(int sock) {
  process request;
  ++global_counter;
  close(sock);
}
```

---

## API: POSIX threads (pthreads)

- Standardized C language thread programming API.
- `pthreads` specifies the interface of using threads, but not how threads 
are implemented in OS.
- Different implementations include: 
    - kernel-level threads,
    - user-level threads, or 
    - hybrid
- [pthread_create](http://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [pthread_join](http://man7.org/linux/man-pages/man3/pthread_join.3.html)

---

## Hands on: say hello to my little threads ...

- Create a directory named `concurrency` change to this directory

```bash
mkdir ~/concurrency
cd ~/concurrency
```
- Create `thread_hello.c` with the following contents:

<script src="https://gist.github.com/linhbngo/d2f3a0b28b73a3f48c751410c6c91fd6.js?file=thread_hello.c"> </script>

- Compile and run `thread_hello.c`:

```c
gcc -o thread_hello thread_hello.c -lpthread
./thread_hello 1
./thread_hello 2 
./thread_hello 4
```

{% include figure.liquid path="assets/img/courses/csc331/10-concurrency/02.png" width="50%" zoomable=true %}

---

## The problem with threads

{% details Edward Lee (2006). The Problem with Threads. Computer 39(5). %}

From a fundamental perspective, threads are seriously flawed 
as a computation model because they are wildly nondeterministic... 
The programmer’s job is to prune away that nondeterminism. We have 
developed tools to assist in the pruning: semaphores, monitors, and 
more modern overlays on threads offer the programmer ever more effective 
pruning. But pruning a wild mass of brambles rarely yields a satisfactory 
hedge. To offer another analogy, a folk definition of insanity is to do 
the same thing over and over again and expect the results to be different. 
By this definition, we in fact require that programmers of multithreaded 
systems be insane. Were they sane, they could not understand their programs.

{% enddetails %}
---

## Challenge

- Inside `concurrency`, change to this directory, and create `thread_matrix.c` with 
the following contents:

<script src="https://gist.github.com/linhbngo/d2f3a0b28b73a3f48c751410c6c91fd6.js?file=thread_matrix.c"></script>

- Find out how to enhance this implementation in the followings way:
    - Identify thread numbers and which sections of which matrices (A, B, and C) each thread is 
    working on. 
    - How do you avoid random threads picking up specific work assignments over times?


