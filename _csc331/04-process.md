---
layout: lecture
pretty_table: true
collection: csc331

title: "Abstraction: Process and Process API"
toc:
  - name: Program and process
  - name: Process API
  - name: Hands-on
  - name: The Shell
  - name: Other system calls ...
---

{% include quiz.liquid
   id="process-intro-1"
   question="In a C program, when you call a function, the CPU jumps to a new address and executes code there. If you want to run a completely different executable file from your program, can you just 'call' it like a function?"
   choices="Yes, you can call any binary file as if it were a function|No, because the other program is not part of the current running memory space|No, but only if the second program is written in a different language|Yes, provided you have a pointer to its main function"
   answer="1"
   hint="Think about how memory is organized when a single program is running."
   explanation="Unlike a function call (which jumps within the same allocated memory space), another executable file resides on disk and requires its own separate environment—memory, registers, and state—to run. This need for a 'container' for a running program is why the OS provides the Process abstraction."
%}

## Program and process

{% details What is a program? %}

- A program is a static list of instructions and data.
- When a program runs, the OS takes this list and asks the CPU to execute them. 
- If we only have one CPU, how can we run more than one program at a time. 

{% enddetails %}

{% details What is a process? %}

- A process is a **running program**.
  - But the program itself is not running ...
- A process is an **abstraction** provided by the OS to describe the running of a program.   
- What is a process made of?
  - Memory that the process (running program) can address.
  - Memory registers.
  - Program counter. 
  - Stack pointer.
  - Frame pointer.
  - I/O devices. 

{% enddetails %}

## Process API

{% details Minimal API capabilities %}

- Create: an OS must have some methods to create new processes to run programs. 
- Destroy: interface to destroy process forcefully.    
- Wait: temporarily pausing the process. 
- Miscellaneous Control: suspend and resume processes. 
- Status: provide status about the state of the process. 
  - Program counter. 
  - Stack pointer.
  - Frame pointer.
  - I/O devices. 

{% enddetails %}

{% details Process creation %}

When a program is run, the OS performs the following steps: 

- Load a program's code and static data into memory (the virtual address space
of the process).
- Allocate memory for run-time stack (for stack).     
- Allocate memory for heap (used for dynamic memory allocation via `malloc` family).
- Initialization: 
  - File descriptor for standard input.
  - File descriptor for standard output. 
  - File descriptor for error. 
  - *In Linux, everything is a file.*
- Begin executing from **main()**. 

{% enddetails %}

{% details From program to process %}

{% include figure.liquid path="assets/img/courses/csc331/process/01.png" width="50%" zoomable=true %}

- A process can be in one of the three states. 
    - Running: the CPU is executing a process' instructions.
    - Ready: the process is ready to run, but the OS is not running 
    the process at the moment.
    - Blocked: the process has to perform some operation (e.g., I/O request
    to disk) that makes it not ready to run. 

{% include figure.liquid path="assets/img/courses/csc331/process/02.png" width="50%" zoomable=true %}

- State transition
    - When a process moves from **ready** to **running**, this means
    that it has been **scheduled** by the OS. 
    - When a process is moved from **running** to **ready**, this means
    that it has been descheduled by the OS. 
    - When an I/O request (within the process) is initiated, the **running** 
    process become **blocked** by the OS until the I/O request is completed. 
    Upon receiving the I/O completion signal, the OS moves the process' state
    from **blocked** to **ready**, to wait to be scheduled by the OS. 

{% include figure.liquid path="assets/img/courses/csc331/process/03.png" width="50%" zoomable=true %}

{% enddetails %}


{% details Process data structure %}

- The OS is a program, and will data structures to track different pieces of information.
that it has been **scheduled** by the OS. 
- How does the OS track the status of processes?
  - **process list** for all processes.  
  - additional information for running process.  
  - status of blocked process, from **blocked** to **ready**, to wait to be scheduled by the OS. 
- Example: xv6
    - [kernel/proc.h](https://github.com/ngo-classes/xv6-riscv/blob/riscv/kernel/proc.h)

{% enddetails %}

{% details Key function calls %}

Include three function calls:

- fork()
- exec()  
- wait()  

{% enddetails %}


## Hands-on

{% details Hands-on: setup %}

- Open a shell into your csc331 container (ssh or Code browser)
- Run the following command to build the example code for process API

```bash
cd ~/ostep-code/cpu-api
make
```

{% include figure.liquid path="assets/img/courses/csc331/process/04.png" width="50%" zoomable=true %}

{% enddetails %}

{% details fork() %}

- ... is a system call. 
- ... is used to create a new process.   
- [Documentation for fork()](https://www.man7.org/linux/man-pages/man2/fork.2.html)    
- Some important points:
- fork() creates a new process by duplicating the calling process. 
The new process is referred to as the child process.  The calling process
is referred to as the parent process.
- The child process and the parent process run in separate memory
spaces.  **At the time of fork() both memory spaces have the same 
content**.  
- The child process is an exact duplicate of the parent process except
for the following points:
    - The child has its own unique process ID, and this PID does not 
    match the ID of any existing process group (setpgid(2)) or session.
    - The child's parent process ID is the same as the parent's process
    ID.
    - The child does not inherit outstanding asynchronous I/O operations
    from its parent (aio_read(3), aio_write(3)), nor does it inherit 
    any asynchronous I/O contexts from its parent (see io_setup(2)).
    - The child inherits copies of the parent's set of open file 
    descriptors.  Each file descriptor in the child refers to the same 
    open file description (see open(2)) as the corresponding file 
    descriptor in the parent.  This means that the two file 
    descriptors share open file status flags, file offset, and 
    signal-driven I/O attributes.

{% enddetails %}

{% details Hands-on: fork() %}


{% details View source code of p1.c on Code browser %}


- Line 5-6: No idea why the author sets up the source code that way ...
- Line 8: prints out hello world and the process identifier (pid) of the current process.
- Line 9: calls `fork()`, which initiate the creation of a new process. The return of this function call is assigned to variable `rc`. 
- Line 10: If `rc` is negative, the function call failed and the program exits with return value 1. 
This line is evaluated within the parent process (since the child process creation failed).
- Line 14: If `rc` is non-negative
- The `fork` call is successful, and you now have **two** process. 
    - The new process is an almost exact copy of the calling process.
    - The new process does not start at `main()`, but begins immediately after `fork()`.
- The value of `rc` differs in each process. 
    - The value of `rc` in the new process is `0`. 
    - The value of `rc` in the parent process is non-zero and actually is the `pid` of the new process. 
- Line 16 and line 19 confirms the above point by having the child process prints out its own 
process ID and the parent process prints out the `rc` value. These two values should be the same. 

{% enddetails %}
- Run `p1` several times. 

```bash
./p1
```

{% details What do you notice? %}


- What is one point of inconsistency in this screenshot?

{% include figure.liquid path="assets/img/courses/csc331/process/05.png" width="50%" zoomable=true %}

{% enddetails %}
{% enddetails %}
{% details Processes management using wait() %}


- ... belongs to a family of system calls. 
- ... are used to make a process to *wait* for its child process. 
- [Documentation for wait()](https://man7.org/linux/man-pages/man2/wait.2.html)
- Some important points:
- What are we waiting for? **state changes**. 
    - The child process was stopped by a signal.  
    - The child process terminated. 
    - The child process was resumed by a signal. 
- **wait()**: suspends execution of the calling thread until one of its child processes terminates.

{% enddetails %}
{% details Hands-on: wait() %}


{% details View source code of p2.c on Code browser %}


- Line 1-4: Pay attention to the libraries included. 
- Line 6-7: No idea why the author sets up the source code that way ...
- Line 9: prints out hello world and the process identifier (pid) of the current process.
- Line 10: calls `fork()`, which initiate the creation of a new process. The return of this fuction 
call is assigned to variable `rc`. 
- Line 11: If `rc` is negative, the function call failed and the program exits with return value 1. 
This line is evaluated within the parent process (since the child process creation failed).
- Line 15: If `rc` is equal to `0`.
- The child process will execute the codes inside this conditional block. 
- Line 17: prints out a statement and the child's `pid`. 
- Line 18: sleeps for one second. 
- Line 19: This is the parent process (`rc` is non-negative and not equal to 0) 
    - Line 21: calls the `wait()` function. 
    - Line 22: prints out the information of the parent process. 

{% enddetails %}
- Run p2 several times. 

```bash
./p2
```

{% details What do you notice? %}


{% include figure.liquid path="assets/img/courses/csc331/process/06.png" width="50%" zoomable=true %}

{% enddetails %}

{% enddetails %}

{% details exec() %}


- [Documentation for exec()](https://linux.die.net/man/3/exec)
- `fork()` lets you create and run a copy of the original process. 
- `exec()` lets you run a different process in place of **the copy** of the original process. 

{% enddetails %}
{% details Hands-on: exec() %}


{% details View source code of p3.c on Code browser %}

- Line 1-5: Pay attention to the libraries included. 
- Line 7-8: `main`
- Line 10: prints out hello world and the process identifier (pid) of the current process.
- Line 11: calls `fork()`, which initiate the creation of a new process. The return of this function 
call is assigned to variable `rc`.
- Line 12: If `rc` is negative, the function call failed and the program exits with return value 1. 
This line is evaluated within the parent process (since the child process creation failed).
- Line 16: If `rc` is equal to `0`.
- The child process will execute the codes inside this conditional block. 
- Line 18: prints out a statement and the child's `pid`. 
- Line 19-22: sets up parameters for a shell command (`wc` in this case). 
- Line 23: `exec` replaces the current child process with a completely new process to 
execute the `wc` command. 
- Line 24: This line's code is contained in the current child process, but was wiped 
out when `exec` replaces the current child process with the new process for `wc`. 
- Line 25: This is the parent process (`rc` is non-negative and not equal to 0) 
    - Line 27: calls the `wait()` function. 
    - Line 28: prints out the information of the parent process. 

{% enddetails %}
- Run p3.

```bash
./p3
```

- What is not being printed? Why?

{% enddetails %}
{% details Why fork(), wait(), and exec()? %}


- The separation of `fork()` and `exec()` is essential to the building of a Linux shell.  
- It lets the shell runs code after the call to `fork()`, but before the call to `exec()`.  
- This facilitates a number of interesting features in the UNIX shell. 

{% enddetails %}


## The Shell

{% details What is the UNIX shell? %}

In Unix, the shell is a program that interprets commands and acts as an intermediary between 
the user and the inner workings of the operating system. Providing a command-line interface (that 
is, the shell prompt or command prompt), the shell is analogous to DOS and serves a purpose similar 
to graphical interfaces like Windows, Mac, and the X Window System. 

{% enddetails %}

{% details Why is the shell a process? %}
- **In Unix, the shell is a program ...** 
    - Therefore, the running shell is **a process**.
    - In other words, inside a running shell, if we want to run another program, we are essentially
    *asking a process (the running shell) to create and run another process*. 

- When you run a program from the shell prompt, the shell will  
    - find out where the program is in the file system. 
    - call `fork()` to create a new child process (to run the program). 
    - call one of the `exec()` family functions in the scope of this child process
    to actually load and run this program. 
    - call `wait()` to wait for the child process to finish (now with new process content) before
    giving user the **shell prompt** again. 

{% enddetails %}

{% details Hands-on: redirection %}

- Run the following command

```bash
wc p3.c
wc p3.c > newfile.txt
cat newfile.txt
```

- The shell ... 
    - finds out where `wc` is in the file system. 
    - prepares `p3` as in input to `wc`. 
    - calls `fork()` to create a new child process to run the command.
    - recognizes that `>` represents a redirection, thus closes the file descriptor to 
    standard output and replaces it with a file descriptor to newfile.txt.
    - calls one of exec() family to run wc p3.c.
    - output of wc p3.c are now send to newfile.txt.
    - calls wait() to wait for the child process to finish before giving user the prompt again. 

{% enddetails %}
{% details Hands-on: redirection and file descriptors %}


- Run the following commands

```bash
./p4
ls
cat p4.output
cat -n p4.c
```

- `wc p4` should have printed out to terminal.
- `close(STDOUT_FILENO)` closes the file descriptor that writes to the terminal 
(hence free up that particular file descriptor ID).
- `open(“./p4.output”, …)` creates a file descriptor for the p4.output file, but since the 
file descriptor ID for the terminal is now free, this file descriptor is assigned to p4.output.
- As `wc p4` is executed and attempts to write to terminal, it actually writes to p4.output instead.  
- This is the basis for the concepts of redirection and pipelining in Linux.

{% enddetails %}


## Other system calls ...

- `kill()`: send signals to a process, including directive to pause, die, and other imperatives.
  - http://man7.org/linux/man-pages/man2/kill.2.html
  - SIGINT: signal to terminate a process  
  - SIGTSTP: pause the process (can be resumed later).
- `signal()`: to catch a signal.
  - http://man7.org/linux/man-pages/man7/signal.7.html 
