---
layout: lecture
pretty_table: true
order: 1
title: "Virtualization for cloud computing: KVM, docker, singularity, and podman"
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
  - name: KVM
  - name: Docker
  - name: Singularity
  - name: Podman
---

# Virtualization for cloud computing: KVM, docker, singularity, and podman

---

## 1. KVM

{% details Overview %}


- Created by Avi Kivity at Qumranet
    - Become part of the Linux kernel in 2007
    - Hardware-based virtualization
- Virtualizing the x86 architecture (Intel and AMD)
- Hardware vendors provide the following extensions to the x86 architectures
    - A new guest operating mode: the CPU can switch into a guest mode that allows 
    system software to trap specific privileged instructions or accesses.
    - Hardware state switch: Hardware is responsible for switching the control registers that 
    affect the CPU operation modes and relevant segment registers.
    - Exit reason reporting: When a switch from guest to host happens, the hardware reports 
    the reason so that the software can take appropriate responses. 
- KVM has been developed to take advantage of these extensions.

{% enddetails %}
{% details General architecture %}


- Virtual machines are created by opening a device node (`/dev/kvm`) - essentially a file. 
- Operations provides by `/dev/kvm` includes:
    - Create a new VM
    - Allocate memory to a VM
    - Reading and writing virtual CPU registers
    - Injecting an interrupt into a virtual CPU
    - Running a virtual CPU

{% include figure.liquid path="assets/img/courses/csc468/06-virtualization/01.png" width="50%" zoomable=true alt="KVM Architecture" %}

{% enddetails %}
{% details Memory mapping %}


- Kernel allocates discontiguous pages to form the Guest address space.
- User address space (of processes inside the VM) can `mmap` directly to 
these allocation to provide direct-memory-access capability. 

{% include figure.liquid path="assets/img/courses/csc468/06-virtualization/02.png" width="50%" zoomable=true alt="Virtual memory mapping" %}


{% enddetails %}
{% details CPU execution %}


- A new mode is added called `guest mode`.
- User space calls the kernel to execute guest code.
- Kernel causes hardware to enter guest mode and handles interrupts when CPU exits guest mode. 
- Hardware execute guest code until it encounters instructions that needs assistance. 

{% include figure.liquid path="assets/img/courses/csc468/06-virtualization/03.png" width="50%" zoomable=true alt="KVM CPU" %}

- Intel versus AMD
      - X86 family has different branches
      - KVM uses C’s function pointer vector 
      (kvm_arch_ops) to call the appropriate 
      function that handles each architecture.


{% enddetails %}
{% details Virtualizing the MMU (memory management unit) %}


- MMU: Translate virtual address space (from users’ perspective) 
to physical addresses.
    - Page table: virtual-to-physical translation, located in hardware registers
    - Page faults mechanism (missing translation)
    - On-chip cache (translation lookaside buffer) that accelerates lookup of the page table.
- Hardware support mmu virtualization:
    - Provides support for guest_virtual to guest_physical
    - Does not account for guest_physical to host_physical
- Solutions: shadow page table that performs the later task. 


{% enddetails %}
{% details MMU: Initial implementation %}


- Less complicated, but also sacrificed performance.
- Copy the contents changes due to guest instructions that 
require access to TLB’s page tables.
- Most common TLB instruction is context_switch, which invalidate 
the entire TLB (impacting shadow table). 
- Rebuilding the shadow table is expensive.
- Impact guest’s workload with multiple processes

{% enddetails %}
{% details Caching virtual mmu %}


- Virtual MMU implementation (from hardware vendor) was enhanced to 
allow page tables to be cached across context switches.
- Guest memory pages (on physical host) that are shadowed by KVM need 
to be write-protected.
- Write access to guest page table needs to be emulated (rather than 
trying to use the host x86 instructions) so that we know exactly what 
happens to the guest memory and to the shadow page table. 

{% enddetails %}
{% details I/O Virtualization %}


- Software uses programmed I/O (pio) and memory mapped I/O 
(mmio) to communicate with hardware devices.
- KVM needs to be able to trap and emulate pio and mmio 
request (from guest to physical host) and simulate interrupts 
from virtual hardware to programs running in guest.  

{% enddetails %}
{% details Why the complexity %}


- Essential characteristics of VMM:
      - Essentially identical to the physical resource
      - Efficiency
      - Complete control of system resources (with regard to 
      the processes running inside the VM)
- Support advanced complex devices in modern computers
      - Graphical devices
      - High speed storage devices  

{% include figure.liquid path="assets/img/courses/csc468/06-virtualization/04.png" width="50%" zoomable=true alt="KVM Complexity" %}

{% enddetails %}
---

## 2. Docker

{% details History %}



{% include figure.liquid path="assets/img/courses/csc468/06-virtualization/05.png" width="50%" zoomable=true alt="Docker" %}
{% include figure.liquid path="assets/img/courses/csc468/06-virtualization/06.png" width="50%" zoomable=true alt="Docker" %}

- Benefits of VM
    - Better resource pooling
        - One physical machine divided into multiple VMs
    - Easier to scale
    - VMs in the Cloud
        - Rapid elasticity
        - Pay as you go model
- Limitation of VM
    - Each VM still requires
        - CPU allocation
        - Storage
        - RAM
        - An entire guest OS
- The more VM you runs, the more overhead resources you need
- Guest OS means wasted resources
- Application portability is not guaranteed

{% enddetails %}
{% details What is a container %}



- Standardized packaging for software and dependencies
- Isolate apps from each other
- Share the same OS kernel
- Work with all major Linux and Windows server

{% include figure.liquid path="assets/img/courses/csc468/06-virtualization/07.png" width="50%" zoomable=true alt="Docker" %}
{% include figure.liquid path="assets/img/courses/csc468/06-virtualization/08.png" width="50%" zoomable=true alt="Docker" %}


{% enddetails %}
{% details Containers and VMs together %}


{% include figure.liquid path="assets/img/courses/csc468/06-virtualization/09.png" width="50%" zoomable=true alt="Docker" %}

{% enddetails %}
{% details Key benefits of Dockers %}


- Speed
    - No OS to boot
- Portability
    - Less dependencies between process layers
- Efficiency
    - Less OS overhead
    - Improved VM density

{% enddetails %}
---

## 3. Singularity

{% details Overview %}


- Begin as an open source project in 2015 at 
Lawrence Berkeley National Laboratory.
- Released until BSD License
- Top 5 new technologies to watch in 2016-2017 (HPCWire)
- Being used in academic:
    - Standard University Research Computing Center
    - National Institute of Health
    - 60% of the Open Science Grid Consortium.
    - Ohio State, Michigan State, TACC, SDSC, and Oak Ridge National Lab
- Supports for native high performance interconnects (InfiniBand, OmniPath)
- Supports for native graphic accelerators
- Supports for Open MPI, including a hybrid mode (inside and outside 
of containers)
- Useful for new advanced research areas such as ML, Deep Learning, and 
data-intensive workloads


{% enddetails %}
{% details Motivation: container software unit for scaled science %}


- Current approaches suitable for industry’s micro-service virtualization and 
web-enabled cloud application.
    - Wiki: Microservices are a `software development` technique—a variant of the 
    `service-oriented architecture` (SOA) architectural style that structures an 
    `application` as a collection of `loosely coupled services`. In a `microservices`
    architecture, services are `fine-grained` and the `protocols` are lightweight.
- Not quite suitable for  scientific world, and HPC communities.
- The reproducibility and portability aspects of containers are highly desirable.
- Security level of Docker is not good enough for a shared research environment.

{% enddetails %}
{% details The needs of scientists %}

- Technological innovation of container-based environments
- The needs for scalable and reproducible products
- Preference for usability
- Necessity to operate on everything from laptops to large-scale HPC
- Before: Scientists exchange data files and source codes
- Today: Scientists exchange workflows
- These two things need to be encapsulated into a single computing environment
- Challenges with Docker:
    - Security concerns: Docker’s containers are spawned as a child of a root-owned Docker daemon
        - Potential issue: privilege leakage
    - Lack of administrative control in what’s being run/monitored (opposite of an 
    industry environment)

{% enddetails %}
{% details What Singularity aims to solve %}

- Specific accomplishments
    - Mobility of Compute
        - Distributable image format that encapsulates the entire container 
        and software stack into a single image file.
  - Reproducibility
      - Utilize single files, which allow snapshot, archive, and lock-down 
      for reusability purposes.
      - No external influence from the host OS.
  - User freedom
      - Can install any relevant dependencies inside the system without 
      worrying about the host OS.
  - Support existing traditional HPC resources.

{% include figure.liquid path="assets/img/courses/csc468/06-virtualization/10.png" width="50%" zoomable=true alt="Singularity" %}

{% enddetails %}
---

## 4. Podman

{% details Overview %}


- Container engine developed by RedHat. 
- Addressing issues with Docker
    - Persistent daemon on host. 
    - Root/privileged concerns
- OCI: Open Container Initiative (2015). 
- Podman
    - Client-only tool, based on Docker CLI
    - No Daemon
    - Similar CLI experience as Docker CLI
    - Build and run containers as non-root
    - Simple CLI, no client-server architecture. 

{% enddetails %}
