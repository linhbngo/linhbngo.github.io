---
layout: lecture
pretty_table: true
collection: csc568
title: "Syllabus: CSC 568 - Cloud Computing Fundamentals"
hide:
  - toc
toc:
  - name: General Information
  - name: Course Information
  - name: Required Materials
  - name: Resources and Accessibility
  - name: Course Description
  - name: Course Student Learning Outcomes (CSLO)
  - name: Prerequisites
  - name: Evaluation Policy
  - name: Course Schedules
---

# Syllabus: CSC 568 - Cloud Computing Fundamentals

## General Information

- **Semester**: Spring 2026
- **Class Meeting Time**: Tuesday, Thursday from 7:15PM to 8:30PM 

{!assets/text/instructor_info.md!}

---

## Course Information

- The course runs from January 21, 2026 until May 09, 2026. 
  - The distance learning modality of the course is 100% online synchronous. 
  - All class materials and recorded links to the lectures will be provided via D2L. 

---

## Required Materials:

- There is no required textbook for this course. Reading materials will be 
made available in D2L. 
- Access to a laptop or desktop computer is required for the learning 
activities in this course. 

---

## Resources and Accessibility:

- For general technical support, students can contact WCU IT 
HelpDesk at 610-436-3350 or via email: helpdesk@wcupa.edu.
- For distance education support, students can contact WCU Distance 
Education Services at 610-436-3373 or via email: distanceed@wcupa.edu.
- A Discord server will be created and invitation link made available 
inside D2L. Technical questions specific to online competition platforms 
used in the course can be sent via email to the instructor or posted on 
the Discord server.

---

## Course Description

This course provides an introductory overview to the technologies that enable cloud 
computing. Topics covered include basic concepts about cloud computing, and advanced 
technical concepts regarding virtualization and containerization. As a graduate level course, 
students are expected to demonstrate a deeper critical understanding of cloud technologies, evaluating trade-offs between different 
approaches and relating them to current research or industry practices. Projects will contain components such as scalability 
analysis, security considerations, or integration of recent scholarly or industrial advances.

---

## Course Student Learning Outcomes (CSLO)

1. Be able to formulate the definition of cloud computing based on 
essential characteristics, service models, and deployment models.
2. Be able to understand enabling technologies including virtualization, 
containerization, and orchestration.
3. Be able to develop various services and applications inside containers.
4. Be able to deploy and enable access to containers inside cloud infrastructure.
5. Be able to critically analyze strengths, limitations, and trade-offs of different cloud platforms and container technologies.
6. Be able to connect course concepts to research or cutting-edge industrial practices (e.g., through a literature survey or project extension).

### MS in CS Program Objectives (CSPO):
1. Be well prepared to enter a career.
2. Be able to apply their course learnings to research career in an industrial setting.
3. Be exposed to the latest, cutting-edge technology.

---

### Course Topics:

- Basic Concepts  
    - Introduction, Essential Characteristics, and Enabling Technologies
    - Service Models and Deployment Models
    - Cloud Infrastructure in Academic: CloudLab
- Virtualization
    - Introduction to Virtualization in Cloud Computing
    - KVM, Docker, Podman, and Singularity
- Containerization
    - CloudLab: Programmatically Deployment of Infrastructure
    - Container development: Docker and Dockerfile
    - Container development: Docker 
- Comparative analysis of containerization platforms (Docker, Podman, Apptainer)
- Survey of emerging research or industry practices in container runtime design, isolation models, and reproducibility. 

---

## Prerequisites

- CSC 535: Data Communications and Networking

---

## Evaluation Policy:

### Method of Evaluation

| Assessment     | % of Final Grade | Course Objectives Assessed | Program Objectives Assessed |
| -------------- | ---------------- | -------------------------- | --------------------------- |
| Assignments    | 30%              |         1,2,3              |             1               |
| Course Project | 30%              |         1,2,3              |             1               |
| Quizzes        | 10%              |         1                  |        1        |
| Exams          | 30%              |         1,2                |             1               |

### Grade Scale:

{{ read_csv("docs/assets/data/grade_grad.csv") }}

### Assessments:

Details on assessments will be made available on D2L. 

- Assignments: 
    - Accessing and deploying cloud infrastructures based on ready-to-run templates
    - Carrying out manual steps to spin up containers and manual setup services 
    inside containers
    - Writing bash scripts that automate the deployment processes
- Project: Design, implement, and deploy various services and applications inside small 
containers.
- Quizzes and Exams: Assessing understanding of theoretical concepts
necessary to support the tasks described in the assignments and projects.

### Lateness Policy:
Assignments that are late are assessed a 10% per day late penalty.
Saturday and Sunday are each days.

## Course Schedules

- Quizzes are typically disseminated once a week. 

{{ read_csv("docs/csc568/topics.csv") }}

---

{!assets/text/policy.md!}

---

{!assets/text/distance_education.md!}
