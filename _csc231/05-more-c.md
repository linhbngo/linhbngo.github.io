---
layout: lecture
pretty_table: true
collection: csc231
course: CSC 231: Computer Systems
title: "Even more C"
toc:
  - name: Addresses and pointers
  - name: Pointers and memory allocation
  - name: Array in C
  - name: Command line arguments.
  - name: String
  - name: Object in C
  - name: Function in C
---
# Even more C

{% details Relevant Reading %}

{% enddetails %}
:class: tip
This lecture will cover contents from [Chapter 2](https://diveintosystems.org/book/C2-C_depth/index.html) and [Chapter 3](https://diveintosystems.org/book/C3-C_debug/index.html) of the book. 

```


## Addresses and pointers


- In Java, you can manipulate the value of a variable via the program but not directly 
in memory (inside the JVM). 
- In C, you can retrieve the address of the location in memory where the variable is 
stored. 
- The operator `&` (reference of) represents the memory address of a variable.



::::{dropdown} Hands-on: Pointer

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `pointer-1.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=pointer-1.c"></script>

- `%p` is an output conversion syntax (similar to Java specifiers) for displaying memory 
address in hex format. See [Other Output Conversions](https://www.gnu.org/software/libc/manual/html_node/Other-Output-Conversions.html#Other-Output-Conversions) for more 
details.
- Compile and run `pointer-1.c`

~~~
ls
gcc -o pointer-1 pointer-1.c
./pointer-1
~~~

:::{image} fig/02-c/08.png
:alt: Compile and run pointer-1.c
:class: bg-primary mb-1
:height: 400px
:align: center
:::

::::

:::{dropdown} Pointer Definition

- Pointer is a variable that points to a memory location (contains a memory location).  
  - We call them *pointer variables*. 
- A pointer is denoted by a `*` character. 
- The type of pointer must be the same as that of the value being stored in 
the memory location (that the pointer points to).
- If a pointer points to a memory location, how do we get these locations?
  - An `&` character in front of a variable (includes pointer variables) denotes that
  variable's address location. 

:::

::::{dropdown} Hands-on: Pointer and Variable's Addresses

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `pointer-2.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=pointer-2.c"></script>

- Since `p_i` is a pointer variable, `p_i` contains a memory address (hence `%p`).
- Then, `*p_i` will point to **the value in the memory address contained in p_i**. 
  - This is referred to as *de-referencing*. 
  - This is also why the type of a pointer variable must match the type of data stored
  in the memory address the pointer variable contains. 
- Compile and run `pointer-2.c`

:::{image} fig/02-c/09.png
:alt: Compile and run pointer-2.c
:class: bg-primary mb-1
:height: 150px
:align: center
:::
::::


::::{dropdown} Pass by Value and Pass by Reference

- Parameters are passed to functions. 
- Parameters can be value variables or pointer variables. 
- What is the difference?  

::::

::::{dropdown} Hands-on: Pass by value

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `pointer-3.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=pointer-3.c"></script>

- Compile and run `pointer-3.c`

:::{image} fig/02-c/10.png
:alt: Compile and run pointer-3.c
:class: bg-primary mb-1
:height: 150px
:align: center
:::
::::


::::{dropdown} Hands-on: Pass by reference

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `pointer-4.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=pointer-4.c"></script>

- Compile and run `pointer-4.c`

:::{image} fig/02-c/11.png
:alt: Compile and run pointer-4.c
:class: bg-primary mb-1
:height: 450px
:align: center
:::
::::


- In Java, do you pass by value or pass by reference?

:::{dropdown} Answer     
- Primitives are passed by value. 
- Objects are passed by reference. 
:::



## Pointers and memory allocation


- How does C request dynamic memory when you don't know at 
compile-time exactly what you will need?
- How does C allocate memory?
  - Automatic: compile arranges for memory to be allocated 
  and initialized for local variables when it is in scope.
  - Static: memory for static variables are allocated once 
  when program starts.
  - Dynamic: memory is allocated on the fly as needed.

::::{dropdown} Dynamic memory allocation

- Unlike Java, you have to do everything!
  - Ask for memory.
  - Return memory when you are done (garbage collection!).
- C function: [`malloc`](https://linux.die.net/man/3/malloc)
  - `void *malloc(size_t size);`
  - The `malloc()` function allocates `size` bytes and returns 
  a pointer to the allocated memory. The memory is **not initialized**. 
  If size is 0, then `malloc()` returns either `NULL`, or a unique 
  pointer value that can later be successfully passed to `free()`.
- C function: [`free`](https://linux.die.net/man/3/free)
  - void free(void *ptr);
  - The `free()` function frees the memory space pointed to by ptr, 
  which must have been returned by a previous call to `malloc()`, 
  `calloc()` or `realloc()`. Otherwise, or if `free(ptr)` has already 
  been called before, undefined behavior occurs. If `ptr` is `NULL`, 
  no operation is performed.

::::


::::{dropdown} Void pointer

- When `malloc` allocates memory, it returns a sequence of bytes, with
no predefined types. 
- A pointer that points to this sequence of bytes (the address of the 
starting byte), is called a **void pointer**.  
- A void pointer will then be typecast to an appropriate type. 

::::

::::{dropdown} Hands-on: malloc and type cast

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `malloc-1.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=malloc-1.c"></script>

- What points to where:
  - `void *p = malloc(4);`: allocate 4 contiguous bytes. The address of the
  first byte is returned and assign to pointer variable `p`. `p` has no 
  type, so it is a `void pointer`. 
  - `int *ip = (int *)p;`: The address value *pointed to* by `p` is assigned
  to pointer variable `ip`. The bytes pointed to be `p` are now casted to 
  type `int`. 
- Compile and run `malloc-1.c`

:::{image} fig/02-c/12.png
:alt: Compile and run malloc-1.c
:class: bg-primary mb-1
:height: 150px
:align: center
:::
::::

::::{dropdown} Hands-on: malloc and type cast with calculation

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `malloc-2.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=malloc-2.c"></script>

- Only ask for exactly what you need!
- Compile and run `malloc-2.c`

:::{image} fig/02-c/13.png
:alt: Compile and run malloc-2.c
:class: bg-primary mb-1
:height: 150px
:align: center
:::
::::

::::{dropdown} Hands-on: Safety

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `malloc-3.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=malloc-3.c"></script>

- Return and free memory after you are done!
- Compile and run `malloc-3.c`

:::{image} fig/02-c/14.png
:alt: Compile and run malloc-3.c
:class: bg-primary mb-1
:height: 150px
:align: center
:::
::::


::::{dropdown} Dynamic memory allocation

- Critical to support complex data structures that grow as the 
 program executes. 
- In Java, custom classes such as ArrayList and Vector provide 
such support.
- In C, you have to do it manually: How?
- Let’s start with a simpler problem:
  - How can we dynamically allocate memory to an array 
  whose size is not known until during run time?
::::



## Array in C


- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `array-1.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=array-1.c"></script>

- What is the distance between addresses? Why?
- Compile and run `array-1.c`

:::{image} fig/02-c/15.png
:alt: Compile and run array-1.c
:class: bg-primary mb-1
:height: 250px
:align: center
:::

:::::{dropdown} Exercise

- Create a copy of `array-1.c` called `array-2.c`. 
- Change the type of `numbers` to `double`. 
- What is the address step now?

::::{dropdown} Answer    

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=array-2.c"></script>

:::{image} fig/02-c/16.png
:alt: Compile and run array-2.c
:class: bg-primary mb-1
:height: 250px
:align: center
:::
::::
:::::

::::{dropdown} An array variable

- ... is in fact pointing to an address containing a value. 
- ... without the bracket notation and an index points to the 
corresponding address of the value at the index. 
- ... is quite similar to a pointer!
::::

::::{dropdown} Hands-on: Array as pointer (or vice versa ...)

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `array-3.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=array-3.c"></script>

- Compile and run `array-3.c`

:::{image} fig/02-c/17.png
:alt: Compile and run array-3.c
:class: bg-primary mb-1
:height: 250px
:align: center
:::
::::



## Command line arguments.

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `array-4.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=array-4.c"></script>

- In C, the command line arguments **include** the program's name. The
actual arguments start at index position 1 (not 0 like Java).
- Compile and run `array-4.c`

:::{image} fig/02-c/18.png
:alt: Compile and run array-4.c
:class: bg-primary mb-1
:height: 250px
:align: center
:::




## String


- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `string-1.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=string-1.c"></script>

- Compile and run `string-1.c`

:::{image} fig/02-c/19.png
:alt: Compile and run string-1.c
:class: bg-primary mb-1
:height: 150px
:align: center
:::

- In C, string is considered an array of characters.
- How many characters were printed out on the second line in the terminal?
- Hint: Can you see all of them?

:::{dropdown} Answer     
24 
:::

::::{dropdown} Hands-on: Array of strings

- Inside the terminal, make sure that you are still inside
`intro-c`, then use `nano` to create `string-2.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=string-2.c"></script>

- Compile and run `string-2.c`

:::{image} fig/02-c/20.png
:alt: Compile and run string-2.c
:class: bg-primary mb-1
:height: 150px
:align: center
:::
::::





## Object in C


- C has no classes or objects. 
- Instead, it has `struct` type (think ancestor of objects) .

::::{dropdown} Hands-on: Struct in C

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `struct-1.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=struct-1.c"></script>

- Compile and run `struct-1.c`

:::{image} fig/02-c/21.png
:alt: Compile and run struct-1.c
:class: bg-primary mb-1
:height: 150px
:align: center
:::
::::

::::{dropdown} Challenge

- Modify `struct-1.c` so that it prints out the address of `origin` variable. 
- What do you learn from the printed out addresses?

:::{dropdown} Answer     
Insert `printf("The address of the origin is: %p\n", &origin);` between the existing
`printf` calls.  
:::
::::

::::{dropdown} Hands-on: Struct of structs in C

- Inside the terminal, make suse that you are still inside
`intro-c`, then use `nano` to create `struct-2.c`with the source code below. 

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=struct-2.c"></script>

- Compile and run `struct-2.c`

:::{image} fig/02-c/22.png
:alt: Compile and run struct-2.c
:class: bg-primary mb-1
:height: 150px
:align: center
:::
::::




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

