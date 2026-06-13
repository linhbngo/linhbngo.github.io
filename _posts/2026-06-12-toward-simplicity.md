---
layout: post
title: "A Good Engineering Habit: Knowing When To Stop"
date: 2026-06-10 12:00:00
description: ... and when to rollback. 
tags: engineering, simplicity, best-practice
categories: technical
hidden: true
---

I like to build things. And as mentioned in a [previous essay](https://linhbngo.github.io/blog/2026/cursor/), with AI support, I have become a lot more productive in building various things such as experiment workflows, container frameworks for various classes, and automated grading scripts, to name a few. 

One notable example is [The One Ring](https://github.com/WCU-AIR/the-one-ring/tree/main), a container-based infrastructure where instructors and students can deploy containers customized for different classes such as Operating Systems, Parallel and Distributed Programming, and Web Development. This infrastructure will ensure that all students have the exact same setup as the instructors do, and that students have the ability to replicate this environment on their personal computing devices. With [an initial publication in CCSC Eastern](https://dl.acm.org/doi/10.5555/3801163.3801217), I had excited to continue expanding this work. More specifically, I was attempting to include [spack](https://spack.io/), one of the package management software for data centers, so that I can better organize all the various software packages for different classes. 

And then it hits me, am I over-engineering this setup? Spack is great for a university's supercomputer, but not so much for a course that only needs MPI. As I take one step back and look at other work, the sign of over-engineering is everywhere. While it is easy to blame the AI agents that seamlessly generate complex code and enable my grander ambitions, the responsibility ultimately stops with me. I am accountable for everything created, the elegant and the bloated alike. In this essay, I want to reflect on how I fall into these technical traps and identify a mindset that can help guide my engineering decisions back toward simpler and more intentional solutions.

## The Tendency

As I recall my train of thought for The One Ring, I realize that, ironically, the **complexity** came from my own desire to make things **simpler**. The core design of The One Ring relies on a base container with a collection of common software, from which course-specific containers install additional software as needed. However, as I began planning the expansion of the framework, I realized that advanced courses share very few commonalities. They would end up not using much of the base container's presets. To simplify the container structure for these advanced courses, I decided to enhance the base container with Spack and populate an externally mounted host directory with all necessary software packages. This sounded simple and elegant in theory.

Alas, it is not in practice. 
