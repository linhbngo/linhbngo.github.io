---
layout: lecture
pretty_table: true
order: 1
title: Introduction to FABRIC
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
last_updated: 2026-03-24

toc:
  - name: What is FABRIC
  - name: Slices, Sites, and Resource Thinking
  - name: Access Patterns and Simple Provisioning
---

## What is FABRIC

{% details Overview %}

- `FABRIC`: `F`ABRIC is `A`daptive Programma`B`le `R`esearch `I`nfrastructure for `C`omputer Science and Science Applications.
  - Recursive acronym similar to GNU ("GNU's Not Unix")
- [Funded by NSF](https://par.nsf.gov/biblio/10132161-fabric-national-scaleprogrammable-experimentalnetwork-infrastructure)
- To enable new paradigms for distributed applications and Internet protocols
  - A nation-wide programmable network with compute and storage at each node: run computationally intensive programs & maintain information in the network.
  - GPUs, FPGAs, and network processors (NICs) inside the network
  - Quality of service (QoS): dedicated optical 100Gb
  - Interconnects national facilities: HPC, cloud & wireless testbeds, commercial clouds, Internet, and edge
  - Design and test applications, protocols and services that run at any node in the network
  - Science cases: IoT sensors, Cybersecurity, AI/ML, SDN/P4, Science apps

{% enddetails %}



{% details Why FABRIC %}

– `Internet is showing its age.`
  - Applications designed around discrete points in the solution space
  - Inability to program the core of the network
- What changed?
  - Cheap compute/storage that can be put directly in the network
  - Multiple established methods of programmability (OpenFlow, P4, eBPF, DPDK, BGP flowspec)
  - Advances in Machine Learning/AI
  - Emergence of 5G, IoT, various flavors of cloud technologies
- Opportunity for the community to push the boundaries of distributed, stateful,‘everywhere’ programmable infrastructure
  - More control or dataplane state, or some combination? Multiple architectures (co)exist in thisspace.
  - Network as a big-data instrument? Autonomous network control?
  - New protocols and applications that program the network?
  - Security as an integral component

{% enddetails %}


{% details Nationwide Topology and Connected Facilities %}

- One of the big conceptual differences from CloudLab is that FABRIC was designed as a **distributed national infrastructure**, not just as a small set of isolated clusters.
- Even if we do not build complex cross-site experiments in this course, students should see that the platform was built to span multiple sites and to connect to external facilities.

{% include figure.liquid path="assets/img/courses/csc468/fabric/fabric-topology.png" max-width="50%" zoomable=true %}

{% enddetails %}


{% details Key Differences from GENI %}

- FABRIC has a programmable core network infrastructure
- FABRIC provides guaranteed quality of service by utilizing its own dedicated optical 100G infrastructure or relying on dedicated L2 capacity wherever possible to create QoS-guaranteed connections.
- FABRIC provides access to a variety of programmable PCI devices○ Network cards, GPUs, FPGAs
- FABRIC interconnects a large number of existing scientific, computational and experimental facilities
- FABRIC experimenter network topologies can peer with the Internet, R&E Networks for access other facilities and public clouds on-demand

{% enddetails %}


{% details Scope of FABRIC usage in this course %}

- The attached overview describes FABRIC as a **nation-wide programmable network with compute and storage at each node**.
- The design goal is broader than a local cluster:
  - compute,
  - storage,
  - programmable networking,
  - accelerators such as **GPUs** and **FPGAs**,
  - and connectivity to other facilities such as cloud, HPC, wireless, and edge resources.
- For this course, we are **not** trying to use all of FABRIC,
  - we are mostly using the approachable part of it,
  - especially the ability to provision resources through slices and work with a modern research testbed.

{% enddetails %}


---

## Slices, Sites, and Resource Thinking



{% details Node Design %}

- 33 FABRIC Nodes
  - 9 nodes co-located at ESnet6 (DOE's Energy Science Network) Points of Presence: 
    - Connected via dedicated 100 Gbps DWDM across the ESnet6 open line optical system; some sites to be upgraded to Terabit SuperCore soon
  - 20 other nodes distributed across the R&E community at various regional networks, major CI facilities, and university hosting sites
    - many connected via 100 Gbps Layer 1
  - 4 Nodes deployed at International Locations (CERN, University of Amsterdam, University of Bristol, University of Tokyo)
- Individual Node Configuration
  - 2x32-core AMD Rome and Milan with 512G RAM
  - GPUs (NVIDIA RTX 6000, T4, A30), FPGA network/compute accelerators
  - Storage - experimenter provisionable 1TB NVMe drives in servers and a pool of ~250TB rotating storage at each site
  - Network ports connect to a 100G+ switch, programmable through control software
  -   Tofino-based P4 switches (4 or more sites)
  - Reconfigurable Network Interface Cards
    - FPGAs (U280 XILINX with P4 support)
    - Mellanox ConnectX-5 and ConnectX-6 with hardware off-load
    - Multiple interface speeds (25G, 100G, 200G+(future))
  - Kernel Bypass/Hardware Offload
    - VMs sized to support full-rate DPDK (Data Plane Development Kit) for access to Programmable NICs, FPGA, and GPU resources via PCI pass-through

{% enddetails %}

{% details FABRIC Features %}
- `Facility Ports`: ability to add external facilities to slices using on-demand L2 connections
- Mirror Ports : ability to mirror traffic from the dataplane switch into slice
- Support for on-demand public connectivity
  - Slices with L3 IPv4 or IPv6 can connect on-demand with public internet
  - This is in testing
- L3 VPN service + CloudConnect
- Persistent storage for slices: get storage allocation at multiple sites for your project
- In-slice measurement framework - instrumentize your slice to get data about its performance
- Inter-testbed federation features, more Facility Ports
- Future
  - Support for P4 Tofino switches in topologies
  - Support for P4 workflows on top of U280 FPGAs (in collaborations withOCT/NorthEastern and ESnet)
{% enddetails %}

{% details FABRIC External Connections %}
- FABRIC experiments (slices) can run in an isolated manner within FABRIC Infrastructure, and isolated from external networks.
- Slices can also utilize FABRIC's external connections to access a variety of external experimental and production resources.
- These external connections are organized as follows:
  - Layer 3 IPv4 and IPv6 public connectivity on demand (with policy restrictions)via peering points provided by ESnet and Internet2
  - Layer 2 Services Peering (aka Facility ports)
  - Public Cloud Connections via CloudConnect

{% enddetails %}


{% details Interaction with FABRIC %}

- FABRIC has three ways to interact with it:
  - Portal - focus on creating small topologies
  - upyter Hub notebooks via API - don’t just create topologies - run experiments
  - API libraries from your laptop/desktop
- Recommended Starting Point: Notebook
- A **FABRIC slice** is the closest analogue to a **CloudLab experiment**.
- In both cases, the experiment is the thing you create, inspect, renew, and delete.
- The analogy becomes less exact on the definition side:
  - **CloudLab profile**: reusable platform-level template used to instantiate an experiment.
  - **FABRIC notebook / FABlib script**: the procedure that creates and configures a slice.

{% enddetails %}

{% details Site, node, and component %}

- FABRIC still uses the word **node**, but students should think a bit more carefully about what that means.
- A helpful vocabulary set is:
  - **site** = the institution or hosting location,
  - **node** = the compute resource instantiated inside a slice,
  - **component** = attached capability such as GPU, storage, or specialized networking hardware,
  - **slice** = the overall experiment boundary tying resources together.
- This is why FABRIC feels different from the older habit of thinking only in terms of "give me a machine."
- A better mindset is:
  - compose an experiment from **nodes + network services + optional components**.

{% enddetails %}

## Access Patterns and Simple Provisioning

{% details Access is slightly more complex than CloudLab %}

- CloudLab often feels straightforward:
  - instantiate,
  - wait for resources,
  - SSH into the machines.
- FABRIC is usually a little more ceremonial:
  - create a slice,
  - place nodes,
  - submit the slice,
  - use the expected FABRIC access workflow,
  - and then log into the provisioned resources.

{% enddetails %}

{% details Step 1: Initiate Configuration %}

- Start Jupyter with `default` option:

{% include figure.liquid path="assets/img/courses/csc468/fabric/server-option.png" max-width="50%" zoomable=true %}

- Run the following on a Terminal inside the Notebook server:

```bash
pip show fabrictestbed-extensions
pip install -U fabrictestbed-extensions
pip show fabrictestbed-extensions
```
- We should see a version 2.0.2 for the extension

{% include figure.liquid path="assets/img/courses/csc468/fabric/fabric-extensions.png" max-width="50%" zoomable=true %}

- Next, we will generate the configurations

```bash
fabric-cli configure setup
```

{% enddetails %}


{% details Step 2: Starting a notebook %}

- Go to `jupyter-examples-rel1.9.0/`
- Open `start_here.ipynb` notebook

{% enddetails %}


{% details Bottom Lines %}

- **CloudLab is easier to start with.**
- **FABRIC gives us another way to keep moving when CloudLab is full.**
- **Later courses or advanced projects can make deeper use of FABRIC's networking and distributed features.**

{% enddetails %}

## Local Deployment

You are to clone the following repository

{% details Preparation %}

If you have a Windows machine, run the followings:

~~~bash
git config --global core.autocrlf false
git clone https://github.com/CSC468-WCU/fabric-examples.git
cd fabric-examples
~~~

{% enddetails %}


{% details Home Preparation %}

- A home directory for `fabric` service account is available inside the `fabric-examples` directory. Everything inside this directory has been included `.gitginore` file inside this directory. This is to ensure that all credential information 
are not accidentally pushed back upstream. 
- You will need to populate this home directory. 
- Create two directories inside this `home` directory:

~~~bash
# Make sure that you start out inside fabric-examples. 
pwd
cd home
mkdir .ssh
mkdir .fabric
~~~

{% details .fabric %}

- Copy the file `fabric_env.sh.template` into the newly created `.fabric` directory.
  - Change the file name to `fabric_rc`. 
  - Change the value `__FABRIC_PROJECT_ID__` with the project id from your Fabric Hub Profile. 
  - Change the value `__FABRIC_BASTION_USERNAME__` to the Basion ID from your Fabric Hub Profile. 
- Login into `https://cm.fabric-testbed.net/` to generate a new token. 
  - Download the generated token file and save them inside `.fabric`. 

{% include figure.liquid path="assets/img/courses/csc468/fabric/fabric-token.png" max-width="50%" zoomable=true %}

{% enddetails %}

{% details .ssh %}

- Go to `https://portal.fabric-testbed.net/` and Log in. 
- On the top bar, visit `Experiments`, then select `Manage SSH Keys`. 
- On the `Sliver0` tab, in the `Generate Sliver Key Pair` box
  - Enter `slice_key` as the name
  - Enter a short description, perhaps the date when you generated this key pair or the host computer name. 
  - Generate, then download the `slice_key` and `slice_key.pub` files into this `.ssh` directory. 

{% include figure.liquid path="assets/img/courses/csc468/fabric/generate-slice-key.png" max-width="50%" zoomable=true %}

- Switch to the `Bastion` tab, and do the same thing. 
  - For the name, enter `fabric-bastion-key`
  - Generate, then download the `fabric-bastion-key` and `fabric-bastion-key.pub` files into this .ssh directory. 

{% enddetails %}

It is important that you populate both `.fabric` and `.ssh` prior to building the image. 

{% enddetails %}

{% details Building Image %}

Build the image, then launch

~~~bash
docker compose build --no-cache
docker compose up
~~~

{% enddetails}


{% details Validation %}

Visit `127.0.0.1:8888`

The following items are to be done in the `configuration_and_validation.ipynb` notebook. 

{% enddetails %}
