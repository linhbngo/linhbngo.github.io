---
layout: lecture
pretty_table: true
collection: csc530
course: CSC 530: Data Structures
title: "Minimum Range Query"
toc:
  - name: Minimum Range Queries
  - name: Most Beautiful Item for Each Query
  - name: Hybrid Strategies
  - name: Find the Scope of All Prefixes of an Array
  - name: Extras on Block Decomposition
---
# Minimum Range Query


## Minimum Range Queries

[Presentation](data/slide00_rmq.pdf)


## Most Beautiful Item for Each Query

{% details Problem description %}

[Most Beautiful Item for Each Query](https://leetcode.com/problems/most-beautiful-item-for-each-query/description/)

{% enddetails %}
{% details Initial processing %}

- Sort items array
- Extract price and beauty into two arrays but maintain relative indices

```java linenums="1"
import java.util.Arrays;
class Solution {
    public int[] maximumBeauty(int[][] items, int[] queries) {
        Arrays.sort(items, (a, b) -> Integer.compare(a[0], b[0]));

        // get the unique prices and max beauty for each unique price
        int[] tmpPrices = new int[items.length];
        int[] tmpBeauty = new int[items.length];
        tmpPrices[0] = items[0][0];
        tmpBeauty[0] = items[0][1];
        int pCount = 0;
        for (int i = 1; i < items.length; i++ ) {
            if (items[i][0] == tmpPrices[pCount]) {
                if (items[i][1] > tmpBeauty[pCount]) {
                    tmpBeauty[pCount] = items[i][1];
                }
            }
            else {
                pCount++;
                tmpPrices[pCount] = items[i][0];
                tmpBeauty[pCount] = items[i][1];
            }
        }

        // Perform RMQ
        int nq = queries.length;
        return res;
    }
}
```

{% enddetails %}
{% details Block decomposition %}


```java linenums="1"
import java.util.Arrays;

class Solution {
    public int[] maximumBeauty(int[][] items, int[] queries) {
        Arrays.sort(items, (a, b) -> Integer.compare(a[0], b[0]));

        // get the unique prices and max beauty for each unique price
        int[] tmpPrices = new int[items.length];
        int[] tmpBeauty = new int[items.length];
        tmpPrices[0] = items[0][0];
        tmpBeauty[0] = items[0][1];
        int pCount = 0;
        for (int i = 1; i < items.length; i++ ) {
            if (items[i][0] == tmpPrices[pCount]) {
                if (items[i][1] > tmpBeauty[pCount]) {
                    tmpBeauty[pCount] = items[i][1];
                }
            }
            else {
                pCount++;
                tmpPrices[pCount] = items[i][0];
                tmpBeauty[pCount] = items[i][1];
            }
        }
        // refine data
        int[] prices = new int[pCount + 1];
        int[] beauty = new int[pCount + 1];
        for (int i = 0; i < prices.length; i++ ) {
            prices[i] = tmpPrices[i];
            beauty[i] = tmpBeauty[i];
        }

        // block approach
        int n = pCount + 1;
        int b = (int)Math.ceil(Math.sqrt(n));
        int nBlocks = (int)Math.ceil(1.0 * n/b);
        int[] maxBlock = new int[nBlocks];

        // find max at each block
        for (int i = 0; i < nBlocks; i++) {
            int maxBeauty = 0;
            for (int j = 0; j < b; j++) {
                int pos = i * nBlocks + j;
                if (pos >= n) break;
                if (beauty[pos] > maxBeauty)
                    maxBeauty = beauty[pos];
            }
            maxBlock[i] = maxBeauty;
        } 

        // Perform RMQ
        int nq = queries.length;
        int[] res = new int[nq];
        for (int i = 0; i < nq; i++) {
            res[i] = 0;
            for (int j = 0; j < n; j++) {
                if (prices[j] > queries[i]) break;
                int bIndex = j / b;
                for (int localB = 0; localB < bIndex; localB++) {
                    if (res[i] < maxBlock[localB]) res[i] = maxBlock[localB];
                }
                int maxBlockIndex = (bIndex + 1) * b;
                for (int localB = bIndex * b; localB < maxBlockIndex && localB < n; localB ++) {
                    if (prices[localB] > queries[i]) break;
                    if (res[i] < beauty[localB]) res[i] = beauty[localB];
                }
            }
        }

        return res;
    }
}
```
{% enddetails %}
## Hybrid Strategies

{% details Hybrid strategies %}

- Split the input into blocks of size b.
- Form an array of the block minima.
- Construct a “summary” RMQ structure over the block minima.
- Construct “block” RMQ structures for each block.
- Aggregate the results together.

{% include figure.liquid path="assets/img/courses/csc530/rmq/hybrid-1.png" width="50%" zoomable=true %}
{% include figure.liquid path="assets/img/courses/csc530/rmq/hybrid-2.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Runtime analysis %}

- Suppose
    - Summary RMQ: $<p_{1}(n), q_{1}(n)>$
    - Block RMQ: $<p_{2}(n), q_{2}(n)>$
    - Total size: n
    - Block size: b
- Preprocessing time
    - $\bigO(n)$ time to compute the minima for each block.
    - $\bigO(p_{1}(n/b))$ time to construct the summary RMQ on the minima
    - $\bigO((n/b)p_{2}(b))$ tim to construct the block RMQs
    - Total: $\bigO(n) + \bigO(p_{1}(n/b)) + \bigO((n/b)p_{2}(b))$ 
- Query time
    - $\bigO(q_{1}(n/b))$ time to query the summary RMQ
    - $\bigO(q_{2}(b))$ tim to query the block RMQs

{% enddetails %}
{% details Block decomposition and precomputed table %}


```java linenums="1"
import java.util.Arrays;

class Solution {
    public int[] maximumBeauty(int[][] items, int[] queries) {
        Arrays.sort(items, (a, b) -> Integer.compare(a[0], b[0]));

        // get the unique prices and max beauty for each unique price
        int[] tmpPrices = new int[items.length];
        int[] tmpBeauty = new int[items.length];
        tmpPrices[0] = items[0][0];
        tmpBeauty[0] = items[0][1];
        int pCount = 0;
        for (int i = 1; i < items.length; i++ ) {
            if (items[i][0] == tmpPrices[pCount]) {
                if (items[i][1] > tmpBeauty[pCount]) {
                    tmpBeauty[pCount] = items[i][1];
                }
            }
            else {
                pCount++;
                tmpPrices[pCount] = items[i][0];
                tmpBeauty[pCount] = items[i][1];
            }
        }
        // refine data
        int[] prices = new int[pCount + 1];
        int[] beauty = new int[pCount + 1];
        for (int i = 0; i < prices.length; i++ ) {
            prices[i] = tmpPrices[i];
            beauty[i] = tmpBeauty[i];
        }

        // block approach
        int n = pCount + 1;
        int b = (int)Math.ceil(Math.sqrt(n));

        int nBlocks = (int)Math.ceil(1.0 * n/b);
        int[] maxBlock = new int[nBlocks];

        // find max at each block
        for (int i = 0; i < nBlocks; i++) {
            int maxBeauty = 0;
            for (int j = 0; j < b; j++) {
                int pos = i * nBlocks + j;
                if (pos >= n) break;
                if (beauty[pos] > maxBeauty)
                    maxBeauty = beauty[pos];
            }
            maxBlock[i] = maxBeauty;
        } 

        // Perform RMQ
        int nq = queries.length;
        int[] sorted = queries.clone();
        Arrays.sort(sorted);
        HashMap<Integer, Integer> beautyMap = new HashMap<Integer, Integer>();
        int[] sortedRes = new int[nq];
        int prevMaxIndex = 0;
        int maxPrev = 0;
        for (int i = 0; i < nq; i++) {
            sortedRes[i] = 0;
            for (int j = prevMaxIndex; j < n; j++) {
                if (prices[j] > sorted[i]) {
                    prevMaxIndex = j;
                    break;
                }
                int bIndex = j / b;
                for (int localB = 0; localB < bIndex; localB++) {
                    if (sortedRes[i] < maxBlock[localB]) sortedRes[i] = maxBlock[localB];
                }
                int startLocalIndex = bIndex * b;
                int endLocalIndex = (bIndex + 1) * b;
                for (int localB = startLocalIndex; localB < endLocalIndex && localB < n; localB ++) {
                    if (prices[localB] > sorted[i]) break;
                    if (sortedRes[i] < beauty[localB]) sortedRes[i] = beauty[localB];
                }
            }
            if (sortedRes[i] < maxPrev) {
                sortedRes[i] = maxPrev;
            } else maxPrev = sortedRes[i];
            beautyMap.put(sorted[i],sortedRes[i]);
        }
        int[] res = new int[nq];
        for (int i = 0; i < nq; i++) {
            res[i] = beautyMap.get(queries[i]);
        }

        return res;
    }
}
```

{% enddetails %}
{% details Challenge: Implement Sparse Table solution %}


```java linenums="1"
// create a HashMap, using a String format for combining
// i and j: "i-j" as key
// Preprocessing:
// for each index i in the range
//     for each index j starting from i, increment by 1, 2, 4, ..., 2^k
//         Calculate minimum value using linear method, add to HashMap using "i-j" as key
// Queries: 
// for each index i in queries
//     Access the minimum values from range [0,2^k-1] and [i - 2^k + 1, i] using the HashMap
//     Update values in the result queries.     
```

{% enddetails %}
## Find the Scope of All Prefixes of an Array

{% details Problem description %}

[Find the Scope of All Prefixes of an Array](https://leetcode.com/problems/find-the-score-of-all-prefixes-of-an-array/description/)

{% enddetails %}
{% details Questions %}

- Is this an RMQ problem?
- How do we apply a technique from RMQ

{% enddetails %}
## Extras on Block Decomposition

{% details Better but not good enough - as per Dan's suggestion %}

- Improved: 34/35 correct
- Still encounter time limit

```java linenums="1"
import java.util.Arrays;

class Solution {
    public int[] maximumBeauty(int[][] items, int[] queries) {
        Arrays.sort(items, (a, b) -> Integer.compare(a[0], b[0]));

        // get the unique prices and max beauty for each unique price
        int[] tmpPrices = new int[items.length];
        int[] tmpBeauty = new int[items.length];
        tmpPrices[0] = items[0][0];
        tmpBeauty[0] = items[0][1];
        int pCount = 0;
        for (int i = 1; i < items.length; i++ ) {
            if (items[i][0] == tmpPrices[pCount]) {
                if (items[i][1] > tmpBeauty[pCount]) {
                    tmpBeauty[pCount] = items[i][1];
                }
            }
            else {
                pCount++;
                tmpPrices[pCount] = items[i][0];
                tmpBeauty[pCount] = items[i][1];
            }
        }
        // refine data
        int[] prices = new int[pCount + 1];
        int[] beauty = new int[pCount + 1];
        for (int i = 0; i < prices.length; i++ ) {
            prices[i] = tmpPrices[i];
            beauty[i] = tmpBeauty[i];
        }

        // block approach
        int n = pCount + 1;
        int b = (int)Math.ceil(Math.sqrt(n));
        System.out.println("N and B: " + n + " " + b);

        int nBlocks = (int)Math.ceil(1.0 * n/b);
        int[] maxBlock = new int[nBlocks];

        // find max at each block
        int pos = 0;
        for (int i = 0; i < nBlocks; i++) {
            int maxBeauty = 0;
            for (int j = 0; j < b; j++) {
                //int pos = i * nBlocks + j;
                if (pos >= n) break;
                if (beauty[pos] > maxBeauty)
                    maxBeauty = beauty[pos];
                //System.out.println(i + "-" + j + " " + pos + "-" + maxBeauty + "-" + beauty[pos]);
                pos++;
            }
            maxBlock[i] = maxBeauty;
        } 

        // Perform RMQ
        int nq = queries.length;
        int[] res = new int[nq];
        for (int i = 0; i < nq; i++) {
            System.out.println("=========");
            res[i] = 0;
            int stopIndex = 0;
            for (int j = 0; j < n; j++) {
                if (prices[j] > queries[i]) {
                    break;
                }
                stopIndex = j;
            }

            int bIndex = stopIndex / b;
            for (int localB = 0; localB < bIndex; localB++) {
                if (res[i] < maxBlock[localB]) res[i] = maxBlock[localB];
            }
            int maxBlockIndex = (bIndex + 1) * b;
            for (int localB = bIndex * b; localB <= stopIndex; localB ++) {
                if (prices[localB] > queries[i]) break;
                if (res[i] < beauty[localB]) res[i] = beauty[localB];
            }
        }

        return res;
    }
}
```

{% enddetails %}
{% details Accepted, but not as good as hybrid %}

- Accepted
- Only better than 5.36%

```java linenums="1"
import java.util.Arrays;

class Solution {
    public int[] maximumBeauty(int[][] items, int[] queries) {
        Arrays.sort(items, (a, b) -> Integer.compare(a[0], b[0]));

        // get the unique prices and max beauty for each unique price
        int[] tmpPrices = new int[items.length];
        int[] tmpBeauty = new int[items.length];
        tmpPrices[0] = items[0][0];
        tmpBeauty[0] = items[0][1];
        int pCount = 0;
        for (int i = 1; i < items.length; i++ ) {
            if (items[i][0] == tmpPrices[pCount]) {
                if (items[i][1] > tmpBeauty[pCount]) {
                    tmpBeauty[pCount] = items[i][1];
                }
            }
            else {
                pCount++;
                tmpPrices[pCount] = items[i][0];
                tmpBeauty[pCount] = items[i][1];
            }
        }
        // refine data
        int[] prices = new int[pCount + 1];
        int[] beauty = new int[pCount + 1];
        for (int i = 0; i < prices.length; i++ ) {
            prices[i] = tmpPrices[i];
            beauty[i] = tmpBeauty[i];
        }

        // block approach
        int n = pCount + 1;
        int b = (int)Math.ceil(Math.sqrt(n));
        System.out.println("N and B: " + n + " " + b);

        int nBlocks = (int)Math.ceil(1.0 * n/b);
        int[][] maxBlock = new int[nBlocks][2];

        // find max at each block
        int pos = 0;
        for (int i = 0; i < nBlocks; i++) {
            int maxBeauty = 0;
            int maxPrice = 0;
            for (int j = 0; j < b; j++) {
                if (pos >= n) break;
                if (beauty[pos] > maxBeauty)
                    maxBeauty = beauty[pos];
                if (prices[pos] > maxPrice)
                    maxPrice = prices[pos];
                pos++;
            }
            maxBlock[i][0] = maxBeauty;
            maxBlock[i][1] = maxPrice;
        } 

        // Perform RMQ
        int nq = queries.length;
        int[] res = new int[nq];
        for (int i = 0; i < nq; i++) {
            System.out.println("=========");
            res[i] = 0;
            int bIndex = nBlocks - 1;
            for (int j = 0; j < nBlocks; j++) {
                if (maxBlock[j][1] > queries[i]) {
                    bIndex = j;
                    break;
                }
            }
            for (int localB = 0; localB < bIndex; localB++) {
                if (res[i] < maxBlock[localB][0]) res[i] = maxBlock[localB][0];
            }
            int maxBlockIndex = (bIndex + 1) * b;
            for (int localB = bIndex * b; localB <= maxBlockIndex && localB < n; localB ++) {
                if (prices[localB] > queries[i]) break;
                if (res[i] < beauty[localB]) res[i] = beauty[localB];
            }
        }
        return res;
    }
}     
```
{% enddetails %}
