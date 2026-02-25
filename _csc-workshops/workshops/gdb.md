# GDB Debugger

## 1. Introduction

???note In a nutshell

- Developed in 1986 by Richard Stallman at MIT.
- Current official maintainers come from RedHat, AdaCore, and Google.
- Significant contribution from the open source community.

```

???note Brief technical details

- Allows programmers to see inside and interact/modify with all components of a programs,
including information inside the registers.
- Allows programmers to walk through the program step by step, including down to 
instruction level, to debug the program.

```

???note Cheatsheet

- Study this [cheatsheet](https://cs.brown.edu/courses/cs033/docs/guides/gdb.pdf)
- Developed by Dr. Doeppner at Brown University. 
- Become very comfortable with terminal!

```

## 2. tmux

???note Introduction

- Our workspace is limited within the scope of a single terminal (a single shell) 
to interact with the operating system. 
- `tmux`: *terminal multiplexer*. 
- `tmux` allows user to open multiple terminals and organize split-views (panes) 
within these terminals within a single original terminal. 
- We can run/keep track off multiple programs within a single terminal. 

```

???note Beginning with tmux

- SSH into `molly`
- Start new with a session name:

~~~bash
tmux new -s csc231
~~~

:::{image} fig/gdb/01.png
:alt: A new tmux windows
:class: bg-primary mb-1
:height: 600px
:align: center
:::

- You are now in the new tmux session. 
- You can list all active tmux sessions. 

~~~bash
tmux ls
~~~

:::{image} fig/gdb/02.png
:alt: List active tmux sessions
:class: bg-primary mb-1
:height: 600px
:align: center
:::

- **Notation**: Key press combinations connected with a single dash (`-`) means to 
be pressed together, otherwise, it means **lift your finger, then press ...**. 
- To go back to the main terminal, press `Ctrl-b`, then press `d`.

:::{image} fig/gdb/03.png
:alt: Go back to main terminal
:class: bg-primary mb-1
:height: 50px
:align: center
:::

- To go back into the `csc231` session: `tmux attach-session -t csc231`. 

:::{image} fig/gdb/04.png
:alt: Go back to the previous tmux session
:class: bg-primary mb-1
:height: 600px
:align: center
:::

- To kill a session: 
  - From inside the session: `exit`, or
  - From outside the session: `tmux kill-session -t csc231`

- By the end of this slide your should exit out/terminate the `csc231` tmux session. 
- Be careful to not exit out of molly altogether. 
```

???note Hands on: navigating among multiple tmux sessions

- Run `tmux ls` to check and `tmux kill-session` to clean up all existing 
tmux sessions. 
- Create a new session called `s1`. 
- Detach from `s1` and go back to the main terminal. 
- Create a second session called `s2`. 
- Detach from `s2`, go back to the main terminal, and create a third session called `s3`. 
- Use `tmux ls` to view the list of tmux sessions. 
- Navigate back and forth between the three sessions several times. 
- Kill all three sessions using only `exit`!

:::{image} fig/gdb/05.png
:alt: Listing multiple tmux sessions
:class: bg-primary mb-1
:height: 600px
:align: center
:::

```


???note Multiple panes in tmux

- Create a new session called `p1`.

~~~bash
tmux new -s p1
~~~

- Splits terminal into vertical panels: `Ctrl-b` then `Shift-5` (technical documents
often write this as `Ctrl-b` and `%`).

:::{image} fig/gdb/06.png
:alt: Tmux session with two vertical panels
:class: bg-primary mb-1
:height: 600px
:align: center
:::

- Splits terminal (the current pane) into horizontal panels: `Ctrl-b` then `Shift-'` 
( technical documents often write this as `Ctrl-b` and `"`).

:::{image} fig/gdb/01.png
:alt: Tmux sessions with one vertical panel and the other vertical panel splitted into two horizontal panels
:class: bg-primary mb-1
:height: 600px
:align: center
:::

- Toggle between panels: `Ctrl-b` then `Space`.
- To move from one panel to other directionally: `Ctrl-b`then the corresponding 
arrow key. 
- Typing `exit` will close the pane with the activate cursor.  
- Run `exit` multiple times to completely close out the `p1` session. Pay attention 
to not get out of the container. 

```

???note Hands on: creating multiple panes

- Run `tmux ls` to check and `tmux kill-session` to clean up all existing 
tmux sessions. 
- Create a new session called `p1`. 
- Organize `p1` such that: 
  - `p1` has four vertical panes. 
  - The last vertical pane of `p1` has three internal horizontal panes. 
- Kill all panes using `exit`!

:::{image} fig/gdb/08.png
:alt: Tmux with multiple panels
:class: bg-primary mb-1
:height: 600px
:align: center
:::

```


???note Resizing panels

- What we did in the previous hands-on was not quite usable. 
- We need to be able to adjust the panes to the proper sizes. 
- This can be done by issuing additional commands via tmux's command line terminal.
- Run `tmux ls` to check and `tmux kill-session` to clean up all existing 
tmux sessions. 
- Create a new session called `p1`.
- Split the session horizontally.
- Windows:
  - You can adjust the size of two adjacent horizontal panes by **press and hold** `Ctrl-b` then 
the left/right arrows.
  - You can adjust the size of two adjacent vertical panes by **press and hold** `Ctrl-b` then 
the up/down arrows.
- Mac and Windows:
  - Press `Ctrl-b` then `Shift-;` to open up the command line bar at the bottom. Type in:
    - `rezise-pane -U 20` then press `Enter` to move the horitontal bar up 20 pixels
    - `rezise-pane -D 20` then press `Enter` to move the horitontal bar down 20 pixels
    - `rezise-pane -L 20` then press `Enter` to move the vertical bar left 20 pixels
    - `rezise-pane -R 20` then press `Enter` to move the vertical bar right 20 pixels
  - You can adjust the number for aesthetic purpose. 

```



???note Challenge

- Redo the hands-on activity of slide 8 so that all the panes are aesthetically 
proportional. 
- After complete, finish and exit out of all tmux sessions

```


## 3. Running and exiting gdb

???note Setup pretty gdb

- Create a new tmux session called `gdb`. 
- Run the following command in the `gdb` session.

~~~bash
cd 
git clone https://github.com/longld/peda.git
echo "source $HOME/peda/peda.py" > $HOME/.gdbinit
gdb
~~~


- To exit from gdb type `q` and hit `Enter`. 

:::{image} fig/gdb/09.png
:alt: Color-coded gdb
:class: bg-primary mb-1
:height: 600px
:align: center
:::

```

???note Setup an application with gdb

- To use `gdb` to debug, we need to compile the program with a `-g` flag.
- Split the `gdb` session into two **horizontal** panes.
- In the top pane, run the followings command:

~~~bash
cd ~/csc231/intro-c
gcc -g -o hello hello.c
~~~


- In the bottom pane, run the followings command:

~~~
cd ~/intro-c
gdb hello
gdb-peda$ run
~~~

:::{image} fig/gdb/10.png
:alt: Running gdb on hello.c
:class: bg-primary mb-1
:height: 800px
:align: center
:::

```

???note Debugging with gdb

- This is a continue from the previous slide's tmux windows

- We need to set a `breakpoint`:
  - Could be a line number or
  - Could be a function name

~~~bash
gdb-peda$ b main
gdb-peda$ run
~~~

:::{image} fig/gdb/11.png
:alt: Set break points and run
:class: bg-primary mb-1
:height: 800px
:align: center
:::

```


???note Scrolling within tmux's panes

- Mouse scrolling does not work with tmux. 
- To enable scrolling mode in tmux, type `Ctr-b` then `[`. 
- You can use the `Up`/`Down`/`PgUp`/`PgDn` keys to navigate. 
- To quit scrolling mode, type `q` or `Esc`. 

:::{image} fig/gdb/12.png
:alt: Scrolling in tmux
:class: bg-primary mb-1
:height: 800px
:align: center
:::

- At a glance
  - Registers' contents
  - Code
  - Stack contents
  - Assembly codes
- `gdb` stops at our breakpoint, just before function `main`. 
- The last line (before the `gdb-peda$` prompt) indicates the next line of 
C code to be executed. 

```

???note Hands on: finish running hello

- Type `q` or `Esc` to quit scrolling mode. 
- To continue executing the next line of code, type `n` then `Enter`. 
- Turn back into the scrolling mode and scroll back up
to observe what happens after typing `n`. 
- What is the next line of code to be executed?
- Type `n` three more times to observe the line of codes being executed
and the final warning from `gdb`. 
- Type `q` to exit from `gdb`. 

```

???note Examining contents of program while debugging  malloc-1.c

- This slide should start in a two-horizontal-panel tmux session
- Change to the directory containing your `malloc-1.c` that was 
created from the previous lectures. If you don't have it, create a new `malloc-1.c` 
with the code below

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=malloc-1.c"></script>

- In the top pane, compile `malloc-1.c` in debugging mode.

~~~bash
gcc -g -o malloc-1 malloc-1.c
cat -n malloc-1.c
~~~

- Adjust the top/bottom panes proportion as needed. 
- In the bottom pane, quit the current gdb session and 
rerun it on the recently created `malloc-1` executable. 
- Setup `main` as the `breakpoint` and start running. 

~~~bash
gdb malloc-1
gdb-peda$ b main
gdb-peda$ run
~~~

::::{dropdown} After initial run command
:::{image} fig/gdb/malloc-01.png
:alt: After initial run command
:class: bg-primary mb-1
:height: 800px
:align: center
:::
:::: 

- Type `n` and `Enter` to run the next line of code: `int main(int argc, char *argv[]) {`
- Type `p p`: the first `p` is short for `print` and the second `p` is the 
void pointer variable `p` in the program. 
- Try running `p *p`. What does that feedback mean? 

::::{dropdown} After running int main(int argc, char *argv[]) {
:::{image} fig/gdb/malloc-02.png
:alt: After running int main(int argc, char *argv[]) {
:class: bg-primary mb-1
:height: 800px
:align: center
:::
::::

- Type `n` and `Enter` to run the next line of code: `void *p = malloc(4);`
- Type `p p` then `p *p` again. 
  - Why do we have the change in value of `p`?
  - Why doesn't value of `*p` change?

::::{dropdown} After running void *p = malloc(4);
:::{image} fig/gdb/malloc-02.png
:alt: After running void *p = malloc(4);
:class: bg-primary mb-1
:height: 800px
:align: center
:::
::::

- Type `n` and `Enter` to run the next line of code: `int *ip = (int *)p;`
- Type `p ip`: what is the printed value?
- Type `p *ip`: what is the printed value?
- Type `p /t *ip`: what type of data is value? what is the corresponding value in 
decimal?

::::{dropdown} After running int *ip = (int *)p;
:::{image} fig/gdb/malloc-03.png
:alt: After running int *ip = (int *)p;
:class: bg-primary mb-1
:height: 800px
:align: center
:::
::::

- Type `n` and `Enter` to run the next line of code: `*ip = 98765;`
- Type `p ip`: what is the printed value?
- Type `p *ip`: what is the printed value?
- Type `p /t *ip`: what type of data is value? what is the corresponding value in 
decimal?

::::{dropdown} After running *ip = 98765;
:::{image} fig/gdb/malloc-04.png
:alt: After running *ip = 98765;
:class: bg-primary mb-1
:height: 800px
:align: center
:::
::::

- Keep hitting `n` until you finish stepping through all the remain lines of code. 

::::{dropdown} After finish 
:::{image} fig/gdb/malloc-05.png
:alt: After finish
:class: bg-primary mb-1
:height: 800px
:align: center
:::
::::

```


???note Examining contents of program while debugging array-4.c

- In the top pane, compile `array-4.c` in debugging mode. 

~~~bash
gcc -g -o array-4 array-4.c
cat -n array-4.c
~~~


- In the bottom pane, quit the current gdb session and 
rerun it on the recently created `array-4` executable as follows: 

~~~bash
gdb array-4
gdb-peda$ b main
gdb-peda$ run
~~~

::::{dropdown} After initial run command
:::{image} fig/gdb/array-01.png
:alt: After initial run command
:class: bg-primary mb-1
:height: 800px
:align: center
:::
:::: 

- The next line of code to be run is `int main(int argc, char *argv[]) {`
- Type `n` and `Enter` to run the next line of code: `int main(int argc, char *argv[]) {`
- Run the following commands and observe the outcomes: 
  - `p argc` 
  - `p argv[0]` 
  - `p argv[1]` 
  - `p argv[2]`
  - `p argv[3]` 
  - `p argv[4]` 
  - ...

::::{dropdown} After running int main(int argc, char *argv[]) {
:::{image} fig/gdb/array-02.png
:alt: After running int main(int argc, char *argv[]) {
:class: bg-primary mb-1
:height: 800px
:align: center
:::
:::: 

- Type `n` and `Enter` to run the next line of code: `size = atoi(argv[1]);`
- Observe that dreaded `Segmentation fault` notice: `SIGSEGV` 
- Type `q` to exit `gdb`.

::::{dropdown} After running size = atoi(argv[1]);
:::{image} fig/gdb/array-03.png
:alt: After running size = atoi(argv[1]);
:class: bg-primary mb-1
:height: 800px
:align: center
:::
:::: 

- Rerun gdb on `array_4` executable as follows: 

~~~
gdb array-4
gdb-peda$ b main
gdb-peda$ run 3
~~~

::::{dropdown} After initial run command
:::{image} fig/gdb/array-04.png
:alt: After initial run command
:class: bg-primary mb-1
:height: 800px
:align: center
:::
:::: 


- The next line of code to be run is `int main(int argc, char *argv[]) {`
- Type `n` and `Enter` to run the next line of code: `int main(int argc, char *argv[]) {`
- Run the following commands and observe the outcomes: 
  - `p argc` 
  - `p argv[0]` 
  - `p argv[1]` 
  - `p argv[2]`
  - `p argv[3]`
  - ...

::::{dropdown} After running int main(int argc, char *argv[]) {
:::{image} fig/gdb/array-05.png
:alt: After running int main(int argc, char *argv[]) {
:class: bg-primary mb-1
:height: 800px
:align: center
:::
:::: 

- Type `n` and `Enter` to run the next line of code: `size = atoi(argv[1]);`
- Run the following commands and observe the outcomes: 
  - `p size` 
  - `p &size`

::::{dropdown} After running size = atoi(argv[1]);
:::{image} fig/gdb/array-06.png
:alt: After running size = atoi(argv[1]);
:class: bg-primary mb-1
:height: 800px
:align: center
:::
:::: 


```

???note Hands on: finish running array-4

- Use `n` to run the next two lines (`printf...` and `malloc..`).
- Step through the `for` loop and printing out values of `i`, `p[i]`, `&p[i]`, 
and `p + i` at every iteration. 
- Make sure that you understand the lines of code that cause these variables to 
change value.
- Utilize scrolling as needed. 

```

