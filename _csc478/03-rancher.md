---
layout: lecture
pretty_table: true
collection: csc478
title: "Rancher RKE2"
mermaid:
  enabled: true
  zoomable: true
toc:
  - name: What is RKE2?
  - name: Key Features
  - name: "Hands-on: Typical Installation Workflow"
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

{% details Fabric %}

Run a `git pull` (run `git stash` if necessary) on your `fabric-examples` repository. Navigate to `478-examples` and open up the notebook. Run the notebook!


```mermaid
flowchart TB
  subgraph Laptop["Your laptop"]
    Browser["Browser / curl<br/>http://127.0.0.1:5555"]
    HostDocker["Docker Desktop<br/>publishes host:5555 → container:5555"]
  end

  subgraph Jupyter["fabric-jupyter container"]
    NB["Notebook + Ansible + FABlib"]
    Tunnel["SSH local forward<br/>-L 0.0.0.0:5555:127.0.0.1:8080"]
  end

  subgraph FabricEdge["FABRIC access path"]
    Bastion["bastion.fabric-testbed.net"]
  end

  subgraph Slice["FABRIC slice: RancherK8s"]
    subgraph Mgmt["Management network (often IPv6)"]
      N1mgmt["node1 mgmt IP"]
      N2mgmt["node2 mgmt IP"]
    end

    subgraph DP["L2 dataplane 192.168.1.0/24"]
      N1dp["node1<br/>192.168.1.1"]
      N2dp["node2<br/>192.168.1.2"]
    end

    subgraph RKE2["RKE2 cluster"]
      Server["rke2-server<br/>control-plane + etcd"]
      Agent["rke2-agent<br/>worker"]
      API["Kubernetes API :6443"]
      Canal["Canal / Flannel CNI<br/>iface-can-reach 192.168.1.1"]
      Svc["Service nginx-demo<br/>ClusterIP + NodePort 30080"]
      Pods["Pods nginx-demo<br/>replicas on cluster network"]
      PF["kubectl port-forward<br/>127.0.0.1:8080 → svc/nginx-demo:80"]
    end
  end

  Browser -->|"http://127.0.0.1:5555"| HostDocker
  HostDocker --> Tunnel
  NB -->|"provision / ansible"| Bastion
  Tunnel -->|"SSH via bastion"| Bastion
  Bastion --> N1mgmt
  Bastion --> N2mgmt

  N1mgmt --- Server
  N2mgmt --- Agent
  N1dp --- Server
  N2dp --- Agent
  Server --- API
  Server --- Canal
  Agent --- Canal
  Canal --- Pods
  API --> Svc
  Svc --> Pods
  Server --> PF
  Tunnel -->|"after SSH lands on node1<br/>connect to loopback :8080"| PF
  PF -->|"cluster networking"| Svc

  classDef warn fill:#fff3cd,stroke:#856404
  classDef ok fill:#d4edda,stroke:#155724
  classDef path fill:#cce5ff,stroke:#004085
  class Tunnel,PF ok
  class Canal path
  class Svc warn
```

{% enddetails %}

