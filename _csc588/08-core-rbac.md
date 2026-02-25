---
layout: lecture
pretty_table: true
collection: csc588
course: CSC 603: Access Control in the Cloud
title: "RBAC Model Taxonomy"
toc:
  - name: Overview
  - name: Core RBAC
  - name: Hierarchical RBAC
  - name: Separation of Duty and RBAC Constraints
---

# RBAC Model Taxonomy


## Overview

{% details Models %}


{% enddetails %}
- Core RBAC
- Hierarchical RBAC
- Static constrained RBAC
- Dynamic constrained RBAC


{% details Roles versus ACL groups %}


{% enddetails %}
- ACL (access control list) 
  - a lower-level mechinism that contains names of subjects 
  that are authorized to access the object to which it refers.
  - specific permissions that are granted to each authorized subject
- Roles
  - at a basic level, could be equivalent to the concept of groups
    - collection of users
    - users can have multiple roles (belong to multiple groups)
  - semantically different from group
    - groups are implementation-specific and characteristics can change. 
    - roles are defined in term of properties with fixed characteristics. 
  
```

## Core RBAC


{% details Overview %}


{% enddetails %}
- Consists of `users`, `roles`, and `permissions`, which are `operations` applied to `objects`.
- Permissions are associated with roles. 
- Users are members of roles. 


{% details Administrative support %}


{% enddetails %}
- Permissions are assigned to roles
- Simplifying the understanding and management of permissions. 	
- Access requirements to resources are performed at the same level 
of abstractions as typical business processes in an enterprise:
  - role: teller, loan officer, doctor, nurse ...
  - operation: withdraw cash, deposit cash, write prescription, draw blood test


{% details Permissions %}


{% enddetails %}
- Reflect higher-level organizational policy	
- Mutually exclusive roles
- Cardinality: maximum numbers with respect to role	
- Pre-requisite:
  - can	assign	role	only if	already	assigned	prerequisite	role
  - Not hierarchical 


{% details Role activation %}


{% enddetails %}
- Properties and mappings in RBAC can be divided into static 
and dynamic components. 
- Dynamic components of RBAC includes role activation and subject access. 
  - Dynamic mapping of subject to user
  - Dynamic mapping of user to active role set. 


{% details Mapping the enterprise view to the system view %}


{% enddetails %}
- Privileges are system-specific and permissions are mapped into privileges. 
- Uses and roles can have common meaning across multiple systems. 

:::{image} ../fig/csc603/09-core-rbac/privilege-association.png
:alt: User-roles and role-privilege associations
:class: bg-primary mb-1
:height: 500px
:align: center
:::

- The relationship between roles and permissions depends on the scope on which 
RBAC is implemented. 
  - RBAC implemented within an operating system: integration with users/groups/operations 
  and resources of the computer system. 
  - For distributed systems: RBAC needs to be implemented at the LDAP/server level to support 
  SSO/Shibboleth Authentication. 

:::{image} ../fig/csc603/09-core-rbac/global-local-mapping.png
:alt: Mapping global users and roles to local user accounts, groups, and privileges
:class: bg-primary mb-1
:height: 500px
:align: center
:::

- First step for enterprise-level RBAC
  - Create and maintain direct associations between RBAC users and local user IDs. 
  - Local resources are protected via local users IDs and groups. 
- Operations and resources are created as abstractions.   

:::{image} ../fig/csc603/09-core-rbac/system-level-mapping.png
:alt: Mapping abstract permissions
:class: bg-primary mb-1
:height: 500px
:align: center
:::


```

## Hierarchical RBAC

{% details Role hierarchies %}


{% enddetails %}
- Permissions that are assigned to the role are known to contain, or be contained by, 
other roles in hierarchy. 
- A inherits B means all B's permissions are available to A. 
- Additional complexity cost in planning and construction but achieve improved 
adminitrative productivity.


{% details Building hierarchies %}


{% enddetails %}
- Motivation: individual roles have overlapping functions. 
- With role hierarchy, collections of permissions can be defined using 
multiple subordinate roles. 
- Example:
  - Physician inherits from Resident
  - Cardiologist inherits from Physician
  - Oncologist inherits from Physician
  - Accounts receivable clerk does not inherit from or is inherited by any
  of the above roles. 

:::{image} ../fig/csc603/09-core-rbac/example-hierarchy.png
:alt: Example of functional role hierarchy
:class: bg-primary mb-1
:height: 300px
:align: center
:::


{% details Inheritance schemes %}


{% enddetails %}
- Direct privilege inheritance
  - Closed management systems where there is only a single class of resources 
  and operations. 
- Permission and user membership inheritance
  - Role represents both collections of permissions and users. 
  - Top of graph represents more powerful roles
  - Greater opportutinies for redundant authorization of permissions to a user
  exist. 

:::{image} ../fig/csc603/09-core-rbac/privilege-graph.png
:alt: Baldwin's privilege graph
:class: bg-primary mb-1
:height: 500px
:align: center
:::

- User containment and indirect privilege inheritance
  - Used in distributed RBAC implementations
  - Permissions are assigned to groups and groups are mapped to roles. 
  - Users belong to groups
  - Examples: Supercomputing infrastructures


{% details Hierarchy structures and inheritance forms %}


{% enddetails %}
- Role hierarchies can also support
  - line of authority
  - functional delineation
  - geographic responsibilities
- Connector roles
  - not typicall assigned to users
  - define collection of permisisons to be inherited by higher-order roles. 
  - Example:
    - Physician inherits from Resident
    - `Specialist` inherits from Physician
    - Cardiologist inherits from Specialist
    - Oncologist inherits from Specialist
    - Accounts receivable clerk does not inherit 
    from or is inherited by any of the above roles. 

:::{image} ../fig/csc603/09-core-rbac/example-hierarchy-connector.png
:alt: Example with connector roles
:class: bg-primary mb-1
:height: 400px
:align: center
:::



{% details Organization chart hierarchies %}


{% enddetails %}
- Typical enterprises are structured and managed along organizational boundaries
  - departments, divisions, groups, and teams. 
  - OU: organizational units.

:::{image} ../fig/csc603/09-core-rbac/example-ou.png
:alt: Example organizational chart
:class: bg-primary mb-1
:height: 400px
:align: center
:::

- Means of precisely describe (delineate)
  - line of authority
  - resource ownership
  - areas of responsibility
- OUs do not
  - define complete sets of jobs positions or roles
  - prescribe privilege inheritance relations
- OUs do
  - assist in defining roles
  - represent collection of functions and users
  - define business processes and workflows


{% details General and limited role hierarchies %}


{% enddetails %}
- General hierarchies
  - support multiple inheritances of permissions and user membership among roles
  - allow a role to have more than one immediate ascendants (inheriting user membership
  from multiple sources) and more than one immediate descendents (inheriting permissions 
  from multiple sources).
  - Example: student worker
- Limited role hierarchies impose restrictions on the above characteristics:
  - single immediate descendent only. 
  - remain the norm in popular commercial authorization management products

- Stanford model:
  - Object-oriented approach to management enterprise's distribution of permissions. 
  - recognizes various layers of abstractions: entitlements, tasks, functions, roles

:::{image} ../fig/csc603/09-core-rbac/stanford-model-2.png
:alt: Stanford abstractions
:class: bg-primary mb-1
:height: 400px
:align: center
:::

:::{image} ../fig/csc603/09-core-rbac/stanford-model.png
:alt: Example Stanford model
:class: bg-primary mb-1
:height: 400px
:align: center
:::

```


## Separation of Duty and RBAC Constraints

{% details Overview %}


{% enddetails %}
- Separation of Duty (SoD) is a fundamental principle in security systems. 
- Critical operations are divided among two or more people, so that no single
individual can compromise security. 


{% details Type of SoD %}


{% enddetails %}
- Two broad categories: static and dynamic
  - Distinguish by the time at which the role constraints are applied. 
  - Static SoD places constraints at the time users are authorized for roles. 
  - Dynamic SoD constraints are applied when users are using the system. 


{% details Static SoD (SSD) %}


{% enddetails %}
- Enforce assignment of users to roles. 
  - If a user is assigned to one role, they cannot be member of another role. 
  - In the presence of a hierarchy, inherited roles are also considered when enforcing constraints. 
  - For example, a billing clerk role cannot also be a account receivable clerk role. 

:::{image} ../fig/csc603/09-core-rbac/static-sod.png
:alt: Example Stanford model
:class: bg-primary mb-1
:height: 400px
:align: center
:::



{% details Dynamic SoD %}


{% enddetails %}
- Users maybe authorized for roles with conflict, but limitations are imposed when the user is logged on to 
the system. 
  - Timely revocation of trust. 
  - Can still create policy concerns. 
  - Need extensive system support. 



{% details Using SoD in real systems %}


{% enddetails %}
- Most RBAC systems available today support role hierarchies
  - Property 1: Two roles $R_i$ and $R_j$ can be mutually exclusive only if neither
  one inherits the other, either directly or indirectly. 
  - Property 2: If there are two roles $R_i$ and $R_j$ that are mutually exclusive, 
  then there can be no third role that inherits both of them. As with property 1, this 
  property must be handled properly by role management tools to allow administrators 
  to set up role hierarchies that do not violate SoD constraints. 
  - Property 3: If static SoD holds, then DSD is maintained. Clearly, if a user 
  is only authorized for one of two roles, then he or she can never be 
  active in both. 
  - Property 4: If there are any two roles $R_i$ and $R_j$ that are mutually 
  exclusive, then there can be no `root` or `superuser` role active on the 
  system. 
- Mutual exclusion is used to enforce SoD policies. 
  - Exclusion specified by sets (membership in one set preclude membership in others)
  - Exclusion specified by role-pair (potentially computationally intensive)
- Assigning roles to users
  - Roles must be assigned in such away that no user can violate SoD rules through 
  a combination of roles. 
    - No single user posesses all privileges needed to accomplish a task controled 
    under SoD. 
    - Govem a set of roles and relationships, what is the minimal number of users 
    required to ensure SoD?


{% details Temporal constraints in RBAC systems %}


{% enddetails %}
- Incorporate the notion of time in specifying access control requirements
  - To limit resource usage in workflow environment
  - To limit role availability and activation capability
- Taxonomy
  - Temporal constraints on roles
  - Temporal constraints on user-role assignments
  - Temporal constraints on role-permission assignments
- Time-related concepts
  - Periodicity
  - Duration
- Constraints
  - Role-enabling and disabling constraints (e.g. enable role doctor-on-call for specific doctors)
  - Role-activation and deactivation constraints (e.g. duration available for download)
  - Role-permission assignments constraints (e.g., hire John Smith as contractor between Sep and Dec)
- Supporting requirements must also be enabled to support temporal constraints. 
```
