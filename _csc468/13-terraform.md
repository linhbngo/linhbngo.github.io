---
layout: lecture
pretty_table: true
order: 1
title: Declarative Provisioning
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

### Declarative Provisioning: Terraform and FABRIC

#### 1. Beyond CloudLab: The FABRIC Testbed
???note "Deep Programmability"
    - In earlier lectures, we defined **Deep Programmability** as the ability to influence the behavior of computing, storage, and routing components deep inside the network [2].
    - While CloudLab provides bare-metal access [3], the **FABRIC** testbed allows us to program the actual network topologies connecting these nodes across the country.
    - Instead of clicking through a web GUI to request nodes, we will deploy infrastructure programmatically.

#### 2. Infrastructure as Code: Terraform
???note "The Declarative Paradigm"
    - We previously learned that `docker-compose.yml` uses a descriptive (declarative) syntax to define the *desired state* of a container stack.
    - **Terraform** applies this exact same declarative paradigm to the physical hardware.
    - You write code to declare: "I want two bare-metal nodes connected by a 10Gbps private link." Terraform's engine translates this into the necessary API calls to the FABRIC testbed.

???note "Theory: Directed Acyclic Graphs (DAGs)"
    - How does Terraform know which piece of infrastructure to build first?
    - Terraform does not execute your code top-to-bottom like an imperative Bash script.
    - It builds a **Directed Acyclic Graph (DAG)**.
    - **The CS Concept:** A DAG is a graph with directed edges and no cycles. Terraform maps every resource as a node in the graph. If Node B (a network interface) depends on Node A (a server), a directed edge is drawn. 
    - Terraform walks the graph to determine the exact order of creation, allowing it to provision independent resources in parallel.

???note "Theory: Immutable Infrastructure"
    - Traditional System Administration: A server breaks, an admin logs in, and fixes it (Mutable).
    - Terraform Approach: A server breaks, you destroy it, and run the Terraform code to provision a brand new, identical server (Immutable).
    - This maps perfectly to the reproducibility requirement of modern cloud engineering [2, 4].

#### 3. Hands-on: Provisioning FABRIC Nodes
???note "Writing the Terraform Configuration (.tf)"
    - Create a file named `main.tf`.
    ~~~hcl
    # Example pseudo-code for FABRIC provider
    resource "fabric_node" "manager_node" {
      name  = "manager-1"
      cores = 4
      ram   = 8
    }
    resource "fabric_node" "worker_node" {
      name  = "worker-1"
      cores = 4
      ram   = 8
    }
    ~~~
???note "Executing the Graph"
    - `terraform plan`: Calculates the DAG and previews the API calls.
    - `terraform apply`: Executes the graph and provisions the physical hardware on the FABRIC testbed.
