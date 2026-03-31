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

{% details Theory: Idempotency %}
    - Writing a Bash script to install Docker is imperative and fragile. If you run `mkdir` twice, it can generate 
    an error, which then can cause a crash.
    - **Ansible** is based on the mathematical concept of **Idempotency** ($f(f(x)) = f(x)$).
    - An operation is idempotent if applying it multiple times has the same effect as applying it once. 
    - Ansible modules check the current state first; if the software is already installed, it does nothing.
{% enddetails %}

{% details Theory: Finite State Automata %}
    - Ansible treats your infrastructure as a state machine.
    - $S_0$: The blank FABRIC node.
    - $Transition$: The Ansible Playbook (declarative code).
    - $S_{final}$: The node configured exactly as desired (Docker installed, security policies set).
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