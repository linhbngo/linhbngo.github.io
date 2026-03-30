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
  - name: Set up environment
  - name: Prepare the service
---
### Declarative Configuration Management: Ansible
#### 1. Bridging the Gap
???note "The Pipeline So Far"
    - **Lecture 12:** We used Terraform to provision raw, blank hardware on FABRIC.
    - **Lecture 14 (Next):** We want to use Docker Swarm to deploy containers.
    - **The Missing Link:** The raw FABRIC nodes don't have Docker installed. We need a way to configure them automatically to satisfy our course project requirements [1].

#### 2. Configuration Management Theory
???note "Theory: Idempotency"
    - Writing a Bash script to install Docker is imperative and fragile. If you run `mkdir` twice, it crashes.
    - **Ansible** is based on the mathematical concept of **Idempotency** ($f(f(x)) = f(x)$).
    - An operation is idempotent if applying it multiple times has the same effect as applying it once. 
    - Ansible modules check the current state first; if the software is already installed, it does nothing.

???note "Theory: Finite State Automata"
    - Ansible treats your infrastructure as a state machine.
    - $S_0$: The blank FABRIC node.
    - $Transition$: The Ansible Playbook (declarative code).
    - $S_{final}$: The node configured exactly as desired (Docker installed, security policies set).

#### 3. Architecture of Ansible
???note "Agentless Design"
    - Unlike older tools (Chef/Puppet), Ansible is **Agentless**. It does not require a daemon running on the target machines.
    - It uses standard SSH, pushing Python modules to the targets, executing them, and tearing them down.
    - **Inventory:** A file mapping IP addresses to logical groups (e.g., `[managers]`, `[workers]`).
    - **Playbook:** A YAML file describing the desired state.

#### 4. Hands-on: Bootstrapping the Cluster
???note "Creating the Playbook"
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
???note "Executing the Playbook"
    ~~~bash
    ansible-playbook -i inventory.ini site.yml
    ~~~
