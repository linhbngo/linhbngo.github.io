---
layout: lecture
pretty_table: true
collection: csc478
title: "Syllabus: CSC 478 - Cloud Engineering"
toc:
  - name: General Information
  - name: Course Description
  - name: Course Student Learning Outcomes (CSLO)
  - name: Prerequisites
  - name: Required Text (either print or e-book)
  - name: Evaluation Policy
  - name: Course Schedules
---

# Syllabus: CSC 478 - Cloud Engineering

## General Information

- **Semester**: Fall 2026

{!assets/text/instructor_info.md!}

## Course Description

This course provides students with more in-depth understanding of 
advanced cloud computing technical concepts. Through the perspective of 
infrastructure-as-code and project-based learning activities, we will study 
how cloud computing orchestation works to enable the deployment of large-scale 
complex services in business and academic environments. 

## Course Student Learning Outcomes (CSLO)
  1. Be able to write programs that describe the deployment, installation, 
  and configuration of complex services in the cloud. 
  2. Be able to demonstrate understading of -as-a-service (networking, firewall, storage).
  3. Be able to develop a complex infrastructure that support a full-stack set of services 
  inside the cloud. 
  
### CS Program Objectives (CSPO):
  1. Be able to apply theory, techniques, and methodologies to create and/or 
  maintain high quality computing systems that function effectively and reliably 
  in the emerging and future information infrastructure (CSLO 1, 2, 3).
  2. Be able to work in teams, demonstrate ethical professionalism in their work, 
  and grow professionally while engaging in life-long learning (CSLO 2, 3).

### CS/ABET Program Outcomes (ABET):
  1. ABET 1: Analyze a complex computing problem and to apply principles of 
  computing and other relevant disciplines to identify solutions (CSLO 1).
  2. ABET 2: Design, implement, and evaluate a computing-based solution to meet 
  a given set of computing requirements in the context of the program’s 
  discipline (CSLO 2, 3).
  3. ABET 5: Function effectively as a member or leader of a team engaged in 
  activities appropriate to the program’s discipline (CSLO 2, 3).

## Prerequisites
- CSC 468: Introduction to Cloud Computing

## Required Text (either print or e-book):
There is no required text for this class. 

## Evaluation Policy:

### Grade Distributions

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
necessary to support the tasks decribed in the assignments and projects.

### Lateness Policy:
Assignments that are late are assessed a 10% per day late penalty.
Saturday and Sunday are each days.

{!assets/text/ai_policy.md!}
{!assets/text/policy.md!}

## Course Schedules

- Quizzes are typically disseminated once a week. 

{{ read_csv("docs/csc478/topics.csv") }}

