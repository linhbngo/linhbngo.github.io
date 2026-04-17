---
layout: lecture
pretty_table: true
collection: csc302

title: "Introduction to SEED Labs"
---
# Introduction to SEED Labs

{% details 1. Overview %}



{% enddetails %}
- NSF-funded project since 2002
- Hands-on, practical approach to learning computer security
- Labs are self-contained and can be created/run on individual students' computer


{% details 2. Platforms %}


{% enddetails %}
- First choice: Docker containers
  - Pros: Light-weight
  - Cons: Might be a bit difficult to use, especially on Windows

- Second choice: VirtualBox VM
  - Pros: Full administrative control, full isolation from host environment
  - Cons: The SEED VM files are massive, and running VM takes up a lot of resources

- Third choice: CloudLab
  - Pros: When your personal computer cannot support first or second choice
  - Cons: Very cumbersome to setup


{% details 3. Hands-on: Setup your own SEED platform %}


{% enddetails %}
- Try Docker first: 
  - Visit https://docs.docker.com/desktop/install/ and figure out how to install Docker Desktop
  and whether your computer will support it. 

- If Docker doesn't work, try VirtualBox for VM
  - Visit https://www.virtualbox.org/wiki/Downloads, download and install VirtualBox

```
