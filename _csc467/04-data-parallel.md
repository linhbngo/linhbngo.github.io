---
layout: lecture
pretty_table: true
order: 5
title: Data Parallel Computing with Spark
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
  - name: Matrix-vector multiplication I
  - name: Matrix-vector multiplication II
  - name: Analyzing text data (not using Spark SQL)
---


## Matrix-vector multiplication I

- Run `git pull` on the `big-data-engineering` repository.
- Source Code

```python
import sys
import numpy as np
from pyspark.sql import SparkSession

np.random.seed(123)

def matvec(N: int):
  try:
    spark = SparkSession.builder.appName("Vector and Matrix Multiplication").getOrCreate()
    sc = spark.sparkContext
    M = np.random.randint(5, size = (N, N))
    V = np.random.randint(5, size = N)
        
    P = np.matmul(M, V)

    # Print the matrices
    print(f"Matrix M:\n {M}")
    print(f"Vector N:\n {V}")
    print(f"Dot Product P:\n {P}")
    
    mspark = sc.parallelize(M)
    print(f"Parallelize M inside Spark Context:\n {mspark.take(4)}")

    mspark = sc.parallelize(M).zipWithIndex()
    print(f"Parallelize M inside Spark Context with Index:\n {mspark.take(4)}")

    mspark = (sc
              .parallelize(M)
              .zipWithIndex()
              .map(lambda item: item[0].dot(V))
    )

    print(f"MapReduce Dot Product:\n {np.array(mspark.take(4))}")
    print(f"Serial Dot Product P for comparison purposes:\n {P}")

    spark.stop()

  except Exception as e:
    print(f"Spark failed to start: {e}")

if __name__ == "__main__":
    matvec(int(sys.argv[1]))
```

Run the following command

```bash
spark-submit --master="local[*]" .\data-parallel\matrix-vector.py 4
```

{% details Screenshot: output %}

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/04-data-parallel/mat-vec.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true alt="Example output" %}

{% enddetails %}

{% details Data initialization %}

- Lines 11-12: We initialize matrix M of size N by N, and vector V of size N. 
- Line 14: We carry out a dot product using the builtin function of numpy. 

{% details Initial assumption %}

Vector V fits into memory

{% enddetails %}

{% enddetails %}


{% details Parallelizing data in Spark cluster %}

- Lines 21-22: Data can be generated on the driver side, then `parallelize` into 
RDD objects on the cluster. 
    - This will not work well, as we no longer have an indicator of row order. We need to provide some additional information as we parallelize our local data. 
- Lines 24-25: This is possible with [zipWithIndex](https://spark.apache.org/docs/latest/api/python/reference/api/pyspark.RDD.zipWithIndex.html)

{% enddetails %}


{% details Direct multiplication %}

- Lines 27-31: We can take each data element of `mspark` and perform a dot product between the element and Vector V. 
- **What happens if Vector V no longer fits into memory?**

{% enddetails %}

## Matrix-vector multiplication II

```python
import sys
import numpy as np
from pyspark.sql import SparkSession

np.random.seed(123)

def getPos(t):
  res = []
  for idx,x in np.ndenumerate(t[1]):
    res.append((idx[0], (t[0], x.item()))) # (row, (column, cell value))
  return res

def arrayMul(t):
  res = []
  vectorVal = None
  for x in t[1]:
    if type(x) != tuple:
      vectorVal = x
  for x in t[1]:
    if isinstance(x, tuple):
      row_index = x[0]
      matrix_value = x[1]
      res.append((row_index, matrix_value * vectorVal))
  return res

def matvec(N: int):
  try:
    spark = SparkSession.builder.appName("Vector and Matrix Multiplication").getOrCreate()
    sc = spark.sparkContext
    M = np.random.randint(5, size = (N, N))
    V = np.random.randint(5, size = N)
        
    P = np.matmul(M, V)

    # Print the matrices
    print(f"Matrix M:\n {M}")
    print(f"Vector V:\n {V}")
    print(f"Dot Product P:\n {P}")
    
    mspark = sc.parallelize(M).zipWithIndex().map(lambda item: (item[1],item[0].tolist()))
    print(f"Parallelize M inside Spark Context with Index:")
    local_mspark = mspark.collect()
    for item in local_mspark:
      print(item)

    vspark = sc.parallelize(V).zipWithIndex().map(lambda item: (item[1],item[0].tolist()))
    print(f"Parallelize V inside Spark Context with Index:")
    local_vspark = vspark.collect()
    for item in local_vspark:
      print(item)

    pspark = (mspark
              .flatMap(getPos)
              .union(vspark)
              .groupByKey()
              .mapValues(list)
              .flatMap(arrayMul)
              .reduceByKey(lambda a, b: a + b)
    )
    
    print(f"MapReduce Dot Product:")
    local_pspark = pspark.collect()
    for item in local_pspark:
      print(item)

    #flatMap(arrayMul)

    #print(f"MapReduce Dot Product:\n {np.array(pspark.take(16))}")
    print(f"Serial Dot Product P for comparison purposes:\n {P}")

    spark.stop()

  except Exception as e:
    print(f"Spark failed to start: {e}")

if __name__ == "__main__":
    matvec(int(sys.argv[1]))
```

Run the following command

```bash
spark-submit --master="local[*]" .\data-parallel\matrix-big-vector.py 16
```

{% details Data processing for multiplication %}

- Lines 40-50: Both matrix M and vector V are loaded onto Spark
    - Line 40 and line 50: We want to use indices as keys

{% enddetails %}

{% details Matrix multiplication %}

- Because V no longer fits into memory, it can be reasoned that each of these numpy arrays also does not fit in memory. 
- Line 53: Need to extract column identifier from each numpy array and turn them into individual values, similar to the vector's values with `getPos`
- Line 54: Combine individual items of M and V, and group them together with `groupBy`. 
    - Line 56: Convert data into `list` type instead of Spark's `iterables`
    - Each element in this frame after `groupBy` is a key/value pair:
    - The key is the row index 
    - The value is a (N+1)-element array: 
        - N elements belong to a row of the matrix M, each of this element is a tuple with the key representing the column index and the value represent the corresponding matrix cell value. 
        - One remaining element belong to the value of the vector V at that row index position. 
- Line 57: As shown in the previous output, we cannot assume proper order after union, especially for large scale data
    - Need to flatten the final results (list of tupples instead of list of lists of tuples)
- Line 58: Add elements together with `reduceByKey`. 

{% enddetails %}

## Analyzing text data (not using Spark SQL)

{% details Getting MovieLens data %}

- Downloading move review data

```python
!wget https://files.grouplens.org/datasets/movielens/ml-32m.zip
!unzip ml-32m.zip
```

- How big of a data set are we talking about?

```python
!ls -lh ml-32m/
```

- You can review the [README](https://files.grouplens.org/datasets/movielens/ml-32m-README.html) of this data set. 

```python
ratings = sc.textFile(working_dir + "/ml-32m/ratings.csv")
print(ratings.take(5))   
ratings.cache()
```

- First count, not yet loaded into memory

```python
%%time
ratings.count()
```

{% details Output %}


```output
CPU times: user 252 ms, sys: 28.2 ms, total: 280 ms
Wall time: 1min 40s
32000205
```

{% enddetails %}
- Second count, preloaded

```python
%%time
ratings.count()
```
{% details Output %}


```output
CPU times: user 147 ms, sys: 19.8 ms, total: 167 ms
Wall time: 58.4 s
32000205
```

{% enddetails %}
- Third count, preloaded

```python
%%time
ratings.count()
```

{% details Output %}


```output
CPU times: user 147 ms, sys: 19.8 ms, total: 167 ms
Wall time: 58.4 s
32000205
```

{% enddetails %}
{% details Hands-on 1 %}

- What are the average ratings over the years of each movie?    
- Note: don't forget to filter!

{% enddetails %}
{% details Hands-on 2 %}

- What are the average ratings over the years of each movie?
    - Display the results with movie titles instead of movie IDs
- Assumption: **movies.csv does not fit in memory**

{% enddetails %}
{% details Hands-on 3 %}

- Identify movies that can be considered cult-classic?

{% enddetails %}
{% details Hands-on 4 %}

- What are the average ratings over the years of each genre
- Assumption: **movies.csv does not fit in memory**

{% enddetails %}
{% enddetails %}
