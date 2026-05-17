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
  - name: Application
  - name: Linear models for classification
  - name: Support Vector Machine
---
# Distributed Machine Learning with Spark

## Application

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

## Linear models for classification

{% details Overview %}

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

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/03.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}



{% enddetails %}
{% details Linear classifiers %}

- Each feature `i` as a weight w_i$
- Prediction is based on the weighted sum:
{% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/04.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
- If f(x) is:
    - Positive: predict +1
    - Negative: predict -1

  {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/05.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}


{% enddetails %}
## Support Vector Machine

{% details Overview %}
- Originally developed by Vapnik and collaborators as a linear classifier. 
- Could be modified to support non-linear classification by mapping into high-dimensional spaces. 
- Problem statement:
    - We want to separate `+` from `-` using a line. 
    - Training examples: 
  
    {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/06.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
  
    - Each example `i`:
  
    {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/07.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
    {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/08.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
  
    - Inner product:
    {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/09.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

- Which is the best linear separate defined by w?

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/10.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

{% enddetails %}
{% details Support Vector Machine: largest margin %}

- Distance from the separating line corresponds to the **confidence** of the prediction. 
- For example, we are more sure about the class of `A` and `B` than of `C`. 

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/11.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

- Margin definition:

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/12.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
{% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/13.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

- Maximizing the margin while identifying `w` is good according to intuition, theory, and practice. 

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/14.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

- A math question: how do you narrate this equation?

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/15.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

{% enddetails %}
{% details Support Vector Machine: what is the margin? %}

- Slide from the book

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/16.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

- Notation:
  - `Gamma` is the distance from point A to the linear separator L: `d(A,L) = |AH|`
  - If we select a random point M on line L, then d(A,L) is the projection of AM onto vector `w`. 
  - [Project](https://mathworld.wolfram.com/Projection.html)
  - If we assume the normalized Euclidean value of `w`, `|w|`, is equal to one, that bring us to 
  the result in the slide. 
- In other words, maximizing the margin is directly related to how `w` is chosen.
- For the *i<sup>th</sup>* data point:

  {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/17.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}.

{% enddetails %}
{% details Some more math ... %}

  {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/18.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
  - After some more mathematical manipulations:
  {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/19.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
  - Everything comes back to an optimization problem on `w`:
  {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/20.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
  {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/21.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}


{% enddetails %}
{% details SVM: Non-linearly separable data %}

  {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/22.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}
  - For each data point:
    - If margin greater than 1, don't care. 
    - If margin is less than 1, pay linear penalty. 
  - Introducing slack variables:

  {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/23.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

  {% include figure.liquid loading="eager" path="assets/img/courses/csc467/10-svm/24.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}


{% enddetails %}
