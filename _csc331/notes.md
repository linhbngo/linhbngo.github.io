---
layout: lecture
pretty_table: true
collection: csc331
course: CSC 331: Operating Systems
title: "Notes"
---
15-Week Semester Outline (Sample)

Week 1: Introduction
Topics: What is an OS? Goals, abstractions, structure.

OSTEP: Introduction chapters

xv6: Build and run xv6 in QEMU. Overview of source tree.

Lab: Set up xv6 build env (Docker or Linux VM)

Week 2: Processes
OSTEP: Processes (Ch. 4–5)

xv6: proc.c, fork(), exec(), wait()

Lab: Modify fork() to track parent-child relationships or log system calls.

Week 3: Context Switching
OSTEP: Limited Direct Execution (Ch. 6), Context Switching (Ch. 7)

xv6: swtch.S, trap.c

Lab: Instrument context switch count

Week 4: Scheduling
OSTEP: Scheduling (Ch. 8–10)

xv6: Scheduler loop in proc.c

Lab: Implement Round-Robin or priority scheduler in xv6

Week 5: System Calls
OSTEP: System Calls (review)

xv6: syscall.c, usys.S, system call dispatch table

Lab: Add a new system call to xv6

Week 6–7: Memory Abstraction
OSTEP: Virtual Memory (Ch. 13–15)

xv6: vm.c, kalloc.c, trap.c

Lab: Modify memory allocation, track page usage

Week 8: Midterm + Review
OSTEP: Summary and midterm catch-up

Lab: Debugging walkthrough of trap handling

Week 9–10: Memory Management
OSTEP: Paging (Ch. 16–18), Swapping (Ch. 19)

xv6: Extend memory system or implement page replacement simulation

Lab: Write a user program that triggers allocation and observe sbrk()

Week 11: File Systems
OSTEP: File system intro + APIs (Ch. 35–38)

xv6: fs.c, file.c, bio.c, inode.c

Lab: Walk through inode/block logic, add logging or stats

Week 12: File System Internals
OSTEP: FS implementation (Ch. 39–41)

xv6: Add new file type or a pseudo device file

Lab: Modify block allocator or file metadata

Week 13: Synchronization
OSTEP: Locks, Mutexes, Semaphores (Ch. 26–28)

xv6: spinlock.c, sleeplock.c

Lab: Add locking to critical sections in new system call

Week 14: Concurrency Bugs
OSTEP: Deadlock, Concurrency Bugs (Ch. 30–32)

xv6: Demonstrate deadlock through crafted syscall ordering

Lab: Implement deadlock detection or avoidance

Week 15: Capstone Project
Options:

Add a system monitor syscall

Improve xv6 shell

Add user-level threading

Presentation + Code Review
