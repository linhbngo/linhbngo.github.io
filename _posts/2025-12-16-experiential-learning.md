---
layout: post
title: "Keeping up with the Rising Bar through Experiential Learning"
date: 2025-12-16 12:00:00
description: Knowledge and Skills, Why Not Both 
tags: experiential-learning, cs-education
categories: non-technical
hidden: false
---

I was listening to [Practical AI's](https://practicalai.fm/) *The AI engineering skills gap* podcast this afternoon, which raised two increasingly common themes in today's technology workforce: first, that employees are now evaluating candidates not only by what they know but also by what they can build, and second, that the expectations for entry-level positions now often approach those of mid level roles. These ideas are gaining broad traction. In September of this year, Coursera developed a [Skills Track](https://blog.coursera.org/introducing-coursera-skill-tracks/), a new solution to help learners track their proficiencies through verified skill paths. Similarly, Andrew Ng, founder of deeplearning.ai, argues in [Knowledge Is Great, Skills Are Greater](https://www.deeplearning.ai/the-batch/knowledge-is-great-skills-are-greater) that "for individuals who want to improve their job prospects, shifting the emphasis from gaining knowledge to gaining skills can be very helpful." While these discussions are often framed broadly, they are particularly salient in computer science and AI, where the ability to deploy working systems increasingly defines professional readiness.

At West Chester University (WCU), the Computer Science program has taken a proactive approach to incorporating skills-based training into our Computer Science undergraduate and graduate curricula while strengthening, rather than displacing, foundational CS theory. This integration is achieved through a deliberate, scaffolded introduction of experiential learning across all academic levels. 

## Scaffolded Experiential Learning

In Introduction to Programming I and II, basic industry-standard tools are integrated into our courses in a seamless manner and scaffolded. For example, **Git tools** are included throughout the courses by having programming assignments disseminated via [GitHub Classroom](https://classroom.github.com/). This allows students to build familiarity with version control systems while giving faculty the ability to store, organize, and implement auto-graders to reduce instructional overhead for programming tasks. These early design decisions ensure that students acquire technical fluency gradually, without overwhelming cognitive load, while developing habits and workflows that transfer directly to internships and professional environments.

Familiarity with using Git via command line interface for both Windows and non-Windows systems prepare students to pick up **Linux skills** and the ability to comfortably work within a terminal in `Computer Systems`, a upper sophomore level course. In other technical elective courses like `Operating Systems` and `Modern Web Applications`, students begin learning to use container-based learning environments that can be deployed on their own computers. Rather than requiring students to design these infrastructures from scratch, the courses intentionally focus on using and reasoning about production-grade containerized environments, mirroring how most engineers encounter such systems in practice. This approach has multiple advantages:
- Learning environments are consistent throughout all students' computers, significantly reducing technical issues. 
- Students become familiar with cloud-based container environments. This contributes toward hardening their fundamental cloud computing skills.
- Students become familiar with the idea of using pre-built infrastructures and reading relevant documentations, occasionally performing minor technical trouble-shooting.
- Students retain the ability to continue using these environments to learn on their own after the semester ends. 

## Project-based Experiential Learning

For advanced technical elective courses that deal with specific topics like Cloud Computing or Artificial Intelligence, we adopt a project-based learning approach. This is to ensure that students understand how to turn theoretical knowledge into practical application. In other words, we want students to not only know things but also be able to build things. 

For example, in `Introduction to Cloud Computing`, students start out with finding a project idea that requires them to build an end-to-end system infrastructure. The core requirement is that the service components of these infrastructures must be designed as cloud containers. The gradual lectures of the class will require students how to design and build the individual containers and integrate them all inside an actual Cloud environment, available through federally funded cloud platforms (CloudLab). This allows students access to high-performance enterprise-level resources at no additional cost. Together with the fundamental cloud computing knowledge, students learn how to write Dockerfile, build Docker images, and manage dependencies. They also take the first steps toward understanding how to manage multiple containers locally by using Docker Compose. 

The next class in the sequence, `Cloud Engineering`, teaches students the principles of cloud orchestration and cloud security. The spirit of the project is the same as the previous class, but this time students are required to deploy them on a live server, made possible through the resources of CloudLab. While not dealing directly with industry platforms like AWS and Google Cloud Platform, the students use the open-source tool Kubernetes. This knowledge can easily be transferred to other cloud platforms.  

## Final Capstone with external client or legacy self-project

The students’ learning journey culminates in a senior Capstone course. Since Fall 2024, the guiding principle of this course has been simple: give students sustained exposure to the kinds of ambiguity, scale, and accountability that characterize real-world software engineering. Projects are sourced either from external industry clients or are intentionally designed to be substantially larger and more complex than traditional academic assignments.

Students must engage in requirements negotiation, technical trade-offs, team coordination, and long-term system evolution. They have often encountered constraints and setbacks that cannot be resolved by following a prescribed rubric. Over multiple semesters, we have observed that as the course matures, the level of real-world ambiguity increases; paradoxically, this is also where the greatest student growth occurs. The resulting [final projects](https://www.cs.wcupa.edu/LNGO/courses/csc402/projects/) serve not only as academic deliverables, but as concrete evidence of students’ emerging professional maturity, a demonstration of their ability to build, integrate, and communicate complex systems in realistic contexts. By graduation, our students are not just ready to learn on the job, but they are ready to deploy code on they one. 

## Conclusion

As the computing workforce shifts toward skills-based evaluation and higher entry-level expectations, the distinction between knowing and doing continues to narrow. By intentionally embedding experiential learning throughout the curriculum, WCU’s Computer Science program prepares students not just to enter the workforce, but to contribute immediately and grow sustainably in a rapidly evolving field.