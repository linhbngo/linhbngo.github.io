---
layout: lecture
pretty_table: true
collection: csc586
course: CSC 586: Linux System Administration and Security - Summer 2024 - 100% online asynchronous
title: "Networked File System"
toc:
  - name: Anyone knows/remembers?
  - name: Design goal
  - name: NSF design components
  - name: NFS protocol
  - name: NFS Server
  - name: NFS Client
  - name: Architectural Design
  - name: Challenge
---
# Networked File System

## Anyone knows/remembers?

{% include figure.liquid path="assets/img/courses/csc586/10-nfs/sun.png" width="50%" zoomable=true %}

*Sandberg, R., Goldberg, D., Kleiman, S., Walsh, D., & Lyon, B. (1985, June)*. [Design and implementation of the Sun network filesystem](http://www.cs.cornell.edu/courses/cs6411/2018sp/papers/nfs.pdf). In Proceedings of the Summer USENIX conference (pp. 119-130)

---

## Design goal

- Machine and operating system independence
- Crash recovery
- Transparent access
- UNIX semantics maintained on client
- Reasonable performance (target 80% as fast as local disk)

---

## NSF design components

- NFS protocol
- Server side implementation
- Client side implementation
 
---

## NFS protocol

- Remote Procedure Call (RPC) mechanism
  - Simplify the definition, organization, and implementation of remote services. 
- Stateless protocol
  - Parameters to each procedure call contain all the information
  necessary to complete the call.
  - The server does not keep track of past requests. This makes crash recovery easy. 
- Transport independent (works with both TCP and UDP). 
- Key procedure parameter: a file handler (`fh`)

---

## NFS Server

- Commit modified data to stable storage before returning RPC calls
  - Write to disk
- New parameter, generation number, for inode and file system id. 

---

## NFS Client

- Allow `mount` to attach remote file system
- New Unix kernel interface for all file system types: Virtual FileSystem (VFS)
  - Allows system calls to be unified
  - VFS will automatically determine/interact with the correct file system types, 
  including networked file systems. 

---

## Architectural Design

{% include figure.liquid path="assets/img/courses/csc586/10-nfs/nfs.png" width="50%" zoomable=true %}

---

## Challenge

- Modify CloudLab's experimental profile with the following requirements
  - Two nodes
  - One node setup as Ansible master (public IP)
  - One node setup as Ansible host (public IP)
  - On Ansible host, automate the setup of Ansible stack
- Keyoutcome:
  - By the time everything is setup, a webserver is available on the Ansible host.
  - Which means we are doing two things:
    - Manual setup (for testing purpose)
    - Convert setup commands to bash scripts ...

- Relevant documents:
  - [Setup NSF](https://www.digitalocean.com/community/tutorials/how-to-set-up-an-nfs-mount-on-ubuntu-20-04)
  - [Non-interactive passwordless SSH keygen](https://superuser.com/questions/1634427/non-interactive-ssh-keygen-in-windows-powershell-create-a-key-pair-and-avoid-pr)
  - [Install and configure Ansibe](https://www.digitalocean.com/community/tutorials/how-to-install-and-configure-ansible-on-ubuntu-18-04)
  - [Install and setup lamp on Ubuntu](https://www.digitalocean.com/community/tutorials/how-to-use-ansible-to-install-and-set-up-lamp-on-ubuntu-18-04) to setup 
  and create a LAMP stack using Ansible playbooks.

---
