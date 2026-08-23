---
layout: lecture
pretty_table: true
order: 6
title: "Working in a Team"
mermaid:
  enabled: true
  zoomable: true
code_diff: true
map: true
chart:
  chartjs: true
  echarts: true
  vega_lite: true
tikzjax: true
typograms: true

toc:
  - name: Objectives
  - name: Feasibility studies are difficult
  - name: Things to consider in a feasibility study
  - name: Milestones and deliverables
  - name: Initial preparation steps
---

## Objectives

{% details Assess project feasibility %}

- Estimation
- Scheduling
- Risk
- Should you commit to a project?
    - Before committing, conduct a study to inform a go/no-go decision
    - Result may be a proposal or lead to a budget request

{% enddetails %}
{% details Produce a project plan %}

- A detailed project plan is critical  

{% enddetails %}
## Feasibility studies are difficult
    
{% details Must grapple with uncertainty %}

- Unclear scope
- Uncertain or hard-to-quantify benefits
- Rough estimates of resource requirements and timetable
- Technical approach may not pan out
- Organizational changes may be required
- Opportunity costs

{% enddetails %}
{% details Rely on judgement of experienced people %}

- Early mistakes are the most costly
    - Need to advocate to build support
- But beware risk distortion, ulterior motives
    - Example: US government agency

{% enddetails %}
{% details Discussion %}

- Designate one person as a note taker/final reporter 
- Which methodology is most appropriate for a large, complex project with 
incomplete requirements?

{% enddetails %}
## Things to consider in a feasibility study

{% details Overview %}

- Scope
- Approach
- Methodology
- Resources
- Schedule
- Risks
- Alternatives

{% enddetails %}
{% details Scope clarification %}

- Define the boundaries of the system
    - List of included features
    - List of excluded features
    - List of dependencies
    - List of current systems being replaced
- Confusion over scope often leads to client dissatisfaction
- Should also review existing systems (including competitors')

{% enddetails %}
{% details Technical approach %}

- Proposed system must be technically feasible
    - Estimates of scale (number of users, volume of data, rate of transactions)
    - Identify features that require research (no standard solution) or new team expertise 
    (domain-specific knowledge, advanced techniques)
- Analyze a viable design to estimate resources, schedule
    - Tentative system architecture (data storage, UI context, deployment infra)
- Approach used by final product may be very different

{% enddetails %}
{% details Estimation %}

- Essential skill for efficient planning

{% enddetails %}
{% details Discussion %}

- Designate one person as a note taker/final reporter
- Fermi problems: 
    - Tips: first identify dimensions of answer (dimensional analysis)
    - What is the sustained half-duplex bandwidth between Ithaca and NY 
    Tech of a UPS truck full of hard drives?
    - How many Raspberry Pi computers would be required to serve as a 
    distributed cache for a global reverse phone book?

{% enddetails %}
{% details Estimation for scheduling %}

- Estimating task duration is very difficult, but can be improved with feedback
    - Estimate effort of task before starting
    - Keep a log of time spent on each task (design, documentation, 
    implementation, testing, review)
    - Compare log to estimate when closing out tasks
    - Keep a log of time spent on other aspects of project (meetings, training, 
    reports, reviews)
- Do not evaluate effort until task is 100% complete
    - Large gap between "almost done" and "done"
    - Documentation
    - Tests
    - Cleanup
    - Review
- Beware Parkinson's Law: "Work expands to fill the time available"
    - Don't neglect startup time

{% enddetails %}
{% details Agile velocity %}

- Dartmouth example: projects consistently took 30-40% longer even when 
requirements were well understood.
    - Additional tasks discovered
    - Some tasks must be iterated
    - Personnel have other commitments
    - Schedule conflicts
- Decouple effort from time
    - Estimate effort required for task in relative units (e.g. "story points")
    - Tally the effort units completed by the whole team in one sprint: velocity
    - Use velocity to select appropriate number of tasks for future sprints; forecast milestones accordingly

{% enddetails %}
## Milestones and deliverables

{% details Deliverable %}

- Work product provided to the client
    - Mock-up
    - Demonstration
    - Prototype
    - Report
    - Presentation
    - Documentation
    - Code
- Release of a system or subsystem to customers and users

{% enddetails %}
{% details Milestone %}

- Completion of a predetermined set of activities
    - Delivery of a deliverable
    - Completion of a process step
    - End of a sprint
    - Reaching a testing target
- An internal goalpost, useful for monitoring progress against the schedule
    - Provides visibility

{% enddetails %}
## Initial preparation steps

{% details Outline plan %}

- Your first report requires an outline plan
    - Preliminary timetable
    - Process steps (or sprints)
    - Milestones (including deliverables)
    - Decision points
    - Interactions with and dependencies on external parties
- Plan should be reviewed, refined, revised regularly

{% enddetails %}
{% details Scheduling activities %}

- Inputs:
    - Duration
    - Dependencies
    - Resources

{% enddetails %}
{% details Activity networks %}

- Critical path analysis

{% include figure.liquid path="assets/img/courses/csc402/critical_path.png" width="50%" zoomable=true %}

- Gannt charts
    - In combination with milestones

{% enddetails %}
{% details Risk management %}

- Identify risks
    - Brainstorm what could go wrong
- Analyze risks
    - Determine likelihood and consequence
    - Prioritize based on "risk"
- Plan
    - Avoidance: reduce likelihood
    - Mitigation: reduce consequence
    - Contingency: "Plan B"
- Monitor
    - Update risks regularly
- Feasibility studies and project plans should be written
    - Well-written, well-presented – review entire document
    - Short enough that everybody reads it
    - Long enough that no important topics are skipped
    - A report that is not read and understood is not useful
- Keep in mind:
    - Team availability, team skills
    - Time constraints
    - Equipment and software
    - Start-up time
    = Client availability
    - Scope (not vague, not too ambitious)














{% enddetails %}
