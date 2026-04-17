---
layout: lecture
pretty_table: true
collection: csc302

title: "Buffer Overflow"
toc:
  - name: Program Memory
  - name: Stack Memory
  - name: Buffer overflow attack
---
# Buffer Overflow


## Program Memory

{% details Overview %}



{% enddetails %}
- When a program runs, it is loaded into memory. 
- A running program is called a process.


{% details Five segments of a typical C program %}



{% enddetails %}
- Text segment (also known as code segment): stores the executable code of 
the program (usually read-only). 
- Data segment: stores static/global variables initialized in the program.
- BSS (block started by symbol) segment: stores uninitialized static/global 
variables. These variables will be initialized with zeros.
- Heap: provides space for dynamic memory allocation (caused by malloc, calloc, 
realloc, free, etc).
- Stack: is simple data structure with a LIFO (last-in-first-out access policy). 
Stack stores local variables defined inside functions, and data related to function 
calls (return address, arguments, etc)


{% details Segment allocation %}



{% enddetails %}
- Sizes of text, data, and BSS segment are known as soon as compilation 
or assembly is completed.
- Stack and heap segments will grow and shrink during program execution.
- Therefore, they tend to be configured such that they grow toward each other.
- The boundary between them is flexible.
- Both can grow until all available memory is used.

{% include figure.liquid path="assets/img/courses/csc302/buffer-overflow/segment.png" width="50%" zoomable=true alt="Memory segment allocations" %}


{% details Hands-on: mem_layout.c %}



{% enddetails %}
- Create a file called `mem_layout.c`

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=mem_layout.c"></script>

- Run the following commands

~~~bash
sudo apt-get update
sudo apt-get install -y gcc-multilib g++-multilib
gcc -m32 -W -c mem_layout.c
gcc -m32 -o mem_layout mem_layout.o
size mem_layout mem_layout.o
~~~

- Why don’t we see the stack and heap information?


{% details Hands-on: mem_layout_print.c %}



{% enddetails %}
- Create a file called `mem_layout_print.c`
  - You can make a copy from `mem_layout.c` and edit. 

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=mem_layout_print.c"></script>


- Run the following commands

~~~bash
gcc -m32 -o mem_layout_print mem_layout_print.o
./mem_layout_print
~~~

- Can you relate the variables’ position in memory to their respective position 
in a program’s memory layout?

{% include figure.liquid path="assets/img/courses/csc302/buffer-overflow/print_mem_layout.png" width="50%" zoomable=true alt="Mapping process memory to memory layout" %}

```

## Stack Memory

{% details Stack memory layout %}



{% enddetails %}
- When a function is called, a block of memory called stack frame will 
be pushed onto the top of stack. 
- A stack frame contains four regions:
  - Arguments that are passed to the function (if they don't fit on the 
  general purpose registers)
  - Return address (the address of the instructions right after 
  the function call
  - Previous frame pointer
  - Local variables of the function
- When the program first starts, the stack contains only one frame, 
that of the main function.

{% include figure.liquid path="assets/img/courses/csc302/buffer-overflow/stack_mem_layout.png" width="50%" zoomable=true alt="Stack memory layout" %}


{% details Previous frame pointer and function call chain %}



{% enddetails %}
- We can call a function from inside a function. 
- Any time we enter a function, a stack from is allocated on top of the stack. 
  - When the function returns, the allocated space is released. 

{% include figure.liquid path="assets/img/courses/csc302/buffer-overflow/call_chain.png" width="50%" zoomable=true alt="Chain of function calls" %}

```

## Buffer overflow attack

{% details Memory copy %}



{% enddetails %}
- Memory copy happens in programming when data from one place (source) is 
duplicated to another place (destination).
- Before copying can happen, memory needs to be allocated at the destination.
- If the allocation fails to be sufficient, it will result in an overflow.
- One of the oldest and most well-known attacks.


{% details Why do we need to learn this? %}



{% enddetails %}
- Can still be found buried in legacy or glue code from third party libraries 
as web sites get more complex and evolved.
- An important point of learning as you work through the theory and practice 
of this exploit:
  - C programming
  - C Assembler
  - Linux debugger using gdb
  - Engage in mathematics to understand the breaking points and 
  the hex contents in memory in order to place an attack


{% details strcpy %}



{% enddetails %}
- Create `strcpy_overflow.c`

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=strcpy_overflow.c"></script>

- Run the following commands

~~~bash
gcc -m32 -o strcpy_overflow strcpy_overflow.c
./strcpy_overflow
~~~

- What happens?
- The region above the buffer includes critical values, including the return address 
and the previous frame pointer.
- The consequences of a modified return address (due to buffer overflow) include:
  - The new address (virtual address) might not be mapped to any physical address, 
  leading to an invalid return instruction and a crashed program.
  - The address might be mapped to a physical address in protected system space, leading 
  to a failed jump and a crashed program.
  - The address might be mapped to a physical address that does not contain any valid 
  instruction, leading to a failed return and a crashed program.
  - The address might be mapped to a physical address that happens to contain valid 
  machine instructions, leading to a continuing program with logic different from the original program.

- Run the following commands

~~~bash
git clone https://github.com/longld/peda.git
echo "source $HOME/peda/peda.py" > $HOME/.gdbinit
gcc -m32 -g -o gdb_strcpy_overflow strcpy_overflow.c
gdb gdb_strcpy_overflow
~~~

- Setup gdb with a breakpoint at main (`b main`) and start running (`run`).
- A new GDB command is `si`: executing the next instruction (machine or code instruction).
  - It will execute the highlighted (greened and arrowed) instruction in the code section.
  - If the Assembly instruction is calling another function, we need to use `ni` if we don’t 
  want to step into that instruction.



{% details A vulnerable program %}



{% enddetails %}
- Create `stack.c`

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=stack.c"></script>

- This file has a clear buffer overflow issue. 
  - How can we exploit this?

{% include figure.liquid path="assets/img/courses/csc302/buffer-overflow/design_exploit.png" width="50%" zoomable=true alt="Design a buffer overflow exploit" %}


{% details Preparations %}



{% enddetails %}
- Rerun `mem_layout_print` several times

~~~bash
./mem_layout_print
./mem_layout_print
./mem_layout_print
~~~

- You will notice the addresses printed out change each time. This is one of the 
system protection against buffer overflow attacks. 
- First, we need to disable the countermeasures

~~~bash 
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
~~~

- Rerun mem_layout_print several time to confirm that addresses are not changing
	
~~~bash
./mem_layout_print
./mem_layout_print
./mem_layout_print
~~~


{% details First try %}



{% enddetails %}
- We need to include the following flags in compiling
	- `-z execstack`
	- `-fno-stack-protector`

~~~bash
gcc -m32 -o stack -z execstack -fno-stack-protector stack.c
sudo chown root stack
sudo chmod 4755 stack
echo "aaaa" > badfile
./stack
echo "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" > badfile
./stack
~~~

- Why segmentation fault?


{% details Second try %}



{% enddetails %}
- How do we know (guess) where the stack frame of `foo()` will be for us 
to find out where the malicious code is located (and hence set the relevant 
jump address)?
  - Fixed starting address of the stack (before countermeasure).
  - The stack is shallow (good programming practice don't use deeply nested functions).
- To make a (much more) educated guess

~~~bash
gcc -m32 -g -o gdb_stack -z execstack -fno-stack-protector stack.c
rm badfile
touch badfile
gdb gdb_stack
~~~

- Run the following GDB command inside gdb (gdb-peda)

~~~bash
break foo
run
print $ebp
print &buffer
print <hex address of ebp> - <hex address of buffer>
quit
~~~

- Take notes of your $ebp
- What is the result of the subtraction? 
  - Either `108` (decimal) or `0x6C` (hex)?

{% include figure.liquid path="assets/img/courses/csc302/buffer-overflow/why_108.png" width="50%" zoomable=true alt="Why 108" %}


{% details Third try %}



{% enddetails %}
- Payload: A shellcode containing the `/bin/sh` command
- Use Assembly's NOP to improve the attack chance

{% include figure.liquid path="assets/img/courses/csc302/buffer-overflow/nop.png" width="50%" zoomable=true alt="NOP to improve attach chance" %}

- Create and run exploit.c

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=exploit.c"></script>

- Does it work
  - Unlikely to work the first time.
  - If hang, Ctrl-C to quit out of the hanging stack program.
  - Need to modify added hex value (increment multiples of 4 at a time) 

{% include figure.liquid path="assets/img/courses/csc302/buffer-overflow/buffer_overflow.png" width="50%" zoomable=true alt="NOP to improve attach chance" %}


{% details Countermeasures %}



{% enddetails %}
- Safer functions: specification of maximum data length 
to be copied
- Safer dynamic link library: dynamic link to safer libraries (as 
opposed to calling unsafe functions)
- Program static analyzer: warn of code patterns that could lead 
to buffer overflow
- Programming language: self-check against buffer overflow in the language
- Compiler: `-fno-stack-protector`
- Operating system: `kernel.randomize_va_space`

```
