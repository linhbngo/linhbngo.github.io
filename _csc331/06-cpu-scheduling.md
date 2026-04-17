---
layout: lecture
pretty_table: true
collection: csc331

title: "CPU Scheduling"
toc:
  - name: What is CPU scheduling?
  - name: Basic Scheduling Algorithms (Non-preemptive)
  - name: Preemptive vs Non-preemptive
  - name: Multi-level Feedback Queue (MLFQ)
---

# CPU Scheduling

---

## What is CPU scheduling?

- The allocation of processors to processes over time
- Key to multiprogramming
- Increase CPU utilization and job throughput by overlapping I/O and computation
- Different process queues representing different process states 
(ready, running, block ...)
- Policies: Given more than one runnable processes, how do we choose which one to 
run next?

---

## Basic Scheduling Algorithms (Non-preemptive)

{% details Initial set of simple assumptions %}

1. Each job (process/thread) runs the same amount of time.
2. All jobs arrive at the same time.
3. Once started, each job runs to completion (no interruption in the middle).
4. All jobs only use the CPU (no I/O).
5. The run time of each job is known.

These are unrealistic assumptions, and we will relax them gradually to see 
how it works in a real system.


{% enddetails %}
{% details First performance metric %}

- **Average turn around time of all jobs**:

turn_around_time = job_completion_time - job_arrival_time


{% enddetails %}
{% details Algorithm 1: First Come First Serve/First In First Out(FCFS/FIFO) %}


| Job | Arrival Time | Service Time |
| --- | --- | --- |
| A | 0 | 3 |
| B | 0 | 3 |
| C | 0 | 3 |

- For FCFS, jobs are executed in the order of their arrival. 
- When jobs with same arrival time arrive, let's assume a simple alphabetic
ordering based on jobs' names. 

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| A | A | A |  |  |  |  |  |  |  |  |  |
|  |  |  | B | B | B |  |  |  |  |  |  |
|  |  |  |  |  |  | C | C | C |  |  |  |

- Average_turn_around_time = (3 + 6 + 9) / 3 = **6** 


{% enddetails %}
{% details Initial set of simple assumptions: first adjustment %}


1. ~~Each job (process/thread) runs the same amount of time.~~
2. All jobs arrive at the same time.
3. Once started, each job runs to completion (no interruption in the middle).
4. All jobs only use the CPU (no I/O).
5. The run time of each job is known.

{% enddetails %}
{% details FCFS/FIFO Performance %}


| Job | Arrival Time | Service Time |
| --- | --- | --- |
| A | 0 | 8 |
| B | 0 | 3 |
| C | 0 | 3 |


- For first come first server, jobs are executed in the order of their arrival. 
- When jobs with same arrival time arriva, let's assume a simple alphabetic
ordering based on jobs' names. 

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| A | A | A | A | A | A | A | A |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  | B | B | B |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  | C | C | C |  |  |


- Average_turn_around_time = (8 + 11 + 14) / 3 = **11**
- This is worse than the metric from the initial set of assumptions. 


{% enddetails %}
{% details Algorithm 2: Shortest Job First (SJF) %}


| Job | Arrival Time | Service Time |
| --- | --- | --- |
| A | 0 | 8 |
| B | 0 | 3 |
| C | 0 | 3 |


- For SJF, jobs are executed in the order of their arrival. 
- When jobs with same arrival time arriva, jobs with shorter service time 
are executed first. 

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| B | B | B |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  | C | C | C |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  | A | A | A | A | A | A | A | A |  |  |

- Average_turn_around_time = (3 + 6 + 14) / 3 = 7.67
- This is better than FCFS. 


{% enddetails %}
{% details Initial set of simple assumptions: second adjustment %}


1. ~~Each job (process/thread) runs the same amount of time.~~
2. ~~All jobs arrive at the same time.~~
3. Once started, each job runs to completion (no interruption in the middle).
4. All jobs only use the CPU (no I/O).
5. The run time of each job is known.

- Without the second assumption, SJF does not apply and we are back to FCFS only. 

{% enddetails %}
{% details FCFS/FIFO Performance %}


| Job | Arrival Time | Service Time |
| --- | --- | --- |
| A | 0 | 8 |
| B | 2 | 3 |
| C | 2 | 3 |


- For FCFS, jobs are executed in the order of their arrival time.
- When jobs with same arrival time arrive, let’s assume a simple 
alphabetic ordering based on jobs’ names. 

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| A | A | A | A | A | A | A | A |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  | B | B | B |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  | C | C | C |  |  |


- Average_turn_around_time = (8 + 9 + 12) / 3 = 9.67
- B and C suffer from a long waiting time, but A already got the CPU. 


{% enddetails %}
{% details Initial set of simple assumptions: third adjustment %}


1. ~~Each job (process/thread) runs the same amount of time.~~
2. ~~All jobs arrive at the same time.~~
3. ~~Once started, each job runs to completion (no interruption in the middle).~~
4. All jobs only use the CPU (no I/O).
5. The run time of each job is known.

{% enddetails %}
---

## Preemptive vs Non-preemptive

- Non-Preemptive Scheduling
    - Once the CPU has been allocated to a process, it keeps the CPU 
    until it terminates or blocks.
    - Suitable for batch scheduling, where we only care about the total 
    time to finish the whole batch.
- Preemptive Scheduling
    - CPU can be taken from a running process and allocated to another 
    (timer interrupt and context switch).
    - Needed in interactive or real-time systems, where response time 
    of each process matters.


{% details Second performance metric %}


- **Average response time of all jobs**:
    - The time from when the job arrives to when it is first scheduled. 

response_time = first_scheduled_time - job_arrival_time

{% enddetails %}
{% details Algorithm 3: Shortest Time-to-Completion First (STCF) %}

- Also known as **Preemptive Shortest Job First (PSJF)**

| Job | Arrival Time | Service Time |
| --- | --- | --- |
| A | 0 | 8 |
| B | 2 | 3 |
| C | 2 | 3 |


- For FCFS, jobs are executed in the order of their arrival time.
- When jobs with same arrival time arrive, let’s assume a simple 
alphabetic ordering based on jobs’ names. 

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| A | A |  |  |  |  |  |  | A | A | A | A | A | A |  |  |
|  |  | B | B | B |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  | C | C | C |  |  |  |  |  |  |  |


- Average_turn_around_time = (14 + 3 + 6) / 3 = 7.67
- This is better than FCFS. 

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| A | A |  |  |  |  |  |  | A | A | A | A | A | A |  |  |
|  |  | B | B | B |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  | C | C | C |  |  |  |  |  |  |  |


- Average_response_time = (0 + 0 + 3) / 3 = 1 


{% enddetails %}
{% details Algorithm 4: Round Robin (RR) %}


| Job | Arrival Time | Service Time |
| --- | --- | --- |
| A | 0 | 8 |
| B | 2 | 3 |
| C | 2 | 3 |


- All jobs are placed into a circular run queue.
- Each job is allowed to run for a time quantum `q` before
being preempted and put back on the queue. 
- Example: `q=1` 

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| A | A |  |  | A |  |  | A |  |  | A | A | A | A |  |  |
|  |  | B |  |  | B |  |  | B |  |  |  |  |  |  |  |
|  |  |  | C |  |  | C |  |  | C |  |  |  |  |  |  |


- Average_response_time = (0 + 0 + 1) / 3 = 0.33 
- The choice of `q` is important. 
    - If `q` becomes infinite, RR becomes non-preemptive FCFS.
    - If `q` becomes 0, RR becomes simultaneously sharing of 
    process (not possible due to context switching).
    - `q` should be a multiple of the timer interrupt interval

{% enddetails %}
{% details Initial set of simple assumptions: fourth adjustment %}


1. ~~Each job (process/thread) runs the same amount of time.~~
2. ~~All jobs arrive at the same time.~~
3. ~~Once started, each job runs to completion (no interruption in the middle).~~
4. ~~All jobs only use the CPU (no I/O).~~
5. The run time of each job is known.

{% enddetails %}
{% details (Almost) all processes perform I/O %}


- When a job is performing I/O, it is not using the CPU. 
In other words, it is blocked waiting for I/O to complete.
- It makes sense to use this time to run some other jobs. 

{% enddetails %}
{% details Jobs with I/O %}


| Job | Arrival Time | CPU Time | I/O |
| --- | --- | --- | --- |
| A | 0 | 5 | One per 1 sec |
| B | 0 | 5 | none |


- Normal STCF treating A as a single job

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| A | I/O | A | I/O | A | I/O | A | I/O | A |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  | B | B | B | B | B |  |  |

- Average_turn_around_time = (9 + 14) / 2 = 11.5
- Average_response_time = (0 + 9) / 2 = 4.5

- STCF treating A as 5 sub-jobs

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| A | I/O | A | I/O | A | I/O | A | I/O | A |  |  |  |  |  |  |  |
|  | B |  | B |  | B |  | B |  | B |  |  |  |  |  |  |


- Average_turn_around_time = (9 + 10) / 2 = 9.5
- Average_response_time = (0 + 1) / 2 = 0.5


{% enddetails %}
{% details Initial set of simple assumptions: No more assumption %}


1. ~~Each job (process/thread) runs the same amount of time.~~
2. ~~All jobs arrive at the same time.~~
3. ~~Once started, each job runs to completion (no interruption in the middle).~~
4. ~~All jobs only use the CPU (no I/O).~~
5. ~~**The run time of each job is known.**~~

- The fifth assumption is he worst assumption:
    - Most likely never happen in real life
    - Yet, without it, SJF/STCF becomes invalid. 

{% enddetails %}
{% details The question %}

How do we schedule jobs **without knowing** their run time
duration so that we can minimize **turn around time** and 
also minimize **response time** for interactive jobs?

{% enddetails %}
---

## Multi-level Feedback Queue (MLFQ)

- Invented by Fernando Jose Corbato (1926 - 2019)
- Ph.D. in Physics (CalTech)
- MIT Professor
- One of the original developers of Multics (Predecessor of UNIX)
- First use of password to secure file access on computers. 
- Recipient of the 1990 Turing Award (The Nobel prize in computing)


{% details Overview of MLFQ %}

- Learn from the past to predict the future
- Common in Operating Systems design. Other examples include 
hardware branch predictors and caching algorithms.
- Works when jobs have phases of behavior and are predictable.
- Assumption: Two categories of jobs
- Long-running CPU-bound jobs
- Interactive I/O-bound jobs


{% enddetails %}
{% details MLFQ: the queues %}


- Consists of a number of distinct **queues**, each assigned a 
different **priority level**.
- Each queue has **multiple** ready-to-run jobs with the **same** priority.
- At any given time, the scheduler choose to run the jobs in the **queue** 
with the highest priority
- If **multiple** jobs are chosen, run them in **Round-Robin**

{% include figure.liquid path="assets/img/courses/csc331/cpu-scheduling/cpu-scheduling-01.png" width="50%" zoomable=true %}


{% enddetails %}
{% details MLFQ's feedback rules 1 and 2 %}


- Rule 1: If Priority(A) > Priority(B), A runs and B doesn't
- Rule 2: If Priority(A) == Priority(B), RR(A, B)

{% details Does it work well? %}

{% include figure.liquid path="assets/img/courses/csc331/cpu-scheduling/cpu-scheduling-01.png" width="50%" zoomable=true %}

With only these two rules, A and B will keep alternating via RR, 
and C and D will never get to run.  

What other rule(s) do we need to add?  

{% enddetails %}
- We need to understand how job **priority** changes over time.

{% enddetails %}
{% details Attempt 1: How to change priority? %}


- Rule 3: When a job enter the system, it is placed at the 
highest priority (the top most queue).
- Rule 4a: If a job uses up an entire time slice while running, 
its priority is reduced (it moves down one queue).
- Rule 4b: If a job gives up the CPU (voluntarily) before the 
time slice is up, it stays at the same priority level.


{% enddetails %}
{% details Example %}


- System maintains three queues, in the order of 
priority from high to low: Q2, Q1, and Q0. 
- Time-slice of 10 ms

{% details info Initial: A single long-running job %}


{% include figure.liquid path="assets/img/courses/csc331/cpu-scheduling/cpu-scheduling-02.png" width="50%" zoomable=true %}


{% enddetails %}
{% details info Along came a short job %}


- Job A (Dark): long-running CPU intensive 
- Job B (Gray): short-running interactive
- Major goal of MLFQ: At first, since the scheduler does not 
know about the job, it first assumes that is might be a short 
job (higher priority). If it is not a short job, it will 
gradually be moved down the queues.

{% include figure.liquid path="assets/img/courses/csc331/cpu-scheduling/cpu-scheduling-03.png" width="50%" zoomable=true %}


{% enddetails %}
{% details info What about I/O? %}


- The interactive job (gray) only needs the CPU for 1 ms before 
performing an I/O. MLFQ keeps B at the highest priority before 
B keep releasing the CPU.
- What are potentially problems?

{% include figure.liquid path="assets/img/courses/csc331/cpu-scheduling/cpu-scheduling-04.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Problem 1: Starvation %}

- If new interactive jobs keep arriving, long running job will 
stay at the bottom queue and never get any work done. 

{% include figure.liquid path="assets/img/courses/csc331/cpu-scheduling/cpu-scheduling-05.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Problem 2: Gaming the system %}


- What if some industrious programmers intentionally write a 
long running program that relinquishes the CPU just before the 
time-slice is up (Job B). 

{% include figure.liquid path="assets/img/courses/csc331/cpu-scheduling/cpu-scheduling-06.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Problem 3: What if a program changes behavior? %}

- Starting out as a long running job
- Turn into an interactive job


{% enddetails %}
{% enddetails %}
{% details Attempt 2: Priority boost %}

- Rule 5: After some time period `S`, move all the jobs in the system to 
the topmost queue.

{% details success Problem: Starvation %}

Rule 5 help guaranteeing that processes will not be 
staved. It also helps with CPU-bound jobs that become interactive

{% include figure.liquid path="assets/img/courses/csc331/cpu-scheduling/cpu-scheduling-07.png" width="50%" zoomable=true %}

{% enddetails %}
{% details What S should be set to? %}

- S is considered a voodoo constants (John Ousterhout)
    - requires some form of magic to set them correctly. 
- Too high: long running jobs will starve
- Too low: interactive jobs will not get a proper share of the CPU. 

{% enddetails %}
{% enddetails %}
{% details Attempt 3: Better accounting %}


- Rewrite of Rule 4 to address the issue of gaming the system. 
- Rule 5: Once a job uses up its time allotment at a given level 
(regardless of how many time it has given up the CPU), its priority 
is reduced. 

{% include figure.liquid path="assets/img/courses/csc331/cpu-scheduling/cpu-scheduling-08.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Summary %}


- Rule 1: If Priority(A) > Priority(B), A runs (B doesn’t)
- Rule 2: If Priority(A) = Priority(B), RR(A, B)
- Rule 3: When a job enter the system, it is placed at the highest priority 
(the top most queue).
- Rule 4: Once a job uses up its time allotment at a given level 
(regardless of how many time it has given up the CPU), its priority 
is reduced. 
- Rule 5: After some time period S, move all the jobs in the system to 
the topmost queue.


{% enddetails %}
MLFQ observes the execution of a  job and gradually learns what type of job 
it is, and prioritize it accordingly. 

- Excellent performance for interactive I/O bound jobs: good response time.
- Fair for long-running CPU-bound jobs: good turnaround time without starvation.

- Used by many systems, including FreeBSD, MacOS X, Solaris, Linux 2.6, and Windows NT

