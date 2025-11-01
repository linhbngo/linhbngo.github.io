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


# Optionally, you can add a table of contents to your post.
# NOTES:
#   - make sure that TOC names match the actual section names
#     for hyperlinks within the post to work correctly.
#   - we may want to automate TOC generation in the future using
#     jekyll-toc plugin (https://github.com/toshimaru/jekyll-toc).
toc:
  - name: Course Information
    # if a section has subsections, you can add them as follows:
    # subsections:
    #   - name: Example Child Subsection 1
    #   - name: Example Child Subsection 2
  - name: Required Materials
  - name: Prerequisites
  - name: Course Description
  - name: Learning Objectives
  - name: Assessments and Grading
  - name: Course Topics and Schedules
  - name: University Policies 
  - name: Resources for Student Success
  
# Below is an example of injecting additional post-specific styles.
# If you use this post as a template, delete this _styles block.
_styles: >
  .fake-img {
    background: #bbb;
    border: 1px solid rgba(0, 0, 0, 0.1);
    box-shadow: 0 0px 4px rgba(0, 0, 0, 0.1);
    margin-bottom: 12px;
  }
  .fake-img p {
    font-family: monospace;
    color: white;
    text-align: left;
    margin: 12px 0;
    text-align: center;
    font-size: 16px;
  }
---

# CSC 418/587: Modern Web Applications Using Server-Side Technologies 

{% include courses/instructor_info.md %}

## Course Information

- The course runs from December 16, 2024 until January 19, 2025. It is an 100% online asynchronous course. 

## Required Materials

- Jonathan Wrexler. **Get Programming with NodeJS**. Manning Publications, 2019. 
- You can get this textbook throuch Inclusive Access or from [the publisher's website](https://www.manning.com/books/get-programming-with-node-js) 

## Prerequisites

- Permission from the instructor for graduate students.
 
## Course Description

This 100% Distance Education course provides training in the area of building web
applications using Node.js (with Express, and MongoDB) for the backend and EJS for
the front-end user interface. JavaScript has been a client-side script programming
language until later in 2009 when Google combined it’s V8 search engine with Node.JS.
Since then, JavaScript has become a full-stack scripting language from the client-side to
the server-side. Starting from building a web site without programming, students will be
guided with hands-on labs and develop a website using Node.JS and EJS for the front-
end, and MongoDB for the backend.

## Learning Objectives

### Course Student Learning Outcomes (CSLO)

1. To describe the basic principles and structure about the Node.js architecture.
2. To develop server-side scripts applying the asynchronous web technologies.
3. To describe the principles of web app development using Node.js.
 

### BS in CS Program Objectives (CSPO):

1. Be able to apply theory, techniques, and methodologies to create 
and/or maintain high quality computing systems that function effectively 
and reliably in the emerging and future information infrastructure. (CSLO 1, 2)
2. Perform well in a computer science graduate program or a career in computer 
science and have the communication skills and quantitative/analytical skills necessary 
for career advancement. (CSLO 3)

### ABET Objectives (AO):

1. ABET 1: Analyze a complex computing problem and to apply principles of computing 
and other relevant disciplines to identify solutions. 
2. ABET 2: Design, implement, and evaluate a computing-based solution to meet a given 
set of computing requirements in the context of the program’s discipline. 
6. ABET 6: Apply computer science theory and software development fundamentals 
to produce computing-based solutions. 

## Assessments and Grading

### Method of Evaluation

| Assessment             | % of Final Grade | CSLO Assessed | CSPO Assessed | AO Assessed |
| ---------------------- | ---------------- | -------------------------- | -------------------------- | ------------------------- |
| Projects               | 50%              | 1, 2, 3                    | 1, 2                       | 1, 2, 6                   |
| Quizzes                | 50%              | 1, 3                       | 1, 2                       | 1,                        |


### Grade Scale:

<table
  data-toggle="table"
  data-url="{{ '/assets/json/grade_undergrad.json' | relative_url }}">
  <thead>
    <tr>
      <th data-field="grade">Grade</th>
      <th data-field="gpa">Quality Points</th>
      <th data-field="numeric">Numeric</th>
      <th data-field="interpretation">Interpretation</th>
    </tr>
  </thead>
</table>

{{ read_csv("docs/assets/data/grade_undergrad.csv") }}

Refer to the Undergraduate Catalog for description of NG (No Grade), W, & other grades.

### Assessments:

- Individual Assignments: Technical tasks or writing assignments that require significant reflection on procedural and technical 
aspects of software development and teamwork. 
- Team Project: Major development projects, most likely with external clients. 
- Class Participation: Being in class and participating in discussion of reading assignments. 
- Quizzes: Short online quizzes to test students on key concepts. 

### Lateness Policy:

Individual assignments that are late are assessed a 10% per day late penalty. Saturday and Sunday 
are each days. There is no late acceptance for team-based milestones. 

## Course Topics and Schedules 

This is subject to modification.


| Week       | Topic                                      | Assessments              |
| ---------- | ------------------------------------------ | ------------------------ |
|  1: Dec 16 | Install Docker | - |
|            | Setup Node.JS, VSCode, JavaScript | - |
|            | Node.js | Project 1 Assigned |
|            | EJS     | - |
|            | Express.JS | Quiz 1 | 
|  2: Dec 30 | MongoDB | Project 1 Due, Project 2 Assigned |
|            |                 | Quiz 2 |
|  3: Jan 06 | Building a user model  | Project 2 Due, Project 3 Assigned |
|  4: Jan 13 | Building an API (REST) | - |
|            |                 | Quiz 3 |
|     Jan 19 |                 | Project 3 Due |
