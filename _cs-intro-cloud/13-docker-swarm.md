---
layout: lecture
pretty_table: true
order: 1
title: Docker Swarm
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
  - name: Set up environment
  - name: Docker Swarm
  - name: Running Applications on Swarm
---

# Docker Swarm

---

## 1. Set up environment 

{% details Update CloudLab Git Repository %}

- Create a new branch called `docker-swarm` from your **Docker branch**. 
- Update the `profile.py` in your `docker-swarm` branch with the content from [this profile.py](https://github.com/linhbngo/cloudlab/blob/docker-swarm/profile.py). 

{% enddetails %}
{% details Launch CloudLab profile %}

- Update your CloudLab profile to see the new branch. 
- Instantiate the experiment. 
- Fill in the parameters as follows:
    - `Node type: XenVM or RawPC`: XenVM
    - `Number of nodes`: 2
    - `Number of cores in each node`: 4
    - `MB of RAM in each node`: 4096

{% enddetails %}
---

## 2. Docker Swarm

{% details SwarmKit %}

- Open source tool kit to build multi-node systems
- Reusable library.
- Plumbing part of the Docker ecosystem.
- Adopted into Docker as Docker Swarm

{% enddetails %}
{% details SwarmKit Features %}

- Highly-available, distributed store based on Raft consensus algorithm.
- Raft was developed by Ongaro, Diego, and John Ousterhout at Stanford.
- [In search of an understandable consensus algorithm. In 2014 USENIX Annual Technical Conference, pp. 305-319. 2014.](https://www.usenix.org/system/files/conference/atc14/atc14-paper-ongaro.pdf)
    - Dynamic reconfiguration of Raft without interrupting cluster operations
    - Services managed with declarative API
    - Integration with overlay networks and load balancing
    - Strong emphasis on security

{% enddetails %}
{% details SwarmKit Concepts %}

- A cluster will be at least one node.
- A node can be a manager and a worker.
- A manager actively takes part in the Raft consensus and keeps the Raft log.
- You can talk to a manager using the SwarmKit API.
- One manager is elected as the leader; other manager merely forward requests to it.
- The workers get their instructions from the managers.
- Both workers and managers can run containers.

{% enddetails %}
{% details SwarmKit Concepts %}

- The managers expose the SwarmKit API.
- Using the API, you can indicate that you want to run a service.
- A service is specified by its desired state: which image, how many instances…
- The leader uses different subsystems to break down services into tasks: orchestrator, scheduler, allocator, dispatcher.
- A task corresponds to a specific container, assigned to a specific node.
- Nodes know which tasks should be running, and will start or stop containers accordingly.

{% enddetails %}
{% details Deploying your swarm %}

- By default, SwarmKit features are asleep until you active Swarm mode
- Swarm Mode commands:
    - `docker swarm`: enable Swarm mode, join Swarm, adjust Swarm’s parameters
    - `docker node`: view nodes, promote/demote managers, manage nodes
    - `docker service`: create and manage services.
- Run the following on head node:

```bash
cd
docker swarm init --advertise-addr eth1:7777 --listen-addr eth1:7777
```

{% include figure.liquid path="assets/img/courses/csc468/docker-swarm/swarm-init.png" width="50%" zoomable=true %}

- Read the output and use the provided commands on the worker nodes to have these nodes joining the swarm.

{% include figure.liquid path="assets/img/courses/csc468/docker-swarm/swarm-join.png" width="50%" zoomable=true %}

- On the head node, run the following command to view the swarm nodes

```bash
docker node ls
```

{% include figure.liquid path="assets/img/courses/csc468/docker-swarm/swarm-nodes.png" width="50%" zoomable=true %}

{% enddetails %}
---
    
## 3. Running Applications on Swarm

{% details Local registry %}

- Build images for application,
- Ship these images with a registry,
- Run services using these images.
    - Why?
    - For docker-compose up, images are built locally for services.
    - For a Swarm, images need to be distributed.
    - The easiest way is to use a Docker registry.

{% enddetails %}
{% details Hands-on: Launching a registry inside Swarm %}

- Run the following on the head node

```bash
docker service create --name registry --publish 5000:5000 registry
docker service ps registry
curl 127.0.0.1:5000/v2/_catalog
```

- Test your registry
    - This is a demo registry with no security!

```bash
docker pull busybox
docker tag busybox 127.0.0.1:5000/busybox
docker push 127.0.0.1:5000/busybox
curl 127.0.0.1:5000/v2/_catalog
```

{% enddetails %}
{% details Hands-on: Deploying a service on Swarm %}

- Getting the ramcoin app

```bash
git clone https://github.com/CSC468-WCU/ram_coin.git
cd ram_coin
```

- Run the following to build and push the images into the local registry

```bash
export REGISTRY=127.0.0.1:5000
export TAG=v0.1
for SERVICE in hasher rng webui worker; do docker build -t $REGISTRY/$SERVICE:$TAG ./$SERVICE; docker push $REGISTRY/$SERVICE:$TAG; done
curl 127.0.0.1:5000/v2/_catalog
```

- Launching the overlay network and other services

```bash
docker network create --driver overlay ramcoins
docker service create --network ramcoins --name redis redis
for SERVICE in hasher rng webui worker; do docker service create --network ramcoins --detach=true --name $SERVICE $REGISTRY/$SERVICE:$TAG; done
docker service ls
docker service update webui --publish-add 8000:80
docker service ls
```

- Visit the head node at port 8000 to observe the application running. 
- Try scaling up services using: `docker service scale SERVICE_NAME=...`
{% enddetails %}
