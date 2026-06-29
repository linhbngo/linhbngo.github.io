---
layout: lecture
pretty_table: true
collection: csc302

title: "Environmen Variables"
toc:
  - name: Technical overview
  - name: Attack surface caused by environment variables
---

# Environmen Variables


## Technical overview

{% details Overview %}



{% enddetails %}
- Environment variables (EV) are a set of dynamic name-value pairs stored inside a process. 
  - Can affect a process's behaviors. 
  - Example: The `PATH` environment varible provides a list of diectories where executable 
  programs are stored. When a shell executes a program, it uses this EV to find where the 
  program is if the full path is not provided. 

```bash

echo "Hello World"
mkdir test
cp $(which echo) test/myecho
myecho "Hello World"
echo $PATH
export PATH=$PATH:/home/seed/test
echo $PATH
myecho "Hello World"

```


{% details Accessing EV from a process %}



{% enddetails %}
- Two approaches for C programs
  - A third argument can be passed to the `main` function. 
  This argument will contain the environment variables. 
  - A global variable that points to the environment array called 
  `environ`. 


:::::{tab-set}
::::{tab-item} envp

```bash

gcc -w -o my_envp /local/repository/setup_scripts/software/env/my_envp.c
./my_envp

```

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=my_envp.c"></script>

::::
::::{tab-item} environ

```bash

gcc -w -o my_environ /local/repository/setup_scripts/software/env/my_environ.c
./my_environ

```

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=my_environ.c"></script>


::::
:::::


{% details How a process get its EV %}



{% enddetails %}
- A process is created through two ways
  - Via `fork()` system call 
  - Via `execve()` system call
- Process created via `fork()`:
  - A child process is a duplicate of the parent's memory
  - All EV are inherited
- Process created via `execve()`:
  - The copy of parent's memory for the child is overwritten
  - EV need to be specifically passed. 

```bash

gcc -w -o passenv /local/repository/setup_scripts/software/env/passenv.c
./passenv
./passenv 1
./passenv 2
./passenv 3

```

<script src="https://gist.github.com/linhbngo/a583a6912f26fb77b67c835933f76dce.js?file=passenv.c"></script>


{% details Where the wild things are %}



{% enddetails %}
{% include figure.liquid path="assets/img/courses/csc302/env/env_memory.png" width="50%" zoomable=true alt="Memory placement of environment variables in process" %}

- Recompile `my_envp.c` with GDB flag and check the 
location of the environment variables

```bash

gcc -g -o my_envp_gdb my_envp.c
gdb my_envp_gdb
gdb-peda$ b main
gdb-peda$ run
gdb-peda$ n
gdb-peda$ p argv
gdb-peda$ p envp
gdb-peda$ x/s *((char **)envp + 1)

```



{% details Shell variables and EV %}



{% enddetails %}
- Are not the same thing
- Different but related concepts
- Shell is a command line interface for users to interact with an 
operating system (Linux)
  - Shell variables are internal variables maintained by a shell program
  - User can create, assign, and delete shell variables
- Environment variables can become shell variables and vice versa
  - The shell defines a shell variable for each environment variable of 
  the process (the shell process)
  - Same name, same value
  - The shell can easily get the value of the environment variables 
  by referring to its own shell variables

```bash

strings /proc/$$/environ | grep LOGNAME
echo $LOGNAME
LOGNAME=ram
echo $LOGNAME
strings /proc/$$/environ | grep LOGNAME

```

{% include figure.liquid path="assets/img/courses/csc302/env/env_shell.png" width="50%" zoomable=true alt="Shell variables" %}

```

## Attack surface caused by environment variables


{% details Overview %}



{% enddetails %}
{% include figure.liquid path="assets/img/courses/csc302/env/attack_surface.png" width="50%" zoomable=true alt="Attack surface caused by environment variables" %}


{% details Attacks via dynAmic linkers and libraries %}



{% enddetails %}
- Linking finds the external library code referenced in the 
program and links the code to the program (think import in Java).
- Linking can be done when a program is compiled
  - Static linking
  - Requires a lot of memory
  - Compiled external functions are static and cannot be updated/patched

```bash

gcc -o my_envp my_envp.c
gcc -static -o my_envp_static my_envp.c
ls -lh my_envp*

```

- Linking can be done on the fly
  - External functions are linked at run time, called `shared libraries`.
  - `.so` on Unix system, `.dll` on Windows system
   - `ldd` can be used to see what shared libraries a program depends on. 

```bash

ldd my_envp_static
ldd my_envp

```


{% details Vulnerabilities via environment variables %}



{% enddetails %}
- Part of what is being executed is undecided during compilation time, when 
the developer has full control.
- Instead, the binaries rely on linked libraries, which are determined during 
runtime, under users' control.
- Examples: **LD_PRELOAD** and **LD_LIBRARY_PATH**
  - During the linking stage, the Linux system search for library 
  functions from default locations.
  - These locations are determined via **LD_PRELOAD** and **LD_LIBRARY_PATH**

```bash

echo $LD_PRELOAD
echo $LD_LIBRARY_PATH
cp /local/repository/setup_scripts/software/env/linking.c .
gcc -o linking linking.c
./linking
cp /local/repository/setup_scripts/software/env/sleep.c .
gcc -c sleep.c
gcc -shared -o libmylib.so.1.0.1 sleep.o
export LD_PRELOAD=./libmylib.so.1.0.1
echo $LD_PRELOAD
./linking
export LD_PRELOAD=""
./linking

```


{% details Countermeasures for EV's dynamic linking %}



{% enddetails %}
- Linux system libraries, `ld.so` or `ld-linux.so`, implement a countermeasure, which 
ignores **LD_PRELOAD** and **LD_LIBRARY_PATH** when there is a difference in a process' real 
and effective user IDs or group IDs.

```bash

cp $(which env) myenv
export LD_PRELOAD=./libmylib.so.1.0.1
export LD_LIBRARY_PATH=.
export LD_MYOWN="my own EV"
env
env | grep LD_
myenv | grep LD_
sudo chown root myenv
sudo chmod 4755 myenv
myenv | grep LD_

```



{% details Vulnerabilities via external program %}



{% enddetails %}
- `PATH` environment variable

```bash

echo $PATH

```

- Many system commands are placed in `/usr/bin` or `/bin`, which are 
mapped in `PATH`

```bash

cp /local/repository/setup_scripts/software/env/vul.c .
gcc -o vul vul.c
./vul
cp /local/repository/setup_scripts/software/env/cal.c .
gcc -o cal cal.c
sudo chown root vul
sudo chmod 4755 vul
export PATH=.:$PATH
vul
$ id
$ exit

```

- Open a new terminator shell to reset `PATH` to default. 
- What happens when you switch the order of the new `PATH` 
export for the previous exercise?
- Why?

```bash

cp /local/repository/setup_scripts/software/env/vul.c .
gcc -o vul vul.c
./vul
cp /local/repository/setup_scripts/software/env/cal.c .
gcc -o cal cal.c
sudo chown root vul
sudo chmod 4755 vul
export PATH=$PATH:.
vul
$ id
$ exit

```



{% details Attack via application codes %}



{% enddetails %}
- Happens when application uses environment variables, 
which can be manipulated. 


```bash

cp /local/repository/setup_scripts/software/env/pwd.c .
echo $PWD
gcc -o pwd pwd.c
./pwd
cd /tmp
~/pwd
PWD=randomdir
~/pwd

```



{% details A service-based approach to protect %}



{% enddetails %}
{% include figure.liquid path="assets/img/courses/csc302/env/service_based.png" width="50%" zoomable=true alt="Service-based approach" %}

```

