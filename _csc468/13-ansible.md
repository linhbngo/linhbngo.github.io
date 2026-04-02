---
layout: lecture
pretty_table: true
order: 1
title: Declarative Configuration Management
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
last_updated: 2026-02-24

toc:
  - name: Bridging the Gap
  - name: Configuration Management Theory
  - name: Architecture of Ansible
  - name: Hands-on
---

## Bridging the Gap

{% details The Pipeline So Far %}
    - **Lecture 12:** We used FABRIC to provision raw, blank hardware on FABRIC.
    - **Lecture 14 (Next):** We want to use Docker Swarm to deploy containers.
    - **The Missing Link:** The raw FABRIC nodes don't have Docker installed. We need a way to configure them automatically to satisfy our course project requirements.
{% enddetails %}

## Configuration Management Theory

{% details Theory: What “Declarative Configuration” Really Means %}

- In **imperative configuration**, we describe a sequence of commands:
  - install this package
  - start this service
  - create this directory
  - copy this file
- In **declarative configuration**, we describe the **desired final state** of the system:
  - Docker **is installed**
  - the Docker service **is enabled and running**
  - a configuration file **exists with specific contents**
  - firewall rules **allow required traffic**

- The key idea is that the user specifies the **goal state**, while the tool determines whether any changes are needed to move the machine from its **current state** to that goal state.
- This is why declarative systems are often described as **state reconciliation systems**.

{% enddetails %}

{% details Theory: Convergence and Drift %}

- Declarative configuration management is built around **convergence**:
  - No matter what state a machine starts in, repeated application of the playbook should drive it toward the same target configuration.
- This helps manage **configuration drift**, where machines that were originally identical slowly become different over time because of manual fixes, forgotten updates, or one-off experiments.
- In other words:
  - Imperative scripts: **"Do these steps."**
  - Declarative systems: **"Make reality match this description."**

{% enddetails %}

{% details Theory: Why This Matters in Cloud and Distributed Systems %}

- In cloud environments, machines are often short-lived, replaced frequently, or provisioned in batches.
- Manual setup does not scale well because:
  - it is error-prone,
  - it is hard to reproduce,
  - and different nodes can silently diverge.
- Declarative configuration gives us:
  - **reproducibility**: we can rebuild environments consistently,
  - **auditability**: the desired configuration is written down in version-controlled files,
  - **maintainability**: changes are made by updating code, not by logging into random machines,
  - **scalability**: the same playbook can configure one node or many nodes.

{% enddetails %}

{% details Theory: Declarative Configuration as Infrastructure Discipline %}

- Treat infrastructure as an engineered system rather than a collection of hand-maintained machines.
- This is especially important in modern environments where:
  - systems are rebuilt often,
  - services are distributed,
  - and reproducibility is critical for both industry and research computing.

{% enddetails %}

## Architecture of Ansible

{% details Overall Design %}

- Agentless
  - Unlike older tools (Chef/Puppet), Ansible is **Agentless**. It does not require a daemon running on the target machines.
  - It uses standard SSH, pushing Python modules to the targets, executing them, and tearing them down.
- Idempotency
  - An Ansible playbook is guaranteed to result in the same system state no matter how many times it is run. 
- Declarative Syntax:
  - Users define `what` the system state should look like, and Ansible will handle `how` to achieve it. 
- Extensible
  - Support hundreds of built-in modules and allows for custom modules written in Python

{% enddetails %}


{% details Idempotency %}
    - Writing a Bash script to install Docker is imperative and fragile. If you run `mkdir` twice, it can generate 
    an error, which then can cause a crash.
    - **Ansible** is based on the mathematical concept of **Idempotency** ($f(f(x)) = f(x)$).
    - An operation is idempotent if applying it multiple times has the same effect as applying it once. 
    - Ansible modules check the current state first; if the software is already installed, it does nothing.
{% enddetails %}

{% details Finite State Automata %}
    - Ansible treats your infrastructure as a state machine.
    - $S_0$: The blank FABRIC node.
    - $Transition$: The Ansible Playbook (declarative code).
    - $S_{final}$: The node configured exactly as desired (Docker installed, security policies set).
{% enddetails %}


{% details Components %}

- **Control Node**:
  - Ansible installation
  - Playbook deployment
- **Managed Nodes (Hosts)**:
  - Computing instances managed by Ansible
  - Management connection is handled by SSH
- **Inventory** :
  - A file mapping IP addresses to the managed hosts (e.g., `[managers]`, `[workers]`), or
  - A script that query cloud providers for list of current running instances
- **Modules**:
  - Small programs that Ansible pushes to the managed nodes to perform tasks (e.g., yum, apt, service, ...)
  - Core modules are maintained by Ansible
  - Custom modules can be developed by users
- **Playbook**:
  - A YAML file describing the desired state.
- **Plugins**:
  - Extend Ansible's core functionality

{% enddetails %}

##  Hands-on

{% details Baseline Imperative Setup and SSH Tunneling %}

- Once the slice (experiment) is setup, the process of uploading the startup file is somewhat similar to CloudLab. 
- We can `upload` the installation directory, then `execute` the uploaded scripts:
  - The installation log is ready locally. 

```bash
node.upload_directory('scripts','.')
node.execute('bash scripts/web_server.sh',  quiet=True, output_file=f"{node.get_name()}.log")
```

- For this example, to view the installed Nginx server, we need to setup an SSH tunnel. 

{% include figure.liquid path="assets/img/courses/csc468/ansible/fabric-ssh-tunneling.png" max-width="50%" zoomable=true %}

{% enddetails %}

{% details Declarative Setup using Ansible %}

- Review notes from [web_ansible.ipynb](https://github.com/CSC468-WCU/fabric-examples/blob/main/468_examples/web_ansible/web_ansible.ipynb).

{% enddetails %}

{% details Challenges %}

Develop an Ansible playbook to setup Docker inside a single-node slice. 

{% enddetails %}