---
layout: lecture
pretty_table: true
collection: csc402
course: CSC 402: Software Engineering.
title: "Software Projects and Process Models"
toc:
  - name: Software projects
  - name: Stakeholders
  - name: Risk
  - name: Minimizing risk
  - name: Development processes
  - name: Software methodologies
  - name: Agile methods and eXtreme Programming (XP)
---
# Software Projects and Process Models

## Software projects

{% details note Project variety %}

- No two projects are the same. Even a single project 
may serve many different purposes, in many 
different settings, for many different people.
- Project variety demands developer versatility.
- There is no `best` way to create software in all cases.
- A software engineer must know a wide variety of methods & tools and 
select appropriate ones for the project at hand

{% enddetails %}
## Stakeholders

- First step in any project: identify the stakeholders.
- Stakeholder interests are not always aligned.

{% details note Developers %}

- Should be considered a stakeholder (but not the most important one)
- Are also an expensive resource
- Have responsibilities of competence, confidentiality, compliance

{% enddetails %}
{% details note Client %}

- Provides resources in exchange for software
- Bears risk in event of project failure
- Sets requirements, priorities
- Client satisfaction is primary measure of project success

{% enddetails %}
{% details note Customer %}

- Buys the software or selects it for use by an organization
- What is the difference between `Customer` and `Client`?

{% enddetails %}
{% details note User %}

- Actually uses (interfaces with) the software

{% enddetails %}
{% details note Society %}

- May be affected by the software
- Often not represented when stakeholders are consulted
- Advisable to appoint an advocate for their interests
- Automated processes tend to become invisible
- Risks to society should be identified and acknowledged

{% enddetails %}
{% details Example: Discussion %}

- Designate one person as a note taker/final reporter 
for the group. 
- Identify the stakeholders (developer, client, customer, user) for:
    - ramportal.wcupa.edu
    - The FAA’s Advanced Automation System (based on assigned reading)

{% enddetails %}
## Risk

All projects require tradeoffs between function, cost, and time

{% details Question: Who should set priorities when deciding tradeoffs? %}

The client should be given the information necessary to make an informed 
decision based on their priorities

{% enddetails %}
{% details note Consequences %}

- Failed projects can bankrupt companies.
- Managers can lose their jobs
- Users and society may be harmed

{% enddetails %}
## Minimizing risk

{% details note Communication %}

- As much as half of delivered software is never used
    - Developers build the “wrong software” – doesn’t meet client’s needs
- Developer must work to understand client, customer, and user expectations
- Developer may add technical insights, but **client satisfaction** is the primary 
measure of success

{% enddetails %}
{% details note Communicating via deliverables %}

- Feasibility study
- Requirements and design (separated)
- Milestones & releases
- User & acceptance testing
- Handover

{% enddetails %}
{% details note Visibility %}

- Those responsible for the project (client, managers) must 
know what is happening
- But most developers are bad at providing good visibility
- Large projects dilute visibility at each layer of hierarchy
- Working software provides good visibility
    - But be upfront about limitations
- Short dev cycles improve visibility
- Risk accumulates with time since last check-in
- Deliver working software frequently (weeks rather than months, or 
even continuously)
    - Clients, customers, & users can evaluate work
    - Opportunity to adapt to new circumstances

{% enddetails %}
{% details note Management %}

- Project management
    - Track progress against schedule
    - Prioritize tasks
- Personnel management
    - Allocate the right number of developers with the right skills 
    at the right time
    - Ensure that developers have a productive work environment
- Compliance advising
    - Understand legal, regulatory, economic environment
- Development processes
    - Enforce best practices to minimize risk without excessive overhead

{% enddetails %}
## Development processes

{% details note Overview %}


- Composed of process decisions
- Tradeoff between risk reduction and overhead
    - Effectiveness, cost depend on tool support, developer skill, culture
    - Initial risk depends on project size
    - Risk tolerance depends on application
- Must adapt process to each project
- Aim to improve processes throughout project

{% enddetails %}
{% details note Process steps %}


- Project specifics are different, but they need to address similar issues
- Process decisions should be adopted to address common process steps
- Testing & documentation occur in many steps
- Feasibility & planning
- Requirements
- System & interface design
- Program development (includes program design)
- Acceptance and release
- Operations and maintenance

{% enddetails %}
## Software methodologies

{% details note Waterfall model %}


- Heavyweight
- Based on traditional engineering project management
- Was a reasonable choice for early software
    - Well-understood requirements
    - Standardized system design
    - Coding was tedious
- Advantages
    - Separation of tasks
    - Process visibility
    - Quality control, cost monitoring at each step
- Disadvantages
    - Does not account for revising earlier stages
    - Not flexible enough to react to changing conditions
- Cost of defects
    - Cost of defects can be exponential in time between introduction and discovery
    - "Shift left": catch defects as early as possible
    - Traditional waterfall deliverables are not effective at catching many defects
- Modified waterfall model
    - Appropriate when requirements are well understood and system design is fixed
    - Recommended for safety-critical and highly-regulated systems
    - Requirements must be thoroughly analyzed and documented

{% enddetails %}
{% details note Iterative refinement: prototype development %}


- Medium-weight process
    - Create early prototype
    - Review prototype with stakeholders; clarify requirements
    - Refine prototype
- "Plan to throw one away" (prototypes are not release-worthy)
    - Prototype can’t be used to evaluate non-functional requirements
    - Revising working but low-quality code is difficult; better to start over after requirements are clarified
- Incremental delivery
    - Deliver fully-tested increments with subset of functionality

{% enddetails %}
## Agile methods and eXtreme Programming (XP)

{% details note Overview %}


- User stories
- Incremental planning
- Small releases
- Simple design
- Test-first development
- Periodic refactoring
- Pair programming
- Collective ownership
- Continuous integration
- On-site customer
- Often not realistic as originally proposed. Relies on developer autonomy.

{% enddetails %}
{% details note Scrum %}


- Provides management structure for XP
- Work scheduled in time-boxed “sprints” (2-4 weeks)
- Tasks selected from backlog
- Sprint product is production-ready code + docs
- Daily team meetings
- Benefits:
    - Provides good visibility and communication
    - Accommodates vague, changing requirements
    - Popular for small, dynamic projects
- Challenges:
    - Tricky to scale to large projects
    - Poor fit for bureaucratic organizations
    - Works best with highly-skilled developers
    - Hard to validate requirements for completeness
    - Lack of formal "internal" documentation impedes maintenance, handoff

{% enddetails %}
{% details note Integration and configuration %}


- When system design is standardized, can better take advantage of code reuse
- Leverage commercial-off-the-shelf (COTS) platforms
- Integrate and configure existing components based on client requirements
- Reduced cost and time, at expense of functionality

{% enddetails %}
{% details note Mixed processes %}


- Many projects mix elements of multiple methodologies
- Phased development
    - Early benefit from initial investment
    - Clarifies requirements for later phases
    - Facilitates cost control










{% enddetails %}
