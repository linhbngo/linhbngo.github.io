---
layout: lecture
pretty_table: true
collection: csc466
course: CSC 466: Distributed and Parallel Computing
title: "Computing Environments"
toc:
  - name: Overview
---
# Computing Environments

{% details Preparation %}

In preparation for this lecture, you are to:

- Follow the [instructions to set up Docker Desktop](https://cs.wcupa.edu/LNGO/courses/workshops/docker-environment/#1-quick-setup-reminder)
- If you are not familiar with Docker, quickly go through the [Introduction to Docker workshop](https://cs.wcupa.edu/LNGO/courses/workshops/intro-docker/)
- Follow the [instructions to set up the parallel computing environment for CSC466](https://cs.wcupa.edu/LNGO/courses/workshops/docker-environment/#3-csc466-distributed-and-parallel-programming)

{% enddetails %}
## Overview

{% details General architecture %}


- One head node: where users interact with the backend computing cluster
- Two compute nodes: where actual computations are carried out (in a traditional HPC model)

{% include figure.liquid path="assets/img/courses/csc466/parallel-environment/architecture.jpg" width="50%" zoomable=true %}

{% enddetails %}
