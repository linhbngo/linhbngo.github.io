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
  - name: What is Spark?
  - name: Programming for Spark Computing Environment
  - name: Word Count in Spark
---

{% details tip Lecture notebook %}

This is the link to this lecture's [Colab notebook](https://colab.research.google.com/drive/1fLyCM1eW1pG45KnGWS2Tab1KYtniijHa?usp=sharing)

{% enddetails %}

## What is Spark?

{% details Design philosophy %}

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


{% include figure.liquid loading="eager" path="assets/img/courses/big-data-engr/03-spark/spark_env.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true alt="Spark Computing Environment" %}

{% enddetails %}

{% details info A brief history of Spark %}

- Research project at UC Berkeley AMP Lab in 2009 to address drawbacks of 
Hadoop MapReduce. 
- Paper published in 2010: [Spark: Cluster Computing with Working Sets](https://www.usenix.org/legacy/event/hotcloud10/tech/full_papers/Zaharia.pdf) 
- Source code is contributed to Apache in 2013. The project had more than 100 
contributors from more than 30 organizations outside UC Berkeley. 
- Version 1.0 was released in 2014. 
- Currently, Spark is being used extensively in academic and industry 
(NASA, CERN, Uber, Netflix …). 

{% enddetails %}

{% details tip A workflow system %}

- A more advanced workflow system
    - Efficient way to cope with failures
    - Efficient way of group tasks among computing nodes and scheduling
execution of tasks
- Integration of programming language features and libraries

{% enddetails %}

{% details RDD: Resilient distributed dataset %}

- Immutable file of objects of one type (e.g., files of key-value pairs)
- `Distributed`: An RDD is broken into chunks and stored on different 
compute nodes.
- `Resilient`: Spark is able to recovered from the loss of any of all chunks 
of an RDD. 

{% enddetails %}

{% details Spark applications %}

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

{% include figure.liquid loading="eager" path="assets/img/courses/big-data-engr/03-spark/driver_executor.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true alt="Spark application architecture" %}

- Spark also has a local mode, where driver 
and executors are simply processes on the same machine. 
- Spark application developed in local mode can be carried over almost `as-is` 
to run in cluster mode (one of the attractiveness of Spark).
- Spark supports the following language APIs: Scala, Java, Python, SQL 
(ANSI SQL 2003 standard), and R.

{% enddetails %}

## Programming for Spark Computing Environment

Programming operations applied on RDDs:

{% details note Transformations %}

- Applying some functions on an RDD to create another RDD
- In Spark, the core data structures are `immutable`, meaning they cannot be changed after creation. 
    - To `change` a data collection means to `create` a new data 
    collection that is a `transformation` from the old one. 
- There are two types of transformation:
    - Narrow dependencies (1-to-1 transformation). 
    - Wide dependencies (1-to-N transformation). 

{% enddetails %}

{% details note Actions %}

- Storing RDDs to a file system or creating a result that is made available to the Spark application on the `driver` process. 
- There are three kind of actions:
    - Actions to view data in the console (e.g., `take`). 
    - Action to collect data to native objects (e.g., `collect`).
    - Action to write to output data sources (e.g., `saveAsTextFile`). 

{% enddetails %}


{% details note Lazy Evaluation %}   

- `Transformations`are logical plan only. 
    - Spark will wait until the very last moment to execute the graph of computation instructions (the logical plan).
- To trigger the computation, we run an `action`. 
- Detailed syntax can be found via [Spark Python API](https://spark.apache.org/docs/latest/api/python/reference/pyspark.html)

{% enddetails %}

{% details tip Common Spark Transformations %}
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

{% enddetails %}

{% details tip Common Spark actions %}
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

{% enddetails %}

## Word Count in Spark

Let's revisit the WordCount example from the inititial setup in [Introduction]({{ '/big-data-engr/01-introduction/' | relative_url }}#setup-computing-environment). 


{% details Running WordCount %}

This is the source code for the cell running Word Count

```python
# Input and output paths
input_path = "100-0.txt"
output_path = "output-wordcount-01"

# If output path exists, then delete the output directory first
import shutil
if os.path.exists(output_path):
    shutil.rmtree(output_path)

# The logic remains the same.
# We use the SparkContext's textFile method, which is the same as the old sc.textFile
textFile = sc.textFile(input_path)

# Perform the word count
wordcount = textFile.flatMap(lambda line: line.split(" ")) \
    .map(lambda word: (word, 1)) \
    .reduceByKey(lambda a, b: a + b)

# Save the results
wordcount.saveAsTextFile(output_path)

```

- Pay attention to `input_path` and `output_path` variables. They are used to 
provide a path to the location of the input file, and the directory containing the output files. 
- A successful run will generate the resulting output directory that contain `_SUCCESS` flag file (size 0). 
    - There will be several `*.crc` files, these are the check files to confirm data validity. 
    - The output of the word counting process is stored in two files: `part-00000` and `part-00001`. 

{% include figure.liquid loading="eager" path="assets/img/courses/big-data-engr/03-spark/wordcount_output_dir.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

{% enddetails %}

{% details Word Count workflow breakdown %}

- Let's breakdown the WordCount Python statements by save each stage individually. 

```python
# Input and output paths
input_path = "100-0.txt"
output_path = "output-wordcount-02"

# If output path exists, then delete the output directory first
import shutil
if os.path.exists(output_path):
    shutil.rmtree(output_path)

textFile = sc.textFile(input_path)
print(f"Loaded content: {textFile.take(10)}")

# Perform the word count
wc_flatMap = textFile.flatMap(lambda line: line.split(" "))
print(f"Flat Map: {wc_flatMap.take(5)}")

wc_map = wc_flatMap.map(lambda word: (word, 1)) 
print(f"Map: {wc_map.take(5)}")

wc_reduce = wc_map.reduceByKey(lambda a, b: a + b)
print(f"Reduce: {wc_reduce.take(5)}")

# Save the results
wc_reduce.saveAsTextFile(output_path)
```

{% include figure.liquid loading="eager" path="assets/img/courses/big-data-engr/03-spark/spark_wordcount.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

{% enddetails %}

{% details Data distribution in Spark %}

- This is an updated word count code
    - Log Level is set to display ERROR only. 
    - We print out the default number of partitions for the data. 
    - This value can be reset and change. 

```python
# Input and output paths
input_path = "100-0.txt"
output_path = "output-wordcount-03"

# If output path exists, then delete the output directory first
import shutil
if os.path.exists(output_path):
    shutil.rmtree(output_path)

textFile = sc.textFile(input_path)
print(f"The file has {textFile.getNumPartitions()} partitions")

textFile_4 = textFile.repartition(4)
print(f"The new RDD of the file has {textFile_4.getNumPartitions()} partitions")

# Perform the word count
wordcount = textFile_4.flatMap(lambda line: line.split(" ")) \
    .map(lambda word: (word, 1)) \
    .reduceByKey(lambda a, b: a + b)

# Save the results
wordcount.saveAsTextFile(output_path)
```

{% include figure.liquid loading="eager" path="assets/img/courses/big-data-engr/03-spark/spark_nums.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

{% enddetails %}


