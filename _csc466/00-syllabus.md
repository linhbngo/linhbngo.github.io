---
layout: lecture
pretty_table: true
collection: csc466
course: CSC 466: Distributed and Parallel Computing
title: "CSC 466: Distributed and Parallel Computing"
toc:
  - name: General Information
  - name: Course Information
  - name: Required Materials:
  - name: Course Description
  - name: Prerequisites
  - name: Learning Objectives
  - name: Assessments and Grading:
  - name: Course Topics and Schedules
  - name: Bibliography
---

# CSC 466: Distributed and Parallel Computing

## General Information

- **Semester**: Spring 2025
- **Class Meeting Time**: MWF 12:00PM-12:50PM. 

{!assets/text/instructor_info.md!}


## Course Information

- The course runs from January 20, 2025 until May 5, 2025. It is an in-person course.


## Required Materials:

- We will utilize the following textbook in this course (freely available online via CC_BY license by the author):
  - ["Parallel Programming for Science and Engineering" by Victor Eijkhout (2017)](https://theartofhpc.com/pcse/index.html)

## Course Description
- This course will investigate issues in modern distributed platforms 
by examining a number of important technologies in the areas of 
distributed computing in computational and data-intensive problems.
- By the end of the course, each student should understand and be able 
to apply several specific tradeoffs for parallel application and algorithms 
development, performance, and management on a number of distributed platforms.

## Prerequisites
- Data structures and algorithms (CSC 241). 
- Computer systems (CSC 231). 
  - Working knowledge of C/C++ and Linux. 

## Learning Objectives

### Course Student Learning Outcomes (CSLO)
  1. Be able to identify data structures and algorithms to solve a 
  complex computational problem.
  2. Be able to implement data structures and algorithms to solve 
  a complex computational problem.
  3. Be able to develop extensive testing strategies to ensure 
  implementations work across edge cases
  4. Be able to work as a team to solve complex computation 
  problems under timing constraints
  5. Understand various critical components of a supercomputing 
  infrastructure.
### CS Program Objectives (CSPO):
  1. Be able to apply theory, techniques, and methodologies to create and/or 
  maintain high quality computing systems that function effectively and reliably 
  in the emerging and future information infrastructure (CSLO 1, 2, 3).
### CS/ABET Program Outcomes (ABET):
  1. ABET 1: Analyze a complex computing problem and to apply principles of 
  computing and other relevant disciplines to identify solutions (CSLO 1).
  2. ABET 2: Design, implement, and evaluate a computing-based solution to meet 
  a given set of computing requirements in the context of the program’s 
  discipline (CSLO 2, 3).


## Assessments and Grading:

### Grade Scale:

{{ read_csv("docs/assets/data/grade_undergrad.csv") }}

Refer to the [Grading Information section](https://catalog.wcupa.edu/undergraduate/academic-policies-procedures/grading-information/) 
section of the Undergraduate Catalog for description  of NG (No Grade), 
W, Z, and other grades. 

### Assessments:

| Assessment  | % of Final Grade  | Course Objectives Assessed | Program Objectives Assessed | ABET Objectives |
| ----------- | ----------------- | -------------------------- | --------------------------- | --------------- |
| Assignments |       30%         |         1,2,3,4,5          |             1               |        1,2      |
| Labs        |       20%         |         1,2,3,4,5          |             1               |        1,2      |
| Quizzes     |       20%         |         1,2,5              |             1               |        1        |
| Exams       |       35%         |         1,2,5              |             1               |        1        |


- Assignments: Writing and running programs and analyzing execution performances
  - Writing C codes that demonstrate understanding and the ability to:
    - develop and test OpenMP program using basic directives.
    - develop and test OpenMP programs using advanced directives. 
    - prepare and submit batch jobs to remote supercomputing systems. 
  - Writing C codes that demonstrate understanding and the ability to:
    - develop and test MPI programs using basic communication routines.
    - develop and test MPI programs using advanced communication routines. 
    - prepare and submit batch jobs to remote supercomputing systems.
- Lab: Design, implement, and deploy various components of high-performance 
computing infrastructures as part of a team.
- Quizzes and Exams: Assessing understanding of theoretical concepts
necessary to support the tasks decribed in the assignments and labs.

### Midterm and Final Exam:

- Midterm Exam will be disseminated the week before Spring Break. 
- Final Exam date will be scheduled according to the University's Final 
Exam Schedule for Spring 2025. 

### Lateness Policy:
Assignments that are late are assessed a 10% per day late penalty. 
Saturday and Sunday are each days.

{!assets/text/policy.md!}

## Course Topics and Schedules

- Quizzes are typically disseminated once a week. 


{{ read_csv("docs/csc466/topics.csv") }}

## Bibliography

1. High Performance Computing:Modern Systems and Practices. Sterling, T., Anderson, M., and Brodowicz, M., ISBN: 012320158X
2. High Performance Computing: Programming and Applications. Levesque, J. and Wagenbreth, G., ISBN: 9781420077056
3. Distributed Computing: Fundamentals, Simulations, and Advanced Topics. Attiya, H. and Welch, J., ISBN: 9780471453246
4. Elements of Distributed Computing. Garg, V., ISBN: 0471036005
5. Parallel Programming: Concepts and Practice. Schmidt, B.,
6. An Introduction to Parallel Programming. Pacheco. P., ISBN: 0123742609
7. Using MPI: Portable Parallel Programming with the Message-Passing Interface (Scientific and Engineering Computation). Gropp, W., Lusk, E., and Skjellum, A., ISBN: 0262527391
8. Programming Distributed Computing Systems: A Foundational Approach.  Varela, C. and Agha, G., ISBN: 0262018985
