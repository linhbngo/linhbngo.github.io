---
layout: lecture
pretty_table: true
order: 1
title: Docker Container Security and Host-to-Container Security Propagation
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
  - name: Introduction to Docker Security
  - name: Container Security Layers
  - name: Host-to-Container Security Propagation
  - name: Recommended Tools and Best Practices
---

# Docker Container Security and Host-to-Container Security Propagation

---

## 1. Introduction to Docker Security

{% details Differences between containers and virtual machines %}

- Fundamentally different in terms of architecture, performance, and security. 
- VM: 
    - includes:
        - its own full OS (kernel and user space)
        - hypervisor that emulates hardware
    - is heavier
    - has strong isolation
- Container:
    - does not include its own kernel
        - runs as isolated processes on the host's kernel
    - is much more lightweight and faster to start
    - has lower overhead. 


{% enddetails %}
{% details Linux kernel features for containers %}

- `Namespaces` provide isolation between containers and the host system. 
    - Ensuring the one container cannot `see` or `interfere` with other containers or with host processes. 

| **Namespace** | **Isolates**              | **Example**                                         |
|---------------|---------------------------|-----------------------------------------------------|
| `PID`         | Process IDs               | Each container has its own independent process tree |
| `NET`         | Network interfaces        | Containers have separate virtual Ethernet devices   |
| `MNT`         | Mount points / filesystems| Separate view of file system mounts                |
| `IPC`         | Inter-process communication| Shared memory and semaphores are isolated          |
| `UTS`         | Hostname & domain name    | Containers set their own host names                 |
| `USER`        | User and group IDs        | Maps container users to host UID/GIDs on host      |

- `Control groups (cgroups)` control how much CPI, memory, disk I/O, and network bandwidth a container can use. 
- `Namespaces` isolate visibility and `cgroups` limit impact. 
    - Additional security mechanisms are still needed. 


{% enddetails %}
{% details Potential security issues %}

- **Isolation vs. Security**: Isolation via namespaces does not imply total security. Containers are separated but can still interact with the host if not properly configured.
- **Shared Kernel Risks**: Since all containers share the host kernel, any kernel-level vulnerability can compromise the entire host and all running containers.

{% enddetails %}
---

## 2. Container Security Layers

{% details Kernel-level Isolation %}

- **Namespaces**: Provide process, network, and filesystem isolation. E.g., PID namespace isolates process IDs.
- **cgroups**: Limit container resource usage (CPU, memory, IO) to prevent resource starvation attacks.
- **seccomp**: Filters and blocks dangerous system calls, reducing kernel attack surface.

{% enddetails %}
{% details Container Runtime Configuration %}

- **Drop Linux Capabilities**: Use `--cap-drop` to remove unnecessary kernel privileges (e.g., `CAP_SYS_ADMIN`).
- **Read-only Filesystem**: `--read-only` prevents write access to the root filesystem, limiting impact of compromise.
- **Run as Non-root**: Set a non-root user via the `USER` directive in Dockerfile to prevent privilege escalation inside containers.
- All these can and should be set in Dockerfile and docker-compose.yml

{% enddetails %}
{% details Image Security %}

- **Trusted Base Images**: Always use official or verified images to avoid introducing malware.
- **Scanning for Vulnerabilities**: Tools like `docker scan`, Trivy, and Clair help detect outdated or vulnerable packages.
- **Multistage Builds**: Reduces image size and removes build-time dependencies that aren’t needed in production, minimizing attack surface.

{% enddetails %}
{% details Network Security %}

- **Avoid Host Networking**: Using `--network host` can expose the container to the host network stack, reducing isolation.
- **Restrict Published Ports**: Use `--publish` judiciously to expose only necessary ports.
- **Internal Networks**: Use Docker's `bridge` or `overlay` networks to isolate traffic between containers, enabling service segmentation.

{% enddetails %}
---

## 3. Host-to-Container Security Propagation

{% details Kernel Shared Surface %}

- Containers share the host’s kernel — a critical point of failure.
- Kernel exploits in one container can lead to full host compromise if not isolated with `AppArmor`, `seccomp`, etc.

{% enddetails %}
{% details Privileged Containers %}

- `--privileged` lifts all security restrictions, giving container full host access (devices, kernel modules, etc.).
- Should only be used for trusted tools or low-risk environments like CI runners with additional controls.

{% enddetails %}
{% details Dangerous Mounts %}

- **Root Filesystem Exposure**: `-v /:/host` gives container access to the host’s entire filesystem, which can be exploited.
- **Docker Socket Exposure**: Mounting `/var/run/docker.sock` allows the container to control the Docker daemon — effectively full root access.
- These mounts are high-risk and should be avoided or tightly secured with user namespace remapping.

{% enddetails %}
---

## 4. Recommended Tools and Best Practices

{% details AppArmor / SELinux %}

- **Mandatory Access Control (MAC)**: Systems like AppArmor and SELinux enforce security policies even if root is compromised.
- **AppArmor Example**: Use `--security-opt apparmor=docker-default` to apply a restrictive policy.
- **Policy Effects**: Limit syscalls, restrict filesystem access, and reduce impact of zero-day exploits.

{% enddetails %}
{% details seccomp and Capabilities %}

- **seccomp**: Docker’s default profile blocks about 44 high-risk syscalls (e.g., `ptrace`, `keyctl`). Custom profiles allow more granular control.
- **Linux Capabilities**: Drop unneeded ones to reduce what containers can do (e.g., remove `CAP_NET_RAW` to block raw socket use).
- **Fine-grained Privilege**: Tailor container permissions using `--cap-add` and `--cap-drop` to follow the principle of least privilege.

{% enddetails %}
{% details Defense in depth %}


| **Feature**       | **AppArmor / SELinux**                                             | **seccomp**                                                |
|------------------|---------------------------------------------------------------------|------------------------------------------------------------|
| **Type**         | Mandatory Access Control (MAC)                                      | System Call Filtering                                       |
| **Scope**        | Controls access to **files**, **network**, **processes**, etc.      | Controls access to specific **system calls** (`syscalls`)  |
| **Goal**         | Limit what a process/container can **access** or **interact with**  | Limit what a process can **ask the kernel to do**          |
| **Granularity**  | File paths, network, IPC, user/group ID, etc.                       | Individual syscalls like `clone`, `ptrace`, `mount`, etc.  |
| **How it works** | Applies a profile that **labels and restricts access**              | Uses a syscall filter list to **allow or deny** operations |
| **Docker Usage** | `--security-opt apparmor=profile_name` or SELinux `label=...`       | Enabled by default in Docker with a **default profile**     |
| **Example**      | Deny write to `/etc/shadow` or opening raw sockets                  | Deny syscalls like `keyctl`, `mount`, or `ptrace`          |
| **OS Dependency**| AppArmor (Ubuntu), SELinux (RHEL, Fedora, CentOS)                   | Works across most Linux distributions                      |


{% enddetails %}
{% details Best Practices Summary %}

- Use minimal and verified base images
- Scan and update images frequently
- Never run containers as root unless absolutely required
- Apply AppArmor or SELinux policies
- Avoid privileged containers and dangerous mounts
- Use dedicated networks for container communication
- Enable Docker Content Trust (DCT) to verify image signatures


{% enddetails %}
{% details Hands-on: Dropping Capabilities %}

- Start a container with and without `--cap-drop=ALL`
```bash
docker run -it --rm ubuntu bash
apt update
apt install -y iputils-ping
ping -c 4 www.google.com
```


```bash
docker run -it --rm --cap-drop=ALL ubuntu bash
apt update
apt install -y iputils-ping
ping -c 4 www.google.com
```
{% enddetails %}
