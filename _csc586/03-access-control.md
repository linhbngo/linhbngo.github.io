---
layout: lecture
pretty_table: true
collection: csc586
course: CSC 586: Linux System Administration and Security - Summer 2024 - 100% online asynchronous
title: "Access Control"
toc:
  - name: Unix standards
  - name: CloudLab - a place with rootly power!
  - name: Setup GitHub Repository
  - name: Setup CloudLab profile
  - name: Unix/Linux standards for access control
  - name: Root and Rootly Powers
  - name: Hands-on: Rootly power
  - name: Other (less secure) means of granting rootly powers
  - name: Managemen of the root account
  - name: Challenge
  - name: Drawback of standard models
  - name: Extensions to standard models
  - name: Modern access control
---
# Access Control

## Unix standards
- Access control decisions depend on which user is attempting to 
perform and operation on that user’s membership in a UNIX group.
- Objects have owners. Owners have broad (but not necessarily unrestricted) 
control over their objects.
- You own the object you create. 
- The special user account `root` can act as the owner of any object. 
Only `root` can perform certain sensitive administrative operation. 


## CloudLab - a place with rootly power!

{% details Setup CloudLab Account %}

- Go over and complete all registration steps outlined in Section 1 and 2 of 
the [CloudLab Lecture](https://www.cs.wcupa.edu/LNGO/courses/csc468/lectures/02-cloudlab/)
- Do not follow Section 3 of the CloudLab lecture, we will use a different repository. 

{% enddetails %}
## Setup GitHub Repository

- If you don't already have one, create a GitHub account. 
- Go to your GitHub account, under `Repositories`, select `New`.

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/github-new.png" width="50%" zoomable=true %}


- You can select any name for your repo.
- It must be `public`.
- The `Add a README file` box must be checked.
- Click `Create repository` when done.

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/github-create-repo.png" width="50%" zoomable=true %}

- Click `Add file` and select `Create new file`.

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/github-create-new-file.png" width="50%" zoomable=true %}

- Type `profile.py` for the file name and enter the code below into the 
text editor.
- Click `Commit new file` when done.

<script src="https://gist.github.com/linhbngo/060f8a99fbc3666b6abf8f05be54a28c.js?file=profile-basic.py"></script>

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/github-commit-new-file.png" width="50%" zoomable=true %}

---

## Setup CloudLab profile

- Login to your CloudLab account, click `Experiments`
 on top left, select `Create Experiment Profile`.

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-1.png" width="50%" zoomable=true %}

- Click on `Git Repo` 


{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-2.png" width="50%" zoomable=true %}

- Open another browser tab, go to the previously created Git repository, 
and get the URL of your Git repository

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-3.png" width="50%" zoomable=true %}

- Paste the URL of your previously created Git repo and click Confirm

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-4.png" width="50%" zoomable=true %}

- Enter the name for your profile, put in some words for the Description.
- You will not have a drop-down list of Project.
- Click Create when done.

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-5.png" width="50%" zoomable=true %}

- Click `Instantiate` to launch an experiment from your profile.

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-6.png" width="50%" zoomable=true %}
:alt: Instantiate an experiment from the profile 

- Select a Cluster from Emulab, then click `Next`.

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-7.png" width="50%" zoomable=true %}

- Do not do anything on the next Start on date/time screen. Click `Finish`.

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-8.png" width="50%" zoomable=true %}

- Your experiment is now being provisioned

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-9.png" width="50%" zoomable=true %}

- Your experiment is now being booted up

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-10.png" width="50%" zoomable=true %}

- A view of the booting experiment via the `List View` tab. 
    - Note the `Cluster` and `Status` column.

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-11.png" width="50%" zoomable=true %}

- Your experiment is now ready. 
    - Note the `Cluster` and `Status` column.

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-12.png" width="50%" zoomable=true %}

- You can ssh to the experiment from `molly` using the `ssh` command 
shown in the previous screenshot:
  - Type `yes` and press Enter when inquired about `The authenticity of host ...`
  - Type 2 to go with the default setting of zshell

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/cloudlab-profile-14.png" width="50%" zoomable=true %}

---

## Unix/Linux standards for access control
- Access control decisions depend on which user is attempting to perform 
and operation on that user’s membership in a UNIX group.
- Objects have owners. Owners have broad (but not necessarily unrestricted) 
control over their objects.
- You own the object you create. 
- The special user account `root` can act as the owner of any object. 
Only `root` can perform certain sensitive administrative operation. 

---

## Root and Rootly Powers
- The omnipotent administrative user (superuser)
  - Can perform all restrictive operations:
  - Creating device files
  - Setting the system clock
  - Raising resource usage limits and process priorities
  - Setting the system’s hostname
  - Configuring network interfaces
  - Opening privileged network ports (those below 1024)
  - Shutting down the system
- `sudo`: Running the commands as another user. If there is no username
  provided, the user is going to be `root`. 
  - For security purposes, the password of the `root` account should always 
  be very complicated and not be given out lightly. 
  - Administrative teams are often granted `sudo` power, meaning that they 
  can execute commands `in the name of` other accounts, including `root`. 

---

{% include figure.liquid path="assets/img/courses/csc586/04-access-control/sudo.png" width="50%" zoomable=true %}

---

- **How does it help with security aspects, since technically everyone 
  have rootly power anyway with sudo?**

---

## Hands-on: Rootly power
- SSH into the CloudLab experiment launched earlier. 
- `whoami`: Give you the effective user id of the one running the shell. 
- Run the following bash commands to observe the power of `sudo`:

~~~bash
whoami
sudo whoami
cat /etc/shadow
sudo cat /etc/shadow
~~~

---

## Other (less secure) means of granting rootly powers
- [`setuid`](https://man7.org/linux/man-pages/man2/setuid.2.html)
  - Grant privilege to the task (the program), not the user
  - Possible by leveraging a process' user ID:
    - real user ID (ruid)
    - effective user ID (euid)
    - saved user ID (suid)

~~~bash
id
~~~
 
- A way to grant privileges to `non-root` and `non-sudo` account. 

~~~bash
man chown
man chmod
cat /etc/shadow
which cat
cp $(which cat) mycat
./mycat /etc/shadow
sudo chown root mycat
sudo chmod 4755 mycat
./mycat /etc/shadow
~~~

---

## Managemen of the root account

- Why direct log in of root account is a bad idea. 
  - Root logins leave no record of what operations where performed as root. 
  - We also don't know who logged in as root. 
- By default, most systems allow root login to be disabled on
terminals, through the windows systems, and across the network.
  - Passwordless root account is another solution. 
- If root is accessible, password must be really good. 

---

## Challenge
- Run the following command to create a new account called `student`.  

~~~bash
sudo useradd -s /bin/sh -d /home/student -m student
~~~

- Search for documentation to find out how to turn `student` into an account 
with passwordless power. 

---

## Drawback of standard models
   
- Root access presents a potential single point of failure. 
- The `setuid` alternative is difficult to manage due to potential capability leaks
from complex software suites. 
- Minimal control over network security. 
- Group management cannot be done by users (more work for adminsitrators). 
- Access control rules are embedded in individual codes, cannot be easily rewritten. 
- Little to no support for auditing and logging.  

---

## Extensions to standard models
   
- PAM: Pluggable Authentication Modules
  - Wrapper for various method-specific authentication libraries
  - SSO (Single Sign-On)
- Kerberos: netowrk cryptographic authentication
  - Authentication rather than accesss control
  - Uses trusted third party to perform authentication for an entire network. 
- Filesystem access control lists )ACL)
  - Set permissions for multiple users and groups at once. 
- Linux capabilities
  - [man capabilities](https://man7.org/linux/man-pages/man7/capabilities.7.html)
  - Privileges traditionally associated with superuser are divided into 
  units, known as capabilities, which can be independently enabled and disabled. 
  - Capabilities are a per-thread attribute. 
  - This is in use extenively for higher-level systems like `AppArmor` or `Docker`. 
- Linux namespaces
  - Processes can be separated into hierarchical partitions (`namespaces`) from 
  which they see only a subset of the system's files, network ports, and processes. 
  - Preemptive access control. 
  - Foundation for software containerization
  - Docker
 
---

## Modern access control
   
- Linux's standard access control model is considered `discretionary access control` (DAC)
  - Owners of access-controlled entities to set the permissions on them. 
  - Bad example: users expose their home directories. 
- Mandatory access control (MAC)
  - Adminstrators write access control policies that override or supplement DAC. 
  - Enabling technology for new security models. 
  - Principle of least privilege
- Role-based access contrl (RBAC)
  - Added layer of indirection to access control calculations
  - Permissions are granted to intermediate constructs (`roles`), and 
  `roles` are assigned to `users`. 
  - `roles` can have hierarchical relationships (easier to administer)
- SELinux: Security-Enhanced Linux
  - MAC model
  - Created by NSA
  - Difficult to administer and troubleshoot
 
