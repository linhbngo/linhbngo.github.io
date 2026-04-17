---
layout: lecture
pretty_table: true
collection: csc478
title: "Rancher Desktop"
toc:
  - name: Welcome to Rancher Desktop
  - name: Setting Up Rancher Desktop
  - name: Container runtimes
  - name: Kubernetes Readiness Check
  - name: Docker Practice
  - name: What’s Next
---
# Rancher Desktop

---

## Welcome to Rancher Desktop

{% details info Details %}

- A modern, Kubernetes-native replacement for Docker Desktop
- Rancher Desktop provides:
    - Container runtime (via `containerd`)
    - Kubernetes cluster (via `k3s`)
    - Open source and license-free
    - Local cloud-in-a-box: Build, run, push, and deploy
- Rancher Desktop is part of [SUSE' Rancher: Enterprise Kubernetes Management Ecosystem](https://www.rancher.com/).


{% enddetails %}
{% details tip Details %}

- The goal of this lecture is to get you to become familiar with Rancher Desktop and its container operations. 
- This lecture uses hands-on activities that are similar to [CSC468](https://www.cs.wcupa.edu/LNGO/courses/csc468/lectures/06-docker/).

{% enddetails %}
{% details Rancher vs Docker Desktop %}


| Feature          | Docker Desktop          | Rancher Desktop                    |
| ---------------- | ----------------------- | ---------------------------------- |
| Docker CLI       | Built-in                | Nerdctl (alias to Docker commands) |
| Kubernetes       | Optional, single-node   | Built-in K3s, enabled by default   |
| Licensing        | Commercial for business | Free, open-source                  |
| Registry login   | Native                  | nerdctl login required             |
| Resource control | GUI                     | GUI with YAML config               |

{% enddetails %}
{% details tip Details %}

Rancher Desktop is designed with Kubernetes in mind from day one

{% enddetails %}
---

## Setting Up Rancher Desktop

- Ideally, you should uninstall Docker Desktop before starting to install Rancher Desktop. 
    - Rancher Desktop can do the same tasks as Docker Desktop (with less GUI tools).
    - Rancher Desktop provides more support for Kubernetes (focus of this class).
- Install from [rancherdesktop.io](https://rancherdesktop.io)
- On first launch, Rancher Desktop will bring up the `Settings` tab:

    {% details On Virtual Machine, select the appropriate Memory and CPUs amount %}

{% include figure.liquid path="assets/img/courses/csc478/rancher/01.png" width="50%" zoomable=true %}

    {% enddetails %}
    {% details On Container Engine, select containerd %}

{% include figure.liquid path="assets/img/courses/csc478/rancher/02.png" width="50%" zoomable=true %}

    {% enddetails %}
    {% details On Kubernetes, check Enable Kubernetes %}

{% include figure.liquid path="assets/img/courses/csc478/rancher/03.png" width="50%" zoomable=true %}


    {% enddetails %}
- Confirm setup in terminal:

~~~bash
docker version
kubectl version
~~~

{% include figure.liquid path="assets/img/courses/csc478/rancher/04.png" width="50%" zoomable=true %}

---

## Container runtimes

{% details What is a container runtime? %}

- A runtime is the low-level component responsible for managing container lifecycle: create, start, stop, and delete containers.
- It sits below tools like Docker CLI or Kubernetes.

{% enddetails %}
{% details Common runtimes %}


| Runtime      | Used By                           | Notes                                                                                                                                  |
| ------------ | --------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| `dockerd`    | Docker CLI                        | The original Docker daemon. Handles image builds, networks, volumes, and calls `containerd` internally for actual container execution. |
| `containerd` | Docker (since v1.11+), Kubernetes | A lightweight runtime daemon. Docker delegates runtime operations to containerd. Kubernetes uses it directly via the CRI.              |
| `cri-o`      | OpenShift, Kubernetes             | A runtime that interfaces directly with Kubernetes, focusing only on running containers (no builds or volumes).                        |
| `runc`       | containerd, cri-o                 | The actual binary that creates containers from OCI bundles. Very low-level.                                                            |

{% enddetails %}
{% details How Docker uses dockerd and containerd %}

- When you run `docker run`:
    - The Docker CLI talks to the `dockerd` daemon
    - `dockerd` builds images, manages networking, and oversees the container lifecycle
    - For actual execution, `dockerd` delegates container lifecycle tasks to `containerd`
    - `containerd` then uses `runc` to spawn the container
- In modern Docker, `containerd` is embedded and managed by `dockerd`. You rarely see it unless you use advanced tooling.

{% enddetails %}
{% details What about Nix* systems? %}

- **NixOS / nixpkgs**: use a purely functional package and system configuration model
- While container runtimes like `docker` and `containerd` are supported in Nix-based systems, users often prefer reproducible builds via `nix build`, `nix-shell`, or `nix develop`
- Containers on Nix:
    - You can build container images with `nix` and export them to Docker/OCI
    - Popular for CI/CD pipelines or reproducible scientific workflows 
    - Nix is not a container runtime, but complements them by ensuring immutable container definitions

{% enddetails %}
{% details tip Details %}

- Docker = monolith with features + embedded containerd. 
- Kubernetes = speaks directly to `containerd` or `cri-o`.

{% enddetails %}
---

## Kubernetes Readiness Check

~~~bash
kubectl get nodes
kubectl get pods -A
~~~

You’re ready for Week 2: Kubernetes deployments

---

## Docker Practice

- Complete section 2 and 3 of the [Docker lecture in CSC 468](https://www.cs.wcupa.edu/LNGO/courses/csc468/lectures/06-docker/) to quickly review and also to confirm that Docker of Rancher Desktop works properly. 

---

## What’s Next

- Week 2: Kubernetes core objects

  - Pods, Services, Deployments
  - Apply with `kubectl`
- Rancher Desktop gives you local Kubernetes + container runtime all in one

{% details tip Details %}

Familiar tasks from Docker Desktop now live in Rancher, ready for Kubernetes.

{% enddetails %}
