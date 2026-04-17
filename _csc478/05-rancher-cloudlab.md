---
layout: lecture
pretty_table: true
collection: csc478
title: "Rancher RKE2"
toc:
  - name: What is RKE2?
  - name: Key Features
  - name: Hands-on: Typical Installation Workflow
---
# Rancher RKE2

---

## What is RKE2?

{% details RKE2 %}

- Rancher Kubernetes Engine 2
- A CNCF-certified Kubernetes distribution developed by SUSE Rancher.
- Designed as the next generation of RKE, focusing on:
    - Security first (FIPS 140-2 compliance, SELinux, CIS hardening profiles).
    - Simplicity of deployment (single binary installer).
    - Production-ready for on-premise, edge, and cloud environments.

{% enddetails %}
{% details CNCF %}

- Cloud Native Computing Foundation, part of the Linux Foundation
- To support and advance cloud-native technologies, especially Kubernetes. 
- Other projects:
    - Prometheus: open-source monitoring and alerting system designed for reliability and scalabiliaty. 
    - Envoy: a high-performance service proxy and communication bus designed for microservices
    - Helm: a package manager for Kubernetes, aims to simplify the deployment and management of applications using reusable configuration templates (`charts`)
    - Containerd: lightweight container runtime. 

```mermaid
flowchart TD
subgraph Kubernetes["Kubernetes Cluster"]
    direction TB

    subgraph ControlPlane["Control Plane"]
        Helm["Helm\n(Package Manager)"]
        Prometheus["Prometheus\n(Monitoring & Alerting)"]
    end

    subgraph DataPlane["Data Plane"]
        Containerd["Containerd\n(Container Runtime)"]
        Envoy["Envoy\n(Service Proxy / Networking)"]
    end
end

Helm -->|Deploys apps| Containerd
Prometheus -->|Monitors| ControlPlane
Envoy -->|Routes traffic| Containerd
```

{% enddetails %}
---

## Key Features

{% details Security Enhancements %}

- Built-in support for CIS benchmarks (kube-bench ready).
    - CIS: Center for Internet Security
- SELinux policies enforced by default.
- Containerd (not Docker) as runtime for security and performance.

{% enddetails %}
{% details Operational Simplicity %}

- Single binary distribution (rke2).
- Automated etcd management.
- Rancher integration for centralized multi-cluster management.

{% enddetails %}
{% details Flexibility %}

- Works in data centers, cloud, and at the edge.
- Supports air-gapped environments.

{% enddetails %}
{% details Architecture Overview %}


- Server Nodes: Run the Kubernetes control plane + etcd.
- Agent Nodes: Run workloads (similar to workers).
- Runtime: Containerd, not Docker.
- Networking: Uses CNI plugins (default: Canal, but others supported).
- Ingress: NGINX ingress controller by default.

{% enddetails %}
{% details Why RKE2 Matters %}


- A production-grade Kubernetes distro hardened out-of-the-box.
- Ideal for regulated industries (finance, healthcare, government).
- Designed for multi-cluster management with Rancher.
- Future-facing: aligns with CNCF standards and cloud-native practices.

{% enddetails %}
---

## Hands-on: Typical Installation Workflow

{% details CloudLab GitHub Repository %}

- GitHub Repo: https://github.com/WCU-AIR/k8s-lab/tree/main
- CloudLab Profile: Instantiate from `main` branch of `k8s-lab` profile. 
    - Three nodes
    - Alternate between emulab/Clemson/Wisconsin

{% enddetails %}
{% details Hands-on %}

- Part 1:
    - Repeat the deployment exercise from the Pod-Service-Deployment lecture. 
- Part 2:
    - Explore the usage of `kubectl exec -it` and attempt to open a shell terminal into your running pods/containers from part 1. 
    - Who are you inside the container?
    - Can you ping other pods/containers?
    - Can you download/install software (apt-get/yum/wget ...) inside the pods/containers?


{% enddetails %}
