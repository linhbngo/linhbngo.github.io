---
layout: lecture
pretty_table: true
collection: csc302

title: "Operating System Security"
toc:
  - name: Overview
  - name: Privileged Program
  - name: "Set UID: what can go wrong?"
---

# Operating System Security

## Overview

{% details Roadmap %}



{% enddetails %}
- Process security
- Memory and filesystem security
- Application software security


{% details Process Security %}



{% enddetails %}
- It is essential to monitor and protect the processes that 
are running on that computer
- Inductive trust from start to finish


{% details Memory and Filesystem Security %}



{% enddetails %}
- The contents of a computer are encapsulated in its memory 
and filesystem. 
- Protection of a computer’s content has to start with the 
protection of its memory and its filesystem.
  - Virtual memory security
  - Access control and advanced file permissions
  - File descriptors

```

## Privileged Program

{% details Overview %}



{% enddetails %}
- A program that is executable by users
  - carries elevated (administrative) power
- Example: `passwd`
  - In Linux, passwords are stored in `/etc/shadow`
  - Users need to be provided indirect access to modify 
  their passwords. 


{% details Two-tiered access control design %}



{% enddetails %}
- Daemon (background processes) launched by privileged user ID (`root`).
- Utilize `Set-UID` mechanism of Linux to mark a program is privileged.
  - Meaning that the program is owned by root but executable by users.
  - Grant privilege to the task (process), not the user (using effective user ID)

{% include figure.liquid path="assets/img/courses/csc302/os-security/01.png" max-width="50%" zoomable=true alt="Two-tiered access control" %}


{% details Hands-on: Set UID %}



{% enddetails %}
```bash

id
which id
cp /usr/bin/id ./myid
ls -l ./myid
sudo chown root myid
./myid
sudo chmod 4755 myid
./myid

```

- We want to use `cat` to view `/etc/shadow` as a normal user. 

```bash

cat /etc/shadow

```

- Standard execution is not possible. We need more privileges

```bash

cp $(which cat) ./mycat
sudo chown root mycat
sudo chmod 4755 mycat
./mycat /etc/shadow 

```

- `cp $(which cat) ./mycat`: Create a copy of `cat` called `mycat`
- `sudo chown root mycat`: Set the owner of `mycat` to be `root`
- `sudo chmod 4755 mycat`: This is a setuid mechanism - run `mycat` as its owner, 
not as the user. 

```

## Set UID: what can go wrong?

{% details Attack surface of Set UID %}



{% enddetails %}
{% include figure.liquid path="assets/img/courses/csc302/os-security/02.png" max-width="50%" zoomable=true alt="Attack surfaces of Set UID" %}

- User inputs (explicit inputs): Failure of input sanitization
  - Buffer overflow
  - SQL injection
- System inputs: System-provided inputs that were faked by other users
  - Race condition
- Environment variables: inputs that can be manipulated by others
- Non-privileged process: capability leaking



{% details Hands-on: Capability leaking %}



{% enddetails %}
- Creates a file called `/etc/zzz`. You will need to use `sudo` 
to create this file with the following content:
  - `This is quality content!`
- A normal user cannot attempt to edit this file. 

```bash

ls -l /etc/zzz
cat /etc/zzz
echo 'insert bad data' >> /etc/zzz

```

- Make a copy of a file `cap_leak.c` into `seed` directory. 

```bash

gcc -w -o cap_leak /local/repository/setup_scripts/software/setuid/cap_leak.c
sudo chown root cap_leak
sudo chmod 4755 cap_leak
ls -l cap_leak

```

- How about now?

```bash

./cap_leak
echo 'insert bad data' >&3
exit
cat /etc/zzz

```


{% details Hands-on: Questions ... %}



{% enddetails %}
- What just happened?
- Why did it happen?


{% details Real-world scenarios %}



{% enddetails %}
- [OSX 10.10 DYLD_PRINT_TO_FILE Local Privilege Escalation Vulnerability](https://www.sektioneins.de/en/blog/15-07-07-dyld_print_to_file_lpe.html)
- [How does the DYLD privilege escalation vulnerability work on OSX](https://security.stackexchange.com/questions/94640/how-does-the-dyld-privilege-escalation-vulnerability-work-on-os-x)


{% details A more serious case of capability leaking %}



{% enddetails %}
- [What does system() do?](http://man7.org/linux/man-pages/man3/system.3.html)
- Switch shell (**CAREFUL!!!**)

```bash

ls -l /bin/sh
sudo rm /bin/sh
sudo ln -s /bin/zsh /bin/sh
ls -l /bin/sh

```

- Make a copy of a file `catall.c` into `seed` directory. 

```bash

gcc -w -o catall /local/repository/setup_scripts/software/setuid/catall.c
sudo chown root catall
sudo chmod 4755 catall
ls -l catall

```

- Normal operation
  - `cat` cannot access `/etc/shadow`
  - But `cat` called from `catall` with elevated 
  privilege can access `/etc/shadow`

```bash

cat /etc/shadow
./catall /etc/shadow

```

- Bad stuff!!!
  - What just happened?
  - Why?
  - what is the security implication?
- Make a copy of `catall.c`, modify the file to comment out line 22 
and uncomment line 23. 
  - Instead of using `system`, use `execve`. 
- Vulnerability is gone, why?
  - [system](https://man7.org/linux/man-pages/man3/system.3.html)
  - [execve](https://man7.org/linux/man-pages/man2/execve.2.html)
- Very carefully, switch `/bin/sh` back to `/bin/dash`

```bash

ls -l /bin/sh
sudo rm /bin/sh
sudo ln -s /bin/dash /bin/sh
ls -l /bin/sh

```

- [Dash bug](https://bugs.launchpad.net/ubuntu/+source/dash/+bug/1215660)
- [Bash correction](https://unix.stackexchange.com/questions/451048/from-which-version-does-bash-drop-privileges)


{% details Security lessons %}



{% enddetails %}
- Principle of least privilege
- Principle of Data/code isolation
- Keep things updated (or be aware when things could not be updated)!

```
