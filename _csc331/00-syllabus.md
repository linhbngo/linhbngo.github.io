---
layout: lecture
pretty_table: true
collection: csc331

title: "Syllabus"
toc:
  - name: General Information
  - name: Course Description
  - name: Learning Objectives
  - name: Prerequisites
  - name: Required Text (either print or e-book)
  - name: Evaluation Policy
  - name: Course Schedules
---


## General Information

- **Semester**: Fall 2026
- **Class Meeting Time**: TR 12:30PM-01:45PM. 
- **Meeting Location**: 25 University Ave 162

{% include courses/instructor_info.md %}

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



## Prerequisites

- Foundation of Computer Science (CSC 220)
- Computer Science III (CSC 240)
- Computer Organizations (CSC 242) or Computer Systems (CSC 231)
- Data Structures and Algorithms (CSC 241)

## Required Text (either print or e-book):

- **Operating Systems: Three Easy Pieces** by Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau.
    - The authors offer free downloadable PDF of all the book's chapters on [the book's website][ostep]. 

**xv6: a simple, Unix-like teaching operating system** by Russ Cox, Frans Kasshoek, and Robert Morris. 
    - The book is available as [a free PDF copy](https://pdos.csail.mit.edu/6.1810/2025/xv6/book-riscv-rev5.pdf).
    - The LaTEX source code of the book is available via [GitHub](https://github.com/mit-pdos/xv6-riscv-book.git).



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

*Quizzes are typically disseminated once a week.*

## Evaluation Policy:

### Method of Evaluation

| Assessment     | % of Final Grade | Course Objectives Assessed | Program Objectives Assessed | ABET Objectives |
| -------------- | ---------------- | -------------------------- | --------------------------- | --------------- |
| Assignments    | 20%              |         1,2                |             1               |     1,2,3       |
| Lab            | 20%              |         1,2,3,4            |             1               |     1,2,3       |
| Quizzes        | 35%              |         1,2,3              |             1               |       1,3       |
| Exams          | 20%              |         1,2,3              |             1               |       1,3       |
| Participation  |  5%              |         1                  |                             |                 |


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
necessary to support the tasks described in the assignments.
- Participation: A combination of attendance and in-class interaction. 

### Lateness Policy:
Assignments that are late are assessed a 10% per day late penalty.
Saturday and Sunday are each days.

{% include courses/policy.md %}

