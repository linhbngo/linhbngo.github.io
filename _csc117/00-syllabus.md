---
layout: lecture
pretty_table: true
collection: csc117

title: "Syllabus"
toc:
  - name: General Information
  - name: Course Information
  - name: Learning Objectives
  - name: Prerequisites
  - name: Required Text (either print or e-book)
  - name: Evaluation Policy
  - name: Course Schedules
---


## General Information

- **Semester**: Spring 2027
- **Class Meeting Time**: TBD 
- **Meeting Location**: TBD

{% include courses/instructor_info.md %}

## Course Information

This is an approved Science General Education distributive course.

This course introduces students from all disciplines to the fundamentals of artificial intelligence (AI) by examining how ideas from natural intelligent systems such as the human brain and biological perception inspire the design of AI systems. We will explore core AI concepts including pattern recognition, image processing, language models, and decision-making, with an emphasis on practical understanding rather than technical depth. 

The students will engage in interactive, no-code labs using modern AI tools, including large language models and prompt engineering, to learn how these systems work and how to interact with them effectively. As a Science Distributive course, it emphasizes observation, data collection, analysis, and the role of theory and falsifiability in understanding AI and its potential integration into other scientific disciplines. The course also examines the ethical implications of AI, including fairness, transparency, and societal impact. There is no prerequisite for this course. 

## Learning Objectives

### Course Student Learning Outcomes (CSLO)

By the end of this course, students will be able to:

1. Apply the scientific method to evaluate artificial intelligence systems (formulate hypotheses, collect data, test, analyze, replicate).
2. Employ quantitative methods (e.g. confusion matrices, accuracy/recall, threshold trade-offs) to examine AI behavior. 
3. Explain connections between natural intelligent systems (e.g., neurons, perception) and artificial models, recognizing both inspirations and limitations. 
4. Demonstrate effective communication of AI concepts and results through written reports and oral presentations.
5. Critically evaluate AI claims by distinguishing scientific evidence from pseudoscience or unsupported assertions. 
6. Analyze ethical and societal implications of AI, including fairness, bias, safety, and human-AI collaboration. 

### Applicable Programmatic Student Learning Outcomes (PSLO):
1. Students will gain foundational literacy in AI concepts without requiring technical prerequisites, supporting broader CS program goals of exposing non-majors to computing. 
2. Students will develop evidence-based reasoning skills transferable to other scientific and quantitative disciplines. 
3. Students will practice ethical reasoning about computing technologies, aligning with CS program emphasis on computing and society. 

### Applicable General Education Student Learning Outcomes (GSLO):
1. Goal #1: Communicate effectively
    - 1a. Express oneself effectively in common college-level written forms.
    - 1c. Express oneself effectively in presentations.
    - 1d. Demonstrate comprehension of and ability to explain information and ideas accessed through reading. 
2. Goal #2: Think critically and analytically
    - 2a. Use relevant evidence gathered through accepted scholarly methods. 
    - 2b. Construct and/or analyze arguments, considering assumptions and counterarguments. 
    - 2c. Reach sound conclusions based on logical analysis of evidence.
3. SCIENCE Goal #3: Employ quantitative concepts and mathematical methods
    - 3a. Employ quantitative methods to examine a problem in the natural or physical world. 
    - 3b. Apply the basic methods and through processes of the scientific method for natural/physical science in a particular discipline. 


## Prerequisites

There is no prerequisite for this course

## Required Text (either print or e-book):

- **Co-Intelligence: Living and Working with AI** by Ethan Mollick (2024). ISBN-10: 0753560771
- **Introduction to AI Safety, Ethics, and Society** by Dan Hendrycks (2024). ISBN-10: 1032869925
    - This book has an [open source version](https://arxiv.org/pdf/2411.01042).

## Course Topics and Tentative Schedule

### Course Topics

- Virtualization
    - Process 
    - CPU scheduling
    - Memory management 
- Concurrency
    - Threads
    - Locks and condition variables
    - Semaphores and deadlocks
- Persistence
    - Input/output
    - File systems
- Real-time OS and security issues

### Tentative Schedule

## Tentative Course Outline

| Week | Topic and Readings | Lab/Activity | Assessments |
|---|---|---|---|
| **1** | **What Counts as Intelligence?**<br>- Mollick, Introduction: *Three Sleepless Nights* | In-class falsifiability exercise | Quiz 1 |
| **2** | **Brains, Neurons, and Signals**<br>- Mollick, Ch. 1: *Creating Alien Minds*<br>- *The Perceptron: A Probabilistic Model for Information Storage and Organization in the Brain*<br>- *Professor's perceptron paved the way for AI - 60 years too soon* | Neuron Simulation | Quiz 2 |
| **3** | **Machines that Learn from Patterns**<br>- Hendrycks, Ch. 2: *Artificial Intelligence Fundamentals* | TensorFlow Playground | Quiz 3 |
| **4** | **Seeing Like a Machine**<br>- Olah, C., Mordvintsev, A., & Schubert, L. (2017). *Feature Visualization*. Distill.<br>- Zeiler, M. D., & Fergus, R. (2014). *Visualizing and Understanding Convolutional Networks*. ECCV 2014. | CNN Explainer | Quiz 4 |
| **5** | **Collecting and Questioning Data**<br>- Mollick, Ch. 5: *AI as A Creative*<br>- Hendrycks, Ch. 6: *Bias and Fairness*<br>- Google Inclusive Images Challenge | Teachable Machine | Quiz 5<br>Essay 1 Assigned |
| **6** | **Living with Uncertainty**<br>- Mollick, Ch. 5: *AI as A Creative* (cont.) | Threshold adjustment on Teachable Machine outputs (analyze true positive, false positive, false negative, true negative in Excel) | Quiz 6 |
| **7** | **Talking with Machines**<br>- Mollick, Ch. 6: *AI as Co-worker*<br>- (Brief) Mollick, Ch. 3: *Four Rules for Co-Intelligence*<br>- (Revisit) Mollick, Ch. 1: *Creating Alien Minds* | Google ngrams | Quiz 7<br>Essay 1 Due |
| **8** | **From Chatbots to Storytellers**<br>- Mollick, Ch. 5: *AI as A Creative* (cont.)<br>- Google: *Attention is All You Need* | Transformer Explainer | Quiz 8 |
| **9** | **Prompt Crafting 101**<br>- Mollick, Ch. 3: *Four Rules of Co-Intelligence*<br>- Hendrycks, Ch. 6: Bias/Fairness | OpenAI Playground | Quiz 9<br>Essay 2 Assigned |
| **10** | **Teaching AI to Follow Your Lead**<br>- Mollick, Ch. 6,7,8: *AI as A ...* | Claude AI | Quiz 10 |
| **11** | **When Humans and AI Work Together**<br>- *Towards an AI co-scientist*<br>- *Advancising AI-Scientist Understanding: Making LLM Think Like a Physicist with Interpretable Reasoning* | Human versus AI labeling in Google Sheets (inter-rater reliability) | Quiz 11<br>Essay 2 Due |
| **12** | **AI in Our Lives**<br>- Mollick, Ch. 8: *AI as Our Future*<br>- (Revisit) Mollick, Ch. 5, 6, 7. | Small-group case study debate prep | Quiz 12 |
| **13** | **Can AI Fail Safely**<br>- Hendrycks, Ch. 3: *Single-Agent Safety*<br>- Hendrycks, Ch. 4: *Safety Engineering* | Inducting an AI Hallucination | Quiz 13 |
| **14** | **What’s Next for AI?**<br>- Mollick, Ch. 8: *AI As Our Future*<br>- Hendrycks, Ch. 7: *Collective Action Problems* | Demo of small LLM on personal computers | Quiz 14 |
| **15** | **Debate and Reflection**<br>- Mollick, Epilogue<br>- Hendrycks, Ch. 8: *Governance* | In-class group debate/presentation (continue into Final Exam time) | Quiz 15<br>Group Position Paper Due |

*Quizzes are typically disseminated once a week.*

## Evaluation Policy:

### Method of Assessment

| Assessment                        | % of Final Grade | 
| --------------------------------- | ---------------- | 
| Essays                            | 20%              |
| Lab                               | 40%              |
| Quizzes                           | 20%              |
| Group Debates and Position Paper  | 20%              |


### Assessing Student Learning Outcomes:
1. In-class weekly quizzes (20%)
    - Purpose: Ensure reading comprehension and reinforce weekly concepts
    - Mapped Outcomes:
        - CSLO: 4, 5
        - GSLO: 1d
2.	Labs (5 labs total, 8% each: 40%)
    - Students submit short reports (hypothesis, data/graph, reflection) from selected labs.
    - Week 3: TensorFlow Playground (Decision Boundaries)
        - CSLO: 1, 2, 3
        - GSLO: 3a, 3b, 2c.
    - Week 5: Teachable Machine (Classifier and Bias)
        - CSLO: 1, 2, 5
        - GSLO: 3a, 3b, 2a.
    - Week 6: Threshold and ROC (Receiver Operating Characteristics) 
        - CSLO: 1, 2
        - GSLO: 3a, 2c
    - Week 7: Text Prediction (N-grams)
        - CSLO: 3, 4
        - GSLO: 1d, 2a
    - Week 10: Persona Prompt Engineering
        - CSLO: 4, 6
        - GSLO: 1a, 1c, 2b
3.	Essays (2 essays, 10% each: 20%)
    - Structured essays (3-4 pages) evaluating AI in applied domains (e.g., health, environment, education).
    - Mapped Outcomes:
        - CSLO: 4, 5, 6
        - GSLO: 1a, 1d, 2a, 2b, 2c. 
4.	Group Debate and Position Paper (20%)
    - Small groups take a position on a societal AI issue, present in a short in-class debate (5-10 min) and submit a 3-4 page position paper. 
    - Mapped Outcomes:
        - CSLO: 4, 5, 6
        - GSLO: 1a, 1c, 2a, 2b, 2c. 

### Grade Scale:

<table
  data-toggle="table"
  data-url="{{ '/assets/json/grade_undergrad.json' | relative_url }}">
  <thead>
    <tr>
      <th data-field="grade">Grade</th>
      <th data-field="gpa">Quality Points</th>
      <th data-field="numeric">Numeric</th>
      <th data-field="interpretation">Interpretation</th>
    </tr>
  </thead>
</table>

Refer to the [Grading Information section](https://catalog.wcupa.edu/undergraduate/academic-policies-procedures/grading-information/) 
section of the Undergraduate Catalog for description  of NG (No Grade), 
W, Z, and other grades. 

### Lateness Policy:
Assignments that are late are assessed a 10% per day late penalty.
Saturday and Sunday are each days.

{% include courses/policy.md %}

