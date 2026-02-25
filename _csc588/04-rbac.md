---
layout: lecture
pretty_table: true
collection: csc588
course: CSC 603: Access Control in the Cloud
title: "RBAC: Role-based Access Control"
toc:
  - name: Overview
  - name: NIST RBAC
  - name: Role Engineering
---

# RBAC: Role-based Access Control


## Overview

{% details Basic RBAC illustration %}


{% enddetails %}
:::{image} ../fig/csc603/05-rbac/basic_rbac.png
:alt: Basic RBAC illustration
:class: bg-primary mb-1
:height: 500px
:align: center
:::


{% details Reference Models %}

{% enddetails %}
- RBAC<sub>0</sub>: minimum functionalities
- RBAC<sub>1</sub>: RBAC<sub>0</sub> + role hierarchies
- RBAC<sub>2</sub>: RBAC<sub>0</sub> + constraints
- RBAC<sub>3</sub>: RBAC<sub>1</sub> + RBAC<sub>2</sub> 
  

{% details RBAC<sub>0</sub> %}

{% enddetails %}
- Users:	individuals	with access	to the	system	
- Role:	named	job	function within the	org	
- Permission:	approval of	a	particular	mode	of access to objects	
- Session:	mapping	between	a	user and a	subset	of	roles 

:::{image} ../fig/csc603/05-rbac/rbac0.png
:alt: RBAC0
:class: bg-primary mb-1
:height: 500px
:align: center
:::


{% details RBAC<sub>1</sub> %}

{% enddetails %}
- Reflect	hierarchical structure of roles in org	
- Mathematically,	partial	order (reflexive, transitive,	antisymmetric)

:::{image} ../fig/csc603/05-rbac/rbac1.png
:alt: RBAC1
:class: bg-primary mb-1
:height: 500px
:align: center
:::


{% details RBAC<sub>2</sub> %}

{% enddetails %}
- Reflect higher-level organizational policy	
- Mutually exclusive roles
- Cardinality: maximum numbers with respect to role	
- Pre-requisite:
  - can	assign	role	only if	already	assigned	prerequisite	role
  - Not hierarchical 


{% details RBAC<sub>3</sub> %}

{% enddetails %}
- Consolidation

:::{image} ../fig/csc603/05-rbac/rbac3.png
:alt: RBAC3
:class: bg-primary mb-1
:height: 500px
:align: center
:::

```

## NIST RBAC

{% details Overview %}

{% enddetails %}
- RBAC System and Administrative Functional Specifications
- Three categories:
  - Administrative functions: create, delete, maintain RBAC elements and relations
  - Supporting system functions: session management, access control decisions
  - Review functions: query operations on RBAC elements and relations
- Four components:
  - Core RBAC: similar to RBAC<sub>0</sub>
  - Hierarchical RBAC: similar to RBAC<sub>1</sub>
  - Static Separation of Duty (SSD):
    - Prevent conflict of interest
    - Cardinality constraints (e.g., maximum number of roles)
    - Mutually exclusive roles
  - Dynamic Separation of Duty (DSD):
    - Similar to SSD but activated within session
    - Temporary conflict of interest (e.g., author and PC member of a conference)

:::{image} ../fig/csc603/05-rbac/nist_rbac.png
:alt: NIST RBAC
:class: bg-primary mb-1
:height: 500px
:align: center
:::


{% details Unspecified by NIST RBAC %}

{% enddetails %}
- Scalability
- Authentication
- Negative permissions
- Nature of permissions
- Discretionary role activation
- Role engineering
- Constraints
- RBAC administration
- Role revocation
```

## Role Engineering

{% details Overview %}

{% enddetails %}
- Definition of role can be difficult
  - Requirement engineering process
- Basic steps:
  - Collect activities
  - Group into clusters
  - Name clusters
  - Describe
  - Remove duplicates
  - Indentify minimal set of permissions
  - Simulate activities
  - Role candidates

{% details Case Study: RBAC for a bank %}

{% enddetails %}
- Migrating from old local access control files
- Application now query security for authorization profiel
- Role = (official position, job function)

:::{image} ../fig/csc603/05-rbac/case1.png
:alt: role and functions
:class: bg-primary mb-1
:height: 400px
:align: center
:::

:::{image} ../fig/csc603/05-rbac/case2.png
:alt: Role, applications, and access rights
:class: bg-primary mb-1
:height: 400px
:align: center
:::

:::{image} ../fig/csc603/05-rbac/case3.png
:alt: Assume B inherits A
:class: bg-primary mb-1
:height: 400px
:align: center
:::

:::{image} ../fig/csc603/05-rbac/case4.png
:alt: Architecture
:class: bg-primary mb-1
:height: 500px
:align: center
:::

```

