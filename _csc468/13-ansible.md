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

{% details Agentless Design %}
    - Unlike older tools (Chef/Puppet), Ansible is **Agentless**. It does not require a daemon running on the target machines.
    - It uses standard SSH, pushing Python modules to the targets, executing them, and tearing them down.
    - **Inventory:** A file mapping IP addresses to logical groups (e.g., `[managers]`, `[workers]`).
    - **Playbook:** A YAML file describing the desired state.
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

{% details Creating the Playbook %}
    - We will write a `site.yml` to install Docker on the nodes Terraform just built.
    ~~~yaml
    - hosts: all
      become: yes
      tasks:
        - name: Ensure Docker is installed
          apt:
            name: docker.io
            state: present
        - name: Ensure Docker service is running
          service:
            name: docker
            state: started
    ~~~
{% enddetails %}

{% details "Executing the Playbook" %}
    ~~~bash
    ansible-playbook -i inventory.ini site.yml
    ~~~
{% enddetails %}