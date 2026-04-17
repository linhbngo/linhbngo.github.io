---
layout: lecture
pretty_table: true
collection: csc478
title: "From Prototype to Production: Deploying in the Cloud"
toc:
  - name: Welcome to Cloud Engineering
  - name: What is Kubernetes?
  - name: Kubernetes in Context
  - name: Inside Borg (2003-2015)
  - name: What Kubernetes Learned from Borg
  - name: Kubernetes Architecture Overview
  - name: Course Plan
---

# From Prototype to Production: Deploying in the Cloud

---

## Welcome to Cloud Engineering

{% details info Details %}

From working prototypes to production infrastructure

{% enddetails %}
- You built something that works. Now comes the hard part: **making it work reliably, at scale**
- This course takes you 
    - from developer to cloud engineer
    - from local services to orchestrated microservices
    - from Docker to Kubernetes

{% details You have built the app %}

- We all remember RamCoin (a cryptocurrency mining stack)
    - Services:
        - `rng`: generates random data
        - `hasher`: hashes the data
        - `worker`: coordinates hashing jobs
        - `redis`: backend store
        - `webui`: frontend dashboard

{% include figure.liquid path="assets/img/courses/csc478/intro/01-ram-coin.png" width="50%" zoomable=true alt="Components of a coin mining infrastructure" %}

{% enddetails %}
{% details Now you need to deploy it %}

{% details warning Problem: Prototype != Production %}

- How do you run this system across multiple machines?
- How do you recover from failure?
- How do you update without downtime?
- How do you manage logs, secrets, access controls?
{% enddetails %}
- We have options (but not all are equal)

{% details note Docker Compose %}

- Great for dev/test
- But no self-healing, no scaling (single node scaling only), no declarative control

{% enddetails %}
{% details note Docker Swarm %}

- Lightweight orchestration
- But nearly deprecated and not widely supported

{% enddetails %}
{% details note Kubernetes %}

- Designed for large-scale, production deployments
- Industry-standard
- Built for resilience, scaling, and management

{% enddetails %}
{% enddetails %}
{% details tip Details %}

If Docker Compose is your local test bed, Kubernetes is your data center.

{% enddetails %}
---

## What is Kubernetes?

- Open-source container orchestration platform
- Maintains **desired state** using declarative configuration (YAML)
- Core resources:

  - **Pods**: smallest deployable unit
  - **Services**: expose pods
  - **Deployments**: manage pod replicas

{% details What does orchestrate mean? %}

- Dictionary definition: *to arrange or combine so as to achieve a desired or maximum effect*
    - Kubernetes documentation: *We tell Kubernetes what the desired state of our system 
  is like, and Kubernetes will work to maintain that*
- Before containerization/virtualization, we have cluster of computers running jobs.
    - Jobs = applications running on single or multiple computing nodes
    - Applications' dependencies are tied in to the supporting operating system on these nodes.
    - Cluster management system only need to manage applications. 
- Container is more than an application. 
    - A lightweight virtualization of an operating system and its components that help an application
    to run, including external libraries.
    - A running container does not depending on a host computer's libraries. 
    - Is the management process the same as a cluster management system? 

{% enddetails %}
---

## Kubernetes in Context

- Kubernetes didn't emerge from nowhere
- It was **inspired by Borg**, Google’s internal cluster manager

{% details Before Kubernetes: Borg, a cluster management system %}

- Google’s Cluster Management System
    - First developed in 2003.
    - Abhishek Verma, Luis Pedrosa, Madhukar Korupolu, David Oppenheimer, Eric Tune, 
    and John Wilkes. `Large-scale cluster management at Google with Borg.` In 
    Proceedings of the Tenth European Conference on Computer Systems, p. 18. ACM, 2015.
    - Manages hundreds of thousands of jobs, from many thousands of different applications, across 
    clusters up to tens of thousands machines. 
- Borg is the predecessor of Kubernetes. Understand Borg helps understand the 
design decision in creating Kubernetes. 
    - Kubernetes is perhaps the most popular open-source container orchestration
    system today, for both academic and industry. 
    - Other container orchestration systems are either
        - Deprecating (Docker Swarm)
        - Integrates container management as part of the existing framework rather 
          than developing a new management system (UC Berkeley's Mesos and Twitter's Aurora) 

{% enddetails %}
- Borg runs:
    - Gmail
    - YouTube
    - Google Search

{% details info Details %}

Kubernetes is Borg’s spiritual child but open, modular, extensible

{% enddetails %}
---

## Inside Borg (2003-2015)

- Manages 10K+ machines per cluster
- Schedules hundreds of thousands of jobs
- Uses a **central master**, and node-level agents ("Borglets")
- Concepts:
    - Jobs
    - Tasks
    - Allocations
    - Cells

{% details Borg's concepts elaborated %}

- Work is submitted to Borg as **jobs**, which can have one or more **tasks** (binary). 
- Each job runs in one Borg **cell**, consisting of multiple machines that are managed 
as a single unit. 
- A Borg’s **allocation** defines a reserved set of resources on a machine in which one or more tasks 
can be run. 
- Job types:
    - Long running services that should never goes down and have short-lived 
    latency-sensitive 
    requests: Gmail, Google Docs, Web Search …
    - Batch jobs that take a few seconds to a few days to complete. 
- Borg cells allow for not just applications, but applications frameworks
    - One master job and one or more worker jobs. 
    - The framework can execute parallel applications itself. 
    - Examples of frameworks running on top of Borg:
        - MapReduce
        - FlumeJava: Data-Parallel Pipelines
        - Millwheel: Fault-tolerant Stream Processing at Internet Scale
        - Pregel: Large-scale graph processing
- Machines in cells belong to a single cluster, defined by the 
high-performance datacenter-scale network fabric connecting them. 
    - How is this different that the traditional cluster model?

{% enddetails %}
{% details Borg's architecture %}

- Borg Master
- Borglet

{% include figure.liquid path="assets/img/courses/csc478/intro/02-borg.png" width="50%" zoomable=true alt="Borg architecture" %}

- Scalability of Borg Master
  - Reported in the 2015 paper: `Unsure of the ultimate scalability limit` (flex anyone?)
  - A single master can 
    - manage many thousands machines in a cell
    - several cells have arrival rates of more than 10,000 tasks per minute. 
  - 2020 Borg analysis report:
    - (Muhamad Tirmazi, Adam Barker, Nan Deng, Md E. Haque, Zhijing Gene Qin, Steven Hand, 
    Mor Harchol-Balter, and John Wilkes. "Borg: the next generation." In Proceedings of the fifteenth European conference on computer systems)[https://dl.acm.org/doi/pdf/10.1145/3342195.3387517]
  - 2011 log data: 1 cell, 12000 machines (40 GB compressed)
  - 2020 log data: 8 cells, 96000 machines (350 GB compressed)
- The below graph show fraction of CPU and memory **allocation** of each category
of priority queue **relative to cell's capacity". 
- What is special about this?

{% include figure.liquid path="assets/img/courses/csc478/intro/03-scalability.png" width="50%" zoomable=true alt="Borg architecture" %}

{% enddetails %}
{% details Benefits of Borg %}

- Hides the details of resource management and failure handling so its users can 
focus on application development. 
- Operates with very high reliability and availability, and supports applications 
that have similar requirements. 
- Runs workloads across tens of thousands of machines efficiently. 
- Is not the first system that can do these, but is one of the very few that 
can do it at such scale. 

{% enddetails %}
---

## What Kubernetes Learned from Borg

{% details tip Details %}

- Avoided the monolithic "job" abstraction
- Introduced **Pods** as logical units
- Uses **labels** to select and control resources
- Maps IPs to **services**, not physical machines
- Emphasized **resilience and observability**

{% enddetails %}
We will cover these concepts through the course!

---

## Kubernetes Architecture Overview

{% include figure.liquid path="assets/img/courses/csc478/intro/04-k8s.svg" width="50%" zoomable=true alt="Kubernetes architecture diagram" %}

- Control Plane: `api-server`, `scheduler`, `controller`, `etcd`
- Node Agent: `kubelet`, `kube-proxy`, container runtime

{% details What Kubernetes learned from Borg %}

- Rejection of the `job` concept and organize around the concept of `pods`. 
    - `labels` are used to described the `objects` (`jobs`, `services`, ...) 
    and their desired states. 
    - Kubernetes schedules and orchestrates things at the pod level, not 
    at the container level. 
    - Containers running in the same pod have to be managed together (shared fate). 
    - Management transparency: You don’t have to micromanage processes within a pod. 
- IP addresses are mapped to `pods` and `services` and not physical computers. 
- Optimizations for high-demand jobs.  
- The perception of Kubernetes' kernel as an operation system kernel for a 
distributed system. 

{% enddetails %}
---

## Course Plan

- Project-based cloud engineering
    - Will depend on projects that you (or members of your group) worked on in CSC 468, Introduction to Cloud Computing
- Local testbed: Moving from Docker Desktop to Rancher Desktop
- Cloud testbed: CloudLab
- Rancher Desktop, minikube, or kind (local clusters)
