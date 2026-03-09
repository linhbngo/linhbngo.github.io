---
layout: post
title: "Bring Engineering Thinking to What We Do"
date: 2026-03-07 12:00:00
description: Carrying an engineering mindset with you
tags: memory, measurement, engineering
categories: technical
hidden: false
---

Last week, I was teaching my Introduction to Cloud Computing class, and I was demonstrating to my students how additional containers can 
place additional constraints on the host computer's resources using my MacBook Pro M4 24GB. As I was showing Mac's Activity Monitor, one thing 
that struck me was that I was using 18 out of 24GB of available memory. This surprised me by a lot. I thought at most I was consuming 
10-12GB, and it turned out that I was wrong. So what have I been using that consumed this much memory? 

As I was contemplating my Mac's utilization, another thought popped up. How did my estimate get so wrong? Perhaps my engineering senses 
have become dull over time, given how much resources I have access to (*since I started making real money*). At the moment, my PC with 96GB 
of memory and my laptop with 24GB of memory have given me a wrong sense of having abundant resources. Gone are the days where I had to adjust 
swap memory to fit applications into tiny machines having only 4GB or 6GB of memory. Has the abundance of resources made me sloppy about resource 
intuition. I need to return to that mindset and become more tuned in to my application usage and resource consumptions. 

*This essay is written for my Mac, but the principles can be applied to Windows machines as well.*


## How To Measure Things

To become resource-aware, we need to be able to know how much resources we are using. First, to know how much resources we are using, we need to 
know how to measure them. In this essay, I am going to limit to measure memory consumption only. Secondly, we need to know which applications 
to measure. Modern OSes come with many operations and they will take up resources and there is nothing we can do about those. Let's consider only 
applications that we have launched. The simplest way to check is to look at the top right corner for Mac and examine those. At the moment, I have 
the following (from left to right):


<div class="row mt-3 justify-content-center">
    {% include figure.liquid loading="eager" path="assets/img/blogs/2026-03-07/top-right.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
</div>

- Docker Desktop
- Cursor
- Zoom
- One Drive (Personal)
- One Drive (WCUPA)
- Ollama
- Rectangle
- Microsoft Teams
- Cisco AnyConnect

We also look at the open applications that are not shown on the top. A dot indicates that there is an opened instance for these applications. 


<div class="row mt-3 justify-content-center">
    {% include figure.liquid loading="eager" path="assets/img/blogs/2026-03-07/bottom.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
</div>

- Obsidian
- WezTerm
- Discord
- Zalo
- Microsoft OneNote
- Terminal
- Chrome

One approach is to use Activity Monitor to observe and estimate the resource usage. A quick view identified several culprits, including Virtual Machine Service for Docker (2GB) 
and several helpers for various other apps that could come up to 300-400MB each. As I scrolled down, there are other associated processes that are part of the same parent 
applications.

<div class="row mt-3 justify-content-center">
    {% include figure.liquid loading="eager" path="assets/img/blogs/2026-03-07/activity-monitor.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="25%" zoomable=true %}
</div>

We can type the name of an application into the search box on the top right corner of Activity Monitor to filter down to only processes related to the entered keyword, which 
would be the name of the Application. At this point, we can ballpark the memory usage of these applications. For example, Docker is costing me around 2.6G of memory, with one 
container running. 

<div class="row mt-3 justify-content-center">
    {% include figure.liquid loading="eager" path="assets/img/blogs/2026-03-07/activity-monitor-3.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="25%" zoomable=true %}
</div>

Upon further examination, the values shown in Activity Monitor are not as simple as they first appear. The per-process numbers are useful, but the overall memory picture in macOS also involves app memory, compressed memory, cached files, wired memory, and swap. 

<div class="row mt-3 justify-content-center">
    {% include figure.liquid loading="eager" path="assets/img/blogs/2026-03-07/activity-monitor-2.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="25%" zoomable=true %}
</div>

To have a simpler view for process memory consumption, perhaps we need a more systematic approach to measuring memory. This automated approach involves setting a list of applications (or keywords associated with an application), then writing a script to go through these keywords to extract individual usages and summarize their values. In this setting, my script is best understood as a simpler RSS-based estimate for user-launched processes, not a complete model of macOS memory behavior. 


First, a text file was created in which each line represents keywords associated with one of the open applications. These keywords are selected by normalizing the keyword found in 
the Activity Monitor. 

~~~
docker|virtualization
cursor
zoom
onedrive
ollama
rectangle
teams
cisco
obsidian
wezterm
discord
zalo
onenote
terminal
chrome
~~~

The bash script will iterate through these lines, extract the memory usage value from all processes that contain the keyword (assumed relationship), and add the values together. 
The script does the following:

- Read the file `apps` (content above) line by line, and store the content of the line into variable `line`.
- For each `line` (as iterated through the while loop), we will run a piped command:
    - First, `ps -axo rss,pid,pgid,comm` will display all processes. Flags `a` and `x` let `ps` displays all processes (terminal and non-terminal) from all users. The `o` 
    flag will display the results using the subsequent format, which specified `rss` (resident set size, the non-swapped physical memory that a process has used), `pid` (process 
    id), `pgid` (group id), and `comm` (starting command that launched the process). 
    - Next, the results is filtered. Using `grep`, only lines containing the values of `line` will remain. The `i` flag ignores case, and the `E` flag consider `line` as an 
    extended regular expression to support multiple keywords. 
    - Finally, `awk` process the final result and sum up the first column (`rss`) then return the value (`print`). 
    - The returned value is assigned to variable `mem`
    - The value of `mem` is added to the value of `sum_mem`, which was declared outside of the loop and initialized to 0. 
- Once the loop complete, we print out the value of `sum_mem` with conversion to MB (divided by 1024) and GB (divided by 1048576).

~~~bash
#!/usr/bin/env bash

sum_mem=0

while IFS= read -r line; do
  mem=$(ps -axo rss,pid,pgid,comm | grep -Ei "$line" | awk '{sum+=$1} END {print sum}')
  sum_mem=$((sum_mem += mem))
  echo "$line $((mem / 1024)) MB"
done < apps

echo "Total memory usage (MB then GB):"
echo "$((sum_mem / 1024)) MB"
echo "$((sum_mem / 1048576)) GB"
~~~

When I run this script, the total sum was `10GB`. Now things make sense. Out of 17-18GB of memory used up on my Mac, 10GB can be accounted for by my own running processes. 

~~~
docker|virtualization 1497 MB
cursor 1768 MB
zoom 214 MB
onedrive 163 MB
ollama 66 MB
rectangle 48 MB
teams 1093 MB
cisco 75 MB
obsidian 114 MB
wezterm 100 MB
discord 733 MB
zalo 554 MB
onenote 80 MB
terminal 82 MB
chrome 4043 MB
Total memory usage (MB then GB):
10636 MB
10 GB
~~~

So, Chrome is using up a lot of memory (4GB). I need to rein in my bazillions of opened tabs. I am not using Teams frequently, so that should go away. Discord is 
surprisingly heavy for a chat. Zalo is yet another chat, but I probably only need to maintain that for another year or so. Many of these apps are unexpectedly 
lightweight (e.g., ollama, onedrive, zoom, etc). Docker is another that eats up memory even when it is idle. 

As I was creating a draft for this essay, I had this line down: *Launch at Log In is the bane of good resource awareness*. It turns out that this anecdotal evidence 
is not quite applicable here, and most memory consumption in my case seems to show up during run time, not at startup time. That brings us to the next section, which 
is to focus on one application that can be managed. 

## Moving Forward

Being aware of computational resource consumption is important. Maybe this is the universal truth, or maybe I say it because of my history working as a research 
facilitator trying to get people to use computational resources in an efficient manner. In carrying out this measurement exercise, I got to stay aware of my applications 
and I got to practice my scripting skills a little bit. It was fun, and I should do this more often! On a more serious note, resource awareness is not nostalgia for 
weaker machines. It is part of the discipline of computing.



