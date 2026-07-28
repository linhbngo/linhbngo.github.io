---
layout: lecture
pretty_table: true
collection: csc331

title: "Introduction to xv6"
toc:
  - name: The need for a real OS  
  - name: More about xv6
---

## The need for a real OS

- OSTEP textbook gave us concepts: processes, memory, files, concurrency
    - How these are actually implemented?
- Actual OSes are too complex
    - xv6, operating system for teaching.

{% details What is xv6? %}

- [Educational reimplementation of Unix V6 by MIT](https://github.com/mit-pdos/xv6-riscv)
    - For this class, we will use [a fork of the MIT repository](https://github.com/ngo-classes/xv6-riscv.git) (so that the repository's content is frozen through the semester)
- MIT Operating System Engineering: 6.1810
- Approximately 10K lines of C and Assembly
- Clean, modular, readable
- No user-facing features — only a minimal shell and kernel

{% enddetails %}


{% details History of xv6 %}

- The original Unix Version 6, one of the first OS written using C, ran on PDP-11, a 16-bit minicomputer.
    - processes, system calls, pipes, files,..
- xv6 attempts to cover same foundational concepts as Unix V6. 
    - First developed on 32-bit x86 architecture in 2006. 
- Overtime, x86 became bloated.
    - Legacy support (real mode, segmented memory)
    - Complex bootstrapping
    - Modern system no longer supports x86
        - Not by default, had to install from custom libraries
        - Rocky Linux 10 drops completely. 
- In 2020
    - MIT ported xv6 to RISC-V architecture
    - Open source alternative to x86 and ARM

{% enddetails %}


## More about xv6 

{% details Why RISC-V? %}

| Aspect     | x86.           | RISC-V              |
| ---------- | -------------- | ------------------- |
| Complexity | Very high      | Low                 |
| Openness	 | NDA-heavy	    | Fully open          |
| Toolchain	 | Aging (32-bit) |	Actively maintained |

- Other attributes of RISC-V
    - Well-documented (due to open source nature)
    - Modern and gaining traction from academia and industry
- RISC-V in industry
    - [SiFive Chip](https://www.sifive.com/)
    - [Espressif Systems for Internet of Things](https://www.espressif.com/)
    - [Tenstorrent: AI inference with RISC V](https://tenstorrent.com/en/ip/risc-v-cpu)
    - [Google OpenTitan: Silicon Root of Trust with RISC V](https://opentitan.org/)
    - ...

{% enddetails %}


{% details What are we actually running? %}

- xv6-riscv runs on a RISC-V CPU, which was emulated by Qemu, which was setup inside a Ubuntu 24:04 container. 
- More specifics:
    - [Qemu](https://www.qemu.org/), a machine emulator, starts the simulation of a tiny computer using RISC-V architecture. 
    - This computer loads an operating system from scratch, not Linux, but xv6.
    - Once finished loading, xv6 gives you a simple shell, a place to type and run commands like ls, echo, and cat.

{% enddetails %}

{% details Hands-on %}

- Open a terminal into your container. This can be done by either launch the terminal tab inside your Code browser, or SSH into the container. 

```bash
docker exec -u student -it csc331 /bin/bash #if SSH into container
cd /workspace
git clone https://github.com/ngo-classes/xv6-riscv.gitc
cd xv6-riscv
make
make qemu
```

- You will be booted into the xv6's shell, as seen below.

{% include figure.liquid path="assets/img/courses/csc331/02-xv6/01.png" max-width="50%" zoomable=true %}

- Run the following commands inside the xv6's shell

```bash 
echo hello
cat README
ls
ps
uptime
```

{% enddetails %}

{% details What are the outcomes of the above commands? %}

- `echo hello` produces `hello`.
- `cat README` prints out the content of the README file.
- `ls` shows the content of the root directory, which are a list of files/commands.
- `ps` and `uptime` failed to run, as you can see they are not available in the `/` directory.

{% enddetails %}

- To quit qemu, first press `Ctrl-A` then `X`.

{% details Default xv6 commands %}

| Command   | Purpose                          |
| --------- | -------------------------------- |
| ls	    | List files in current directory  |
| cat	    | Print contents of a file         | 
| echo      | Print arguments to stdout        |
| sh	    | The xv6 shell                    |
| init	    | First user-space process         |
| kill	    | Kill a process by PID            |
| sleep	    | Sleep for a number of ticks      |
| forktest	| Test process creation limits     |    
| zombie	| Test zombie process behavior     |
| stressfs	| Stress-test file system          |
| usertests | Runs test suite for xv6 syscalls |

{% enddetails %}
