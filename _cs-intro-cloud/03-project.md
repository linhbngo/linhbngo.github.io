---
layout: lecture
pretty_table: true
order: 1
title: Course Project
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

toc:
  - name: Introduction
  - name: Project Requirements
  - name: Project Deliverables
  - name: "Project Ideas (Suitable for 1 Person)"
---

# Course Project

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

{% details Perception %}

This class differs from other classes. We are focusing on the system 
infrastructure aspect of cloud computing. Therefore, software implementation 
is somewhat secondary. 

{% enddetails %}
The project idea should evolve around a full stack deployment of an 
an application framework that involves multiple components (at least two or more). 
In a realistic deployment, these components will be setup on different physical 
computers and communicate with one another via network protocols. The deployment 
process of these components, in this class, will teach students the concept of 
infrastructure as code and improve their administrative automation and scripting 
skills. 

{% enddetails %}
---

## Project Requirements

{% details General requirements %}

- All projects will be done using containerization. No direct physical installation 
will be accepted under any circumstances. 
- During development, projects can be done on personal computers using Docker Desktop. 
However, final project demonstration must be carried out on CloudLab. 
- **Team Size**: 1 member

{% enddetails %}

{% details C-level technical requirements %}

- Architecture: Minimum of two components (e.g., 1 Web App + 1 Database, or 1 Producer + 1 Consumer).
- Implementation: Simple docker-compose setup connecting these two services.
- Constraint: You must write at least one custom Dockerfile (you cannot just link two existing public images 
like WordPress + MySQL; you must build at least one part of the stack).
- Documentation: Detailed README.md explaining how to launch the stack.

{% enddetails %}

{% details B-level technical requirements %}

- Everything from the C-level requirements  
- Registry: Push your custom image to the Docker Hub registry (public or private).
- CI/CD: Implement a GitHub Actions pipeline that builds your custom image automatically upon a push to the repository.
- Automation: The CloudLab deployment must pull the image from the registry rather than building it locally. 
- Documentation:  Detailed README.md explaining how the stack was created and how to launch the stack.

{% enddetails %}

{% details A-level technical requirements %}

- Full CI/CD Loop: The GitHub Action must not only build the image but trigger a 
deployment update on the CloudLab runner (Self-Hosted Runner) so the running container updates live.
- Security Best Practices: Implement Defense in Depth features from Lecture 12:
    - Run the container as a non-root user.
    - Drop unused Linux capabilities (e.g., CAP_SYS_ADMIN) in the Compose file.
    - Implement resource limits (CPU/Memory) in the Compose file to demonstrate cgroup understanding  
- Documentation:  Extensive README.md explaining how the stack was created, explanation of technical justification, and 
how to launch the stack.Extensive discussion of these technical implementations in the README.md.
- I want this project to be something that will wow your technical interviewers. 

{% enddetails %}

---

## Project Deliverables

All project deliverables will be uploaded in a public repository that is also a CloudLab launch repository. 
Proper folder organization is paramount and will be taken into consideration for grading purposes. 

{% details Deliverable 1 %}

The repository should contain the followings:

- Your professional resume (no page limit).
- First sections of your `README.md` file:
    - Vision: A diagram showing your 2 components and how they talk to each other (e.g., REST API, TCP).
    - Proposal: Briefly describe which base images (e.g., Python, Node, Alpine) you plan to use. 

{% enddetails %}
{% details Deliverable 2 (tentatively after Spring Break) %}

The repository is updated with all the latest progress of your project (Dockerfiles, scripts, compose files, etc)

- Update the next sections of `README.md` file:
    - Build Process: Explain your Dockerfile line-by-line. Why did you choose that base image?.
    - Networking: Explain how your containers communicate (e.g., Bridge network, DNS resolution by container name)

{% enddetails %}
{% details Deliverable 3 %}

- Repository with all necessary files for deployment on Cloud Lab. 
    - A 5-minute recording demonstrating a live deployment demo. 
- Final Report: Complete documentation in `README.md`. 

{% enddetails %}
{% details Documentation Requirements (strict) %}

- `READMD.md` with proper Markdown syntax only. No other format will be considered.  
- Correct grammar, vocabulary, and clear and concise sentences are required. 

{% enddetails %}

---

## Project Ideas (Suitable for 1 Person)

To keep the workload manageable, consider these simple architectures:

{% details The Visitor Counter %}

- Component 1 (Python/Node): A simple web server that displays "Visitors: X".
- Component 2 (Redis): A database storing the integer X.
- Infrastructure Challenge: Ensure the Python app crashes gracefully if Redis is not ready (health checks).

{% enddetails %}
{% details The Text Hasher (Async) %}

- Component 1: A script that generates random strings every 5 seconds.
- Component 2: A script that calculates the MD5 hash of those strings and logs them to a volume.
- Infrastructure Challenge: Use a shared Docker Volume so both containers can access the log file.

{% enddetails %}
{% details The Static Site + API %}

- Component 1 (Nginx): Serves a static HTML file.
- Component 2 (Go/Python): A backend API that the HTML file queries via Javascript.
- Infrastructure Challenge: Configure Nginx as a reverse proxy to the backend container.
{% enddetails %}
