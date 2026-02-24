---
layout: lecture
pretty_table: true
order: 1
title: CloudLab
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
  - name: CloudLab
  - name: Setup SSH
  - name: CloudLab Profiles and Experiments
---

# Introduction to CloudLab

---

## 1. CloudLab    
 
{% details Overview %}

- Visit [CloudLab's website](https://cloudlab.us)
- Click "Request an Account" 
- Fill in the information as shown in the following figure and click "Submit Request"
- Wait for a confirmation email to arrive in your wcupa.edu mailbox. You might have to 
resubmit a new request if you don't see this email in about half an hour. 

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/01.png" width="50%" zoomable=true alt="Account creation forms" %}

- After your account is confirmed, the instructor will be able to see your application 
and can grant you access to CloudLab. 
- If you already had a CloudLab account, you can select `Start/Join Project` under
your username, then select `Join Existing Project` and provide the name `cloud-edu`. 


{% enddetails %}
{% details CloudLab Network %}

- Experimental testbed for future computing research
- Allow researchers control to the bare metal
- Diverse, distributed resources at large scale
- Allow repeatable and scientific design of experiments

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/02.png" width="50%" zoomable=true alt="CloudLab GENI" %}

{% enddetails %}
{% details GENI %}

- Global Environment for Networking Innovation
- Combining heterogeneous resource types, each virtualized 
along one or more suitable dimensions, to produce a single 
platform for network science researchers"
- Key components:
  - GENI racks: virtualized computation and storage resources
  - Software-defined networks (SDNs): virtualized, programmable network resources
  - WiMAX: virtualized cellular wireless communication

*Berman, M., Chase, J.S., Landweber, L., Nakao, A., Ott, M., Raychaudhuri, 
D., Ricci, R. , and Seskar, I., 2014. GENI: A federated testbed for innovative 
network experiments. Computer Networks, 61, pp.5-23.*

{% enddetails %}
{% details Key experimental concepts %}

- Sliceability: the ability to support virtualization while 
maintaining some degree of isolation for simultaneous experiments
- Deep programmability: the ability to influence the behavior of 
computing, storage, routing, and forwarding components deep inside the 
network, not just at or near the network edge.

{% enddetails %}
{% details CloudLab Hardware %}

- Utah/HP: Low-power ARM64 (785 nodes)
  - 315 m400: 1X 8-core ARMv8 at 2.4GHz, 64GB RAM, 120GB flash
  - 270 m510: 1X 8-core Intel Xeon D-1548 at 2.0 GHz, 64GB RAM, 256 GB flash
  - 200 xl170: 1X 10-core Intel E5-2640v4 at 2.4 Ghz, 64 GB RAM, 480 GB SSD
- Wisconsin/Cisco: 530 nodes
  - 90 c220g1: 2X 8-core Intel Haswell at 2.4GHz, 128GB RAM, 1X 480GB SDD, 2X 1.2TB HDD
  - 10 c240g1: 2X 8-core Intel Haswell at 2.4GHz, 128GB RAM, 1X 480GB SDD, 1X 1TB HDD, 12X 3TB HDD
  - 163 c220g2: 2X 10-core Intel Haswell at 2.6GHz, 160GB RAM, 1X 480GB SDD, 2X 1.2TB HDD
  - 7 c240g2: 2X Intel Haswell 10-core at 2.6GHz, 160GB RAM, 2X 480GB SDD, 12X 3TB HDD
  - 224 c220g5: 2X 10-core Intel Skylake at 2.20GHz, 192GB RAM, 1TB HDD
  - 32 c240g5: 2X 10-core Intel Skylake at 2.20GHz, 192GB RAM, 1TB HDD, 1 NVIDIA P100 GPU
  - 4 c4130: 2X 8-core Intel Broadwell at 3.20GHz, 128GB RAM, 2X 960GB HDD, 4 NVIDIA V100
- Clemson/Dell: 281 nodes
  - 96 c8220: 2X 10-core Intel Ivy Bridge at 2.2GHz, 256GB RAM, 2X 1TB HDD
  - 4 c8220x: 2X 10-core Intel Ivy Bridge at 2.2GHz, 256GB RAM, 8X 1TB HDD, 12X 4TB HDD
  - 84 c6420: 2X 14-core Intel Haswell at 2.0GHz, 256GB RAM, 2X 1TB HDD
  - 2 c4130: 2X 12-core Intel Haswell at 2.5GHz, 256GB RAM, 2X 1TB HDD, 2 NVIDIA K40m
  - 2 dss7500: 2X 6-core Intel Haswell at 2.4GHz, 128GN RAM, 2X 126GB SSD, 45X 6TB HDD
  - 72 c6420: 2X 16-core Intel Skylake at 2.6GHz, 386GB RAM, 2X 1TB HDD
  - 6 ibm8335: 2X 10-core IBM POWER8NVL at 2.87GHz, 512GB RAM, 1X 2TB HDD, 2 NVIDIA GV100GL
  - 15 r7515: 2X 32-core AMD EPYC Rome at 2.9GHz, 512GB RAM, 1X 2TB HDD, 2 NVIDIA GV100GL

{% enddetails %}
---

## 2. Setup SSH

{% details Command line terminal software on Windows %}

- Download and install [Windows Terminal from the Microsoft Store](https://www.microsoft.com/en-us/p/windows-terminal/9n0dx20hk701?activetab=pivot:overviewtab).

{% enddetails %}
{% details Command line terminal software on Mac %}

- Use the Search box (magnifying glass on top-right of your Mac Desktop) and 
type in the word `Terminal`. 
- Launch the resulting Terminal app. 

{% enddetails %}
{% details SSH setup %}

- Launch your terminal (Windows Terminal or Mac) and run the following command: 
- Hit `Enter` for all questions. **Do not enter a password or change the default location of the files**. 

```bash
cd
ssh-keygen -t rsa
```

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/03.png" width="50%" zoomable=true alt="Generate SSH keys" %}


- Run the following command to display the public key
- Drag your mouse over to paint/copy the key (just the text, no extra spaces after the last 
character)

```bash
cat ~/.ssh/id_rsa.pub
```

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/04.png" width="50%" zoomable=true alt="Public key generated" %}

- Log into CloudLab, click on your username (top right) and select `Manage SSH Keys`:

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/05.png" width="50%" zoomable=true alt="Manage SSH Keys box" %}

- Paste the key into the `Key` box and click `Add Key`: 

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/06.png" width="50%" zoomable=true alt="Paste SSH keys" %}

{% enddetails %}
---

## 3. CloudLab Profiles and Experiments

{% details Setup GitHub repository %}


- Go to your GitHub account, under `Repositories`, select `New`. 

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/07.png" width="50%" zoomable=true alt="Button to create new repository" %}

- You can select any name for your repo. 
- Repository must be `public`. 
- The `Add a README file` box must be checked. 
- Click `Create repository` when done.  

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/08.png" width="50%" zoomable=true alt="Create new repository" %}

{% enddetails %}
{% details Create first profile file %}


- Click `Add file` and select `Create new file`

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/09.png" width="50%" zoomable=true alt="Button to create new file in repository" %}

- Type `profile.py` for the file name and enter the content below into the text editor. 
- Click `Commit new file` when done. 

```python linenums="1"
--8<-- "docs/csc468/lectures/data/profile-basic.py"
```

{% enddetails %}
{% details CloudLab profile creation and experiment instantiation %}


- Login to your CloudLab account, click `Experiments` on top left, 
select `Create Experiment Profile`. 

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/11.png" width="50%" zoomable=true alt="Create a CloudLab profile" %}

- Click on `Git Repo`

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/12.png" width="50%" zoomable=true alt="Create a CloudLab profile using Git Repo" %}

- Paste the URL of **your** previously created Git repo here and click `Confirm`

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/13.png" width="50%" zoomable=true alt="HTTPS Git URL" %}

- Enter the name for your profile, put in some words for the Description. 
- You will not have a drop-down list of Project. 
- Click `Create` when done. 

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/14.png" width="50%" zoomable=true alt="Fill in name and description of a CloudLab profile" %}

- Click `Instantiate` to launch an experiment from your profile. 

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/15.png" width="50%" zoomable=true alt="CloudLab profile description and instantiation" %}

- Select a Cluster from Wisconsin, Clemson, or Emulab, then click `Next`. 
- Do not do anything on the next `Start on date/time` screen. Click `Finish`.  

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/16.png" width="50%" zoomable=true alt="Cluster selection" %}

- Your experiment is now being `provision`, and then `booting`  

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/17.png" width="50%" zoomable=true alt="CloudLab experiment provisioning" %}
{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/18.png" width="50%" zoomable=true alt="CloudLab experiment booting" %}

{% enddetails %}
{% details Experiment validation %}


- When it is ready, you can use the provided SSH command to log in to your experiment (assuming 
your key was set up correctly). 
- The command is in the **List View** tab. 

{% include figure.liquid path="assets/img/courses/csc468/02-cloudlab/19.png" width="50%" zoomable=true alt="CloudLab experiment status" %}


{% enddetails %}
