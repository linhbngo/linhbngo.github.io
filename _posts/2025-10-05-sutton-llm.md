---
layout: post
title: Richard Sutton, LLMs, and the Extended Brain
date: 2025-10-05 17:01:00
tags: AI, cognition, philosophy, education
categories: non-technical
hidden: false
---

In a recent episode of the *Dwarkesh Podcast*, Richard Sutton, the father of reinforcement learning 
and author of the *Bitter Lesson*,  discussed large language models (LLMs). While the title of the 
episode is [Richard Sutton – Father of RL thinks LLMs are a dead end](https://youtu.be/21EYKqUsPfg?si=MAzgFYuFeMpf_5pX), 
the actual content of the one-hour conversation contains much more nuances than that. I highly recommend that 
you watch this episode and form your own opinions. It should be noted that the recording and transcript of the 
conversation are also available on the [website of Dwarkesh Patel]((https://www.dwarkesh.com/p/richard-sutton)). I am 
interested in this conversation partly because of another recent [MIT study](https://www.media.mit.edu/publications/your-brain-on-chatgpt/0) that LLM users displayed weakest brain connectivity when carrying out the task of essay writing. 
The combined negativity prompted me to listen to the episode carefully and to write down my thoughts. 


## The Interview That Sparked a Thought

True to form, Sutton repeated his long-held view: progress in AI comes not from hand-crafted reasoning but from *scaling simple, general methods* with data and computation[^sutton-bitter]. This can be observed from several statements from Sutton early in the conversation: "Reinforcement learning is about understanding your world, whereas large language models are about mimicking people, doing what people say you should do. They’re not about figuring out what to do" *00:00:33*. When Dwarkesh pushed back that LLMs themselves have robust world models, Sutton responded with the following (*00:01:38*):

"I would disagree with most of the things you just said. To mimic what people say is not really to build a model of the world at all. You’re mimicking things that have a model of the world: people. I don’t want to approach the question in an adversarial way, but I would question the idea that they have a world model. A world model would enable you to predict what would happen. They have the ability to predict what a person would say. They don’t have the ability to predict what will happen.

What we want, to quote Alan Turing, is a machine that can learn from experience, where experience is the things that actually happen in your life. You do things, you see what happens, and that’s what you learn from. The large language models learn from something else. They learn from “here’s a situation, and here’s what a person did”. Implicitly, the suggestion is you should do what the person did."

The remainder of this conversation revolves around the earlier premise that Sutton set up: "Reinforcement learning is about understanding your world, whereas large language models are about mimicking people, doing what people say you should do." This 
distinction sounds tidy, but as I will argue, it's also misleading. 

## Imitation or Real Learning?

Dwarkesh’s follow-up question (*00:02:39*) implicitly accepts Sutton’s framing that large language models are a form of imitation learning. I find this framing inadequate. LLMs don’t imitate behavior. Rather, they infer the semantics of the world  
through linguistic statistics derived from human-generated text. LLMs are not copying what people do: they are modeling how meanings about the world unfold, as revealed through language itself.

Furthermore, if we are being philosophically honest, all learning is a kind of imitation learning: A process of aligning 
internal expectations with external regularities. Reinforcement learning imitates successful behaviors through feedback while 
LLMs imitate linguistic coherence through prediction. Both are engines for compression and generalization. The only real 
difference is that Sutton’s notion of “reinforcement” is continuous and embodied, while LLM reinforcement is distributed and 
epochal. 

Perhaps, then, the more useful distinction isn’t between “real learning” and “imitation,” but between **pre-learning** and 
**learning on the job**. Sutton’s own example of AlphaGo/AlphaZero illustrate this divide once again:

- AlphaGo/AlphaZero learns *while* acting: it generates its own data through self-play, updating its model with each iteration.  
- LLMs learn *before* acting: they internalize an immense prior of the world and later use it to predict, reason, and generate.

Both optimize internal models of reality; they simply differ in *when* and *how* data arrive. From that angle, LLMs aren’t mindless parrots — they’re **pre-trained minds** waiting to be directed.

## Thinking Without Purpose

Another point that Sutton made was the needs for a goal: "First of all, you have a goal. Without a goal, there’s no sense of 
right or wrong or better or worse. Large language models are trying to get by without having a goal or a sense of better or 
worse. That’s just exactly starting in the wrong place" (*00:12:37*). That reflects the reinforcement-learning perspective: 
intelligence equals purposeful optimization. In my opinion, that view is semantically incomplete because it defines thinking 
only in terms of optimization toward explicit objectives, rather than as the continuous generative process of pattern formation 
and recombination. Going back to the human 
perspective: when we sleep, we dream. When our minds wander, neurons keep firing and chemicals keep diffusing even though no 
specific objective is being optimized. Thinking happens because that’s what brains *do*: they generate and recombine patterns, 
purpose or not. In that sense, LLMs mirror us more than Sutton allows. They too **think without purpose**: a vast associative 
mesh always ready to infer, connect, and respond when stimulated. They don’t *want* anything; they *activate* upon input, like 
the cortex waking to a new thought. LLMs thus **separate thinking from purpose**, allowing human users to inject goals 
dynamically. They externalize one of the oldest human capacities: to think idly, creatively, even purposelessly. 

Another interesting snippet of conversation regarding this point happens around *00:06:28*, when Sutton mentioned that LLMs 
"don't have in any meaningful sense a prediction of what will happen next." Dwarkesh suggested "next token prediction", but 
Sutton responded with "the next token is what they should say, what the actions should be. It's not what the world will give 
them in response to what they do". To me, Sutton’s argument is like saying an engine is useless because it doesn’t move on its 
own, while praising a bicycle because its gears and chain have a visible purpose: to propel the rider forward. The fallacy lies 
in mistaking embedded purpose for intrinsic purpose. An engine’s value emerges when it’s integrated into a vehicle, just as an 
LLM’s purpose emerges when it’s integrated into a larger cognitive system.

## The Cognitive Sidecar: Thinking with LLMs

The ending of the previous section brings up my perspective regarding LLMs: they are **thinking engines**. Therefore, they 
are meant to be integrated into other intelligent systems (RL system included) to help amplifying cognitive tasks. This 
perspective will contribute to the interpretation of studies from MIT and elsewhere showing that people’s brains exhibit *less 
activation* when using AI tools: That’s not evidence of laziness but of **distributed cognition**!

When we use an LLM, part of our reasoning migrates outward into a shared cognitive space between human and machine.  
It’s not disuse, it’s redistribution. The LLM becomes a **sidecar brain**, stabilizing and extending our range. It 
is like riding an e-bike: you still steer and decide, but the motor assists the climb. If you are learning how to bike, 
you should not be relying on an e-bike with supporting wheels. You really need to get on a bicycle to learn all the balancing 
tricks and to train your leg muscles. At the same time, if you need to deliver morning papers along a hilly route then get back 
to go to school, then perhaps an e-bike will help tremendously! The difference lies in **intention**, as I said in the previous 
blog about [being well-versed in AI](https://linhbngo.github.io/blog/2025/well-versed-ai/): are you using AI to help with your 
learning process, or are you using AI to get through your learning process!


## Toward the Extended Brain

Watching the Sutton-Dwarkesh conversation is frustrating sometimes, because it feels like the two don't know that they 
are agreeing on principles but keep arguing on different levels of abstraction. Sutton’s world is one where learning occurs 
through closed feedback loops: agent, environment, and reward. The LLM world now includes a new loop: human, language model, 
and reflection. 

Sutton is right about RL models intelligence well **on the practical intelligent and learning process for a specific 
practical task**. The LLM can and will contribute to that process through its ability to extend learning capability: a 
cognitive sidecar that amplifies, stabilizes, and occasionally humbles our thought process.  

The MIT brain-scan study made headlines because people are interpreting this study to confirm their worst suspicion: *AI is 
making us think less.*  To me, that’s like saying if we’d never invented cars, we’d all be as strong as horses and run as 
fast as cheetahs. Tools don’t make us weaker; they change what strength means. We didn’t lose the ability to walk when we built 
engines: we gained the ability to cross continents. Likewise, we won’t lose the ability to think when we use LLMs: we’ll gain 
the ability to think **further**, across boundaries of memory, language, and time.

If anything, AI is forcing us to confront a deeper question: **What does “thinking” even mean when the act itself can be extended beyond the skull?** Maybe our brains don’t light up as much because they’ve learned something evolutionarily 
efficient: Thinking *together* with machines is still thinking, just with a larger brain.

But, make sure that you still know how to cook your food with firewood if there is a worldwide electrical blackout!

## Postscript (October 2025):

My reflections in this essay resonate with a [recent piece in Communications of the ACM](https://cacm.acm.org/news/can-ai-expand-the-human-mind/) describing AI as `System 0`, a new cognitive layer that precedes and interacts with human 
intuitive (`System 1`) and analytical (`System 2`) reasoning. I find it encouraging that this line of thought is converging across fields: what I described as the Extended 
Brain now has a formal name in cognitive science.
