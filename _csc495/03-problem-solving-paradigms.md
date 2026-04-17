---
layout: lecture
pretty_table: true
collection: csc495
title: "Problem solving paradigms"
toc:
  - name: Four Common Problem Solving Paradigms
  - name: Strategies
  - name: Improving Complete Search: Iterative Complete Search
  - name: Improving Complete Search: Looping and Pruning
  - name: Iterative Complete Search: Permutations
  - name: Recursive Complete Search: Backtracking
  - name: Challenges
  - name: Complete Search Tips:
  - name: Divide and Conquer (D&C):
  - name: D&C Binary Search: Uncommon Data Structures
  - name: D&C Binary Search: Binary Search the Answer
  - name: Challenges
  - name: Greedy
  - name: Challenges
  - name: Dynamic Programming (DP)
  - name: Dynamic Programming (DP): Example
  - name: Non DP Approaches
  - name: Top-down DP:
  - name: Bottom-up DP:
  - name: LeetCode example
---
# Problem solving paradigms

## Four Common Problem Solving Paradigms

- Complete Search (Brute Force)
- Divide and Conquer
- Greedy
- Dynamic Programming

Given a simple task involving an array A with up to 200K positive integers whose value can be up to 1M.

- Find the largest and small values in A.
  -  Complete Search: O(n)
- Find the k<sup>th</sup> smallest element in A
  - Complete Search: O(n<sup>2</sup>)
  - Divide and Conquer: O(nlog(n)) or O(n)
- Find two numbers in A that have the largest absolute difference
  - Complete Search: O(n<sup>2</sup>)
  - Greedy (largest gap is the difference between max and min): O(n)  
- Find the longest increasing subsequence of A
  - Complete Search: O(2<sup>n</sup>)
  - Greedy and D&C: O(nlog(k))
  - Dynamic Programming: O(n<sup>2</sup>) 




## Strategies

- Estimating expected run time. 
- Complete Search if quick and bug-free solution development is a possibility
  - Will have TLE but no WA

Problem size | Worst accepted algorithm 
------------ | ------------------------
≤ [10..11]   | O(n!), O(n<sup>6</sup>) 
≤ [17..19]   | O(2<sup>n</sup> * n<sup>2</sup>) 
≤ [18..22]   | O(2<sup>n</sup> * n) 
≤ [24..26]   | O(2<sup>n</sup>) 
≤ 100        | O(n<sup>4</sup>) 
≤ 450        | O(n<sup>3</sup>) 
≤ 1.5K       | O(n<sup>2.5</sup>) 
≤ 2.5K       | O(n<sup>2</sup>log(n)) 
≤ 10K        | O(n<sup>2</sup>) 
≤ 200K       | O(n<sup>1.5</sup>) 
≤ 4.5M       | O(nlog(n))
≤ 10M        | O(nlog(log(n))) 
≤ 100M       | O(n), O(log(n)), O(1) 




## Improving Complete Search: Iterative Complete Search

- [UVa Division](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=9&page=show_problem&problem=666)
- Summary: Find all pairs of 5-digit numbers that use the digits 0 through 9 each such that the first number divided
by the second number is equal to N with 2 ≤ N ≤ 79: `abdef/fghij = N`  
- Naive Complete Search: 
  - Both numbers are permuted from 10 digits (no replacement): 10! iterations ~ 3M
- Analysis:
  - Max possible value: 98,765
  - Denominator `fghij`: max value = 98,765 / N, which is at most 49,382
  - Instead of checking pairs, go through all possible values of `fghij` and check if `fghij * N` is a numbers whose digits 
  combining with `fghij`'s digits match 0 through 9 (bit masking technique):
    - Recall: to set (turn on) the bit at position `j`, use bitwise OR: `S = S | (1 << j)`
  - Time complexity: ~ 49,382 * 10 ~ 500K (comparing to 3M)

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=iterative_complete_search.java"></script>



## Improving Complete Search: Looping and Pruning

- [UVa Simple Equations](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2612)
- Summary: Find distinct integers x, y, and z such that
  - x + y + z = A
  - x * y * z = B
  - x<sup>2</sup> + x<sup>2</sup> + x<sup>2</sup> = C  
  - 1 ≤ A, B, C ≤ 10,000
  - Answer should prefer x with least value, then y. 
- Naive Complete Search: 
  - Worst case: 10000<sup>3</sup>
- Analysis:
  - With x<sup>2</sup> + x<sup>2</sup> + x<sup>2</sup> = C, we can deduce that x, y, z is between -100 and 100. 
    - Worst case: 200<sup>3</sup>
  - Further deduction: x, y, z ≤ B<sup>1/3</sup>, therefore one value is between -22 and 22. 
    - Worst case: 45 * 200<sup>2</sup>

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=prune_simple_equations.java"></script>

- Additional optimizations to scale loop size with input. 

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=prune_simple_equations_more.java"></script>




## Iterative Complete Search: Permutations

- [UVa 11742 Social Constraints](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2842)
- Summary: 
  - There are 0 ≤ n ≤ 8 movie goers, seating in n consecutive open seats. 
  - There are 0 ≤ m ≤ 20 seating constraints, where each constraint specifies two movie goers a and b has to be 
  at least c seats apart.
  - How many possible seating arrangements are there?
- Permutations: 
 - Have to search through all possible permutations and check if each permutation satisfies 
 - The problem of `next_permutation`. 
- Example:
  - [LeetCode's Next Permutation](https://leetcode.com/problems/next-permutation/)
<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=next_permutation.java"></script>
- Applying the technique:
  - I[LeetCode's Permutation Sequence](https://leetcode.com/problems/permutation-sequence/)




## Recursive Complete Search: Backtracking

- [UVa 00750 8 Queens Chess Problem](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=691)
- Summary: 
  - In chess it is possible to place eight queens on the board so that no one 
  queen can be taken by any other. 
  - Write a program that will determine all such possible arrangements for eight 
  queens given the initial position of one of the queens. 
- Naive complete search: 
  - Enumerate all possible combinations of 8 different cells out of 8x8 = 64 possible cells on a chess board. 
  - Runtime: C(64,8) = 64! / (8! * 56!) ~ 4B
  - Don't even think about it. 
- Naive row pruning:
  - Each Queen can only occupy one column. 
  - Runtime: 8<sup>8</sup> ~ 17M
  - Likely to be TLE
- Faster row/column pruning:
  - Each Queen control one row and one column.
  - Runtime: 8! ~ 40K
  - Fast enough but could be better. 
- Row/column/diagonal:
  - Queen cannot share diagonal lines.
  - Runtime: sub (8!)

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=00750.java"></script>




## Challenges

- Kattis: [Eight Queens](https://open.kattis.com/problems/8queens)
  - Simpler problem that focuses on data input and checking. 
- Kattis: [Queens](https://open.kattis.com/problems/queens)
  - A variety of both UVA and the Kattis' 8queens problem.
- LeetCode: [N-Queens](https://leetcode.com/problems/n-queens/).
 



## Complete Search Tips:

- Filtering versus Generating:
  - Filtering: 
    - examine  a lot (if not all) candidate solutions and choose the ones that are correct. 
    - written iteratively. 
  - Generating:
    - gradually build the solutions and immediately prune invalid partial solutions.
    - written recursively.
  - Filtering is easier to code but run slower. 
- Prune infeasible/inferior search space early. 
- Utilize symmetries.
- Pre-computation: generate lookup tables (data structures)
- Solve the problem backwards. 
- Data compression (bit masking).
- Optimize source code. 
- Use better data structures/algorithms.  



## Divide and Conquer (D&C):

- Divide the original problem into sub-problems, usually by half or nearly half. 
- Find (sub-)solutions for each of these sub-problems, which are now easier.
- If needed, combine the sub-solutions to get a complete solution for the main problem. 
- Most well-known: Binary Search



## D&C Binary Search: Uncommon Data Structures

- Common usage of Binary Search: to search a static sorted array.  
- Problem ([Thailand ICPC National Contest 2009](https://github.com/class-master/csc495/blob/master/data/ACM_Contest_2009.pdf))
  - Given a weighted tree of up to N vertices with one condition: `vertex values are increasing from root to leaves`.
    - The tree is not necessarily binary
  - For each of Q starting vertex, find an ancestor vertex closest to root who value is at least P. 
  - Input constraints:
    - 1 ≤ N ≤ 200000
    - 1 ≤ Q ≤ 100000
    - 1 ≤ P ≤ 2<sup>31</sup> - 1 
- Naive solution:
  - Starting from each given vertex `v`, move up the tree until we find the first vertex whose direct parent  has value less
  then P or until we reach root. 
  - Runtime (TLE): O(NQ)
- Better solution:
  - Traverse the tree once (`preorder-traversal`) and store the paths (node index and value). 
  - Within each path, the nodes are always sorted (special tree condition). 
  - If encountered node in query (query as array so node index is array index), binary research previous path to find answer. 
  - Runtime: O(N + Olog(N))




## D&C Binary Search: Binary Search the Answer

- [UVA: Through the Desert](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3086)
  - Analysis: 
    - Range of possible answer is between 0.000 and 1000.000 (10M possibilities).
  - Binary Search the Answer
    - If  `x` is the correct answer, then any value between 0.000 and `x` will not get the jeep to goal. 
    - On the other hand, the value between `x` and 1000.000 will possibly get you there.  
    - This is the `monotone` property that we need to find. 
- Problem ([LeetCode Contest 275 Maximum Running Time of N Computers](https://leetcode.com/problems/maximum-running-time-of-n-computers/))
  - Analysis:
    - Maximum possible simultaneous run time for all: `n`/`sum of all battery charges`.
    - Minimum possible simultaneous run time for all: `0`. 
    - If the computers can run simultaneously for `X` minutes, then they **may** run simultaneously for more than `X` minutes. 
    - If the computers cannot run simultaneously for `X` minutes, then they **definitely** cannot run simultaneously for more than `X` minutes.
    - Possible choices for minutes are limited/round numbers. 
    - Binary Search the Answer.
  <script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=maximum-running-time-of-n-computers.java"></script>



## Challenges

- Kattis: [Need for Speed](https://open.kattis.com/problems/speed)
 



## Greedy

- Make locally optimal choice at each step with the hope of eventually reaching the globally optimal solution. 
  - Sliding windows is an example of greedy technique.  
- Works for **some** cases, not for many others. 
- Required characteristics 
  - Optimal solution to the problem contains optimal solutions to the sub-problem  
  - Has greedy property: if we make the choice that seems like best at the moment and proceed to 
  the sub-problem, eventually we will reach the optimal solution.   
- Problem ([LeetCode Contest 275 Maximum Running Time of N Computers](https://leetcode.com/problems/maximum-running-time-of-n-computers/))

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=maximum-running-time-of-n-computers-greedy.java"></script>

<div class="mxgraph" style="max-width:100%;border:1px solid transparent;" data-mxgraph="{&quot;highlight&quot;:&quot;#0000ff&quot;,&quot;nav&quot;:true,&quot;resize&quot;:true,&quot;toolbar&quot;:&quot;zoom layers tags lightbox&quot;,&quot;edit&quot;:&quot;_blank&quot;,&quot;xml&quot;:&quot;&lt;mxfile host=\&quot;app.diagrams.net\&quot; modified=\&quot;2022-01-19T15:54:24.510Z\&quot; agent=\&quot;5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/97.0.4692.71 Safari/537.36\&quot; etag=\&quot;aGv4yR17Gvz8T97vfhGy\&quot; version=\&quot;16.1.2\&quot; type=\&quot;google\&quot;&gt;&lt;diagram id=\&quot;rJTc4IwxH4mLOic-fluw\&quot; name=\&quot;Page-1\&quot;&gt;5ZtRk5sqFMc/TR53R0SNeWzc3fbOvZ12up2520dWibGLkhKySfrpL0Y0EdzENtF46UNm4Sigv8MfDuCOYJBu3jO0mH+kESYj24o2I3g3sm1gAVv8yS1bafEtq7DELImkbW94TH7isqi0rpIIL2s3ckoJTxZ1Y0izDIe8ZkOM0XX9thkl9VYXKMaa4TFERLf+m0R8Xlh919rbP+Aknpctg/L9UlTeLA3LOYro+sAE70cwYJTyIpVuAkxyeiWXotzDG1erB2M4420KkNenn5/+/vb04+HGJ1+/Z+TH+5cbWcsrIiv5wvJh+bYkwOgqi3BeiTWC0/U84fhxgcL86lo4XdjmPCUiB0RylhASUELZriyczWZ2GAr7kjP6gg+uRN6z53riinwAzDjevPlmoOIlehqmKeZsK24pC3gSsexkTumD9d5jUJrmB85ypA3JPhJXNe8xioQk+QtUbSOoTupUodeOqt8VVdgt1cjFfuQ0UfXtZ+hdiGqFR1KtOuEJqrbVFVbHiM4KBzYEuCZQreaucgiw21EFdldYPRPGgKpzbhVcJ7DCzrCOTcAKHQVrywmruxnLNwGrow2tLUfWrqhOTKAKgRIHtJywupuxygf6n09Z7tCmLNDxGqun/joe2pwF9BArE9ldyhJxgkfEI0yfmUjFuxTiHLOk2Exwp+J1g/wnqgig/IkaA1EyENNh4MufkIV7pzlMgOR1r9TpZzTDiqukCZEkzkQ2FOCxsE9ztyQhIu/khTSJoryZxm5Q7ygX8CsoMUq/3vi6X22vz8gZtAhGlnO0yJPhipHtlKHwBfPTwtnD28mIJIsP1RWOeEJz/JMLgYXKpgQcuzrYpoFo0hlYPRyxNLLmdGxY79hOQ9zSxL+78UqPW4DB+L2B4bf18EYfV8zBPxkafj0KgubiF2HowPDbGn7HYPzu0PDre9euwfj9oeHX97g9c/FDMDT8+kptbDB+Z2j49U1z32D846Hh19ezE3PxO9bA8EM98AQGL3udoS17oR55ivHICmm6WAlgS3NdAdWDk4attUmvrtBDfhzF+FFmKeNzGtMMkfu9VcGyv+cfShfSP98x51v56RZacVr3XtFm3tBxjuK56IqF+NgLwGbgDBPEk9d6A034ZNHPNBFNH8Sr9q2iGnUTjiMWYy7LKW6oHuQMz+jrg6Vokv8l0G9G5aa2yUsG5ezWBbpWylVFP1rRY1aGc47Lyh0gT9nTWsquUrCeKkqYPPEo291QdyAY9+pBPexN0ebLKvuapPhQU+pBUVITncEuA8o6velof9Kry/TAuIcJStBi2yeRubFuq/y3vL5by4el4W4jWyhy28PcZ8xEn9q59MA3l5ny5FKtmICO3Dg5c2o8z3H60VKECUeHY2WQV6JKS9UepxyRO7VofiNKcw3sbt+9lhyL1QoaJO4VbavDt4mLsCMfkwC/IdTs7BDX0Y+2+lYyhIqWxehyXS2XtE9qeXxNLZdP+WtaBq20bJ+r5XGzlk3cTiw/tHGvruWrLBuPzcoQXFvJdkslgzec25OU9b2XFlK2W0kZnitlv1nKBh9LKp98gqZZutdPrRz9FKxPZVu3bk3YJ0R9Sf26LfXrXVW++h5EXb5Wk3xhK/laF5DvH6zdhpVyz9LVj/AGLN0ZzbisFFxayuOWUvavKmX9EDBSI2Ndyk67BXJNy/FvarnYqxQtPriH9j9Ez9XngR0IWmT3/+VdnBjs/1ke3v8H&lt;/diagram&gt;&lt;/mxfile&gt;&quot;}"></div>
<script type="text/javascript" src="https://viewer.diagrams.net/js/viewer-static.min.js"></script>





## Challenges

- Kattis: [Inflation](https://open.kattis.com/problems/inflation)
- Kattis: [The Dragon of Loowater](https://open.kattis.com/problems/loowater)




## Dynamic Programming (DP)

- The most challenging problem-solving techniques among the four paradigms. 
  - It is best to be well-versed in the previous three techniques (Complete Search, D&C, Greedy) before trying out DP. 
- Key skills:
  - Able to determin the problem `states`/ 
  - Able to determine the `relationship`/`transitions` between the `states`. 
- These are the same skills used in recursive backtracking for complete search. 
  - Small DP problems can be solved with recursive backtracking. 
- Naive interpretation of DP:
  - Top-down DP is `intelligen`/`smart` recursive back tracking. 
- Problem types:
  - `maximize this`, `minimize that`, or `count the ways to do that`. 
- Conditions:
  - Has optimal sub-structure: optimal solutions for sub-problems are guaranteed to be part of the final solution. 
  - Has overlapping sub-problems: sub-problems share partial states.  



## Dynamic Programming (DP): Example

- [UVA: Wedding Shopping](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2445)
  - Sypnosis:
    - Given different pricing options for each garment. 
    - Given a limited budget. 
    - Buy one model of each garment. 
  - Input:
    - Budget: 1 ≤ M ≤ 200
    - Number of garments: 1 ≤ C ≤ 20
    - For each garment `g`: 
      - Number of models for each garment, 1 ≤ K ≤ 20 , followed by price for each model (1 ≤ p ≤ K). 
  - Output:
    - Either a single number or `no solution`. 
  - Example test case 1:
    - M = `20`, C = 3
    - g<sub>0</sub>: 3 6 4 8
    - g<sub>1</sub>: 2 5 10
    - g<sub>2</sub>: 4 1 5 3 5
    - Answer: 19 (8, 10, 1) or (6, 10, 3) or (4, 10, 5)
  - Example test case 2:
    - M = `9`, C = 3
    - g<sub>0</sub>: 3 6 4 8
    - g<sub>1</sub>: 2 5 10
    - g<sub>2</sub>: 4 1 5 3 5
    - Answer: no solution

## Non DP Approaches
 - Greedy Approach: Wrong Answer
   - Example test case 3:
     - M = `12`, C = 3
     - g<sub>0</sub>: 3 6 4 8
     - g<sub>1</sub>: 2 5 10
     - g<sub>2</sub>: 4 1 5 3 5
   - Greedy principle: a `optimal` solution also contains a `local` solution for a sub-problem. Therefore we should pick the 
   most expensive model for each garment.  
     - Case (0,8): no budget for anything in g<sub>1</sub>lead to `no solution`.
     - Case (1,10): no budget for anything in g<sub>0</sub> lead to `no solution`. 
     - Case (2, 5): no budget for the third garment piece lead to `no solution`. 
     - Correct answer: (4, 5, 3). 
 - D&C approach: does not work because sub-problems are dependent on one another. 
 - Complete Search: 
   - 20 possible garments, each has up to 20 possible models
   - C(20,20) ~ 10<sup>26</sup>
   - TLE


## Top-down DP:
 - Does have the `optimal sub-structure` as a Greedy problem. 
   - If we select model `i` for garment `g = 0`, for the final selection to be optimal, 
   our choice for garment `g = 1` and above must also be the optimal choice for a reduce budget M (minus cost of `i`).
 - Lack the `greedy` characteristics:  
   - The costliest model `i` for `g = 0` is not guaranteed to be the best selection. 
 - **Distinction between Greedy and DP**: find counter-example. 
 - Does have `over-lapping` sub-problem.
   - If there are two models in a certain garment `g` with the same price `p`. 
   - A complete search will move to the same sub-problem (garment + 1, budget - p) after picking either model. 
   - Similar scenario if some combination of budget and models' prices lead to: b<sub>1</sub> - p<sub>1</sub> = b<sub>2</sub> - p<sub>2</sub>
   - Overlapping: Pricing of each model can not exceed 20, and the maximum value for budget is 201.
     - Problem state: The current budget when a garment is selected.
     - Maximum possible search space: 20 * 201 = 4020 (comparing to 10<sup>26</sup> of Complete Search)
 - Implementation
   - Add an efficient data structure (`memo` table) to map state to value. Initialize the table with dummy values. 
   - At the start of the recursive function, check if the state has been computed. 
     - If it has, return the value of the `memo` table. 
     - If it has not, perform the computation as normal and store the computed  value in the `memo` table. 
  <script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=11450_td.java"></script>

  
## Bottom-up DP:
 - True form of DP
 - DP is original known as `tabular method`. 
 - Basic steps:
   - Determine the required set of parameters that `uniquely` describe the problem (the `state`).
   - If there are `N` parameters required to represent the states, prepare an `N` dimensional array with 
   one entry per state. 
     - Only initialize some cells (base cases). 
   - With the base cases filled out, determine the cells/states that can be filled next. 
   - Repeat the process until the DP table is complete. 
  
  <script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=11450_bu.java"></script>




## LeetCode example
- [LeetCode Contest 275 Solving questions with brainpower](https://leetcode.com/problems/solving-questions-with-brainpower/)
  - Greedy does not work due to the lack of `greedy` properties
  <script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=solving-questions-with-brainpower_incorrect.java"></script>
  - Top down
  <script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=solving-questions-with-brainpower_td.java"></script>
  - Bottom up
  <script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=solving-questions-with-brainpower_bu.java"></script>

