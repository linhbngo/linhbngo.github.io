---
layout: lecture
pretty_table: true
order: 2
title: Distributed Machine Learning with Spark
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

# Distributed Machine Learning with Spark

## 1. Application 

Example: Spam filtering

|    | viagra | learning | the | dating | nigeria | spam? |
| ---| ------ | -------- | --- | ------ | ------- | ------------ |
| X1 | 1      | 0        | 1   | 0      | 0       | $y_1$ = 1       |
| X2 | 0      | 1        | 1   | 0      | 0       | $y_2$ = -1      |
| X3 | 0      | 0        | 0   | 0      | 1       | $y_3$ = 1       |

- Instance spaces X1, X2, X3 belong to set X (data points)
    - Binary or real-valued feature vector X of word occurrences
    - `d` features (words and other things, d is approximately 100,000)
- Class Y
    - Spam = 1
    - Ham = -1

---

## 2. Linear models for classification

### 2.1. Overview

$$
f(x) =
\begin{cases}
+1 & \text{if } w_{1}x_{1}+w_{2}x_{2}+...+w_{d}x_{d} \ge \theta \\
-1 & \text{otherwise}
\end{cases}
$$

- Vector $X_j$ contains real values
    - The [Euclidean norm](https://en.wikipedia.org/wiki/Norm_(mathematics)#Euclidean_norm) is `1`. 
    - Each vector has a label $y_j$
- The goal is to find a vector W = ($w_1$, $w_2$, ..., $w_d$) with $w_j$ is a real number such that:
    - The labeled points are clearly separated by a line: 
  
$$
w_{1}x_{1}+w_{2}x_{2}+...+w_{d}x_{d} = \theta \\
$$

- Dot is spam, minus is ham!

![](fig/10-svm/03.png)



### 2.2. Linear classifiers

- Each feature `i` as a weight w_i$
- Prediction is based on the weighted sum:
![](fig/10-svm/04.png)
- If f(x) is:
    - Positive: predict +1
    - Negative: predict -1

  ![](fig/10-svm/05.png)


## 3. Support Vector Machine

### 3.1. Overview
- Originally developed by Vapnik and collaborators as a linear classifier. 
- Could be modified to support non-linear classification by mapping into high-dimensional spaces. 
- Problem statement:
    - We want to separate `+` from `-` using a line. 
    - Training examples: 
  
    ![](fig/10-svm/06.png)
  
    - Each example `i`:
  
    ![](fig/10-svm/07.png)
    ![](fig/10-svm/08.png)
  
    - Inner product:
    ![](fig/10-svm/09.png)

- Which is the best linear separate defined by w?

![](fig/10-svm/10.png)

### 3.2. Support Vector Machine: largest margin

- Distance from the separating line corresponds to the **confidence** of the prediction. 
- For example, we are more sure about the class of `A` and `B` than of `C`. 

![](fig/10-svm/11.png)

- Margin definition:

![](fig/10-svm/12.png)
![](fig/10-svm/13.png)

- Maximizing the margin while identifying `w` is good according to intuition, theory, and practice. 

![](fig/10-svm/14.png)

- A math question: how do you narrate this equation?

![](fig/10-svm/15.png)

### 3.3. Support Vector Machine: what is the margin?

- Slide from the book

![](fig/10-svm/16.png)

- Notation:
  - `Gamma` is the distance from point A to the linear separator L: `d(A,L) = |AH|`
  - If we select a random point M on line L, then d(A,L) is the projection of AM onto vector `w`. 
  - [Project](https://mathworld.wolfram.com/Projection.html)
  - If we assume the normalized Euclidean value of `w`, `|w|`, is equal to one, that bring us to 
  the result in the slide. 
- In other words, maximizing the margin is directly related to how `w` is chosen.
- For the *i<sup>th</sup>* data point:

  ![](fig/10-svm/17.png).

### 3.4. Some more math ...

  ![](fig/10-svm/18.png)
  - After some more mathematical manipulations:
  ![](fig/10-svm/19.png)
  - Everything comes back to an optimization problem on `w`:
  ![](fig/10-svm/20.png)
  ![](fig/10-svm/21.png)


### 3.5. SVM: Non-linearly separable data

  ![](fig/10-svm/22.png)
  - For each data point:
    - If margin greater than 1, don't care. 
    - If margin is less than 1, pay linear penalty. 
  - Introducing slack variables:

  ![](fig/10-svm/23.png)

  ![](fig/10-svm/24.png)


