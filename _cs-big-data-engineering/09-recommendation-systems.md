---
layout: lecture
pretty_table: true
order: 2
title: Recommendation Systems
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

# Recommendation Systems

## 1. Recommendations

### 1.1. Overview

- Shelf space is a scarce commodity for traditional retailers 
    - Also: TV networks, movie theaters,…
- Web enables near-zero-cost dissemination of information about products
    - From scarcity to abundance
- More choice necessitates better filters
    - Recommendation engines
    - How Into Thin Air made Touching the Void a bestseller: http://www.wired.com/wired/archive/12.10/tail.html

![](fig/14-recommendation/examples.png)

### 1.2. Types of recommendations
- Editorial and hand curated
    - List of favorites
    - Lists of “essential” items
- Simple aggregates
    - Top 10, Most Popular, Recent Uploads
- Tailored to individual users
    - Amazon, Netflix, …

### 1.3. Formal Model

- X = set of Customers
- S = set of Items

- Utility function u: $X \times S \rightarrow R$
    - R = set of ratings
    - R is a totally ordered set
    - e.g., 0-5 stars, real number in [0,1]

|        | Avatar  | LOTR  | Matrix  | Pirates |
| ------ | ------- | ----- | ------- | ------- |
| Alice  |  1      |       | 0.2     |         |
| Bob    |         | 0.5   |         |  0.3    |
| Carol  |  0.2    |       | 1       |         | 
| David  |         |       |         |  0.4    | 

{% details Key Problems %}

- Gathering `known` ratings for matrix
    - How to collect the data in the utility matrix
- Extrapolate unknown ratings from the known ones
    - Mainly interested in high unknown ratings
    - We are not interested in knowing what you don’t like but what you like
- Evaluating extrapolation methods
    - How to measure success/performance of recommendation methods

{% enddetails %}
{% details Gathering ratings %}

- Explicit
    - Ask people to rate items
    - Doesn’t work well in practice: people can’t be bothered
- Implicit
    - Learn ratings from user actions
        - E.g., purchase implies high rating
    - What about low ratings?

{% enddetails %}
{% details Extrapolating utilities %}

- Key problem: Utility matrix U is sparse
    - Most people have not rated most items
    - Cold start: 
        - New items have no ratings
        - New users have no history
- Three approaches to recommender systems:
    - Content-based
    - Collaborative
    - Latent factor based

{% enddetails %}
---

## 2. Content-based Recommender Systems

### 2.1. Main Idea
- Main idea: Recommend items to customer x similar to previous items rated highly by x
- Example:
    - Movie recommendations: Recommend movies with same actor(s), director, genre, …
    - Websites, blogs, news: Recommend other sites with `similar` content

    ![](fig/14-recommendation/main-idea.png)
   <figcaption>J. Leskovec, A. Rajaraman, J. Ullman: Mining of Massive Datasets</figcaption>


### 2.2. Item profiles
- For each item, create an item profile
- Profile is a set (vector) of features
    - Movies: author, title, actor, director,…
    - Text: Set of “important” words in document
- How to pick important features?
    - Usual heuristic from text mining is TF-IDF 
    (Term frequency * Inverse Doc Frequency)
    - Term … Feature
    - Document … Item

### 2.3. User profiles and prediction
- User profile possibilities:
    - Weighted average of rated item profiles
    - Variation: weight by difference from average rating for item
    - ...
- Prediction heuristic:
    - Given user profile $x$ and item profile $i$, estimate 
    
    $$
        u(x,i)=cos(x,i)=\frac{x \cdot i}{||x|| \times ||i||}
    $$
    
### 2.4. Pros and cons

- Pros:
    - No need for data on other users
        - No cold-start or sparsity problems
    - Able to recommend to users with unique tastes
    - Able to recommend new & unpopular items
        - No first-rater problem
    - Able to provide explanations
        - Can provide explanations of recommended items by listing content-features that caused an item to be recommended
- Cons:
    - Finding the appropriate features is hard
        - E.g., images, movies, music
    - Recommendations for new users
        - How to build a user profile?
    - Overspecialization
        - Never recommends items outside user’s content profile
        - People might have multiple interests
        - Unable to exploit quality judgments of other users
    
---

## 3. Collaborative Filtering

### 3.1. Overview
- Consider user x
- Find set N of other users whose ratings are `similar` to x’s ratings
- Estimate x’s ratings based on ratings of users in N

![](fig/14-recommendation/CF-overview.png)

### 3.2. How do we find similar users
- Assume:
    - Ratings are 1 to 3 stars
    - Two users:
        - $r_x=[*,\_,\_,*,***]$
        - $r_y=[*,\_,**,**,\_]$
- Jaccard similarity measure
    - $r_x={1,4,5}$ or $r_x={1,0,0,1,1}$
    - $r_y={1,3,4}$ or $r_x={1,0,1,1,0}$
    {% details Potential problem? %}

Ignores the value of the rating

    {% enddetails %}
- Cosine similarity measure
    - $r_x={1,0,0,1,3}$ 
    - $r_y={1,0,2,2,0}$ 

    $$
        sim(x,y)=cos(r_x,r_y)=\frac{r_x \cdot r_y}{||r_x|| \times ||r_y||}
    $$

    {% details Potential problem? %}

Treats missing ratings as `negative`

    {% enddetails %}
- Person correlation coefficient
    - $r_x={1,0,0,1,3}$ with average rating $\overline{r_x}$
    - $r_y={1,0,2,2,0}$ with average rating $\overline{r_y}$
    - $S_{xy}$ are items rated by both x and y
        - $r_{xs}={1,1}$ 
        - $r_{ys}={1,2}$ 

    $$
        sim(x,y) = \frac{\sum_{s \in S_{xy}}(r_{xs} - \overline{r_x})(r_{ys} - \overline{r_y})}{\sqrt{\sum_{s \in S_{xy}}(r_{xs} - \overline{r_x})^2}\sqrt{\sum_{s \in S_{xy}}(r_{ys} - \overline{r_y})^2}}
    $$

### 3.3. Example differences of similarity metrics

- HP: Harry Potter
- TW: Twilight
- SW: Star Wars

|   | HP1 | HP2 | HP3 | TW | SW1 | SW2 | SW3 |
| - | --- | --- | --- | -- | --- | --- | --- | 
| A |  4  |     |     | 5  | 1   |     |     |
| B |  5  | 5   |  4  |    |     |     |     |
| C |     |     |     | 2  | 4   | 5   |     |
| D |     | 3   |     |    |     |     |  3  |

{% details Immediate intuition %}

A is more similar to B than A is to C

{% enddetails %}
{% details Jaccard similarity %}

- $r_A={1,0,0,1,1,0,0}$ 
- $r_B={1,1,1,0,0,0,0}$ 
- $r_C={0,0,0,1,1,1,0}$
- $sim(A,B) = \frac{1}{5}$
- $sim(A,C) = \frac{2}{4}$
- A is more similar to C than to B!!!

{% enddetails %}
{% details Cosine similarity %}

- $r_A={4,0,0,5,1,0,0}$ 
- $r_B={5,5,4,0,0,0,0}$ 
- $r_C={0,0,0,2,4,5,0}$

$$
    sim(x,y)=cos(r_x,r_y)=\frac{r_x \cdot r_y}{||r_x|| \cdot ||r_y||}
$$

$$
    sim(A,B)=\frac{r_A \cdot r_B}{||r_A|| \cdot ||r_B||}=\frac{4 \times 5 + 0 \times 5 + 0 \times 4 + 5 \times 0 + 1 \times 0 + 0 \times 0 + 0 \times 0 }{\sqrt{4^2+5^2+1^2} \times \sqrt{5^2+5^2+4^2}}=0.380
$$

$$
    sim(A,C)=\frac{r_A \cdot r_C}{||r_A|| \cdot ||r_C||}=\frac{5 \times 2 + 1 \times 4}{\sqrt{4^2+5^2+1^2} \times \sqrt{2^2+4^2+5^2}}=0.322
$$

- A is more similar to B than to C!
- What else?

{% enddetails %}
{% details Normalization %}

- Sutract the row mean
    - This normalizes data and turns cosine similarity into Pearson correlation

$$
    sim(x,y)=cos(r_x,r_y)=\frac{r_x \cdot r_y}{||r_x|| \cdot ||r_y||}
$$

$$
    sim(x,y) = \frac{\sum_{s \in S_{xy}}(r_{xs} - \overline{r_x})(r_{ys} - \overline{r_y})}{\sqrt{\sum_{s \in S_{xy}}(r_{xs} - \overline{r_x})^2}\sqrt{\sum_{s \in S_{xy}}(r_{ys} - \overline{r_y})^2}}
$$

- $r_A={4,0,0,5,1,0,0}$ and $\overline{r_A}=\frac{10}{3}$
- $r_B={5,5,4,0,0,0,0}$ and $\overline{r_B}=\frac{14}{3}$
- $r_C={0,0,0,2,4,5,0}$ and $\overline{r_C}=\frac{11}{3}$
- $r_D={0,3,0,0,0,0,3}$ and $\overline{r_D}=3$


|   | HP1 | HP2 | HP3  | TW   | SW1  | SW2 | SW3 |
| - | --- | --- | ---- | ---- | ---- | --- | --- | 
| A | 2/3 |     |      | 5/3  | -7/3 |     |     |
| B | 1/3 | 1/3 | -2/3 |      |      |     |     |
| C |     |     |      | -5/3 | 1/3  | 4/3 |     |
| D |     | 0   |      |      |      |     |  0  |

- sim(A,B)=0.092
- sim(A,C)=-0.559

- A is more similar to B than to C!
- Because the value is also the correlation value:
    - A is very similar to B
    - A is very different from C


{% enddetails %}
### 3.4. Rating Predictions
- From similarity metric to recommendations:
    - Let $r_x$ be the vector of user x’s ratings
    - Let $N$ be the set of $k$ users most similar to $x$ who have rated item $i$
- Prediction for item $s$ of user $x$:

$$
r_{xi} = \frac{1}{k}\sum_{y \in N}r_{yi}
$$

$$
r_{xi} = \frac{\sum_{y \in N}s_{xy} \cdot r_{yi}}{\sum_{y \in N}s_{xy}}
$$

- Other approaches

### 3.5. Item-item collaborative filtering
- Another view: item-item
- For item i, find other similar items
- Estimate rating for item i based on ratings for similar items
- Can use same similarity metrics and prediction functions as in user-user model

    - $s_{ij}$: similarity of items $i$ and $j$
    - $r_{xj}$: rating of user $x$ on item $j$
    - $N(i;x)$: set items rated by $x$ similar to $i$ 

$$
r_{xi} = \frac{\sum_{j \in N(i;x)}s_{ij} \cdot r_{xj}}{\sum_{j \in N(i;x)}s_{ij}}
$$

### 3.6. Example: item to item

|       | $u_1$ | $u_2$ | $u_3$ | $u_4$ | $u_5$ | $u_6$ | $u_7$ | $u_8$ | $u_9$ | $u_{10}$ | $u_{11}$ | $u_{12}$ | 
| ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | -------- | -------- | -------- | 
| $m_1$ |   1   |       |   3   |       |       |   5   |       |       |   5   |          |     4    |          | 
| $m_2$ |       |       |   5   |    4  |       |       |   4   |       |       |     2    |     1    |     3    | 
| $m_3$ |   2   |   4   |       |    1  |   2   |       |   3   |       |   4   |     3    |     5    |          | 
| $m_4$ |       |   2   |   4   |       |   5   |       |       |   4   |       |          |     2    |          |
| $m_5$ |       |       |   4   |    3  |   4   |   2   |       |       |       |          |     2    |     5    |
| $m_6$ |   1   |       |   3   |       |   3   |       |       |   2   |       |          |     4    |          | 

{% details Estimate rating of movie 1 by user 5 %}


|       | $u_1$ | $u_2$ | $u_3$ | $u_4$ | $u_5$ | $u_6$ | $u_7$ | $u_8$ | $u_9$ | $u_{10}$ | $u_{11}$ | $u_{12}$ | 
| ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | -------- | -------- | -------- | 
| $m_1$ |   1   |       |   3   |       |   ??? |   5   |       |       |   5   |          |     4    |          |
| $m_2$ |       |       |   5   |    4  |       |       |   4   |       |       |     2    |     1    |     3    |
| $m_3$ |   2   |   4   |       |    1  |   2   |       |   3   |       |   4   |     3    |     5    |          | 
| $m_4$ |       |   2   |   4   |       |   5   |       |       |   4   |       |          |     2    |          |
| $m_5$ |       |       |   4   |    3  |   4   |   2   |       |       |       |          |     2    |     5    | 
| $m_6$ |   1   |       |   3   |       |   3   |       |       |   2   |       |          |     4    |          |


{% enddetails %}
{% details Identify movies similar to movie 1, rated by user 5 %}

- Pearson correlation for similarity calculation:
    - Movie 3
    - Movie 5

|       | $u_1$ | $u_2$ | $u_3$ | $u_4$ | $u_5$ | $u_6$ | $u_7$ | $u_8$ | $u_9$ | $u_{10}$ | $u_{11}$ | $u_{12}$ | $sim(1,m_i)$ |
| ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | -------- | -------- | -------- | ------------ |
| $m_1$ |   1   |       |   3   |       |   ??? |   5   |       |       |   5   |          |     4    |          |       1.0    |
| $m_2$ |       |       |   5   |    4  |       |       |   4   |       |       |     2    |     1    |     3    |     -0.18    |
| $m_3$ |   2   |   4   |       |    1  |   2   |       |   3   |       |   4   |     3    |     5    |          |      0.41    |  
| $m_4$ |       |   2   |   4   |       |   5   |       |       |   4   |       |          |     2    |          |     -0.10    |
| $m_5$ |       |       |   4   |    3  |   4   |   2   |       |       |       |          |     2    |     5    |     -0.31    |
| $m_6$ |   1   |       |   3   |       |   3   |       |       |   2   |       |          |     4    |          |      0.59    |

{% enddetails %}
{% details Similarity weights %}

- $s_{1,3} = 0.41$
- $s_{1,6} = 0.59$

|       | $u_1$ | $u_2$ | $u_3$ | $u_4$ | $u_5$ | $u_6$ | $u_7$ | $u_8$ | $u_9$ | $u_{10}$ | $u_{11}$ | $u_{12}$ | $sim(1,m_i)$ |
| ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | -------- | -------- | -------- | ------------ |
| $m_1$ |   1   |       |   3   |       |   ??? |   5   |       |       |   5   |          |     4    |          |       1.0    |
| $m_2$ |       |       |   5   |    4  |       |       |   4   |       |       |     2    |     1    |     3    |     -0.18    |
| $m_3$ |   2   |   4   |       |    1  |   2   |       |   3   |       |   4   |     3    |     5    |          |      0.41    |  
| $m_4$ |       |   2   |   4   |       |   5   |       |       |   4   |       |          |     2    |          |     -0.10    |
| $m_5$ |       |       |   4   |    3  |   4   |   2   |       |       |       |          |     2    |     5    |     -0.31    |
| $m_6$ |   1   |       |   3   |       |   3   |       |       |   2   |       |          |     4    |          |      0.59    |

{% enddetails %}
{% details Predict rating %}

- $s_{1,3} = 0.41$
- $s_{1,6} = 0.59$
- $r_{1,5} = \frac{0.41 * 2 + 0.59 * 3}{0.41 + 0.59} = 2.6$

|       | $u_1$ | $u_2$ | $u_3$ | $u_4$ | $u_5$ | $u_6$ | $u_7$ | $u_8$ | $u_9$ | $u_{10}$ | $u_{11}$ | $u_{12}$ | $sim(1,m_i)$ |
| ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | -------- | -------- | -------- | ------------ |
| $m_1$ |   1   |       |   3   |       |   2.6 |   5   |       |       |   5   |          |     4    |          |       1.0    |
| $m_2$ |       |       |   5   |    4  |       |       |   4   |       |       |     2    |     1    |     3    |     -0.18    |
| $m_3$ |   2   |   4   |       |    1  |   2   |       |   3   |       |   4   |     3    |     5    |          |      0.41    |  
| $m_4$ |       |   2   |   4   |       |   5   |       |       |   4   |       |          |     2    |          |     -0.10    |
| $m_5$ |       |       |   4   |    3  |   4   |   2   |       |       |       |          |     2    |     5    |     -0.31    |
| $m_6$ |   1   |       |   3   |       |   3   |       |       |   2   |       |          |     4    |          |      0.59    |

{% enddetails %}
### 3.7. CF: Common Practice
- Define similarity $s_{ij}$ of items $i$ and $j$
- Select k nearest neighbors $N(i; x)$
    - Items most similar to $i$, that were rated by $x$
- Estimate rating $r_{xi}$ as the weighted average: 

$$
r_{xi} = b_{xi} + \frac{\sum_{j \in N(i;x)}s_{ij} \cdot (r_{xj} - b_{xj})}{\sum_{j \in N(i;x)}s_{ij}}
$$

- $b_{xi}$: baseline estimate for $r_{xi}$
- $b_{xi} = \mu + b_x + b_i$
    - $\mu$ is overall mean rating
    - $b_x$ is the rating deviation of user $x$ (average rating minus overall mean rating)
    - $b_i$ is the rating deviation of movie $i$

### 3.8. CF: Pros and cons
- Pros:
    - Works for any kind of item
    - No feature selection needed
- Cons:
    - Cold Start:
        - Need enough users in the system to find a match
    - Sparsity: 
        - The user/ratings matrix is sparse
        - Hard to find users that have rated the same items
    - First rater: 
        - Cannot recommend an item that has not been previously rated
        - New items, Esoteric items
    - Popularity bias: 
        - Cannot recommend items to someone with unique taste 
        - Tends to recommend popular items
- Hybrids:
    - Implement two or more different recommenders and combine predictions
        - Perhaps using a linear model
    - Add content-based methods to collaborative filtering
        - Item profiles for new item problem
        - Demographics to deal with new user problem

### 3.9. Evaluation

![](fig/14-recommendation/cf_evaluation.png)

- Compare predictions with known ratings
- Root-mean-square error (RMSE)
    - $r_{xi}$: predicted
    - ${r^*}_{xi}$: true rating

    $$
    RMSE = \sqrt{\sum_{xi}(r_{xi} - {r^*}_{xi})^2}
    $$

- Precision at top 10: 
    - % of those in top 10
- Rank Correlation: 
    - Spearman’s correlation between system’s and user’s complete rankings

{% details Add data %}

- Leverage all the data
    - Don’t try to reduce data size in an effort to make fancy algorithms work
    - Simple methods on large data do best

- Add more data
    - e.g., add IMDB data on genres

- [More data beats better algorithms](http://anand.typepad.com/datawocky/2008/03/more-data-usual.html)

{% enddetails %}
---

## 4. The Netflix Prize

### 4.1. Training data
- Training data
    - 100 million ratings, 480,000 users, 17,770 movies
    - 6 years of data: 2000-2005
- Test data
    - Last few ratings of each user (2.8 million)
- Evaluation criterion: 
    - Root Mean Square Error
    - Netflix’s system RMSE: 0.9514
- Competition
    - 2,700+ teams
    - **$1 million** prize for 10% improvement on Netflix
- Data no longer available due to later researchers were able to extract personal information based on reviews. 

### 4.2. Winner: BellKor Recommender System
- [Y. Koren, Collaborative filtering with temporal dynamics, KDD 2009](data/cf_temporal_dynamics.pdf)
- Multi-scale modeling of the data: Combine top level, “regional” modeling of the data, with a refined, local view:
    - Global:
        - Overall deviations of users/movies
    - Factorization: 
        - Addressing “regional” effects
- Collaborative filtering: 
    - Extract local patterns

{% details Example: modeling local and global effects %}

- Global:
    - Mean movie rating: 3.7 stars
    - The Sixth Sense is 0.5 stars above avg.
    - Joe rates 0.2 stars below avg. 
    - Baseline estimation: Joe will rate The Sixth Sense 4 stars
- Local neighborhood (CF/NN):
    - Joe didn’t like related movie Signs
    - Final estimate: Joe will rate The Sixth Sense 3.8 stars

{% enddetails %}
### 4.3. Interpolation weights
$$
r_{xi} = b_{xi} + \frac{\sum_{j \in N(i;x)}s_{ij} \cdot (r_{xj} - b_{xj})}{\sum_{j \in N(i;x)}s_{ij}}
$$

{% details Problems %}

- Similarity measures are “arbitrary”
- Pairwise similarities neglect interdependencies among users 
- aking a weighted average can be restricting

{% enddetails %}
{% details Solution %}

Instead of $s_{ij}$ use $w_{ij}$ that we estimate directly from data

$$
r_{xi} = b_{xi} + \sum_{j \in N(i;x)}w_{ij}(r_{xj} - b_{xj})
$$

- $N(i;x)$ is set of movies rated by user x that are similar to movie i
- $w_{ij}$ is the interpolation weight (some real number)
- $w_{ij}$ models interaction between pairs of movies (it does not depend on user $x$)
- Goals:
    - Find $w_{ij}$ that minimize SSE (sum of squared errors) on training data!
        - Models relationships between item i and its neighbors j
    - $w_{ij}$ can be learned/estimated based on x and all other users that rated i

{% enddetails %}
### 4.4. Recommendations via Optimization
- Idea: Let’s set values w such that they work well on known (user, item) ratings
- How to find such values w?
- Idea: Define an objective function and solve the optimization problem
- Find $w{ij}$ that minimize SSE on training data! 
    - Think if w as a vector of numbers. 

$$
J(w)=\sum_{x,i} \left( \left[ b_{xi} + \sum_{j \in N(i;x)}w_{ij}(r_{xj} - b_{xj}) \right] - r_{xi} \right)^2
$$

### 4.5. Performance
- Optimization via gradient descent
    - Not there yet
![](fig/14-recommendation/netflix_1.png)


### 4.6. Latent factor models (singular value decomposition - SVD)"

- Utility matrix:

|   | HP1 | HP2 | HP3 | TW | SW1 | SW2 | SW3 |
| - | --- | --- | --- | -- | --- | --- | --- | 
| A |  4  |     |     | 5  | 1   |     |     |
| B |  5  | 5   |  4  |    |     |     |     |
| C |     |     |     | 2  | 4   | 5   |     |
| D |     | 3   |     |    |     |     |  3  |

- Idea:  
    - Users respond to a `small` number of features in movies: genres, actors, actresses, theme songs, etc.
    - We can break utility matrix M(n,m) into two matrices, U (n,d) and V (d,v)
        - U correponds to movies and features
        - V corresponds to features and users
    - Instead of estimating the rating on M, we estimate users' response toward features, and movies' relationship 
    with features. 
        - We can calculate the missing rating as a dot product of these two matrices. 
        - Optimization/estimation of U and V using Stochastic Gradient Descent. 

![](fig/14-recommendation/netflix_2.png)

### 4.7. Bringing everything together
- Baseline predictor
    - Separates users and movies
    - Benefits from insights into user’s behavior
    - Among the main practical contributions of the competition
- User-Movie interaction
    - Characterizes the matching between users and movies
    - Attracts most research in the field
    - Benefits from algorithmic and mathematical innovations

$$
r_{xi} = \mu + b_x + b_i + q_i \cdot p_x
$$

- Example
    - Mean rating: $\mu$ = 3.7
    - You are a critical reviewer: your ratings are 1 star lower than the mean: $b_x$ = -1
    - Star Wars gets a mean rating of 0.5 higher than average movie:  $b_i$ = + 0.5
    - Predicted rating for you on Star Wars:	= 3.7 -  1  +  0.5  = 3.2 

### 4.8. Additional details
- Sudden rise in the average movie rating (early 2004)
    - Improvements in Netflix 
    - GUI improvements
    - Meaning of rating changed
- Movie age
    - Users prefer new movies without any reasons
    - Older movies are just inherently better than newer ones

$$
r_{xi} = \mu + b_x(t) + b_i(t) + q_i \cdot p_x
$$

- Add temporal dependence

### 4.9. Still not there yet

![](fig/14-recommendation/netflix_3.png)

- Continuous calibration of models

![](fig/14-recommendation/netflix_4.png)
