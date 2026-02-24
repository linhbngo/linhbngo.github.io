---
layout: lecture
pretty_table: true
order: 1
title: Programmatic Deployment of Infrastructures
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
  - name: Deploy OpenStack on CloudLab
  - name: Deployment on OpenStack
  - name: Challenge
  - name: Cloud Security Basic
---

# Programmatic Deployment of Infrastructures
 
---

## 1. Deploy OpenStack on CloudLab

{% details Find CloudLab profile for OpenStack %}


- Log into [CloudLab](https://www.cloudlab.us/)
- Under **Experiments** drop down box, select **Start Experiment**.

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/01.png" width="50%" zoomable=true alt="Start Experiment" %}

- Click **Change Profile**. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/02.png" width="50%" zoomable=true alt="Change Profile" %}

- Type **OpenStack** in the search box, and select the profile **OpenStack** 
as shown in the figure below. 
  - Created By: `johnsond`
  - Last Updated: `2017-12-20 10:05:21`
  - Click **Select Profile** when done. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/03.png" width="50%" zoomable=true alt="OpenStack profile created by johnsond" %}

- Click **Next**. 

{% enddetails %}
{% details Setup parameters and selecting sites %}


{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/04.png" width="50%" zoomable=true alt="OpenStack select profile" %}

- Select the options similar to the figure below. 
- If the **Parameterize** tab does not look like this, click **Previous** to 
go back one step, and then click **Next** again.

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/05.png" width="50%" zoomable=true alt="Patameterization options" %}

- Only **Utah**, **Wisconsin**, and **Clemson** have been known to work with this 
profile. 
- I will use **Utah** for the remaining steps. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/06.png" width="50%" zoomable=true alt="Resource selections" %}

- Do not change anything on the **Schedule** step and click **Finish**. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/07.png" width="50%" zoomable=true alt="Provisioning resources" %}

- The startup scripts of this profile will take sometimes to run, approximately 
**thirty minutes to one hour**. 
- You will receive an email from CloudLab (to the registered) to inform you when 
the experiment is ready. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/08.png" width="50%" zoomable=true alt="Waiting for email confirmations" %}

- Go to the experiment, and open the blue *Profile Instructions** box. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/09.png" width="50%" zoomable=true alt="Profile Instructions" %}

- Follow the instructions to login to OpenStack dashboard. Your passwords 
will be randomly generated and unique to each experiment. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/10.png" width="50%" zoomable=true alt="Domain, User Name, Password" %}

- You will see a Dashboard on a successful deployment as follows.

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/11.png" width="50%" zoomable=true alt="Administrative Dashboard" %}

{% enddetails %}
---

## 2. Deployment on OpenStack

- In the next sequence of hands-on, we will look at how OpenStack can 
support the deployment of a virtual machine inside its Nova compute 
components. 

{% details Hands-on: Download Linux distribution %}


- We will use Alpine Linux, a light-weight distribution that was created
for containerization/cloud deployment. 
- From [Alpine Download Page](https://alpinelinux.org/downloads/), select the 
x86_64 Virtual version. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/12.png" width="50%" zoomable=true alt="Select correct x86_64 download" %}

{% enddetails %}
{% details Create cloud image %}


- Go to your CloudLab Dashboard. 
- Go to **Compute**/**Images**, then click on **Create Image**.  

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/13.png" width="50%" zoomable=true alt="List of compute images" %}

- Click **Browse** and find and select the downloaded ISO file from the
the previous slide. 
- Set the other parameters as shown in the figure below. 
- Click **Create Image** when done. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/14.png" width="50%" zoomable=true alt="Create image" %}

- The image will show up in the **Images** tab. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/15.png" width="50%" zoomable=true alt="Newly added image" %}

{% enddetails %}
{% details Create volumes %}


- Go to your CloudLab Dashboard. 
- Go to **Volumes**/**Volumes**, then click on **Create Volume**.  

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/16.png" width="50%" zoomable=true alt="Create Volumes" %}

- Set the other parameters as shown in the figure below. 
- Alpine takes up a small amount of storage, so 2GB is more than enough 
for a simple installation.
- Click **Create Volume** when done. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/17.png" width="50%" zoomable=true alt="Options to create a new volume" %}

- The volume will show up in the **Volumes** tab. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/18.png" width="50%" zoomable=true alt="New volume is added" %}

{% enddetails %}
{% details Launching a compute instance %}


- Go to your CloudLab Dashboard. 
- Go to **Compute**/**Instances** and click on **Launch Instance**.  

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/19.png" width="50%" zoomable=true alt="Create Instances" %}

- Set the instance name and other parameters, then click **Next**

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/20.png" width="50%" zoomable=true alt="Selecting source with instance" %}

- Use the up arrow to select the **alpine** image as the allocated image. 
Click **Next**. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/21.png" width="50%" zoomable=true alt="Selecting image to boot from" %}

- Select **m1.tiny** as the compute flavor. Click **Next**. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/22.png" width="50%" zoomable=true alt="Selecting compute resource" %}

- Select **flat-lan-1-net** as the connected network. Click **Launch Instance**. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/23.png" width="50%" zoomable=true alt="Selecting network resource" %}

- It should take a few minute for the instance to become ready. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/24.png" width="50%" zoomable=true alt="Active compute resource" %}

{% enddetails %}
{% details Volume attachment and Linux installation %}


- Go to your CloudLab Dashboard. 
- Go to **Compute**/**Instances**
- Click on the drop-down arrow under **Actions** for the alpine instance, 
then click **Attach Volume**.  

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/25.png" width="50%" zoomable=true alt="Attach volume actions" %}

- Select your `sda_****` volume ID created earlier, then click **Attach Volume**

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/26.png" width="50%" zoomable=true alt="Attach volume" %}

- Click on the drop-down arrow under **Actions** for the alpine instance. 
- Select **Console**.

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/27.png" width="50%" zoomable=true alt="Provisioning resources" %}

- Right click on **Click here to show only console** and select 
**Open link in new tab**.
- This helps with navigating back and forth.  

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/28.png" width="50%" zoomable=true alt="Launch a console" %}

- A new console tab appears! 
- You are now booting from the Alpine distro. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/29.png" width="50%" zoomable=true alt="Login to the instance" %}

- Type **root** into the`localhost login:` prompt and hit Enter to log in. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/30.png" width="50%" zoomable=true alt="Logged into the system as root" %}

- A quick review of Alpine installation process can be found 
on [their wiki](https://wiki.alpinelinux.org/wiki/Install_to_disk)
- Type `setup-alpine` and hit Enter to start the installation process. 
- Use the following options:
  - `Select keyboard layout`: `us`
  - `Select variant`: `us`
  - `Enter system hostname ...`: Hit Enter to accept default. 
  - `Which one do you want to initialize?`: Hit Enter to accept `eth0` as the default interface. 
  - `Ip address for eth0`: Hit Enter to accept `dhcp` as the default value. 
  - `Do you want to do any manual network configuration?`: Hit Enter to accept `n` as the default value. 
  - Enter a **complex** password for root. DO NOT MAKE AN EASY PASSWORD. If your cloud instance got 
  hacked and used for malicious purposes, you will be banned from CloudLab. Retype the password. 
  - `Which timezone are you in?`: Type `EST` and hit Enter. 
  - `HTTP/FTP proxy URL?`: Hit Enter to accept `none` as the default value. 
  - For the mirror question, type `30` (the one from princeton), then hit Enter. 
  - `Which SSH server?`: Hit Enter to accept `openssh` as the default value. 
  - `Which disk(s) would you like to use?`: Review the lines above, and select the listed disk. 
  There should be one as we already attached a volume to this instance. For me, it is `vdb`, so I 
  type in `vda` and hit Enter. 
  - `How would you like to use it?`: Type `sys` and hit Enter. 
  - `WARNING: Erase the above disk(s) and continue?`: Type `y` and hit Enter. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/31.png" width="50%" zoomable=true alt="Finish setting up different options" %}

- Once the installation process is completed, Leave this console running and return to the Dashboard. 
- Go to **Compute**/**Instances**
- Click on the drop-down arrow under **Actions** for the alpine instance.  
- Select the `sda_****` volume ID selected earlier, then click **Detach Volume**

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/32.png" width="50%" zoomable=true alt="Option to detach volume" %}

- Select the `sda_****` volume ID created earlier, then click **Detach Volume**

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/33.png" width="50%" zoomable=true alt="Detaching for volumes" %}

- Go to your CloudLab Dashboard. 
- Go to **Volumes**/**Volumes**.  
- In the **Actions** box of `sda_****`, click the drop-down arrow and select **Upload to Image**. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/34.png" width="50%" zoomable=true alt="Volume options" %}

- Set **Image Name** to `alpine-disk` and **Disk Format** as `Raw`, then click 
**Upload**. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/35.png" width="50%" zoomable=true alt="Upload volumes to image" %}

- Successful upload:

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/36.png" width="50%" zoomable=true alt="Image appeared in list" %}

{% enddetails %}
---

## 3. Challenge

{% details Setup new instance %}


- Launch another compute instance using the newly created `alpine-disk` image. 
  - Pay attention to the flavor. 
- Log into the console and confirm that you can use the root password created earlier to log in

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/37.png" width="50%" zoomable=true alt="New launched instance with working image" %}


{% enddetails %}
{% details Setup Apache webserver on the previous new instance %}


- You should be inside the console after log in as root and have the root password. 
- Run the following commands to install Apache webserver

~~~
$ apk update
$ apk add apache2
$ rc-service apache2 start
~~~

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/38.png" width="50%" zoomable=true alt="Update and install apache2" %}

{% enddetails %}
{% details Setup public IP address %}



- To expose the webserver, we need a public IP address. 
- Go to your CloudLab Dashboard. 
- Go to **Compute**/**Instances**
- Click on the drop-down arrow under **Actions** for the alpine instance, 
then click **Associate Floating IP**. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/39.png" width="50%" zoomable=true alt="Associating floating IPs" %}

- Click on the `+` sign to allocate IP address. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/40.png" width="50%" zoomable=true alt="Allocating public IP addresses" %}

- Click on **Allocate IP**. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/41.png" width="50%" zoomable=true alt="Associate public IP address with the running instance" %}

- Click on **Associate**.

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/42.png" width="50%" zoomable=true alt="Associating IP to instance" %}

- You should see the public IP address with your instance

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/43.png" width="50%" zoomable=true alt="IP address on instance" %}

- Try visiting this IP address now, anything?

{% enddetails %}
---

## 4. Cloud Security Basic

{% details Cloud security basic %}


- In the cloud, `egress` means traffic that’s leaving from inside the private network out to the 
public internet (similar to standard network definition).

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/44.png" width="50%" zoomable=true alt="Egress traffic generated from inside the cloud" %}

- In the cloud, `ingress` refers to unsolicited traffic sent from an address in public internet to 
the private network – it is not a response to a request initiated by an inside system. In this case, 
firewalls are designed to decline this request unless there are specific policy and configuration that 
allows ingress connections.

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/45.png" width="50%" zoomable=true alt="Ingress traffic generated from inside the cloud" %}


{% enddetails %}
{% details Handle security %}


- Go to your CloudLab Dashboard. 
- Go to **Network**/**Security Group**
- Click on **Manage Rules**. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/46.png" width="50%" zoomable=true alt="Security groups" %}

- Click `Add Rules` 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/47.png" width="50%" zoomable=true alt="Security group rule lists" %}

- In the `Rule` drop down box, select `HTTP`, then click `Add`. 

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/48.png" width="50%" zoomable=true alt="HTTP port" %}

- You can see the new `Ingress` rule for HTTP.

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/49.png" width="50%" zoomable=true alt="Security rules for HTTP is added" %}

- The apache webserver is now visible

{% include figure.liquid path="assets/img/courses/csc468/05-programmatic/50.png" width="50%" zoomable=true alt="Apache2 webserver" %}



{% enddetails %}
