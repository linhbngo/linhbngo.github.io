---
layout: lecture
pretty_table: true
collection: csc331
course: CSC 331: Operating Systems
title: "Process in XV6"
toc:
  - name: How does fork() behave in xv6?
  - name: What about wait()?
  - name: The implementation of fork() in xv6
---
# Process in XV6

---

## How does fork() behave in xv6?

- Using the code browser, create a file called `p1.c` inside the `user` directory of `xv6-riscv` directory with the following content:

~~~c
#include "kernel/types.h"
#include "user/user.h"

int main() {
  int pid = fork();
  if (pid == 0) {
    printf("Child: my pid is %d\n", getpid());
    exit(0);
  } else {
    printf("Parent: my pid is %d, child is %d\n", getpid(), pid);
  }
  exit(0);
}

{% details Screenshot: creating p1.c inside xv6-riscv/user %}

{% include figure.liquid path="assets/img/courses/csc331/process-xv6/01.png" width="50%" zoomable=true %}   

{% enddetails %}
- In `Makefile` under `xv6-riscv`, find the section `UPROGS=` and edit to include the `$U/_p1\` line. 

{% details Screenshot: Edit xv6-riscv/Makefile %}

{% include figure.liquid path="assets/img/courses/csc331/process-xv6/02.png" width="50%" zoomable=true %}  

{% enddetails %}
- Let's rebuild and relaunch xv6. In a terminal, run the followings

~~~bash
cd ~/xv6-riscv
make clean
make
make qemu
~~~


- When you run `ls`, you will see the content of the available commands in xv6, which now includes `p1`. 
- Run p1 several times. 

{% details Screenshot: content of ls %}

{% include figure.liquid path="assets/img/courses/csc331/process-xv6/03.png" width="50%" zoomable=true %}

{% enddetails %}
{% details What do you expect to see, and what do you have? Why? %}

{% include figure.liquid path="assets/img/courses/csc331/process-xv6/04.png" width="50%" zoomable=true %}


{% enddetails %}
---

## What about wait()?


- Using the code browser, create a file called `p2.c` inside the `user` directory of `xv6-riscv` directory with the following content:

~~~c
#include "kernel/types.h"
#include "user/user.h"

int main() {
  int pid = fork();
  if (pid == 0) {
    printf("Child: my pid is %d\n", getpid());
    exit(0);
  } else {
    wait(0);
    printf("Parent: my pid is %d, child is %d\n", getpid(), pid);
  }
  exit(0);
}

{% details Screenshot: creating p2.c inside xv6-riscv/user %}

{% include figure.liquid path="assets/img/courses/csc331/process-xv6/05.png" width="50%" zoomable=true %}   

{% enddetails %}
- In `Makefile` under `xv6-riscv`, find the section `UPROGS=` and edit to include the `$U/_p2\` line. 

{% details Screenshot: Edit xv6-riscv/Makefile %}

{% include figure.liquid path="assets/img/courses/csc331/process-xv6/06.png" width="50%" zoomable=true %}  

{% enddetails %}
- Let's rebuild and relaunch xv6. In a terminal, run the followings

~~~bash
cd ~/xv6-riscv
make clean
make
make qemu
~~~


- When you run `ls`, you will see the content of the available commands in xv6, which now includes `p1` and `p2`. 
- Run p2 several times. Observe the change in output. 

---

## The implementation of fork() in xv6

- Source code of `fork()` can be found in `kernel/proc.c`.
    - This is the kernel implementation of the `fork()` system call.  
    - **Goal**: Create a new process that is an (almost) exact copy of the calling process.

{% details info Details %}

~~~c
int i, pid;
struct proc *np;
struct proc *p = myproc();
~~~

{% enddetails %}
- `p = myproc()` retrieves the **current running process** (caller of `fork()`).
    - `myproc()` is defined in `kernel/proc.c`.
    - Uses `r_tp()` (thread pointer register) to find the process on the current CPU.
- `np`: placeholder for the new process structure.
- `i`: loop index.
- `pid`: the child’s PID to return.

{% details info Details %}

~~~c
// Allocate process.
if((np = allocproc()) == 0){
    return -1;
}
~~~

{% enddetails %}
- `allocproc()` finds an UNUSED `struct proc` and sets up a kernel stack and page table.
    - Defined in `kernel/proc.c`
    - Initializes `trapframe`, `pagetable`, and locks the process.
    - Returns `-1` on failure, signaling fork error.
    - Expect to find an available proc slot in the process table. Maximum limit is 64 (see `kernel/param.h`).

{% details info Details %}

~~~c
// Copy user memory from parent to child.
if(uvmcopy(p->pagetable, np->pagetable, p->sz) < 0){
    freeproc(np);
    release(&np->lock);
    return -1;
}
np->sz = p->sz;
~~~

{% enddetails %}
- `uvmcopy(...)` copies the parent’s entire user address space into the child.
    - `uvmcopy()` is defined in `kernel/vm.c`
    - On failure, clean up the new proc and return error.
    - `sz` is the size of the user memory (stack, heap, etc), defined in `struct proc`. 

{% details info Details %}

~~~c
// copy saved user registers.
*(np->trapframe) = *(p->trapframe);
~~~

{% enddetails %}
- The **trapframe** stores user-space registers saved during a syscall/trap.
    - `trapframe` is a `struct` defined in `kernel/riscv.h`
    - This ensures that when the child resumes in user space, it resumes from the same point.

{% details info Details %}

~~~c
// Cause fork to return 0 in the child.
np->trapframe->a0 = 0;
~~~

{% enddetails %}
- In RISC-V calling convention:
    - `a0` is the return value register. 
    - The parent's `a0` will be set to the child's PID (done after fork returns).
    - The child's `a0` is set to 0 here, so that when the child process is ready to resume running, it will see that fork() returned 0. 
- This mimics how `fork()` returns in POSIX:
    - In the **parent**, it returns child's PID.
    - In the **child**, it returns `0`.

{% details info Details %}

~~~c
// increment reference counts on open file descriptors.
for(i = 0; i < NOFILE; i++)
    if(p->ofile[i])
    np->ofile[i] = filedup(p->ofile[i]);
~~~

{% enddetails %}
- Copies the parent's open file table to the child.
    - At the very least, you have the entries 0, 1, 2 for input, output, and error. 
    - `ofile[]` is an array of file pointers in `struct proc` (📍 in `kernel/proc.h`)
    - `filedup()` increases reference counts.
        - Defined in `kernel/file.c`


{% details info Details %}

~~~c
np->cwd = idup(p->cwd);
~~~

{% enddetails %}
- Duplicates the parent’s **current working directory** inode for the child.
    - `idup()` increments the inode’s ref count.
    - `idup()` is defined in `kernel/fs.c`

{% details info Details %}

~~~c
safestrcpy(np->name, p->name, sizeof(p->name));
~~~

{% enddetails %}
- Copies the process name (for debugging purposes).
    - `safestrcpy()` is defined in `kernel/string.c`


{% details info Details %}

~~~c
pid = np->pid;
~~~

{% enddetails %}
- Store the child’s PID for returning to the parent.

{% details info Details %}

~~~c
release(&np->lock);
~~~

{% enddetails %}
- Done modifying the child; release its lock temporarily.

---

{% details info Details %}

~~~c
acquire(&wait_lock);
np->parent = p;
release(&wait_lock);
~~~

{% enddetails %}
- Set the parent pointer.
- This is protected by `wait_lock` so that `wait()` and `exit()` (which also touch `parent`) are synchronized.
    - `wait_lock` is declared in `kernel/proc.c`


{% details info Details %}

~~~c
acquire(&np->lock);
np->state = RUNNABLE;
release(&np->lock);
~~~

{% enddetails %}
- Marks the child process as `RUNNABLE`, so it can be scheduled.
    - Process states are defined as `enum procstate` in `kernel/proc.h`
    - Once marked RUNNABLE, the child will be picked up by the scheduler in a future time slice.

{% details info Details %}

~~~c
return pid;
~~~

{% enddetails %}
- Return the child’s PID to the parent.
- The child will resume execution from the exact point where `fork()` was called, but will receive return value `0` because of `trapframe->a0 = 0`.


{% details Summary of key structures and calls %}


| Symbol         | Description                         | File              |
| -------------- | ----------------------------------- | ----------------- |
| `struct proc`  | Per-process control block           | `kernel/proc.h`   |
| `myproc()`     | Get current process                 | `kernel/proc.c`   |
| `allocproc()`  | Allocate and initialize new proc    | `kernel/proc.c`   |
| `uvmcopy()`    | Copy address space (page tables)    | `kernel/vm.c`     |
| `trapframe`    | Saved user-space CPU registers      | `kernel/riscv.h`  |
| `filedup()`    | Increment file descriptor refcount  | `kernel/file.c`   |
| `idup()`       | Increment inode refcount            | `kernel/fs.c`     |
| `safestrcpy()` | Safe string copy                    | `kernel/string.c` |
| `wait_lock`    | Lock for parent/child relationships | `kernel/proc.c`   |


{% enddetails %}
