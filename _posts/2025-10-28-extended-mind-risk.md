---
layout: post
title: "Beware the Zone of Cognitive Overreach"
date: 2025-10-28 12:00:00
description: AI can help you learn, and too much AI can hamper your learning. 
tags: learning, teaching, AI
categories: non-technical
hidden: false
---

In the recent CCSC-Eastern Regional Conference, my colleagues brought up the issue of how we can adapt students’ learning process to fit in with this new environment where AI is fast becoming pervasive. One of the challenges in doing this is to figure out how to ensure originality and critical thoughts while also preparing students to use AI tools valued in industry. As I ponder on this issue, like any modern human, I discuss my thoughts with my trusted companion, aka ChatGPT. The initial question was on whether human originality would be the next valuable commodity. The conversation went on for a bit with follow up questions like to what extent could an AI-assisted artifact be considered as originated by a human and how much human intention is required. At one point, ChatGPT suggested that it could write an essay based on the conversation, and my immediate response was that it would *defeat the purpose of originality*. 

The conversation unfolded beautifully. We discussed the framework of authorship, the question of feasibility via AI tools integration versus human authenticity, and the idea from *The Extended Mind* that our tools can become part of our cognition. I was excited to sit down and start writing, by myself in my own words, about all these exciting ideas that came to me after this AI-assisted conversation. And then a sobering realization follows, what about the students? All of these, for me, were fun and even philosophically fruitful. However, for my students, this is dangerous to their learning process. The illusion of having an extended mind without proper control can and will irreparably harm the learning process. As an educator, this is now the question: How do we teach students to extend their minds through AI without letting the extension amputate their agency? 

## The Perils of Unreflective Extension

Without grounding in self-awareness and reflective practice, early and extensive AI usage can lead to a number of problems. 

- First, there is the illusion of competence, and I am not talking about vibe coding here. Surface-level learning activities with AI can lead students to believe that they understand the materials. This is possibly because AI models have a tendency to appease their users unless explicitly asked not to. Minor achievements, while they can serve as encouragement for the learning process, can be exaggerated by AI and misunderstood for mastery by students.
- Secondly, frequent usage of AI on repetitive or routine tasks in the name of time saving will let the machine’s fluency replace students’ own cognitive capabilities. Surely this issue is minor for experts wanting to maximize their performance outputs. However, for those who are still in the learning stage, almost all activities are designed with pedagogical purposes. Reductions or omissions can have consequences. Imagine remembering algorithms and being able to implement code, but having trouble typing because you are so used to tab-completion, while in an in-person technical interview with no AI!
- Finally, one of the more precious commodities of the AI-permeated future would be originality. Even when the core ideas are yours, working with AI’s generated output too much could lead to identity diffusion. Students run the risks of mistaking these for their own self-expression, thus merging their originality with some generic statistics and losing their identity in authorship. Because AI's generative process normalizes patterns from massive data, it erodes the friction from which originality grows. 

In short, students risk mistaking borrowed coherence for owned understanding. It is another form of illusion of learning. This is where the extended mind becomes feral, and the AI tool becomes parasitic rather than prosthetic. A biological parasite, when ripped off, can cause potential damage to the host’s body. A mental parasite, when ripped off, can make the hosts unable to exhibit the perceived competency, leading to crisis of confidence such as shame, imposter syndrome, or even cynicism. 

## Control Before Power: Reclaiming Agency Through Guided Scaffolding

To address this issue, it is imperative then that students are taught control before power. 

Let’s start by drawing from Vygotsky’s Zone of Proximal Development, where students are scaffolded to operate beyond their ability without losing agency. In this sense, we can interpret that the first risk (illusion of competence) of AI comes from its ability to super-scaffolding students to do work without possessing the knowledge (aka vibe coding!). Perhaps we could call this **Zone of Cognitive Overreach**, where students can produce work without possessing the knowledge. How do faculty address this issue (without banning AI outright)? One possible approach would be to provide students with the proper pedagogical prompting framework to ensure that AI do not overreach and provide too much scaffolding. In other words, we are scaffolding the scaffold. One example would be to require/suggest students to use the following prompt structure when debugging:

```yaml
TASK FRAMING: 
- I am debugging a function that implements insertion sort in Python.
- My goal is not just to fix the bug but to understand why the bug occurs and how the algorithm logic flows.

MY UNDERSTANDING: 
...

MY CODE:
...

RESULTING BUGS:
...

HELP BOUNDARIES: 
- Do not give me the full corrected code.
- Guide me by asking one diagnostic question at a time.
- Explain what conceptual mistake each question is designed to uncover.


REFLECTION CHECKPOINTS:
- After each question, pause and wait for me to respond with my reasoning.
- Once I answer, explain whether my reasoning shows partial, full, or flawed understanding — and why.

FINAL STEP:
- At the end, summarize the reasoning steps we took without revealing final code, and ask me to rewrite the full function independently.
- Then evaluate my new code only in terms of whether it demonstrates understanding of insertion sort logic.
```

There are other different prompting strategies to use, and this would warrant extensive prompt engineering research. A dynamic framework that can generate these prompt templates based on students’ performance (encourage the weak and push the strong) would be another possible approach. 

I do not think that there is any easy solution for the second and third problems. AI offers the seductive illusion of control over knowledge, and this is very tempting. At the moment, my best approach is to continuously talk to the students and explicitly emphasize the importance of making the knowledge their own. 

## Conclusion

While the extended mind is empowering for experts, it is existentially risky for novices. Experts will use AI to amplify thoughts, but novices are at risk of using AI to replace thought. This mirrors developmental hierarchies in any craft: before using fancy oils and canvases, one should always start with a pencil and a piece of paper. 

As educators, our task is then not to restrict AI per se, but to re-synchronize capability and comprehension and to teach students how to stay grounded while their minds are extended. This is so that their ability grows in step with their understanding. They need to understand what the AI did, whether they should accept or reject the results, and why. They should have access to AI tools to be familiar with  the operations but not to all the tools’ capabilities. To this extent, it is our responsibility to build the proper prompts to help establish these guardrails for students’ learning activities. Maybe this is also our new role in the AI world, to become meta-educators. 


