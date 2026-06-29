---
layout: lecture
pretty_table: true
order: 1
title: Docker Storage
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
  - name: Overview
  - name: The Linux Storage Model
  - name: Docker Storage
  - name: Hands-on
---

## Overview

{% details Why does storage matter? %}


- Applications (and supporting libraries) are packaged inside container images.
- Running containers are instants of these images
    - Will eventually be removed.
    - Modifications will be lost if not committed into a new image.
- This has implications on the application: stateless or stateful?

{% enddetails %}

{% details Stateless applications %}


- Do not retain any client or session data beyond the request/response cycle
    - All requests/responses are independent from one another
    - No historical knowledge is necessary
    - Have no dependency on persistent storage
    - Can be easily scaled by adding more containers
    - Will not loose critical data if containers are properly stopped/restarted
- Examples: web servers, REST APIs

{% enddetails %}
{% details Stateful applications %}


- Retain data across multiple interactions or previous session information
    - Require persistent storage
    - If containers are stopped or restarted, there are risk of loosing critical data
    - Scaling can be complex
- Examples: databases, message queues

{% enddetails %}
- Depending on application architectures, a persistent storage solution from Docker is needed.

---

## The Linux Storage Model

{% details The Virtual File System (VFS) %}

- In Linux, `Everything is a file`, but 
    - not all files are on disks.
- The [**VFS (Virtual File System)**](https://docs.kernel.org/filesystems/vfs.html) is a kernel layer that abstracts physical storage.
- It allows the kernel to treat a physical disk, a network share, and a memory block (`tmpfs`) identically.
- Docker does not "create" storage; it manipulates the **Mount Namespace** to map VFS pointers.

{% enddetails %}
{% details Inodes: The Reality of Files %}

- A filename (e.g., `/app/data.txt`) is just a human-readable label.
- The actual data is referenced by an **Inode (Index Node)**, which contains metadata (permissions, owner) and pointers to disk blocks.
- If two filenames point to the same Inode, they are the *same physical file*.

{% enddetails %}
{% details The mechanics of linking: Hard vs. Soft Links %}

- Before understanding Docker Volumes, we must understand how Linux handles file references.
- **Hard Link:** A second filename pointing to the *same* Inode number.
    - All hard links are equal; there is no "original."
    - The data is deleted only when the last link to the Inode is removed.
- **Soft (Symbolic) Link:** A file that points to another *path*.
    - Has its own unique Inode.
    - If the target path is deleted, the link becomes "broken."

{% enddetails %}
{% details Hands-on: Proving Links in Linux %}

- **Step 1: Create Data**

```bash
echo "Important Data" > original.txt
```

- **Step 2: Create Links**

```bash
# Create a Hard Link (Direct reference to inode)
ln original.txt hard.txt
# Create a Soft Link (Reference to path)
ln -s original.txt soft.txt
```

- **Step 3: Forensic Inspection**

```bash
ls -li *.txt
```

- **Observation:**
    - Look at the first column (Inode Number). `original.txt` and `hard.txt` have the **identical number**.
    - Look at `soft.txt`. It has a different number, and explicitly points `-> original.txt`.
- **Step 4: The Persistence Test**
```bash
rm original.txt
cat hard.txt   # SUCCEEDS: Data still exists because Inode ref count > 0
cat soft.txt   # FAILS: "No such file or directory"
```


{% enddetails %}
{% details Connection to Docker %}

- Docker storage options utilize these kernel linking concepts across namespaces.
- **Key Takeaway:** The persistence nature of data depends on the mounting mechanism used.

{% enddetails %}
---

## Docker Storage

{% details Docker Storage Concepts %}

- Multiple layers
    - Read-only and writable layers for containers and their images. 
- OverlayFS
    - Based on UnionFS
- Have three types:
    - Volumes
    - Bind mounts
    - Tmpfs mounts

{% details The Persistence Model %}

- Data persists on the disk as long as the **Inode Reference Count > 0**.
- We can classify Docker storage types by who holds the **"Anchor"** (the primary link to the Inode).

{% enddetails %}
{% details Case A: Bind Mounts (The User Anchor) %}

- **Mechanism:** You explicitly link a directory on your Host (`/home/user/data`) to the Container (`/app`).
- **The Anchor:** The **Host Operating System** holds the primary reference.
- **Lifecycle:** Even if Docker removes the container's reference, the data persists because the User/Host OS still holds the "Anchor."

{% enddetails %}
{% details Case B: Docker Volumes (The Managed Anchor) %}

- **Mechanism:** Docker creates a directory in its own protected area (`/var/lib/docker/volumes/`).
- **The Anchor:** The **Docker Daemon** holds the primary reference.
- **Lifecycle:** Even if the container is deleted, the data persists because the Docker Daemon maintains the Volume object separate from the container's lifecycle.

{% enddetails %}
{% details Case C: Container Root (The Ephemeral Link) %}

- **Mechanism:** The container writes to the UpperDir of the OverlayFS.
- **The Anchor:** The **Container Process** itself is the *only* entity holding a reference to this specific layer.
- **Lifecycle:** When the container dies, the Inode reference count drops to zero. The data is garbage collected (deleted).

{% enddetails %}
{% enddetails %}
{% details Union file systems %}

- "Combines the namespaces of two or more file systems to produce a 
single merged namespace" - Valerie Aurora, LWN 2009. 
    - A real-only file system with an writable overlay on top
- The overlay store changes and allow arbitrary manipulation of 
  the combined namespace
    - `whiteout` items from the read-only layer if they are modified 
    in the writable layer. 
- Docker uses OverlayFS, an implementation of a union file system
- Run `docker info` and identify your Docker's `Storage Driver`

{% enddetails %}
{% details The Architecture of Overlay2 %}

- Docker uses the `overlay2` storage driver by default.
- It constructs the container's root filesystem using four directories:
    1.  **LowerDir:** Read-only Image layers.
    2.  **UpperDir:** The read-write layer (where the container writes).
    3.  **WorkDir:** Internal directory for atomicity.
    4.  **MergedDir:** The unified view the container sees.

{% enddetails %}
{% details Container storage %}

- `Layered storage`: Each Docker image is built from multiple layers
- `Read-only base layers`: Image layers are immutable and shared between 
containers.
- `Writable container layer`: Any changes made in a running container occur in this topmost layer.
- `Copy-on-Write (CoW)`: When a file in a lower layer is modified, it is copied to the writable layer.
- Example: [linhbngo/csc331:19.05](https://hub.docker.com/repository/docker/linhbngo/csc331/tags/19.05/sha256:4291c9b4d395ec2627972425d6dee75e4627be91d1cf34810a6054da0bbe1776)


{% details The Engineering Cost of Copy-on-Write (CoW) %}

- **The Scenario:** A container tries to modify a 1GB file that exists in the Image (`LowerDir`).
- **The Mechanics:**
    1.  **Trap:** The kernel intercepts the write attempt.
    2.  **Pause:** The writing process is blocked.
    3.  **Copy:** The kernel copies the *entire* 1GB file from `LowerDir` up to `UpperDir`.
    4.  **Write:** The process is unblocked and writes to the copy in `UpperDir`.
- **The Consequence:** This introduces massive **I/O Latency**.
- **Engineering Principle:** NEVER put high-write workloads (like Databases) on the Container Root. Always use Volumes to bypass OverlayFS.


{% enddetails %}
{% enddetails %}
{% details Volume and Bind Mounts %}


{% details The `mount --bind` Syscall %}

- Both **Volumes** and **Bind Mounts** bypass the slow OverlayFS driver.
- They function by injecting a VFS pointer directly into the container's Mount Namespace.
- **Performance:** Zero overhead. Reads/Writes happen at native disk speed.

{% enddetails %}
{% details Engineering Distinction: Volume vs. Bind Mount %}

- **Bind Mount:** User can specify the host Inode location (e.g., `/home/user/project`).
    - *Use Case:* Development (Source code edits reflect instantly).
- **Volume:** Docker controls the host Inode location.
    - *Use Case:* Production & Ops. Docker handles permissions, migrations, and drivers.

{% enddetails %}
{% details Docker Volume %}

- A **persistent storage mechanism** that allows data to be stored outside of a container's filesystem. 
    - This allows data to be retained after the containers are stopped or restarted.

- Run the following commands to create and inspect a new volume

```bash
docker volume create myrepo
docker volume ls
docker volume inspect myrepo
```

{% include figure.liquid path="assets/img/courses/csc468/docker-volume/volume-create.png" width="50%" zoomable=true %}

- Create two containers called `point1` and `point2` in interactive mode
- Container `point1` is an alpine container and will mount `myrepo` as directory `/point1`
    - The flag `v` represents the mount of the volume `myrepo` to `/point1`.

```bash
docker run -it --name point1 -v myrepo:/point1 alpine sh
```
- Create a directory called `the_ram_was_here` inside `/point1`.
- Container `point2` is an alpine container and will mount `myrepo` as directory `/point2`

```bash
docker run -it --name point2 -v myrepo:/point2 ubuntu sh
```

- Check that `the_ram_was_here` exists inside `/point2`

{% enddetails %}
{% details Bind Mounts %}

- Allow the mounting of a specific directory from the host into a container.
- Files created inside the container appear immediately on the host machine, and vice versa.
- The directory must exist on the host before the container starts. 
    - We are still using the `v` flag, but the part in front of the `:` should now point to a 
    directory. 

- Create a new directory called `my_host_repo` in the current directory.
- Use the `realpath` command to get the full path to `my_host_repo` (Linux/Mac only). 
- Launch an interactive container with the `alpine` image and mount the new directory to a 
directory called `/from_host` using the `v` flag. 
    - The host directory path must be the full path!
    - Create some test contents inside `/from_host`
    - Exit the running container. 

```bash
mkdir my_host_repo
realpath my_host_repo
docker run -it -v /Users/lngo/my_host_repo:/from_host alpine sh
cd /from_host
touch test
exit
```

- Check that test is now created in the `my_host_repo` directory. 
- Launch an interactive container with the `ubuntu` image and mount the new directory to a 
directory called `/from_host` using the `v` flag. 
    - The host directory path must be the full path!
    - Check that `/from_host` directory also contains the test file. 

```bash
docker run -it -v /Users/lngo/my_host_repo:/from_host alpine sh
cd /from_host
ls
exit
```

{% enddetails %}
{% details Tmpfs Mounts %}

- **temporary in-memory filesystem** that does not write data to disk, but to memory directly. 
- **OS Concept:** This utilizes the Linux Virtual Memory manager.
- **Security Theory:** Data is stored in Pages (RAM). If the host loses power, data vanishes. It is never flushed to the physical disk platter, making it ideal for **secrets**.
- Fast ephemeral storage will go away once the container stops. 
- Run an interactive shell with a tmpfs mount using the following command.
    - `--tmpfs` flag specifies the setup of the tmpfs mount, with permission, size, and management mode. 
    - Use `df -h` to check that your mount is available inside the container. 

```bash
docker run -it --tmpfs /tmpfs:rw,size=1g,mode=1777 ubuntu sh       
df -h
exit
```

{% include figure.liquid path="assets/img/courses/csc468/docker-volume/tmpfs.png" width="50%" zoomable=true %}


{% enddetails %}
{% enddetails %}
{% details Best Practices for Docker Storage? %}

- Docker Volume
    - Persistent storage that can survive container restarts
    - Portable data across different Docker host
    - Sharing databases, logs, application data, or shared storage 
    across multiple containers
    - Docker-managed storage
    - Isolation from host
- Bind mount
    - Access to host files from inside containers
    - Access to configuration files, logs, or source code from host
    - Real-time file updates
    - Security is not a primary focus
- tmpfs mount
    - Fast, temporary storage on RAM
    - Data that disappears when container stops
    - Reduce disk writes

{% enddetails %}
---

## Hands-on 

{% details Bind mounts %}


- Launch a nodejs container with a bind mount to a host directory. 
- Mount this host directory to an internal directory called `/app`
- Create the `server.js` file inside the host directory and use the nodejs container to test:

```bash
cd /app
node server.js
```



{% enddetails %}
{% details Forensics and Inodes %}

- This must be done on a Linux environment (CloudLab)
    - Windows and Mac use a virtual machine to run the Linux host file, therefore this cannot be 
    observed on either Windows WSL2 or Mac Terminal. 
- On the host machine, create a file and identify its **Inode Number**.

```bash
echo "This is physical evidence" > host_evidence.txt
ls -i host_evidence.txt
# Example Output: 123456 host_evidence.txt
```

- Run a container mapping this file.

```bash
docker run -it -v $(pwd)/host_evidence.txt:/container_evidence.txt ubuntu:20.04 bash
```

- Inside the container, check the Inode.

```bash
ls -i /container_evidence.txt
# Output: 123456 /container_evidence.txt
```

- **Observation:** The Inode numbers are identical.
- **Conclusion:** There is no "Container File" vs "Host File". There is only one physical set of blocks on the disk, with two different doors (VFS entries) leading to it.

{% enddetails %}
