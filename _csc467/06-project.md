---
layout: lecture
pretty_table: true
order: 2
title: Project
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
  - name: Data Acquisition
  - name: Core Data Science Query
  - name: Code Development Task
  - name: 'PageRank: the Google formulation'
  - name: 'Hands-on: Page Rank in Spark'
  - name: Hub and Authority
  - name: 'Hands-on: HITS'
---

This project is to be completed individually.

## Data Acquisition

- The target data source of this project should be a dataset with either of the following conditions:
    - has a raw size larger than 1GB, or
    - contains at least 1,000,000 entities (graph nodes or edges)
- Example of such data sources include 
    - [Stanford's Large Network Dataset Collection](https://snap.stanford.edu/data/index.html) (varied)
    - [Google Data Traces](https://github.com/google/cluster-data/blob/master/ClusterData2011_2.md) (warning, 40GB+ compressed)
    - [Yelp Dataset](https://www.yelp.com/dataset) (3-6GB)
    - [Kaggle Datasets](https://www.kaggle.com/datasets?sizeStart=1024%2CMB) (filter for ones greater than 1024MB)

## Core Data Science Querry

- From your selected dataset, identify a core data science query that would, **in your opinion**, bring added value to the dataset. 
    - For example: From the Yelp's restaurant location dataset, one could ask which city blocks in the observerd metropolitan area has the highest 
    density of restaurants. This information would help inform tourisms or entrepreneurs looking to open new restaurant. 
- This selection process and the justification of your querry (what is the added value?) will form the core of the Introduction section of your Technical Report. 

## Code Development Task:

Develop a Python program that solve your query. The program (could include multiple files) should include the following components:

{% details Task 1: Data Engineering %}

- Carry out descriptive analysis **and** data reduction tasks over the dataset. You should be responsible to identify relevant analysis for 
your selected dataset and query. For example, if it is text data, analysis like word count, sentence count, sentiment analysis .. are relevant. 
For numerical data, statistical analysis are relevant. 
- The raw data is definitely larger that what you need. You will need to trim down and create smaller dataset and/or combine multiple data sources. 
- Write a narration describing how you implemented this task. The narration should not be as simple as *I did this, I did that ...*. 
Rather, it should include extensive justification, especially regarding data manipulation activities. Why did you select the specific implementation that you did? How did the dataset (size, attributes, quirks, etc) influence your technical choices. It should also report the outcome of your data engineering activities (e.g. decsrie the resulting intermediate dataset). This narration will make up the Data Engineering sections of your Technical Report. 

{% enddetails %}

{% details Task 2: Data Analytic %}

- Implement the necessary Spark-based code to resole your query. You should use of one or more of the techniques that we have 
covered in class this semester (HITS, frequent itemsets, similarity/LSH, clustering, recommendation system). 
- Write a narration describing how you implemented this task. The narration should not be as simple as *I did this, I did that ...*. 
Rather, it should include extensive justification, especially regarding data manipulation activities. Why did you select the specific implementation that you did? How did the dataset (size, attributes, quirks, etc) influence your technical choices. It should also describe the final outcome of your query and the non-technical insights from the added value achieved through this query. This narration will make up the Data Analytic sections of your Technical Report. 
Describe 

{% enddetails %}

## Related Work

Carry out a search on Google Scholar and identify prior work that either analyze the same datasets or solving the same query type. Write about your results using proper IEEE citation standards. This will form the Related Work section of your Technical Report. Feel free to adapt a previous known approach in your query. 

## Technical report:

The general requirements for the technical report are as follows:

- Follow the [IEEE conference proceeding standard](https://www.ieee.org/conferences/publishing/templates.html)
    - Page limit: 4
- Including at least the following sections:
    - Introduction and Motivation
        - Present the data
        - Why is this data set interesting to you
    - Related work (academic citations on previous work that used this data or similar techniques). This could be done after Descriptive Analysi and Technical Analysis sections. 
    - Data Engineering
    - Data Analytic
    - Conclusion
    - References

## Submissions requirements

- All the source codes should be included in a zipped file called **project.zip**. 
- A README file that describes the data acquistion process and running instruction for the project. 
- The final technical report **in PDF format**. 

Failure to adhere to details in this project description will result in points taken off. 