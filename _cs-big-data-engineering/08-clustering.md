---
layout: lecture
pretty_table: true
order: 2
title: Clustering
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

# Clustering


## 1. Overview

### 1.1. General problem statement

- Given a **set of data points**, with a notion of **distance** between points, 
**group the points** into some number of **clusters** so that:
    - Members of a cluster are close/similar to each other.
    - Members of different clusters are dissimilar.
- Usually
    - Points are in high-dimensional space (observations have many attributes).
    - Similarity is defined using a distance measure: Euclidean, Cosine, Jaccard, edit distance ...

### 1.2. Clustering is a hard problem

- Clustering in two dimensions looks easy.  
- Clustering small amounts of data looks easy. 
- In most cases, looks are **not** deceiving. 
- But:
    - Many applications involve not 2, but 10 or 10,000 dimensions. 
    - High-dimensional spaces look different. 

???example "Clustering Sky Objects"
    - A catalog of 2 billion **sky objects** represents objects by their radiation in 7 dimensions (frequency bands)
    - Problem: cluster into similar objects, e.g., galaxies, stars, quasars, etc.

    <figure markdown="span">
        ![](fig/08-clustering/sn_gallery24.jpg)
        <figcaption>36 of the 500+ Type Ia supernovae discovered by the Sloan Supernova Survey</figcaption>
    </figure>

???example "Clustering music albums"
    - Music divides into **categories**, and customer prefer a few categories
        - Are **categories** simply genres?
    - Represent an album by a set of customers who bought it
        - Similar albums have similar sets of customers, and vice-versa
    - Space of all albums:
        - Think of a space with one dimension for each customer
        - Values in a dimension may be 0 or 1 only
    ???abstract "Data representation"
        - An album is a point in this space $(x_1, x_2, ...,x_k)$ where $x_i = 1$ `if 
        and only if` the $i^{th}$ customer bought the CD.
        - For Amazon, the dimension is tens of millions
    - Find clusters of similar CDs
    

???example "Clustering documents"
    - Finding topics
        - Group together documents on the same topic. 
        - Documents with similar sets of words maybe about the same topic. 
        - Dual formulation: a topic is a group of words that co-occur in many documents. 
    ???abstract "Data representation"
        - Represent a document by a vector $(x_1, x_2, ...,x_k)$ where $x_i = 1$ `if 
        and only if` the $i^{th}$ word (in some order) appears in the document.
        - Document with similar sets of words may be about the same topic. 
    
### 1.3. Distance Measurements: Cosine, Jaccard, Euclidean

- Different ways of representing documents or music albums 
lead to different distance measures. 
    - Document as `set of words `
        - Jaccard distance
    - Document as `point in space of words`. 
        - $x_i$ = 1 if `i` appears in doc. 
        - Euclidean distance
    - Document as `vector in space of words`. 
        - Vector from origin to ...
        - Cosine distance. 

- Review sequential implementation of these distance via the [distance-measurment notebook](https://colab.research.google.com/drive/1r0fxDR1hffHVyREEINLicoB5lNiIfYSQ?usp=sharing).

## 1.4. Overview: methods of clustering

=== "Hierarchical"
    ![Hierrarchical](fig/08-clustering/hierarchical_dendo.png){ align=left width=300 loading=lazy }

    - Agglomerative (bottom up): each point is a cluster, 
    repeatedly combining two nearest cluster.
    - Divisive (top down): start with one cluster and 
        recursively split it. 
    - Key operation: repeatedly combine two nearest clusters. 

=== "Point assignment"
    ![Point assignment](fig/08-clustering/point_assignment.png){ align=left width=300 height=200 loading=lazy }

    - Maintain a set of clusters
    - Points belong to `nearest` cluster

- Three important questions:

    ???info "1. How do you represent a cluster of more than one point?"
        - Key problem: As you merge clusters, how do you represent the 
        “location” of each cluster, to tell which pair of clusters is closest?
        - Euclidean case: 
            - Each cluster has a `centroid` = average of its (data)points
        - Non-Euclidean case: 
            - The only “locations” we can talk about are the points themselves
            i.e., there is no “average” of two points
            - `clustroid`  = (data)point **closest** to other points
                - Smallest maximum distance to other points
                - Smallest average distance to other points
                - Smallest sum of squares of distances to other points

    ???info "2. How do you determine the “nearness” of clusters?"
        - Measure cluster distances by distances of `centroids`, `clustroid`
        - Define Intercluster distance = minimum of the distances between any two points, 
        one from each cluster
        - Pick a notion of “cohesion” of clusters, e.g., maximum distance from the 
        clustroid
            - Merge clusters whose union is most cohesive
        
    ???info "3. When to stop combining clusters?"
        - Minimal differences between iteration
        - Native iteration: $O(N^3)$
        - Priority queue: $O(N^2logN)$

---

## 2. K-means clustering

### 2.1. Overview
- Assumes `Euclidean` space/distance 
- Pick `k`, the number of clusters. 
- Initialize clsuters by picking on point per cluster. 
    - Example: Pick one point at random, then  k-1 other points, 
    each as far away as possible from the previous points

### 2.2. Populating clusters

1. For each point, place it in the cluster whose current centroid it is nearest. 
    - A cluster centroid has its coordinates calculated as the averages of all its points' coordinates. 
2. After all points are assigned, update the locations of centroids of the `k` clusters. 
3. Reassign all points to their closest centroid. 

- Repeat 1. and 2. until convergence
    - Points don’t move between clusters and centroids stabilize, or
    - Very few points move, and the movements are back and forth in nature

### 2.3. How to select k?

- Try different `k`, looking at the change in the average distance 
to centroid, as `k` increases. 
- Approach 1: sampling
    - Cluster a sample of the data using hierarchical clustering, to obtain `k` clusters.
    - Pick a point from each clsuter (e.g. point closest to centroid)
    - Sample fits in main memory.
- Approach 2: Pick `dispersed` set of points
    - Pick first point at random
    - Pick the next point to be the one whose minimum distance from the selected points is as large as possible. 
    - Repeat until we have `k` points. 

???example "Visual example"

    ???warning "Too few"

        ![Too few](fig/08-clustering/kmean_few.png)

        - Many long distances to centroid

    ???success "Just right"

        ![Just right](fig/08-clustering/kmean_right.png)

        - Distances are relatively short

    ???warning "Too many"
    
        ![Too many](fig/08-clustering/kmean_many.png)

        - Little improvement in avaerage distance

---

## 3. K-means on big data: BFR (Bradley-Fayyad-Reina)

### 3.1. BFR: Bradley-Fayyad-Reina

- [Scaling EM (Expectation-Maximization) Clustering to Large Databases](data/scaling_em.pdf)
- BFR [Bradley-Fayyad-Reina] is a variant of k-means designed 
to handle very large (disk-resident) data sets
- Assumes that clusters are normally distributed around a centroid in 
a Euclidean space
    - Standard deviations in different dimensions may vary
    - Clusters are axis-aligned ellipses
- Efficient way to summarize clusters (want memory required O(clusters) and not O(data))

???abstract "BFR"
    - Points are read from disk one main-memory-full at a time
    - Most points from previous memory loads are summarized by simple statistics
    - To begin, from the initial load we select the initial k centroids by 
    some sensible approach:
        - Take k random points
        - Take a small random sample and cluster optimally
        - Take a sample; pick a random point, and then k-1 more points, each as far from the 
        previously selected points as possible
    
### 3.2. Three classes of points

![Point classes](fig/08-clustering/kmean_point_class.png)

???info "Discard set (DS)"
    - Points close enough to a centroid to be summarized

???info "Compression set (CS)"
    - Groups of points that are close together but not close to any existing centroid
    - These points are summarized, but not assigned to a cluster

???info "Retained set (RS)"
    - Isolated points waiting to be assigned to a compression set

### 3.3. Discard set (DS)
- Represented by:
    - The number of points, N
    - The vector `SUM`, whose $i^{th}$ component is the sum of 
    the coordinates of the points in the $i^{th}$ dimension
    - The vector `SUMSQ`: whose $i^{th}$ component is the sum 
    of squares of coordinates in $i^{th}$ dimension
- Properties:
    - $2d + 1$ values represent any size cluster
        - $d$ is the number of dimensions
    - Average in each dimension (the centroid) can be 
    calculated as $\frac{SUM_i}{N}$ with $SUM_i$ is the 
    $i^th$ component of SUM.
    - Variance of a cluster's discard set in dimension i 
    is: $\frac{SUMSQ_i}{N} - (\frac{SUM_i}{N})^2$
        - And standard deviation is the square root of variance. 

### 3.4. Processing the Memory-Load of points
0. Start out with a selection of k centroids. 
1. Find those points that are “sufficiently close” to a cluster 
centroid and add those points to that cluster and the DS
    - These points are so close to the centroid that 
    they can be summarized and then discarded
2. Use any main-memory clustering algorithm to cluster the 
remaining points and the old RS
    - Clusters go to the CS; outlying points to the RS
3. DS set: Adjust statistics of the clusters to account 
for the new points
    - Add Ns, SUMs, SUMSQs
4. Consider merging compressed sets in the CS
5. If this is the last round, merge all compressed sets in the CS 
and all RS points into their nearest cluster

???tip "1. How do we decide if a point is “close enough” to a cluster that we will add the point to that cluster?"
    BFR suggests two approaches

    - The Mahalanobis distance is less than a threshold
        - Normalized Euclidean distance from centroid
        - For point $(x_1,x_2,...,x_d)$ and centroid $(c_1,c_2,...,c_d)$
            - Normalize in each dimension: $y_i = \frac{x_i - c_i}{\sigma_i}$
            - ${\sigma_i}$: standard deviation of points in the cluster in the $i^{th}$ dimension
            - Take sum of the squares of the $y_i$
            - Take the square root
    - High likelihood of the point belonging to currently nearest centroid
    

???tip "2. How do we decide whether two compressed sets (CS) deserve to be combined into one?"
    - Compute the variance of the combined subcluster
        - `N`, `SUM`, and `SUMSQ` allow us to make that calculation quickly
    - Combine if the combined variance is below some threshold
    - Many alternatives: Treat dimensions differently, consider density
    
---
 
## 4. Improvement on BFR: CURE

### 4.1. Overview
- Problem with BFR/k-means:
    - Assumes clusters are normally distributed in each dimension
    - And axes are fixed - ellipses at an angle are not OK  
- CURE (Clustering Using REpresentatives):
    - Assumes a Euclidean distance
    - Allows clusters to assume any shape
    - Uses a collection of representative points to represent clusters

![](fig/08-clustering/cure_example.png)


### 4.2. Two-pass algorithm
- Pass 1:
    1. Pick a random sample of points that fit in main memory
    2. Initial clusters: 
        - Cluster these points hierarchically – group nearest points/clusters
    3. Pick representative points:
        - For each cluster, pick a sample of points, as dispersed as possible
        - From the sample, pick representatives by moving them (say) 20% toward the centroid of the cluster
- Pass 2:
    1. Rescan the whole dataset and visit each point p in the data set
    2. Place it in the “closest cluster”
        - Normal definition of “closest”: Find the closest representative to p and assign it to representative’s cluster

---

## 5. Clustering on Spark

- [Libraries for major clustering techniques](https://spark.apache.org/docs/latest/ml-clustering.html) 
- [K-means](https://spark.apache.org/docs/latest/api/python/reference/api/pyspark.ml.clustering.KMeans.html)
- [Bisecting-Kmeans](https://spark.apache.org/docs/latest/api/python/reference/api/pyspark.ml.clustering.BisectingKMeans.html) 

