---
layout: post
title: "Where to Begin: The Gartner Hype Cycle"
date: 2026-02-03 12:00:00
description: How to start the learning process
tags: cs-education, robotic, ai, learning
categories: technical
hidden: false
---

From my own pedagogical perspective, *"go ahead and start learning (on your own)"* and other 
varieties of this statement is perhaps one of the most overrated statements that I know. One of the 
most significant challenges of self-learning is to know exactly where to start. To learn is to 
traverse and consume contents of the knowledge tree relevant to the selected topic. Starting at a 
too low a level will lead to wasted time and effort and potentially misalignment of learning 
trajectories. Starting too further up will make it harder to grasp the necessary fundamentals and 
more likely to cause mistake and frustration. The modern abundance of knowledge only serves to 
exacerbate this challenge. 

Starting the learning process takes grit, but it helps to have small motivations and successes 
along the way. It also helps to maintain a clear sight on what we want to learn, or as I mentioned 
in other posts, a clear intention. The act of learning should be strategic and deliberate. As I 
reflect on this, I find the [Gartner hype cycle](https://en.wikipedia.org/wiki/Gartner_hype_cycle) 
an excellent mapping/analogy for my learning process. In this essay, I will retrace my own recent 
learning trajectory on a new potential research topic across different stages of the Gartner hype 
cycle. 

<div class="row mt-3 justify-content-center">
    {% include figure.liquid loading="eager" path="assets/img/blogs/2026-02-03/gartner.png" class="img-fluid rounded z-depth-1 mx-auto d-block" width="50%" zoomable=true %}
</div>

## Technology Trigger

One of the challenges as a CS (associate) professor at a newly minted R2 institution is to find the research 
area to move forward. We want research activities that are exciting and have potential to get federal funding, 
but we also want these activities to support our students' career trajectories. We do not (yet) have the 
luxury of doing highly advanced theoretical basic research while enjoying the institutional brand that would 
make our students marketable to employers. For me, this means selecting a research topic that is both 
academically exciting and professionally marketable. Nowadays, it means moving closer toward the boundary 
between hardware and software with a healthy sprinkling of applied AI/ML. Hence the trigger: robotic-related 
research. The initial topic of interest, proposed by an undergraduate student, is to study whether LLM can 
contribute to the management of sensors on a drag-racing car and help making technical suggestion to the 
driver. At a higher level of abstraction, the broader research will focus on understanding how LLM can help 
translate human-level instructions into detailed technical instructions that control robots. Hello R2D2!

## Peak of Inflated Expectations 

The subsequent search for learning materials has supported my decision to learn about this specific topic. 
The [Code as Policies](https://code-as-policies.github.io/) paper by Google Robotic team clearly presented 
the idea of using LLMs to generate policy codes that help control robotic activities. From an applied 
research perspective, this means potentials to create smaller projects for LLM evaluations, workflow designs, 
and even the direct generation of system level codes for micro controllers. By the date of this entry, the 
paper has 1501 citations since its first publication in 2022, and most of the papers citing this work are 
themselves highly cited (in the hundreds). 

It also seems very feasible to learn how to do the work. After all, there are hundreds of videos online 
teaching how to do robotic programming, many programmable robotic cars are quite affordable, and I myself 
has done work related to system programming on Arduino and work related to LLM/MCP (Model Context Protocol). 
Everything is possible with proper experimental design! We are at the top of the world!

## Trough of Disillusionment

The fall from the peak was not a single drop, but a series of stumbles over several days. Things 
started out quite well. While my students 
go out and prepare a more extensive shopping list for a remote control drag racing car with sensors, I 
look around for how to get started on the experiments themselves. From a larger perspective, I reasoned 
that the core abstract workflow involves creating a communication pathway between an LLM agent, an MCP 
server with proper tools, and a robotic entity whose actions can be remotely controlled through the MCP 
tools. It just so happens that my son has an original [mBot](https://support.makeblock.com/hc/en-us/sections/360001828973-mBot) toy car by MakeBlock. After some search, it looks like MakeBlock's products are 
programmable via Python, and the actions and code controllers can be sent off via wireless connection. I 
promptly commandeered the toy, installed mBlock 5.0, and started my learning process. Then the troubles 
started to show up. Some of them are shown below. 

- I spent a good amount of time deciding where to start. It turns out that the micro controllers inside 
these toys can be quite different, and each of them has a different SDK. It turns out that my prior 
Arduino experience barely scratches the surface. GPT was nice enough to recommend me a 700-page 
fundamental book on the topic, which would guarantee in-depth understanding. I would have taken this 
approach **if I was in my undergraduate years**!. 
- The mBot car is a first generation, and many of the capabilities mentioned are only available on the 
second generation. There was no Python coding, and programming has to be done via C/Arduino. 
- Wireless connection can only be used to send control signal. MCU codes must be compiled and uploaded 
via the wired USB connection. 

These issues really dampen my morale. I still feel excited about the progress, but this is exactly where 
I face that question: **where do I start?** on this massive knowledge tree of robotic engineering. 
Should I start learning Arduino coding and just grinding through that 700-page book? Should I buy the 
latest robotic toys first, so that software and APIs are 
modern and convenient? Should I just get rid of the hardware all together and learn how to use 
[Webots](https://cyberbotics.com/) so that everything can be simulated? I am not yet disillusioned, but 
I am certainly a lot more sober and worried. 

## Slope of Enlightenment

It is quite easy to give up at the bottom of the trough. Among the three questions that I listed earlier, 
two of which already carry a hint of giving up. It is not necessary a bad thing, but it is important to 
stay focus on the original intention. Why did we want to learn to start with? Taking one step back, I 
determined that I want to learn because:

- I want to have a broad understanding of the majority of this new area of research. Not broad as in 
marketing broad, but broad as in technically enough to know what exactly it is that I don't know. 
- I want to have a very rudimentary workflow built as a proof of concept. My students were excited to 
start learning about this topic, but as an advisor, I need to be able to stoke the fire. Nothing better 
than to lead by example. 

In this case, the first option, reading 700-page book and learning MCU programming from scratch is too 
in-depth and inefficient. Some of my students will follow this route. I just need to clear an initial 
path for them to explore. The third option sounds good, but it is certainly not as exciting as playing 
with real hardware and it is very close to choosing a different research path. That leaves the second 
option and I don't like it. Progression and learning that depends too much on latest technologies will 
be prone to technological bottleneck. To start climbing the slope of enlightenment, or perhaps a 
less marketable phrase, *the learning curve*, I used a debugging approach. I stopped looking at the 
big picture and I started address small challenges. 

1. **Hardware issues**: I stopped thinking about advanced techniques and started out testing that the 
`mbot` toy car can be connected and controlled via vendor documentation and application. Simple block 
programming done via the mBlock 5.0 program is tested. USB connections are tested. Through this process, 
I now have a better understanding of the serial USB connection, and that it is possible to create 
wireless connection via a USB-based vendor-specific dongle. I guess I did lean a bit on the purchasing 
new hardware of the second option here, but not by much. 

2. **Platform setup**: To be able to learn, you have to be able to carrying out learning activities. I 
need to setup a learning environment that is not vendor-specific and allows for inter-process 
communication (LLM agents talking to MCP servers talking to robots). I asked GPT to help me set up an 
environment on which I can write, compile, and upload MCU code from the terminal. This includes 
installing `arduino-cli` and `MBlock libraries` on my Mac Pro M4. Without experience writing code for 
the motors of the `mCore` board, I also asked GPT to generate some vibe `.ino` examples. This allows me 
to test the feasibility of direct code upload from terminal, direct control sequence sent via `screen`, 
and indirect control bytecode sequence sent via Python's `pyserial`. This is where the hardware 
communication part of my research interest is proven to be feasible. 

3. **LLM communication**: I also generated two Python scripts, one MPC server whose tools include 
byte code controlling sequence and one LLM agent that read in a string and potentially translate that 
(via LLM) into a proper MCP tool calls. The pieces are combined together, and after some tweaking, I have 
a very basic LLM-controlled car running round. Along the way, I have learned how `pyserial` can be used, 
how to funnel embedded logs to the screen, and that the original research idea is completely feasible. I 
also learned that different LLM models perform differently in the ability to generate the right tool calls. 

The slope of enlightenment itself is the true growth after the hype, where we really dive into preparing 
the learning activities. This is where one needs the most help. I believe I was able to get through mine 
due to extensive strategic support from GPT/Gemini, my own experience in finding the starting points from 
other learning projects, and the excitement and inspiration from my students. Everyone will have a 
different way of getting through this slope, and it is important to keep one's mind open and agile along 
the way. 


## Plateau of Productivity

For my own original learning purpose, the proof of concept at the end of the slope of enlightenment is 
the platform on which further learning activities can be carried out. I can go more in-depth into MCU 
programming by focusing on improving the `.ino` file and update the specific tool calls in the MCP 
server accordingly to test the new MCU implementation. I can focus more on evaluating various LLMs to 
see how well they translate the natural language instructions into proper MCP tool calls to drive the 
car. Future research directions are (almost) limitless here. 

From a learning perspective, this is also where one reviews their enlightenment climb. Similar to a 
real climb, in the first time around, you want to make it to the top. But to truly make the route 
your own, you will need to slow down and look back slowly. After all my proof of concept has a lot of 
AI-generated contents. It gave me a starting point, and it is my turn to truly start. 

## Conclusion

*Just start learning* is not an easy thing to do. To some extent, my learning process described above 
is done so that I know where to help my students to get started. However, if you ever have to really 
start learning on your own, I hope my experience here can give you yet another approach to consider. 
We do really have to find out the right starting point in learning before we can start learning. This 
process can be frustrating and sometimes demoralizing, so take your time, be strategic, and be resilient. 


