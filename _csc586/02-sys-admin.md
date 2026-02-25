---
layout: lecture
pretty_table: true
collection: csc586
course: CSC 586: Linux System Administration and Security - Summer 2024 - 100% online asynchronous
title: "Linux System Administrators"
toc:
  - name: Controlling access
  - name: Adding hardware
  - name: Automating tasks
  - name: Overseeing backup
  - name: Installing and upgrading software
  - name: Monitoring
  - name: Troubleshooting
  - name: Maintaining local documentation
  - name: Vigilantly monitoring security
  - name: Tuning performance
  - name: Developing site policies
  - name: Working with vendors
  - name: Fire fighting
  - name: Relevant Tools
  - name: Specialization and related areas of emphasis
---
# Linux System Administrators


{% details Essential duties of a Linux system aministrator (sysadmin) %}

- Controlling Access
- Adding Hardware
- Automating Tasks
- Overseeing Backups
- Installing and Upgrading Software
- Monitoring
- Troubleshooting
- Maintaining Local Documentation
- Vigilantly Monitoring Security
- Tuning Performance
- Developing Site Policies
- Working With Vendors
- Fire Fighting

{% enddetails %}
---

## Controlling access

- Create new user accounts
- Remove expired accounts
- Handle all account-related issues
    - Access control

---

## Adding hardware

- Adding/removing physical components from the system
- Installing/configuring corresponding hardware drivers

---

## Automating tasks

- Leverage script programming (scripting) and Linux/Unix system commands to automate 
repetitive and time-consuming tasks. 
- Reduce human errors
- Improve response time
- Indispensable to adminstrating and managing large cluster of computers. 
- Example script installing and configuring Docker for all user accounts on CloudLab:

<script src="https://gist.github.com/linhbngo/060f8a99fbc3666b6abf8f05be54a28c.js?file=install_docker.sh"></script>

---

## Overseeing backup

- Computing systems **will** fail. 
- Large computing systems will **fail frequently**.
- Backup is time consuming, tedious, and **highly critical**. 
    - Should be automated!

---

## Installing and upgrading software

- Installing software as needed.
- Upgrading/patching security holes of existing software as needed.
    - Juggling multiple versions of same software. 
- Manage software to manage installed software.

---

## Monitoring

- Help identifying issues related to the computing systems. 
    - Collecting and analyzing log files
    - Monitoring resource avaiability (CPU and memory utilization, storage availability,)

{% include figure.liquid path="assets/img/courses/csc586/02-sys-admin/system_monitor.png" width="50%" zoomable=true %}

---

## Troubleshooting

- The sysadmin identifies the issue via monitoring or users' complaints
- The sysadmin needs to fix the issue. 

---

## Maintaining local documentation

- Overtime, computing systems will become customized according to the preferences and 
styles of their current sysadmins. 
    - Software vendors
    - Deployment methods
    - Automation scripts
- It is critical that sysadmins maintain detailed documentations so that **you** and others 
can understand/remember how the systems worked (and evolved) for maintenance and upgrade 
purposes. 

---

## Vigilantly monitoring security

- Attempts within 12 hours on `molly`:
    - This is only the most naive type of hacking attempts, there are others. 
- Exercise:
    - Visit https://www.iplocation.net
    - Find out where are these IP addresses located. 

{% include figure.liquid path="assets/img/courses/csc586/02-sys-admin/hacking_attempts.png" width="50%" zoomable=true %}

---

## Tuning performance

- Based on system monitors, sysadmins can, and should, configure 
system components (operating system configurations, software-specific configuration) 
in order to improve users’ application performance. 
- In many cases, sysadmins need to work with users to ensure that users apply 
application-specific run-time configuration to ensure optimal performance. 

---

## Developing site policies

- The main responsibility of sysadmins are to deploy and maintain complex 
computing systems that support a diverse set of applications and users. 
- This includes developing appropriate documents regarding:
    - Acceptable use of computer systems
    - Management and retention of data
    - Privacy and security of networks and systems
    - Adherence to regulation (local and governmental)
    - Anything specifics  that you want (hope) the users to follow ...

---

## Working with vendors

- Be the liaison between vendors and the institutions (businesses). 
    - Hardware vendors
    - Software vendors
    - Cloud providers

---

## Fire fighting

- On-the-fly troubleshooting of critical issues
    - Most of the time user-related
    - Critical patching of security issues (outside of normal maintenance schedule)

---

## Relevant Tools

- Highly comfortable with keyboard (say goodbye to the mouse)
- Know your environment (laptop)
- Text editors: nano or vim
- Scripting: bash (or Python or Ruby)

---

## Specialization and related areas of emphasis

- DevOps
- Site-reliability engineers
- Security operations (SecOps) engineers
- Network administrators
- Database administrators
- Network operations center (NOC) engineers
- Data center technicians
- System architects


