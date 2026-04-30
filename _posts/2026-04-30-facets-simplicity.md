---
layout: post
title: "Pork Rib Congee versus Beef Stew: The Facets of Simplicity"
date: 2026-04-30 12:00:00
description: What does simplicity really mean?
tags: cooking, pedagogy
categories: non-technical
hidden: false
---

Last week, my wife and I got into another debate about food. Or more specifically, how difficult or easy it is to 
make certain food. After watching the video of a distant relative making pork rib congee, she thought that this dish 
was good and that we should try to cook it because the dish is simple to make. I dissented! 

For me, any kind of congee is complex. Without using a pressure cooker, my success rate of not burning congee has been 
lower than 20%. For pork rib congee, the steps initially look straightforward. We start with washing the ribs, then cook 
them in a pot of water on high heat until the water boils, remove impurities, continue cooking on small/medium heat for about 20 minutes, mix in the 
rice flour, stir and add salt and spices to taste, and voila, the dish is done. It is quite simple, really (my wife's 
words). I agree with that statement for the majority of the steps, except for the stirring part. For me, this 
stirring stage is quite challenging since it requires me to stand there and stir continuously for 20-25 minutes. At this 
point, my wife raised the example of my favorite dish, beef stew. She listed all the steps, including dicing and marinating 
the meat, peeling the potatoes, chopping the carrots, browning the meats, stir-frying the meat-carrot-potato mixture, 
adding the wine, and adding salt/pepper to taste. There are too many steps to consider! I find these steps, while numerous, 
are straight forward and well organized. 

As the debate continues, we start to explore deeper into our own arguments. Why, individually, did we have these
differences in perceiving the level of difficulty/simplicity. And that is the main premise of this essay. 

## The Control Loop versus the Recipe

I have been told that the critical step of a good congee dish is that final stirring stage. You need to stir non-stop with 
a slow circular motion, which supposedly help creating that smooth and slightly sticky consistency and preventing clumping 
or watering of the congee. Do we stir for five minutes, ten minutes, or twenty minutes? It is not an exact science. You stir 
until the congee looks `translucent` and feels `consistent`. This is real-time interaction/feedback loop(!), and as we all 
know it in Computer Science, it is a very difficult problem to resolve. 

```c
while(!translucent and !consistent) {
    stir();
    check_consistency();
    check_opaqueness();
}
```

On the other hand, while the beef stew recipe has 
many steps, all of these steps are pre-determined. You dice this, cut that, cook for X minutes, put some wines in, cook for 
Y more minutes, and then it is done. The beef stew is a beautiful and simple deterministic algorithm that is easy to trace. 

```c
for step in beef_stew_recipe:
    do(step);
```

As I was making the case with my wife about how congee is difficult and stew is easy, I realized that perhaps we both 
are describing the elephant with our eyes covered here. If we use `difficult` and `simple` as our 
ground markers, then to me, `difficult` means lengthy repetitive tasks (stirring congees) and `simple` mean short and clearly 
defined tasks regardless of quantity (chopping, dicing, mixing, etc.). For my wife, `difficult` means too many steps to 
remember and managed, and `simple` means single actions that could be reacted to immediately. 

## Margin of Error and Recoverability

The reason my success rate with congee is so low is that once you make a mistake in the final stirring process (like getting lost 
in a TV show for 10 minutes) and the congee is burned, there is no coming back. Even though only the bottom layer is burned,  
that smell is blended in with the entire pot making it almost inedible. The beef stew is a lot more forgiving. If I overcook it 
for 5-10 minutes, it will only get a bit more dry and the taste will not be impacted as much. It is entirely possible to fix a burned stew. 

After due consideration, my wife agreed with my point here. To me, simplicity also means it has to be simple and easy to either 
prevent failure or to recover once an error happens. Regardless of how few and straight forward the instructions are, if we cannot 
easily recover from failure, it means the difficulty is implied in the preparations that are needed to prevent failure. 

## The Fried Summer Roll Paradox

One example that my wife brought up to demonstrate how she considers dishes with multiple messy steps `difficult` is the fried summer roll. 
The initial preparation steps for this dish are quite numerous. We need to prepare slice wood-ear mushroom, cut glass noodles into small 
portions, grate carrots, dice onion, dice jicama, mix minced meat, vegetable oil, and eggs. However, I did not find those preparation steps 
problematic at all. I also think the dish is `difficult`, but the stage that I have a problem with is the one after, where we have to assemble 
the rolls one-by-one repeatedly. And I have seen my wife finish this stage in a flash! Does it mean that if both of us work on this dish 
together, with me preparing the ingredients and my wife making the rolls, it will become `simple`? I don't think that the dish will magically 
become simpler, but we have simplify the process by matches the various stages to people with the right temperaments. 

## Implication for Teaching (or Learning)

At the end of the conversation, my wife remarked that the perception about the level of difficulty is likely to be 
influenced by our own mindset and circumstances. And I agree with her. As a grad student, it is a lot easier to *batch* cook 
the dishes that are hard to fail that dishes that require *dedicated* time and attention. Perhaps it is not that I can't stir for a long time, 
but that I am so used to short multi-step cooking and I don't want to consider an alternative. 

This realization leads to another thought. It is entirely possible for our own perception of `difficulty` to spread onto how we teach others. 
A `Hello, World` program is so *simple* to run. Yet, for a novice student, the challenge is not about running and understanding `Hello, World`. 
The challenge would be to launch VSCode, find the Editor button, type in the code with no mistake, open up the Terminal, type the commands to 
compile and run, and deal with possible errors if a typo happens. It is important for us to be empathetic of students' circumstances and to understand 
where their struggle is truly coming from. 


