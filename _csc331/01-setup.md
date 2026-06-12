---
layout: lecture
pretty_table: true
collection: csc331

title: "Setup"
toc:
  - name: Setup Docker
  - name: Setup CSC 331 Environment
  - name: Test
---

- MIT provides instructions to setup [the tools directly on Linux/Mac and Windows](https://pdos.csail.mit.edu/6.1810/2025/tools.html). You are permitted to follow these instructions directly if you do not want to use container. 

- For this class' materials, we will be using running a Docker container with additional privilege to emulate the ability to 
interact with the OS system calls. 

- It should be noted that once we access the running container via the terminal, everything should be the same regardless of the setup choice. 

## Setup Docker

- If you have not used Docker Desktop before, you can go over the [instruction on how to setup Docker Desktop](https://linhbngo.github.io/csc-workshops/intro-docker/#setup).


## Setup CSC 331 Environment

- Clone the repository

```bash
git config --global core.autocrlf false 
git clone -b csc331 https://github.com/ngo-classes/the-one-ring
cd the-one-ring
```

- An external directory is mounted to the container so that students can easily share files between the container and the host computer. 
  - The shared directory is located at `/workspace` inside the container. 
  - It is also mapped to the `workspace` directory inside the `the-one-ring` directory. 
  - All of `workspace`'s content is gitignored. 

```bash
docker image pull linhbngo/onering:csc331
docker compose up -d
docker compose exec -it csc331 /bin/bash
```

- This opens up a terminal inside the container. 
  - You are logged in by default as the `student` account, with passwordless sudo privilege. 
- Test that the tools are available inside the container

```bash
whoami
qemu-system-riscv64 --version
riscv64-unknown-elf-gcc --version
```

{% include figure.liquid loading="eager" path="assets/img/courses/csc331/setup/csc331-terminal.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true alt="Screenshot of the terminal view inside csc331 container" %}


## Customize CSC 331 Environment

- If you want to customize your own environment, you are welcomed to do so. 
  - It is highly recommended that you keep the minimal core libraries in `install.sh`.
- After the repository with the `csc331` branch has been cloned, you can edit line 5 of `docker-compose.yml` to 
change the image name to your preferred name. 
- Build and push the image

```bash
docker compose build
docker compose push
```

You can repeat the tests above to make sure that the custom container is ready to go. 