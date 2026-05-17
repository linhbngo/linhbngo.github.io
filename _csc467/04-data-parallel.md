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
  - name: Initial preparation
  - name: Matrix-vector multiplication
  - name: Analyzing text data (not using Spark SQL)
---
# Data Parallel Computing with Spark

## Initial preparation

- The code instructions here is meant for Spark running on local devices. 
    - If you are using Colab or Kaggle, make sure that you prepare your notebook with instructions in the Setup lecture. 
- Each segment of codes in this lecture is meant to be run 
on a separate Jupyter notebook cell. The ordering is important!

```python linenums="1"
import sys
import os
sys.path.insert(0, '/opt/spark/python')
sys.path.insert(0, '/opt/spark/python/lib/py4j-0.10.9.7-src.zip')
os.environ['SPARK_HOME'] = '/opt/spark'

import pyspark

conf = pyspark.SparkConf()
conf.setMaster("spark://spark-master:7077")
conf.set("spark.driver.memory","1g")

sc = pyspark.SparkContext(conf=conf)
```

---

## Matrix-vector multiplication

{% details Initial data %}

```python linenums="1"
import numpy as np
np.random.seed(123)
N = 4
M = np.random.randint(5, size = (N, N))
V = np.random.randint(5, size = N)

P = np.matmul(M, V)

# Print the matrices
print(f"Matrix M:\n {M}")
print(f"Vector N:\n {V}")
print(f"Dot Product P:\n {P}")
```

{% details Output %}

```output
Matrix M:
[[2 4 2 1]
[3 2 3 1]
[1 0 1 1]
[0 0 1 3]]
Vector N:
[4 0 0 4]
Dot Product P:
[12 16 8 12]
```

{% enddetails %}
{% details Initial assumption %}

Vector V fits into memory

{% enddetails %}
{% enddetails %}
{% details Moving data from notebook's memory into Spark cluster %}

- Data can be generated on the driver side, then `parallelize` into 
RDD objects on the cluster. 

```python linenums="1"
mspark = sc.parallelize(M)
print(mspark.take(4))
```

{% details Output %}

```output
[array([2, 4, 2, 1]), array([3, 2, 3, 1]), array([1, 0, 1, 1]), array([0, 0, 1, 3])]
```

{% enddetails %}
- This will not work well, as we no longer have an indicator of row order. We need to provide some additional information as we parallelize our local data. 
    - [zipWithIndex](https://spark.apache.org/docs/latest/api/python/reference/api/pyspark.RDD.zipWithIndex.html)

```python linenums="1"
mspark = sc.parallelize(M).zipWithIndex()
print(mspark.take(4))
```

{% details Output %}


```output
[(array([2, 4, 2, 1]), 0), (array([3, 2, 3, 1]), 1), (array([1, 0, 1, 1]), 2), (array([0, 0, 1, 3]), 3)]    
```

{% enddetails %}
{% enddetails %}
{% details Direct multiplication %}

```python linenums="1"
def vectorDot(mRow): 
    return mRow.dot(V)

mspark = sc.parallelize(M).zipWithIndex().\
    map(lambda item: (vectorDot(item[0])))

print(f"MapReduce Dot Product:\n {np.array(mspark.take(4))}")
print(f"Dot Product P:\n {P}")
```
{% details Output %}


```output
MapReduce Dot Product:
[12 16 8 12]
Dot Product P:
[12 16 8 12]
```

{% enddetails %}
{% details Remove assumption %}

- Vector V no longer fits into memory

{% enddetails %}
{% enddetails %}
{% details Data processing for multiplication %}

- Both matrix M and vector V are loaded onto Spark

```python linenums="1"
mspark = sc.parallelize(M).zipWithIndex()
vspark = sc.parallelize(V).zipWithIndex()
print(mspark.take(4))
print(vspark.take(4))
```

{% details Output %}


```output
[(array([2, 4, 2, 1]), 0), 
(array([3, 2, 3, 1]), 1), 
(array([1, 0, 1, 1]), 2), 
(array([0, 0, 1, 3]), 3)]
[(np.int64(4), 0), (np.int64(0), 1), (np.int64(0), 2), (np.int64(4), 3)]
```

{% enddetails %}
- We want to use indices as keys

```python linenums="1"
mspark = sc.parallelize(M).zipWithIndex().map(lambda item: (item[1],item[0]))
vspark = sc.parallelize(V).zipWithIndex().map(lambda item: (item[1],item[0]))
print(mspark.take(4))
print(vspark.take(4))
```

{% details Output %}


```output
[(0, array([2, 4, 2, 1])), 
(1, array([3, 2, 3, 1])), 
(2, array([1, 0, 1, 1])), 
(3, array([0, 0, 1, 3]))]
[(0, np.int64(4)), (1, np.int64(0)), (2, np.int64(0)), (3, np.int64(4))]
```

{% enddetails %}
- Let's turn RDDs of M and V into a single RDD

```python linenums="1"
pspark = mspark.union(vspark)
print(pspark.take(8))
```

{% details Output %}


```output
[(0, array([2, 4, 2, 1])), 
(1, array([3, 2, 3, 1])), 
(2, array([1, 0, 1, 1])), 
(3, array([0, 0, 1, 3])), 
(0, np.int64(4)), 
(1, np.int64(0)), 
(2, np.int64(0)), 
(3, np.int64(4))]
```

{% enddetails %}
- Each of these numpy array represents one row 
of the matrix (see `Initial data`).
    - The summation is made on the product of each element of the same column
    on each row. 
- Because V no longer fits into memory, it can be reasoned taht each of these numpy arrays also does not fit in memory. 
    - Need to extract column identifier from each numpy array and turn them into individual values, similar to the vector's values. 
    - This needs to be done prior to `union`

```python linenums="1"
def getPos(t):
    res = []
    for idx,x in np.ndenumerate(t[1]):
        res.append((idx[0], (t[0], x))) # (row, (column, cell value))
    return res

pspark = mspark.flatMap(getPos).union(vspark)
print(pspark.take(20))
```

{% details Output %}


```output
[(0, (0, np.int64(2))), (1, (0, np.int64(4))), (2, (0, np.int64(2))), (3, (0, np.int64(1))), 
(0, (1, np.int64(3))), (1, (1, np.int64(2))), (2, (1, np.int64(3))), (3, (1, np.int64(1))), 
(0, (2, np.int64(1))), (1, (2, np.int64(0))), (2, (2, np.int64(1))), (3, (2, np.int64(1))), 
(0, (3, np.int64(0))), (1, (3, np.int64(0))), (2, (3, np.int64(1))), (3, (3, np.int64(3))), 
(0, np.int64(4)), (1, np.int64(0)), (2, np.int64(0)), (3, np.int64(4))]
```

{% enddetails %}
- The keys of the above pairs represent the row identifier. 
- If value is a tuple, first element is the column identifier and second element 
represent the value of the matrix cell corresponding to the specific row and column. 

```python linenums="1"
def getPos(t):
    res = []
    for idx,x in np.ndenumerate(t[1]):
        res.append((idx[0], (t[0], x)))
    return res
    
pspark = mspark.flatMap(getPos).union(vspark).groupByKey()
print(pspark.take(16))
```

{% details Output %}


```output
[(0, <pyspark.resultiterable.ResultIterable object at 0xffff885f62c0>), 
(1, <pyspark.resultiterable.ResultIterable object at 0xffff885f4d30>), 
(2, <pyspark.resultiterable.ResultIterable object at 0xffff885f6a70>), 
(3, <pyspark.resultiterable.ResultIterable object at 0xffff885f6ec0>)]
```

{% enddetails %}
- Convert data into `list` type instead of Spark's `iterables`

```python linenums="1"
def getPos(t):
    res = []
    for idx,x in np.ndenumerate(t[1]):
        res.append((idx[0], (t[0], x)))
    return res
    
pspark = mspark.flatMap(getPos).union(vspark).groupByKey().mapValues(list)
print(pspark.take(16))
```

{% details Output %}


```output
[(0, [(1, np.int64(3)), (2, np.int64(1)), (3, np.int64(0)), (0, np.int64(2)), np.int64(4)]), 
(1, [(3, np.int64(0)), np.int64(0), (0, np.int64(4)), (1, np.int64(2)), (2, np.int64(0))]), 
(2, [(0, np.int64(2)), (1, np.int64(3)), (3, np.int64(1)), (2, np.int64(1)), np.int64(0)]), 
(3, [(1, np.int64(1)), np.int64(4), (3, np.int64(3)), (0, np.int64(1)), (2, np.int64(1))])]
```

{% enddetails %}
- Each element in this `pspark` frame is a key/value pair:
    - The key is the row index 
    - The value is a 5-element array: 
        - Four elements belong to a row of the matrix M, each of this element is a tuple with the key representing the column index and the value represent the corresponding matrix cell value. 
        - One remaining element belong to the value of the vector V at that row index position. 
- As shown in the previous output, we cannot assume proper order after union, especially for large scale data
- Need to flatten the final results (list of tupples instead of list of lists of tuples)

```python linenums="1"
def getPos(t):
    res = []
    for idx,x in np.ndenumerate(t[1]):
        res.append((idx[0], (t[0], x)))
    return res

def arrayMul(t):
    res = []
    vectorVal = 0
    for x in t[1]:
        if type(x) != tuple:
            vectorVal = x
    for x in t[1]:
        if type(x) == tuple:
            res.append((x[0], x[1] * vectorVal))
    return res
    
pspark = mspark.flatMap(getPos).union(vspark).groupByKey().mapValues(list).flatMap(arrayMul)
print(pspark.take(16))
```

{% details Output %}


```output
[(3, np.int64(0)), (2, np.int64(4)), (0, np.int64(8)), (1, np.int64(12)), 
(1, np.int64(0)), (2, np.int64(0)), (0, np.int64(0)), (3, np.int64(0)), 
(3, np.int64(0)), (2, np.int64(0)), (1, np.int64(0)), (0, np.int64(0)), 
(0, np.int64(4)), (2, np.int64(4)), (3, np.int64(12)), (1, np.int64(4))]
```

{% enddetails %}
- Final steps: 
    - groupByKey: Bring the values with same row index together.
    - mapValues: Convert value type `iterables` into `list`.
    - mapValues: Apply sum on the value list. 

```python linenums="1"
dotspark = pspark.groupByKey().mapValues(list).mapValues(sum).map(lambda x: x[1])
print(f"MapReduce Dot Product:\n {np.array(dotspark.take(4))}")
print(f"Dot Product P:\n {P}")
```

{% details Output %}


```output
MapReduce Dot Product:
[12 16 8 12]
Dot Product P:
[12 16 8 12]
```

{% enddetails %}
---
{% enddetails %}
## Analyzing text data (not using Spark SQL)

{% details Getting MovieLens data %}

- Downloading move review data

```python linenums="1"
!wget https://files.grouplens.org/datasets/movielens/ml-32m.zip
!unzip ml-32m.zip
```

- How big of a data set are we talking about?

```python linenums="1"
!ls -lh ml-32m/
```

- You can review the [README](https://files.grouplens.org/datasets/movielens/ml-32m-README.html) of this data set. 

```python linenums="1"
ratings = sc.textFile(working_dir + "/ml-32m/ratings.csv")
print(ratings.take(5))   
ratings.cache()
```

- First count, not yet loaded into memory

```python linenums="1"
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

```python linenums="1"
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

```python linenums="1"
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
