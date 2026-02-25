---
layout: lecture
pretty_table: true
collection: csc588
course: CSC 603: Access Control in the Cloud
title: "Access Control: Properties, Policies, and Models"
toc:
  - name: Properties
  - name: Policies and Models
---

# Access Control: Properties, Policies, and Models


## Properties

{% details Objectives and enforcement artifacts %}

{% enddetails %}
  - Recall: 
    - authentication only ensures system users are who they claim to be. 
    - access control determines the allowed activities of legitimate users. 
  - Objective:
    - Protecting system resources against inappropriate or undesired user access. 
    - Optimizing sharing of information.
  - Abstractions of controls:
    - `Policies`
    - `Models`
    - `Mechanism`
  - Policies:
    - High-level requirements
      - How access is managed
      - Who may access what under what circumstances
    - Pertain to user actions within the context of an organizational units 
    or across organizational boundaries. 
    - Not useful to create a colelction of well known policies due to potential 
    differences. 
  - Mechanism:
    - Help enforcing policies
    - Can have policy advantages and disadvantages. 
    - Determining policy implications of a given access control mechanism is a formidable task. 
    - Components:
      - Users' security attributes
      - Resource attributes
      - Access control check to compare users'a security attributes against resource 
      attributes. 
  - Security Models:
    - Written to descrie security properties of access contrl system. 
    - Written to accomodate a wide variety of implementation choices and computing environments. 
    - Bridge the abstraction between policy and mechanism. 

{% details Core entities and principles %}

{% enddetails %}
  - Subject
    - A computer system entity that can initiate requests to perform an operation or a series of operations on objects. 
    - Can be users, processes, or domains.
    - Have exclusive access to their own memory
    - Different accesses to objects from different subjects
    - Semiautonomous 
  - Object
    - A system entity on which an operation can be performed. 
    - An abstract concept for modeling access control approaches
    - Resource objects (general interest) and system objects (sensitive core operations)
  - Principles of secure design
    - Least privilege
    - Economy of mechanism
    - Fail-safe defaults
    - Complete mediation
    - Open design
    - Separation of privilege
    - Least common mechanism
    - Psychological acceptability


{% details Reference monitor %}

{% enddetails %}
  - Abstract concept
  - All access that subjects make to objcets are authorized based on information 
    contained in an access control database.
  - Not a policy or implementation, but an assurance framework. 
  - Require three fundamental principles:
    - Completeness: always invoked and impossible to bypass.
    - Isolation: Tamper proof
    - Verifiability: Proven to be properly implemented. 
  - Additional three design principles:
    - Flexibility: enforce the access control policies of the host enterprise
    - Manageability: intuitive and easy to manage
    - Scalability: scale to the number of users and resources 

{% details Access control matrix and data structures %}

{% enddetails %}
  - Provide a framework for analyzing protection properties
  - State of an access control system is defined by a triple $(S,O,A)$ 
    - S is the set of subjects
    - O is the set of objects
    - A is an access matrix, which each entry is a set of rights. 
  - Access control data structures:
    - Capability list and access control lists (ACLs): Another realization of 
    the matrix format. 
    - Protection bits. 
```

## Policies and Models

{% details Discreationary access control (DAC) policies %}

{% enddetails %}
  - Restricting access to objects based on the identity of users or groups or both. 
  - A subject with discretionary access is capable of passing the information to another subject. 
  - Origin: ".. no person may have access ... unless access is necessary for the performance of 
  official duties." - DOD regulatory need-to-know requirement.
  - Inherently weak:
    - Granting read access is transitive.
    - Vulnerable to Trojan horse attack. 

{% details Mandantory access control (MAC) policies and models %}

{% enddetails %}
- Security levels are assigned to users, and subjects acting on behalf of users and objects. 
- Hierarchical and non-hierarchical components. 
- Levels are partially ordered under a dominance relations: TS > S > C > U
- Bell-LaPadula model:
  - A subject is permitted read access to an object if the subject's security level dominates 
  the object's security level.
  - A subject is permitted write access to an object if the object's security level dominates 
  the subject's security level. 

:::{image} ../fig/csc603/04-access-control/BellLaPadula.png
:alt: Bell-LaPadula security model (https://www.geeksforgeeks.org/introduction-to-classic-security-models/)
:class: bg-primary mb-1
:height: 500px
:align: center
:::


{% details Biba's integrity model %}

{% enddetails %}
  - An adjunct to Bell-LaPadula model. 
  - Forcus on integrity (unauthorized modification of information)
  - Prevent process at high security level from reading lower-level 
  objectts without being negatively affected by information at the lower security
  level. 
    - A subject is permitted read access to an object if the object's security level dominates 
    the object's security level.
    - A subject is permitted write access to an object if the subject's security level dominates 
    the object's security level. 

:::{image} ../fig/csc603/04-access-control/Biba.png
:alt: Biba integrity model (https://www.geeksforgeeks.org/introduction-to-classic-security-models/)
:class: bg-primary mb-1
:height: 500px
:align: center
:::


{% details The Clark-Wilson model %}

{% enddetails %}
- Addresses differences between military and commercial security requirements. 
- Keywords:
  - Transformation procedure (TP)
  - Constrained data item (CDI)
  - Unconstrained data item (UDI)
  - Integrity verification procedure (IVP)
- Model rules:
  - For any CDI, there must be an IVP
  - Every TP that modifies a CDI must be certified to only 
  modify in valid ways
  - A CDI can only be modified by a certified TP
  - Every TP must be certified to log its changes to CDIs
  - Any TP that takes UDI must perform valid transformation 
  - Only certified TP can modify CDI
  - Any user can access CDIs only through TPs for which the user is authorized
  - Every user must be authenticated before executing a TP
  - Only security admins can authorize users for TPs. 

:::{image} ../fig/csc603/04-access-control/ClarkeWilsonSecurityModel.png
:alt: Clark Wilson security model (https://www.geeksforgeeks.org/introduction-to-classic-security-models/)
:class: bg-primary mb-1
:height: 500px
:align: center
:::


{% details The Chinese wall policy model %}

{% enddetails %}
- Application-specific
- Prevent illicit flows of information that can result in conflict of interest. 
  - Example: consultants working for two banks
- COI categories limit user to access only one company within a single category. 
- If the user has not accessed any companies, there is no such limit. 

{% details The Brewer-Nash model %}

{% enddetails %}
- Write rule for the Chinese wall policy model
- Subject S can write object O only if
  - S can read O under the read rule
  - No object can be read within a different company dataset other than the one 
  for which write access is required. 
```





