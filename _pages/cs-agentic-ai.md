---
layout: default
permalink: /csc-agentic-ai/
title: "Agentic Artificial Intelligence: Design, Implementation, and Orchestration"
nav: false
collection: csc-agentic-ai
---
 
This course explores the emerging paradigm of Agentic Artificial Intelligence, which 
are AI systems capable of reasoning, planning, and acting autonomously through structured 
protocols and external tool integration. Students will learn to design, implement, 
and deploy Model-Context-Protocol (MCP)-based agent systems, integrate multiple models 
and APIs, and evaluate their ethical, cognitive, and computational implications.

The course emphasizes applied construction and reflective practice over rote theory. 
Students will build containerized agent workflows, practice context and protocol design, 
and engage in iterative *fail-and-survive* learning cycles to develop robust technical 
and critical thinking skills. 

<div class="post">
  <ul class="post-list">
    {% assign postlist = site.csc-agentic-ai %}
    {% for post in postlist %}
        {% assign year = post.date | date: "%Y" %}
        {% assign tags = post.tags | join: "" %}
        {% assign categories = post.categories | join: "" %}

        <li>
            <h3>
                {% if post.redirect == blank %}
                    <a class="post-title" href="{{ post.url | relative_url }}">{{ post.title }}</a>
                {% elsif post.redirect contains '://' %}
                    <a class="post-title" href="{{ post.redirect }}" target="_blank">{{ post.title }}</a>
                    <svg width="2rem" height="2rem" viewBox="0 0 40 40" xmlns="http://www.w3.org/2000/svg">
                        <path d="M17 13.5v6H5v-12h6m3-3h6v6m0-6-9 9" class="icon_svg-stroke" stroke="#999" stroke-width="1.5" fill="none" fill-rule="evenodd" stroke-linecap="round" stroke-linejoin="round"></path>
                    </svg>
                {% else %}
                    <a class="post-title" href="{{ post.redirect | relative_url }}">{{ post.title }}</a>
                {% endif %}
            </h3>
            <p>{{ post.description }}</p>
        </li>
    {% endfor %}
  </ul>
</div>
