---
layout: lecture
pretty_table: true
order: 1
title: Docker Compose
mermaid:
  enabled: true
  zoomable: true
code_diff: true
map: true
chart:
  chartjs: true
  echarts: true
  vega_lite: true
tikzjax: true
typograms: true

toc:
  - name: Imperative versus Declarative
  - name: Docker Compose
  - name: "Example Compose File: Multiple Services"
  - name: "Example Compose File: A cluster of computers"
---

# Docker Compose

---

## Imperative versus Declarative

To understand why Docker Compose is powerful, we must distinguish between two fundamental programming paradigms:
- Imperative Programming
- Declarative Programming

{% details Imperative Programming: The How %}

- You write code that explicitly defines the step-by-step sequence of actions the computer must take to reach a goal. It relies heavily on action verbs and control flow (loops, if/then statements).
- Most major programming languages are designed this way: C, Java, Python, and Bash scripts. 

{% enddetails %}
{% details Declarative Programming: The What %}

- You write code that describes the *desired end state* without specifying 
the exact steps to get there. An underlying engine reads your description and handles the 
imperative execution automatically.
- SQL is one example of this. While there are *action words* (SELECT, ADD, SORT), the intention is 
still about what you desire your data to be, not how to shape the data that way. HTML is another 
example where you describe the layout, not how to draw pixels on the screen. 

{% enddetails %}
---

## Docker Compose

{% details Why? %}

- Dockerfile is a great mechanism for describing the steps for building container images.
    - This is imperative by nature (*COPY* this, *RUN* that, ...)
- It starts to become more complex when you want to arrange these containers into more 
complex infrastructure.
- We want another layer of abstraction to help us *declare* what we want out of all 
these building blocks.  
- This is possible via Docker Compose.

{% enddetails %}
{% details In a nutshell %}

- External, Python-based tool. 
- Open source.
- Simple deployment workflow
    - Checkout code
    - Run `docker compose up`
    - Everything is up and running!

{% enddetails %}
{% details Overview of compose %}

- Design of a container stack is declared/described in a YAML file typicalled 
named called `docker-compose.yml`.
    - Similar to docker build, `-f` flag can be used to specified non-standard 
    compose file names. 
- Run `docker compose up`.
- Compose automatically pulls images, builds containers, and starts them. 
- Compose can
    - Set up links, volumes, and other Docker options for the container stack. 
    - Run containers in the background or in the foreground.

{% enddetails %}
---

## Example Compose File: Multiple Services

{% details The ramcoin miner! %}


- Run the following commands:

~~~bash
cd
git clone https://github.com/CSC468-WCU/ram_coin.git
cd ram_coin
docker compose up
~~~

- Visit `YOUR_CLOUDLAB_HEADNODE:YOUR_CHOSEN_PORT` to see the deployed webserver. 
- Does it work?
- Open another terminal, connect to your CloudLab node and run `docker ps` to see 
how many containers were deployed by the docker-compose. 
- Press `Ctrl-C` to stop the containers. 

{% enddetails %}
{% details Sections of a compose file %}

- Use `cat` or `nano` to view `docker-compose.yaml` file. 
- `version` used to be mandatory, now is optional (“2” or later).
    - Version 1 is legacy.
    - Version 2 has support for networks and volumes.
    - Version 3 has support for deployment options.
- `services` is mandatory. A service is one or more replicas of the same 
image running as containers.
- `networks` is optional and indicates to which networks containers should be connected. 
By default, containers will be connected on a private, per-compose-file network.
- `volumes` is optional and can define volumes to be used and/or shared by the containers. 

{% enddetails %}
{% details Containers in docker-compose.yaml %}

- Each service in the YAML file must container either `build` or `image`.
- `build` indicates a path containing a Dockerfile.
- `image` indicates an image name (local or on registry).
- If both are specified, an image will be built from the build directory and named `image`
- Other parameters are optional and typically what you would add to docker run
    - command = `CMD`
    - ports = `-p`
    - volumes = `-v`

{% enddetails %}
{% details Hands-on: Rerun ram_coin in background %}


~~~bash
docker compose -d up
docker compose ps
~~~

{% enddetails %}
{% details Hands-on: cleanup %}


~~~bash
docker compose kill
docker compose rm
~~~

{% enddetails %}
---

## Example Compose File: A cluster of computers

{% details CSC466 computing environment %}

[Git repository](https://github.com/ngo-classes/csc466env)
{% enddetails %}
