---
layout: lecture
pretty_table: true
collection: csc302

title: "Security at a Glance"
toc:
  - name: Computer Security: Additional attributes
  - name: Vulnerabilities and Attacks
  - name: Security Skills
---

# Security at a Glance

### 1. Computer Security

{% details Security Overview %}



{% enddetails %}
- Secure: Free from danger, free from risk of loss, affording safety, trustworthy, dependable
- What are we securing in a computer system?
  - Data (information)
  - Hardware/software systems (that store, manage, manipulate, and transfer data)
 

{% details Computer Security %}



{% enddetails %}
- Confidentiality
- Authenticity
- Integrity
- Non-repudiation
- Access control
- Availability
 

{% details CIA %}



{% enddetails %}
- Confidentiality
  - Keep your data private and only accessible by authorized person
- Authenticity
  - The origin of information is correctly identified
-  Integrity
  - Only authorized parties can change information


{% details The other three %}



{% enddetails %}
- Non-repudiation
  - Neither sender nor receiver can deny that they performed a transaction
- Access control
  - Access to information is controlled and limited to authorized parties
- Availability
  - User should have access to information assets as needed

```

## Computer Security: Additional attributes

{% details Overview %}



{% enddetails %}
- Reliability
- Availability
- Safety
- Liveness
- Self-stabilization


{% details Reliability %}



{% enddetails %}
- Expected time to system failure
  - Mean time to failure (MTTF)
  - Mean time between failures (MTBF)
 

{% details Availability %}



{% enddetails %}
- Percentage of time that a system is operational
 

{% details Safety %}



{% enddetails %}
- A condition where a predefined set of error conditions never occurs


{% details Liveness %}



{% enddetails %}
- A condition where a system always returns to a predefined set of desirable states (aspect of fault-tolerance)


{% details Self-stabilization %}



{% enddetails %}
- The ability of a system to recover from any possible fault condition
 
```

## Vulnerabilities and Attacks

{% details Seven categories of vulnerabilities %}



{% enddetails %}
- Architecture/Design: 
  - directly related to system design
- Behavioral Complexity: 
  - how system interacts to its environment
- Adaptability and Manipulation:
  - how a system's flexibility can impact its responsiveness to attacks
- Operation/Configuration: 
  - how systems can be used in an attacks
- Non-physical Exposure: 
  - vulnerabilities come from non-physical access to the systems (remote access)
- Physical Exposure: 
  - vulnerabilities come from direct access to the systems
- Dependency on Supporting Infrastructure: 
  - lack of power, air conditioning, network connections .. that causes the systems to fail

*A Common Language for Computer Security Incidents - John Howard and Thomas*


{% details Attack Surface %}



{% enddetails %}
- The number of components that an attacker can access
  - Number of open sockets
  - Number of open pipes
  - Number of open remote procedure call endpoints
  - Number of services
  - Number of services running with elevated privileges
  - Number of web server scripts, filters, and applications
  - Number of accounts with elevated privilege
  - Number of files, directories, etc. with weak access control


{% details Class of attacks %}



{% enddetails %}
- Interruption
- Interception
- Modification
- Fabrication
 
```

## Security Skills

{% details Overview %}



{% enddetails %}
- System knowledge (technical knowledge)
- Organizational knowledge (political/policy knowledge) 
- Sense of Security
- Security principles knowledge

```
