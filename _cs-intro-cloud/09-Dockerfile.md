---
layout: lecture
pretty_table: true
order: 1
title: Dockerfile
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
  - name: "Automatic image construction: Dockerfile"
  - name: Infrastructure as Code
  - name: "Infrastructure as Code: Storage"
---

# Dockerfile

---

## 1. Automatic image construction: Dockerfile

{% details Overview %}


- A build recipe for a container image.
- Contains a series of instructions telling Docker/Podman how an image is to be constructed.
- The `docker build` command builds an image from a Dockerfile.


{% enddetails %}
{% details Hands on: writing the first Dockerfile %}


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

{% include figure.liquid path="assets/img/courses/csc468/docker/image-docker-build.png" width="50%" zoomable=true %}

- Running `docker image ls` and examining the GUI's Image tab, you will 
see that there are now two tags for the same repository name. If you run 
`docker push` and check your Docker Hub repo, you will see the second 
tag now stored in the same repository

~~~bash
docker push linhbngo/ubuntu_figlet:2.0
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/image-docker-push.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Exercise: test new image %}

- Test run the new `ubuntu_figlet` image by launching an interactive 
container using this image, then immediately run `figlet hello world`. 

{% details Solution %}

- Replace `linhbngo` with your own DockerHub account

~~~bash
docker run -it linhbngo/ubuntu_figlet:2.0 /bin/bash
figlet hello world
exit
~~~

{% include figure.liquid path="assets/img/courses/csc468/docker/image-test-image.png" width="50%" zoomable=true %}

{% enddetails %}
{% enddetails %}
---

## 2. Infrastructure as Code

{% details Overview %}

- Containers can be customized to run as programs/services
    - Barebone containers with just enough dependencies packages
- Customizable parameters to feed to containers at start time
- Ephemeral/persistent storages
- Network infrastructures

{% enddetails %}

{% details CMD and ENTRYPOINT %}

- Both commands enable containers to run a default program or script. 
- `CMD` executes a default program or script with a predefined set of parameters. 
    - To be run if the container is invoked without any command.
- `ENTRYPOINT` defines a default program or script with a predefined set of parameters, 
but also allows users to append additional parameters to `docker run` call.  

{% enddetails %}

{% details Hands on: CMD %}


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

{% include figure.liquid path="assets/img/courses/csc468/docker/image-create-cmd.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Exercise: storage consumption %}

- Run the following commands

~~~bash
docker image ls
~~~

- Did we use any additional storage for this new image?
    - Hint: Try running `docker system df`

{% details Solution %}


{% enddetails %}
{% include figure.liquid path="assets/img/courses/csc468/docker/image-storage.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Hands on: ENTRYPOINT %}
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

    {% include figure.liquid path="assets/img/courses/csc468/docker/image-entrypoint.png" width="50%" zoomable=true %}

{% enddetails %}


{% details Hands on: Using both ENTRYPOINT and CMD %}

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

    {% include figure.liquid path="assets/img/courses/csc468/docker/image-cmd-entrypoint.png" width="50%" zoomable=true %}

    - Caveat with `ENTRYPOINT`: `/bin/bash` does not work as expected.  
        - Need to override with `--entrypoint` flag.

    ~~~bash
    docker run -it linhbngo/ubuntu_figlet:5.0
    docker run -it --entrypoint bash linhbngo/ubuntu_figlet:5.0
    exit
    ~~~

{% enddetails %}


---

## Infrastructure as Code: Storage

{% details Overview %}

- Docker images are immutable (read-only)
- Docker containers are mutable, but are available only for the running duration 
of the containers. 
    - Once containers are shutdown, to retain modifications, they need to be made 
    immutable. 
- How do we reconcile new data into Docker images/containers?
    - Copy data into images during the building process
    - Mount storage directory from host machines into containers at run time


{% enddetails %}

{% details COPY %}

- `COPY src dst`
- Copy contents into the image prior to the installation steps. 
- Need to be done prior to `RUN` statements. 

{% enddetails %}

{% details Hands on: Importing and building external code using COPY %}
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

    {% include figure.liquid path="assets/img/courses/csc468/docker/image-docker-build-copy.png" width="50%" zoomable=true %}

{% enddetails %}


{% details Hands on: Mounting external storage to running containers %}
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

    {% include figure.liquid path="assets/img/courses/csc468/docker/image-volume.png" width="50%" zoomable=true %}

{% enddetails %}
