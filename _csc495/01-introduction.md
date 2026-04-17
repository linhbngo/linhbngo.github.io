---
layout: lecture
pretty_table: true
collection: csc495
title: "Introduction to competitive programming"
toc:
  - name: Overview
  - name: First set of tips to be competitive
  - name: Getting started
  - name: Typical input/output routines
  - name: Basic String Processing Tasks
  - name: Ad Hoc problems
  - name: Challenges
---
# Introduction to competitive programming

## Overview

{% details What is competitive programming? %}



{% enddetails %}
- **Given well-known Computer Science (CS) problems, solve them as quickly as possible**
- `well-known CS problems`: We are dealing with **solved** problems and not new ones. 
- `solve`: produce working code. 
- `quickly`: time limitation. 


{% details Types of (competitive) programmers: %}



{% enddetails %}
- Uncompetitive programmer A: becomes confused, try something, anything. 
- Uncompetitive programmer B: realizes the simple general type of the problem, give up 
and select a different problem.
- Uncompetitive programmer C: realizes the complex type of the problem, attempts implementation
using a non-optimized approach, finishes after a very long time. 
- Competitive programmer D: does everything C did in less than 30 minutes. 
- Very competitive programmer E: does everything D did in less than 10 minutes, maybe using 
untraditional approaches. 
- **Class assumption**: everyone starts out at A and B. 
- **Class goal**: everyone reaches at least C by the end of the class. 
- Hopefully, if everyone keeps up practice and compete after the class ended, you 
will become D or E prior to going for technical interviews. 


{% details How does competitive programming help with interviews? %}



{% enddetails %}
- Most SDE (software development engineering) entry positions will 
involve some forms of coding/algorithms questions. 
- While these questions are unlikely to be at the level of ICPC 
(not even divisional), the abilities to quickly recall data structures 
(DS) and algorithms (AL) under pressue (just like competitive programming!) 
will give you a significant advantage in these interviews. 
- Caveats: 
  - Competitive programming will not train you in writing clean codes, 
designing software systems, following Scrum/Agile methodologies ...
  - However, those things are probably not asked in interviews anyway, 
  and you will have time to develop those skills **after you passed the 
  technical interview and get hired!**. 
  - Also, the problem-solving skill of competitive programming is going to be 
  usable everywhere. 

```

## First set of tips to be competitive

{% details Type faster!!! %}



{% enddetails %}
- Take the [typing test](https://www.typingtest.com).
- Dr. Ngo's typing speed is 70wpm.
- A graduated Master student (formerly a concert pianist) was 85wpm.
- CSC 141 students in Fall 2019 averaged between 20-30 wpm. 
- The book's authors' speeds are: 85-95, 55-65, and 70-80. 
- What's yours?
- Typing faster and more accurately means you don't have to *think* 
about typing, and therefore have more time/efforts to focus on 
problem solving.


{% details Quickly identify problem-type %}



{% enddetails %}
- This is important in ICPC competition: divide work among team members. 
- Helps with recalling DS/AL. 

{% details Understand how to do algorithm analysis (CSC 241) %}


{% enddetails %}
- Competition problems often come with time/space limits
- You need to know what are the limits of your solutions. 


{% details Master programming languages %}



{% enddetails %}
- Also helps with interviews!
- C/C++, Java, Python:
 - C/C++: faster, good bitwise-operations, 
 - Java/Python: extensive support libraries, easy to implement some simpler problems. 



{% details Master the art of testing codes %}



{% enddetails %}
- Be comfortable in Linux!
- Setup automated test scripts. 
 - Include all sample test cases. 
 - Run same test cases several times (to test for variable initialization/cleanup)
 - Test for corner cases: extreme max/min values, negative, very big values, empty values ...
 - Check for input format cases (rarely an issue in modern competitive programming contests)


{% details Miscellaneous %}



{% enddetails %}
- Teamwork!
- Practice, practice, and more practice!

```

## Getting started

{% details Online judges and platforms %}



{% enddetails %}
- We will utilize a number of online judging platform to evaluate the correctness of 
practice problems and also to have you participate in online training competitions. 
- You are to create accounts on the following platforms:
  - [UVa Online Judge](https://onlinejudge.org/)
  - [Kattis](https://open.kattis.com/)
  - [Leetcode](https://leetcode.com/)



{% details Anatomy of a programming contest problem %}



{% enddetails %}
A programming contest problem usually contains the following components. 
- Background story/problem descriptions: intended to `deceive` and `confuse`. 
  - It is important to be able to `filter` out unimportant details. 
- Input and output description: details on how input is formatted and you should 
format your output. 
  - Pay attention to input constraints. 
-  Sample input and sample output: trivial test cases for contestants, to test 
basic understanding and verify the code's ability to parse input and display output
properly.
- Hints or Footnotes: additional details to help contestants. 

```


## Typical input/output routines

{% details Overview %}



{% enddetails %}
There are a number of common input/output formats:
1. The number of test cases is given in the first line of the input
2. The multiple test cases are terminated by special values (0s or 1s)
3. The multiple test cases are terminated by the EOF signal. 
4. Variable number of inputs (type 1)
5. Variable number of inputs (type 2)


{% details Code template %}



{% enddetails %}
The authors provide the code templates for input/output routines 
and other examples online at [CP-book Code](https://github.com/stevenhalim/cpbook-code.git)



{% details Your first problem: Moscow Dream %}



{% enddetails %}
We will look at our very first problem from Kattis: 
[Moscow Dream](https://open.kattis.com/problems/moscowdream)

:::::{tab-set}
::::{tab-item} Core descriptions

- Need to take away all the bells and whistles!

Given 4 integers a, b, c, and n (0 ≤ a, b, c ≤ 10, 1 ≤ n ≤ 20), output `YES` if
 a ≥ 1, b ≥ 1, c ≥ 1, and a + b + c ≥ n, or output `NO` otherwise. 

::::
::::{tab-item} Sol. 1

- Can we get an Accepted (AC) verdict?

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=kattis_moscowdream.java"></script>

::::
::::{tab-item} Sol. 2

- If a, b, and c are greater than 1, what is the minimum value that n could possibly be?
- Correct and resubmit. 

::::
:::::



{% details UVa problem 10071: Back to High School Physics %}



{% enddetails %}
[Problem's link](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=1012)

:::::{tab-set}
::::{tab-item} Descriptions

- `Initial velocity and acceleration`: bells and whistle
- Actual information: Given velocity `v`, how far can the particle go after `2 * t`.  

::::
::::{tab-item} IO format

- Type 3: The multiple test cases are terminated by the EOF signal.
- Needs modification from the book's template code: it seems to be 
reading in from command line (using the `<` redirect rather than 
a specific filename)

::::
::::{tab-item} Solution

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=10071.java"></script>
 
- Correct and resubmit. 

::::
:::::




{% details UVa problem 11614: Etruscan Warriors Never Play Chess %}



{% enddetails %}
[Problem's link](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2661)

:::::{tab-set}
::::{tab-item} Descriptions

- *In the first row, there is only one warrior; then, 
the second row contains two warriors; the third row contains three warriors, 
and so on. In general, each row i contains i warriors.*: `1+2+3+...`
- Naive implementation: `for` loop until the sum is greater than the total number of warriors. 

::::
::::{tab-item} IO format

- Type 1: The number of test cases is given on the first line.
- Needs modification from the book's template code: it seems to be 
reading in from command line (using the `<` redirect rather than 
a specific filename)

::::
::::{tab-item} Naive 1

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=11614_1.java"></script>
 
- [Runtime Error](https://onlinejudge.org/index.php?option=com_content&task=view&id=16&Itemid=31).
  - What is the range of `n`?
  - What is the range of `int`? 
  - The word `integer` in the input description tricked us into not 
  checking the range. 

::::
::::{tab-item} Naive 2

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=11614_2.java"></script>
- [Time Limit Exceeded](https://onlinejudge.org/index.php?option=com_content&task=view&id=16&Itemid=31).

- Revisiting the thinking process
  - `1+2+3+...`: Arithmetic sum
  - `S`: the number of warriors (input)
  - `n`: number of terms in the arithmetic sum (expected output)

$$
S = \sum_{i=1}^{n} i = \frac{n(n+1)}{2}
$$

- Simplification of the arithmetic sum equation brings up a different perspective:
 
$$
n^{2}+n-2S = 0
$$

- The problem becomes `estimating the solution of a quadratic equation`. 

$$
Ax^{2} + Bx + C = 0 \\
x = \frac{-B \pm \sqrt{B^{2} - 4AC}}{2A} \\
A = 1;\ B = 1;\ C = -2S \\
x = \frac{-1 \pm \sqrt{1 + 8S}}{2}
$$

::::
::::{tab-item} AC

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=11614_3.java"></script>

::::
:::::

- Similar challenges
  - Kattis: [Solving for carrots](https://open.kattis.com/problems/carrots)
  - Kattis: [R2](https://open.kattis.com/problems/r2) 



{% details UVa problem 12250: Language Detection %}



{% enddetails %}
[Problem's link](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3402)


:::::{tab-set}
::::{tab-item} Descriptions

 - *You will be given one of the six words mentioned above or any other 
 word and you will have to try and detect the language it is from.*
 - Looks too simple to be true? 

::::
::::{tab-item} IO format

 - Type 2: The multiple test cases are terminated by special values (0s or 1s)
 - Needs modification from the book's template code: it seems to be reading in 
 from command line (using the `<` redirect rather than a specific filename)
 - Output needs to be formatted with `Case i:` with `i` is the line number of input. 
 - More details came out after viewing the input/output examples.

::::
::::{tab-item} Sol 1

- Does this work?

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=12250_1.java"></script>

::::
::::{tab-item} AC

 <script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=12250.java"></script>

::::
:::::

- Similar challenges
  - Kattis: [Eligibility](https://open.kattis.com/problems/eligibility)
  - Kattis: [Leftbeehind](https://open.kattis.com/problems/leftbeehind) 



{% details UVa problem 11764: Jumping Mario %}



{% enddetails %}
[Problem's link](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2864)

:::::{tab-set}
::::{tab-item} Descriptions

- You will be given the heights of N walls from left to right.
- Mario is currently standing on the first wall.
- He has to jump to the adjacent walls one after another until he reaches the last one.
- That means, he will make (N − 1) jumps.
  - A high jump is one where Mario has to jump to a taller wall
  - a low jump is one where Mario has to jump to a shorter wall. 
- Can you find out the total number of high jumps and low jumps Mario has to make?

::::
::::{tab-item} IO format

- Type 2: The multiple test cases are terminated by special values (0s or 1s)
- The first line of input is an integer T (T < 30) that indicates the number of test cases. 
  - Each case starts with an integer N (0 < N < 50) that determines the number of walls. 
  - The next line gives the height of the N walls from left to right. 
  - Each height is a positive integer not exceeding 10.
- Output needs to be formatted with `Case i:` with `i` is the line number of input. 

::::
::::{tab-item} Thought Process

- Read first line for case number, setup for loop. 
  - Why for loop? So that we can use the case number. 
- Each iteration has two lines. 
  - one `nextInt` to grab the number of walls. 
  - another loop to start jumping from wall to wall.  
  - initializes high jump (`hj`) and low jump (`lj`) to 0 
  - increment the jumps accordingly  
- Output needs to be formatted with `Case i:` with `i` is the line number of input. 

::::
::::{tab-item} AC

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=11764.java"></script>

::::
:::::

- Similar challenges
  - Kattis: [FizzBuzz](https://open.kattis.com/problems/fizzbuzz)
    - This is the generalized form of the famous FizzBuzz problem
  - Kattis: [Thanos](https://open.kattis.com/problems/thanos) 


{% details UVa problem 10424: Love Calculator %}



{% enddetails %}
[Problem's link](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1365)

:::::{tab-set}
::::{tab-item} Descriptions

- You will be given two names (**String**).
- The strings can contain any character. But only **a-z** and **A-Z** count.
- Numeric range **1-26** for both **a-z** and **A-Z**.  
- For each string, convert alphabet to numbers.
  - First add numbers together. 
  - Then add digits of results together **until it comes in one digit**. 
- Result cannot be more than 100%
  - This means the smaller value is divided by the bigger value

::::
::::{tab-item} IO format

- Type 3: The multiple test cases are terminated by EOF.
- Each test case requires two lines of inputs.  
- Output needs to be formatted with two decimal points and a `%` sign. 

::::
::::{tab-item} Thought Process

- Read every two lines. We can have the following approaches:   
  - Read each character and compare characters with a preset array.
  - Read each character and check their ASCII value (what are the value 
  ranges for a-z and A-Z?) 
  - Remove all non-alphabet characters: adapted from [this guide](https://www.geeksforgeeks.org/how-to-remove-all-non-alphanumeric-characters-from-a-string-in-java/). 
- With the last approach, could also compare with a `toUpperCase` or 
`toLowerCase` call. 
- Still need to remember the ASCII value of characters. 
  - What if I don't remember? 
  - Write a quick program to check. 
- Write a function to get sum of all digits of a number.

::::
::::{tab-item} Solution

<script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=10424_1.java"></script>

- Edge cases:
  - Two empty names; 
  - One empty name, one valid name (at least one alphabet);
  - One empty name, one invalid name (no alphabet);
  - Two invalid names; 
- Extreme edge case:
  - "E" and "EE", or "A" and "AAA"

:::: 
::::{tab-item} AC

 <script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=10424.java"></script>

::::
:::::

- Similar challenges
  - Kattis: [Filip](https://open.kattis.com/problems/filip)
  - Kattis: [Treasure Hunt](https://open.kattis.com/problems/treasurehunt) 


{% details UVa problem 12643 (Medium): Tennis Rounds %}



{% enddetails %}
[Problem's link](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=602&page=show_problem&problem=4391)

:::::{tab-set}
::::{tab-item} Descriptions

- Number of players are a power of two: guaranteed binary tree? 
- Identify the round where two seeds will meet:
  - Assume always win
- What is the patterns?

 <div class="mxgraph" style="max-width:100%;border:1px solid transparent;" data-mxgraph="{&quot;highlight&quot;:&quot;#0000ff&quot;,&quot;nav&quot;:true,&quot;resize&quot;:true,&quot;toolbar&quot;:&quot;zoom layers tags lightbox&quot;,&quot;edit&quot;:&quot;_blank&quot;,&quot;xml&quot;:&quot;&lt;mxfile host=\&quot;app.diagrams.net\&quot; modified=\&quot;2021-12-20T17:33:23.209Z\&quot; agent=\&quot;5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36\&quot; etag=\&quot;dvZ68OP2vhn3E6_HVSwH\&quot; version=\&quot;16.0.0\&quot; type=\&quot;google\&quot;&gt;&lt;diagram id=\&quot;pkFxKJHYkNPQ7IBuaBae\&quot; name=\&quot;Page-1\&quot;&gt;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&lt;/diagram&gt;&lt;/mxfile&gt;&quot;}"></div><script type="text/javascript" src="https://viewer.diagrams.net/js/viewer-static.min.js"></script>

- Example cases to identify pattern (N=8):
  - 8 2 5
  - 8 1 5
  - 8 3 13
  - 8 8 15

::::
::::{tab-item} IO format

- Type 4: Variables number of inputs.
- Each line has three numbers: The power value of $2^N$, and two initial seeds. 
- Output: single value indicates the round. 

::::
::::{tab-item} Thought Process

- Read each line and parse the integers for seed.    
- The question: 
  - What is the new seed after each round?
  - How do we know when the two seeds are in the same round?

::::
::::{tab-item} AC

 <script src="https://gist.github.com/linhbngo/3529c879f8375d9e7eb29f355805bc0c.js?file=12643.java"></script>

::::
:::::

- Similar challenges
  - Kattis: [Battle Simulation](https://open.kattis.com/problems/battlesimulation)

```

## Basic String Processing Tasks


{% details Overview %}



{% enddetails %}
Review the following operations and make sure that you know how to (either manually 
or via a library) do the followings:

- Store a string.
- Read a given text input line by line.
- Concatenate two strings.
- Check if a string starts with a specific phrase. 
- Find first occurrence of a substring in a string. 
- Find all occurrences of a substring in a string. 
- Upper/lower case transformation.
- Consonants/vowels/digits separation. 
- Break string into array of substrings using tokens. 
- Sort array of substrings. 

```


## Ad Hoc problems

- Problems that cannot be classified into anywhere. Their descriptions and solutions
are unique. 
  - Require quick thinkings, does not require advanced data structures/algorithms. 
- Ad Hoc problems are typically easy ones, but sometimes could be time waster/harder. 
  - If a team can only do ad hoc problems, that team is guaranteed to rank in the lower half. 
- Ad Hoc problem categories:
  - Game (Card)
  - Game (Chess)
  - Game (Others: Tic Tac Toe, Rock Paper Scissors, BINGO ...)
  - Real life problems
  - Time
  - Roman Numerals
  - Cipher/Encode/Encrypt/Decode/Decrypt
  - Input Parsing (Iterative)
  - Output Formatting
  - Time Waster


## Challenges

- Game (Card): [Bela](https://open.kattis.com/problems/bela)
  - Input parsing and adding.
- Game (Chess): [Help Me](https://open.kattis.com/problems/helpme)
  - Input parsing, array of strings sorting, output formatting. 
- Game (Others): [Connect the Dots](https://open.kattis.com/problems/connectthedots)
  - Input parsing, output formatting. 
- Real life: [Chopin](https://open.kattis.com/problems/chopin)
- Roman Numerals: [Roman Holidays](https://open.kattis.com/problems/romanholidays)
  - Time wasting!
- Cipher: [Conumdrum](https://open.kattis.com/problems/conundrum)
- Input Parsing: [Autori](https://open.kattis.com/problems/autori)
- Output Formatting: [Display](https://open.kattis.com/problems/display)
  - What are the patterns?
- Time Waster: [Froggie](https://open.kattis.com/problems/froggie)


