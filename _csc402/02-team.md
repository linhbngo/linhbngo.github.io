---
layout: lecture
pretty_table: true
collection: csc402
course: CSC 402: Software Engineering.
title: "Working in a Team"
toc:
  - name: Overview
  - name: Aspects of software engineering teams
  - name: Examples of conflict resolutions in Team
  - name: Client meeting.
  - name: Team preparation checklist
---
# Working in a Team

## Overview

{% details Necessity of teams and organizations %}

- Large projects require many people
    - Need to deliver while still relevant
    - Diversity of ideas, peer review improve quality
    - Utilize many different skill sets
- Multi-person development requires collaboration

{% enddetails %}
{% details Team size %}

- Number of pairwise communication paths is quadratic in team size
    - Cannot understand full system, keep pace with all updates
    - Need efficient meetings, decisions
    - Quality benefits from consistency
- Effective teams have 4-10 members; sweet spot is around 7

{% enddetails %}
{% details Myth of the man-month %}

- Development effort often measured in person-months
    - How much does one developer accomplish in one month?
- Suggests that work could be sped up by adding more developers
- Brooks’s law: `adding manpower to a late software project makes it later`

{% enddetails %}
## Aspects of software engineering teams

{% details Team member roles %}

- No `team leader`
    - Project is a shared responsibility
    - Team decisions by consensus
- Team point-of-contact
    - Communicates with client (scheduling, reports)
    - Communicates with course staff
- Project manager
    - Maintains schedule
    - Monitors risks
    - **Does not** dictate tasking
    - May rotate
- Toolsmith
    - Infrastructure expert (DevOps)
- Roles during meetings
    - Moderator
    - Recorder

{% enddetails %}
{% details Developer strengths and motivations %}

- Developer growth through
    - Mentorship
    - Training
    - Self-learning
    - Documentation
    - Reviews
    - Goals (w/ manager assistance)
    - Osmosis (slow, shallow)
    - At a point in time, some devs may be much more productive than others
    - But all devs have the potential to become more productive
        - Maximize benefit by "leveling up" early
        - "Teach a man to fish" parable
        - Will get most out of this course by leveling up your whole team

{% enddetails %}
{% details Team disfunctions %}

- Examples of what you have observed in your previous team projects?
- Yak shaving
    - Balance quality/growth with short-term productivity
    - Prioritize simplicity
- Bike-shedding
    - Prioritize addressing the largest technical risks

{% enddetails %}
{% details Setting expectations %}

- Avoid misunderstandings, disappointment by setting clear expectations
    - Capture in writing: team charter, iteration plan
- Be consistent, firm when expectations are not met
    - Address acute issues ASAP
    - Address persistent, lingering issues at retrospectives
- Communicate often, ask for help if stuck

{% enddetails %}
## Examples of conflict resolutions in Team

{% details Original email A %}

I’m writing to address some concerns regarding our --- group project. With only 2-3 weeks left, 
it's clear that we're facing significant challenges in terms of project viability and technical development. 
Currently, our project lacks the necessary components to be presented as a prototype. While we have functional 
elements such as the …. and the …. server for entry storage, there are several critical components still missing 
for our cloud-based diary platform to be fully functional. 

I'd like to address some specific concerns regarding attendance and contribution:

A and B, there has been a severe lack of attendance and contribution from both of you. I haven't seen any code 
or YAML files from either of you in our GitHub repository, and your absence from group meetings and classes 
has been noted. I don't think it is justifiable at this stage in the process to be missing from group work and 
not contributing. 

A, I understand you're working on the …... service for user authentication, with the starter code I already 
provided, but I haven't received any updates. B, while you mentioned working on the …. and security encryptions, 
I haven't received progress reports or heard from you in a while. 

As for me, I've managed to set up a …. server on Kubernetes, but I need assistance in connecting it to the 
document pages, which are still under development. C, it would be very helpful if we could collaborate on this 
during tomorrow's class and afterward.

Given the current situation, I propose that we prioritize the technical aspects of the project and focus on 
developing a working, rudimentary deployment and CI/CD pipeline. This approach will ensure that we address 
the most critical requirements by the project deadline even if we can't do all that we promised.

I urge everyone to attend tomorrow's class and the weekly meeting at 12:15 in the lounge. I don't think we 
can afford any more absences or lost time. We must come together as a team to salvage and make this project 
a success.

Let's regroup tomorrow to strategize and allocate tasks effectively.

{% enddetails %}
{% details Feedback A %}

Hi Dr. Ngo,  

I am completely fine with permitting the use of our letter as an example for future student groups. 

Quite frankly, I'm not sure the letter worked in fixing our technical issues, but it did make it clear 
to the group members who weren't contributing that they needed to increase participation. A did start attending 
more meetings (even though their contributions did not increase). B had family issues but at least they was there 
for the presentations and did her part on some HTML files. I think that issues like this should be addressed 
relatively soon in the project to avoid what happened to us. If group members aren't contributing, that's an issue 
to address in early February or March because all the work adds up in April/May and you don't have time to think 
about equality/contributions, you need to finish the project. 

Overall, I would say the letter helped, but it was sent a month late, and that part is my fault when it comes to 
the group dynamics of this project.

{% enddetails %}
{% details Original email B %}


A,
Since returning from Spring Break, we have devoted a significant amount of time and effort towards developing 
our project components. During this time, we have taken note that the amount of effort from your end has been 
below expectations, and we have concluded as a group that this needed to be addressed formally. First, we have 
taken note that you have been absent every class session other than our Midterm and Presentation date since 
returning from the break, during which we have had many discussions about what each member will focus on for the 
project, and learning relevant information in lectures that we will help us in completing the project on time.

Our group has arranged work sessions in advance for both our presentation poster and technical report, both of 
which you were not present for and made no attempt to make up the work missed in those sessions. This was apparent 
this past weekend for our deliverable 2 work session, for which you made no contribution towards editing our poster, 
writing Chapter 3 of the report, or developing any of the project components in our GitHub repository.  Along with 
this, we have received very little communication from you regarding what you have been working on or what times 
you plan on dedicating to working on the project, which has become very concerning for us as the final project due 
date approaches.

Our wish is not to blame you for the shortcomings of our group’s progress, but to inform you that we are aware of 
your lack of effort and expect much more from you for the remainder of the course. This includes attending class 
regularly, being present for future project work sessions, and clear communication regarding what you will work 
on for the project.

If you have any concerns or objections to this, then we would be happy to have a team meeting to discuss further. 
Thank you for reading and we hope to see you in class this week.

Best,

{% enddetails %}
{% details Feedback B %}

I gladly give my permission to use the team member performance letter I wrote as learning material for future 
students. I found that writing the email directly to the team member as opposed to you (the professor was BCC on 
the group  email) was the best way to address the performance issues without creating tension within the team. 
Approaching the letter this way ensured that the team member understood the seriousness of the situation, while 
also not feeling blamed or denounced by the team. The purpose of the letter was to motivate the team member to 
be more active in the project and not to “throw them under the bus”, and I believe that this method successfully 
conveyed that message.
I am happy to say that after the letter was sent to the team member, they were very professional in apologizing 
for their shortcomings while also working very hard for the remainder of the course to be present in class and 
make notable progress in their assigned project tasks. The group member also was present for all the remaining 
work sessions we organized for the project, and we were quickly able to move forward from any dynamic tension 
and focus on meeting our project goals. Overall, writing the letter in this manner provided the outcome my team 
was looking for when we decided to address the situation, and I would highly recommend that future students 
approach performance issues like this in a similar way. 

{% enddetails %}
## Client meeting.

{% details Meetings %}

- High-bandwidth, high-visibility synchronous communication
- Expensive in terms of person-hours

{% enddetails %}
{% details What to do %}

- Have an agenda
- Circulate agenda + docs ahead of time
- Record action items
- Review previous action items
- Spin off detailed discussions if not relevant to all or not prepared for
- Avoid status reports
- Beware slides

{% enddetails %}
{% details Communicating with client %}

- Respect client's time
    - Unless client requests chat-like communications, try to batch questions
    - Come prepared, stick to agenda, respect end time
- Prefer synchronous meetings
    - Higher bandwidth
    - Lower error rate
- Messages should go through point-of-contact
- Meetings should include most of development team
    - No one-on-one meetings
    - Need multiple viewpoints
    - Separate moderator from recorder

{% enddetails %}
{% details Retrospectives %}

- Process improvement
- Retrospectives are regular
- Like milestones, phased development – gates for evaluation, corrective action
- Postmortems come after an incident
    - Discussed in Google reading

{% enddetails %}
{% details Breakout %}

- What makes a good team player?

{% enddetails %}
{% details Collaboration tools %}

- Make sure entire team and client are onboard if using external services
    - Remember confidentiality obligation

{% enddetails %}
{% details Peer review rubric %}

- Professionalism
    - Attendance/promptness
    - Preparation for meetings
    - Respectful interactions
- Quality of contributions
- Effective communication
    - Reports problems early
    - Communicates clearly
- Initiative
    - Contributes to brainstorming
    - Volunteers for tasks
- Healthy team dynamics
    - Raises and resolves conflicts
    - Trusts other members, helps them grow



{% enddetails %}
## Team preparation checklist

{% details Team Charter %}

- Identify Project Objective and Timeline
- Identify Goals
- Identify Team commitment (hrs/week) - [please be mindful of all the team members' time, with
{% enddetails %}
consideration of their course loads and the holidays]
    - Housekeeping rules regarding team meetings/interactions 
    - Team tools/processes preferred
    - Assignment of roles and responsibilities

{% details External kick-off with Client %}

- The next thing to do is set up a meeting with the clients. 
- Before the meeting
    - Send the kick-off email and provide team availability 
    - Send an email invite (zoom) with a high-level meeting agenda
- During the meeting
    - Consider recording the meeting (ask for permission)
    - Make sure that there is a note taker
    - Provide team introduction and meet the stakeholders
    - Understand the Project overview and scope
    - Discuss which communication channel to use
    - Discuss frequency of subsequent meetings
    - Ask clarifying questions in the meeting
    - Summarize the meeting discussion, especially action items
- After the meeting
    - Send a follow-up "Thank you" email with the meeting summary, 
    decision made, and action items. 

{% enddetails %}
{% details Introductory email 1 %}

Hi ..., 

We are writing to let you know that we’re the WCU team who will work on your project this fall. We are very excited to work on this project and to get started. We would like to schedule a Project Kickoff Meeting with you next week. If possible, we would like to schedule an hour as there is a lot to learn and discuss. Here is our availability. 

Tues. Sep. 3 – 10:00am to 11:00am or 3:30pm to 4:30pm. 
Wed. Sep. 4 – 12:00pm to 1:00pm or 1:00pm to 2:00pm.
Thurs. Sep. 5 – 12:00pm to 1:00pm or 1:00pm to 2:00pm.

Please let us know:
- The times that work for you
- Anything in specific you’d like to see on the meeting agenda
- The names and emails of your attendees

We will send a meeting agenda to you the day prior to the kickoff meeting.

Our team is:
    abc
    def
    ...

Thank you very much for the opportunity to work on this project. We’re looking forward to working with you.

Best regards, 

{% enddetails %}
{% details Introductory email 2 %}

Greetings everyone, 

On behalf of the team, I want to say we’re excited to collaborate with you this semester on the upcoming project. We would like to set up a meeting with you to introduce ourselves and discuss the project requirements and introduction.

The teams availability is as follows: 
- Friday (1/31) at 12-3pm 
- Monday (2/3) at 11-3pm or any time after 4:15pm 
- Wednesday (2/5) 2-3pm or any time after 4:15pm 

Please let us know at your earliest convenience what dates and times work for you. 

Best regards, 
















{% enddetails %}
