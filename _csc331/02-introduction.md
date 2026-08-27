---
layout: lecture
pretty_table: true
collection: csc331

title: "Introduction to Operating Systems"
toc:
  - name: Overview
  - name: Virtualization
  - name: Concurrency
  - name: Persistency
  - name: A Brief History
---

## Overview

{% details What happens when a computer program run? %}

- The fundamental **Von Neumann** model of computing.
- The process
    - **fetches** an instruction from memory,
    - **decodes** the instruction, and
    - **executes** the instruction.

{% enddetails %}

{% details Why do we need OS? %}

{% include figure.liquid path="assets/img/courses/csc331/intro/01.png" max-width="50%" zoomable=true %}

- What a programmer see is all code, lines of codes.
- Underneath, there is a complex ecosystem of hardware components. 
- How do we hide this complexity away from the programmers?

{% enddetails %}

{% details How do the OS help? %}

- Each physical component in a computing system is considered a resource. 
- The OS **manages** these resources so that:
  - Different programs can access these resources through the corresponding virtual interfaces: `virtualization`
  - Different programs can access these resources at the same time: `concurrency`
  - Modifying accesses (write) can be made permanent: `persistence`.   

{% enddetails %}

{% include quiz.liquid
   id="os-intro-1"
   question="Which of the following best describes the primary role of an Operating System?"
   choices="Execute user applications directly on hardware|Manage hardware resources and provide services to programs|Store files permanently on disk|Connect computers to the internet"
   answer="1"
   hint="Think about what sits between your hardware and your applications."
   explanation="The OS acts as an intermediary between hardware and software. It manages the CPU, memory, storage, and I/O devices, and exposes them to programs through a set of abstractions (processes, files, sockets, etc.) so applications don't have to talk to hardware directly."
%}

## Virtualization

- **Virtualization**: presents general, powerful, and easy-to-use **virtual** forms of  **physical** computing resources to users (*programmers*). 
- The linkage between virtual interfaces and physical components are enabled through the OS' **system calls** (or **standard library**).  

{% details info Preparation %}

- The source code examples from the OSTEP book is located inside the container at `/home/student/ostep-code`
- For this lecture, we will build the source codes inside the `intro` subdirectory. 
- Launch the `csc331` container if necessary, then open a bash terminal into the container. 
  - In [docker-compose.yml](hhttps://github.com/WCU-AIR/the-one-ring/blob/csc331/docker-compose.yml), the following setting is made `cpusets: "0-1"`. This means the container is limited to run on the physical cores 0 and 1 of the CPU, which is to emulate a simple dual-core configuration. 

```bash
cpuset: "0-1"
```
- View the file list
- Compile all the files using `make`

```bash
docker compose up -d
docker compose exec -u student -it csc331 /bin/bash
cd ~/ostep-code/intro
ls
make
```

{% include figure.liquid path="assets/img/courses/csc331/intro/intro-src.png" max-width="50%" zoomable=true %}


{% enddetails %}

{% details CPU Virtualization %}

The example program, `cpu.c`, will run an infinite loop that prints out the first command line argument:

```c
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
	fprintf(stderr, "usage: cpu <string>\n");
	exit(1);
    }
    char *str = argv[1];
    while (1) {
	printf("%s\n", str);
	Spin(1);
    }
    return 0;
}
```

- Open two terminals, and connect to the running container from these two terminals
- In the left terminal pane, run the following command. 

```bash
./cpu A & ./cpu B & ./cpu C &./cpu D 
```

- To stop the running processes on the left pane, move to the right pane and running the
following commands:

```bash
ps aux | grep cpu
```

- Identify the process ID (the second columns), then use the `kill` to kill all the process IDs 
(see figure below). 

{% include figure.liquid path="assets/img/courses/csc331/intro/intro-cpu.png" max-width="50%" zoomable=true %}

- The illusion of infinite CPUs
  - A limited number of physical CPUs can still be represented as infinite number of CPUs through 
**virtualization**.  
  - The OS will **manage** the scheduling and allocation of the actual run on physical resources. 

{% enddetails %}


{% details Memory Virtualization %}

- In the left terminal pane, run the following commands:
  - `-R` will disable randomization of virtual memory address space for shells. 

```bash
clear
sudo setarch `uname -m` -R /bin/bash
./mem 100 &./mem 200
```

- In the right pane, use the same procedure as above to kill the two running programs 
after a few iterations. 

{% include figure.liquid path="assets/img/courses/csc331/intro/06.png" max-width="50%" zoomable=true %}

Do programs running concurrently occupy the same memory locations (addresses)?

**No**

The illusion of dedicated memory resources

- Many running program share the physical memory space. 
- Each running program is presented with the illusion that they have access to their own private
memory. This is called **virtual address space**, which is mapped to physical memory space
by the OS.  
- Making memory references within one running program (within one's own virtual address space) 
does not affect the private virtual address space of others. 
- Without the `setarch` command, the location of variable `p` will be 
randomize within the virtual address space of a process. This is a security mechanism to 
prevent others from guessing and applying direct manipulation techniques to the physical 
memory location that actually contains `p`. 

{% enddetails %}


## Concurrency

- As shown in **CPU Virtualization** and **Memory Virtualization** examples, the OS 
wants to manage many running programs at the same time.
- This is called **concurrency**, and it leads to a number of interesting challenges 
in designing and implementing various management mechanisms within the OS.
- This can be observed through the following hands-on exercise. 
- Type exit to close one of the two terminal panes. 
- Run the following commands in the remaining terminal:

```bash
./threads 50
./threads 100
./threads 200
```

- `threads.c` creates two functions running at the same time, within the same memory 
space of the  main program.
- A single global variable named counter is being increased by both functions, thus 
the final value of counter should be twice that of the command line argument.
- Now run with bigger values.

```bash
./threads 20000
./threads 30000
./threads 30000
./threads 30000
```

{% include figure.liquid path="assets/img/courses/csc331/intro/07.png" max-width="50%" zoomable=true %}

{% details Problem with concurrency %}

{% details success the good %}
- Naive concurrency on very naive data **could** give you performance boost up to a certain limit
{% enddetails %}

{% details warning the bad %}
- Naive concurrency gives you wrong results.  
{% enddetails %}

{% details danger the ugly %}
- Naive concurrency gives you wrong **and** inconsistent results. 
{% enddetails %}

{% enddetails %}

{% details Why does this happen? %}

- At machine level, incrementing counter involves three steps:
  - Load value of counter from memory into register,
  - Increment this value in the register, and
  - Write the value of counter back to memory.
- What should have happened:
  - One thread increments counter (all three steps), then the other thread increments
  counter, now with the updated value.
- What really happened:
  - One thread increments counter.
  - While this thread has not done with all three steps, the other thread 
  steps in and attempts to increment the stale content of counter in memory.

{% enddetails %}


## Persistency 

- When the programs stop, everything in memory goes away: `counter`, `p`, `str`.
- Physical components to store information persistently are needed.
- Input/output or I/O devices:
    - Hard drives
    - Solid-state drives
- Software managing these storage devices is called the file system.
- Examples of system calls/standard libraries supporting the file system:
    - `open()`
    - `write()`
    - `close()`



## A Brief History

A good paper to read: [Hanser, Per Brinch. "The evolution of operating systems" 2001](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.104.1524&rep=rep1&type=pdf)


- Early operating systems: just libraries
    - Include only library for commonly used functions.
    - One program runs at a time.
    - Manual loading of programs by human operator.
- Beyond libraries: protection
    - System calls
    - Hardware privilege level
    - User mode/kernel mode
    - **trap**: the initiation of a system call to raise privilege from user mode to kernel mode. 
- The era of multiprogramming
    - Minicomputer
    - **multiprogramming**: multiple programs being run with the OS switching among them. 
    - Memory protection
    - Concurrency
- The modern era
    - Personal computer
    - DOS: the Disk Operating System
    - Mac OS
    - Multics (MIT) -> UNIX (Bell Labs) -> BSD (Berkeley) -> Sun OS/Linux
