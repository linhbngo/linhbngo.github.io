---
layout: lecture
pretty_table: true
order: 1
title: Introduction to Docker Containers
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
  - name: Setup
  - name: Introduction to Docker
  - name: Docker Images
  - name: Docker on Linux (in-class activities)
---

# Introduction to Docker Containers

---

## 1. Setup

{% details Older version of Docker Desktop %}

If you had previously installed Docker Desktop on your system, you need to 
make sure that what you have installed is up to date. The latest Docker Desktop 
and the accompanying Docker Engine contain many useful tools to help administrating 
your images and containers. 

This material is written on:
    - Docker Desktop version `4.35.1 (173168)`
    - Docker Engine: `27.3.1`
    - Docker Compose: `v2.29.7-desktop.1`

It is possible that by the time that you read this setup, the versions you have 
will be higher. That would be a good thing!

{% enddetails %}
{% details Links to download and install Docker Desktop %}

- Select the appropriate link for your computing platform:
    - [Mac](https://docs.docker.com/desktop/setup/install/mac-install/)
    - [Windows](https://docs.docker.com/desktop/setup/install/windows-install/)
        - **You should run Linux containers when installing Docker Desktop for Windows**
        - It is recommended that you use WSL2 option when installing Docker Desktop on Windows
    - [Linux](https://docs.docker.com/desktop/setup/install/linux/)
- Successful installation and startup of Docker will show the following application
    - Screenshot is taken on a Mac, but the GUI should be the same across platforms
    {% include figure.liquid path="assets/img/courses/csc468/docker/docker-desktop-mac.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Docker Desktop Terminal %}

- The most recent version of Docker Desktop comes with a built-in Terminal. 
- If you are running the latest Docker Desktop version (4.35.1), this is a default feature 
available on the lower right corner of the GUI. 
- For earlier versions, this could show up as a beta feature. 

{% include figure.liquid path="assets/img/courses/csc468/docker/docker-desktop-mac-terminal.png" width="50%" zoomable=true %}

- The remainder of this workshop will use the Docker Desktop Terminal app for 
consistency purpose. All the CLI docker commands can be executed on the standard 
Linux-based terminal of Mac and Linux platforms. 

{% enddetails %}
{% details Docker Hub %}

- Docker Hub is one of the public repository for Docker images (think GitHub for 
container images). 
- You should register for Docker Hub account at [https://hub.docker.com](https://hub.docker.com) 
and use it to log into your Docker Desktop environment (similar to how you link your 
GitHub account to GitHub Desktop, if you use GitHub Desktop).

{% enddetails %}
---

## 2. Introduction to Docker

{% details Motivation %}

- Limit the chaos between computing platforms of 
    - Development and production
    - Developers, Testers, and Users
    - Dependencies of various software components 
    across a full-stack infrastructure
    - ...
- Inspiration
    - Shipping containers
    - Ship anything under any forms anywhere

{% enddetails %}
{% details Getting started %}

- Launch your Docker Desktop app
- Open the built-in terminal and run

~~~bash
docker version
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/docker-version.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Overview of Docker %}

- Docker is client-server application.
    - Docker daemon (Engine): receives and processes incoming Docker API request 
    and requires root privilege.
    - Docker Hub registry: collection of public images (https://hub.docker.com/).
    - Docker client : Talks to the Docker daemon via the docker API and the registry API.

{% enddetails %}
{% details Hands-on: Hello world %}


- Docker `containers` are instantiated from Docker `images`. 
- You can check availability of local `images` and `containers`. 

~~~bash
docker image ls
docker container ls
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/docker-ls.png" width="50%" zoomable=true %}

- If you click on the `Images` and `Container` tabs, you can also confirm 
that there is no existing container or image on your Docker environment. 

{% include figure.liquid path="assets/img/courses/csc468/docker/gui-container-image.png" width="50%" zoomable=true %}

- We want to issue the following to start a service that will echo 
`hello world` to the screen. 
    - This requires a Linux container to run the `echo` command. 

~~~bash
docker run alpine echo hello, world
docker image ls
docker container ls 
docker container ls --all
~~~

- The outcomes of the above commands are shown in the screenshot below
    - User want to run a Linux command using an alpine Linux container
    - There is no locally available alpine image, therefore Docker goes 
    ahead and download the image. 
    - Docker uses the image as a blueprint to launch a container, which 
    then executes the `echo hello, world` command. 
    - The container is shutdown after the execution. 

{% include figure.liquid path="assets/img/courses/csc468/docker/cli-docker-run.png" width="50%" zoomable=true %}

- `docker run alpine echo hello world`
    - `docker`: invoke the container engine. 
    - `run`: subcommand to run a container. 
    - `alpine`: name of the image based on which a container will be launched. 
    - `echo hello, world`: the command to be executed in the container environment. 
- `docker image ls`
    - Now an image shows up (it has just been downloaded)
    - The Image tab should also show the alpine image
- `docker container ls`
    - There is no running container listed. Although, you can see from the GUI 
    that there was a container there. 
- `docker container ls --all`
    - This command shows **all** containers, including those that finished running. 

{% enddetails %}
{% details Hands-on: Interactive container %}

- We can launch a container and get into the shell of the container. 

~~~bash
docker run -it ubuntu bash
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/cli-docker-run-interactive.png" width="50%" zoomable=true %}

- You are now in a new prompt: a shell inside the container
    - **notice the changes in the prompt comparing to the previous prompt where you 
    type in the docker run ... command**
    - This is important when you are on the terminal to know whether you are 
    inside the container's environment or the host machine's environment. 
- `-it`: combination of `-i` and `-t`. 
  - `-i` tells Docker to connect to the container’s stdin for interactive mode
  - `-t` tells Docker that we want a pseudo-terminal
- Let's attempt to run `figlet` inside the container (`#` prompt)

~~~bash
figlet hello
~~~

- There will be an error: `bash: figlet: command not found`
- The current container does not have the `figlet` program yet. 
- Let's install `figlet` inside the container (`#` prompt)

~~~bash
apt update -qq
apt install -y -qq figlet
figlet hello
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/cli-docker-run-figlet.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Exercise: exit container %}

- Type `exit` to shutdown the container and back to your normal terminal. 
- Repeat the process of launching an interactive container from start and try 
running `figlet` again. 
- Is the `figlet` program still there?

{% details Solution %}

- The `figlet` program is no longer available again. 
- Notice the recently shutdown container and the newly created container 
from the upper half of the GUI. 

{% include figure.liquid path="assets/img/courses/csc468/docker/cli-docker-run-figlet-exercise.png" width="50%" zoomable=true %}

{% enddetails %}
{% enddetails %}
{% details Hands-on: Background container %}


- You should have already exited out of the container shell and 
back to the host machine environment. 
- Run the following command
    - Press `Ctrl-C` to stop after a few time stamps. 

~~~bash
docker run ubuntu /bin/sh -c "while date; do sleep 1; done"
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/cli-docker-run-date.png" width="50%" zoomable=true %}

- Run the following command 

~~~bash
docker run -d jpetazzo/clock
docker container ls
~~~

- Notice in the screenshot that you are now returned to the host machine's 
terminal. 
- A running container is shown in both the `docker container ls` command 
and in the GUI's container tab. 
- The hash string, underlined by the red line, is a unique identifier 
for containers. 

{% include figure.liquid path="assets/img/courses/csc468/docker/cli-docker-run-date-BG.png" width="50%" zoomable=true %}

- Use the first four characters of your container ID to view the 
log of the running Docker container
    - From the above screenshot, it is `cd16`
- Use `--tail N` to only look at latest `N` lines of the log. 

~~~bash
docker logs --tail 5 cd16
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/cli-docker-logs.png" width="50%" zoomable=true %}

- To kill a running container, you can use `docker kill` with the container 
ID or click on the `Stop` or `Trash Can` icons on the container's line inside the 
GUI's Container tab. 

{% enddetails %}
{% details Hands-on: Memory limit %}


- How does Docker help restrict resources?

~~~bash
docker run -it --memory 100M ubuntu bash
~~~

- `--memory`: limit size of memory in bytes, megabytes (M), ...
- Test the limits:

~~~bash
apt update
apt install -y stress
stress --vm 1 --vm-bytes 99M --vm-keep
stress --vm 1 --vm-bytes 101M --vm-keep
~~~

{% enddetails %}
---

## 3. Docker Images

{% details Docker images %}

- Image = files + metadata
- The files form the root filesystem of the container
- The metadata describes things such as:
    - The author of the image
    - The command to execute in container when starting it
    - Environment variables to be set
    - ...
- Images are made of layers, conceptually stacked on top of each other.
- Each layer can add, change, and remove files and/or metadata.
- Images can share layers to optimize disk usage, transfer times, and memory use.

{% enddetails %}
{% details Example of a Java webapp %}

- CentOS base layer
- Packages and configuration files added by our local IT
- JRE
- Tomcat
- Our application’s dependencies
- Our application code and assets
- Our application configuration

{% enddetails %}
{% details The read-write layer %}

{% include figure.liquid path="assets/img/courses/csc468/docker/rw-layer.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Containers versus images %}

- An image is a read-only filesystem.
- A container is an encapsulated set of processes running in a 
read-write copy of that filesystem.
- To optimize container boot time, copy-on-write is used instead of regular copy.
- `docker run` starts a container from a given image. 

{% include figure.liquid path="assets/img/courses/csc468/docker/container-image.png" width="50%" zoomable=true %}

- Object-oriented analogy
    - Images are conceptually similar to classes
    - Layers are conceptually similar to inheritance
    - Containers are conceptually similar to instances

{% enddetails %}
{% details How do we change an image? %}

- It is read-only, we don’t.
- We create a new container from the image
- We make changes to the container. 
- When we are satisfied with the changes, we transform them into a new layer.
- A new image is created by stacking the new layer on top of the old image.

{% enddetails %}
{% details Image namespaces %}

- Official images (ubuntu, busybox, …)
    - Root namespace. 
    - Small, distro images to be used as bases for the building process.
    - Ready-to-use components and services (redis, postgresl …)
- User (and organizations) images: `<registry_name>/<image_name>:[version]`
    - linhbngo/csc331:latest
- Self-hosted images
    - Images hosted by third party registry
    - `URL/<image_name>`

{% enddetails %}
{% details Hands-on: listing local images and searching for new images %}


- At this point, you should have at least two images 
downloaded to Docker's local repository: `alpine` and `ubuntu`. 

~~~bash
docker image ls
~~~

- The command should show two outputs clearly. 
- You should also see the images listed in the `Image` tab 
of Docker Desktop, on the top portion of the GUI. 

{% include figure.liquid path="assets/img/courses/csc468/docker/docker-image.png" width="50%" zoomable=true %}

- We can search for available images in the public Docker Hub 

~~~bash
docker search mysql
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/docker-search.png" width="50%" zoomable=true %}

{% enddetails %}
{% details General steps to create an image %}


- Create a container using an appropriate base distro
- Inside the container, install and setup the necessary software
- Review the changes in the container
- Turn the container into a new image
- Tag the image

{% include figure.liquid path="assets/img/courses/csc468/docker/image-create.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Hands-on: create a container with a base distro %}

- Launch an interactive bash shell on a running container

~~~bash
clear
docker run -it ubuntu /bin/sh
~~~

- Install `figlet`, test, then exit the container
    - **Remember the hash id of your container**

~~~bash
apt update -qq
apt install -y -qq figlet
figlet hellp
exit
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/image-create-container.png" width="50%" zoomable=true %}

- From the screenshot above, next to the top container (the one that just got 
started and stopped 56 seconds ago), you can see the ID `cb2149...`
- It is possible to check for the differences between this container and 
the base image with the ID and `docker diff`

~~~bash
docker diff cb21
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/image-docker-diff.png" width="50%" zoomable=true %}

- A: A file or directory was added
- C: A file or directory was changed
- D: A file or directory was deleted


{% enddetails %}
{% details Hands-on: commit changes into a new image %}


- We are still using the container from the previous example. 
    - From the first screenshot in the previous example, next to 
    the top container (the one that just got started and stopped 
    56 seconds ago), you can see the ID `cb2149...`
- Run the following commands
    - Do not use **linhbngo**. It is my Docker login. You should use 
    your Docker login. 

~~~bash
docker commit cb21 linhbngo/ubuntu_figlet:1.0
docker image ls
~~~

- The `docker commit ...` command created a new image named `ubuntu_figlet` that 
is associated with the DockerHub account `linhbngo` (my DockerHub account). This 
combination (`linhbngo/ubuntu_figlet`) is called a repository, and has the tag `1.0`. 
- The `docker image ls` command shows this image and other images available locally 
for Docker. 

{% include figure.liquid path="assets/img/courses/csc468/docker/image-docker-commit.png" width="50%" zoomable=true %}

- In reviewing the previous screenshot, you can se that a new image has been 
created with a size of 144MB. 
    - The original Ubuntu image has a size of 101MB.

- We can examine the layers of the newly committed image by running the 
command `docker history ...` as shown below.  

~~~bash
docker history 2379
~~~

- The previous screenshot also shows that the new layer making up the new image
has a size of 43.3MB. This, adding to the base ubuntu image, is what giving 
the new image the size of 144MB (101 + 43.3).
    - Docker will not duplicate the base layer, but will reuse this layer storage 
    when additional new images are created from the same base. 
- You can now push the new image up to Docker Hub:
    - If you are not logging into Docker Hub from DockerDesktop, or 
    are running on an external terminal, you will need to run `docker login` first 
    to sign in to your Docker Hub account. 

~~~bash
docker push linhbngo/ubuntu_figlet:1.0
~~~

{% enddetails %}
---

## 4. Docker on Linux (in-class activities)

{% details CloudLab Experiment Setup %}

- Instantiate an experiment from your existing CloudLab profile

{% enddetails %}
{% details Docker on Linux %}

- Follow the [Install Docker Engine on Ubuntu](https://docs.docker.com/engine/install/ubuntu/) guide to setup Docker inside your experiment.
- Repeat all previous Docker commands/activities for this lecture to practice. 

{% enddetails %}
