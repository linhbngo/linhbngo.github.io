---
layout: post
title: "A Good Engineering Habit: Knowing When To Stop"
date: 2026-06-13 12:00:00
description: ... and when to rollback. 
tags: engineering, simplicity, best-practice
categories: technical
hidden: false
---

As mentioned in a [previous essay](https://linhbngo.github.io/blog/2026/cursor/), with AI support, I have become a lot more productive in building various things such as experiment workflows, container frameworks for various classes, and automated grading scripts, to name a few. 

One notable example is [The One Ring](https://github.com/WCU-AIR/the-one-ring/tree/main), a container-based infrastructure where instructors and students can deploy containers customized for different classes such as Operating Systems, Parallel and Distributed Programming, and Web Development. This infrastructure will ensure that all students have the exact same setup as the instructors do, and that students have the ability to replicate this environment on their personal computing devices. With [an initial publication in CCSC Eastern](https://dl.acm.org/doi/10.5555/3801163.3801217), I was excited to continue expanding this work. More specifically, I was attempting to include [spack](https://spack.io/), one of the package management software for data centers, so that I can better organize all the various software packages for different classes. 

Am I over-engineering this setup? Spack is great for a university's supercomputer, but not so much for a course that only needs MPI. As I take one step back and look at other work, the sign of over-engineering is everywhere. While it is easy to blame the AI agents that seamlessly generate complex code and enable my grander ambitions, the responsibility ultimately stops with me. I am accountable for everything created, the elegant and the bloated alike. In this essay, I want to reflect on how I fall into these traps and identify a mindset that can help guide my engineering decisions back toward simpler and more intentional solutions.

## The Friction of a Simpler Solution

As I recall my train of thought for The One Ring, I realize that, ironically, the **complexity** came from my own desire to make things **simpler**. The core design of The One Ring relies on a base container with a collection of common software, from which course-specific containers install additional software as needed. However, as I began planning the expansion of the framework, I realized that advanced courses share very few commonalities. They would end up not using much of the base container's presets. To simplify the container structure for these advanced courses, I decided to enhance the base container with Spack and populate an externally mounted host directory with all necessary software packages. This sounded **simple and elegant in theory**.

Alas, it was not simple and elegant at all in practice. The initial Spack setup was straightforward enough. However, issues started to creep up when I began to install various packages. These include, but not limited to:

**Docker Volume or Host Mounted:** The initial AI-generated script went with a Docker Volume setup. In my opinion, this would limit the portability of the infrastructure and make it harder for students to reset or rebuild their containers. In the end, I decided to modify the generated Compose file to go back to a host-mounted directory. My "simplifying" solution had already created more decision paths down the line. 

**Unsupported Package:** I should have remembered this issue from my past dealings with Spack. As an open-source package management system, Spack provides a systematic way to program installation procedures, but it depends on the community to maintain and update the packages. Because the community's primary focus is large-scale computational work, packages outside that scope tend to be missing or outdated. Several packages for my Big Data Engineering and Web Development courses had to be installed either without Spack or via custom Spack scripts. Complexities were compounding.

**Practicality:** After working through these various issues, it was finally at the point when Spack is up and running. It turned out that Spack took a significant amount of time to download and compile these various packages and their respective dependencies. I hadn't experienced this latency when using Spack inside a multi-core supercomputer with a high-speed network. The reality is vastly different when running inside a localized container with limited cores and a wireless connection. I realized I had not arrived at a simpler engineering solution at all. Instead, I had traded the structural complexity of the original design for longer deployment times and a heavier storage and configuration burden on the user's side.

In the end, I am scrapping the vision of The One Ring altogether, and going back to a one-container-per-class design where everything is fully customized exactly as needed, no more no less. It is certainly not fancy, but it works with minimal fuss. 

## Macro versus Micro Engineering

In another recent work, I worked with a team of faculty and students to build and test a Discord chatbot that can answer students' questions via a LLM-augmented RAG backend. The students did a wonderful job building up the entire framework, and we were soon at the benchmarking and evaluation stage. 

I felt it was important to evaluate the entire framework in a setup mirroring a production environment. In this setup, a testing bot would send a question to the server, and the RAG bot would receive it, forward the query to the LLM backend, and send the generated result back to the Discord channel. Because we wanted to execute a rigorous engineering evaluation, we collected a wide array of parameters, including response time, accuracy, and token count. We evaluated accuracy using [DeepEval](https://deepeval.com/), an LLM-judge framework.

However, the evaluation process quickly slowed to a crawl. Our hardware was juggling too many resource-heavy procedures at once, such as loading the RAG's localized LLM models alongside the judge's own LLM models—compounded by their inherent processing delays. It dawned on me that in trying to be thorough, I was trying to measure everything simultaneously. Once I identified the bottleneck, the team pivoted to a different approach that decoupled the operational evaluation from the accuracy evaluation. In `operational evaluation`, we focused strictly on whether the workflow and UI functioned correctly, ensuring all distributed components—MinIO, Qdrant, the dashboard frontend, and the Discord backend—communicated as expected. For the `accuracy evaluation`, we bypassed the full infrastructure by adding a lightweight CLI/API interface. This allowed us to feed question-and-answer pairs directly to the LLM judge automatically. By breaking the problem down, the entire process became scriptable. We could automate the benchmark to run multiple times across different LLM model combinations in a statistically rigorous manner. Ultimately, we gathered enough comprehensive data just in time for a paper submission.

While this macro/micro separation is not new in engineering, how did I step into this issue? I think, as I was responsible for the final integration and validation of the entire system, I incorrectly brought the comprehensive system mindset into the evaluation of individual components. In other words, I was trying to set up a driving route to test whether my car would start up!

## The Mechanics of Restraint

From these experiences, I have mapped out a few personal principles to guide my workflow. Others who have walked this path likely have more. 

**The Labor Tax:** Before integrating AI into my workflow, I rarely ran into the over-engineering problem. This is mostly because my projects weren't as structurally sophisticated. In the past, I might have thought about using a tool like Spack, but I would have stalled out at the grueling stage of writing the initial automated configuration scripts from scratch. AI support removes that friction, rendering the building phase nearly effortless. Because the architecture is essentially *free* to construct, my brain accidentally assumes that long-term maintenance and deployment will be effortless too. I have to remind myself that building is cheap, but maintenance is an ongoing tax.

**The Right Mindset for the Right Abstraction:** Once the product gets to a certain level of *shine*, it is a bit tedious to dig down under the hood again. This is why it is easy for me to forget about the principle of mapping the appropriate level of engineering rigor to different levels of abstraction, especially when I work on large-scale systems with various components that possibly come from others. Ensuring proper evaluations are setup immediately as the localized components are developed is a good way to avoid issues *even when* this principle is forgotten. 

**The Freedom to Stop and Restart:** While AI makes it incredibly easy to slip into over-engineering, it also grants the welcomed ability to quickly recover. In both of my case studies, scrapping days of architectural work to start over would have felt devastatingly tedious if I had to manually rewrite all the mundane boilerplate code required to pivot. AI removes that friction. Knowing I can rebuild a simpler version in an afternoon changes my psychology. It allows me to look at my work critically without the weight of the sunk-cost fallacy. **Too much work has already been done** is no longer an excuse to keep a bad design.

## Conclusion

An engineering mindset fits perfectly with my natural habit of building things. However, I have to be careful not to let the momentum of building pull me down a rabbit hole of increasingly over-complicated architectures. The process of exploring these setups is always fun, and I learned a lot from the "somewhat wasted" efforts described above. But the real discipline was knowing when to stop before the system became too convoluted to rescue.

Having AI assistance means that almost any technical architecture is now quickly within reach. But just because I can easily manifest a complex engineering vision doesn't mean I should. Moving forward, my goal is to let restraint be the ultimate metric of a mature engineering mindset.