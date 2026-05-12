---
layout: lecture
pretty_table: true
order: 2
title: Frequent Itemsets
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
  - name: Association rule discovery
  - name: Definition of a frequent itemsets.
  - name: Finding frequent itemsets
  - name: A-Priori algorithm.
  - name: PCY (Park-Chen-Yu) Algorithm
  - name: 'SON: Savasere-Omiecinski-Navathe'
---
# Frequent Itemsets


## Association rule discovery

{% details Overview %}

- Example motivation: supermarket shelf management 
- Goal:
    - Identify items that are bought together by sufficiently many customers
- Approach: Process the sales data collected with barcode scanners to find dependencies 
among items
- Example:
    - If someone buys diaper and milk, then he/she is likely to buy beer
{% enddetails %}
{% details The market-basket model %}

- Describe a common form of many-to-many relationship between two kinds of objects. 
- A large set of `items`. e.g.: things sold in a supermarket. 
- A large set of `baskets`
    - each of which is a small set of items. e.g.: things 
    one customer buys on one trip to the supermarket. 
- Number of `baskets` cannot fit into memory. 
- Want to discover `association` rule:
    - People who bought {x,y,z} tend to buy {v,w}
    - Amazon's recommendation
{% enddetails %}
{% details Example applications %}

- Baskets = sets of products someone bought in one trip to the store; Items = products
    - Real market baskets: Chain stores keep TBs of data about what customers buy together
        - Tells how typical customers navigate stores, lets them position tempting items
        - Suggests tie-in `tricks`, e.g., run sale on diapers and raise the price of beer
        - Need the rule to occur frequently, or no monetary benefit
- Baskets = sentences; Items = documents containing those sentences
    - Items that appear together too often could represent plagiarism
    - Notice items do not have to be `in` baskets
- Baskets = patients; Items = drugs and side-effects
    - Has been used to detect combinations of drugs that result in particular 
    side-effects
    - But requires extension: Absence of an item needs to be observed as well as presence

---
{% enddetails %}
## Definition of a frequent itemsets.

{% details Definition %}

- A set of items that appears in many baskets is said to be `frequent`. 
- Assume a value `s`: *support threshold*. 
- If `I` is a set of items. 
    - The `support` for `I` is the number of baskets in which `I` is a subset. 
- `I` is frequent if its support is `s` or higher. 
{% enddetails %}
{% details Example of frequent itemsets %}
<a id="example-of-frequent-itemsets"></a>
- Items = {milk, coke, pepsi, beer, juice}
- Observed baskets:
    - B1: m,c,b
    - B2: m,p,j
    - B3: m,b
    - B4: c,j
    - B5: m,p,b
    - B6: m,c,b,j
    - B7: c,b,j
    - B8: b,c
- Support value `s` = 3 (items appear in at least three baskets)
- Frequent itemsets:
    - {m} appears 5 times in baskets: B1, B2, B3, B6, B6
    - {c} appeats 5 times in baskets: B1, B4, B6, B7, B8
    - {b} appears 6 times in baskets: B1, B3, B5, B6, B7, B8
    - {j} appears 4 times in baskets: B2, B4, B6, B7
    - Pair {m,b} appears 4 times in baskets: B1, B3, B5, B6
    - Pair {b,c} appears 4 times in baskets: B1, B6, B7, B8
    - Pair {c,j} appears 3 times in baskets: B4, B6, B7
{% enddetails %}
{% details Association rules %}

- `If-then` rules about the contents of baskets. 
- Notation ${i_1, i_2, ..., i_k} \rightarrow j$ means
    - If a basket contains all of items $i_1,...,i_k$ then it is **likely** to contain item $j$.
- `Confidence` of this association rule is the probability of having item $j$ in a basket given that basket already contained items ${i_1,...,i_k}$.
    - The fraction of the basket with ${i_1,...,i_k}$ that also contain j. 
- Example:
    - Given the following baskets:
        - B1: m,c,b
        - B2: m,p,j
        - B3: m,b
        - B4: c,j
        - B5: m,p,b
        - B6: m,c,b,j
        - B7: c,b,j
        - B8: b,c
    - An association rule ${m,b} \rightarrow c$ represents the relationship between having item $c$ and having both items $m$ and $b$. 
        - There are four baskets containing both $m$ and $b$: B1, B3, B5, B6
        - Out of these four baskets, two baskets also contain $c$: B1, B6
        - The confidence of this association rule is: $C = \frac{2}{4} = 0.5$
{% enddetails %}
{% details Interesting association rules %}

- Not all high-confidence rules are interesting
- The rule $X \rightarrow milk$ may have high confidence for many itemsets X, because milk 
is just purchased very often (independent of X) and the confidence will be high.
    - Not interesting!
- Interest of an association rule $I \rightarrow j$: difference between its confidence and the 
fraction of baskets that contain j
- Interesting rules are those with high positive or negative interest values (usually above 0.5)
- Example:
    - Given the following baskets:
        - B1: m,c,b
        - B2: m,p,j
        - B3: m,b
        - B4: c,j
        - B5: m,p,b
        - B6: m,c,b,j
        - B7: c,b,j
        - B8: b,c
    - An association rule: ${m,b} \rightarrow c$ has confidence $C = \frac{2}{4} = 0.5$
    - Since item $c$ apepars in 5 out of the total 8 baskets, fraction of baskets that contains $c$ is $\frac{5}/{8} = 0.625$.
    - Association rule interest is: $|0.5-5/8| = 0.125$
        - This association rule is not very interesting!
{% enddetails %}
{% details Finding association rules %}

- Problem: Find all association rules with support greater than **s** and confidence greater than **c**.
    - Note: Support of an association rule is the support of the set of items on the left side
- Hard part: Finding the frequent itemsets!
    - If ${i_1, i_2,…, i_k} \rightarrow j$ has high support and confidence, 
    then both ${i_1, i_2,…, i_k}$ and ${i_1, i_2,…,i_k, j}$ will be “frequent”
{% enddetails %}
{% details Mining association rules %}

- Step 1: Find all frequent itemsets I
- Step 2: Rule generation
    - For every subset A of I,  generate a rule $A \rightarrow I | A$ 
        - Since I  is frequent, A is also frequent
        - Variant 1: Single pass to compute the rule confidence
        $confidence(A,B \rightarrow C,D) = support(A,B,C,D) / support(A,B)$
        - Variant 2: Observation: If $A,B,C \rightarrow D$ is below confidence, so is $A,B \rightarrow C,D$
            - Can generate **bigger** rules from smaller ones! 
    - Output the rules above the confidence threshold
{% enddetails %}
{% details Example %}
- Given the following baskets:
    - B1: m,c,b
    - B2: m,p,j
    - B3: m,b
    - B4: c,j
    - B5: m,p,b
    - B6: m,c,b,j
    - B7: c,b,j
    - B8: b,c
- We have the following parameters:
    - Support threshold $s = 3$: We want frequent itemsets that appear at least three times or higher.
    - Association rule confidence $c = 0.75$: We want association rules with confience threshold at least 0.75 or higher. 
- Given the support threshold $s=3$, we have the following frequent itemsets: 
    - {b,m}, {b,c}, {c,m}, {c,j}, {m,c,b}
- Based on these itemsets, we can generate the following rules:
    
    {% details $b \rightarrow m$ %}

- Item $b$ appears in 6 baskets: B1, B3, B5, B6, B7, B8
- Out of these baskets, 4 of them contains $m$: B1, B3, B5, B6
- Confidence $C = \frac{4}{6} = 0.6667$
- This is below confidence threshold

    {% enddetails %}
    {% details $m \rightarrow b$ %}

- Item $m$ appears in 5 baskets: B1, B2, B3, B5, B6
- Out of these baskets, 4 of them contains $b$: B1, B3, B5, B6
- Confidence $C = \frac{4}{5} = 0.8$
- Basket fraction of $b$ is $\frac{6}{8} = 0.75$
- Interest = $$|0.8-0.75| = 0.05$ (not very interesting!)

    {% enddetails %}
    {% details $b \rightarrow c$ %}

- Item $b$ appears in 6 baskets: B1, B3, B5, B6, B7, B8
- Out of these baskets, 4 of them contains $c$: B1, B6, B7, B8
- Confidence $C = \frac{4}{6} = 0.6667$
- Basket fraction of $c$ is $\frac{4}{8} = 0.5$
- Interest = $$|0.6667-0.5| = 0.1667$ (not very interesting!)

    {% enddetails %}
    {% details $c \rightarrow b$ %}

- Item $c$ appears in 5 baskets: B1, B4, B6, B7, B8
- Out of these baskets, 4 of them contains $b$: B1, B6, B7, B8
- Confidence $C = \frac{4}{5} = 0.8$
- Basket fraction of $b$ is $\frac{6}{8} = 0.75$
- Interest = $$|0.8-0.75| = 0.15$ (not very interesting!)

    {% enddetails %}
    {% details $b \rightarrow c,m$ %}

- Item $b$ appears in 6 baskets: B1, B3, B5, B6, B7, B8
- Out of these baskets, 2 of them contains both $c$ and $m$: B1, B6
- Confidence $C = \frac{2}{6} = 0.3333$
- Basket fraction of the pair $m$ and $c$ is $\frac{2}{8} = 0.25$
- Interest = $$|0.3333-0.25| = 0.08$ (not very interesting!)x

    {% enddetails %}
    {% details $b,c \rightarrow m$ %}

- Pair $b$ and $c$ appears in 4 baskets: B1, B6, B7, B8
- Out of these baskets, 2 of them contains $m$: B1, B6
- Confidence $C = \frac{2}{4} = 0.5$
- Basket fraction of $m$ is $\frac{5}{8} = 0.625$
- Interest = $$|0.5-0.625| = 0.125$ (not very interesting!)

    {% enddetails %}
    {% details $b,m \rightarrow c$ %}

- Item $b$ and $m$ appears in 4 baskets: B1, B3, B5, B6
- Out of these baskets, 2 of them contains $m$: B1, B6
- Confidence $C = \frac{2}{4} = 0.5$
- Basket fraction of $c$ is $\frac{4}{8} = 0.5$
- Interest = $$|0.5-0.5| = 0$ (not very interesting!)

    {% enddetails %}
- Exercise: Identify whether the remaining association rules of {c,m}, {c,j}, and {m,c,b} meet the confidence threshold. If they do, identify if they are interesting!

---
{% enddetails %}
## Finding frequent itemsets

{% details Computation model %}
- Back to finding frequent itemsets
- Typically, data is kept in flat files rather than in a database system:
    - Stored on disk
    - Stored basket-by-basket
    - Baskets are small but we have many baskets and many items
        - Expand baskets into pairs, triples, etc. as you read baskets
        - Use k nested loops to generate all sets of size k
{% enddetails %}
{% details Computational cost %}
- The true cost of mining disk-resident data is usually the number of disk I/Os
- In practice, association-rule algorithms read the data in passes: all baskets read in each pass.
- We measure the cost by the number of passes an algorithm makes over the data
{% enddetails %}
{% details Main-memory bottleneck %}
- For many frequent-itemset algorithms, main-memory is the critical resource.
- As we read baskets, we need to count something, e.g., occurrences of pairs of items
- The number of different things we can count is limited by main memory
    - Swapping counts in/out is a disaster
{% enddetails %}
{% details Finding frequent pairs %}
- The hardest problem often turns out to be finding the frequent 
pairs of items ${i_1, i_2}$.
    - Why? Freq. pairs are common, freq. triples are rare, and frequent sets with higher item counts are much rarer!
- Let’s first concentrate on pairs, then extend to larger sets
- The approach:
    - We always need to generate all the itemsets
    - But we would only like to count (keep track) of those itemsets that in the end turn out to be frequent
{% enddetails %}
{% details Naive approach %}
- Read file once, counting in main memory the occurrences of each pair:
    - From each basket of n items, generate its $\frac{n(n-1)}{2}$ pairs by two nested loops
- Fails if the square of number of items exceeds main memory
    - Remember: number of items can be 100K (Wal-Mart) or 10B (Web pages)
    - Suppose $10^5$ items, counts are 4-byte integers
    - Number of pairs of items: $10^{5}(10^{5}-1)/2 = 5*10^9$
    - Therefore, $2*10^{10}$, or 20 GB of memory, is needed.
{% enddetails %}
{% details Counting pairs in memory %}

{% details Approach 1: Count all pairs using a matrix %}


- Requires 4 bytes per pair
- If n = total number items
    - Count pair of items {i, j} only if $i \leq j$
    - Keep pair counts in lexicographic order: 
        - {1,2}, {1,3},…, {1,n}, {2,3}, {2,4},…,{2,n}, {3,4},…
    - Pair {i, j} is at position (i –1)(n – i/2) + j –1
    - Total number of pairs n(n –1)/2; total bytes= $2n^2$

{% enddetails %}
{% details Approach 2: Keep a table of triples [i, j, c] %}


- The count of the pair of items {i, j} is c.
- If integers and item ids are 4 bytes, we need approximately 
12 bytes for pairs with count > 0
- Plus some additional overhead for the hashtable
- **but only for pairs with count > 0**
- Beats Approach 1 if less than 1/3 of possible pairs actually occur

{% enddetails %}
---
{% enddetails %}
## A-Priori algorithm.

{% details Overview %}

- Limit the need for main memory.
- Key idea: `monotonicity`
    - If a set of items I appears at least `s` times, so does every subset J
    of I. 
- Contrapositive: If an item `i` does not appear in `s` baskets, then no 
pair containing `i` can appear in s baskets. 
{% enddetails %}
{% details A-Priori algorithm %}

- Pass 1: read baskets and count the item occurrences. Only keep items 
that appear at least `s` times - `frequent items`. 
    - Requires only amount of memory proportional to number of items
- Pass 2: read baskets again and only count in main memory only those 
pairs whose both items were found to be frequent from Pass 1. 
    - Requires memory proportional to square of frequent items only (for counts)
    - Plus a list of the frequent items (so you know what must be counted)
- Repeat the process with increasing number of items added to only sets 
found to be `frequent`. 
{% enddetails %}
{% details Frequent triples %}

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/07-frequent-items/01.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

- For each k, we construct two sets of k-tuples  (sets of size k):
    - $C_k$ = candidate k-tuples = those that might be frequent sets 
    (support > s) based on information from the pass for k–1
    - $L_k$ = the set of truly frequent k-tuples
{% enddetails %}
{% details Example %}

- Review the [sequential implementation of A-Priori](https://colab.research.google.com/drive/1lJR-8yEWn_mQoQ8_f0NmKc5oDFAYTwc0?usp=sharing)
- Confirm that the output matches with the example in [Section 2.2](#example-of-frequent-itemsets).
- Question: How to turn this sequential implementation into the mapreduce programming paradigm for Spark (See [Section 6](#son-savasere-omiecinski-navathe))?

---
{% enddetails %}
## PCY (Park-Chen-Yu) Algorithm

{% details Observation %}
- Observation: In pass 1 of A-Priori, most memory is idle
    - We store only individual item counts
    - Can we use the idle memory to reduce 
    memory required in pass 2?
- Pass 1 of PCY: In addition to item counts, maintain a hash table with 
as many buckets as fit in memory 
    - Keep a `count` for each bucket into which `pairs` of items are hashed
    - For each bucket just keep the count, not the actual 
    pairs that hash to the bucket!
{% enddetails %}
{% details PCY Algorithm - First Pass %}

```
FOR (each basket) :
    FOR (each item in the basket) :
        add 1 to item’s count;
    FOR (each pair of items) :
        hash the pair to a bucket;
        add 1 to the count for that bucket;
```

- Few things to note:
    - Pairs of items need to be generated from the input 
    file; they are not present in the file
    - We are not just interested in the presence of a pair, 
    but we need to see whether it is present at least `s` (support) times
- If a bucket contains a frequent pair, then the bucket is surely frequent 
    - However, even without any frequent pair, a bucket can still be frequent 
- For a bucket with total count less than s, none of its pairs can be frequent
- Pairs that hash to this bucket can be eliminated as candidates (even if the 
pair consists of 2 frequent items)
{% enddetails %}
{% details PCY Algorithm - Second Pass %}
- Before the second pass
    - Replace the buckets by a bit-vector
    - 1 means the bucket count exceeded the support `s` 
    (call it a frequent bucket); 0 means it did not.   
    - 4-byte integer counts are replaced by bits, 
    so the bit-vector requires 1/32 of memory
    - Also, decide which items are frequent and 
    list them for the second pass
- The second pass
    - Count all pairs {i,j} that meet the 
    conditions for being a candidate pair:
        - Both i and j are frequent items
        - The pair {i,j} hashes to a bucket whose bit in the bit vector 
        is 1 (i.e., a frequent bucket)
    - Both conditions are necessary for the pair to have a chance of 
    being frequent

{% include figure.liquid loading="eager" path="assets/img/courses/csc467/07-frequent-items/pcy.png" class="img-fluid rounded z-depth-1 mx-auto d-block" max-width="50%" zoomable=true %}

---
{% enddetails %}
## SON: Savasere-Omiecinski-Navathe

{% details Overview %}
- Under two passes.
- Adaptable to a distributed data model (mapreduce). 
- Repeatedly read small subsets of the baskets into main memory 
and perform `a-priori` on these subsets, using a support that is
equal to the main support divided by the total numbers of subsets. 
- Aggregate all candidate itemsets and determine which are frequent 
in the entire set. 
{% enddetails %}
{% details SON: MapReduce Phase 1 %}
- Find candidate itemsets
- Map: Take the assigned subset of the baskets and find the
itemsets frequent in the subset. 
    - Lower the support threshold from s to ps if each Map task 
    gets fraction $p$ ($p$ < 1) of the total input file. 
    - The output is a set of key-value pairs (F, 1),
    where F is a frequent itemset from the sample. The value is always 1 
    and is irrelevant.
- Reduce: Each Reduce task is assigned a set of keys, which
are itemsets. The value is ignored, and the Reduce task simply produces 
those keys (itemsets) that appear one or more times. 
- The output of the first Reduce function is the candidate itemsets.
{% enddetails %}
{% details SON: MapReduce Phase 2 %}
- Find true frequent itemsets
- Map: The Map tasks for the second Map function take 
all the output from the first Reduce Function (the candidate itemsets) 
and a portion of the input data file. 
    - Each Map task counts the number of occurrences of each of the candidate 
    itemsets among the baskets in the portion of the dataset that it was assigned. 
    - The output is a set of key-value pairs (C, v), where C is one of the 
    candidate sets and v is the support for that itemset among the baskets 
    that were input to this Map task.
- Reduce: The Reduce tasks take the itemsets they are given as keys 
and sum the associated values. 
    - The result is the total support for unique itemsets (the keys)
    - Those itemsets whose sum of values is at least `s` are frequent 
    in the whole dataset, so the Reduce task outputs these itemsets.
{% enddetails %}
