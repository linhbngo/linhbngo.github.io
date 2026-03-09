---
layout: post
title: "Redefining Rigor: From Selecting Talent to Developing Students in Computer Science"
date: 2026-03-08 12:00:00
description: How teaching and learning operate through different levels of assumptions
tags: cs-education, learning, assumptions
categories: technical
hidden: false
---

This essay is written in the context of computer science education. 

Teaching and learning are often treated as if they were the same process. Once they are conflated, it becomes easy to assume that good teaching 
should work equally well for all students, or that student success depends only on effort and ability. In reality, teaching and learning are 
related but distinct, and the gap between them is bridged by instructional design, motivation, prior preparation, and resilience. Instructors 
have the most direct control over instructional design, but they often build courses around assumptions about the other three factors, even 
though those vary substantially from student to student.

The effectiveness of instructional design depends heavily on how these assumptions are made. In a sense, 
this explains the difference between **selecting** and **developing** students, as suggested by 
[Thomas R. Guskey](https://tguskey.com/wp-content/uploads/PDK-14-Class-Rank2.pdf). In selecting students, we can make strong assumptions about 
students' prior preparation. Even if the students lack prior preparation, we can also assume that they have high levels of motivations and 
resiliency to catch up with the academic requirements. In other words, we are designing for the select few to reach their full  
potentials. On the other hand, in developing students, very few assumptions, if any, should be made regarding students. In theory, admissions 
and placement processes establish a baseline for preparation and motivation, if not resilience directly. In practice, however, that baseline 
is often crude. At best, it reflects the median; at worst, it reflects an average that hides meaningful individual variation.  

Recent advances in technology, especially the emergence of AI, have both widened these differences and made them harder to see. Students can 
now produce work that appears more polished, more complete, and more confident than their actual understanding might support. In regional public 
institutions, where developing students may matter more than selecting among the already advantaged, this creates a serious pedagogical challenge: 
how do we design instruction that relies on as few assumptions as possible about prior preparation, motivation, and resilience? Of course, no 
course can operate without assumptions. Learning still depends on preparation, motivation, and persistence. The deeper challenge, then, is not 
to ignore these factors but to cultivate them alongside the content itself. In the remainder of this essay, I explore these factors in turn and 
consider whether the supposed tradeoff between academic rigor and educational inclusion is as real as many assume. 

## Prior Preparation

Prior preparation for computer science is a complex issue. In this section, I want to focus on the theoretical and technical preparations prior to 
taking *any* CS courses. In theory, this should be addressed by prerequisites, and this assumption regarding prior preparation could certainly 
be made. However, are we selecting or developing students if we make this particular assumption given the following scenarios:

1) Due to an external factor (improper advising, family issue, health issue, etc), students are not taking the designated prerequisites in 
successive sequences and have large gaps between course sequences. 

2) Students are theoretically prepared but lack the technical preparations regarding new tools, since prerequisites often cover theories only. 
Students spend time outside class working and do not have the luxury of spending too much time self-learning. 

3) Students come in with transferred prerequisites and do not have the time or financial resources to retake the proper courses. 

4) And similar disruptions. 

The question, then, is not whether prior preparation matters. It does. If we care about academic rigor, we cannot simply discard prerequisites. 
The real issue is whether we treat prerequisites as guaranteed readiness or as necessary but imperfect indicators. My own view is that we should 
preserve prerequisite expectations while also providing enough scaffolding for students to rebuild missing preparation as they move through the 
course. I have done the following and anecdotally appear to help students catch up. 

1) **Be explicit and frequent about pre-requisites**: A single line on prerequisites in the course syllabus does not work. It provides students with 
the false sense of security: hey, I took the prerequisites. A prerequisite exam works, but in many cases, it only serves as a comprehensive notifier (*you are 
missing this and this and that*) without providing a solution and/or justification. Perhaps narratives that tie directly to the new contents and provides more 
explicit pointers to the missing knowledge (*We are learning A, you are probably missing B, which can be learned from source C*). 

2) **Distinguish between theoretical prerequisites and technical prerequisites**: Let's take Algorithm as an example course. Without continuous and 
effective prerequisites, it is quite possible that students can understand the algorithms but not implement them in an effective manner. Knowing the 
theory behind quick sort is not equivalent to knowing how to create a Java file from scratch, implement proper I/O procedure, and compile, test, and 
debug the resulting source code. 

3) **Distribute technical prerequisites**: Unlike knowledge prerequisites whose omission is likely due to atrophy or forgetfulness and can be addressed through 
reviews, technical prerequisites, when missing, indicate a long term absence of practical experience. This lack of practical experience cannot be 
addressed through simple reviews. Rather, instructional designs should not assume apparent mastery of skills and tools, and the process of scaffolding 
students with this experience should be frequent and spread across different courses. One example for me is the inclusion of container technologies and 
git usage across most, if not all, of the courses that I teach regardless of whether the students pursue a career in cloud-related subjects or not. In 
my opinion, being comfortable in the cloud is among the new professional skills that students must be equipped before joining the workforce. 

These approaches do not eliminate standards. They simply reduce the number of hidden assumptions embedded in the course. In fact, as technologies 
continue to evolve, it becomes less realistic to keep raising the bar of presumed preparation. A more practical approach is to maintain rigorous 
goals while surrounding students with enough scaffolding to catch up when needed. This does create additional work for instructors. However, this is also 
one area where AI can be genuinely useful. It can help generate prerequisite refreshers, low-stakes review exercises, worked examples, troubleshooting 
guides, and technical practice materials that augment the course without requiring instructors to build every support artifact by hand. 

## Motivation and Resilience

*We must give them hope, pride, a desire to fight. Yes, we need to make examples. But examples to follow.* — Commissar Danilov, *Enemy at the Gates*. 

I place motivation and resilience together because they are closely related and often reinforce one another. The scaffolding used to address gaps 
in prior preparation can also support both. When students begin to see a path forward, they are more likely to stay engaged. When they remain engaged 
long enough to recover from setbacks, that persistence can in turn strengthen their motivation.

Many students enter college with only a vague idea of what success after graduation might look like. Many choose computer science because they hope it 
will lead to stable and well-paying work. Yet hope alone is thin fuel, especially amid economic uncertainty or AI-driven job market shifts. Under such 
conditions, motivation and resilience become critical. Students must be motivated enough to engage seriously with the work, and resilient enough to 
continue when the work does not immediately go well. These qualities are related, but neither should be taken for granted.

If instructors want to cultivate motivation, the connection between course activities and meaningful outcomes must be made explicit. Students are often 
surrounded by vague encouragement, but vague encouragement rarely sustains effort. What helps more is a clear line between what they are learning and why 
it matters, whether in practice, theory, or professional life. This is one reason experiential learning can be powerful: it gives students a concrete sense 
that the work is real, useful, and connected to something beyond the classroom.

Resilience is harder to build, but it can be supported through design. Some students arrive with stronger habits of persistence than others, but resilience 
is not simply an inborn trait. It can be trained. At minimum, resilience means continuing after failure, confusion, or delay. Experienced practitioners do 
this almost automatically because they know that difficult problems usually yield with enough time, feedback, and iteration. Students do not yet have that 
confidence. For that reason, course materials and assessments should be difficult enough for students to struggle, but supported enough for them to recover 
and continue.

This is where alternative grading can be especially useful. Traditional grading often reduces performance to a one-time numerical judgment. Alternative 
approaches can instead preserve standards while giving students room to improve. One method I have used allows late work without penalty, but only by 
attaching additional work to later submission windows. An assignment has multiple versions with different due dates, and the later versions require more 
work. In this model, students who need more time can still earn the same grade, but they do so by completing more substantial work. Students who submitted 
early and performed poorly may also revise later by taking on the added requirements. Informal end-of-semester feedback suggested that students found this 
arrangement both motivating and fair: those who needed another chance appreciated the opportunity, while those who submitted early did not feel penalized 
for doing so.

The scaffolding approaches to facilitate the lack of prior preparation will also help. Rather than saying that *you are not yet ready to do this*, we can 
say *you could do this but you may need extra work to rebuild some missing foundations*. The first closes the door. The second keeps standards intact while 
leaving room for growth. 


## Academic Rigor versus Inclusiveness

As assumptions are relaxed, courses will become accessible to more students. Does this mean we are giving up academic rigor for the sake of inclusiveness. 
I want to make it clear that I reject this false binary choice between academic rigor and inclusiveness. The aspect of inclusiveness must not be 
viewed as *everyone can pass this class*, but rather, *there are enough pedagogical means available such that anyone who wishes to pass this class has a chance to do so*. 
The nuance here is that academic rigor can be defined differently depending on the degree of assumptions. An analogy of this matter 
can be seen through the lens of supercomputers: the difference between high performance computing (HPC) and high throughput computing (HTC). The distinction here 
is not about student quality, but about the assumptions embedded in the learning environment and the kind of success the course is designed to optimize.

High-Performance Computing (HPC) focuses on maximizing speed and peak capability for a single, tightly integrated, high-complexity computing task. HPC requires 
extremely fast interconnects, high-speed CPU, and large memory, all well tuned for intense synchronization. HPCs are often suited for problems that demand 
rapid, interdependent progress (e.g., tightly coupled parallel algorithms). HPC is an analogy for a strong assumption approach, where instructors assume students 
arrive with strong, uniform preparation, high intrinsic motivation, domain-specific resilience, and the ability to handle fast-paced, interdependent challenges 
without much scaffolding. The "hardware" (course design, pace, barriers) is optimized for peak performers who can keep up without friction. 

High-Throughput Computing (HTC) focuses on maximizing the total number of tasks completed over time, even if individual tasks take longer or proceed at uneven paces.
HTC requires lots of independent, loosely coupled resources, fault tolerance, and the ability to handle variable completion times and "pleasantly parallel" workloads 
(tasks that don't need constant inter-node chatter). HTC is well suited for large volumes of semi-independent subtasks where the goal is overall productivity across 
a diverse set (e.g., parameter sweeps, batch processing thousands of simulations). The idea of HTC aligns with inclusive pedagogy. The "workload" (core learning objectives/mastery) is the same, but tight synchronization assumptions are relaxed. Students proceed at different paces, with different 
"hardware configurations" (prior knowledge gaps, motivation levels, resilience in that domain, and support needs). We design for high overall throughput, where more 
students achieve competence over the semester through scaffolding, varied entry points, low-stakes practice, and flexibility through alternative grading.

This analogy illustrates that rigor isn't abandoned but redefined by design philosophy. In either case, academic rigor is preserved through different means: 
intensity and speed for the first (HPC/selection), and scale, resilience, and aggregate success for the latter (HTC/inclusion). The question, then, is not 
whether rigor should be preserved, but what kind of rigor our institutions are actually designed to serve. If the mission is only to identify those already prepared 
to succeed, then selection may be enough. But if the mission is to develop a broader range of students into capable practitioners, then rigor must be measured not 
only by speed and attrition, but also by how effectively a course helps students grow into competence without diluting the work itself.