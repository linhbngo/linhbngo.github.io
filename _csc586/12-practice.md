---
layout: lecture
pretty_table: true
collection: csc586
course: CSC 586: Linux System Administration and Security - Summer 2024 - 100% online asynchronous
title: "Practice Scenarios"
toc:
  - name: Preparation
  - name: Scenario 1: LDAP-protected web server
  - name: Scenario 2: Shared home directory
  - name: Scenario 3: Webserver/Ansible
---

# Practice Scenarios

## Preparation

- Launch the `webserver-ldap` experiment on CloudLab. We will assume that there are three connected nodes:
  - `webserver`
  - `observer`
  - `ldap`. 

- The `webserver` should have an apache server ready (`setup_apache.sh`). 
- The `ldap` should have an ldap server ready. There should be 
one user account (student/rammy) created. 

---

## Scenario 1: LDAP-protected web server

- Enable the `public_html` directory and create an `index.html` 
page in that directory that displays `Hello World` when access. 
- Secure this location by requiring viewer to authenticate via the 
ldap server with the `student/rammy` login/password.  

---

## Scenario 2: Shared home directory

- Add the following users to the LDAP server
  - Make sure to change the password hash (password remains `rammy`)
  - Confirm that the users were added correctly by view the page 
  from scenario 1 using users `merino` and `dorper`. 

<script src="https://gist.github.com/linhbngo/060f8a99fbc3666b6abf8f05be54a28c.js?file=users-nfs.ldif"></script>

- Set up the NFS server on `ldap`.  
  - Create a directory called `nfs/home` and make it available 
  via NFS for both `webserver` and `observer`. 
- Setup NFS clients on `webserver` and `observer`. 
  - Create `nfs/home` and mount `/nfs/home` from `ldap` 
- Using `su` (do not use `sudo`), confirm that you can switch users, 
and that their home directories are shared across `ldap`, 
`webserver`, and `observer`.  
 
---

## Scenario 3: Webserver/Ansible
- Review [https://github.com/CSC586-WCU/csc586cloud/tree/webserver](https://github.com/CSC586-WCU/csc586cloud/tree/webserver) 
for correction against previous class' errors. 
- Instantiate the `webserver` profile. 
- Setup the Ansible `control` node to be an LDAP node. 
- Configure the apache server on the Ansible `host` node (previously installed via Ansible lamp stack) 
to be authenticated with the LDAP server on the `control` node. 
  - You can use the template `users.ldif` file from the lecture. 

---
