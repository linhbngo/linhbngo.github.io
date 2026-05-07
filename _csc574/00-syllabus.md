---
layout: lecture
pretty_table: true
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
  - name: Learning Objectives
  - name: Required Learning Materials
  - name: Assessments and Grading
  - name: Course Topics and Schedules (subject to change)
  - name: University Policies
  - name: Resources for Student Success
---

## General Information

- **Semester**: Summer 2026

{% include courses/instructor_info_summer.md %}

- The course runs from May 11, 2026 until June 14, 2026. It is a fully online course. 
  - The course is 100% asynchronous. 
  - All class materials and recorded links to the lectures will be provided via D2L. 

## Course Description

In this course, students will study the emerging field of tiny machine learning (tinyML). This 
field is at the intersection of machine learning (ML) applications and embedded 
devices/microcontrollers. It requires both software and embedded-hardware knowledge. More 
specifically, students will follow a hands-on learning approach with training and optimizing ML models 
in such ways that they are deployable onto tiny microcontrollers. The course will involve work with 
an [Nano 33BLE sense microcontroller Rev 2](https://store-usa.arduino.cc/products/nano-33-ble-sense-rev2). 


## Learning Objectives

### Course Student Learning Outcomes (CSLO)
  1. Understand fundamental concepts of machine learning.
  2. Be able to apply programming tools in training, optimizing, and inferencing of ML models.
  3. Be able to interact with microcontrollers.
  4. Be able to deploy ML models on microcontrollers.
  
### MS in CS Program Objectives (MSPO):
  1. Be well prepared to enter a career.
  2. Be exposed to the latest, cutting-edge technology.


## Required Learning Materials

There is no textbook requirement for this class. However, students are required to purchase an 
[Nano 33BLE Sense Microcontroller Rev 2](https://store-usa.arduino.cc/products/nano-33-ble-sense-rev2). 
The cost of the kit is $38.70, not including shipping. If you get this from Amazon, you might be able to 
get it via free shipping. 


## Assessments and Grading

### Grade Scale

<table
  data-toggle="table"
  data-url="{{ '/assets/json/grade_grad.json' | relative_url }}">
  <thead>
    <tr>
      <th data-field="grade">Grade</th>
      <th data-field="gpa">Quality Points</th>
      <th data-field="numeric">Percentage</th>
      <th data-field="interpretation">Equivalent Interpretation</th>
    </tr>
  </thead>
</table>

D grades are not used. Refer to the Graduate Catalog for description of NG (No Grade), W, & other grades.

### Method of Evaluation

| Assessment          | % of Final Grade  | CSLO    | MSPO |
| ------------------- | ----------------- | ------- | ---- | 
| Quizzes             |       30%         | 1,2     | 1,2  |
| Labs                |       30%         | 1,2,3,4 | 1,2  |
| Project             |       40%         | 1,2,3,4 | 1,2  |

### Assessments

- Quizzes: Be able to recall key theoretical and technical concepts.
- Labs: Be able to work on complex lab problems with partial instruction.
- Projects: Be able to carry out an end-to-end development and deployment of a ML application on a microcontroller. 

### Lateness Policy

Labs/Project milestones that are late are assessed a 10% per day late penalty. 
Saturday and Sunday are each days.


## Course Topics and Schedules (subject to change)

| Week       | Topic                                | Assessments              |
| ---------- | ------------------------------------ | ------------------------ |
|  1         | Introduction                         |            -             |
|            | Machine Learning Paradigm            | - |
|            | Building Blocks of Deep Learning     | - |
|            | Exploring Machine Learning Scenarios | - |
|            | Building a Computer Vision Model     | - |
|            | Responsible AI                       | - |
|            | AI Lifecyle and ML Workflow          | - |
|  2         | ML on Edge: Tensorflow Lite and Quantization | - |
|            | ML on Edge: Post Training Quatization | - |
|            | ML on Edge: Quantization Aware Training | - |
|            | ML on Edge: Model Conversion and Deployment | - |
|            | Keyword Spotting                     | - |
|            | Visual Wake Words                    | - |
|            | Anomaly Detection                    | - |
|  3         | Data Engineering                     | - |
|            | Setting up hardware                  | - |
|            | Embedded hardware and software       | - |
|            | Tensorflow Lite Micro                | - |
|            | Keyword Spotting and Dataset Engineering | - |
|            | Visual Wake Words/Person Detection   | - |
|  4         | Gesture Recognition                  | - |
|            | Introduction to Project              | - |
|            | Responsible AI Deployment            | - |
|            | DNN Compression                      | - |
|  5         | Scaling TinyML                       | - |
|            | History of TinyML                    | - |
|            | ML Hardware Acceleration             | - |


{% include courses/policy.md %}


{% include courses/distance_education.md %}
