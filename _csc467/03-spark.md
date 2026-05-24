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

## What is Spark?

{% details Overview and design philosophy %}

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


{% include figure.liquid loading="eager" path="assets/img/courses/csc467/03-spark/spark_env.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true alt="Spark Computing Environment" %}

{% enddetails %}
{% details A brief history of Spark %}

- Research project at UC Berkeley AMP Lab in 2009 to address drawbacks of 
Hadoop MapReduce. 
- Paper published in 2010: [Spark: Cluster Computing with Working Sets](https://www.usenix.org/legacy/event/hotcloud10/tech/full_papers/Zaharia.pdf) 
- Source code is contributed to Apache in 2013. The project had more than 100 
contributors from more than 30 organizations outside UC Berkeley. 
- Version 1.0 was released in 2014. 
- Currently, Spark is being used extensively in academic and industry 
(NASA, CERN, Uber, Netflix …). 

{% enddetails %}

{% details A workflow system %}

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

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/03-spark/driver_executor.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true alt="Spark application architecture" %}

- Spark also has a local mode (what we are using for this class), where driver 
and executors are simply processes on the same machine. 
- Spark application developed in local mode can be carried over almost `as-is` 
to run in cluster mode (one of the attractiveness of Spark).
- Spark supports the following language APIs: Scala, Java, Python, SQL 
(ANSI SQL 2003 standard), and R.

--- 

{% enddetails %}
## Programming for Spark Computing Environment

{% details Overview %}

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

{% enddetails %}
{% details Common Spark transformations %}
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
{% details Common Spark actions %}
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

{% details Preparation %}

Assuming that you have complete the setup mentioned in [Introduction](https://linhbngo.github.io/csc467/01-introduction/#setup-computing-environment), the example code and data in the remainder of this lecture and 
the subsequent lectures will be available in the `big-data-engineering` directory. You will need to make 
sure that:
    - The terminal prompt is inside `big-data-engineering`
    - The conda environment `pyspark-3.5.1` is activated. 


```bash
pwd 
conda activate pyspark-3.5.1
```

Run the setup scripts

- `setup-pyspark-win.ps1` for Windows
- `source setup-pyspark-mac.sh` for Mac/Linux

{% enddetails %}

{% details Running WordCount %}

This is the source code for `wordcount.py` inside the `wordcount` directory:

```python
import sys
from pyspark.sql import SparkSession

def wordcount(input_path: str, output_path: str):
    try:
        spark = SparkSession.builder.appName("WordCount").getOrCreate()
        sc = spark.sparkContext
        wordcount = sc.textFile(input_path) \
            .flatMap(lambda line: line.split(" ")) \
            .filter(lambda word: word != "") \
            .map(lambda word: (word, 1)) \
            .reduceByKey(lambda a, b: a + b) 
        wordcount.saveAsTextFile(output_path)
        spark.stop()
    except Exception as e:
        print(f"Spark failed to start: {e}")

if __name__ == "__main__":
    wordcount(sys.argv[1], sys.argv[2])
```

- Pay attention to `input_path` and `output_path` variables. They are used to 
provide a path to the location of the input file, and the directory containing the output files. 
- Run the program with the following command

```bash
spark-submit --master="local[*]" ./wordcount/wordcount.py ./wordcount/data/100-0.txt ./wordcount/out-wc-1
```

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/03-spark/wordcount_output.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

- A successful run will generate the resulting output directory that contain `_SUCCESS` flag file (size 0). 
    - There will be several `*.crc` files, these are the check files to confirm data validity. 
    - The output of the word counting process is stored in two files: `part-00000` and `part-00001`. 

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/03-spark/wordcount_output_dir.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

- **For Windows users**: You might have an error message at the end. If the output files are generated correctly, 
feel free to ignore that error. 

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/03-spark/wordcount_output_err.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

{% enddetails %}

{% details Word Count workflow breakdown %}

- Let's breakdown the WordCount Python statements by save each stage individually. 

```python
import sys
from pyspark.sql import SparkSession

def wordcount(input_path: str, output_path: str):
    try:
        spark = SparkSession.builder.appName("WordCount").getOrCreate()
        sc = spark.sparkContext
        wordcount = sc.textFile(input_path)

        wordcount_flatMap = wordcount.flatMap(lambda line: line.split(" "))
        wordcount_flatMap.saveAsTextFile(output_path + "_flatMap")

        wordcount_filter = wordcount_flatMap.filter(lambda word: word != "")
        wordcount_filter.saveAsTextFile(output_path + "_filter")

        wordcount_map = wordcount_filter.map(lambda word: (word, 1))
        wordcount_map.saveAsTextFile(output_path + "_map")

        wordcount_reduceByKey = wordcount_map.reduceByKey(lambda a, b: a + b)
        wordcount_reduceByKey.saveAsTextFile(output_path + "_reduceByKey")
        
        spark.stop()
    except Exception as e:
        print(f"Spark failed to start: {e}")

if __name__ == "__main__":
    wordcount(sys.argv[1], sys.argv[2])
```

Run the program

```bash
spark-submit --master="local[*]" ./wordcount/wordcount-stages.py ./wordcount/data/100-0.txt ./wordcount/out-wc
```

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/03-spark/spark_wordcount.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

- Try to save the RDD file in the output path  is going to create 
an error: `org.apache.hadoop.mapred.FileAlreadyExistsException`. 

```python
step3.saveAsTextFile(output_path)
```

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/03-spark/spark_output_error.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

```python
output_path="output-wordcount-02"
step3.saveAsTextFile(output_path)
```

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/03-spark/spark_output_correct.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

{% enddetails %}

{% details Data distribution in Spark %}

- This is an updated word count code
    - Log Level is set to display ERROR only. 
    - We print out the default number of partitions for the data. 
    - This value can be reset and change. 

```python
import sys
from pyspark.sql import SparkSession

def wordcount(input_path: str, output_path: str):
    try:
        spark = SparkSession.builder.appName("WordCount").getOrCreate()
        sc = spark.sparkContext
        sc.setLogLevel("ERROR")
        wordcount = sc.textFile(input_path)

        print(f"Number of partitions before repartitioning: {wordcount.getNumPartitions()}")

        wordcount_repartitions = wordcount.repartition(4)
        print(f"Number of partitions after repartitioning: {wordcount_repartitions.getNumPartitions()}")

        output = (wordcount_repartitions.flatMap(lambda line: line.split(" "))
                  .filter(lambda word: word != "")
                  .map(lambda word: (word, 1))
                  .reduceByKey(lambda a, b: a + b)
                  )
        
        output.saveAsTextFile(output_path)
        spark.stop()
    except Exception as e:
        print(f"Spark failed to start: {e}")

if __name__ == "__main__":
    wordcount(sys.argv[1], sys.argv[2])
```

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/03-spark/spark_nums.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

{% enddetails %}


