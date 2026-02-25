---
layout: lecture
pretty_table: true
collection: csc586
course: CSC 586: Linux System Administration and Security - Summer 2024 - 100% online asynchronous
title: "Introduction to Linux"
toc:
  - name: Linux, A Brief History
  - name: The course
---
# Introduction to Linux

## Linux, A Brief History

### 1.1. The dawn of computing: system operators


- First commercial computer by IBM: IBM 701 (1952)
    - Require system operators to help run the programs
- Second generation: IBM 704 (1956)
    - Incompatible with IBM 701
    - No support from IBM
    - No textbook/documentation
- IBM 701 system operators
    - Trained by IBM for 701
    - Encouraged by IBM to organize informal meetings to 
    share expertise


### 1.2. From single-purpose to time-sharing

- Concept of time-sharing: Operating System
- Allows computers to become generali-purposes (serving 
multiple users running different programs)
- Enables system operators to transition into the role of 
system administrators.
- MIT, General Electric (GE), and Bell Labs collaborate to create the first time-sharing system call Multics
- Multiplexed Information and Computing Service

### 1.3. The birth of UNIX

- Bell Labs left Multics in 1964 (over budget, behind 
schedule)
    - Ken Thompson, Rudd Canaday, Dennis Ritchie continued 
    working on Multics 
- Summer 1969
    - Ken Thompson’s wife and kids were out of town for a month
    - One week was assigned for each key components of UNIX (the operating system, the shell, the editor, and the assembler).
- UNIX
    - UNiplexed Information and Computing Service
    - An emasculated Multics
- By 1971: as, cal, cat, chdir, chmod, chown, cmp, cp, date, dc, du, ed …
- By 1973: 16 new UNIX installations (components)
    - C programming language (Dennis Ritchie)
    - Pipe (designed by Doug McIlroy, implemented by Ken Thompson)

### 1.4. A new era for UNIX

- Ritchie, D.M. and Thompson, K., 1973. **The UNIX time-sharing system.** 
ACM SIGOPS Operating Systems Review, 7(4), p.27.
- After 6 months, number of UNIX installation tripled. 
- Due to AT&T’s antitrust settlement in 1958, UNIX cannot be sold as a product, but Bell Labs 
still retains licensing right
    - Individual software and licenses must be shipped to others.
    - 1974: Berkeley UNIX (BSD - Berkeley Software Distribution - led by Robert Fabrey at University of California at Berkeley)
    - 1976: V6 (John Lions at University of New South Wales - Australia)
    - 1982: SunOS (Sun Microsystem by Bill Joy - graduate student of Robert Fabrey)
    - 1983: AT&T UNIX System V (after court-ordered divestiture of AT&T in 1983)

### 1.5. The rise of <s>Skywalker</s> system administrators"

- Managing general-purpose computing systems requires a different set of skills.
- Serving a wide variety of users and applications.
- Universities were early leaders in fostering system admin groups
    - Purdue, Utah, Colorado-Boulder, and SUNY Buffalo were the initial hotbeds
- Evi Nemeth: Mother of system administration
    - Graduate student administrative team.
- A system administrator:
    - <s>Jack of all trades</s>
    - **Rabid** jacks of all trades: Hardware, software, system configuration, programming …
- 1989: First edition of UNIX and Linux System Administration Handbook

### 1.6. The Birth of Linux

- Late 1990, UNIX was gaining ground everywhere …
- 1992: AT&T filed copyright lawsuit against BDSI and the Regents of University of California
- 1994: The lawsuit was settled and three files were removed from BSD code base.
    - Impact was lasting
    - Everyone moved to Microsoft Windows
- 1984: Andrew Tennenbaum of Vrije Universiteit in Amsterdam developed MINIX as a learning software for his students.
- 1992: Linus Torvalds, an undergraduate at University of Helsinki, Finland, developed his own OS called Linux, with 
inspirations from both UNIX and MINIX.
- UNIX administration skill sets applies directly to Linux

{% include figure.liquid path="assets/img/courses/csc586/01-intro/01.png" width="50%" zoomable=true %}{"Linux Announcement"} 

### 1.7. Post dot-com bubble burst

- Unix and Linux becomes more mainstream, as their TCO for computing servers was significantly lower than that of a Windows server. 
- It is not a war, but rather the right combination of Windows and Unix/Linux systems within an organization. 
- With its new CEO, Windows has been embracing Linux and open-source:
    - 2019: https://www.anandtech.com/show/14301/microsoft-build-day-1-windows-subsystem-for-linux-gets-more-linux
    - 2019: https://www.theverge.com/2019/5/6/18527870/microsoft-windows-terminal-command-line-tool
    - Fully integrated on Windows 11

### 1.8. Where will Linux be in the future?

- Cloud
- IoT (small devices )

---

## The course

### 2.1. Course progress

- We will follow the book, but not following the chapters in the book's order. 
- Rather, we will glean from the perspective of a normal user than eventually learn enough of Linux to become an administrators. 
    
### 2.2. Work environment

- Operating system: Linux
    - Most servers are remote, even when you are in the same data center. 
    - Remote access via terminal.
- Know your terminal, how to launch them?
    - Linux
    - Mac
        - Mac Terminal
    - Windows
        - Windows Terminal, or
        - MobaXterm
- As an admin, you need to know how to launch terminals on any computer. 
