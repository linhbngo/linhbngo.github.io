---
layout: lecture
pretty_table: true
collection: csc478
course: CSC478: Cloud Engineering
title: "Course Project: Multi-Pod Multi-Container Pipeline on Kubernetes"
toc:
  - name: Introduction
  - name: Example Project Idea
  - name: Milestone 1: Team Formation & Architecture (Design Only)
  - name: Milestone 2: Core Implementation:
  - name: Milestone 3: Persistence & Full Integration (Demo)
  - name: Constraints & Hints
---

# Course Project: Multi-Pod Multi-Container Pipeline on Kubernetes

---

## Introduction

{% details Motivation %}

The goal of this class is to equip students with not only theory but also 
technical skills that are applicable to real world problems. To accomplish 
this, we will follow a project-based learning approach, where students 
start with a top-down project idea and gradually acquire the necessary 
knowledge to implement this project over the duration of the course. 

{% enddetails %}
{% details Project idea %}

The project idea should evolve around a full stack pipeline that involves multiple pods with at least one of which contains multiple containers. 
The deployment of this pipeline will be carried out on Kubernetes, with consideration for authentication and authorization aspects. This deployment process will teach students the concept of infrastructure as code and improve their administrative automation and scripting 
skills. 

{% enddetails %}
---

## Example Project Idea

While groups are free to select their own project ideas, these selections need to reflect the complexity of the pipeline. To that end, we have the following template project idea: **Image Classification Pipeline on Kubernetes**

{% details Project Overview %}

Design and deploy a simplified image classification pipeline on Kubernetes. The system demonstrates multi-pod orchestration and possibly multi-container pods using sidecars. At minimum, include:

- Preprocessing Service (resizes/normalizes images)
- Inference Service (serves a pre-trained model)
- Storage Service (persists original/processed images and results)

{% enddetails %}
It is possible to have in-depth projects that veer away from the multi-pod/multi-container requirements. All project selections need to be approved by the professor. 

---

## Milestone 1: Team Formation & Architecture (Design Only)

{% details Goal %}

- Form a team, 
- Define the pipeline architecture, and 
- Make clear technical choices before building.

{% enddetails %}
{% details Requirements %}

- Form teams between 3-5 students. 
- Learn about your teammates' capabilities and define roles (Lead/PM, DevOps, Backend/Inference, Preprocessing, QA/Docs).
- Develop use cases and workflow: 
    - Write 2–3 user stories and draw data-flow diagram. 
    - Example:
        - User story: As a user, I upload an image and retrieve the predicted label
        - Data-flow diagram: showing upload → preprocessing → inference → storage → retrieval.
- Design K8s architecture:
    - Decide which app stages are separate Pods and where to use a multi-container Pod (e.g., inference + metrics sidecar).
    - Identify Service types (ClusterIP for internal, NodePort/LoadBalancer for external).
    - Decide which component will be scaled later (likely inference).
- Persistence Plan: What needs to be stored? Where? Sketch PVC/PV needs and directory layout.
- Risk & Test Plan: 
    - List top risks (e.g., model size, timeouts) and a basic test matrix (happy path, large image, invalid image).

{% enddetails %}
{% details Deliverables %}

- Technical report:
    - PDF format, 1-inch margin, 10-pts font size. 
- Content:
    - Front matter (names, title)
    - Overview (marketing!)
    - 3–4 page architecture brief, data-flow diagram, and descriptions of (if available)
        - Component list (Pods, optional sidecars), 
        - Service choices, scaling target
        - API contracts (endpoints, payload examples)
        - Persistence plan + initial test plan
    - Team charter (roles, meeting cadence, Definition of Done)

{% enddetails %}
---

## Milestone 2: Core Implementation:

{% details Goal %}

Stand up the pipeline with proper service discovery and resilience. No persistence yet.

{% enddetails %}
{% details What to build %}

- Pods & Services:
    - Create Pods (or directly Deployments) 
        - Example: Preprocessing, Inference, Storage (temporary/ephemeral for now).
- Add Services: ClusterIP for internal, and one external (NodePort/LoadBalancer).
- Deployments & Scaling:
    - Convert to Deployments for self-healing.
    - Example: Scale Inference to ≥3 replicas.
- Manually delete a Pod; verify automatic recreation.
- Multi-Container Pod:
    - Add a sidecar (e.g., metrics exporter or access logger) to one Deployment.
- Basic tests:
    - Example: Demonstrate an upload flowing through preprocessing → inference → storage endpoint (non-persistent).

{% enddetails %}
{% details Deliverables %}

- Project repository submission that includes: (repo + brief):
    - deployments/ and services/ YAMLs (clearly named)
    - Short README with:
        - `kubectl apply -f` instructions
        - How to access the external Service
        - Evidence of scaling & self-healing (screenshots/commands: kubectl get deploy,pods,svc, kubectl scale, pod deletion + recreate)
        - Sidecar rationale (2–3 sentences)

{% enddetails %}
## Milestone 3: Persistence & Full Integration (Demo)

{% details Goal %}

Add persistent storage, verify data survives restarts, and deliver a clean demo.

{% enddetails %}
{% details Adding final components %}

- Storage & Persistence:
    - Create PV/PVC for the Storage Service (or for a small DB if you choose).
        - Example: Persist uploaded images, processed outputs, and prediction results (e.g., JSON metadata).
    - Verification:
        - Restart/redeploy Pods and show persisted data remains accessible.
- Testing: 
    - Example: Include a small script or curl commands to demonstrate upload → preprocessing → inference → storage → retrieval.
- Final operational consideration:
    - Health/readiness probes where appropriate.
    - Resource requests/limits for inference pods (lightweight, realistic).
    - Basic logs/metrics evidence.

{% enddetails %}
{% details Deliverables %}

- Update project repository with manifests for storage/ YAMLs (PV/PVC, or StatefulSet if you go that route)
- Final end-to-end demo video (≤5 min)
- Final technical report
    - PDF format, 1-inch margin, 10-pts font size. 
    - Content:
        - Front matter (names, title)
        - Overview (marketing!)
        - 4–5 page (undergraduates) or 6-7 page (team containing graduate students)
            - Architecture recap, data-flow diagram (updates if changed)
            - Pod grouping & any sidecar choices
            - Services and routing
            - Scaling/self-healing results
            - Persistence design & verification steps
            - Known limitations + next steps

{% enddetails %}
## Constraints & Hints

- Prefer ClusterIP for internal comms; expose exactly one external entrypoint unless justified.
- Keep input data small and predictable; pin versions.
- If using AI-based services, start with a tiny pre-trained model (e.g., MobileNet-v2 or even a mock classifier) to focus on orchestration, not training.
- Test early with kubectl port-forward and curl before wiring the full flow.
- For grading reproducibility, ensure `kubectl delete -f . && kubectl apply -f .` cleanly reprovisions the stack.



