---
layout: post
title: "Thankful for Failures"
date: 2025-11-26 12:00:00
description: Catchy title ain't it? 
tags: philosphy, fails, computer sience education
categories: non-technical
hidden: false
---

Hopefully that I got you here with the catchy title on Thansgiving. Now, let's me rephrase the core topic of this essay: **I am thankful for being able to experience failures throughout my learning process and having the opportunity and mindset to recover from these failures**. A major motivation of this essay comes from my talks with two of my students regarding how to get more students to participate in opportunities outside classes. One of the answers they gave me was about how many students were afraid of attempting new challenges because of the risk of failure. First, experiencing and learning from failures are critical aspects of growth, perhaps not just in computer science but in other fields as well. This sentiment is well known. Second, being able to fail while having the opportunities to learn from failures and the mindset to recognize these opportunities is a privilege that many of my students do not have or are not aware of. 


## Failures in Computer Science

Let's start with a limited definition of failures: technical failures aka bugs and error messages. For example, your program fails to run, you receive angry compilation error messages, or the automated test cases fail. From my experience, I have always thought that comparing to some other sciences like math, physics, or chemistry, computer science (CS) is much nicer in the sense that you know exactly what is wrong the moment you try to compile and test your program. 

Think about it this way, I would try to solve a problem in math, physics, or chemistry then write up and submit the solutions only to receive a red-mark ridden result back. Only then I would know where I went wrong. On the other hand, the moment I finish writing my program and start testing it, the compiler will immediately yell at me if there is anything wrong in my code. I often tell my CSC 231 students that if they write their entire program and that program compiles and runs immediately without any error, then they are either: A) supercoder, B) superlucky (go buy a lottery ticket), or C) there is an error buried so deep that normal tests can't catch. 

Of course, it is not fun at all to see a wall of error messages dotted with with angry red letters. After all, we are all familiar with this limerick in the 1990s on usenets:

> 99 little bugs in the code, 
>
> 99 bugs in the code, 
>
> Fix one bug, patch it all around, 
>
> 101 little bugs in the code. 
>
> ...

However, as I became more fluent and more technically savy in coding, I actually found myself more expectant of these error messages. To some extend, the act of debugging is somewhat therapeutic. Furthermore, unlike what the above limerik said, sometimes fixing one bug can help take down several related, cascaded issues as well. The wall of error message will come crumbling down eventually if you take a deep breath and tackle the messages one by one. Sometimes I feel like cleaning up a buggy program gives me better satisfaction that writing a non-buggy one. 

## Learning from Failure

Resolving error messages is not just for fun and happiness. While in-class lectures, which emphasize theoretical knowledge, give me the foundation necessary to understand conceptual reasons behind these errors, actually encountering the errors and fixing them, sometimes hapharzardly is what really improves my technical skills. It also makes understanding and connecting theories to practice easier. 

Reading error messages and trying (keyword: `trying`) to understand the implication behind them is also an excellent learning activity. Take the typical `IndexError` message from Python for example. After encountering this message several times, one will eventually learn that `IndexError` means the program is trying to access an index position that is outside of a list's range. After encountering this message several more dozen times, one's reaction is no longer about the list though. You will find your mind jumping directly to things like *did I increment my index counter the right way*, *how many elements should this list have*, or even *did I specify the right directory containing my files*. 

While I am no longer a superfan of Thomas Edison, I love this particular quote, which was attributed to him: **I have not failed 700 times. I have not failed once. I have succeeded in proving that those 700 ways will not work. When I have eliminated the ways that will not work, I will find the way that will work**. As I am able to write code that most likely to be correct and has fewer and fewer immediate bugs, I often wonder that is it because I already know the right answer, the right lines of code to write, or is it because I have quickly eliminated all the incorrect lines of code. And this knowledge about what not to write comes from working and resolving error messages, aka learning from failures. Going back to what I said earlier about `supercoders`, I think that supercoders, similar to chessmasters, have the ability to extremely quickly eliminate wrong options, and this is the secret sauce to their ability. If you ever encounter a friend who is very good at coding and they tell you they can't explain why they write their code this way, try asking them why they don't write their code another way, you will see how easy they can explain that. 

## A Failure Expectant Mindset: The Privilege of Resilience

The knowledge of what not to write, gained through accumulated experience with error messages, is the foundation of the failure expectant mindset. This mindset is characterized by resilience, curiosity, and the belief that a technical failure is an expected, necessary step toward a correct solution, not a sign of personal incompetence. It transforms an error message from an accusation into a clue.

However, developing and applying this mindset is deeply connected to the privilege of opportunity. Let's take one step back from the perspective of pure technical failure. Many students, particularly those from under-represented groups including female students, do not consider the ability to afford to fail as a given. They carry a greater burden of representation stress to succeed not just for themselves but for their entire group. They may feel they cannot risk failure because it validates harmful stereotypes or jeopardizes a hard-won opportunity. This external pressure spills catastrophically into the learning process especially for CS students, and this often happens early on. 

From the beginning, in early introductory courses, this external pressure manifests in the classroom as an unfounded belief that "good programmers don't fail" or "I must get it right the first time." The belief will cripple the students' learning capability when they inevitably encounter a bug (the necessary learning step) for the first time. Instead of seeing the error as a standard investigative problem, they see it as proof of personal deficiency, and consequently, they experience disproportionate stress and shame. This is the dreaded feeling in highschool when our returned assignment is riddled with red Xs. 

This stress leads to avoidance behavior. The students may stop attempting new problems, give up too early on debugging existing issues, or seek immediate solutions rather than wrestling with the errors. This avoidance prevents the very failures necessary to build the practical skill and resilience required for mastery. They are trapped in a negative feedback loop where the fear of failure prevents the learning that would cure the fear of failure. Expanding this issue further, the avoid behavior will lead to students not trying for other out-of-class activities as well. Actitivies that would have made great entries in one's resume (e.g., hackathon, club projects, research) are now skipped over. 

This is why cultivating the failure expectant mindset in the classroom is not just good pedagogy; it is a critical act of equity. The task is not merely to teach debugging techniques, but to decouple the emotional threat of failure from the necessary instructional value of error messages.

## Cultivating Failure Expectant Mindset in Students

Perhaps one of the earlier sections in Introduction to Programming should be about common error messages in whichever languages that are being taught. The [Programming with Python lesson from Software Carpentry Workshop](https://swcarpentry.github.io/python-novice-inflammation/) has done very well on this with their dedicated units on Errors and Exceptions. A possible pedagogical argument against this would be that different languages will have different error messages and that it is more important to focus on the theory behind a programming mindset. However, I would argue that this is an important part regarding the cultivation of a failure expectant mindset: students are learning about failures intentionally and should anticipate running into these error messages in the future. 

A second approach to help students would be to engage in helping fellow students to debug. The mental pressure of facing error messages will be lessened if it is other people's error messages! You get to learn from failures (other people's failures). While this is perhaps not the same as learning from one's own failures, which in turn can help one to analyze the root cause of the failures, it is still good practice on resolving errors. I want to shout out to my years providing technical support for the users of Clemson University's Palmetto Supercomputer. I have learned much through analyzing and resolving a great numbers of technical errors spanning different systems, applications, and programming languages. 

## Modeling Resilience

I still remember a core assumption in one of Google's seminal paper, `The Google File System`: *failure is the norm*. Up until that point, a lot of the work in distributed file system that I read was about minimizing failure rates. That particular assumption from Google left a significant impression with me. Go back to this essay's topic, let's have our students embrace a similar mindset: **Failure is a Friend**. However, it is one thing to say the words and it is entirely another thing to truly believe the meanings. A quick search on Google Scholar shows a [healthy collection of research on this topic](https://scholar.google.com/scholar?hl=en&as_sdt=0%2C39&q=teaching+students+to+embrace+failures+computer+science&btnG=). 

For me personally, I will cultivate this mindset in my students through my own example. Let's normalize live coding in class in front of students. Let's normalize making typos, seeing compiling errors, and fixing them in front of our students. Let's show them that if their professor can fail and learn from their failures, then they can too for they are younger, more quick-minded, and better prepared. Let's show students that the bug counts in that limerick will fluctuate but will definitely not be infinite! It is possible that by modeling our own failures, we can give our students the opportunity to build the mindset that turns failure into a universal teacher.



