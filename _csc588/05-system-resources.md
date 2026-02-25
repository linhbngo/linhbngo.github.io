---
layout: lecture
pretty_table: true
collection: csc588
course: CSC 603: Access Control in the Cloud
title: "System Resources"
toc:
  - name: Overview
  - name: Hands-on
---

# System Resources


## Overview

{% details How do we define system resources? %}


{% enddetails %}
- How fine-grained should it be?
  - One cluster of computers
  - One computer
  - One socket
  - One core
  - Portion of times on one core
  - ...
- In a nutshell:
  - What resources do you see: `namespace`
  - What resources can you use: `cgroup`


{% details Namespace %}

{% enddetails %}
- Partitions of kernel resources such that one partition is `viewable` by one 
set of processes but not by another set. 
- Namespace kinds:
  - Mount (mnt): Powerful and flexible tool for creating per-user and per-container filesystem trees
  - Process ID (pid): [Processes in different pid namespaces can have the same pid](https://manpages.ubuntu.com/manpages/xenial/man7/pid_namespaces.7.html)
  - Network (net): [Provide isolation of system resources associated with networking](https://man7.org/linux/man-pages/man7/network_namespaces.7.html)
  - IPC (ipc): [Isolate certain IPC resources and POSIX message queues](https://man7.org/linux/man-pages/man7/ipc_namespaces.7.html)
  - UTS (uts): UTS namespaces allow a single system to appear to have different host and domain names to different processes.
  - User ID (user): [Isolate security-related identifiers and attributes, in particular, user IDs and group IDs, 
  the root directory, keys, and capabilities](https://man7.org/linux/man-pages/man7/user_namespaces.7.html)
  - Control group (cgroup): Will talk about in cgroup.
  - Time: Allow processes to see different system times. 

{% details cgroup (the initial c is never capitalized) %}

{% enddetails %}
- Control groups, usually referred to as cgroups, are a Linux 
kernel feature which allow processes to be organized into 
hierarchical groups whose usage of various types of resources can 
then be limited and monitored. 
- [Man page](https://man7.org/linux/man-pages/man7/cgroups.7.html)
- [Authoritative document on the design, interface, and convention of cgroupv2](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/diff/Documentation/cgroup-v2.txt?id=v4.5&id2=v4.4)
- Features:
  - Resource limiting: memory limit, I/O bandwidth limit, CPU quota limit, or CPU set limit.
  - Prioritization: some groups may get a larger share of CPU utilization or disk I/O throughput.
  - Accounting: measures a group's resource usage.
  - Control: freezing groups of processes, their checkpointing and restarting

```

## Hands-on

{% details Hands-on: cgroup CPU %}

{% enddetails %}
- Instantiate the Docker branch
- Run the following commands

~~~bash
$ sudo apt install -y cgroup-tools
$ sudo cgcreate -g cpu:/cpulimit
~~~

- `cpu.cfs_period_us` and `cpu.cfs_quota.us`: how tasks in a cgroup should 
be able to access a single CPU for `quota` out of `period` microseconds (`us`). 

~~~bash
$ sudo cgset -r cpu.cfs_period_us=1000000 cpulimit
$ sudo cgset -r cpu.cfs_quota_us=10000 cpulimit
$ sudo cgget -g cpu:cpulimit
~~~

- In the above example, tasks in the `cpulimit` group can access 10000 microseconds 
out of 1000000 microseconds of a single CPU time. 
- Create a two-horizontal panes tmux session. Keep the bottom pane running the `top` 
command. 
- For the top pane, run the following commands one by one and observe the CPU usage 
from the `top` pane. 

~~~bash
$ dd if=/dev/zero of=out bs=1M
~~~

and 

~~~bash
$ sudo cgexec -g cpu:cpulimit dd if=/dev/zero of=out bs=1M
~~~

:::{image} ../fig/csc603/06-system-resources/cgroup-cpu-1.png
:alt: Running dd without cgroup
:class: bg-primary mb-1
:height: 300px
:align: center
:::

:::{image} ../fig/csc603/06-system-resources/cgroup-cpu-2.png
:alt: Running dd with cgroup
:class: bg-primary mb-1
:height: 300px
:align: center
:::


{% details Hands-on: cgroup memory %}

{% enddetails %}
- Check the content of the initial memory cgroup

~~~bash
$ sudo ls /sys/fs/cgroup/memory/
~~~

- Create a new memory cgroup called `blue`

~~~bash
$ sudo mkdir /sys/fs/cgroup/memory/blue
$ sudo ls /sys/fs/cgroup/memory/blue
~~~

- Check the initial memory limit

~~~bash
$ cat /sys/fs/cgroup/memory/blue/memory.limit_in_bytes
~~~

- Set the amount of memory for tasks in the `blue` group

~~~bash
$ echo 104857600 | sudo tee /sys/fs/cgroup/memory/blue/memory.limit_in_bytes
$ cat /sys/fs/cgroup/memory/blue/memory.limit_in_bytes
~~~

- Check on `OOM killer` (out-of-memory)

~~~bash
$ sudo su
$ cd /sys/fs/cgroup/memory/blue/
$ cat memory.oom_control
~~~

- Create a memory hog file:

~~~bash
$ nano -l /tmp/memhog.c
~~~

with the following contents:

~~~c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)

int main(int argc, char *argv[]) {
 char *p;

again:
  while ((p = (char *)malloc(GB)))
    memset(p, 0, GB);
  while ((p = (char *)malloc(MB)))
    memset(p, 0, MB);
  while ((p = (char *)malloc(KB)))
    memset(p, 0, KB);
  sleep(1);
  goto again;

  return 0;
}
~~~

- Move the shell into the tasks group of cgroup `blue`: 

~~~bash
$ cat tasks
$ echo $$ > tasks
$ cat tasks
~~~

- Compile and run `memhog` and observe how it is killed:

~~~bash
$ gcc -o /tmp/memhog /tmp/memhog.c
$ /tmp/memhog
~~~

- Turn off the OOM and see how `memhog` hang. 

~~~bash
$ echo 1 > memory.oom_control
$ /tmp/memhog
~~~

- Open a new windows, 
SSH into the CloudLab node, and try to turn the shell into `blue` cgroup. 
You will see that the shell hanged (out of memory)

~~~bash
$ sudo su
$ cd /sys/fs/cgroup/memory/blue/
$ echo $$ >> tasks
~~~

- Open yet another shell and change the `OOM` flag to enable OOM killed. 
You will see that `memhog` is immediately killed once the flag is turned back on.

~~~bash
$ cd /sys/fs/cgroup/memory/blue/
$ cat memory.oom_control
$ echo 0 > memory.oom_control 
~~~

```


