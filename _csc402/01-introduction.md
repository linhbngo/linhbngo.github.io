---
layout: lecture
pretty_table: true
order: 2
title: "Introduction"
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
  - name: Course overview
  - name: Example success and failures
  - name: "Discussion: What is software engineering?"
  - name: The course project
  - name: Available project topics for Spring 2026
  - name: Challenges
---

*This class has originally been built based on Cornell's Software Engineering in Fall 2023.* 

## Course overview

{% details note Goals %}

- Ideal: To learn how to deliver quality software when the scope is 
larger and the stakes are higher
- Realistic: 
    - To work on a project that is significantly more complex 
    than previous courses
    - To learn to take on practices and mentalities that should be 
    as close to a real-world as possible
    - Sprinkles of theoretical concepts about `software engineering`

{% enddetails %}

{% details note Themes %}

- Engineering principles
- Management & teamwork
- Design
- Construction & maintenance
- Quality
- Delivery
- Professionalism

{% enddetails %}

## Example success and failures

{% details success Linux kernel (1991-present) %}

- [Wiki](https://en.wikipedia.org/wiki/Linux_kernel)

{% enddetails %}

{% details success SQLite (2000-present) %}

- [Wiki](https://en.wikipedia.org/wiki/SQLite)

{% enddetails %}

{% details Failure: Therac-25 (1982) %}

- [Wiki](https://en.wikipedia.org/wiki/Therac-25)
- [The Worst Computer Bugs in History: Race conditions in Therac-25](data/Therac25.pdf)
- [An Investigation of the Therac-25 Accidents](data/therac.pdf)

{% enddetails %}

{% details Failure: Ariane 5 (1996) %}

- [Wiki](https://en.wikipedia.org/wiki/Ariane_flight_V88)
- [The Worst Computer Bugs in History: Ariane 5 Disaster](data/arianne5.pdf)

{% enddetails %}

{% details Failure: Boeing 737 MAX (2017) %}

- [IEEE Spectrum: How the Boeing 737 Max Disaster Looks to a Software Developer](data/737max.pdf)
- Engine size issues when move from 737 to 737 Max design
- Boeing's solution to its hardware problem was software (Maneuvering Characteristics Augmentation System - MCAS)
- MCAS automatically pushed aircraft's nose down when it `thinks` the angle-of-attack exceeds its limit (too high up). 
    - It also uses Elevator Feel Computer to override the pilot's ability to manually pulling up (explicit 
    design decision)
    - If the angle-of-attack sensors are faulty (and they were for the incidents), MCAS only believes the sensors!

{% enddetails %}

## The course project

{% details note Teams %}

- Teams
    - 4-8 students
    - Ideal number is a team of 6, but depend on scope
- Check for compatible schedules and work styles
- Try to include members with both frontend and backend experience (well-rounded team)
- Students can form complete or partial team on their own
- For partial teams or students without team
    - Utilize the Discord server to specify that you are looking for 
    more members (which schedules/skills) or if you are looking 
    for a team (provide your schedules/skills)
    - The professor reserve the right to assign individual 
    members (I will most likely only to it for people who can't find 
    a team)
- Teams should be formed by the third lecture, where we will discuss 
the subject of Teamwork and collaboration

{% enddetails %}

{% details note Projects %}

- Projects from the course instructor
- Projects from WCU faculty
- Teams may petition for an external project:
    - Client may not be a student
    - Must be evaluated by the course instructor to ensure adequate complexity  
    - [List of example project ideas](https://engineering.tamu.edu/cse/industry-capstone-program/capstone-projects/index.html)
- Timeline: four 3-week sessions

{% enddetails %}


{% details note Project deliverables %}

- Session reports
- Plan
- Accomplishments, setbacks, discovered work
- Peer feedback
- Work log
- Design documentation
- Test plans and reports
- Coverage analysis
- Requirements
- Code and code reviews
- User documentation

{% enddetails %}


{% details note Self introduction %}

- Name
- Preferred programming language (or one you are most proficient with)
- Preferred operating systems and platforms/libraries (or one you are most familiar with)
- Anything else? 

{% enddetails %}

## Available project topics for Fall 2026

{% details note WCUPA HR Rammy AI Chatbot Enhancement %}

- Client: [WCU HR](https://www.wcupa.edu/hr/)
- Description: his CSC 402 Capstone project will modernize the HR Rammy AI Chatbot by replacing its current single-model setup with an advanced dual-model framework. To ensure a smooth transition, the project begins by building an isolated staging environment restricted to HR staff, giving the team a safe space to test updates without risking production uptime. To measure success, the team will create a standardized testing benchmark using real HR questions paired with human-approved answers. Using this benchmark, the project will evaluate a dual-model RAG architecture, separating query orchestration from response generation, across both fully local and hybrid setups against the current OpenAI model. Upon proving that a dual-model approach improves performance, privacy, and control- the team will deploy the upgraded system to production and deliver complete process documentation.

{% enddetails %}

{% details Jetson Tracking Sensor Package %}
    - Client: [SME Solutions Inc.](https://smexpertsolutions.com/)
    - Description:
        - The system is centered around an NVIDIA Jetson, which serves as the primary computing and control platform for the vehicle. A camera and other supported sensors connect directly to the Jetson using standard interfaces such as USB, Ethernet, or GPIO. The Jetson collects and processes sensor data, performs object detection and tracking, determines the desired vehicle motion, and generates commands to control the vehicle.
        - The architecture is intentionally modular so that sensors and software components can be added, removed, or replaced as the project evolves. Individual software modules may handle functions such as camera processing, object detection, sensor fusion, Guidance, Navigation, and Control (GNC), and vehicle control, while exchanging data through well-defined software interfaces.
        - The initial prototype will focus on integrating a small set of sensors and demonstrating an autonomous vehicle capable of detecting, tracking, and following a selected object. This provides a foundation that can later be expanded with additional sensors, algorithms, and autonomous behaviors.
{% enddetails %}

{% details Hiring Process Modernization %}
    - Client: [Chester County Department of Human Services](https://www.chesco.org/226/Human-Services)
    - Description: 
        - The Chester County Department of Human Services plans to update their existing candidate evaluation matrix to modernize and strengthen the county's hiring process. Building on the functionality of a data driven ranking system, this project will expand the use of a matrix to incorporate scoring criteria, improve usability for hiring managers, streamline documentation, and support more consistent, data‑driven assessments across all interviews. The updated scoring tool will need to align with established Departmental workflows, existing technological stacks, and other to-be-identified administrative and financial constraints.

{% enddetails %}

## Challenges

{% details What do you like the least about this class %}

- I didn't like the lectures. They felt like a waste of time when I could just be working on the project.
- The work for our client could feel disconnected at times from the material we learned in class. The material we learned in class was relevant to presentation projects, but the actual development for the client projects could feel less related.
- The lack of project choices and independent scoring in projects

{% enddetails %}

{% details Additional comments %}

- There were a lot of unrealistic expectations for this class. We only had about 12 weeks to work on the project, and the professor expected us to have a lot more done even though we all have 3 – 5 additional classes on top of this one. If this class is only 3 credits, expect only 3 credits worth of work! 
- Don't expect us to be Clemson students. There were so many references to "Clemson does it this way" or "Clemson students do this" we are West Chester students so only except result that a West Chester student would be able to give.
{% enddetails %}
