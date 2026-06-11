---
layout: lecture
pretty_table: true
collection: csc331

title: "Infrastructure"
toc:
  - name: Setup Docker
  - name: Setup
  - name: Test
---

- MIT provides instructions to setup [the tools directly on Linux/Mac and Windows](https://pdos.csail.mit.edu/6.1810/2025/tools.html). You are permitted to follow these instructions directly if you do not want to use container. 

- For this class' materials, we will be using running a Docker container with additional privilege to emulate the ability to 
interact with the OS system calls. 

- It should be noted that once we access the running container via the terminal, everything should be the same regardless of the setup choice. 

## Setup Docker

- If you have not used Docker Desktop before, you can go over the instruction on how to setup Docker Desktop at 
[Docker for Classroom: Quick Setup Reminder](https://cs.wcupa.edu/LNGO/courses/workshops/docker-environment/#1-quick-setup-reminder).

---

## Setup

{% details Fall 2025 students %}

This setup has been updated and simplified. If you have setup the CSC331 environment already, you should carry out the following steps to reset and repull/rebuild your images. 

- First, stop all running containers (`login` and `csc331`).
- Clean up all stopped containers (type `y` and press `Enter` when asked)

```bash
docker container prune
```

- Remove the previous images

```bash
docker image rm linhbngo/onering:login
docker image rm linhbngo/onering:csc331
```

{% enddetails %}
- Clone the repository (if you don't have it already)

```bash
git config --global core.autocrlf false
git clone https://github.com/ngo-classes/the-one-ring
cd the-one-ring
```

- Pull the images

```bash
docker image pull linhbngo/onering:csc331
docker compose -f docker-compose.yml up csc331
```

## Test

- We first test the ability to access the browser-based Code server environment by open a browser and visit `127.0.0.1:18088` or `localhost:18088`. 
    - Enter `goldenrams` as the password to login. 
    - You should see the Code server browser view of `/home/student`

{% include figure.liquid path="assets/img/courses/csc331/setup/01.png" width="50%" zoomable=true %}

- You can also ssh into the container from your host computer's terminal via the port `22331`.
    - While there is a built-in terminal inside the Code browser, sometimes additional separate terminal instances will be useful for this class. 

~~~bash
ssh -p 22331 student@localhost
~~~

{% include figure.liquid path="assets/img/courses/csc331/setup/02.png" width="50%" zoomable=true %}
