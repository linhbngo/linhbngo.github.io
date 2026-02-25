---
layout: lecture
pretty_table: true
collection: csc402
course: CSC 402: Software Engineering.
title: "Introduction"
toc:
  - name: Course overview
  - name: Example success and failures
  - name: Discussion: What is software engineering?
  - name: The course project
  - name: Available project topics for Spring 2026
  - name: Challenges
---
# Introduction

*This class is based on Cornell's Software Engineering course.* 

## Course overview

{% details note Self introduction %}

- Name
- Preferred programming language (or one you are most proficient with)
- Preferred operating systems and platforms/libraries (or one you are most familiar with)
- Anything else? 

{% enddetails %}
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
## Discussion: What is software engineering?

{% details note Form groups %}

- For this discussion, groups of five to six are to be 
randomly formed
- Reintroduce yourselves to one another: Names, Years

{% enddetails %}
{% details Example: Discussion %}

- Designate one person as a note taker/final reporter 
for the group. 
- Discuss the following question: 
    - What makes **software engineering** different from **programming**?

{% enddetails %}
## The course project

{% details note Teams %}

- Teams
    - External projects: 6-8 students
    - Personal projects: 4-6 students
- Check for compatible schedules and work styles
- Try to include members with both frontend and 
backend experience (well-rounded team)
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
## Available project topics for Spring 2026

{% details note Operations Workflow Modernization %}

- Client: [Polaris Brand Promotion](https://polarisbrandpromotions.com/)
- Description: This project asks the team to modernize a real operations workflow at Polaris Brand Promotions 
by replacing worksheet-based storage solutions, one for scheduling shifts/events and one for client billing & contractor 
payroll, with a secure, cloud-based web application backed by a database. You’ll design the data model so shared fields 
can flow reliably from scheduling into billing/payroll. You will also work on adding more advanced features such as 
searchable client and staff profiles, single-shift entry forms plus bulk CSV/Excel import, reporting dashboards/exports 
for operations and finance, automatic daily backup emails of the data as Excel/CSV, and an audit trail that records which 
logged-in corporate user created or edited each record. The system will be standalone (not integrated into an existing
IT environment), and you’ll work from provided sample/updated spreadsheet extracts rather than direct access to Polaris’ 
live data. Therefore, part of the engineering challenge is building something robust, testable, and maintainable with 
realistic data constraints and clear handoff documentation. 

{% enddetails %}
{% details note AI HR Assistant %}

- Client: West Chester University Human Resources Department
- Description: This project aims to develop and deploy a secure, cost-aware AI chatbot to assist West Chester 
University employees with Human Resources–related inquiries. The system is designed to support high-volume topics 
such as benefits eligibility, leave policies, employee and student worker recruitment questions, and onboarding by 
providing timely, 24/7 access to institution-approved information. Unlike basic informational chatbots, the solution 
incorporates advanced retrieval and reasoning capabilities that allow it to handle contextual, multi-step HR questions 
and determine eligibility outcomes based on user-provided information. The chatbot will operate exclusively within the 
HR domain, reinforcing scope control and reliability while reducing administrative burden on HR staff. The project 
emphasizes responsible AI use through strong data governance practices, including avoiding the collection or storage 
of personally identifiable information, and prioritizes cost-effective operation by leveraging university-managed 
infrastructure. The final outcome is a production-ready system that enhances the employee experience while remaining 
secure, scalable, and sustainable.

{% enddetails %}
{% details note Intelligence Capability Enhancement %}

- Client: [iPipeline](https://ipipeline.com/)
- Description: This iPipeline project focuses on applying AI to interpret internal data, surface meaningful 
insights, and automate tasks that today require slow, manual effort. The goal is to build intelligent capabilities 
that can understand documents, conversations, and decision outputs, and then translate that understanding into 
clear, actionable information for the teams who rely on it. Your role on this project may include:
    - Developing components that analyze and compare internal data to highlight important changes, patterns, or discrepancies
    - Building tools that allow employees to quickly turn raw operational information into insights they can act on
    - Contributing to intelligent automations that reduce manual review, streamline workflows, and help teams make faster, 
    more informed decisions across multiple iPipeline processes

{% enddetails %}
{% details 3D Flight Visualization System %}

- Client: [SME Solutions Inc.](https://smexpertsolutions.com/)
- Description:
    - Develop an open and modular flight visualization application using a modern game engine. 
    - Application will accept real-time motion data and render a real-time 3D visualization of an object during flight.
    - Input data stream will include position data, 6 degrees of freedom, acceleration, etc…
    - The application should be optimized to run on a customer provided NVIDIA Jetson Orin Nano board.
    - Upon data stream completion, application shall provide full flight playback for user review and analysis

{% enddetails %}
{% details Mobile Application Development to Support Biomedical Engineering Device %}

- Client: [Orthoforge](https://www.orthoforge.com/)/BME Capstone team
- Descriptions: WCU BME Capstone Team is developing a quantitative ultrasound device for Orthoforge that attaches 
to a patient’s cast to monitor distal radius fracture healing progress. Your capstone team will help turn the device’s 
raw sensor signals into something clinicians (and optionally patients) can actually use. From a Computer Science 
standpoint, the project can potentially be split into two connected layers:
    - A data transfer layer that utilizes bluetooth or similar wireless technologies to periodically transfer captured data to 
    a device (PC/mobile phone/etc), from which the aggregated data can be moved to a remote repository for further processing. 
    - An application layer (mobile app) that allows patients and clinicians to view the processed results. 
    - There could be additional software development on the analytical layer that ingests and performs signal processing/data 
    analytics on the transferred data. 

{% enddetails %}
{% details Predictive Analysis for Manufacturing %}

- Client: [ProfitMatrix](https://profit-matrix.com/)
- Description: This project is a fantastic opportunity to apply your AI/ML skills to a real-world business challenge. Our goal is to move from simply reporting on profitability to helping small manufacturers proactively identify issues and fix root causes. The primary objective is to build a machine learning model that incorporates time-based forecasting and cluster analysis.
    - Data Structure: You'll start by working with our existing PostgreSQL database that consolidates manufacturer’s ERP data from sources such as Microsoft Dynamics, Netsuite, and SAP. You will be focusing on tables related to sales orders, product hierarchies, and cost of goods sold (COGS) and working closely with our Lead Architect to determine the best method to prepare and feed this data through the model.
    - Model Development & Training: You’ll build a machine learning model that automatically analyzes the data to find patterns, make predictions, and automate decisions without being explicitly programmed for every scenario.
    - Root-Cause Analysis: You’ll dig deeper and perform a statistical analysis to determine the primary drivers of low profitability—is it due to inadequate pricing (e.g., high discounts) or excessive costs (e.g., high material or production costs) or changes in product/customer mix or other features you’ve identified?
    - Prediction: Generate a 3-to-6-month forecast for the variable margin trend, including confidence intervals. 
    - Develop Actionable Recommendations: Based on your root-cause analysis, propose clear, data-driven recommendations to improve & optimize profitability, such as adjusting prices, renegotiating costs, or discontinuing a product.
    - Visualization: Create clear and compelling visualizations to communicate your findings and the model's predictions to a non-technical audience.

{% enddetails %}
{% details note Improvement website platform for WiCS/DAiM %}

This project builds on the existing Women in Computer Science (WiCS) website developed in a previous course and is a 
joint effort between the Women in Computer Science Club and the Data Science, Ai, & ML Club (DAiM) at West Chester 
University. The Capstone team will enhance and extend the current platform by redesigning the frontend to be more 
professional, accessible, and functional, while also strengthening the backend through improved organization, testing 
coverage, and CI/CD workflows etc. The project will also introduce an AI-driven internship and opportunity hub 
designed to help students identify relevant opportunities they may have otherwise overlooked, both within West Chester 
University and beyond. In addition, the website may be expanded to reflect the overlap between the two organizations 
by incorporating AI, machine learning, and data science–related content or features. Overall, the project emphasizes 
maintainable, real-world software development practices and cross-organization collaboration while delivering a 
meaningful resource for the student community

{% enddetails %}
{% details note Surgical Procedure Preparation App %}

- Client: Dr. Neil R. Malhotra, Professor of Neurosurgery at Penn Medicine
- Description: The primary goal of this project is to develop a novel extension of an innovative digital platform designed to transform surgical and procedural care. While our initial work focused on guided preparation before procedures, this new phase centers on procedural documentation after care has been delivered—an area of critical importance to patient safety, quality improvement, and system-wide learning. Our medical group has a strong and sustained track record in advancing patient safety, quality, outcomes, and efficiency, with more than 200 peer-reviewed publications in these areas. The existing platform has already been successfully developed and deployed; this project represents a natural and ambitious evolution of that work. By focusing on post-procedural documentation, the project aims to capture expertise, reduce variability, and create structured data that can meaningfully inform clinical decision-making and operational improvement. The platform translates clinical expertise into a powerful digital tool that simplifies workflow, enhances safety, and reduces the cost of care. It is built around three integrated components: (1) a clinician-facing, AI-supported iOS interface that enables efficient and intuitive procedure documentation; (2) an administrative and analytics dashboard designed to support oversight, quality improvement, and research; and (3) integrated communication tools that strengthen feedback loops among clinicians, administrators, and other stakeholders. This project offers a unique opportunity to work closely with an experienced, multidisciplinary team at the intersection of medicine, technology, and innovation. We are seeking motivated students who are intellectually curious, comfortable with complexity, and eager to contribute in a fast-paced, collaborative environment. Participants will gain hands-on experience building tools with real-world clinical impact, while helping shape the future of patient safety and procedural care. *Teammates wanted for hazardous journey. Small wages, bitter cold, long months of complete darkness, constant danger, safe return doubtful. Honour and recognition in case of success.* – Ernest Shackleton

{% enddetails %}
{% details note General project ideas %}

- It is OK to start your own project ideas. What I want you to keep in mind is that you want to build something big, something 
that last beyond the scope of this class. 

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
