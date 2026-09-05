---
layout: lecture
pretty_table: true
order: 1
title: Docker Network
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
  - name: "Infrastructure as Code: Networking"
  - name: Port mapping
  - name: Port mapping on a Cloud Node
  - name: Common Networking Tasks in Docker
---

## Infrastructure as Code: Networking

{% details Networking for container %}


- How can services provided by a container become available to the world? 
    - Piggyback on the host machine's network.
- Docker has supporting drivers for containers:
    - `bridge`:	The default network driver.
    - `host`:	Remove network isolation between the container and the Docker host.
    - `none`:	Completely isolate a container from the host and other containers.
    - `overlay`:	Overlay networks connect multiple Docker daemons together.
    - `ipvlan`:	IPvlan networks provide full control over both IPv4 and IPv6 addressing.
    - `macvlan`:	Assign a MAC address to a container.

{% enddetails %}
{% details Docker network commands %}


- `docker network` will list all possible command options

{% details docker network %}

{% include figure.liquid path="assets/img/courses/csc468/docker-network/docker-network.png" max-width="50%" zoomable=true %}

{% enddetails %}
- `docker network ls` will list all possible networks

{% details docker network ls %}

{% include figure.liquid path="assets/img/courses/csc468/docker-network/docker-network-ls-windows.png" max-width="50%" zoomable=true %}

- Default network: `bridge`
- `compute`, `csc418env_default`, `docker-spark_default`, and `docker_default`: Dr. Ngo's custom networks

{% enddetails %}
- `docker network inspect NAME`: inspect the NAME network

{% details docker network inspect bridge %}

{% include figure.liquid path="assets/img/courses/csc468/docker-network/network-inspect-bridge.png" max-width="50%" zoomable=true %}

{% enddetails %}
- By default, new containers are attached to the `bridge` network

{% details Attaching a new container %}

- Run the following command to launch a nodejs container

```bash
docker run -itd node:slim
```

- Inspect the `bridge` network to learn about the container. 

{% enddetails %}
{% enddetails %}
---

## Port mapping

{% details Overview %}

- Why do we have to map ports?
    - By default, containers are not exposed to the world.
    - Internally to host, containers have their own private addresses
        - Services have to be exposed port by port.
        - These have to be mapped to avoid conflicts.

{% enddetails %}
{% details Hands on: A simple web server %}


{% details A baseline node.js server %}


- If you don't already have one running from the previous section, run the following command 
to launch a nodejs container

```bash
docker run -itd --name my_nodejs node:slim
```

- Check the status of the running container

```bash
docker ps
```

- Open a terminal into the running container using `docker exec`

```bash
docker exec -it my_nodejs sh
```

{% include figure.liquid path="assets/img/courses/csc468/docker-network/network-nodejs-1.png" max-width="50%" zoomable=true %}

- Inside the `my_nodejs` container, install `nano` and `curl`:

```bash
apt update
apt install -y nano curl
```

- Create a directory called `app` under the root directory. Use `nano` to create a file called 
`server.js` with the following contents

```js linenums="1"
const { createServer } = require('node:http');
const hostname = '0.0.0.0';
const port = 3000;
const server = createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.end('Hello World');
});
server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
```

- Launch the server using the following commands

```bash
cd /app
node server.js
```

{% details CLI access %}

- Open another terminal and use `docker exec` to get into the running `my_nodejs` container.
- Run `curl 127.0.0.1:3000`. What is the outcome?

{% enddetails %}
{% details Host machine browser access %}

- Open a browser on the host machine
- Visit `127.0.0.1:3000`. What is the outcome?

{% enddetails %}
{% details Commit the image %}

- Stop the `my_nodejs` container. 
- Commit the container into an image called `my_nodejs:1.0`. This is for the next step of the hands-on

{% include figure.liquid path="assets/img/courses/csc468/docker-network/network-nodejs-2.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% enddetails %}
{% details A node.js server with port mapping %}


- Launch a container from the newly created `my_nodejs:1.0` image

```bash
docker run -itd -P --expose 3000 --name my_nodejs my_nodejs:1.0 sh
cd /app
node server.js
```

{% details Host machine browser access %}

- Find the mapped port using `docker ps` or the Docker Desktop dashboard
- Open a browser on the host machine and visit `127.0.0.1` at the shown mapped port (most likely 5 digits)
- What is the outcome?

{% enddetails %}
- `-P`: make this service reachable from other computers (`--publish-all`)
- `--expose` : Open a port from inside the container

{% details Where are the ports? %}


{% include figure.liquid path="assets/img/courses/csc468/docker-network/container-networking.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% enddetails %}
{% details Hands on: manual allocation of port numbers %}

- In the previous example, the port randomly assigned by the host machine was random. 
- This could be specified via the `-p` flag as follows:

```bash
docker run -itd -p 30080:3000 --expose 3000 --name my_nodejs my_nodejs:1.0 sh
```

- Convention: `port-on-host:port-on-container`
- Delete the previous container and rerun it with the new `-p` flag. 
- Revisit the host machine browser at `127.0.0.1:30080` to confirm that the Node server 
inside the container is still reachable. 

{% enddetails %}
{% enddetails %}
---

## Port mapping on a Cloud Node

{% details Branching your Cloud profile %}

- On your **Github** repository for CloudLab, create a branch called `docker` from the main branch. 
- Make sure that your `docker` branch contains **all** files from [Dr. Ngo's cloudlab repository's docker branch](https://github.com/linhbngo/cloudlab/tree/docker).
- Go to your CloudLab, and open up the corresponding CloudLab profile. 
- `Edit` and `Update` the link to the GitHub repository. 
- You should see a branch called `docker` added to the `Repository Branches and Tags` of your CloudLab profile. 
- Click on the `Instantiate` button for this branch. 

{% include figure.liquid path="assets/img/courses/csc468/docker-network/docker-branch.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% details Hands-on exercise %}

- Repeat all the activities from Section  2, Port mapping. 
- For the browser test, use the host name of your experiment with the corresponding mapped port instead of `localhost` or `127.0.0.1`. 

{% enddetails %}
---

## Common Networking Tasks in Docker

{% details Create a network %}

```bash
docker network create --driver bridge ramnet
docker network ls
```

{% enddetails %}
{% details Place a container on a network %}

```bash
docker run -d --name es --net ramnet elasticsearch:2
docker network inspect ramnet
```

{% enddetails %}
{% details Place another container on a network %}

```bash
docker run -it --net ramnet alpine sh
ping es
```

- Open another terminal and inspect `ramnet`




{% enddetails %}
