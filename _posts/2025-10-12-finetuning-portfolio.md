---
layout: post
title: "Relearning How to Be Seen: Fine-tuning a Portfolio that Grows with Technology"
date: 2025-10-12 10:00:00
description: How can one improve their portfolio's visibility in this age
tags: learning, writing, AI
categories: non-technical
hidden: false
---

By your third year in computer science, something unsettling often happens. You have done your LeetCode reps, 
maybe contributed to an open-source project, and built a few class assignments that now live half-broken on 
GitHub. You can code. You can debug. You can ship something that works. And yet, you feel that you are 
invisible as all your applications seem to fall into a deep abyss with no response. What happens and what can 
you do? 

The fact is that recruiters are being blasted with a massive amount of applications. If you do not have a prior 
connection, then the process can feel like a game of chance, but the quality and clarity of your portfolio can 
still tip that chance in your favor. However, 
if and when your resume makes it to a recruiter's desk, what does that person actually see? Another line of Python, 
another React app, another student fluent in the same stack as everyone else and their grandmother. The question is 
not about whether you're competent but it is about your work communicates that competence in a way that stands out.

This essay is about relearning how to be seen. Not through louder self-promotion or chasing the newest trend, but 
by fine-tuning the way your portfolio tells the story of your growth: technically, intellectually, and professionally. 
Think of it as a short-term make-over for your technical identity: the kind of make-over that does not require 
extensive new credentials or a six-month boot camp, but a deliberate process of polishing, documenting, and adapting 
what you already have. In today's landscape, standing out isn't about doing more. It's about doing what you already 
do but with sharper intent and traceable intelligence.

I call this process mastering three intertwined crafts:

- Codecraft: rebuilding the foundation of your projects so that they work, build, and speak reliability.
- Storycraft: tightening the narrative around your code so that your reasoning and intent are traceable and legible.
- Modelcraft: integrating and upscaling your work to reflect adaptability and show that your fundamentals grow 
with technology, not against it.

Each layer builds on the previous one. You start by restoring the health of your existing code, then make your 
thinking visible, and finally adapt that clarity into the next technological wave, whether that's AI, data-driven 
systems, or whatever comes after. 

## Codecraft: Rebuilding the Foundation

Codecraft begins with a simple rule: *If your project doesn't demonstrate that it can be built, it doesn't count.*

That is harsh, but it is true. Recruiters and hiring managers do not have the time or curiosity to 
debug your projects to evaluate your competency. When they open your GitHub repository, it should have 
indication that the project has been built (possibly multiple times) immediately, reliably, and predictably. 

At the **recruiter stage**, these visible signals of health (commit activity, badges, or passing builds) 
create a first impression of professionalism. At the **interview stage**, technical reviewers may dig deeper: 
opening your workflow files, checking your Dockerfile, or even scanning test logs. And for **hiring managers**, 
a consistent build process is a quiet signal that you understand how real teams work. A clearly designed build 
plan demonstrates technical hygiene and shows that you treat software as a process, not just a collection of code. 

Start by choosing two or three old projects, the ones that used to run but haven't seen love in a year. Your goal is 
to resurrect them by doing the followings:
- Update dependencies, fix broken imports, and rewrite README instructions so they reflect reality.
- Add a Dockerfile or a simple Makefile so your project becomes reproducible across platforms.
- Integrate GitHub Actions for automated testing: even a single test with a green checkmark signals discipline.
- Include a coverage badge or lint check to show your code meets basic standards.

This is the visible layer of professionalism. A recruiter doesn't need to read your code to know you're serious. 
They can see it in your consistency. The `green check` is the new `trust me I know what I am doing`. Codecraft is 
less about brilliance (like that dozens LeetCode hard that you completed) and more about reliability made visible. 
Anyone can start a project. Few can maintain one.

## Storycraft: Make Your Thinking Visible

If Codecraft is about function, Storycraft is about legibility.

You have probably heard instructors tell you to `comment your code` or `write a good README`. What they rarely tell 
you is why documentation matters or how to go about doing it. Documentation is not just writing for a grade, it is 
for cognitive purpose. It's reasoning made explicit. When you document your project well, you're externalizing your 
internal dialogue about the decisions, tradeoffs, and assumptions that shaped your code. This is what I call **traceability 
of intent**: the ability for another human (or your future self) to understand why you built something a certain way. 

Good documentation (for example, a README file) does not need to be long. It just needs to answer three questions 
clearly:

- What problem does this solve?
- How does it solve it?
  - Be careful of overdoing the `how` and diving into implementation details.
- Why did you choose this approach?

Add a small **Limitations & Next Steps** section: not as self-criticism, but as a professional signal. It 
tells a reviewer you understand your design boundaries and can think beyond the happy path. 

Even commit messages and docstrings become opportunities for clarity:
- Replace *fix bug* with *fixed index mismatch in tokenizer; added boundary check*.
- Replace *update* with *refactored data loader for reproducibility*.

These small traces of reasoning accumulate into a powerful narrative: you're not just coding, 
you're thinking in public. This helps readers (aka recruiters, interviewers, and hiring managers) to have 
a chance to learn about you beyond the resume pages or that short technical interview. 

You can link this step to the previous step by narrating the resurrection process of your older projects. Add a 
short markdown note: **What I fixed and why**. It's a small but powerful reflection that communicates something 
LeetCode never can: that you revisit, repair, and improve. It demonstrates your humility, curiosity, and maturity, all 
encoded in your documentation.

Storycraft transforms your portfolio from a collection of codebases into a map of your mind. It's the difference 
between showing you can write code and showing you can reason about systems.

## Modelcraft: Adapt and Evolve

Modelcraft is not about chasing the AI hype — it's about demonstrating adaptability. It's your way of saying 
that *I can take what I already know and extend it into what's next*. One again, everybody and their grandmothers are doing AI/ML. How do you stand out and signal your competency?

Start simple. Take one of your revived Codecraft projects and augment it with a lightweight ML or AI component, 
something that feels natural to your project, not forced. 
- If it's a web app, add a sentiment analysis or text classification feature.
- If it's a data project, fine-tune a small model for your dataset and publish it on Hugging Face.

The goal isn't to impress with scale, but to show that you can adapt, integrate, and evolve. *This is a new technology, and 
I am able to quickly learn and use it to improve my existing projects*.

When you finish working with the model, make sure that you also publish it to Hugging Face and do the following:
- Write a Model Card that explains intended use, data source, and limitations.
- Link your GitHub repo so the workflow is traceable end-to-end.
- If possible, create a Hugging Face Space, a small live demo that lets anyone interact with your work.

This is what modern visibility looks like: not just static code, but living demonstrations of adaptability. Recruiters 
and companies are increasingly looking for people who can learn at velocity, not just memorize APIs. Modelcraft is 
your visible evolution. It bridges who you were when you wrote that first project and who you're becoming as technology 
shifts under your feet.

## Conclusion: Traceable Intelligence

- Codecraft grounds you in precision.
- Storycraft grounds you in clarity.
- Modelcraft grounds you in evolution.

Together, they form a living ecosystem of your professional identity, one that not only shows what you can do, but 
how you grow. Across every stage, recruiter, technical interviewer, or hiring manager, this triad 
communicates a unified message: *I build with reliability, reason with clarity, and adapt with intent.* 

In this modern digital world where tools change faster than resumes, this triad becomes your new visibility: 
**traceable intelligence**. As an educator, I see the same visibility gap in my students that I once saw in industry. I will 
begin adapting these principles into my course design. Expect something new this Winter for Modern Web Development!
