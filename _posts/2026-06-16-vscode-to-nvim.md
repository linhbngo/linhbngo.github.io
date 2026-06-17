---
layout: post
title: "Ankle Weight for the Mind: Migration to Lazyvim"
date: 2026-06-17 12:00:00
description: Do you even lift? 
tags: learning, vim, terminal
categories: technical
hidden: false  
---

It has been well-documented that ancient humans had higher bone density and stronger upper body muscle than we, their sedentary successors typically do. Perhaps that is why, in lieu of wearing armor and running around all days, we lift weight and run on treadmills in hope that we are not becoming feeble after hours of sitting and coding. If we offload the cognitive capabilities of low-level tasks to AI, effectively using it as an external pre-frontal cortex, would we risk weakening some of our thinking capabilities?

I am an avid supporter of introducing intentional (and reasonable) friction into one's workflow to help introducing implicit learning activities. Analogically speaking, this is similar to wearing weighted ankle bracelets during day to day activities to unconsciously training one's leg muscles and mobility. It is important to determine just the right level of weight. Too light, and it is useless. Too heavy, and the actual daily work suffers. One notable example of intentional friction in my own teaching and research practice is the selection of VSCode as an IDE. Educational IDEs such as BlueJ or jGRASP are too elementary. IntelliJ is an industry beloved, but is a bit too heavy. VSCode, in my opinion, is just right. 

The introduction of AI and AI coding tools presents the needs for additional friction. Cursor IDE and VSCode Extension make it convenient to integrate AI support in my own development process. What I have observed is my own increased reliance on the tools, perhaps because how easy it is to access the resource with no worry about the extra costs (I use Cursor' \$20 monthly plan). It has become too easy, and I don't like it. As a result, I feel the need to tack on some heavy ankle bracelets! I am moving my active development environment from VSCode into nvim via the [lazyvim](https://www.lazyvim.org/) setup. This essay documents my migration process and serves as a future reminder/quick documentation for when I forget some hotkey combinations!

This essay is written using the new lazyvim setup!

## VSCode versus NVim

Before settling down with VSCode, I spent time trying out `Atom` and `Sublime`. They were (are) great, but they are not popular, as shown in the recent [2025 StackOverflow Survey](https://survey.stackoverflow.co/2025/technology#most-popular-technologies-dev-envs-dev-envs). Hence, I move directly to NVim (Neovim) as my new environment. It should be noted that I have always seen struggling to learn to use vim as one of the highlights in my undergraduate years, and I want to do it again. 

Comparing to VSCode, NVim is definitely lighter. After running `ps aux | grep '[v]scode' | awk '{sum += $6} END {print sum / 1024 " MB"}'` to find how much memory VSCode and its affiliated processes took, the result was `2.2GB`. In contrast, NVim only took `94MB`. Both applications opened the same folder structure and file for editor. I thought that it was because of VSCode's extension, including the PlatformIO extension that I needed for my TinyML class. Can I do PlatformIO inside the terminal directly? The answer was yes, I can do everything in the terminal. Then NVim it is. 

## Migration Process 

I don't want to just swap everything over to nvim immediately. Rather, I ask (AI) the question: Is it possible to recreate an interface similar to VSCode in nvim. The answer was yes, and Gemini recommended two possible configurations: [lazyvim](lazyvim) and [nvchad](https://github.com/nvchad/nvchad). Out of those two, lazyvim seems to have more supporters and recent active development. The choice was easy to make. 

The first item that I want to migrate is the ability of VSCode to open directly into the root folder of a project. After Nvim was installed and lazyvim was set up, I learned how to `open the folder explorer side bar` using `Spacebar-e` key combo. This allowed me to traverse throughout the file system of my Mac, but it was too lengthy. A quick Google search showed that:

- I can set the explore to set to the root directory of a folder by pressing `.`
- To get back to the main tree, I can use `Backspace`. 

As I started to write this essay, I wanted to have an easy start by cloning from an existing file. Hence I learned that:

- Pressing `c` when highlighting a file then type in a new name will create a copy of that file. 

With the new template file created, I needed to get rid of the existing text. Holding `Backspace` will not do. I will need to do the following instead:

- Press `v` to get into the Visual Line Mode, then use `j`/`k`/ or `}`/`{` to expand the block selection. Press `d` to delete the marked block. 

I also needed to quickly navigate among the document. Holding down arrow keys and moving one character at a time is not very efficient. I will need to switch out to `Normal` mode to do the followings:
- `w`: Jump to the start of the next word
- `b`: Jump to the start of the previous word
- `e`: Jump to the end of the next word
- `g-e`: Jump to the end of the previous word
- `$`(meaning `Shift-4`): Jump to the absolute end of the line
- `0`: Jump to the absolute beginning of the line 
- `^`(meaning `Shift-6`: Jump to the first non-blank character (skips indentation spaces)
- `}`: Jump to the next blank line (end of current or next block)
- `{`: Jump to the previous blank line (start of current or previous block)
- `]-m`: Jump to the start of the next method/function.
- `[-m`: Jump to the start of the previous method/function.

Moving between windows panel was needed as well. These movement patterns are similar to how things move in `tmux`. 

- `Ctrl + h`: Move focus to the window on the **Left**
- `Ctrl + l`: Move focus to the window on the **Right**
- `Ctrl + j`: Move focus to the window **Below**
- `Ctrl + k`: Move focus to the window **Above**

## Mindset Adjustment 

The biggest friction that I have when making this migration is the navigation process. Without access to the mouse (self-imposed), it took some time getting used to switching in and out of the `Insert` mode, versus `Normal` and `Visual` mode. Out of force of habits, I misused some of the more common hotkey combinations (`Ctrl-c`/`Ctrl-v` anyone?), and `u` for undo has been a wonderful thing to remember. Quick save is no longer done with a simple `Ctrl-s`, and I found myself doing `Esc-w-Enter` for saving more frequently. 

It is possible to use the mouse, but I felt that it breaks the keyboard flow, and the graphical readjustment is awkward for me. As a result, I have been trying to limit myself from using the mouse at all with working with nvim. 

## Conclusion

This has not been a painless process, and yet I like the feeling. It is like that aching soreness that you get after a lifting or running session, knowing that the uncomfortable feelings will leave and you will become stronger or faster over time. 

There is another unanticipated pedagogical benefit here too. Since I am still not used to switching between `Insert` and `Normal` modes yet, I find myself thinking and typing  more carefully, just so that I don't have to spend time going back and deleting things. 

By pulling back from the frictionless autocomplete engine of modern IDEs and embracing a batch-format workflow via Claude Code in the terminal, I am forcing myself to think in entire system designs rather than line-by-line patches. I’ll check back in a few months to see if the weighted vest has paid off.

