---
layout: lecture
pretty_table: true
collection: csc231
title: "CSC 231: Computer Systems"
toc:
  - name: Course Information
  - name: Required Materials
  - name: Resources and Accessibility
  - name: Course Description
  - name: Prerequisites
  - name: Learning Objectives
  - name: Assessments and Grading
---

**Syllabus**

- **Instructor**: Linh B. Ngo
- **Office**: UNA 138
- **Office Hours Fall 2023**:
  - MWF : 11:00AM-12:00PM (in-person and online)
  - TR  : 11:00AM-12:00PM (online)
  - Online Zoom link is posted in D2L's announcement page
- **Email**: lngo AT wcupa DOT edu
  - I will respond to emails within 24 hours during the work week. 
- **Phone**: 610-436-2595

## Course Information
- The course runs from August 28, 2023 until December 11, 2023. 
- There are two sections for the courses:
  - CSC 231-02: In-person, MWF 12:00PM - 12:50PM Anderson Hall 315
  - CSC 231-03: Online asynchronous. For this section, students are 
  not expected to attend the online Zoom session. 
- Recordings for topics will be embedded in the class' website. 
- An introductory recording for the class will be made available in 
the course's D2L page. 

## Required Materials

- **Dive into Systems** by Suzanna J. Matthews, Tia Newhall, and Kevin C. Webb. 
  - A free open-source online version of this book is available 
  at [https://diveintosystems.org](https://diveintosystems.org/)

- **This is for DE section only:** You are expected to have a computer system that meets the minimum 
expectations as outlined by West Chester University Information 
Services on the [Recommended Student Computer Con../figuration](https://www.wcupa.edu/distanceEd/techRequirements.aspx). You need a working web-camera and microphone.


## Resources and Accessibility

- For general technical support, students can contact WCU IT 
HelpDesk at 610-436-3350 or via email: helpdesk@wcupa.edu.
- For distance education support, students can contact WCU Distance 
Education Services at 610-436-3373 or via email: distanceed@wcupa.edu.
- A Discord server will be created and invitation link made available 
inside D2L. Technical questions specific to online competition platforms 
used in the course can be sent via email to the instructor or posted on 
the Discord server.


## Course Description
In this course, we will learn fundamental concepts of modern computer systems. 
Unlike courses in Computer Organizations, Operating Systems, and Computer Architecture, 
we will be approaching these concepts from the perspective of system users rather than 
system builders. This will help us to understand how various computer system components, 
including CPU, memory, storage, and networking, work. Throughout the course, we will learn 
to use assembler language and C language to explore and observe specifically how computer 
systems interpret and execute programs. With the knowledge learned from this course, you 
will be able to build programs that are more efficient and have better performance.

## Prerequisites
- CSC 142: Computer Science II
- MAT 151: Discrete Mathematics

## Learning Objectives

### Course Student Learning Outcomes (CSLO)
  1. Be able to understand and manipulate the byte-representation of 
  different data types (int, float, char …)
  2. Be able to understand simple segment of Assembler codes.
  3. Be able to understand how processes are loaded into memory and 
  memory placements of stack, heap, and code within the virtual memory.
  4. Be able to understand the tradeoff in accessing data stored 
  in various memory hierarchical levels.
  5. Be able to understand how simple network communication works 
  within the Linux operating system.
  6. Be able to understand how to perform various debugging and 
  optimization techniques.
  7. Be able to understand how layered service designs and API 
  works from a systems programming perspective.
### CS Program Objectives (CSPO)
  1. Be able to apply theory, techniques, and methodologies to create and/or 
  maintain high quality computing systems that function effectively and reliably 
  in the emerging and future information infrastructure (CSLO 1, 2, 3, 4, 5, 6, 7).
### CS/ABET Program Outcomes (ABET)
  1. ABET 1: Analyze a complex computing problem and to apply principles of 
  computing and other relevant disciplines to identify solutions (CSLO 1, 2, 3, 4).
  2. ABET 2: Design, implement, and evaluate a computing-based solution to meet 
  a given set of computing requirements in the context of the program’s 
  discipline (CSLO 5, 6, 7).
  
### Certificate in Computer Security Program Outcomes
1. Analyze and resolve security issues in network and computer 
systems to secure an IT infrastructure

## Assessments and Grading

### Method of Evaluation

```{list-table} Method of Evaluation
:header-rows: 1
:name: method-of-evaluation

* - Assessment
  - \% of Final Grade
  - Course Objectives Assessed
  - Program Objectives Assessed
  - ABET Objectives Assessed
* - Programming Assignment Sets
  - 35\%
  - SLO 1, 2
  - CSPO 1
  - ABET 1
* - Labs
  - 25\%
  - SLO 3, 4, 5, 6, 7
  - CSPO 1
  - ABET 1, 2
* - Quizzes
  - 20\%
  - SLO 1, 5
  - CSPO 1
  - ABET 1, 2
* - Participation
  - 5\%
  - SLO 1, 2, 3, 4
  - CSPO 1
  - ABET 1
* - Exams
  - 15\%
  - SLO 2, 3, 4, 5, 6, 7
  - CSPO 1
  - ABET 1, 2
```

### Grade Scale


Refer to the [Grading Information section](https://catalog.wcupa.edu/undergraduate/academic-policies-procedures/grading-information/) 
section of the Undergraduate Catalog for description  of NG (No Grade), 
W, Z, and other grades. 

### Assessments

- Assignments: Writing and running programs written in C programming language, 
and demonstrating ability to read, understand, and modify Assembly/binary code.
  - Writing introductory C codes that demonstrate understanding of the language. 
  - Writing C codes that demonstrate understanding and the ability to manipulate
  the byte-representation of different data types (int, float, char …).
  - Demonstrate understanding by writing corresponding C codes that would translate
  to segment of Assembler codes given by the assignment.
  - Perform calculations to demonstrate understanding the tradeoff in accessing
  data stored in various memory levels.
  - Write a program that performs asynchronous communication tasks across a computer
  network.
- Labs: In the labs, students will learn to use command line tools and programs common
in the Linux operating systems for their programs. 
- Quiz and Exams: Multiple choice, code reading, and code correction are used to 
assess understanding of theoretical concepts necessary to support the tasks 
described in the assignments and labs. 

### Midterm and Final Exam

- The Midterm Exam will be disseminated in the last week of October. 
- Final Exam date will be scheduled according to the University’s Final 
Exam Schedule for Fall 2023.

### Lateness Policy:

- For lab submission, each late day (including weekends) will incur a 5\% penalty 
on the lab grade, up to a maximum of 50\% penalty. No late submission will be accepted 
after two weeks past the due date. 
- There is no late submission accept for assignment. Instead, the instructor will 
follow an mastery grading scheme approach as follows:
  - Each assignment has three versions 
    - The assignment's score is the highest score out of the three attempts. 
    - The versions contain additional work of the same difficulty level (just slightly!).
    - If you can't make it for the first version, keep going and try again. 
    - The final versions for all assignments are due on the last day of class. 

{!assets/text/policy.md!}
{!assets/text/distance_education.md!}
