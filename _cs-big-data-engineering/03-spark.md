---
layout: lecture
pretty_table: true
order: 4
title: Spark Computing Environment
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
  - name: Data Intensive Approach
  - name: Data Mining
  - name: Meaningfulness of Analytic Answers
  - name: Things Useful to Know
  
---

# Spark Computing Environment

## 1. What is Spark?

### 1.1. Overview and design philosophy

- A unified compute engine and a set of libraries for parallel
data processing on computer clusters. 
    - `Unified`: Spark supports a wide range of data analytic tasks over the same 
    computing engine and a consistent set of APIs. 
    - `Computing engine`: Spark handles loading data from storage systems and 
    perform computation on the data (in memory) rather than on permanent storage. 
    To adhere to the data locality principle, Spark relies on APIs to provide a 
    transparent common interface with different storage systems for all applications. 
    - `Libraries`: Via its APIs, Spark supports a wide array of internal and 
    external libraries for complex data analytic tasks. 


![Spark Computing Environment](fig/03-spark/spark_env.png)

### 1.2. A brief history of Spark

- Research project at UC Berkeley AMP Lab in 2009 to address drawbacks of 
Hadoop MapReduce. 
- Paper published in 2010: [Spark: Cluster Computing with Working Sets](files/Zaharia.pdf) 
- Source code is contributed to Apache in 2013. The project had more than 100 
contributors from more than 30 organizations outside UC Berkeley. 
- Version 1.0 was released in 2014. 
- Currently, Spark is being used extensively in academic and industry 
(NASA, CERN, Uber, Netflix …). 

### 1.3. A workflow system

- A more advanced workflow system
- Efficient way to cope with failures
- Efficient way of group tasks among computing nodes and scheduling
execution of tasks
- Integration of programming language features and libraries

### 1.4. RDD: Resilient distributed dataset

- Immutable file of objects of one type (e.g., files of key-value pairs)
- `Distributed`: An RDD is broken into chunks and stored on different 
compute nodes.
- `Resilient`: Spark is able to recovered from the loss of any of all chunks 
of an RDD. 

### 1.5. Spark applications

- Typically consists of a `driver` process and a set of `executor` processes. 
- The `driver` runs the main function and is responsible for: 
    - maintaining information about the Spark application,
    - responding to a user's program or input, and
    - analyzing, distributing, and scheduling work across the executors. 
    - Non-Spark codes are also managed by the `driver`
- The `executors` carry out the actual work assigned to them by the `driver`. 
`Executors` are deployed on Spark cluster, on top of the compute nodes. 
    - Data in spark are managed as `distributed collection`: when running 
    on a cluster, parts of the data are distributed across different machines 
    and are manipulated by different executors. 
    - To allow executor to perform work in parallel breaks up data into 
    chunks called `partitions`. 

![Spark application architecture](fig/03-spark/driver_executor.png)

- Spark also has a local mode (what we are using for this class), where driver 
and executors are simply processes on the same machine. 
- Spark application developed in local mode can be carried over almost `as-is` 
to run in cluster mode (one of the attractiveness of Spark).
- Spark supports the following language APIs: Scala, Java, Python, SQL 
(ANSI SQL 2003 standard), and R.

--- 

## 2. Programming for Spark Computing Environment

### 2.1. Overview

- Operations applied on RDDs:
    - 'transformations': applying some functions on an RDD to create another RDD
        - In Spark, the core data structures are `immutable`, meaning 
        they cannot be changed after creation. 
        - To `change` a data collection means to `create` a new data 
        collection that is a `transformation` from the old one. 
        - There are two types of transformation:
            - Narrow dependencies (1-to-1 transformation). 
            - Wide dependencies (1-to-N transformation). 
    - 'actions': storing RDDs to a file system or creating a result that is 
    made available to the Spark application on the `driver` process. There 
    are three kind of actions:
        - Actions to view data in the console (e.g., `take`). 
        - Action to collect data to native objects (e.g., `collect`).
        - Action to write to output data sources (e.g., `saveAsTextFile`). 
- Lazy evaluation:   
    - `Transformations`are logical plan only. 
    - Spark will wait until the very last moment to execute the graph 
    of computation instructions (the logical plan).
    - To trigger the computation, we run an `action`. 

- Detailed syntax can be found via [Spark Python API](https://spark.apache.org/docs/latest/api/python/reference/pyspark.html)

### 2.2. Common Spark transformations
- `map`: Return a new distributed dataset formed by passing each element of the source 
through a function.
- `filter`:	Return a new dataset formed by selecting those elements of the source 
on which a condition returns true. This condition can be either a statement or a function. 
- `flatMap`: Similar to map, but the output items are brokened down into individual elements 
before aggregated into an output. 
- `sample`: Sample a fraction fraction of the data, with or without replacement, using a 
given random number generator seed.
- `union`: Return a new dataset that contains the union of the elements in the source 
dataset and the argument.
- `intersection`: Return a new RDD that contains the intersection of elements in the 
source dataset and the argument.
- `distinct`: Return a new dataset that contains the distinct elements of the 
source dataset.
- `groupByKey`: When called on a dataset of (K, V) pairs, returns a dataset of 
(K, Iterable<V>) pairs.
- `reduceByKey`: When called on a dataset of (K, V) pairs, returns a dataset of (K, V) pairs 
where the values for each key are aggregated using the given reduce function, which must be of type (V,V) => V. 
- `aggregateByKey`: When called on a dataset of (K, V) pairs, returns a dataset 
of (K, U) pairs where the values for each key are aggregated using the given combine 
functions and a neutral "zero" value. 
- `sortByKey`: When called on a dataset of (K, V) pairs where K implements Ordered, 
returns a dataset of (K, V) pairs sorted by keys in ascending or descending order, as 
specified in the boolean ascending argument.
- `join`:	When called on datasets of type (K, V) and (K, W), returns a dataset 
of (K, (V, W)) pairs with all pairs of elements for each key. Outer joins are 
supported through leftOuterJoin, rightOuterJoin, and fullOuterJoin.
- `pipe`:	Pipe each partition of the RDD through a shell command, e.g. a Perl or 
bash script. RDD elements are written to the process's stdin and lines output to its stdout are returned as an RDD of strings.

### 2.3. Common Spark actions
- `reduce`: Aggregate the elements of the dataset using a function func (which takes 
two arguments and returns one). The function should be commutative and associative 
so that it can be computed correctly in parallel.
- `collect`: Return all the elements of the dataset as an array at the driver program. 
This is usually useful after a filter or other operation that returns a sufficiently 
small subset of the data.
- `count`: Return the number of elements in the dataset.
- `first`: Return the first element of the dataset (similar to take(1)).
- `take`: Return an array with the first n elements of the dataset.
- `takeSample`:	Return an array with a random sample of num elements of the dataset, 
with or without replacement, optionally pre-specifying a random number generator seed.
- `takeOrdered`: Return the first n elements of the RDD using either their natural 
order or a custom comparator.
- `saveAsTextFile`:	Write the elements of the dataset as a text file (or set of 
text files) in a given directory in the local filesystem, HDFS or any other 
Hadoop-supported file system. Spark will call toString on each element to convert it 
to a line of text in the file.

## 3. Hands-on: Word Count in Spark

### 3.1. Preparation


- Clone repository

```bash
git clone https://github.com/ngo-classes/big-data-engineering.git
```
- Setup 

![](fig/03-spark/spark_1.png)

### 3.2. Getting data

- Depending on whether you are on Google Colab, Kaggle, or local device, the download location 
of the files will differ. 
- Direct download link: https://drive.google.com/uc?export=download&id=1oKnG6y2mkKcaPSZEJM9ZjQ7UXo4SzP7I

```python
!wget -O 100-0.txt --no-check-certificate 'https://drive.google.com/uc?export=download&id=1oKnG6y2mkKcaPSZEJM9ZjQ7UXo4SzP7I'
```
![](fig/03-spark/getting_data.png)

### 3.3. Running WordCount

- Enter the following Python code. This should be the same code as from the init notebook. 
- Pay attention to `input_path` and `output_path` variables. They are used to 
provide a path to the location of the input file, and the directory containing the output files. 

```python
input_path="100-0.txt"
output_path="output-wordcount-01"
textFile = sc.textFile(input_path)
wordcount = textFile.flatMap(lambda line: line.split(" ")) \
    .map(lambda word: (word, 1)) \
    .reduceByKey(lambda a, b: a + b)
wordcount.saveAsTextFile(output_path)
```
- A successful run will generate the resulting output 
directory that contain `_SUCCESS` flag file (size 0). 

![](fig/03-spark/wordcount_output.png)



### 3.4. Word Count workflow breakdown

- Let's breakdown the WordCount Python statements by running them 
in individual cells. 
- First, let's review the content of the `input_path` variable. 
    - The `textFile` variable only points to the *address inside the Spark cluster 
    that will hold the RDD*
    - Only by performing `take`, an action, then we can get the actual content. 

```python
print(input_path)
```

```python
textFile.take(5)
```
![](fig/03-spark/spark_data.png)

- Each line of the text file is considered an element in your RDD. 
- To highlight the difference between `map` and `flatMap`, we can 
try the following block of codes to observe the results:
    - Observe how each `line` inside the lambda function corresponds to 
    a line in the original text file. 
    - Observe how `tmp` is a list of lists, while `tmp2` is only a 
    list. In other words, `flatMap` breaks lines into lists of words, and 
    concatenate these lists into a single new RDD. 

```python
tmp = textFile.map(lambda line: line.split(" "))
print(tmp.take(5))
tmp2 = textFile.flatMap(lambda line: line.split(" "))
print(tmp2.take(5))
```

- In the next block of codes, we first repeat the `flatMap` operation, then 
use the resulting RDD (`step2`). Next, we use `map` to apply an operation that 
create a key-value pair, with the key is the word and the value is 1. 

```python
step1 = textFile.flatMap(lambda line: line.split(" "))
print(step1.take(5))
step2 = step1.map(lambda word: (word, 1))
print(step2.take(5))
```

- All pairs with the same key are `reduced` together using pairwise 
summation to get the final count of each key. 

```python
step3 = step2.reduceByKey(lambda a, b: a + b)
step3.take(10)
```

![](fig/03-spark/spark_wordcount.png)

- Try to save the RDD file in the output path  is going to create 
an error: `org.apache.hadoop.mapred.FileAlreadyExistsException`. 

```python
step3.saveAsTextFile(output_path)
```

![](fig/03-spark/spark_output_error.png)

```python
output_path="output-wordcount-02"
step3.saveAsTextFile(output_path)
```

![](fig/03-spark/spark_output_correct.png)

### 3.5. Data distribution in Spark

- Run the following code in a new cell

```python
textFile.getNumPartitions()
```

![](fig/03-spark/spark_nums.png)

- We can make a copy of our `textFile` that is distributed across more 
partitions. Run the following code in a cell on `spark-1`

```python
textFile_2 = textFile.repartition(4)
textFile_2.getNumPartitions()
```

- Rerunning the WordCount codes and observe the output directory
    - There are now four resulting output files

```python
output_path="output-wordcount-03"
wordcount = textFile_2.flatMap(lambda line: line.split(" ")) \
            .map(lambda word: (word, 1)) \
            .reduceByKey(lambda a, b: a + b)
wordcount.saveAsTextFile(output_path)
```

![](fig/03-spark/spark_partitions.png)

---

## 3. Challenges

### 3.1. Challenge 1:

- Augment the mapping process of WordCount with a function to filter out
punctuations and capitalization from the unique words
- Hint: The string module is helpful for removing punctuation.

### 3.2. Challenge 2:

- Look up the [Spark Python API for filter](https://spark.apache.org/docs/latest/api/python/pyspark.html?highlight=filter#pyspark.RDD.filter).
- Augment the results from Challenge 1 to remove the empty spaces (`''`).


