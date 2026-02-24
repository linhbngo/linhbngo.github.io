---
layout: lecture
pretty_table: true
order: 1
title: Syllabus
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
  - name: General Information
  - name: Course Description
  - name: "Course Student Learning Outcomes (CSLO)"
  - name: Prerequisites
  - name: "Required Text (either print or e-book)"
  - name: Evaluation Policy
  - name: Course Schedules
---

# Syllabus: CSC 468 - Introduction to Cloud Computing

## General Information

- **Semester**: Spring 2026
- **Class Meeting Time**: TR 19:15AM-20:30PM. 
- **Location**: BPMC 101

{% include courses/instructor_info.md %}

## Course Description

This course provides an introductory overview to the technologies that enable cloud 
computing. Topics covered include basic concepts about cloud computing, and advanced 
technical concepts regarding virtualization and containerization.

## Course Student Learning Outcomes (CSLO)
  1. Be able to formulate the definition of cloud computing based on 
  essential characteristics, service models, and deployment models.
  2. Be able to understand enabling technologies including virtualization, 
  containerization, and orchestration.
  3. Be able to develop various services and applications inside containers.
  4. Be able to deploy and enable access to containers inside cloud infrastructure.
  
### CS Program Objectives (CSPO):
  1. Be able to apply theory, techniques, and methodologies to create and/or 
  maintain high quality computing systems that function effectively and reliably 
  in the emerging and future information infrastructure (CSLO 1, 2, 3, 4).
  2. Be able to work in teams, demonstrate ethical professionalism in their work, 
  and grow professionally while engaging in life-long learning (CSLO 3, 4).

### CS/ABET Program Outcomes (ABET):
  1. ABET 1: Analyze a complex computing problem and to apply principles of 
  computing and other relevant disciplines to identify solutions (CSLO 1, 2).
  2. ABET 2: Design, implement, and evaluate a computing-based solution to meet 
  a given set of computing requirements in the context of the program’s 
  discipline (CSLO 3, 4).
  3. ABET 5: Function effectively as a member or leader of a team engaged in 
  activities appropriate to the program’s discipline (CSLO 3, 4).

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
  - Container development: Docker Compose
- Infrastructure as Code:
  - Programmatic Deployment of Infrastructure: Ansible

## Prerequisites

- CSC 335: Data Communications and Networking I

## Required Text (either print or e-book)
There is no required text for this class. 

## Evaluation Policy:

### Method of Evaluation

| Assessment     | % of Final Grade | Course Objectives Assessed | Program Objectives Assessed | ABET Objectives |
| -------------- | ---------------- | -------------------------- | --------------------------- | --------------- |
| Assignments    | 30%              |         1,2,3              |             1               |        1        |
| Course Project | 30%              |         1,2,3              |             1               |        2        |
| Quizzes        | 10%              |         1                  |             1               |        1        |
| Exams          | 30%              |         1,2                |             1               |        1        |

### Grade Scale:

{{ read_csv("docs/assets/data/grade_undergrad.csv") }}

### Assessments:

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
    - Quizzes will be opened at the beginning of the class and typically last 10-15 minutes. 
    - Quizzes are available for the first 30 minutes of the class. If you are late, you can still 
    take the quiz, but the instructor will start the lecture 5 minutes after duration of the quiz. 
    - One lowest quiz will be dropped. There will be no quiz retake. 

{{ read_csv("docs/csc468/topics.csv") }}


{% include courses/policy.md %}


