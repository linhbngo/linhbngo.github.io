---
layout: lecture
pretty_table: true
order: 1
title: Introduction
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
  - name: A motivational story
  - name: From vision to reality
  - name: Cloud Computing is the answer!
  - name: The big picture for this course!
---

## A motivational story

{% details A design for a up-and-coming unicorn startup %}


- Cryptocurrency miner startup!
    - Mine coins!
- Mining infrastructure:
    - `worker`, `rng`, `hasher`, `redis`, `webui`. 

{% include figure.liquid path="assets/img/courses/csc468/intro-cloud/ram-coin-1.png" width="50%" zoomable=true alt="Components of a coin mining infrastructure" %}

{% enddetails %}
{% details How does this work? %}

- `rng` produces a constant stream of random bytes
- `worker` issues a **GET** call to `rng` to acquire a number of random bytes. 
- `worker` issues a **POST** call to `hasher` to hash these bytes. 
- `worker` updates `redis` to indicate how many *coins* (loops) were done. 
- `webui` queries `redis` to acquire the rate, then compute and visualize the rate on a web page. 
- This is only the **design** stage

{% include figure.liquid path="assets/img/courses/csc468/intro-cloud/ram-coin-2.png" width="50%" zoomable=true alt="Connection types between components of a coin mining infrastructure" %}

{% enddetails %}
{% details Commonality %}

- This is a common general design for many commercial/production system. 
- Another name: `full stack`
    - front-end: `webui` 
    - back-end: `worker`, `hasher`, `rng`
    - database: `redis`

{% enddetails %}
---

## From vision to reality

{% details Implementation stage %}


- How does the startup implement their design?

{% include figure.liquid path="assets/img/courses/csc468/intro-cloud/ram-coin-3.png" width="50%" zoomable=true alt="Coin mining infrastructure with updated information on connection and language requirements" %}


{% enddetails %}
{% details Deployment stage %}


- Deploy one component per Linux machine!

{% include figure.liquid path="assets/img/courses/csc468/intro-cloud/ram-coin-4.png" width="50%" zoomable=true alt="Coin mining infrastructure with updated information on connection, operating systems, and language requirements" %}

- **Is this really everything?**


{% enddetails %}
{% details Reality of deployment in production environment %}


- Significant considerations need to be made to selection of hardware (computers and network), software, 
and other physical limitations (spaces, power, cooling).
    - Differences in software stacks for different components
    - Differences in network security requirements for different computers hosting different components
- Cost of personnel. 
- True on-site deployment would have hindered many new startups. 

{% include figure.liquid path="assets/img/courses/csc468/intro-cloud/ram-coin-5.png" width="50%" zoomable=true alt="What is the reality of deployment of infrastructure with updated information on connection, operating systems, and language requirements" %}


{% enddetails %}
{% details A more complete deployment %}


- Companies/businesses are relieved from having to manage both software and physical hardware setup. 
- Hardware configurations are feasible, but physical management is not required. 
- Dynamic scaling of resources

{% include figure.liquid path="assets/img/courses/csc468/intro-cloud/ram-coin-6.png" width="50%" zoomable=true alt="A example of a complete deployment of infrastructure with updated information on connection, operating systems, and language requirements" %}

{% enddetails %}
---

## Cloud Computing is the answer!

{% details What is cloud computing? %}


- [The National Institute of Standards and Technology (NIST/Department of Commerce) Definition of Cloud Computing](https://csrc.nist.gov/publications/detail/sp/800-145/final):
- Cloud computing is a model for enabling ubiquitous, convenient, on-demand network access to a shared 
pool of configurable computing resources (e.g., networks, servers, storage, applications, and services) 
that can be rapidly provisioned and released with minimal management effort or service provider 
interaction. 

{% include figure.liquid path="assets/img/courses/csc468/intro-cloud/ram-coin-7.png" width="50%" zoomable=true alt="A example of a complete deployment of infrastructure with updated information on connection, operating systems, and language requirements in the cloud" %}

- This cloud model is composed of 
    - Five essential characteristics 
    - Three service models, and 
    - Four deployment models.

{% enddetails %}
{% details NIST: Five essential characteristics of cloud computing %}


- C1. On-demand self-service
- C2. Broad network access
- C3. Resource pooling
- C4. Rapid elasticity
- C5. Measured service

{% include figure.liquid path="assets/img/courses/csc468/intro-cloud/cloud-computing-1.png" width="50%" zoomable=true alt="Five essential characteristics of cloud computing" %}

{% enddetails %}
{% details NIST: Enabling technologies (equal order of importance) %}


- Broadband networks and Internet architecture
- Data center technology
- Virtualization technology
- Web technology
- Multi-tenant technology

{% include figure.liquid path="assets/img/courses/csc468/intro-cloud/cloud-computing-2.png" width="50%" zoomable=true alt="Enabling technologies for cloud computing" %}

{% enddetails %}
---

## The big picture for this course!

{% details warning Perceived Challenges %}


- [Spring 2022's students response to survey](https://docs.google.com/document/d/1KBTX0v0yE8iAhJl_6QwAdYZR1tsGiVXnN79XIfgDHEg/edit?usp=sharing)
- [Spring 2023's students response to survey](https://docs.google.com/document/d/1-0uIfcCKC8AhH94xfAtZe7H_eAROgbYyaI_MpEz4-BM/edit?usp=sharing)
- [Spring 2024's students response to survey](https://docs.google.com/document/d/16l8ooIRWOImUV5yHxGvp-buHYrTsEY0QGW2QOSPEuEA/edit?usp=sharing)


{% enddetails %}
{% details Certificate in Cloud Engineering %}

- Under `Subbacc` section for Add/Change Program in RamPortal.
    - `Subbacc` means that you can get the certificate prior to getting your undergraduate degree. 
- CSC 331: Operating Systems
- CSC 335: Networking and Data Communications
- CSC 468: Introduction to Cloud Computing
    - Linux 
    - In-depth study on Docker/Docker Compose/CloudLab. 
    - In-depth understanding regarding container to container communication
- CSC 478: Cloud Engineering
    - Kubernetes, CD/CI

{% enddetails %}
{% details Course project and course progress: the big picture %}


- Project-driven course
- General project statement: Enhance the implementation and carry out the full stack deployment of a 
complex system with multiple components. 
- Throughout the course, you will learn about:
    - Theory behind **virtualization**. 
    - Modern data center technologies.
    - Modern cloud orchestration technologies. 
- Recurrent skills:
    - To be performed in similar way over various problems.
    - Linux-based system administration
    - Git repository. 
    - Deploying and managing a cloud infrastructure. 
- Non-recurrent skills (variable-component/open skills):
    - Be able to design a complete micro-service architecture, 
    including components for in-house development/integration. 
    - Be able to design and implement individual microservice
    using appropriate containerization solution. 


{% enddetails %}
