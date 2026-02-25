---
layout: lecture
pretty_table: true
order: 1
title: Container Engines and Platforms
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
  - name: Docker
  - name: Singularity
  - name: Podman
---

## Docker

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

## Singularity

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

## Podman

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
