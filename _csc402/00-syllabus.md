---
layout: lecture
pretty_table: true
order: 1
title: "Syllabus"

toc:
  - name: General Information
  - name: Course Information
  - name: Learning Objectives
  - name: Course Topics and Tentative Schedule
  - name: Evaluation Policy
---

## General Information

- **Semester**: Fall 2026
- **Class Meeting Time**: MW 3:00PM-04:15PM. 
- **Meeting Location**: 25 University Ave 161

{!assets/text/instructor_info.md!}


## Course Information

This course aims to introduce students to apply programming knowledge and technical skills 
learned in previous CS classes to practical aspects of software engineering. This includes 
problem formulation, requirements engineering, architecture, design, implementation, integration, 
documentation and delivery of a software system. The goal will be for each student to have had a hand 
in building complete and useful applications that could be released for real-world use. This course 
is a highly interactive course, in which students are expected to fully participate in class-based 
activities and discussions. Students will also be expected to spend a significant amount of time on 
technical writing, presentations, and practical software development as part of a team project.
 
## Learning Objectives

### Course Student Learning Outcomes (CSLO)

  1. Understand various software development process models and their trade-off.
  2. Be able to work effectively as part of a team.
  3. Be able to communicate with clients and identify project requirements.
  4. Be able to design and implement software projects that satisfy a predetermined 
  set of requirements. 
  5. Be able to apply common practices in software development, including 
  version control, code review, and testing. 
  6. Be able to develop technical documentation.
  7. Be able to provide clear written reflection on various personal and technical 
  aspects of the software development process. 
  8. Understand various licenses and legal consideration in software development. 

### BS in CS Program Objectives (CSPO)

  1. Be able to apply theory, techniques, and methodologies to create 
  and/or maintain high quality computing systems that function effectively 
  and reliably in the emerging and future information infrastructure. (CSLO 1, 3, 4, 5)
  2. Be able to work in teams, demonstrate ethical professionalism in their 
  work, and grow professionally while engaging in life-long learning. (CSLO 3, 4, 5, 6)
  3. Perform well in a computer science graduate program or a career in computer 
  science and have the communication skills and quantitative/analytical skills necessary 
  for career advancement. (CSLO 2, 6, 8)

### ABET Objectives (APO)

1. ABET 1: Analyze a complex computing problem and to apply principles of computing 
and other relevant disciplines to identify solutions. 
2. ABET 2: Design, implement, and evaluate a computing-based solution to meet a given 
set of computing requirements in the context of the program’s discipline. 
3. ABET 3: Communicate effectively in a variety of professional contexts.
4. ABET 4: Recognize professional responsibilities and make informed judgments 
in computing practice based on legal and ethical principles.
5. ABET 5: Function effectively as a member or leader of a team engaged in 
activities appropriate to the program’s discipline.
6. ABET 6: Apply computer science theory and software development fundamentals 
to produce computing-based solutions. 


## Course Topics and Tentative Schedule

### Course Topics

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

### Tentative Schedule

- Week 1: Introduction
  - Reading:
    - OSTEP: Introduction chapters
    - xv6: Build and run xv6 in QEMU. Overview of source tree.
  - Lab: Set up xv6 build env on Docker
- Week 2: Processes
  - Reading:
    - OSTEP: Processes (Ch. 4–5)
    - xv6: proc.c, fork(), exec(), wait()
  - Lab: Modify fork() to track parent-child relationships or log system calls.
- Week 3: Context Switching
  - Reading:
    - OSTEP: Limited Direct Execution (Ch. 6), Context Switching (Ch. 7)
    - xv6: swtch.S, trap.c
  - Lab: Instrument context switch count
- Week 4: Scheduling
  - Reading:
    - OSTEP: Scheduling (Ch. 8–10)
    - xv6: Scheduler loop in proc.c
  - Lab: Implement Round-Robin or priority scheduler in xv6
- Week 5: System Calls
  - Reading:
    - OSTEP: System Calls (review)
    - xv6: syscall.c, usys.S, system call dispatch table
  - Lab: Add a new system call to xv6
- Week 6–7: Memory Abstraction
  - Reading:
    - OSTEP: Virtual Memory (Ch. 13–15)
    - xv6: vm.c, kalloc.c, trap.c
  - Lab: Modify memory allocation, track page usage
- Week 8: Midterm + Review
  - Reading:
    - OSTEP: Summary and midterm catch-up
  - Lab: Debugging walkthrough of trap handling
- Week 9–10: Memory Management
  - Reading:
    - OSTEP: Paging (Ch. 16–18), Swapping (Ch. 19)
    - xv6: Extend memory system or implement page replacement simulation
  - Lab: Write a user program that triggers allocation and observe sbrk()
- Week 11: File Systems
  - Reading:
    - OSTEP: File system intro + APIs (Ch. 35–38)
    - xv6: fs.c, file.c, bio.c, inode.c
  - Lab: Walk through inode/block logic, add logging or stats
- Week 12: File System Internals
  - Reading:
    - OSTEP: FS implementation (Ch. 39–41)
    - xv6: Add new file type or a pseudo device file
- Week 13: Synchronization
  - Reading:
    - OSTEP: Locks, Mutexes, Semaphores (Ch. 26–28)
    - xv6: spinlock.c, sleeplock.c
  - Lab: Add locking to critical sections in new system call
- Week 14: Concurrency Bugs
  - Reading:
    - OSTEP: Deadlock, Concurrency Bugs (Ch. 30–32)
    - xv6: Demonstrate deadlock through crafted syscall ordering
  - Lab: Implement deadlock detection or avoidance
- Week 15: A History of Unix, Linux, and Minix

## Evaluation Policy:

### Method of Evaluation

| Assessment             | % of Final Grade | Course Objectives Assessed | Program Objectives Assessed | ABET Objectives Assessed |
| ---------------------- | ----------------- | -------------------------- | --------------------------- | ------------------------ |
| Individual Assignments | 30%              | 1, 5, 7                    | 1, 3                        | 3, 6                     |
| Team Project           | 50%              | 1, 2, 3, 4, 5, 6, 7, 8     | 1, 2, 3                     | 1, 2, 3, 4, 5, 6         |
| Class Participation    | 5%               | 2                          | 2                           | 3                        |
| Quizzes                | 15%              | 1, 5, 7                    | 1                           | 3, 4                     |


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

{% include courses/policy.md %}


