---
layout: lecture
pretty_table: true
collection: csc331

title: "Syllabus: CSC 331 - Operating Systems"
toc:
  - name: General Information
  - name: Course Description
  - name: Learning Objectives
  - name: Prerequisites
  - name: Required Text (either print or e-book)
  - name: Evaluation Policy
  - name: Course Schedules
---

# Syllabus: CSC 331 - Operating Systems

## General Information

- **Semester**: Fall 2025
- **Class Meeting Time**: TR 12:30PM-01:45PM. 

{!assets/text/instructor_info.md!}

## Course Description
This course will introduce three fundamental concepts in operating system (OS): Virtualization, 
Concurrency, and Persistence.

- In Virtualization, we learn how OS creates abstractions through which programmers can interact 
with the underlying hardware. Examples of these abstractions include processes, memory spaces, 
and CPU scheduling.

- In Concurrency, we learn about how OS supports sharing of physical resources among these 
abstractions. These include thread, lock, and semaphores.

- In Persistence, we learn about how OS enables the long term management of information, produced 
or required by computer programs, in a manner that persists beyond the scope or the 
duration of these programs.

Understanding how operating systems work will facilitate better understanding about how programs 
are run by the computer hardware. This will lead to more efficient, stable, and secure programs.



## Learning Objectives


### Course Student Learning Outcomes (CSLO)
  1. Be able to create and manipulate processes, manage run-time memory, 
  and read and write to file systems
  2. Be able to create and manage threads and navigate around the potential 
  issues in thread concurrency.
  3. Be able to implement architectural changes to an OS.

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
  3. ABET 5: Function effectively as a member or leader of a team engaged in 
  activities appropriate to the program’s discipline (CSLO 4, 5).

### Course Topics:

- Virtualization
    - Process 
    - CPU scheduling
    - Memory management 
- Concurrency
    - Threads
    - Locks and condition variables
    - Semaphores and deadlocks
- Persistence
    - Input/output
    - File systems
- Real-time OS and security issues

## Prerequisites

- Foundation of Computer Science (CSC 220)
- Computer Science III (CSC 240)
- Computer Organizations (CSC 242) or Computer Systems (CSC 231)
- Data Structures and Algorithms (CSC 241)

## Required Text (either print or e-book):

- **Operating Systems: Three Easy Pieces** by Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau.
    - The authors offer free downloadable PDF of all the book's chapters on [the book's website][ostep]. 

**xv6: a simple, Unix-like teaching operating system** by Russ Cox, Frans Kasshoek, and Robert Morris. 
    - The book is available as [a free PDF copy](https://pdos.csail.mit.edu/6.1810/2024/xv6/book-riscv-rev4.pdf).
    - The LaTEX source code of the book is available via [GitHub](https://github.com/mit-pdos/xv6-riscv-book.git).


## Evaluation Policy:

### Method of Evaluation

| Assessment     | % of Final Grade | Course Objectives Assessed | Program Objectives Assessed | ABET Objectives |
| -------------- | ---------------- | -------------------------- | --------------------------- | --------------- |
| Assignments    | 20%              |         1,2                |             1               |     1,2,3       |
| Lab            | 20%              |         1,2,3,4            |             1               |     1,2,3       |
| Quizzes        | 35%              |         1,2,3              |             1               |       1,3       |
| Exams          | 20%              |         1,2,3              |             1               |       1,3       |
| Participations |  5%              |         1                  |                             |                 |


### Grade Scale:

{{ read_csv("docs/assets/data/grade_undergrad.csv") }}

Refer to the [Grading Information section](https://catalog.wcupa.edu/undergraduate/academic-policies-procedures/grading-information/) 
section of the Undergraduate Catalog for description  of NG (No Grade), 
W, Z, and other grades. 


### Artifacts used to demonstrate Student Learning Outcomes:
- Assignments: In writing and running programs and analyzing execution performances, 
students will be assessed on SLO1 and SLO2.
  - Writing C codes that demonstrate understanding and the ability to:
    - create and manipulate processes.
    - manage run-time memory.
    - read and write to file systems. 
  - Writing C codes that demonstrate understanding and the ability to:
    - create and manage threads. 
    - navigate around the potential issues in thread concurrency. 
- Lab: Working as a team to modify existing codes in the xv6 OS to implement architectural 
  changes to the OS. 
- Quizzes and Exams: Students will be assessed on their understanding of theoretical concepts
necessary to support the tasks decribed in the assignments.
- Participation: A combination of attendance and in-class interaction. 


### Lateness Policy:
Assignments that are late are assessed a 10% per day late penalty.
Saturday and Sunday are each days.

{!assets/text/ai_policy.md!}
{!assets/text/policy.md!}

## Course Schedules

- Quizzes are typically disseminated once a week. 

{{ read_csv("docs/csc331/topics.csv") }}
