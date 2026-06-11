---
layout: lecture
pretty_table: true
order: 2
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
  - name: Infrastructure as Code
  - name: "Infrastructure as Code: Storage"
  - name: "Infrastructure as Code: Networking"

---


## Setup

{% details warning Older version of Docker Desktop %}

If you had previously installed Docker Desktop on your system, you need to 
make sure that what you have installed is up to date. The latest Docker Desktop 
and the accompanying Docker Engine contain many useful tools to help administrating 
your images and containers. 

This material is written on:
    - Docker Dekstop version `4.35.1 (173168)`
    - Docker Engine: `27.3.1`
    - Docker Compose: `v2.29.7-desktop.1`

It is possible that by the time that you read this setup, the versions you have 
will be higher. That would be a good thing!

{% enddetails %}

{% details note Links to download and install Docker Desktop %}

- Select the appropriate link for your computing platform:
    - [Mac](https://docs.docker.com/desktop/setup/install/mac-install/)
    - [Windows](https://docs.docker.com/desktop/setup/install/windows-install/)
        - **You should run Linux containers when installing Docker Desktop for Windows**
        - It is recommended that you use WSL2 option when installing Docker Desktop on Windows
    - [Linux](https://docs.docker.com/desktop/setup/install/linux/)

{% enddetails %}

- Successful installation and startup of Docker will show the Docker Desktop Dashboard
    - This screenshot is taken on a Mac, but the GUI should be the same across platforms

{% include figure.liquid loading="eager" path="assets/img/courses/csc-workshops/docker/docker-desktop-mac.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="25%" zoomable=true %}


- You should also carry out a test for Docker inside a terminal.
    - Mac: If you have not used a Terminal on Mac before, click the Magnifying Glass icon (top right) and type in `Terminal` to find the app. 
    - Windows: It is highly recommended that you download and use the Terminal App from Windows Store. For Windows 11+, this has become a default application. 

{% include figure.liquid loading="eager" path="assets/img/courses/csc-workshops/docker/docker-desktop-mac-terminal.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="25%" zoomable=true %}


{% details tip Docker Hub %}

- Docker Hub is one of the public repository for Docker images (think GitHub for 
container images). 
- You should register for Docker Hub account at [https://hub.docker.com](https://hub.docker.com) 
and use it to log into your Docker Desktop environment (similar to how you link your 
GitHub account to GitHub Desktop, if you use GitHub Desktop).

{% enddetails %}

## Introduction to Docker

{% details note Motivation %}

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
{% details note Getting started %}

- Launch your Docker Desktop app
- Open the built-in terminal and run

~~~bash
docker version
~~~

{% include figure.liquid path="fig/docker/docker-version.png" %}

{% enddetails %}
{% details note Overview of Docker %}

- Docker is client-server application.
    - Docker daemon (Engine): receives and processes incoming Docker API request 
    and requires root privilege.
    - Docker Hub registry: collection of public images (https://hub.docker.com/).
    - Docker client : Talks to the Docker daemon via the docker API and the registry API.

{% enddetails %}
{% details example Hands-on: Hello world %}


- Docker `containers` are instantiated from Docker `images`. 
- You can check availability of local `images` and `containers`. 

~~~bash
docker image ls
docker container ls
~~~

{% include figure.liquid path="fig/docker/docker-ls.png" %}

- If you click on the `Images` and `Container` tabs, you can also confirm 
that there is no exissting container or image on your Docker envrironment. 

{% include figure.liquid path="fig/docker/gui-container-image.png" %}

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

{% include figure.liquid path="fig/docker/cli-docker-run.png" %}

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
{% details example Hands-on: Interactive container %}

- We can launch a container and get into the shell of the container. 

~~~bash
docker run -it ubuntu bash
~~~

{% include figure.liquid path="fig/docker/cli-docker-run-interactive.png" %}

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

{% include figure.liquid path="fig/docker/cli-docker-run-figlet.png" %}


{% enddetails %}
{% details question Exercise: exit container %}

- Type `exit` to shutdown the container and back to your normal terminal. 
- Repeat the process of launching an interactive container from start and try 
running `figlet` again. 
- Is the `figlet` program still there?

{% details tip Solution %}

- The `figlet` program is no longer available again. 
- Notice the recenlty shutdown container and the newly created container 
from the upper half of the GUI. 

{% include figure.liquid path="fig/docker/cli-docker-run-figlet-exercise.png" %}

{% enddetails %}
{% enddetails %}
{% details example Hands-on: Background container %}


- You should have already exited out of the container shell and 
back to the host machine environment. 
- Run the following command
    - Press `Ctrl-C` to stop after a few time stamps. 

~~~bash
docker run ubuntu /bin/sh -c "while date; do sleep 1; done"
~~~

{% include figure.liquid path="fig/docker/cli-docker-run-date.png" %}

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

{% include figure.liquid path="fig/docker/cli-docker-run-date-BG.png" %}

- Use the first four characters of your container ID to view the 
log of the running Docker container
    - From the above screenshot, it is `cd16`
- Use `--tail N` to only look at latest `N` lines of the log. 

~~~bash
docker logs --tail 5 cd16
~~~

{% include figure.liquid path="fig/docker/cli-docker-logs.png" %}

- To kill a running container, you can use `docker kill` with the container 
ID or click on the `Stop` or `Trash Can` icons on the container's line inside the 
GUI's Container tab. 

{% enddetails %}
## Docker Images

{% details note Docker images %}

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
{% details note Example of a Java webapp %}

- CentOS base layer
- Packages and configuration files added by our local IT
- JRE
- Tomcat
- Our application’s dependencies
- Our application code and assets
- Our application configuration

{% enddetails %}
{% details note The read-write layer %}

{% include figure.liquid path="fig/docker/rw-layer.png" %}

{% enddetails %}
{% details note Containers versus images %}

- An image is a read-only filesystem.
- A container is an encapsulated set of processes running in a 
read-write copy of that filesystem.
- To optimize container boot time, copy-on-write is used instead of regular copy.
- `docker run` starts a container from a given image. 

{% include figure.liquid path="fig/docker/container-image.png" %}

- Object-oriented analogy
    - Images are conceptually similar to classes
    - Layers are conceptually similar to inheritance
    - Containers are conceptually similar to instances

{% enddetails %}
{% details note How do we change an image? %}

- It is read-only, we don’t.
- We create a new container from the image
- We make changes to the container. 
- When we are satisfied with the changes, we transform them into a new layer.
- A new image is created by stacking the new layer on top of the old image.

{% enddetails %}
{% details note Image namespaces %}

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
{% details example Hands-on: listing local images and searching for new images %}


- At this point, you should have at least two images 
downloaded to Docker's local repository: `alpine` and `ubuntu`. 

~~~bash
docker image ls
~~~

- The command should show two outputs clearly. 
- You should also see the images listed in the `Image` tab 
of Docker Desktop, on the top portion of the GUI. 

{% include figure.liquid path="fig/docker/docker-image.png" %}

- We can search for available images in the public Docker Hub 

~~~bash
docker search mysql
~~~

{% include figure.liquid path="fig/docker/docker-search.png" %}

{% enddetails %}
{% details note General steps to create an image %}


- Create a container using an appropriate base distro
- Inside the container, install and setup the necessary software
- Review the changes in the container
- Turn the container into a new image
- Tag the image

{% include figure.liquid path="fig/docker/image-create.png" %}


{% enddetails %}
{% details example Hands-on: create a container with a base distro %}

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

{% include figure.liquid path="fig/docker/image-create-container.png" %}

- From the screenshot above, next to the top container (the one that just got 
started and stopped 56 seconds ago), you can see the ID `cb2149...`
- It is possible to check for the differences between this container and 
the base image with the ID and `docker diff`

~~~bash
docker diff cb21
~~~

{% include figure.liquid path="fig/docker/image-docker-diff.png" %}

- A: A file or directory was added
- C: A file or directory was changed
- D: A file or directory was deleted


{% enddetails %}
{% details example Hands-on: commit changes into a new image %}


- We are still using the container from the previous example. 
    - From the first screenshot in the previous example, next to 
    the top container (the one that just got started and stopped 
    56 seconds ago), you can see the ID `cb2149...`
- Run the following commands

~~~bash
docker commit cb21 linhbngo/ubuntu_figlet:1.0
docker image ls
~~~

- The `docker commit ...` command created a new image named `ubuntu_figlet` that 
is associated with the DockerHub account `linhbngo` (my DockerHub account). This 
combination (`linhbngo/ubuntu_figlet`) is called a repository, and has the tag `1.0`. 
- The `docker image ls` command shows this image and other images available locally 
for Docker. 

{% include figure.liquid path="fig/docker/image-docker-commit.png" %}

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
{% details note Automatic image construction: Dockerfile %}


- A build recipe for a container image.
- Contains a series of instructions telling Docker/Podman how an image is to be constructed.
- The `docker build` command builds an image from a Dockerfile.


{% enddetails %}
{% details example Hands on: writing the first Dockerfile %}


- The following commands are done in the terminal (Ubuntu WSL on Windows/Mac Terminal). 

~~~bash
cd
mkdir myimage
cd myimage
nano Dockerfile
~~~

- Type the following contents into the nano editor.
    - To save and quit nano, press `Ctrl-X` (or `Control-X` for Mac)
    - Type Y when asked to `Save modified buffer`
    - Press `Enter`. 

<script src="https://gist.github.com/linhbngo/b9f794bed306562f2eb85da310ae7b5e.js?file=Dockerfile.1"></script>

- Content of the above Dockerfile
    - `FROM`: the base image for the build
    - `RUN`: represents one layer of execution. 
    - `RUN` commands must be non-interactive.
- To build the image, you can run the following commands:
    - Assumption: you are still inside `myimage`
    - This could be checked with `pwd`. 

~~~bash
pwd
ls
docker build -t linhbngo/ubuntu_figlet:2.0 .
~~~

- `-t` indicates a tag named `figlet` will be applied to the image. 
- `.` indicates that the `Dockerfile` file is in the current directory. 

{% include figure.liquid path="fig/docker/image-docker-build.png" %}

- Running `docker image ls` and examining the GUI's Image tab, you will 
see that there are now two tags for the same repository name. If you run 
`docker push` and check your Docker Hub repo, you will see the second 
tag now stored in the same repository

~~~bash
docker push linhbngo/ubuntu_figlet:2.0
~~~

{% include figure.liquid path="fig/docker/image-docker-push.png" %}

{% enddetails %}
{% details question Exercise: test new image %}

- Test run the new `ubuntu_figlet` image by launching an interactive 
container using this image, then immediately run `figlet hello world`. 

{% details tip Solution %}

- Replace `linhbngo` with your own DockerHub account

~~~bash
docker run -it linhbngo/ubuntu_figlet:2.0 /bin/bash
figlet hello world
exit
~~~

{% include figure.liquid path="fig/docker/image-test-image.png" %}


{% enddetails %}
{% enddetails %}
## Infrastructure as Code

{% details note Overview %}

- Containers can be customized to run as programs/services
    - Barebone containers with just enough dependencies packages
- Customizable parameteres to feed to containers at start time
- Ephemeral/persistent storages
- Network infrastructures

{% enddetails %}
{% details note CMD and ENTRYPOINT %}

- Both commands enable containers to run a default program or script. 
- `CMD` executes a default program or script with a predefined set of parameters. 
    - To be run if the container is invoked without any command.
- `ENTRYPOINT` defines a default program or script with a predefined set of parameters, 
but also allows users to append additional parameters to `docker run` call.  

{% enddetails %}
{% details example Hands on: CMD %}


- Edit your Dockerfile so that it has the following content

<script src="https://gist.github.com/linhbngo/b9f794bed306562f2eb85da310ae7b5e.js?file=Dockerfile.2"></script>

- Rebuild the image with the tag `linhbngo/ubuntu_figlet:3.0`. 
- Run the following command

~~~bash
cd
cd myimage
docker build -t linhbngo/ubuntu_figlet:3.0 .
docker run -it linhbngo/ubuntu_figlet:3.0
~~~

{% include figure.liquid path="fig/docker/image-create-cmd.png" %}

{% enddetails %}
{% details question Exercise: storage consumption %}

- Run the following commands

~~~bash
docker image ls
~~~

- Did we use any additional storage for this new image?
    - Hint: Try running `docker system df`

{% details tip Solution %}


{% enddetails %}
{% include figure.liquid path="fig/docker/image-storage.png" %}

{% enddetails %}
{% details example Hands on: ENTRYPOINT %}

- Edit `Dockerfile` as follows:

<script src="https://gist.github.com/linhbngo/b9f794bed306562f2eb85da310ae7b5e.js?file=Dockerfile.3"></script>

- Rebuild the image with the tag `linhbngo/ubuntu_figlet:4.0`.  
- Run the followings:

~~~bash
docker build -t linhbngo/ubuntu_figlet:4.0 .
docker run linhbngo/ubuntu_figlet:4.0
docker run linhbngo/ubuntu_figlet:4.0 golden rams
~~~

- Notice that the first `docker run`, without any input parameters, does not generate any text. 
- The second `docker run` takes `golden rams` and feeds it to the figlet command specified by `ENTRYPOINT`. 

{% include figure.liquid path="fig/docker/image-entrypoint.png" %}

{% enddetails %}
{% details example Hands on: Using both ENTRYPOINT and CMD %}


- `ENTRYPOINT` and `CMD` can be used together. 
- The command line arguments are appended to those parameters. 
- Edit `Dockerfile` as follows:

<script src="https://gist.github.com/linhbngo/b9f794bed306562f2eb85da310ae7b5e.js?file=Dockerfile.4"></script>

- Rebuild the image with the tag `linhbngo/ubuntu_figlet:5.0`. 
- Run the followings:

~~~bash
docker build -t linhbngo/ubuntu_figlet:5.0 .
docker run linhbngo/ubuntu_figlet:5.0
docker run linhbngo/ubuntu_figlet:5.0 golden rams
~~~

{% include figure.liquid path="fig/docker/image-cmd-entrypoint.png" %}

- Caveat with `ENTRYPOINT`: `/bin/bash` does not work as expected.  
    - Need to override with `--entrypoint` flag.

~~~bash
docker run -it linhbngo/ubuntu_figlet:5.0
docker run -it --entrypoint bash linhbngo/ubuntu_figlet:5.0
exit
~~~

{% enddetails %}
## Infrastructure as Code: Storage

{% details note Overview %}

- Docker images are immutable (read-only)
- Docker containers are mutable, but are available only for the running duration 
of the containers. 
    - Once containers are shutdown, to retain modifications, they need to be made 
    immutable. 
- How do we reconcile new data into Docker images/containers?
    - Copy data into images during the building process
    - Mount storage directory from host machines into containers at run time


{% enddetails %}
{% details note COPY %}

- `COPY src dst`
- Copy contents into the image prior to the installation steps. 
- Need to be done prior to `RUN` statements. 

{% enddetails %}
{% details example Hands on: Importing and building external code using COPY %}

- Inside the `myimage` directory
- Create the following file called `hello.c`:

<script src="https://gist.github.com/linhbngo/b9f794bed306562f2eb85da310ae7b5e.js?file=hello.c"></script>

- Create the following Dockerfile called `Dockerfile.hello`:

<script src="https://gist.github.com/linhbngo/b9f794bed306562f2eb85da310ae7b5e.js?file=Dockerfile.5"></script>

- You can build an image with a specific Dockerfile

~~~bash
docker build -t linhbngo/hello:1.0 -f Dockerfile.hello .
docker run linhbngo/hello:1.0
~~~

{% include figure.liquid path="fig/docker/image-docker-build-copy.png" %}

{% enddetails %}
{% details example Hands on: Mounting external storage to running containers %}

- Create a directory called `src` inside `myimage`.
- Copy `hello.c` into this directory.

~~~bash
mkdir src
cp hello.c src/
~~~

- Create the following Dockerfile called `Dockerfile.gcc`:

<script src="https://gist.github.com/linhbngo/b9f794bed306562f2eb85da310ae7b5e.js?file=Dockerfile.8"></script>

~~~bash
docker build -t linhbngo/gcc:1.0 -f Dockerfile.gcc .
docker run -it -v ./src:/ext_src linhbngo/gcc:1.0
~~~

- From the screenshot below, notice that after exiting out of the container, the newly 
created binary file `hello` still persists. 

{% include figure.liquid path="fig/docker/image-volume.png" %}

{% enddetails %}
## Infrastructure as Code: Networking

{% details note Networking for container %}


- How can services provided by a container become available to the world? 
  - Piggyback on the host machine's network.
  - Docker has supporting drivers for containers:
      - `bridge`:	The default network driver.
      - `host`:	Remove network isolation between the container and the Docker host.
      - `none`:	Completely isolate a container from the host and other containers.
      - `overlay`:	Overlay networks connect multiple Docker daemons together.
      - `ipvlan`:	IPvlan networks provide full control over both IPv4 and IPv6 addressing.
      - `macvlan`:	Assign a MAC address to a container.
- Why do we have to map ports?
  - By default, containers are not exposed to the world.
  - Internally to host, containers have their own private addresses
    - Services have to be exposed port by port.
    - These have to be mapped to avoid conflicts.

{% enddetails %}
{% details example Hands on: A simple web server %}


- Run the following commands inside the Docker terminal

~~~bash
docker run -d -P nginx
docker container ls
~~~

- `-P`: make this service reachable from other computers (`--publish-all`)
- `-d` : run in background
- Where is the port?

{% include figure.liquid path="fig/docker/container-networking.png" %}

- Run the following command

~~~bash
docker inspect --format '{{json .Config.ExposedPorts}}' nginx 
~~~

- The outconme of the above command is `{"80/tcp":{}}`. 
- In other words, the container exposes its own internal port, `80`. In turn, 
this port is mapped to the external port `55000`, as shown in the screenshot. 
- You can view the nginx webserver by visiting `127.0.0.1:55000`

{% enddetails %}
{% details example Hands on: manual allocation of port numbers %}


- In the previous example, the port randomly assigned by the host machine was `55000`. 
- This could be specified via the `-p` flag as follows:

~~~bash
docker run -d -p 8000:80 nginx
docker run -d -p 8080:80 -p 8888:80 nginx
~~~

- Convention: `port-on-host:port-on-container`
- Check out the web servers at all of these ports 
{% enddetails %}
