---
layout: post
title: "A Good Engineering Habit: Knowing When To Stop"
date: 2026-06-13 12:00:00
description: ... and when to rollback. 
tags: engineering, simplicity, best-practice
categories: technical
hidden: true  
---


It has been well-documented that ancient human had higher bone density and stronger upper body muscle than we, their sedentary successors typically do. Perhaps that is why, in lieu of wearing armor and running around all days, we lift weight and run on treadmills in hope that we are not becoming feeble after hours of sitting and coding. If we offload the cognitive capabilities of low-level tasks to AI, effectively using it as an external pre-frontal cortex, would we risk weakening some of our thinking capabilities?

I am a avid supporter of introducing intentional (and reasonable) friction into one's workflow to help introducing implicit learning activities. Analogically speaking, this is similar to wearing weighted ankle bracers during day to day activities to unconsciously training one's leg muscles and mobility. It is important to determine just the right level of weight. Too light, and it is useless. Too heavy, and the actual daily work suffers. One notable example of intentional friction in my own teaching and research practice is the selection of VSCode as an IDE. Educational IDEs such as BlueJ or jGRASP are too elementary. IntelliJ is an industry beloved, but is a bit too heavy. VSCode, in my opinion, is just right. 

The introduction of AI and AI coding tools presents the needs for additional friction. Cursor IDE and VSCode Extension make it convenient to integrate AI support in my own development process. What I have observed is my own increased reliance on the tools, perhaps because how easy it is to access the resource with no worry about the extra costs (I use Cursor' \$20 monthly plan). It has become too easy, and I don't like it. As a result, I feel the need to tack on some heavy ankle bracelets! I am moving my active development environment from VSCode into nvim via the [lazyvim](https://www.lazyvim.org/) setup. This essay documents my migration process and serves as a future reminder/quick documentation for when I forget some hotkey combinations!



I am setting up LazyNvim to use in addition to VSCode. I still have VSCode up for lectures notes/screenshots instruction, but I am learning LazyNVim and switching to using this for my own development. In fact, I am writing this essay blog on LazyNvim. 

VSCode takes more resources, getting bloated. 
NVim is harder to setup resources, work with more barebone. Perhaps necessary to reclaim cognitive training, getting lost due to AI integration. 
On that note, I am switch to Claude Code for my AI enabled coding, and forcing myself to use AI is a more "batch format" rather than instantatneous quesiton answer mode that Cursor gave.



File directory:
`.` to set to root directory of the project
`Backspace` to get back out. 
`c` to make a copy in the same directory. 

NVim:
Esc to interaction mode. 
`i` for `Insert` (`Edit`) mode. 
`w` to same
`q` to quit. 
V (Shift + v) enters Visual Line Mode, highlighting full lines.Use j / k or } / { to expand your block selection.Press d (or x) to instantly delete the marked block.

wJump to the start of the next wordForwardbJump to the start of the previous wordBackwardeJump to the end of the next wordForwardgeJump to the end of the previous wordBackward

$Jump to the absolute end of the line0Jump to the absolute beginning of the line (column 0)^Jump to the first non-blank character (skips indentation spaces)

}Jump to the next blank line (end of current or next block)Downward{Jump to the previous blank line (start of current or previous block)Upward


]m ➔ Jump to the start of the next method/function.[m ➔ Jump to the start of the previous method/function.

Moving between windows

Ctrl + hMove focus to the window on the LeftFile Tree ExplorerCtrl + lMove focus to the window on the RightMain Code EditorCtrl + jMove focus to the window BelowTerminal / Output PanelCtrl + kMove focus to the window AboveReturn to Editor from Terminal


I still use mouse periodically, the advantage of running nvim on a Mac/PC. 
