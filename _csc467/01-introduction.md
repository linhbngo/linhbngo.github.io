---
layout: lecture
pretty_table: true
order: 2
title: Introduction
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
  - name: Big Data Problems
  - name: Big Data in Science
  - name: Big Data in Industry
  - name: The Vs of Big Data
  - name: Programming Paradigm for Big Data
  - name: Data Mining
  - name: Meaningfulness of Analytic Answers
  - name: Things Useful to Know
  - name: Setup Computing Environment
---
## Big Data Problems

- Not only the processing power, but the size of the data is also the 
limiting factor in being able to find a timely solution.
- Input data carry characteristics of Big Data (the Vs)​.
- Input data may or may not be big data​ but computational process produces massive and complex 
intermediate data that needs to be analyzed during the process.

## Big Data in Science

{% details The four pillars of scientific process %}

- Thousands of years ago, science was **empirical**. 
    - describing natural phenomena
- In the last few hundred years, the **theoretical** branch is developed. 
    - models, generalizations
- In the last few decades, we have the **computational** branch
    - Simulation of complex phenomena
- Today, we  have added the **data-enabled/data-intensive** pillar
    - synthesizing of theory, experiment, and computation with statistics 

{% enddetails %}

{% details Big data analytics in science and engineering %}

For datasets that are:
    - Too big
    - Too complex
    - Too fast (streaming)
    - Too noisy
    - Too heterogeneous

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/01-intro/big_analytics.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="25%" zoomable=true %}

{% enddetails %}

## Big Data in Industry

{% details 2010-2020 %}

- In 2008-2009:​
    - Google processed 20PB a day.
    - Facebook had 2.5PB of user data + 15TB/day​.
    - eBay had 6.5PB of user data + 50TB/day​.
- In 2010-2011:​
    - Facebook had 400M users / 125PB of user data​.
    - eBay had 10PB of user data in 2010, expected to double this number in 2011​
- In 2012-2013:​
    - Facebook had 900M users​
    - Twitter had 400M Tweets/day
- [53% of companies are using big data analytics today](https://www.forbes.com/sites/louiscolumbus/2017/12/24/53-of-companies-are-adopting-big-data-analytics/?sh=6c6c70cb39a1)
    - Data warehouse optimization, customer/social analysis, predictive maintenance, clickstream 
    analytics, fraud detectiton, and Internet of Things. 
    - Spark, MapReduce, and Yarn are among the most popular framework. 
- [Medicine, Retail, Construction, Banking, and Transportation are the new industries that are being defined by big data analytic capabilities](https://towardsdatascience.com/5-industries-becoming-defined-by-big-data-and-analytics-e3e8cc0c0cf)

{% enddetails %}


{% details Post 2020 %}

- IDC-scale (Internet Data Center) forecasts show annual data created/replicated growing from 72 ZB (2020) to 394 ZB (projected for 2028).
    - [Seagate Report](https://s24.q4cdn.com/101481333/files/doc_downloads/2025/05/v3/Analyst-Day-2025.pdf)
- Cloud object storage is now “hundreds of exabytes”
    - AWS reported ([Pi Day 2024](https://aws.amazon.com/blogs/aws/aws-pi-day-2024-use-your-data-to-power-generative-ai/?utm_source=chatgpt.com)) Amazon S3 
    stores 350+ trillion objects and exabytes of data, averaging 100+ million requests/second.
    - By [re:Invent 2025](https://www.aboutamazon.com/news/aws/aws-re-invent-2025-ai-news-updates?utm_source=chatgpt.com), AWS stated S3 stores 500+ trillion objects 
    and hundreds of exabytes, and is raising max single-object size from 5 TB to 50 TB.
- **Exabyte-scale** is an everyday adjective inside big tech
    - Meta describes its exabyte-scale data warehouse and notes stream processing that transports [multiple petabytes per hour](https://engineering.fb.com/2025/07/23/security/policy-zones-meta-purpose-limitation-batch-processing-systems/?utm_source=chatgpt.com).

{% enddetails %}


## The Vs of Big Data

{% details Initial Vs %}

- Volume: the size of the files used to archive and spread data.
- Velocity: the speed with which data is generated and processed.
- Variety: formats and purposes of data, which may include objects as different as 
samples of animal tissue, free-text observations, humidity measurements, GPS coordinates, 
and the results of blood tests.
- Veracity: the extent to which the quality and reliability of big data can be guaranteed. 
Data with high volume, velocity and variety are at significant risk of containing  
inaccuracies, errors and unaccounted-for bias.

{% enddetails %}


{% details Other Vs %}

- Validity: the selection of appropriate data with respect to the intended use. The choice 
of a specific dataset as evidence base requires adequate and explicit justification, 
including recourse to relevant background knowledge to ground the identification of what counts 
as data in that context.
- Volatility: the extent to which data can be relied upon to remain available, accessible and 
re-interpretable despite changes in archival technologies. This is significant given the tendency 
of formats and tools used to generate and analyze data to become obsolete, and the efforts 
required to update data infrastructures so as to guarantee data access in the long term.
- Value: the multifaceted forms of significance attributed to big data by different sections 
of society, which depend as much on the intended use of the data as on historical, social and 
geographical circumstances.

{% enddetails %}

People don't really talk about the Vs that much any more, but it helps to characterize the nature of 
your data. 

## Programming Paradigm for Big Data

{% details Challenges %}

- Require not only parallel computation but also parallel data processing​.
- New computational tools and strategies​.
- New data intensive scalable architectures​.
- Science is moving increasingly from hypothesis-driven to data-driven discoveries​.
- Industry is at a stage where big data infrastructures are integrated and big data sets 
are beginning to be analyzed to produce business insights.
- Example general paradigm:

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/01-intro/data_parallel_programming.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="25%" zoomable=true alt="data parallel programming"%}

{% enddetails %}

{% details Example of Difficulties %}

- It is difficult to write parallel programs​
    - Difficult in converting algorithms from serial to parallel​.
    - Difficult in identifying different ways that the program can fail​.
    - No reliable way to detect failure of a process​.
- It is even more difficult to write parallel programs at large scale​
    - Same set of errors, but scale up with size​.
- It is even more difficult to debug large scale parallel programs​
    - What if the program doesn’t fail but only produce incorrect results?

{% enddetails %}

{% details Design Principles of Data-Intensive Computing %}

- Scale "out", not "up"​
    - It is easier and cheaper to add nodes to an existing cluster than to build a faster cluster.​
- Move computation to the data​
    - Reduce data movement.​
- Sequential processing, avoid random access​
    - Reduce seek movement on disks.​
- Seamless scalability

{% enddetails %}

## Data Mining

- To extract the knowledge data needs to be
    - Stored 
    - Managed
    - And ANALYZED
    - Data Mining ≈ Big Data ≈ Predictive Analytics ≈ Data Science/Engineering
- Given **lots of data**, discover patterns and models that are:
    - Valid:  hold on new data with some certainty
    - Useful:  should be possible to act on the item 
    - Unexpected:  non-obvious to the system
    - Understandable: humans should be able to interpret the pattern
- Modeling
    - Statistical modeling
    - Machine Learning
- Computational approaches to modeling
    - Summarizing the data (PageRank)
    - Extracting the relevant features of the data (Frequent Itemsets or Similar Items)

## Meaningfulness of Analytic Answers

- Bonferroni's principle
    - Meaningless statistical limit can cause analysts can 
    `discover` patterns that are meaningless
    - Statisticians call it Bonferroni’s principle: Roughly, if you look in more 
    places for interesting patterns than your amount of data will support, you are 
    bound to find crap.

{% details Example of Bonferroni's principle %}

- We want to find (unrelated) people who at least twice have stayed 
at the same hotel on the same day
    - $10^9$ people being tracked
    - $10^5$ hotels
    - Each person stays in a hotel 1% of time (p = 0.01)
    - Hotels hold 100 people 
    - 1,000 days
    - `Suspicious activity`: Two random people, on two different days, 
    are both at the same hotel. 
    - If everyone behaves randomly (i.e., no terrorists) will the data mining detect 
    anything suspicious?
    - Expected number of `suspicious` pairs of people:
        - Probability of two people visit a hotel on any given day: $0.01\times0.01=0.0001$
        - The probability that each person select a specific hotel: $0.0001/10^5=10^{-9}$
        - The probability that **both* select the same specific hotel: $10^{-9}\times10^{-9}=10^{-18}$  
    - `Suspicious activity to be monitored`: number of pairs of people ($5\times10^17$) 
    multiplied by the number of pairs of days ($5\times10^5$) multiplied by the probability that 
    **both** select the same hotel on the same date: 250,000
    - Too many to observe ...

{% enddetails %}

## Things Useful to Know

{% details TF.IDF %}
TF.IDF are measures of word importance
- Measure how concentrated into relatively few documents are the occurrences of a given word.
- Suppose we have a collection of $N$ documents. 
- $f_{ij}$ to be the frequency (number of occurrences) of term (word) i in document j. 
- The term frequency (TF): 

$
TF_{ij}=\frac{f_{ij}}{max_{k}f_{kj}}
$

- The inverse document frequency (IDF) with term i appears in $n_i$ of the N documents. 

$
IDF_i=log_2(N/n_i)
$

- The TF.IDF score for term is 

$
TF_{ij}\times IDF_i
$

- The terms with the highest TF.IDF score are often the terms that best characterize the topic of the document.

{% enddetails %}

{% details Hash functions %}
- Given $B$ buckets, 
- A hash function uses a data value to produce a bucket number $b$ that is in the range of 0 to $B-1$
{% enddetails %}

{% details Indices %}
- Index
    - Similar to pointer ...
    - Given an index value, we can access all data related to that 
    index without scanning through the entire collection. 
- Index can be built from hash table
{% enddetails %}

{% details Secondary storage and memory hierarchy impact %}
- Cache/memory/disk/network
- Performance differences can be in multiple orders of magnitude
- Understand data placement on secondary storage is important
{% enddetails %}

## Setup Computing Environment

We will set up a local computing environment for this class that supports Spark and other big 
data engineering/analytics tools. The steps to set up are as follows. 

This setup instruction uses Anaconda to create virtual environment. If you are comfortable with 
virtual environments in Python, feel free to adapt the `environment.yml` file into a `requirements.txt`

If you don't already have one, [download and install Anaconda](https://www.anaconda.com/download/success?reg=skipped) for your computing device. 

Carry out [the setup instructions for your specific platfoms in the README.md](https://github.com/ngo-classes/big-data-engineering/blob/main/README.md).

Going forward, you are to run the `conda activate pyspark-3.5.1` command prior to carrying out coding tasks for the class. 
