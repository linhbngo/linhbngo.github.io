---
layout: lecture
pretty_table: true
collection: csc231
course: CSC 231: Computer Systems
title: "Introduction to C"
toc:
  - name: What is C?
  - name: C and Java
  - name: Hands-on: Getting started
  - name: Challenge: output
  - name: Input: scanf
  - name: Challenge
  - name: Conditionals and Loops
  - name: Function in C
  - name: Arrays
---
# Introduction to C

{% details Relevant Reading %}

{% enddetails %}
:class: tip

This lecture will cover contents from [Chapter 1 - Appendix version](https://diveintosystems.org/book/Appendix1/index.html) of the book. 

```


## What is C?

### Overview

- Developed by Dennis Ritchie at Bell Labs
- First public released in 1972. 
- **The** book: *The C programming languange" by Dennis M. Ritchie and Brian W. Kernighan. 
Prentice Hall 1988. 

:::{dropdown} How to learn C (now that you already know Java)? 

- [C for Java programmers](https://www.cs.rochester.edu/u/ferguson/csc/c/c-for-java-programmers.pdf)
- [C programming vs. Java programming](https://introcs.cs.princeton.edu/java/faq/c2java.html)

:::

### Scary stuff ahead ...
 
- C is much less supportive for programmers than Java.
- (Much) easier to make mistake, and (much) harder to fix. 

### But it is exciting ...     
 
- C requires less memory resources than Java.
- C, in many instances, runs faster than Java. 
- Knowing C will make you a better programmer overall. 


## C and Java

:::::{tab-set} 
::::{tab-item} hello.c

~~~c
#include <math.h>
#include <stdio.h>

/* main function definition: */
int main() {
    printf("Hello World\n");
    printf("sqrt(4) is %f\n", sqrt(4));
    return 0;  // main returns value 0
}
~~~

::::

::::{tab-item} hello.java

~~~java
import java.lang.Math;

/* define a HelloWorld class */
class Hello {

  /* main method definition: */
  public static void main(String[] args){
    System.out.println("Hello World");
    System.out.println("sqrt(4) is " + Math.sqrt(4));
  }
}
~~~

::::
:::::


### Similarities      
 
- Values, types, literals, expressions
- Variables
- Control flow (if, switch, while, for, do-while)
- Call-return: parameters, arguments, return values
- Arrays (mostly)
- Primitive and reference types
- Type casting. 
- Library usage. 


### Differences     


- C has no classes or objects (but something similar)
- C is not object-oriented. 
- C arrays are simpler:
  - No boundary checking. 
  - No knowledge of array's own size. 
- String operations are limited. 
- No collections, exceptions, or generics. 
- No automatic memory management. 
- **Pointers!!!**

:::::{tab-set} 
::::{tab-item} Running Java

:::{image} fig/02-c/java.png
:alt: Java compilation and execution
:class: bg-primary mb-1
:align: center
:::

::::
::::{tab-item} Running C

:::{image} fig/02-c/c.png
:alt: C compilation and execution
:class: bg-primary mb-1
:align: center
:::

::::
:::::


## Hands-on: Getting started

- SSH to `molly`. Refer to the Setup page if you need a refresher on how to 
do so.
- Change into `csc231` from inside your home directory. 
  - Your home directory is represented by the `~` sign. 
- Create a directory named `intro-c` inside `csc231`, 
then change into that directory.

~~~
cd ~/csc231
pwd
mkdir intro-c
ls
cd intro-c
pwd
~~~

:::{image} fig/02-c/02.png
:alt: create intro-c directory
:class: bg-primary mb-1
:align: center
:::


### Create hello.c

- Inside the terminal, make sure that you are still inside
`intro-c`, then use `nano` to create `hello.c`with the source code below. 

~~~
pwd
nano -l hello.c
~~~

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=hello.c"></script>

- Once finished editing in `nano`:
  - first hit `Ctrl-X` (same for both Windows and Mac). 
  - Next hit `Y` to save modified buffer (new contents). 
  - Hit `Enter` to save to the same file name as what you opened with. 
- **Memorize your key-combos!**.

:::{image} fig/02-c/03.png
:alt: Create hello.c using nano
:class: bg-primary mb-1
:align: center
:::

### What's in the code?

- Line 1: Standard C library for I/O, similar to Java's `import`.
- Line 2-4: Function declaration/definition for `main`:
  - Line 2: 
    - return type: `int`
    - function name: `main`
    - parameter list: 
       - `argc`: number of command line arguments.
       - `*argv[]`: pointers to array of command line argument strings. 
   - Line 3: Invoke builtin function `printf` to print out  string `Hello world!`
   with an end-of-line character `\n`. This is similar to `System.out.printf`.
   - Line 4: Exit a successfully executed program with a return value of 0. 

#### Hands-on: Simple compile and run

- Similar to `javac`, we use `gcc` to compile C code. 
- Before compile, make sure that you are still inside `intro-c` in the terminal. 

~~~
ls
pwd
gcc -o hello hello.c
ls
./hello
~~~

:::{image} fig/02-c/04.png
:alt: Creating hello.c using nano
:class: bg-primary mb-1
:align: center
:::

### Hands-on: Compile and show everything

- There are a number of steps from C codes to executable binaries.  

~~~
ls -l
gcc -save-temps -o hello2 hello.c
ls -l
./hello2
~~~

:::{image} fig/02-c/05.png
:alt: compile and run hello.c, keeping intermediate files
:class: bg-primary mb-1
:align: center
:::

### What are those?

- `hello.i`: generated by pre-processor
- `hello.s`: generated by compiler.
- `hello.o`: generated by assembler.
- `hello` (or `hello2`): executable, generated by linker.

:::{image} fig/02-c/06.png
:alt: hello.c compilation process
:class: bg-primary mb-1
:align: center
:::

### Hands-on: View files

- For `hello.i` and `hello.s`, they can be view on the editor. 
- Run the following command to view `hello.i`

~~~
cat -n hello.i
~~~


- Run the following command to view `hello.s`

~~~
cat -n hello.s
~~~


- For `hello.o` and `hello`, we need to dump the binary contents first. 

~~~
xxd -b hello.o hello.o.txt
xxd -b hello hello.txt
ls -l
~~~

:::{image} fig/02-c/07.png
:alt: hexdumping hello.c and hello
:class: bg-primary mb-1
:align: center
:::

- Run the following command to view `hello.o.txt`

~~~
cat -n hello.o.txt
~~~


- Run the following command to view `hello.txt`

~~~
cat -n hello.txt
~~~

## Challenge: output

The usage of C's `printf` is similar to Java's `System.out.printf`. Find out how to 
modify `hello.c` so that the program prints out `Hello Golden Rams!` with each word
on a single line. The program should use exactly one `printf` statement. 

:::{dropdown} Answer
    
<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=hello-3.c"></script>

:::


## Input: scanf

C formatting placeholders: (similar to Java)
- `%g`:  placeholder for a float (or double) value
- `%d`:  placeholder for a decimal value (int, short, char)
- `%s`:  placeholder for a string value
- `%c`:  placeholder for a char value

:::::{tab-set} 
::::{tab-item} readInput.c

~~~c
#include <stdio.h>

int main() {
  int num1, num2;
  printf("Enter a number: ");
  scanf("%d", &num1);
  printf("Enter another: ");
  scanf("%d", &num2);
  printf("%d + %d = %d\n", num1, num2, (num1+num2) );
  return 0;
}
~~~

::::

::::{tab-item} InputReader.java

~~~java
import java.util.Scanner;

class InputReader {
  public static void main(String[] args) {
    int num1, num2;
    Scanner in = new Scanner(System.in);
    System.out.print("Enter a number: ");
    num1 = in.nextInt();
    System.out.print("Enter another: ");
    num2 = in.nextInt();
    System.out.printf( "%d + %d = %d\n",
          num1, num2, (num1+num2) );
  }
}
~~~

::::
:::::

## Challenge

Create a file called **mixedInput.c** that is modified from 
**readInput.c**. The file should do the followings:
- Ask user to provide three input of type **float**
- Print out the multiplication statement with all the multiplicants 
and results as done in **readInput.c**. 

:::{dropdown} Answer     

~~~c
#include <stdio.h>

int main() {
  float num1, num2, num3;
  printf("Enter a number: ");
  scanf("%g", &num1);
  printf("Enter another: ");
  scanf("%g", &num2);
  printf("Enter another: ");
  scanf("%g", &num3);
  printf("%g * %g * %g = %g\n", num1, num2, num3, (num1*num2*num3) );
  return 0;
}
~~~

:::


## Conditionals and Loops

Similar to Java. 

- Conditionals: **compare.c**

~~~c
#include <stdio.h>

int main(void) {
    int num1, num2;

    printf("Enter the 1st number: ");
    scanf("%d", &num1);
    printf("Enter the 2nd number: ");
    scanf("%d", &num2);

    if (num1 > num2) {
        printf("%d is biggest\n", num1);
    } else if (num1 == num2) {
        printf("%d and %d are the same\n", num1, num2);
    } else {
        printf("%d is biggest\n", num2);
    }

    return 0;
}
~~~

- Loops

:::::{tab-set} 
::::{tab-item} forLoop.c

~~~c
#include <stdio.h>

int main(void) {
    int num, i;

    printf("Enter a value: ");
    scanf("%d", &num);
    // make sure num is not negative
    if (num < 0) {
        num = -num;
    }

    for (i = 0; i < num; i++) {
        printf("%d\n", i);
    }

    return 0;
}
~~~

::::

::::{tab-item} whileLoop.c

~~~c
#include <stdio.h>

int main(void) {
    int num, val;

    printf("Enter a value: ");
    scanf("%d", &num);
    // make sure num is not negative
    if (num < 0) {
        num = -num;
    }
    val = 1;
    while (val < num) {
        printf("%d\n", val);
        val = val * 2;
    }

    return 0;
}
~~~

::::
:::::


## Function in C


- Almost the same as methods in Java, except for one small difference. 
- They need to either be declared, or must be defined prior to being
called (relative to written code position). 

::::{dropdown} Hands-on: Functions in C - definition and declaration

- Create three C files, `function-1.c`, `function-2.c`, and `function-3.c`,
with the source codes below:

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=function-1.c"></script>
<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=function-2.c"></script>
<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=function-3.c"></script>

- Compile and run these files. 

:::{image} fig/02-c/23.png
:alt: Compile and run function-1.c, function-2.c, function-3.c
:class: bg-primary mb-1
:height: 250px
:align: center
:::
::::

## Arrays

- Statically declared arrays
- Multiple data values of the same types
- Adjancent locations in memory (we will talk about this in the future)
- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `array-1.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=array-1.c"></script>

- What is the distance between addresses? Why?
- Compile and run `array-1.c`

:::::{dropdown} Exercise

- Create a copy of `array-1.c` called `array-2.c`. 
- Change the type of `numbers` to `double`. 
- What is the address step now?

::::{dropdown} Answer    

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=array-2.c"></script>

::::
:::::

::::{dropdown} An array variable

- ... is in fact pointing to an address containing a value. 
- ... without the bracket notation and an index points to the 
corresponding address of the value at the index. 
- ... is quite similar to a pointer!
::::
