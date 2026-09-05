---
layout: lecture
pretty_table: true
collection: csc302

title: "Return to libc"
toc:
  - name: Overview
  - name: Attack design
  - name: Attack
---

# Return to libc

## Overview

{% details Stack-based buffer overflow attack %}



{% enddetails %}
- Malicious data are used to overflow a function's return 
address in order to get the program to jump to a different 
location on the stack which stores malicious code.
- Existing counter-measures:
  - Random address in virtual address space: `echo 0 | sudo tee /proc/sys/kernel/randomize_va_space`
	- Making code on stack non-executable: `-z execstack`
	- Prevent modification to the stack: `-fno-stack-protector`


{% details Non-executable stack %}



{% enddetails %}
- Create the following file, `shellcode.c`:

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=shellcode.c"></script>

```bash
seed@instructor:~$ gcc -m32 -z execstack -o shellcode shellcode.c
seed@instructor:~$ ./shellcode
seed@instructor:~$ gcc -m32 -o shellcode shellcode.c
seed@instructor:~$ ./shellcode
```

```

## Attack design

{% details Evaluation %}



{% enddetails %}
- Good countermeasure, but not enough.
- If the stack is not executable, an alternative solution is to make 
the program jump to where there are executable codes.
- Enter the region for standard C library on Linux, called `libc`.




{% details Design %}



{% enddetails %}
{% include figure.liquid path="assets/img/courses/csc302/libc/libc_design.png" max-width="50%" zoomable=true alt="Overview of libc attack" %}


{% details The vulnerable program, again %}



{% enddetails %}
- Create a file named `stack.c`

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=stack_libc.c"></script>

- Compile stack with specific flags

```bash
gcc -m32 -fno-stack-protector -z noexecstack -o stack stack.c
sudo sysctl -w kernel.randomize_va_space=0
sudo chown root stack
sudo chmod 4755 stack
```

- Flag meanings
  - `fno-stack-protector`: disable protection against changes in stack
  - `-z noexecstack`: actually turn on protection against executable stack
  - `kernel.randomize_va_space=0`: disable address space layout randomization
  - Afterward, turn the program into a root-owned set-UID program


{% details Launch the return-to-libc attack %}



{% enddetails %}
- Task A: find where in memory is `system()` located.
- Task B: find the address of the `/bin/sh` string.
- Task C: where to place the address of `/bin/sh` in the 
stack so that system() can get to it.


{% details Task A: find the address of the system() function %}



{% enddetails %}
- Anytime a program runs, the `libc` library will be loaded into memory. 
- Using `gdb`, we can find out the location of `system()` with the 
following commands:

```bash
gdb stack
```

- This is to bring up `gdb-peda`. We don't need a `-g` enabled version 
for the followings: 

```bash
(gdb-peda)$ run
(gdb-peda)$ p system
(gdb-peda)$ p exit
(gdb-peda)$ quit
```

- Rerun the entire process. several time to ensure that 
the addresses doesn’t change, and **record the values**.

```

{% details note Task B: find the address of the string "/bin/sh %}



{% enddetails %}
- We want `system()` to execute `/bin/sh`.
- Therefore, `/bin/sh` must be in memory, and 
its address should be passed to `system()` as an argument.
- We cannot embed this in the source code (no access to source 
code of vulnerable program).
- Solution:
  - Utilize environment variables



{% details Where the wild things are ... %}



{% enddetails %}
- Create a file named `find_myshell.c`

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=find_myshell.c"></script>

- Create the EV, then compile and run find_myshell.c

```bash
export MYSHELL="/bin/sh"
gcc -m32 -o myshell find_myshell.c
./myshell
gcc -m32 -o myshell0 find_myshell.c
./myshell0
gcc -m32 -o myshell1 find_myshell.c
./myshell1
gcc -m32 -o myshell22 find_myshell.c
./myshell22
gcc -m32 -o myshell222 find_myshell.c
./myshell222
```

- What is your observation regarding memory position of 
environment variables?


{% details Function prologue %}



{% enddetails %}
- In buffer overflow, we manually place both `system()` and 
its corresponding arguments on the stack for execution.
- In `return-to-libc`, we invoke `system()` remotely.
- How can we place the corresponding arguments onto the stack?
  - `$esp`: Stack register

{% include figure.liquid path="assets/img/courses/csc302/libc/function_prologue_1.png" max-width="50%" zoomable=true alt="Function prologue 1" %}

- What happens just before a function is called?

```bash
pushl %ebp
movl %esp, %ebp
subl $N, %esp
```

- Return address (RA) is pushed onto the stack.
- Save (push) the caller function’s frame pointer (ebp)
- Set frame pointer to the stack pointer (esp) ’s current position
- Move the stack pointer by several bytes, leaving spaces for the 
local variables of the function.

{% include figure.liquid path="assets/img/courses/csc302/libc/function_prologue_2.png" max-width="50%" zoomable=true alt="Function prologue 2" %}


{% details Function Epilogue %}



{% enddetails %}
- What happens just before a function is completed?

```bash
movl %ebp, %esp
popl %ebp
ret
```

- Move `%esp` to where the frame pointer points to 
(releasing the stack space for variables).
- Most most recent value of `%ebp`, return it to 
point to the previous frame pointer. 
- Pops the return address from the stack, then 
jump to it, and move `%esp` to the top of the previous stack frame

{% include figure.liquid path="assets/img/courses/csc302/libc/function_epilogue.png" max-width="50%" zoomable=true alt="Function epilogue" %}




{% details Important Notes %}



{% enddetails %}
- The malicious function did finish properly.
  - Its function epilogue was called.
  - We know the location of $esp.
- The malicious call redirect RA (next instruction) to a new function.
  - Activate this new function prologue
  - But this new function will rely on values in `$esp` for execution
  - We need to manipulate `$esp`
- Observation
  - `$esp` and `$ebp` are values from vul_func(), but they are changed due to 
  the procedural execution of vul_func()'s epilogue and system()'s prologue.

{% include figure.liquid path="assets/img/courses/csc302/libc/vul_func.png" max-width="50%" zoomable=true alt="How changes are made" %}

```

## Attack

{% details Calculating offset %}



{% enddetails %}
- Compile `gdb_stack` 

```bash
gcc -m32 -fno-stack-protector -z noexecstack -g -o gdb_stack stack.c
gdb gdb_stack
```

- Run `gdb_stack` with the following steps

```bash
gdb-peda$ break vul_func
gdb-peda$ run
gdb-peda$ n
gdb-peda$ p $ebp
gdb-peda$ p &buffer
gdb-peda$ p hex_value_from_ebp - hex_value_from_buffer
gdb-peda$ quit
```

- The distance should be `0x3e` (`62`)
- Offsets
  - Offset of 3 is distance + 4: address of `system()`
  - Offset of 2 is distance + 8: address of `exit()`
  - Offset of 1 is distance plus 12: address of `/bin/sh`

{% include figure.liquid path="assets/img/courses/csc302/libc/distance.png" max-width="50%" zoomable=true alt="Distance and offsets" %}


{% details Create ret_to_libc_exploit.c %}



{% enddetails %}
<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=ret_to_libc_exploit.c"></script>

```bash
gcc -o kcats find_myshell.c
./kcats
```

- Keep track of the `/bin/sh` address. 
- Use the recorded address from `system` and `exit`, and 
the `/bin/sh` address to modify `ret_to_libc_exploit.c`. 


{% details The actual attack %}



{% enddetails %}
```bash
gcc -m32 -o exploit ret_to_libc_exploit.c; ./exploit; ./stack
```

```



