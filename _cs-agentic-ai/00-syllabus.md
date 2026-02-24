---
layout: lecture
pretty_table: true
order: 3
title: Syllabus
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


# Optionally, you can add a table of contents to your post.
# NOTES:
#   - make sure that TOC names match the actual section names
#     for hyperlinks within the post to work correctly.
#   - we may want to automate TOC generation in the future using
#     jekyll-toc plugin (https://github.com/toshimaru/jekyll-toc).
toc:
  - name: Course Description
    # if a section has subsections, you can add them as follows:
    # subsections:
    #   - name: Example Child Subsection 1
    #   - name: Example Child Subsection 2
  - name: Learning Objectives
  - name: Required Materials
  - name: Assessments and Grading
  - name: Course Topics and Schedules
  
# Below is an example of injecting additional post-specific styles.
# If you use this post as a template, delete this _styles block.
_styles: >
  .fake-img {
    background: #bbb;
    border: 1px solid rgba(0, 0, 0, 0.1);
    box-shadow: 0 0px 4px rgba(0, 0, 0, 0.1);
    margin-bottom: 12px;
  }
  .fake-img p {
    font-family: monospace;
    color: white;
    text-align: left;
    margin: 12px 0;
    text-align: center;
    font-size: 16px;
  }
---

# Agentic Artificial Intelligence: Design, Implementation, and Orchestration

## Course Description

This course explores the emerging paradigm of Agentic Artificial Intelligence: AI 
systems capable of reasoning, planning, and acting autonomously through structured 
protocols and external tool integration. Students will learn to design, implement, 
and deploy Model-Context-Protocol (MCP)-based agent systems, integrate multiple models 
and APIs, and evaluate their ethical, cognitive, and computational implications.

The course emphasizes applied construction and reflective practice over rote theory. 
Students will build containerized agent workflows, practice context and protocol design, 
and engage in iterative *fail-and-survive* learning cycles to develop robust technical 
and critical thinking skills.

## Learning Objectives

### Course Student Learning Outcomes (CSLO)

1. Explain the principles of rational and cognitive agents.	
2. Implement autonomous behaviors using Model-Context-Protocol design.	
3. Compose multi-agent systems that integrate APIs and external tools.	
4. Deploy and evaluate agent systems in reproducible computing environments.	
5. Communicate design choices and ethical reasoning clearly.
  
## Required Learning Materials:

There is no textbook requirement for this course. Relevant reading materials will be uploaded to LMS. 

## Assessments and Grading:

### Method of Evaluation

| Assessment          | % of Final Grade  | CSLO      | 
| ------------------- | ----------------- | --------- | 
| Reading Reflection  |       30%         | 1,5       | 
| Labs                |       10%         | 1,2,3,4,5 | 
| Midterm Exam        |       20%         | 1,2,3,5   | 
| Final Project       |       40%         | 1,2,3,4,5 | 

### Grade Scale:

<table
  data-toggle="table"
  data-url="{{ '/assets/json/grade_grad.json' | relative_url }}">
  <thead>
    <tr>
      <th data-field="grade">Grade</th>
      <th data-field="gpa">Quality Points</th>
      <th data-field="numeric">Numeric</th>
      <th data-field="interpretation">Interpretation</th>
    </tr>
  </thead>
</table>

D grades are not used. Refer to the Graduate Catalog for description of NG (No Grade), W, & other grades.

### Assessments:

- Reading Reflections: Students critically synthesize foundational readings. This assesses conceptual understanding and their ability to communicate ideas clearly.
- Weekly Labs: Students prototype, fail, analyze, and rebuild various frameworks in each lab. 
- Midterm Exam: Evaluates conceptual reasoning and short design analysis questions. 
- Final Project: A larger project that comprehensively assesses students' 
understanding of the course materials. 

### Lateness Policy:

Labs/Project milestones that are late are assessed a 10% per day late penalty. 
Saturday and Sunday are each days.

## Course Topics and Schedules

| Week | Topic                                       | 
| ---- | ------------------------------------------- | 
|  1   | From Symbolic AI to Agentic AI              | 
|  2   | Rational Agent and Environments             | 
|  3   | Cognitive Architectures and LLM Integration | 
|  4   | From Prompting to Protocols                 | 
|  5   | Context Engineering                         | 
|  6   | The Protocol Layer                          | 
|  7   | Multi-Agent Design Patterns                 | 
|  8   | Communication and Coordination              | 
|  9   | Model Selection and Hybrid Intelligence     | 
| 10   | Agent Infrastructure and Deployment         | 
| 11   | Agent Evaluation and Benchmarking           | 
| 12   | Applications of Agentic AI                  | 
| 13   | Safety, Ethics, and Human Oversight         | 
| 14   | Final Project Development Update            | 
| 15   | Final Project Reflection                    | 


