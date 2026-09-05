---
layout: lecture
pretty_table: true
collection: csc302

title: "Introduction to Operating Systems"
---
# Introduction to Operating Systems


{% details 1. What happens when a computer program run? %}



{% enddetails %}
 The process
   - **fetches** an instruction from memory,
   - **decodes** the instruction, and
   - **executes** the instruction.
 This is the fundamental **Von Neumann** model of computing. 



{% details 2. Why do we need OS? %}



{% enddetails %}
{% include figure.liquid path="assets/img/courses/csc302/os-review/01.png" max-width="50%" zoomable=true alt="Codes to hardware to screen" %}

- When the shell loaded and ran the HelloWorld program, 
and when the HelloWorld program prints its message, neither 
program accessed the keyboard, display, disk, or main memory directly. 
- Rather, they relied on the services provided by the operating system.
- We can think of the operating system as a layer of software 
interposed between the application program and the hardware. 


{% details 3. The operating system %}



{% enddetails %}
- An operating system is software that manages all the hardware resources 
associated with your electronic devices. 
- It manages the communication between your software and hardware.
- Without the operating system (OS), the software wouldn’t function.
  - Examples: Windows 8 and Mac OS X, Linux


{% details 4. The operating system components %}



{% enddetails %}
- Daemons: These are background services (printing, sound, scheduling, etc) 
that either start up during boot, or after you log into the desktop.
- The Shell: is a user interface that allows you to control the computer. OS 
shells use either command-line interface (CLI) or graphical user interface (GUI). 
It is named a shell because it is a layer around the OS kernel. 
- Graphical Server: This is the sub-system that displays the graphics on 
your monitor. 
- Desktop Environment: This is the piece of the puzzle that the users actually 
interact with. Each desktop environment includes built-in applications (such as 
file managers, configuration tools, web browsers, games, etc)


{% details 5. Purposes of operating system %}



{% enddetails %}
- The operating system has two primary purposes: 
  - To protect the hardware from misuse by runaway applications and
  - To provide applications with simple and uniform mechanisms for 
  manipulating complicated and often widely different low-level hardware devices. 
- The operating system achieves both goals via the fundamental abstractions
  - Processes
  - Virtual memory
  - Files


{% details 6. Operating system processes %}



{% enddetails %}
- A process is the operating system’s abstraction for a running program.
- Multiple processes can run concurrently on the same system, and each process 
appears to have exclusive use of the hardware.
  - Many running program share the physical memory space. 
  - Each runnning program is presented with the illusion that they have access 
  to their own private memory. This is called **virtual address space**, which 
  is mapped to physical memory space by the OS.  
  - Making memory references within one running program (within one's own virtual 
  address space) does not affect the private virtual address space of others. 
- By concurrently, we mean that the instructions of one process are interleaved 
with the instructions of another process. 


{% details 7. Kernel %}



{% enddetails %}
- The transition from one process to another is managed by the 
operating system Kernel. 
- The kernel is the portion of the operating system code that is 
always resident in memory. 
- When an application program requires some action by the operating 
system, such as to read or write a file, it requires some action by 
the operating system, such as to read or write a file, it executes a 
special **system call** instruction, transferring control to the kernel.
- The kernel then performs the requested operation and returns back to 
the application program.
- Note that the kernel is not a separate process. Instead, it is a 
collection of code and data structures that the system uses to manage 
all the processes. 


{% details 8. Pre-emptive Multitasking %}



{% enddetails %}
- CPU receives interrupt
- Interrupt stores in program counter
- Interrupt invokes handler
- Handler saves rest of process state
- Handler does its business
- Handler invokes the scheduler
- Scheduler selects a process to run
- Scheduler restores state for that process
- Scheduler jumps execution to that process



{% details 9. Managing scheduling: Multi-Level Feedback Queue %}



{% enddetails %}
- Rule 1: If Priority(A) > Priority(B), A runs (B doesn’t)
- Rule 2: If Priority(A) = Priority(B), RR(A, B)
- Rule 3: When a job enter the system, it is placed at the highest priority 
(the top most queue).
- Rule 4: Once a job uses up its time allotment at a given level 
(regardless of how many time it has given up the CPU), its priority 
is reduced. 
- Rule 5: After some time period S, move all the jobs in the system to 
the topmost queue.
- MLFQ observes the execution of a  job and gradually learns what type of job 
it is, and prioritize it accordingly. 
  - Excellent performance for interactive I/O bound jobs: good response time.
  - Fair for long-running CPU-bound jobs: good turnaround time without starvation.
  - Used by many systems, including FreeBSD, MacOS X, Solaris, Linux 2.6, and Windows NT
  - Invented by Fernando Jose Corbato (1926 - )
    - Ph.D. in Physics (CalTech)
    - MIT Professor
    - One of the original developers of Multics (Predecessor of UNIX)
    - First use of password to secure file access on computers. 
    - Recipient of the 1990 Turing Award (The Nobel prize in computing)



{% details 10. Process States %}



{% enddetails %}
- A process can be in one of the three states. 
  - Running: the CPU is executing a process' instructions.
  - Ready: the process is ready to run, but the OS is not running 
  the process at the moment.
  - Blocked: the process has to perform some operation (e.g., I/O request
  to disk) that makes it not ready to run. 

{% include figure.liquid path="assets/img/courses/csc302/os-review/03.png" max-width="50%" zoomable=true alt="Process state transition" %}

- When a process moves from **ready** to **running**, this means
that it has been **scheduled** by the OS. 
- When a process is moved from **running** to **ready**, this means
that it has been descheduled by the OS. 
- When an I/O request (within the process) is initiated, the **running** 
process become **blocked** by the OS until the I/O request is completed. 
Upon receiving the I/O completion signal, the OS moves the process' state
from **blocked** to **ready**, to wait to be scheduled by the OS. 


{% details 11. Virtual Memory %}



{% enddetails %}
- Provide users (programmers) with an **easy-to-use** abstarction of physical memory. 
- The running program's **view of memory in the system**. 
- Contains all memory states of the running program:
  - `Stack` to keep track of where it is in the function call chain 
  (stack frames), allocate local variables, and pass parameters and 
   return values to and from routines. 
   - `Heap` is used for dynamically allocated, user-managed memory 
   (i.g., malloc()). 
   - `BSS` (block started by symbols) contains all global variables and static 
   variables that are initialized to zero or do not have explicit initialization 
   in source code.
   - `Data` contains the global variables and static variables that are initialized 
   by the programmer.
   - `Code` (binary) of the program.
- Each process can only access its own memory, while OS can access all the memory 
of processes. 
- This is enforced by the CPU running in two different privilege levels
  - When OS code runs, the CPU is put into a privilege level that allows access 
  to the I/O devices and any address of memory. 
  - When a process runs, the CPU is put into a level that triggers a hardware 
  exception when the code attempts to directly access the I/O devices or addresses 
  that are not allowed for that process. 


:::::{tab-set}
::::{tab-item} low-to-high view

{% include figure.liquid path="assets/img/courses/csc302/os-review/04.png" max-width="50%" zoomable=true alt="Address space 1" %}

::::
::::{tab-item} high-to-low view

{% include figure.liquid path="assets/img/courses/csc302/os-review/05.png" max-width="50%" zoomable=true alt="Address space 2" %}

::::
:::::


{% details 12. System calls - how does process invoke actions? %}



{% enddetails %}
- System calls are the means that processes initiate request 
to the OS. 
- These system call provides functions for things like 
reading/writing files or sending/receiving data over the network
- To invoke system calls, a process must use specific CPU 
instructions, a system call number. The processor look in the 
system call table for the address for the system call corresponding 
to the number and jump execution to that address. 
- User space definition:
  - [libc's definition for write()](https://sourceware.org/git/?p=glibc.git;a=blob_plain;f=io/write.c;hb=HEAD)
- Kernel definition:
  - [Linux definition for write()](https://github.com/torvalds/linux/blob/74673fc50babc9be22b32c4ce697fceb51c7671a/include/linux/syscalls.h)
- The user space definition will eventually call the kernel definition.


{% details 13. Files and directories %}



{% enddetails %}
- File: a linear array of bytes, each of which you can read and write.
- A file has some high-level, user-readable name, e.g., `interceptor.c`.
  - One file may have multiple user-readable names, as we will see.
- Each file has a low-level name called the `inode` number.
  - This is the real identifier of a file.
- File system does NOT care about what type of file it is (C code, picture 
or video, it just makes sure to store all bytes in a file **persistently**.

{% include figure.liquid path="assets/img/courses/csc302/os-review/06.png" max-width="50%" zoomable=true alt="Files and inodes" %}


{% details 14. Threads %}



{% enddetails %}
- A normal process is a running program with a single point of execution, 
i.e, a single PC (program counter).
- A **multi-threaded** program has **multiple points of execution**, i.e., 
multiple PCs.
- Each thread is very much like a separate process, except for one difference:
  - All threads of the same process share the same address space and thus can 
  access the same data. 

{% include figure.liquid path="assets/img/courses/csc302/os-review/07.png" max-width="50%" zoomable=true alt="Pages" %}

- Each thread has its own PC.
- Each thread has its own private set of registers for computation.
- Context switching is still needed. 
- Threads use Thread Control Blocks (TCP) to store their execution states.
- Context switching is similar to that of processes, except for:
- Thread context-switching keep the same address space (i.e., no need to switch 
out the page table).

```
