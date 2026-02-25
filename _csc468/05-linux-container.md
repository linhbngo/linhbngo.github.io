---
layout: lecture
pretty_table: true
order: 1
title: The Building Blocks of Containers
mermaid:
  enabled: true
  zoomable: true
code_diff: true
map: true
chart:
  chartjs: true
  echarts: true
  vega_lite: true
tikzjax: true
typograms: true

toc:
  - name: Beyond the Hypervisor
  - name: Setup and Preparation
  - name: Namespaces (Isolation)
  - name: Cgroups (Resource Administration)
  - name: The Filesystem (Chroot)
  - name: Process Isolation (Namespaces)
  - name: "Looking Ahead: Why Docker?"
---

## Beyond the Hypervisor

{% details Recap: The Virtualization Cost %}

- In the previous lecture, we discussed **Hypervisors** (Type 1 & 2) and **VMs**.
- VMs require a full guest OS kernel, which adds overhead (CPU rings, memory mapping).
- **Question:** Can we isolate processes without simulating hardware?
- **Answer:** Yes, by using features built directly into the Linux Kernel.

{% enddetails %}
{% details The Three Pillars of Containerization %}

- **Namespaces:** What a process can *see* (Isolation).
- **Cgroups (Control Groups):** What a process can *use* (Resource Limiting).
- **Chroot/Pivot_root:** Where the process thinks *root* (/) is (Filesystem Isolation).
- *Docker is essentially a fancy wrapper around these three Linux primitives.*

{% enddetails %}
---

## Setup and Preparation

{% details Environment Setup %}

- **Platform:** CloudLab.
- Launch from the `main` branch of your CloudLab class profile. 
- **Goal:** We will create a "container" without using Docker, using only Linux kernel primitives.

{% enddetails %}
{% details Install Dependencies %}

- We need tools to manage control groups and simulate load.
- SSH into your CloudLab node.
- Run the following:

~~~bash
sudo apt update
sudo apt install -y cgroup-tools stress debootstrap
~~~

{% enddetails %}
---

## Namespaces (Isolation)

{% details Overview %}

- Namespaces wrap a global system resource in an abstraction.
- To the processes within the namespace, it appears they have their own isolated instance of the global resource.
- Common Namespaces:
    - **PID:** Process IDs (Process 1 inside container vs Process 1234 on host).
    - **MNT:** Mount points and filesystems.
    - **NET:** Network interfaces, stacks, ports.
    - **UTS:** Hostname and domain name.

{% enddetails %}
{% details Hands-on: The PID Namespace %}

- **Goal:** Create a shell that thinks it is PID 1 (like a container).
- Open your CloudLab terminal.
- Check your current PID:

~~~bash
echo $$
~~~

- Use `unshare` to create a new PID namespace and fork a bash process:

~~~bash
sudo unshare --fork --pid --mount-proc bash
~~~

- Check the PID inside this new environment:

~~~bash
echo $$
ps aux
~~~

- *Observation:* You should see only a few processes, and your bash shell should be PID 1.
- Type `exit` once to return to the host and test pid again.

~~~bash
exit
echo $$
~~~

{% enddetails %}
---

## Cgroups (Resource Administration)

{% details Overview %}

- While Namespaces hide resources, **Control Groups (cgroups)** limit them.
- Originally developed by Google (started as "Process Containers").
- Organized in a hierarchy (tree structure) located at `/sys/fs/cgroup`.
- Controls: Memory limits, CPU quotas, I/O throttling.

{% enddetails %}
{% details Hands-on: Manually Creating a Cgroup %}

- **Goal:** Create a "jail" that limits a process to 100MB of RAM.
- Create a new cgroup called `mygroup`:

~~~bash
sudo cgcreate -g memory:mygroup
~~~

- Set the limit to 100MB (in bytes):

~~~bash
# 100MB = 104857600 bytes
echo 104857600 | sudo tee /sys/fs/cgroup/mygroup/memory.max
~~~

{% enddetails %}
{% details Hands-on: Testing the Limit %}


- Run a `stress` test inside that cgroup that tries to eat 99MB of RAM.
    - You will need to use `Ctrl-C` to terminate the running process

~~~bash
sudo cgexec -g memory:mygroup stress --vm 1 --vm-bytes 99M --vm-keep
~~~

- Run a `stress` test inside that cgroup that tries to eat 101MB of RAM.

~~~bash
sudo cgexec -g memory:mygroup stress --vm 1 --vm-bytes 101M --vm-keep
~~~

- *Observation:* The process should fail or be killed by the OOM (Out of Memory) Killer immediately.
- Compare this to running it without the cgroup (which would succeed).

{% enddetails %}
---

## The Filesystem (Chroot)

{% details Overview %}

- How do containers have different files than the host (e.g., Ubuntu container on CentOS host)?
- They change the "root" directory via `chroot`.
- Docker uses advanced "Copy-on-Write" filesystems (OverlayFS), but `chroot` is the ancestor concept.

{% enddetails %}
{% details Hands-on: Building a 'Container' from Scratch %}

- **Goal:** Create a mini-filesystem and lock a process inside it.
- Create a folder for our new root:

~~~bash
mkdir container
~~~

- Use debootstrap to setup a base file system inside:

~~~bash
sudo debootstrap --variant=minbase stable /users/$USER/container http://deb.debian.org/debian
~~~

- Mount essential virtual filesystems

~~~bash
for dir in dev proc sys; do sudo mount --bind /$dir /users/$USER/container/$dir; done
~~~

- Enter the isolated file system jail:

~~~bash
sudo unshare --mount --uts --ipc --pid --fork chroot /users/$USER/container /bin/bash
~~~

- Try to look at `/home` or `/users`. They don't exist here! You are isolated.
- Exit out of the container when done

~~~bash
exit
~~~

{% enddetails %}
---

## Process Isolation (Namespaces)

{% details Concept: PID Namespace %}

- Even inside `chroot`, if we mounted `/proc`, we would see all the host's processes.
- We need a **PID Namespace** to hide the host processes.

{% enddetails %}
{% details Step 1: Unshare and isolate %}

- We will use `unshare` to create a new namespace, then immediately `chroot` into our folder.

~~~bash
sudo unshare --mount --uts --ipc --pid --fork chroot container /bin/bash
~~~

- Next, we install `ps` and setup a separate mount point for `/proc` from inside the container

~~~bash
apt update
apt install -y procps
~~~

{% enddetails %}
{% details Step 2: Verify Isolation %}

- Run `ps aux` inside the container.
- **Observation:** You should see your `bash` process as **PID 1**.
- On the host, this process might be PID 12345, but inside the namespace, it is PID 1.
- This is exactly how Docker containers perceive themselves as the only thing running on the machine.
- Type `exit` to return to the host.

{% enddetails %}
---

## Looking Ahead: Why Docker?

{% details The Administration Nightmare %}

- Imagine doing the steps above for *every* single application you deploy.
- Manual cgroup math, manual dependency copying, manual network bridging.
- **Docker** is a daemon that automates:
    - Creating Namespaces.
    - Configuring Cgroups.
    - Managing Filesystems.
- Next lecture, we will see how `docker run` replaces all these manual commands.

{% enddetails %}
---
