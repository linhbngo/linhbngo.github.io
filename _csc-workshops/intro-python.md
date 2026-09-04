---
layout: lecture
pretty_table: true
order: 2
title: Introduction to Python Programming
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
  - name: 1. Overview
  - name: 2. Python Fundamentals
  - name: 3. Analyzing Patient Data
  - name: 4. Storing Multiple Values in Lists
  - name: 5. Repeating Actions with Loops
  - name: 6. Analyzing Data from Multiple Files
  - name: 7. Making Choices
  - name: 8. Creating Functions
  - name: 9. Errors and Exceptions
  - name: 10. Defensive Programming
  - name: 11. Debugging
  - name: 12. Command-Line Programs
---


## 1. Overview

{% details Abstract: Workshop Description %}

This Workshop will introduce Python for those that have little to no 
programming experience and consists of two parts:

-	Part 1: A quick introduction to Python and its basic data analytic 
capability in processing and visualizing data.
-	Part 2: A more in-depth view into programming concepts in Python, 
including loops, conditions, functions, and testing and debugging.

The workshop uses materials from [Software Carpentry](https://software-carpentry.org/)'s 
Programming with Python lesson. 

Link to workshop page: [https://linhbngo.github.io/csc-workshops/intro-python/](https://linhbngo.github.io/csc-workshops/intro-python/)

{% enddetails %}

{% details note Setup on Google Colab %}


- Visit [https://colab.research.google.com/](https://colab.research.google.com/) and create a new 
Python notebook. 
- Run the followings inside a cell to download and unzip the data for this workshop. 

```bash
!wget https://swcarpentry.github.io/python-novice-inflammation/data/python-novice-inflammation-data.zip
!wget https://swcarpentry.github.io/python-novice-inflammation/files/code/python-novice-inflammation-code.zip
!unzip python-novice-inflammation-data.zip
!unzip python-novice-inflammation-code.zip
!ls data/
!ls code/ 
```

- Run the following command inside a cell to find out **where you are**

```bash
!pwd
```

- Run the following to confirm that **the data is located where you are**

```bash
!ls -lh /content
```

{% enddetails %}
## 2. Python Fundamentals

{% details Questions %}

- What basic data types can I work with in Python?
- How can I create a new variable in Python?
- How do I use a function?
- Can I change the value associated with a variable after I create it?

{% enddetails %}

{% details note Variables %}

- Any Python interpreter can be used as a calculator:
    - Run the following inside a cell

```python
3 + 5 * 4
```

```output
23
```

This is great but not very interesting.
To do anything useful with data, we need to assign its value to a *variable*.
In Python, we can assign a value to a variable, using the equals sign `=`.
For example, we can track the weight of a patient who weighs 60 kilograms by
assigning the value `60` to a variable `weight_kg`:

```python
weight_kg = 60
```

From now on, whenever we use `weight_kg`, Python will substitute the value we assigned to
it. In layperson's terms, **a variable is a name for a value**.

In Python, variable names:

- can include letters, digits, and underscores
- cannot start with a digit
- are case sensitive.

This means that, for example:

- `weight0` is a valid variable name, whereas `0weight` is not
- `weight` and `Weight` are different variables

{% enddetails %}

{% details note Types of data %}

Python knows various types of data. Three common ones are:

- integer numbers
- floating point numbers, and
- strings.

In the example above, variable `weight_kg` has an integer value of `60`.
If we want to more precisely track the weight of our patient,
we can use a floating point value by executing:

```python
weight_kg = 60.3
```

To create a string, we add single or double quotes around some text.
To identify and track a patient throughout our study,
we can assign each person a unique identifier by storing it in a string:

```python
patient_id = '001'
```

{% enddetails %}
{% details note Using Variables in Python %}

Once we have data stored with variable names, we can make use of it in calculations.
We may want to store our patient's weight in pounds as well as kilograms:

```python
weight_lb = 2.2 * weight_kg
```

We might decide to add a prefix to our patient identifier:

```python
patient_id = 'inflam_' + patient_id
```

{% enddetails %}
{% details note Built-in Python functions %}

To carry out common tasks with data and variables in Python,
the language provides us with several built-in functions.
To display information to the screen, we use the `print` function:

```python
print(weight_lb)
print(patient_id)
```

```output
132.66
inflam_001
```

When we want to make use of a function, referred to as calling the function,
we follow its name by parentheses. The parentheses are important:
if you leave them off, the function doesn't actually run!
Sometimes you will include values or variables inside the parentheses for the function to use.
In the case of `print`,
we use the parentheses to tell the function what value we want to display.
We will learn more about how functions work and how to create our own in later episodes.

We can display multiple things at once using only one `print` call:

```python
print(patient_id, 'weight in kilograms:', weight_kg)
```

```output
inflam_001 weight in kilograms: 60.3
```

We can also call a function inside of another function call.
For example, Python has a built-in function called `type` that tells you a value's data type:

```python
print(type(60.3))
print(type(patient_id))
```

```output
<class 'float'>
<class 'str'>
```

Moreover, we can do arithmetic with variables right inside the `print` function:

```python
print('weight in pounds:', 2.2 * weight_kg)
```

```output
weight in pounds: 132.66
```

The above command, however, did not change the value of `weight_kg`:

```python
print(weight_kg)
```

```output
60.3
```

To change the value of the `weight_kg` variable, we have to
**assign** `weight_kg` a new value using the equals `=` sign:

```python
weight_kg = 65.0
print('weight in kilograms is now:', weight_kg)
```

```output
weight in kilograms is now: 65.0
```

{% enddetails %}
{% details note Variables as Sticky Notes %}

A variable in Python is analogous to a sticky note with a name written on it:
assigning a value to a variable is like putting that sticky note on a particular value.

{% include figure.liquid path="assets/img/courses/workshops/python_programming/01-intro/python-sticky-note-variables-01.svg" alt="Value of 65.0 with weight\_kg label stuck on it" max-width="50%" zoomable=true %}

Using this analogy, we can investigate how assigning a value to one variable
does **not** change values of other, seemingly related, variables.  For
example, let's store the subject's weight in pounds in its own variable:

```python
# There are 2.2 pounds per kilogram
weight_lb = 2.2 * weight_kg
print('weight in kilograms:', weight_kg, 'and in pounds:', weight_lb)
```

```output
weight in kilograms: 65.0 and in pounds: 143.0
```

Everything in a line of code following the '#' symbol is a
comment that is ignored by Python.
Comments allow programmers to leave explanatory notes for other
programmers or their future selves.

{% include figure.liquid path="assets/img/courses/workshops/python_programming/01-intro/python-sticky-note-variables-02.svg" alt="Value of 65.0 with weight\_kg label stuck on it, and value of 143.0 with weight\_lb label stuck on it" max-width="50%" zoomable=true %}

Similar to above, the expression `2.2 * weight_kg` is evaluated to `143.0`,
and then this value is assigned to the variable `weight_lb` (i.e. the sticky
note `weight_lb` is placed on `143.0`). At this point, each variable is
"stuck" to completely distinct and unrelated values.

Let's now change `weight_kg`:

```python
weight_kg = 100.0
print('weight in kilograms is now:', weight_kg, 'and weight in pounds is still:', weight_lb)
```

```output
weight in kilograms is now: 100.0 and weight in pounds is still: 143.0
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/01-intro/python-sticky-note-variables-03.svg" alt="Value of 100.0 with label weight\_kg stuck on it, and value of 143.0 with label weight\_lbstuck on it" max-width="50%" zoomable=true %}

Since `weight_lb` doesn't "remember" where its value comes from,
it is not updated when we change `weight_kg`.

{% enddetails %}
{% details Challenge 1: Check Your Understanding %}

What values do the variables `mass` and `age` have after each of the following statements?
Test your answer by executing the lines.

```python
mass = 47.5
age = 122
mass = mass * 2.0
age = age - 20
```

{% details success Solution %}

`mass` holds a value of 47.5, `age` does not exist
`mass` still holds a value of 47.5, `age` holds a value of 122
`mass` now has a value of 95.0, `age`'s value is still 122
`mass` still has a value of 95.0, `age` now holds 102

{% enddetails %}
{% enddetails %}
{% details Challenge 2: Sorting Out References %}

Python allows you to assign multiple values to multiple variables in one line by separating
the variables and values with commas. What does the following program print out?

```python
first, second = 'Grace', 'Hopper'
third, fourth = second, first
print(third, fourth)
```

{% details success Solution %}

Hopper Grace

{% enddetails %}
{% enddetails %}
{% details Challenge 3: Seeing Data Types %}

What are the data types of the following variables?

```python
planet = 'Earth'
apples = 5
distance = 10.5
```

{% details success Solution %}

```python
print(type(planet))
print(type(apples))
print(type(distance))
```

```output
<class 'str'>
<class 'int'>
<class 'float'>
```

{% enddetails %}
{% enddetails %}
{% details tip Keypoints %}

- Basic data types in Python include integers, strings, and floating-point numbers.
- Use `variable = value` to assign a value to a variable in order to record it in memory.
- Variables are created on demand whenever a value is assigned to them.
- Use `print(something)` to display the value of `something`.
- Use `# some kind of explanation` to add comments to programs.
- Built-in functions are always available to use.

{% enddetails %}
## 3. Analyzing Patient Data

{% details Abstract: Objectives %}

- Explain what a library is and what libraries are used for.
- Import a Python library and use the functions it contains.
- Read tabular data from a file into a program.
- Select individual values and subsections from data.
- Perform operations on arrays of data.
```
{% enddetails %}

{% details Questions %}

- How can I process tabular data files in Python?

{% enddetails %}

{% details Scenario: A Miracle Arthiritis Inflamation Cure %}

Our imaginary colleague **Dr. Maverick** has invented a new miracle drug that promises to
cure arthritis inflammation flare-ups after only 3 weeks since initially taking the
medication! Naturally, we wish to see the clinical trial data, and after months of asking
for the data they have finally provided us with a CSV spreadsheet containing the clinical
trial data.

The CSV file contains the number of inflammation flare-ups per day for the 60 patients
in the initial clinical trial, with the trial lasting 40 days. Each row corresponds to a
patient, and each column corresponds to a day in the trial. Once a patient has their first
inflammation flare-up they take the medication and wait a few weeks for it to take effect
and reduce flare-ups.

To see how effective the treatment is we would like to:

1. Calculate the average inflammation per day across all patients.
2. Plot the result to discuss and share with colleagues.

{% include figure.liquid path="assets/img/courses/workshops/python_programming/02-numpy/lesson-overview.svg" alt="3-step flowchart shows inflammation data records for patients moving to the Analysis stepwhere a heat map of provided data is generated moving to the Conclusion step that asks thequestion, How does the medication affect patients?" max-width="50%" zoomable=true %}

{% enddetails %}
{% details note Data Format %}

The data sets are stored in **comma-separated values** (CSV) format:

- each row holds information for a single patient,
- columns represent successive days.

The first three rows of our first file look like this:

```python
0,0,1,3,1,2,4,7,8,3,3,3,10,5,7,4,7,7,12,18,6,13,11,11,7,7,4,6,8,8,4,4,5,7,3,4,2,3,0,0
0,1,2,1,2,1,3,2,2,6,10,11,5,9,4,4,7,16,8,6,18,4,12,5,12,7,11,5,11,3,3,5,4,4,5,5,1,1,0,1
0,1,1,3,3,2,6,2,5,9,5,7,4,5,4,15,5,11,9,10,19,14,12,17,7,12,11,7,4,2,10,5,4,2,2,3,2,2,1,1
```

Each number represents the number of inflammation bouts that a particular patient experienced on a
given day.

For example, value "6" at row 3 column 7 of the data set above means that the third
patient was experiencing inflammation six times on the seventh day of the clinical study.


Words are useful, but what's more useful are the sentences and stories we build with them.
Similarly, while a lot of powerful, general tools are built into Python,
specialized tools built up from these basic units live in **libraries**.
that can be called upon when needed.

{% enddetails %}
{% details note Loading data into Python %}

To begin processing the clinical trial inflammation data, we need to load it into Python.
We can do that using a library called
[NumPy](https://numpy.org/doc/stable "NumPy Documentation"), which stands for Numerical Python.
In general, you should use this library when you want to do fancy things with lots of numbers,
especially if you have matrices or arrays. To tell Python that we'd like to start using NumPy,
we need to **import** it:

```python
import numpy
```

Importing a library is like getting a piece of lab equipment out of a storage locker and setting it
up on the bench. Libraries provide additional functionality to the basic Python package, much like
a new piece of equipment adds functionality to a lab space. Just like in the lab, importing too
many libraries can sometimes complicate and slow down your programs - so we only import what we
need for each program.

Once we've imported the library, we can ask the library to read our data file for us:

```python
numpy.loadtxt(fname='data/inflammation-01.csv', delimiter=',')
```

```output
array([[ 0.,  0.,  1., ...,  3.,  0.,  0.],
    [ 0.,  1.,  2., ...,  1.,  0.,  1.],
    [ 0.,  1.,  1., ...,  2.,  1.,  1.],
    ...,
    [ 0.,  1.,  1., ...,  1.,  1.,  1.],
    [ 0.,  0.,  0., ...,  0.,  2.,  0.],
    [ 0.,  0.,  1., ...,  1.,  1.,  0.]])
```

The expression `numpy.loadtxt(...)` is a **function call**
that asks Python to run the **function** `loadtxt` which
belongs to the `numpy` library.
The dot notation in Python is used most of all as an object attribute/property specifier or for invoking 
its method. `object.property` will give you the object.property value,
`object_name.method()` will invoke on object\_name method.

As an example, John Smith is the John that belongs to the Smith family.
We could use the dot notation to write his name `smith.john`,
just as `loadtxt` is a function that belongs to the `numpy` library.

`numpy.loadtxt` has two **parameters**: the name of the file
we want to read and the **delimiter** that separates values
on a line. These both need to be character strings
(or **strings** for short), so we put them in quotes.

Since we haven't told it to do anything else with the function's output,
the **notebook** displays it. In this case, that output is the data we just loaded.
By default, only a few rows and columns are shown (with `...` to omit elements when displaying big arrays).
Note that, to save space when displaying NumPy arrays, Python does not show us trailing zeros,
so `1.0` becomes `1.`.

Our call to `numpy.loadtxt` read our file but didn't save the data in memory.
To do that, we need to assign the array to a variable. In a similar manner to how we assign a single
value to a variable, we can also assign an array of values to a variable using the same syntax.
Let's re-run `numpy.loadtxt` and save the returned data:

```python
data = numpy.loadtxt(fname='data/inflammation-01.csv', delimiter=',')
```

This statement doesn't produce any output because we've assigned the output to the variable `data`.
If we want to check that the data have been loaded,
we can print the variable's value:

```python
print(data)
```

```output
[[ 0.  0.  1. ...,  3.  0.  0.]
[ 0.  1.  2. ...,  1.  0.  1.]
[ 0.  1.  1. ...,  2.  1.  1.]
...,
[ 0.  1.  1. ...,  1.  1.  1.]
[ 0.  0.  0. ...,  0.  2.  0.]
[ 0.  0.  1. ...,  1.  1.  0.]]
```

Now that the data are in memory, we can manipulate them.
First, let's ask what **type** of thing `data` refers to:

```python
print(type(data))
```

```output
<class 'numpy.ndarray'>
```

The output tells us that `data` currently refers to an N-dimensional array, the functionality for which is provided by the NumPy library. These data correspond to arthritis patients' inflammation. The rows are the individual patients, and the columns
are their daily inflammation measurements.

{% enddetails %}
{% details note Data Type %}

A Numpy array contains one or more elements of the same type. The `type` function will only tell you that
a variable is a NumPy array but won't tell you the type of thing inside the array.
We can find out the type of the data contained in the NumPy array.

```python
print(data.dtype)
```

```output
float64
```

This tells us that the NumPy array's elements are **floating-point numbers**.

With the following command, we can see the array's **shape**:

```python
print(data.shape)
```

```output
(60, 40)
```

The output tells us that the `data` array variable contains 60 rows and 40 columns. When we
created the variable `data` to store our arthritis data, we did not only create the array; we also
created information about the array, called **members** or
attributes. This extra information describes `data` in the same way an adjective describes a noun.
`data.shape` is an attribute of `data` which describes the dimensions of `data`. We use the same
dotted notation for the attributes of variables that we use for the functions in libraries because
they have the same part-and-whole relationship.

If we want to get a single number from the array, we must provide an **index** in square brackets 
after the variable name, just as we
do in math when referring to an element of a matrix.  Our inflammation data has two dimensions, so
we will need to use two indices to refer to one specific value:

```python
print('first value in data:', data[0, 0])
```

```output
first value in data: 0.0
```

```python
print('middle value in data:', data[29, 19])
```

```output
middle value in data: 16.0
```

The expression `data[29, 19]` accesses the element at row 30, column 20. While this expression may
not surprise you, `data[0, 0]` might. Programming languages like Fortran, MATLAB and R start counting at 1
because that's what human beings have done for thousands of years. Languages in the C family (including C++, Java, Perl, and Python) 
count from 0 because it represents an offset from the first value in the array (the second
value is offset by one index from the first value). This is closer to the way
that computers represent arrays (if you are interested in the historical reasons behind counting indices from zero, you can read
[Mike Hoye's blog post](https://exple.tive.org/blarg/2013/10/22/citation-needed/)).
As a result, if we have an M×N array in Python, its indices go from 0 to M-1 on the first axis
and 0 to N-1 on the second. It takes a bit of getting used to, but one way to remember the rule is that
the index is how many steps we have to take from the start to get the item we want.

{% include figure.liquid path="assets/img/courses/workshops/python_programming/02-numpy/python-zero-index.svg" alt="data is a 3 by 3 numpy array containing row 0: \['A', 'B', 'C'\], row 1: \['D', 'E', 'F'\], androw 2: \['G', 'H', 'I'\]. Starting in the upper left hand corner, data\[0, 0\] = 'A', data\[0, 1\] = 'B',data\[0, 2\] = 'C', data\[1, 0\] = 'D', data\[1, 1\] = 'E', data\[1, 2\] = 'F', data\[2, 0\] = 'G',data\[2, 1\] = 'H', and data\[2, 2\] = 'I', in the bottom right hand corner." max-width="50%" zoomable=true %}

{% enddetails %}
{% details warning In the Corner %}

What may also surprise you is that when Python displays an array,
it shows the element with index `[0, 0]` in the upper left corner
rather than the lower left.
This is consistent with the way mathematicians draw matrices
but different from the Cartesian coordinates.
The indices are `(row, column)` instead of `(column, row)` for the same reason,
which can be confusing when plotting data.

{% enddetails %}
{% details note Slicing data %}

An index like `[30, 20]` selects a single element of an array,
but we can select whole sections as well.
For example,
we can select the first ten days (columns) of values
for the first four patients (rows) like this:

```python
print(data[0:4, 0:10])
```

```output
[[ 0.  0.  1.  3.  1.  2.  4.  7.  8.  3.]
[ 0.  1.  2.  1.  2.  1.  3.  2.  2.  6.]
[ 0.  1.  1.  3.  3.  2.  6.  2.  5.  9.]
[ 0.  0.  2.  0.  4.  2.  2.  1.  6.  7.]]
```

The **slice** `0:4` means, "Start at index 0 and go up to,
but not including, index 4". Again, the up-to-but-not-including takes a bit of getting used to,
but the rule is that the difference between the upper and lower bounds is the number of values in
the slice.

We don't have to start slices at 0:

```python
print(data[5:10, 0:10])
```

```output
[[ 0.  0.  1.  2.  2.  4.  2.  1.  6.  4.]
[ 0.  0.  2.  2.  4.  2.  2.  5.  5.  8.]
[ 0.  0.  1.  2.  3.  1.  2.  3.  5.  3.]
[ 0.  0.  0.  3.  1.  5.  6.  5.  5.  8.]
[ 0.  1.  1.  2.  1.  3.  5.  3.  5.  8.]]
```

We also don't have to include the upper and lower bound on the slice.  If we don't include the lower
bound, Python uses 0 by default; if we don't include the upper, the slice runs to the end of the
axis, and if we don't include either (i.e., if we use ':' on its own), the slice includes
everything:

```python
small = data[:3, 36:]
print('small is:')
print(small)
```

The above example selects rows 0 through 2 and columns 36 through to the end of the array.

```output
small is:
[[ 2.  3.  0.  0.]
[ 1.  1.  0.  1.]
[ 2.  2.  1.  1.]]
```

{% enddetails %}
{% details note Analyzing data %}

NumPy has several useful functions that take an array as input to perform operations on its values.
If we want to find the average inflammation for all patients on
all days, for example, we can ask NumPy to compute `data`'s mean value:

```python
print(numpy.mean(data))
```

```output
6.14875
```

`mean` is a **function** that takes an array as an **argument**.

{% enddetails %}
{% details note Not All Functions Have Input %}

Generally, a function uses inputs to produce outputs.
However, some functions produce outputs without
needing any input. For example, checking the current time
doesn't require any input.

```python
import time
print(time.ctime())
```

```output
Sat Mar 26 13:07:33 2016
```

For functions that don't take in any arguments, we still need parentheses (`()`)
to tell Python to go and do something for us.

Let's use three other NumPy functions to get some descriptive values about the dataset. We'll also use multiple assignment,
a convenient Python feature that will enable us to do this all in one line.

```python
maxval, minval, stdval = numpy.amax(data), numpy.amin(data), numpy.std(data)

print('maximum inflammation:', maxval)
print('minimum inflammation:', minval)
print('standard deviation:', stdval)
```

Here we've assigned the return value from `numpy.amax(data)` to the variable `maxval`, the value
from `numpy.amin(data)` to `minval`, and so on.

```output
maximum inflammation: 20.0
minimum inflammation: 0.0
standard deviation: 4.61383319712
```

{% enddetails %}
{% details note Mystery Functions in IPython %}


How did we know what functions NumPy has and how to use them?
If you are working in IPython or in a Jupyter Notebook, there is an easy way to find out.
If you type the name of something followed by a dot, then you can use
**tab completion**
(e.g. type `numpy.` and then press <kbd>Tab</kbd>)
to see a list of all functions and attributes that you can use. After selecting one, you
can also add a question mark (e.g. `numpy.cumprod?`), and IPython will return an
explanation of the method! This is the same as doing `help(numpy.cumprod)`.
Similarly, if you are using the "plain vanilla" Python interpreter, you can type `numpy.`
and press the <kbd>Tab</kbd> key twice for a listing of what is available. You can then use the
`help()` function to see an explanation of the function you're interested in,
for example: `help(numpy.cumprod)`.

When analyzing data, though, we often want to look at variations in statistical values,
such as the maximum inflammation per patient or the average inflammation per day.
One way to do this is to create a new temporary array of the data we want,
then ask it to do the calculation:

```python
patient_0 = data[0, :] # 0 on the first axis (rows), everything on the second (columns)
print('maximum inflammation for patient 0:', numpy.amax(patient_0))
```

```output
maximum inflammation for patient 0: 18.0
```

We don't actually need to store the row in a variable of its own. Instead, we can combine the selection and the function call:

```python
print('maximum inflammation for patient 2:', numpy.amax(data[2, :]))
```

```output
maximum inflammation for patient 2: 19.0
```

What if we need the maximum inflammation for each patient over all days (as in the
next diagram on the left) or the average for each day (as in the
diagram on the right)? As the diagram below shows, we want to perform the operation across an axis:

{% include figure.liquid path="assets/img/courses/workshops/python_programming/01-intro/python-operations-across-axes.png" alt="Per-patient maximum inflammation is computed row-wise across all columns usingnumpy.amax(data, axis=1). Per-day average inflammation is computed column-wise across all rows usingnumpy.mean(data, axis=0)." max-width="50%" zoomable=true %}

To support this functionality,
most array functions allow us to specify the axis we want to work on.
If we ask for the average across axis 0 (rows in our 2D example),
we get:

```python
print(numpy.mean(data, axis=0))
```

```output
[  0.           0.45         1.11666667   1.75         2.43333333   3.15
3.8          3.88333333   5.23333333   5.51666667   5.95         5.9
8.35         7.73333333   8.36666667   9.5          9.58333333
10.63333333  11.56666667  12.35        13.25        11.96666667
11.03333333  10.16666667  10.           8.66666667   9.15         7.25
7.33333333   6.58333333   6.06666667   5.95         5.11666667   3.6
3.3          3.56666667   2.48333333   1.5          1.13333333
0.56666667]
```

As a quick check, we can ask this array what its shape is:

```python
print(numpy.mean(data, axis=0).shape)
```

```output
(40,)
```

The expression `(40,)` tells us we have an N×1 vector, so this is the average inflammation per day for all patients.
If we average across axis 1 (columns in our 2D example), we get:

```python
print(numpy.mean(data, axis=1))
```

```output
[ 5.45   5.425  6.1    5.9    5.55   6.225  5.975  6.65   6.625  6.525
6.775  5.8    6.225  5.75   5.225  6.3    6.55   5.7    5.85   6.55
5.775  5.825  6.175  6.1    5.8    6.425  6.05   6.025  6.175  6.55
6.175  6.35   6.725  6.125  7.075  5.725  5.925  6.15   6.075  5.75
5.975  5.725  6.3    5.9    6.75   5.925  7.225  6.15   5.95   6.275  5.7
6.1    6.825  5.975  6.725  5.7    6.25   6.4    7.05   5.9  ]
```

which is the average inflammation per patient across all days.

{% enddetails %}
{% details Challenge 1: Slicing Strings %}


A section of an array is called a **slice**. We can take slices of character strings as well:

```python
element = 'oxygen'
print('first three characters:', element[0:3])
print('last three characters:', element[3:6])
```

```output
first three characters: oxy
last three characters: gen
```

- What is the value of `element[:4]`?
- What about `element[4:]`?
- Or `element[:]`?

{% details success Solution %}

```output
oxyg
en
oxygen
```

{% enddetails %}
- What is `element[-1]`?
- What is `element[-2]`?

{% details success Solution %}

```output
n
e
```

{% enddetails %}
- Given those answers, explain what `element[1:-1]` does.

{% details success Solution %}

Creates a substring from index 1 up to (not including) the final index,
effectively removing the first and last letters from 'oxygen'


{% enddetails %}
- How can we rewrite the slice for getting the last three characters of `element`,
so that it works even if we assign a different string to `element`? Test your solution with the following strings: `carpentry`, `clone`, `hi`.

{% details success Solution %}

```python
element = 'oxygen'
print('last three characters:', element[-3:])
element = 'carpentry'
print('last three characters:', element[-3:])
element = 'clone'
print('last three characters:', element[-3:])
element = 'hi'
print('last three characters:', element[-3:])
```

```output
last three characters: gen
last three characters: try
last three characters: one
last three characters: hi
```



{% enddetails %}
{% enddetails %}
{% details Challenge 2: Thin Slices %}


The expression `element[3:3]` produces an **empty string**, i.e., a string that contains no characters.
If `data` holds our array of patient data, what does `data[3:3, 4:4]` produce? What about `data[3:3, :]`?

{% details success Solution %}

```output
array([], shape=(0, 0), dtype=float64)
array([], shape=(0, 40), dtype=float64)
```

{% enddetails %}
{% enddetails %}
{% details Challenge 3: Stacking Arrays %}


Arrays can be concatenated and stacked on top of one another,
using NumPy's `vstack` and `hstack` functions for vertical and horizontal stacking, respectively.

```python
import numpy

A = numpy.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print('A = ')
print(A)

B = numpy.hstack([A, A])
print('B = ')
print(B)

C = numpy.vstack([A, A])
print('C = ')
print(C)
```

```output
A =
[[1 2 3]
[4 5 6]
[7 8 9]]
B =
[[1 2 3 1 2 3]
[4 5 6 4 5 6]
[7 8 9 7 8 9]]
C =
[[1 2 3]
[4 5 6]
[7 8 9]
[1 2 3]
[4 5 6]
[7 8 9]]
```

- Write some additional code that slices the first and last columns of `A`, and stacks them into a 3x2 array.
Make sure to `print` the results to verify your solution.

{% details success Solution 1 %}

A 'gotcha' with array indexing is that singleton dimensions
are dropped by default. That means `A[:, 0]` is a one dimensional
array, which won't stack as desired. To preserve singleton dimensions,
the index itself can be a slice or array. For example, `A[:, :1]` returns
a two dimensional array with one singleton dimension (i.e. a column
vector).

```python
D = numpy.hstack((A[:, :1], A[:, -1:]))
print('D = ')
print(D)
```

```output
D =
[[1 3]
[4 6]
[7 9]]
```


{% enddetails %}
{% details success Solution 2 %}

An alternative way to achieve the same result is to use Numpy's
delete function to remove the second column of A. If you're not
sure what the parameters of numpy.delete mean, use the help files.

```python
D = numpy.delete(arr=A, obj=1, axis=1)
print('D = ')
print(D)
```

```output
D =
[[1 3]
[4 6]
[7 9]]
```

{% enddetails %}
{% enddetails %}
{% details Challenge 4: Change In Inflammation %}

The patient data is *longitudinal* in the sense that each row represents a
series of observations relating to one individual.  This means that
the change in inflammation over time is a meaningful concept.
Let's find out how to calculate changes in the data contained in an array
with NumPy.

The `numpy.diff()` function takes an array and returns the differences
between two successive values. Let's use it to examine the changes
each day across the first week of patient 3 from our inflammation dataset.

```python
patient3_week1 = data[3, :7]
print(patient3_week1)
```

```output
[0. 0. 2. 0. 4. 2. 2.]
```

Calling `numpy.diff(patient3_week1)` would do the following calculations

```python
[ 0 - 0, 2 - 0, 0 - 2, 4 - 0, 2 - 4, 2 - 2 ]
```

and return the 6 difference values in a new array.

```python
numpy.diff(patient3_week1)
```

```output
array([ 0.,  2., -2.,  4., -2.,  0.])
```

Note that the array of differences is shorter by one element (length 6).

- When calling `numpy.diff` with a multi-dimensional array, an `axis` argument may
be passed to the function to specify which axis to process. When applying
`numpy.diff` to our 2D inflammation array `data`, which axis would we specify?

{% details success Solution %}

Since the row axis (0) is patients, it does not make sense to get the
difference between two arbitrary patients. The column axis (1) is in
days, so the difference is the change in inflammation -- a meaningful
concept.

```python
numpy.diff(data, axis=1)
```


{% enddetails %}
- If the shape of an individual data file is `(60, 40)` (60 rows and 40
columns), what would the shape of the array be after you run the `diff()`
function and why?

{% details success Solution %}

The shape will be `(60, 39)` because there is one fewer difference between
columns than there are columns in the data.


{% enddetails %}
- How would you find the largest change in inflammation for each patient? Does
it matter if the change in inflammation is an increase or a decrease?

{% details success Solution %}

By using the `numpy.amax()` function after you apply the `numpy.diff()`
function, you will get the largest difference between days.

```python
numpy.amax(numpy.diff(data, axis=1), axis=1)
```

```python
array([  7.,  12.,  11.,  10.,  11.,  13.,  10.,   8.,  10.,  10.,   7.,
        7.,  13.,   7.,  10.,  10.,   8.,  10.,   9.,  10.,  13.,   7.,
        12.,   9.,  12.,  11.,  10.,  10.,   7.,  10.,  11.,  10.,   8.,
        11.,  12.,  10.,   9.,  10.,  13.,  10.,   7.,   7.,  10.,  13.,
        12.,   8.,   8.,  10.,  10.,   9.,   8.,  13.,  10.,   7.,  10.,
        8.,  12.,  10.,   7.,  12.])
```

If inflammation values *decrease* along an axis, then the difference from
one element to the next will be negative. If
you are interested in the **magnitude** of the change and not the
direction, the `numpy.absolute()` function will provide that.

Notice the difference if you get the largest *absolute* difference
between readings.

```python
numpy.amax(numpy.absolute(numpy.diff(data, axis=1)), axis=1)
```

```python
array([ 12.,  14.,  11.,  13.,  11.,  13.,  10.,  12.,  10.,  10.,  10.,
        12.,  13.,  10.,  11.,  10.,  12.,  13.,   9.,  10.,  13.,   9.,
        12.,   9.,  12.,  11.,  10.,  13.,   9.,  13.,  11.,  11.,   8.,
        11.,  12.,  13.,   9.,  10.,  13.,  11.,  11.,  13.,  11.,  13.,
        13.,  10.,   9.,  10.,  10.,   9.,   9.,  13.,  10.,   9.,  10.,
        11.,  13.,  10.,  10.,  12.])
```

{% enddetails %}
{% enddetails %}
{% details tip Keypoints %}

- Import a library into a program using `import libraryname`.
- Use the `numpy` library to work with arrays in Python.
- The expression `array.shape` gives the shape of an array.
- Use `array[x, y]` to select a single element from a 2D array.
- Array indices start at 0, not 1.
- Use `low:high` to specify a `slice` that includes the indices from `low` to `high-1`.
- Use `# some kind of explanation` to add comments to programs.
- Use `numpy.mean(array)`, `numpy.amax(array)`, and `numpy.amin(array)` to calculate simple statistics.
- Use `numpy.mean(array, axis=0)` or `numpy.mean(array, axis=1)` to calculate statistics across the specified axis.
```

{% enddetails %}
## 4. Visualizing Tabular Data

{% details Abstract: Objectives %}

- Plot simple graphs from data.
- Plot multiple graphs in a single figure.

{% enddetails %}
{% details Questions %}

- How can I visualize tabular data in Python?
- How can I group several plots together?

{% enddetails %}
{% details note Visualizing data %}


The mathematician Richard Hamming once said, "The purpose of computing is insight, not numbers,"
and the best way to develop insight is often to visualize data.  Visualization deserves an entire
lecture of its own, but we can explore a few features of Python's `matplotlib` library here.  While
there is no official plotting library, `matplotlib` is the *de facto* standard.  First, we will
import the `pyplot` module from `matplotlib` and use two of its functions to create and display a
**heat map** of our data:

{% details warning Episode Prerequisites %}

If you are continuing in the same notebook from the previous episode, you already
have a `data` variable and have imported `numpy`.  If you are starting a new
notebook at this point, you need the following two lines:

```python
import numpy
data = numpy.loadtxt(fname='data/inflammation-01.csv', delimiter=',')
```

{% enddetails %}
```python
import matplotlib.pyplot
image = matplotlib.pyplot.imshow(data)
matplotlib.pyplot.show()
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/03-matplotlib/inflammation-01-imshow.svg" alt="Heat map representing the data variable. Each cell is colored by value along a color gradientfrom blue to yellow." max-width="50%" zoomable=true %}

Each row in the heat map corresponds to a patient in the clinical trial dataset, and each column
corresponds to a day in the dataset.  Blue pixels in this heat map represent low values, while
yellow pixels represent high values.  As we can see, the general number of inflammation flare-ups
for the patients rises and falls over a 40-day period.

So far so good as this is in line with our knowledge of the clinical trial and Dr. Maverick's
claims:

- the patients take their medication once their inflammation flare-ups begin
- it takes around 3 weeks for the medication to take effect and begin reducing flare-ups
- and flare-ups appear to drop to zero by the end of the clinical trial.

Now let's take a look at the average inflammation over time:

```python
ave_inflammation = numpy.mean(data, axis=0)
ave_plot = matplotlib.pyplot.plot(ave_inflammation)
matplotlib.pyplot.show()
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/03-matplotlib/inflammation-01-average.svg" alt="A line graph showing the average inflammation across all patients over a 40-day period." max-width="50%" zoomable=true %}

Here, we have put the average inflammation per day across all patients in the variable
`ave_inflammation`, then asked `matplotlib.pyplot` to create and display a line graph of those
values.  The result is a reasonably linear rise and fall, in line with Dr. Maverick's claim that
the medication takes 3 weeks to take effect.  But a good data scientist doesn't just consider the
average of a dataset, so let's have a look at two other statistics:

```python
max_plot = matplotlib.pyplot.plot(numpy.amax(data, axis=0))
matplotlib.pyplot.show()
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/03-matplotlib/inflammation-01-maximum.svg" alt="A line graph showing the maximum inflammation across all patients over a 40-day period." max-width="50%" zoomable=true %}

```python
min_plot = matplotlib.pyplot.plot(numpy.amin(data, axis=0))
matplotlib.pyplot.show()
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/03-matplotlib/inflammation-01-minimum.svg" alt="A line graph showing the minimum inflammation across all patients over a 40-day period." max-width="50%" zoomable=true %}

The maximum value rises and falls linearly, while the minimum seems to be a step function.
Neither trend seems particularly likely, so either there's a mistake in our calculations or
something is wrong with our data. This insight would have been difficult to reach by examining
the numbers themselves without visualization tools.

{% enddetails %}
{% details note Grouping plots %}

You can group similar plots in a single figure using subplots.
This script below uses a number of new commands. The function `matplotlib.pyplot.figure()`
creates a space into which we will place all of our plots. The parameter `figsize`
tells Python how big to make this space. Each subplot is placed into the figure using
its `add_subplot` **method**. The `add_subplot` method takes
3 parameters. The first denotes how many total rows of subplots there are, the second parameter
refers to the total number of subplot columns, and the final parameter denotes which subplot
your variable is referencing (left-to-right, top-to-bottom). Each subplot is stored in a
different variable (`axes1`, `axes2`, `axes3`). Once a subplot is created, the axes can
be titled using the `set_xlabel()` command (or `set_ylabel()`).
Here are our three plots side by side:

```python
import numpy
import matplotlib.pyplot

data = numpy.loadtxt(fname='data/inflammation-01.csv', delimiter=',')

fig = matplotlib.pyplot.figure(figsize=(10.0, 3.0))

axes1 = fig.add_subplot(1, 3, 1)
axes2 = fig.add_subplot(1, 3, 2)
axes3 = fig.add_subplot(1, 3, 3)

axes1.set_ylabel('average')
axes1.plot(numpy.mean(data, axis=0))

axes2.set_ylabel('max')
axes2.plot(numpy.amax(data, axis=0))

axes3.set_ylabel('min')
axes3.plot(numpy.amin(data, axis=0))

fig.tight_layout()

matplotlib.pyplot.savefig('data/inflammation.png')
matplotlib.pyplot.show()
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/03-matplotlib/inflammation-01-group-plot.svg" alt="Three line graphs showing the daily average, maximum and minimum inflammation over a 40-day period." max-width="50%" zoomable=true %}

The **call** to `loadtxt` reads our data,
and the rest of the program tells the plotting library
how large we want the figure to be,
that we're creating three subplots,
what to draw for each one,
and that we want a tight layout.
(If we leave out that call to `fig.tight_layout()`,
the graphs will actually be squeezed together more closely.)

The call to `savefig` stores the plot as a graphics file. This can be
a convenient way to store your plots for use in other documents, web
pages etc. The graphics format is automatically determined by
Matplotlib from the file name ending we specify; here PNG from
'data/inflammation.png'. Matplotlib supports many different graphics
formats, including SVG, PDF, and JPEG.

{% enddetails %}
{% details note Importing libraries with shortcuts %}

In this lesson we use the `import matplotlib.pyplot`
**syntax** to import the `pyplot` module of `matplotlib`. However, shortcuts such as
`import matplotlib.pyplot as plt` are frequently used.
Importing `pyplot` this way means that after the initial import, rather than writing
`matplotlib.pyplot.plot(...)`, you can now write `plt.plot(...)`.
Another common convention is to use the shortcut `import numpy as np` when importing the
NumPy library. We then can write `np.loadtxt(...)` instead of `numpy.loadtxt(...)`,
for example.

Some people prefer these shortcuts as it is quicker to type and results in shorter
lines of code - especially for libraries with long names! You will frequently see
Python code online using a `pyplot` function with `plt`, or a NumPy function with
`np`, and it's because they've used this shortcut. It makes no difference which
approach you choose to take, but you must be consistent as if you use
`import matplotlib.pyplot as plt` then `matplotlib.pyplot.plot(...)` will not work, and
you must use `plt.plot(...)` instead. Because of this, when working with other people it
is important you agree on how libraries are imported.


{% enddetails %}
{% details Challenge 1: Plot Scaling %}

Why do all of our plots stop just short of the upper end of our graph?

{% details success Solution %}

Because matplotlib normally sets x and y axes limits to the min and max of our data
(depending on data range).

If we want to change this, we can use the `set_ylim(min, max)` method of each 'axes',
for example:

```python
axes3.set_ylim(0, 6)
```

Update your plotting code to automatically set a more appropriate scale.
(Hint: you can make use of the `max` and `min` methods to help.)

{% enddetails %}
{% details success Solution 1 %}

```python
# One method
axes3.set_ylabel('min')
axes3.plot(numpy.amin(data, axis=0))
axes3.set_ylim(0, 6)
```

{% enddetails %}
{% details success Solution 2 %}

```python
# A more automated approach
min_data = numpy.amin(data, axis=0)
axes3.set_ylabel('min')
axes3.plot(min_data)
axes3.set_ylim(numpy.amin(min_data), numpy.amax(min_data) * 1.1)
```

{% enddetails %}
{% enddetails %}
{% details Challenge 2: Drawing Straight Lines %}

In the center and right subplots above, we expect all lines to look like step functions because
non-integer value are not realistic for the minimum and maximum values. However, you can see
that the lines are not always vertical or horizontal, and in particular the step function
in the subplot on the right looks slanted. Why is this?

{% details success Solution %}

Because matplotlib interpolates (draws a straight line) between the points.
One way to do avoid this is to use the Matplotlib `drawstyle` option:

```python
import numpy
import matplotlib.pyplot

data = numpy.loadtxt(fname='data/inflammation-01.csv', delimiter=',')

fig = matplotlib.pyplot.figure(figsize=(10.0, 3.0))

axes1 = fig.add_subplot(1, 3, 1)
axes2 = fig.add_subplot(1, 3, 2)
axes3 = fig.add_subplot(1, 3, 3)

axes1.set_ylabel('average')
axes1.plot(numpy.mean(data, axis=0), drawstyle='steps-mid')

axes2.set_ylabel('max')
axes2.plot(numpy.amax(data, axis=0), drawstyle='steps-mid')

axes3.set_ylabel('min')
axes3.plot(numpy.amin(data, axis=0), drawstyle='steps-mid')

fig.tight_layout()

matplotlib.pyplot.show()
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/inflammation-01-line-styles.svg" alt="Three line graphs, with step lines connecting the points, showing the daily average, maximumand minimum inflammation over a 40-day period." max-width="50%" zoomable=true %}

{% enddetails %}
{% enddetails %}
{% details Challenge 3:  Make Your Own Plot %}


Create a plot showing the standard deviation (`numpy.std`)
of the inflammation data for each day across all patients.

{% details success Solution %}

```python
std_plot = matplotlib.pyplot.plot(numpy.std(data, axis=0))
matplotlib.pyplot.show()
```


{% enddetails %}
{% enddetails %}
{% details Challenge 4: Moving Plots Around %}


Modify the program to display the three plots on top of one another
instead of side by side.

{% details success Solution %}

```python
import numpy
import matplotlib.pyplot

data = numpy.loadtxt(fname='data/inflammation-01.csv', delimiter=',')

# change figsize (swap width and height)
fig = matplotlib.pyplot.figure(figsize=(3.0, 10.0))

# change add_subplot (swap first two parameters)
axes1 = fig.add_subplot(3, 1, 1)
axes2 = fig.add_subplot(3, 1, 2)
axes3 = fig.add_subplot(3, 1, 3)

axes1.set_ylabel('average')
axes1.plot(numpy.mean(data, axis=0))

axes2.set_ylabel('max')
axes2.plot(numpy.amax(data, axis=0))

axes3.set_ylabel('min')
axes3.plot(numpy.amin(data, axis=0))

fig.tight_layout()

matplotlib.pyplot.show()
```


{% enddetails %}
{% enddetails %}
{% details tip Keypoints %}

- Use the `pyplot` module from the `matplotlib` library for creating simple visualizations.

{% enddetails %}
## 4. Storing Multiple Values in Lists

{% details Abstract: Objectives %}

- Explain what a list is.
- Create and index lists of simple values.
- Change the values of individual elements
- Append values to an existing list
- Reorder and slice list elements
- Create and manipulate nested lists


{% enddetails %}
{% details Questions %}

- How can I store many values together?

In the previous episode, we analyzed a single file of clinical trial inflammation data. However,
after finding some peculiar and potentially suspicious trends in the trial data we ask
Dr. Maverick if they have performed any other clinical trials. Surprisingly, they say that they
have and provide us with 11 more CSV files for a further 11 clinical trials they have undertaken
since the initial trial.

Our goal now is to process all the inflammation data we have, which means that we still have
eleven more files to go!

The natural first step is to collect the names of all the files that we have to process. In Python,
a list is a way to store multiple values together. In this episode, we will learn how to store
multiple values in a list as well as how to work with lists.

{% enddetails %}
{% details note Python lists %}

Unlike NumPy arrays, lists are built into the language so we do not have to load a library
to use them.
We create a list by putting values inside square brackets and separating the values with commas:

```python
odds = [1, 3, 5, 7]
print('odds are:', odds)
```

```output
odds are: [1, 3, 5, 7]
```

We can access elements of a list using indices -- numbered positions of elements in the list.
These positions are numbered starting at 0, so the first element has an index of 0.

```python
print('first element:', odds[0])
print('last element:', odds[3])
print('"-1" element:', odds[-1])
```

```output
first element: 1
last element: 7
"-1" element: 7
```

Yes, we can use negative numbers as indices in Python. When we do so, the index `-1` gives us the
last element in the list, `-2` the second to last, and so on. Because of this, `odds[3]` and `odds[-1]` point to the same element here.

There is one important difference between lists and strings: we can change the values in a list,
but we cannot change individual characters in a string. For example:

```python
names = ['Curie', 'Darwing', 'Turing']  # typo in Darwin's name
print('names is originally:', names)
names[1] = 'Darwin'  # correct the name
print('final value of names:', names)
```

```output
names is originally: ['Curie', 'Darwing', 'Turing']
final value of names: ['Curie', 'Darwin', 'Turing']
```

works, but:

```python
name = 'Darwin'
name[0] = 'd'
```

```error
---------------------------------------------------------------------------
TypeError                                 Traceback (most recent call last)
<ipython-input-8-220df48aeb2e> in <module>()
    1 name = 'Darwin'
----> 2 name[0] = 'd'

TypeError: 'str' object does not support item assignment
```

does not.

{% enddetails %}
{% details note Ch-Ch-Ch-Ch-Changes %}

Data which can be modified in place is called mutable while data which cannot be modified is called
immutable.
Strings and numbers are immutable. This does not mean that variables with string or number values
are constants, but when we want to change the value of a string or number variable, we can only
replace the old value with a completely new value.

Lists and arrays, on the other hand, are mutable: we can modify them after they have been
created. We can change individual elements, append new elements, or reorder the whole list. For
some operations, like sorting, we can choose whether to use a function that modifies the data
in-place or a function that returns a modified copy and leaves the original unchanged.

Be careful when modifying data in-place. If two variables refer to the same list, and you modify
the list value, it will change for both variables!

```python
mild_salsa = ['peppers', 'onions', 'cilantro', 'tomatoes']
hot_salsa = mild_salsa        # <-- mild_salsa and hot_salsa point to the *same* list data in memory
hot_salsa[0] = 'hot peppers'
print('Ingredients in mild salsa:', mild_salsa)
print('Ingredients in hot salsa:', hot_salsa)
```

```output
Ingredients in mild salsa: ['hot peppers', 'onions', 'cilantro', 'tomatoes']
Ingredients in hot salsa: ['hot peppers', 'onions', 'cilantro', 'tomatoes']
```

If you want variables with mutable values to be independent, you
must make a copy of the value when you assign it.

```python
mild_salsa = ['peppers', 'onions', 'cilantro', 'tomatoes']
hot_salsa = list(mild_salsa)        # <-- makes a *copy* of the list
hot_salsa[0] = 'hot peppers'
print('Ingredients in mild salsa:', mild_salsa)
print('Ingredients in hot salsa:', hot_salsa)
```

```output
Ingredients in mild salsa: ['peppers', 'onions', 'cilantro', 'tomatoes']
Ingredients in hot salsa: ['hot peppers', 'onions', 'cilantro', 'tomatoes']
```

Because of pitfalls like this, code which modifies data in place can be more difficult to
understand. However, it is often far more efficient to modify a large data structure in place
than to create a modified copy for every small change. You should consider both of these aspects
when writing your code.

{% enddetails %}

{% details note Nested Lists %}

Since a list can contain any Python variables, it can even contain other lists.

For example, you could represent the products on the shelves of a small grocery shop
as a nested list called `veg`:

{% include figure.liquid path="assets/img/courses/workshops/python_programming/04_groceries_veg.png" max-width="50%" zoomable=true alt='veg is represented as a shelf full of produce. There are three rows of vegetableson the shelf, and each row contains three baskets of vegetables. We can labeleach basket according to the type of vegetable it contains, so the top rowcontains (from left to right) lettuce, lettuce, and peppers.' %}

To store the contents of the shelf in a nested list, you write it this way:

```python
veg = [['lettuce', 'lettuce', 'peppers', 'zucchini'],
    ['lettuce', 'lettuce', 'peppers', 'zucchini'],
    ['lettuce', 'cilantro', 'peppers', 'zucchini']]
```

Here are some visual examples of how indexing a list of lists `veg` works. First,
you can reference each row on the shelf as a separate list. For example, `veg[2]`
represents the bottom row, which is a list of the baskets in that row.

{% include figure.liquid path="assets/img/courses/workshops/python_programming/04_groceries_veg0.png" max-width="50%" zoomable=true alt='veg is now shown as a list of three rows, with veg\[0\] representing the top row ofthree baskets, veg\[1\] representing the second row, and veg\[2\] representing the bottom row.' %}

Index operations using the image would work like this:

```python
print(veg[2])
```

```output
['lettuce', 'cilantro', 'peppers', 'zucchini']
```

```python
print(veg[0])
```

```output
['lettuce', 'lettuce', 'peppers', 'zucchini']
```

To reference a specific basket on a specific shelf, you use two indexes. The first
index represents the row (from top to bottom) and the second index represents the specific basket (from left to right).
{% include figure.liquid path="assets/img/courses/workshops/python_programming/04_groceries_veg00.png" max-width="50%" zoomable=true alt='veg is now shown as a two-dimensional grid, with each basket labeled according toits index in the nested list. The first index is the row number and the secondindex is the basket number, so veg\[1\]\[3\] represents the basket on the far rightside of the second row (basket 4 on row 2): zucchini' %}

```python
print(veg[0][0])
```

```output
'lettuce'
```

```python
print(veg[1][2])
```

```output
'peppers'
```

{% enddetails %}
{% details note Heterogeneous Lists %}

Lists in Python can contain elements of different types. Example:

```python
sample_ages = [10, 12.5, 'Unknown']
```

There are many ways to change the contents of lists besides assigning new values to
individual elements:

```python
odds.append(11)
print('odds after adding a value:', odds)
```

```output
odds after adding a value: [1, 3, 5, 7, 11]
```

```python
removed_element = odds.pop(0)
print('odds after removing the first element:', odds)
print('removed_element:', removed_element)
```

```output
odds after removing the first element: [3, 5, 7, 11]
removed_element: 1
```

```python
odds.reverse()
print('odds after reversing:', odds)
```

```output
odds after reversing: [11, 7, 5, 3]
```

While modifying in place, it is useful to remember that Python treats lists in a slightly
counter-intuitive way.

As we saw earlier, when we modified the `mild_salsa` list item in-place, if we make a list, (attempt to)
copy it and then modify this list, we can cause all sorts of trouble. This also applies to modifying
the list using the above functions:

```python
odds = [3, 5, 7]
primes = odds
primes.append(2)
print('primes:', primes)
print('odds:', odds)
```

```output
primes: [3, 5, 7, 2]
odds: [3, 5, 7, 2]
```

This is because Python stores a list in memory, and then can use multiple names to refer to the
same list. If all we want to do is copy a (simple) list, we can again use the `list` function, so we
do not modify a list we did not mean to:

```python
odds = [3, 5, 7]
primes = list(odds)
primes.append(2)
print('primes:', primes)
print('odds:', odds)
```

```output
primes: [3, 5, 7, 2]
odds: [3, 5, 7]
```

Subsets of lists and strings can be accessed by specifying ranges of values in brackets,
similar to how we accessed ranges of positions in a NumPy array.
This is commonly referred to as "slicing" the list/string.

```python
binomial_name = 'Drosophila melanogaster'
group = binomial_name[0:10]
print('group:', group)

species = binomial_name[11:23]
print('species:', species)

chromosomes = ['X', 'Y', '2', '3', '4']
autosomes = chromosomes[2:5]
print('autosomes:', autosomes)

last = chromosomes[-1]
print('last:', last)
```

```output
group: Drosophila
species: melanogaster
autosomes: ['2', '3', '4']
last: 4
```

{% enddetails %}
{% details Challenge 1: Slicing From the End %}

Use slicing to access only the last four characters of a string or entries of a list.

```python
string_for_slicing = 'Observation date: 02-Feb-2013'
list_for_slicing = [['fluorine', 'F'],
                    ['chlorine', 'Cl'],
                    ['bromine', 'Br'],
                    ['iodine', 'I'],
                    ['astatine', 'At']]
```

```output
'2013'
[['chlorine', 'Cl'], ['bromine', 'Br'], ['iodine', 'I'], ['astatine', 'At']]
```

Would your solution work regardless of whether you knew beforehand the length of the string or list
(e.g. if you wanted to apply the solution to a set of lists of different lengths)?
If not, try to change your approach to make it more robust.

Hint: Remember that indices can be negative as well as positive

{% details success Solution %}

Use negative indices to count elements from the end of a container (such as list or string):

```python
string_for_slicing[-4:]
list_for_slicing[-4:]
```

{% enddetails %}
{% enddetails %}
{% details Challenge 2: Non-Continuous Slices %}


So far we've seen how to use slicing to take single blocks
of successive entries from a sequence.
But what if we want to take a subset of entries
that aren't next to each other in the sequence?

You can achieve this by providing a third argument
to the range within the brackets, called the *step size*.
The example below shows how you can take every third entry in a list:

```python
primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
subset = primes[0:12:3]
print('subset', subset)
```

```output
subset [2, 7, 17, 29]
```

Notice that the slice taken begins with the first entry in the range,
followed by entries taken at equally-spaced intervals (the steps) thereafter.
If you wanted to begin the subset with the third entry,
you would need to specify that as the starting point of the sliced range:

```python
primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
subset = primes[2:12:3]
print('subset', subset)
```

```output
subset [5, 13, 23, 37]
```

Use the step size argument to create a new string
that contains only every other character in the string
"In an octopus's garden in the shade". Start with
creating a variable to hold the string:

```python
beatles = "In an octopus's garden in the shade"
```

What slice of `beatles` will produce the
following output (i.e., the first character, third
character, and every other character through the end
of the string)?

```output
I notpssgre ntesae
```

{% details success Solution %}

To obtain every other character you need to provide a slice with the step
size of 2:

```python
beatles[0:35:2]
```

You can also leave out the beginning and end of the slice to take the whole string
and provide only the step argument to go every second
element:

```python
beatles[::2]
```


If you want to take a slice from the beginning of a sequence, you can omit the first index in the
range:

```python
date = 'Monday 4 January 2016'
day = date[0:6]
print('Using 0 to begin range:', day)
day = date[:6]
print('Omitting beginning index:', day)
```

```output
Using 0 to begin range: Monday
Omitting beginning index: Monday
```

And similarly, you can omit the ending index in the range to take a slice to the very end of the
sequence:

```python
months = ['jan', 'feb', 'mar', 'apr', 'may', 'jun', 'jul', 'aug', 'sep', 'oct', 'nov', 'dec']
sond = months[8:12]
print('With known last position:', sond)
sond = months[8:len(months)]
print('Using len() to get last entry:', sond)
sond = months[8:]
print('Omitting ending index:', sond)
```

```output
With known last position: ['sep', 'oct', 'nov', 'dec']
Using len() to get last entry: ['sep', 'oct', 'nov', 'dec']
Omitting ending index: ['sep', 'oct', 'nov', 'dec']
```

{% enddetails %}
{% enddetails %}
{% details Challenge 3: Overloading %}

`+` usually means addition, but when used on strings or lists, it means "concatenate".
Given that, what do you think the multiplication operator `*` does on lists?
In particular, what will be the output of the following code?

```python
counts = [2, 4, 6, 8, 10]
repeats = counts * 2
print(repeats)
```

1. `[2, 4, 6, 8, 10, 2, 4, 6, 8, 10]`
2. `[4, 8, 12, 16, 20]`
3. `[[2, 4, 6, 8, 10], [2, 4, 6, 8, 10]]`
4. `[2, 4, 6, 8, 10, 4, 8, 12, 16, 20]`

The technical term for this is *operator overloading*:
a single operator, like `+` or `*`,
can do different things depending on what it's applied to.

{% details success Solution %}

The multiplication operator `*` used on a list replicates elements of the list and concatenates
them together:

```output
[2, 4, 6, 8, 10, 2, 4, 6, 8, 10]
```

It's equivalent to:

```python
counts + counts
```

{% enddetails %}
{% enddetails %}
{% details tip Keypoints %}

- `[value1, value2, value3, ...]` creates a list.
- Lists can contain any Python object, including lists (i.e., list of lists).
- Lists are indexed and sliced with square brackets (e.g., `list[0]` and `list[2:9]`), in the same way as strings and arrays.
- Lists are mutable (i.e., their values can be changed in place).
- Strings are immutable (i.e., the characters in them cannot be changed).


{% enddetails %}
## 5. Repeating Actions with Loops

{% details Abstract: Objectives %}

- Explain what a `for` loop does.
- Correctly write `for` loops to repeat simple calculations.
- Trace changes to a loop variable as the loop runs.
- Trace changes to other variables as they are updated by a `for` loop.

{% enddetails %}
{% details Questions %}

- How can I do the same operations on many different values?

{% enddetails %}
{% details note Overview %}

In the episode about visualizing data,
we wrote Python code that plots values of interest from our first
inflammation dataset (`inflammation-01.csv`), which revealed some suspicious features in it.

{% include figure.liquid path="assets/img/courses/workshops/python_programming/05-loop/03-loop_2_0.png" alt="Line graphs showing average, maximum and minimum inflammation across all patients over a 40-dayperiod." max-width="50%" zoomable=true %}

We have a dozen data sets right now and potentially more on the way if Dr. Maverick
can keep up their surprisingly fast clinical trial rate. We want to create plots for all of
our data sets with a single statement. To do that, we'll have to teach the computer how to
repeat things.

An example task that we might want to repeat is accessing numbers in a list,
which we
will do by printing each number on a line of its own.

```python
odds = [1, 3, 5, 7]
```

In Python, a list is basically an ordered collection of elements, and every
element has a unique number associated with it --- its index. This means that
we can access elements in a list using their indices.
For example, we can get the first number in the list `odds`,
by using `odds[0]`. One way to print each number is to use four `print` statements:

```python
print(odds[0])
print(odds[1])
print(odds[2])
print(odds[3])
```

```output
1
3
5
7
```

This is a bad approach for three reasons:

1. **Not scalable**. Imagine you need to print a list that has hundreds
of elements.  It might be easier to type them in manually.

2. **Difficult to maintain**. If we want to decorate each printed element with an
asterisk or any other character, we would have to change four lines of code. While
this might not be a problem for small lists, it would definitely be a problem for
longer ones.

3. **Fragile**. If we use it with a list that has more elements than what we initially
envisioned, it will only display part of the list's elements. A shorter list, on
the other hand, will cause an error because it will be trying to display elements of the
list that do not exist.

```python
odds = [1, 3, 5]
print(odds[0])
print(odds[1])
print(odds[2])
print(odds[3])
```

```output
1
3
5
```

```error
---------------------------------------------------------------------------
IndexError                                Traceback (most recent call last)
<ipython-input-3-7974b6cdaf14> in <module>()
    3 print(odds[1])
    4 print(odds[2])
----> 5 print(odds[3])

IndexError: list index out of range
```

Here's a better approach: a **for loop**

```python
odds = [1, 3, 5, 7]
for num in odds:
    print(num)
```

```output
1
3
5
7
```

This is shorter --- certainly shorter than something that prints every number in a
hundred-number list --- and more robust as well:

```python
odds = [1, 3, 5, 7, 9, 11]
for num in odds:
    print(num)
```

```output
1
3
5
7
9
11
```

The improved version uses a **for loop**
to repeat an operation --- in this case, printing --- once for each thing in a sequence.
The general form of a loop is:

```python
for variable in collection:
    # do things using variable, such as print
```

Using the odds example above, the loop might look like this:

{% include figure.liquid path="assets/img/courses/workshops/python_programming/05-loop/05-loops_image_num.png" alt="Loop variable 'num' being assigned the value of each element in the list odds in turn andthen being printed" max-width="50%" zoomable=true %}

where each number (`num`) in the variable `odds` is looped through and printed one number after
another. The other numbers in the diagram denote which loop cycle the number was printed in (1
being the first loop cycle, and 6 being the final loop cycle).

We can call the **loop variable** anything we like, but
there must be a colon at the end of the line starting the loop, and we must indent anything we
want to run inside the loop. Unlike many other languages, there is no command to signify the end
of the loop body (e.g. `end for`); everything indented after the `for` statement belongs to the loop.

{% enddetails %}
{% details note What's in a name? %}

In the example above, the loop variable was given the name `num` as a mnemonic;
it is short for 'number'.
We can choose any name we want for variables.  We might just as easily have chosen the name
`banana` for the loop variable, as long as we use the same name when we invoke the variable inside
the loop:

```python
odds = [1, 3, 5, 7, 9, 11]
for banana in odds:
    print(banana)
```

```output
1
3
5
7
9
11
```

It is a good idea to choose variable names that are meaningful, otherwise it would be more
difficult to understand what the loop is doing.

Here's another loop that repeatedly updates a variable:

```python
length = 0
names = ['Curie', 'Darwin', 'Turing']
for value in names:
    length = length + 1
print('There are', length, 'names in the list.')
```

```output
There are 3 names in the list.
```

It's worth tracing the execution of this little program step by step. Since there are three names in `names`,
the statement on line 4 will be executed three times. 

- The first time around, `length` is zero (the value assigned to it on line 1) 
and `value` is `Curie`. The statement adds 1 to the old value of `length`, producing 1, 
and updates `length` to refer to that new value.
- The next time around, `value` is `Darwin` and `length` is 1, so `length` is updated to be 2.
- After one more update, `length` is 3; since there is nothing left in `names` for Python to process,
the loop finishes and the `print` function on line 5 tells us our final answer.

Note that a loop variable is a variable that is being used to record progress in a loop.
It still exists after the loop is over,
and we can re-use variables previously defined as loop variables as well:

```python
name = 'Rosalind'
for name in ['Curie', 'Darwin', 'Turing']:
    print(name)
print('after the loop, name is', name)
```

```output
Curie
Darwin
Turing
after the loop, name is Turing
```

Note also that finding the length of an object is such a common operation
that Python actually has a built-in function to do it called `len`:

```python
print(len([0, 1, 2, 3]))
```

```output
4
```

`len` is much faster than any function we could write ourselves,
and much easier to read than a two-line loop;
it will also give us the length of many other things that we haven't met yet,
so we should always use it when we can.

{% enddetails %}
{% details Challenge 1: From 1 to N %}

Python has a built-in function called `range` that generates a sequence of numbers. `range` can
accept 1, 2, or 3 parameters.

- If one parameter is given, `range` generates a sequence of that length,
starting at zero and incrementing by 1.
For example, `range(3)` produces the numbers `0, 1, 2`.
- If two parameters are given, `range` starts at
the first and ends just before the second, incrementing by one.
For example, `range(2, 5)` produces `2, 3, 4`.
- If `range` is given 3 parameters,
it starts at the first one, ends just before the second one, and increments by the third one.
For example, `range(3, 10, 2)` produces `3, 5, 7, 9`.

Using `range`,
write a loop that prints the first 3 natural numbers:

```python
1
2
3
```

{% details success Solution %}

```python
for number in range(1, 4):
    print(number)
```

{% enddetails %}
{% enddetails %}
{% details Challenge 2: Understanding the loops %}


Given the following loop:

```python
word = 'oxygen'
for letter in word:
    print(letter)
```

How many times is the body of the loop executed?

- 3 times
- 4 times
- 5 times
- 6 times

{% details success Solution %}

{% enddetails %}
The body of the loop is executed 6 times.



{% enddetails %}
{% details Challenge 3: Computing Powers With Loops %}

Exponentiation is built into Python:

```python
print(5 ** 3)
```

```output
125
```

Write a loop that calculates the same result as `5 ** 3` using
multiplication (and without exponentiation).

{% details success Solution %}

{% enddetails %}
```python
result = 1
for number in range(0, 3):
    result = result * 5
print(result)
```
{% enddetails %}
{% details Challenge 4: Summing a list %}

Write a loop that calculates the sum of elements in a list
by adding each element and printing the final value,
so `[124, 402, 36]` prints 562

{% details success Solution %}

```python
numbers = [124, 402, 36]
summed = 0
for num in numbers:
    summed = summed + num
print(summed)
```

{% enddetails %}
{% enddetails %}
{% details Challenge 5: Computing the Value of a Polynomial %}

The built-in function `enumerate` takes a sequence (e.g. a list) and
generates a new sequence of the same length. Each element of the new sequence is a pair composed
of the index (0, 1, 2,...) and the value from the original sequence:

```python
for idx, val in enumerate(a_list):
    # Do something using idx and val
```

The code above loops through `a_list`, assigning the index to `idx` and the value to `val`.

Suppose you have encoded a polynomial as a list of coefficients in
the following way: the first element is the constant term, the
second element is the coefficient of the linear term, the third is the
coefficient of the quadratic term, etc.

```python
x = 5
coefs = [2, 4, 3]
y = coefs[0] * x**0 + coefs[1] * x**1 + coefs[2] * x**2
print(y)
```

```output
97
```

Write a loop using `enumerate(coefs)` which computes the value `y` of any
polynomial, given `x` and `coefs`.

{% details success Solution %}

{% enddetails %}
```python
y = 0
for idx, coef in enumerate(coefs):
    y = y + coef * x**idx
```

{% enddetails %}
{% details tip Keypoints %}

- Use `for variable in sequence` to process the elements of a sequence one at a time.
- The body of a `for` loop must be indented.
- Use `len(thing)` to determine the length of something that contains other values.

{% enddetails %}
## 6. Analyzing Data from Multiple Files

{% details Abstract: Objectives %}

- Use a library function to get a list of filenames that match a wildcard pattern.
- Write a `for` loop to process multiple files.


{% enddetails %}
{% details Questions %}

- How can I do the same operations on many different files?

{% enddetails %}
{% details note Overview %}

As a final piece to processing our inflammation data, we need a way to get a list of all the files
in our `data` directory whose names start with `inflammation-` and end with `.csv`.
The following library will help us to achieve this:

```python
import glob
```

The `glob` library contains a function, also called `glob`, that finds files and directories whose names match a pattern.
We provide those patterns as strings: the character `*` matches zero or more characters,
while `?` matches any one character. We can use this to get the names of all the CSV files in the current directory:

```python
print(glob.glob('data/inflammation*.csv'))
```

```output
['data/inflammation-05.csv', 'data/inflammation-11.csv', 'data/inflammation-12.csv', 'data/inflammation-08.csv',
'data/inflammation-03.csv', 'data/inflammation-06.csv', 'data/inflammation-09.csv', 'data/inflammation-07.csv',
'data/inflammation-10.csv', 'data/inflammation-02.csv', 'data/inflammation-04.csv', 'data/inflammation-01.csv']
```

As these examples show, `glob.glob`'s result is a list of file and directory paths in arbitrary order.
This means we can loop over it to do something with each filename in turn.
In our case, the "something" we want to do is generate a set of plots for each file in our inflammation dataset.

If we want to start by analyzing just the first three files in alphabetical order, we can use the
`sorted` built-in function to generate a new sorted list from the `glob.glob` output:

```python
import glob
import numpy
import matplotlib.pyplot

filenames = sorted(glob.glob('data/inflammation*.csv'))
filenames = filenames[0:3]
for filename in filenames:
    print(filename)

    data = numpy.loadtxt(fname=filename, delimiter=',')

    fig = matplotlib.pyplot.figure(figsize=(10.0, 3.0))

    axes1 = fig.add_subplot(1, 3, 1)
    axes2 = fig.add_subplot(1, 3, 2)
    axes3 = fig.add_subplot(1, 3, 3)

    axes1.set_ylabel('average')
    axes1.plot(numpy.mean(data, axis=0))

    axes2.set_ylabel('max')
    axes2.plot(numpy.amax(data, axis=0))

    axes3.set_ylabel('min')
    axes3.plot(numpy.amin(data, axis=0))

    fig.tight_layout()
    matplotlib.pyplot.show()
```

```output
inflammation-01.csv
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/03-loop_49_1.png" max-width="50%" zoomable=true alt='Output from the first iteration of the for loop. Three line graphs showing the daily average, maximum and minimum inflammation over a 40-day period for all patients in the first dataset.'%}

```output
inflammation-02.csv
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/03-loop_49_3.png" max-width="50%" zoomable=true alt='Output from the second iteration of the for loop. Three line graphs showing the daily average, maximum and minimum inflammation over a 40-day period for all patients in the seconddataset.' %}

```output
inflammation-03.csv
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/03-loop_49_5.png" max-width="50%" zoomable=true alt='Output from the third iteration of the for loop. Three line graphs showing the daily average, maximum and minimum inflammation over a 40-day period for all patients in the thirddataset.' %}

The plots generated for the second clinical trial file look very similar to the plots for
the first file: their average plots show similar "noisy" rises and falls; their maxima plots
show exactly the same linear rise and fall; and their minima plots show similar staircase
structures.

The third dataset shows much noisier average and maxima plots that are far less suspicious than
the first two datasets, however the minima plot shows that the third dataset minima is
consistently zero across every day of the trial. If we produce a heat map for the third data file
we see the following:

{% include figure.liquid path="assets/img/courses/workshops/python_programming/inflammation-03-imshow.svg" max-width="50%" zoomable=true alt='Heat map of the third inflammation dataset. Note that there are sporadic zero values throughoutthe entire dataset, and the last patient only has zero values over the 40 day study.' %}

We can see that there are zero values sporadically distributed across all patients and days of the
clinical trial, suggesting that there were potential issues with data collection throughout the
trial. In addition, we can see that the last patient in the study didn't have any inflammation
flare-ups at all throughout the trial, suggesting that they may not even suffer from arthritis!

{% enddetails %}
{% details Challenge 1: Plotting Differences %}


Plot the difference between the average inflammations reported in the first and second datasets
(stored in `inflammation-01.csv` and `inflammation-02.csv`, correspondingly),
i.e., the difference between the leftmost plots of the first two figures.

{% details success Solution %}

```python
import glob
import numpy
import matplotlib.pyplot

filenames = sorted(glob.glob('data/inflammation*.csv'))

data0 = numpy.loadtxt(fname=filenames[0], delimiter=',')
data1 = numpy.loadtxt(fname=filenames[1], delimiter=',')

fig = matplotlib.pyplot.figure(figsize=(10.0, 3.0))

matplotlib.pyplot.ylabel('Difference in average')
matplotlib.pyplot.plot(numpy.mean(data0, axis=0) - numpy.mean(data1, axis=0))

fig.tight_layout()
matplotlib.pyplot.show()
```

{% enddetails %}
{% enddetails %}
{% details Challenge 2: Generate Composite Statistics %}

Use each of the files once to generate a dataset containing values averaged over all patients by completing the code inside the loop given below:

```python
filenames = glob.glob('data/inflammation*.csv')
composite_data = numpy.zeros((60, 40))
for filename in filenames:
    # sum each new file's data into composite_data as it's read
    #
# and then divide the composite_data by number of samples
composite_data = composite_data / len(filenames)
```

Then use pyplot to generate average, max, and min for all patients.

{% details success Solution %}


```python
import glob
import numpy
import matplotlib.pyplot

filenames = glob.glob('data/inflammation*.csv')
composite_data = numpy.zeros((60, 40))

for filename in filenames:
    data = numpy.loadtxt(fname = filename, delimiter=',')
    composite_data = composite_data + data

composite_data = composite_data / len(filenames)

fig = matplotlib.pyplot.figure(figsize=(10.0, 3.0))

axes1 = fig.add_subplot(1, 3, 1)
axes2 = fig.add_subplot(1, 3, 2)
axes3 = fig.add_subplot(1, 3, 3)

axes1.set_ylabel('average')
axes1.plot(numpy.mean(composite_data, axis=0))

axes2.set_ylabel('max')
axes2.plot(numpy.amax(composite_data, axis=0))

axes3.set_ylabel('min')
axes3.plot(numpy.amin(composite_data, axis=0))

fig.tight_layout()

matplotlib.pyplot.show()
```

{% enddetails %}
After spending some time investigating the heat map and statistical plots, as well as
doing the above exercises to plot differences between datasets and to generate composite
patient statistics, we gain some insight into the twelve clinical trial datasets.

The datasets appear to fall into two categories:

- seemingly "ideal" datasets that agree excellently with Dr. Maverick's claims,
but display suspicious maxima and minima (such as `inflammation-01.csv` and `inflammation-02.csv`)
- "noisy" datasets that somewhat agree with Dr. Maverick's claims, but show concerning
data collection issues such as sporadic missing values and even an unsuitable candidate
making it into the clinical trial.

In fact, it appears that all three of the "noisy" datasets (`inflammation-03.csv`,
`inflammation-08.csv`, and `inflammation-11.csv`) are identical down to the last value.
Armed with this information, we confront Dr. Maverick about the suspicious data and
duplicated files.

Dr. Maverick has admitted to fabricating the clinical data for their drug trial. They did this after discovering that the initial trial had several issues, including unreliable data recording and poor participant selection. In order to prove the efficacy of their drug, they created fake data. When asked for additional data, they attempted to generate more fake datasets, and also included the original poor-quality dataset several times in order to make the trials seem more realistic.

Congratulations! We've investigated the inflammation data and proven that the datasets have been
synthetically generated.

But it would be a shame to throw away the synthetic datasets that have taught us so much
already, so we'll forgive the imaginary Dr. Maverick and continue to use the data to learn
how to program.

{% enddetails %}
{% details tip Keypoints %}


- Use `glob.glob(pattern)` to create a list of files whose names match a pattern.
- Use `*` in a pattern to match zero or more characters, and `?` to match any single character.

{% enddetails %}
## 7. Making Choices

{% details Abstract: Objectives %}


- Write conditional statements including `if`, `elif`, and `else` branches.
- Correctly evaluate expressions containing `and` and `or`.

{% enddetails %}
{% details Questions %}


- How can my programs do different things based on data values?

In our last lesson, we discovered something suspicious was going on
in our inflammation data by drawing some plots.
How can we use Python to automatically recognize the different features we saw,
and take a different action for each? In this lesson, we'll learn how to write code that
runs only when certain conditions are true.

{% enddetails %}
{% details note Conditionals %}

We can ask Python to take different actions, depending on a condition, with an `if` statement:

```python
num = 37
if num > 100:
    print('greater')
else:
    print('not greater')
print('done')
```

```output
not greater
done
```

The second line of this code uses the keyword `if` to tell Python that we want to make a choice.
If the test that follows the `if` statement is true,
the body of the `if`
(i.e., the set of lines indented underneath it) is executed, and "greater" is printed.
If the test is false,
the body of the `else` is executed instead, and "not greater" is printed.
Only one or the other is ever executed before continuing on with program execution to print "done":

{% include figure.liquid path="assets/img/courses/workshops/python_programming/python-flowchart-conditional.png" max-width="50%" zoomable=true alt='A flowchart diagram of the if-else construct that tests if variable num is greater than 100' %}

Conditional statements don't have to include an `else`.
If there isn't one,
Python simply does nothing if the test is false:

```python
num = 53
print('before conditional...')
if num > 100:
    print(num, 'is greater than 100')
print('...after conditional')
```

```output
before conditional...
...after conditional
```

We can also chain several tests together using `elif`,
which is short for "else if".
The following Python code uses `elif` to print the sign of a number.

```python
num = -3

if num > 0:
    print(num, 'is positive')
elif num == 0:
    print(num, 'is zero')
else:
    print(num, 'is negative')
```

```output
-3 is negative
```

Note that to test for equality we use a double equals sign `==`
rather than a single equals sign `=` which is used to assign values.

{admonition} Comparing in Python

Along with the `>` and `==` operators we have already used for comparing values in our
conditionals, there are a few more options to know about:

- `>`: greater than
- `<`: less than
- `==`: equal to
- `!=`: does not equal
- `>=`: greater than or equal to
- `<=`: less than or equal to

We can also combine tests using `and` and `or`.
`and` is only true if both parts are true:

```python
if (1 > 0) and (-1 >= 0):
    print('both parts are true')
else:
    print('at least one part is false')
```

```output
at least one part is false
```

while `or` is true if at least one part is true:

```python
if (1 < 0) or (1 >= 0):
    print('at least one test is true')
```

```output
at least one test is true
```

{% enddetails %}
{% details note True and False %}

`True` and `False` are special words in Python called `booleans`,
which represent truth values. A statement such as `1 < 0` returns
the value `False`, while `-1 < 0` returns the value `True`.

{% enddetails %}
{% details note Checking our Data %}

Now that we've seen how conditionals work,
we can use them to check for the suspicious features we saw in our inflammation data.
We are about to use functions provided by the `numpy` module again.
Therefore, if you're working in a new Python session, make sure to load the
module with:

```python
import numpy
```

From the first couple of plots, we saw that maximum daily inflammation exhibits
a strange behavior and raises one unit a day.
Wouldn't it be a good idea to detect such behavior and report it as suspicious?
Let's do that!
However, instead of checking every single day of the study, let's merely check
if maximum inflammation in the beginning (day 0) and in the middle (day 20) of
the study are equal to the corresponding day numbers.

```python
max_inflammation_0 = numpy.amax(data, axis=0)[0]
max_inflammation_20 = numpy.amax(data, axis=0)[20]

if max_inflammation_0 == 0 and max_inflammation_20 == 20:
    print('Suspicious looking maxima!')
```

We also saw a different problem in the third dataset;
the minima per day were all zero (looks like a healthy person snuck into our study).
We can also check for this with an `elif` condition:

```python
elif numpy.sum(numpy.amin(data, axis=0)) == 0:
    print('Minima add up to zero!')
```

And if neither of these conditions are true, we can use `else` to give the all-clear:

```python
else:
    print('Seems OK!')
```

Let's test that out:

```python
data = numpy.loadtxt(fname='data/inflammation-01.csv', delimiter=',')

max_inflammation_0 = numpy.amax(data, axis=0)[0]
max_inflammation_20 = numpy.amax(data, axis=0)[20]

if max_inflammation_0 == 0 and max_inflammation_20 == 20:
    print('Suspicious looking maxima!')
elif numpy.sum(numpy.amin(data, axis=0)) == 0:
    print('Minima add up to zero!')
else:
    print('Seems OK!')
```

```output
Suspicious looking maxima!
```

```python
data = numpy.loadtxt(fname='data/inflammation-03.csv', delimiter=',')

max_inflammation_0 = numpy.amax(data, axis=0)[0]
max_inflammation_20 = numpy.amax(data, axis=0)[20]

if max_inflammation_0 == 0 and max_inflammation_20 == 20:
    print('Suspicious looking maxima!')
elif numpy.sum(numpy.amin(data, axis=0)) == 0:
    print('Minima add up to zero!')
else:
    print('Seems OK!')
```

```output
Minima add up to zero!
```

In this way, we have asked Python to do something different depending on the condition of our data.
Here we printed messages in all cases, but we could also imagine not using the `else` catch-all
so that messages are only printed when something is wrong, freeing us from having to manually examine every plot for features we've seen before.

{% enddetails %}
{% details Challenge 1: How Many Paths? %}

Consider this code:

```python
if 4 > 5:
    print('A')
elif 4 == 5:
    print('B')
elif 4 < 5:
    print('C')
```

Which of the following would be printed if you were to run this code?
Why did you pick this answer?

1. A
2. B
3. C
4. B and C

{% details success Solution %}

C gets printed because the first two conditions, `4 > 5` and `4 == 5`, are not true,
but `4 < 5` is true.
In this case only one of these conditions can be true for at a time, but in other
scenarios multiple `elif` conditions could be met. In these scenarios only the action
associated with the first true `elif` condition will occur, starting from the top of the
conditional section.
{% include figure.liquid path="assets/img/courses/workshops/python_programming/python-else-if.png" max-width="50%" zoomable=true alt='A flowchart diagram of a conditional section with multiple elif conditions and some possible outcomes.' %}
This contrasts with the case of multiple `if` statements, where every action can occur
as long as their condition is met.
{% include figure.liquid path="assets/img/courses/workshops/python_programming/python-multi-if.png" max-width="50%" zoomable=true alt='A flowchart diagram of a conditional section with multiple if statements and some possible outcomes.' %}

{% enddetails %}
{% enddetails %}
{% details note What Is Truth? %}

`True` and `False` booleans are not the only values in Python that are true and false.
In fact, *any* value can be used in an `if` or `elif`.
After reading and running the code below,
explain what the rule is for which values are considered true and which are considered false.

```python
if '':
    print('empty string is true')
if 'word':
    print('word is true')
if []:
    print('empty list is true')
if [1, 2, 3]:
    print('non-empty list is true')
if 0:
    print('zero is true')
if 1:
    print('one is true')
```

{% enddetails %}
{% details note That's Not Not What I Meant %}

Sometimes it is useful to check whether some condition is not true.
The Boolean operator `not` can do this explicitly.
After reading and running the code below,
write some `if` statements that use `not` to test the rule
that you formulated in the previous challenge.

```python
if not '':
    print('empty string is not true')
if not 'word':
    print('word is not true')
if not not True:
    print('not not True is true')
```

{% enddetails %}
{% details Challenge 2: Close Enough %}

Write some conditions that print `True` if the variable `a` is within 10% of the variable `b`
and `False` otherwise.
Compare your implementation with your partner's:
do you get the same answer for all possible pairs of numbers?

There is a built-in function `abs` that returns the absolute value of
a number:

```python
print(abs(-12))
```

```output
12
```

{% details success Solution 1 %}

```python
a = 5
b = 5.1

if abs(a - b) <= 0.1 * abs(b):
    print('True')
else:
    print('False')
```


{% enddetails %}
{% details success Solution 2 %}

```python
print(abs(a - b) <= 0.1 * abs(b))
```
This works because the Booleans `True` and `False`
have string representations which can be printed.


{% enddetails %}
{% enddetails %}
{% details Challenge 3: In-Place Operators %}

Python (and most other languages in the C family) provides
in-place operators that work like this:

```python
x = 1  # original value
x += 1 # add one to x, assigning result back to x
x *= 3 # multiply x by 3
print(x)
```

```output
6
```

Write some code that sums the positive and negative numbers in a list separately,
using in-place operators.
Do you think the result is more or less readable
than writing the same without in-place operators?

{% details success Solution" 1 %}

```python
positive_sum = 0
negative_sum = 0
test_list = [3, 4, 6, 1, -1, -5, 0, 7, -8]
for num in test_list:
    if num > 0:
        positive_sum += num
    elif num == 0:
        pass
    else:
        negative_sum += num
print(positive_sum, negative_sum)
```

Here `pass` means "don't do anything".
In this particular case, it's not actually needed, since if `num == 0` neither
sum needs to change, but it illustrates the use of `elif` and `pass`.

{% enddetails %}
{% enddetails %}
{% details Challenge 4: Sorting a List Into Buckets %}

In our `data` folder, large data sets are stored in files whose names start with
"inflammation-" and small data sets -- in files whose names start with "small-". We
also have some other files that we do not care about at this point. We'd like to break all
these files into three lists called `large_files`, `small_files`, and `other_files`,
respectively.

Add code to the template below to do this. Note that the string method
[`startswith`](https://docs.python.org/3/library/stdtypes.html#str.startswith)
returns `True` if and only if the string it is called on starts with the string
passed as an argument, that is:

```python
'String'.startswith('Str')
```

```output
True
```

But

```python
'String'.startswith('str')
```

```output
False
```

Use the following Python code as your starting point:

```python
filenames = ['data/inflammation-01.csv',
        'myscript.py',
        'data/inflammation-02.csv',
        'small-01.csv',
        'small-02.csv']
large_files = []
small_files = []
other_files = []
```

Your solution should:

1. loop over the names of the files
2. figure out which group each filename belongs in
3. append the filename to that list

In the end the three lists should be:

```python
large_files = ['data/inflammation-01.csv', 'data/inflammation-02.csv']
small_files = ['small-01.csv', 'small-02.csv']
other_files = ['myscript.py']
```

{% details success Solution %}

```python
for filename in filenames:
    if filename.startswith('data/inflammation-'):
        large_files.append(filename)
    elif filename.startswith('small-'):
        small_files.append(filename)
    else:
        other_files.append(filename)

print('large_files:', large_files)
print('small_files:', small_files)
print('other_files:', other_files)
```

{% enddetails %}
{% enddetails %}
{% details Challenge 5: Counting Vowels %}


1. Write a loop that counts the number of vowels in a character string.
2. Test it on a few individual words and full sentences.
3. Once you are done, compare your solution to your neighbor's.
Did you make the same decisions about how to handle the letter 'y'
(which some people think is a vowel, and some do not)?

{% details success Solution %}

```python
vowels = 'aeiouAEIOU'
sentence = 'Mary had a little lamb.'
count = 0
for char in sentence:
    if char in vowels:
        count += 1

print('The number of vowels in this string is ' + str(count))
```

{% enddetails %}
[abs-function]: https://docs.python.org/3/library/functions.html#abs

{% enddetails %}
{% details tip Keypoints %}


- Use `if condition` to start a conditional statement, `elif condition` to provide additional tests, and `else` to provide a default.
- The bodies of the branches of conditional statements must be indented.
- Use `==` to test for equality.
- `X and Y` is only true if both `X` and `Y` are true.
- `X or Y` is true if either `X` or `Y`, or both, are true.
- Zero, the empty string, and the empty list are considered false; all other numbers, strings, and lists are considered true.
- `True` and `False` represent truth values.

{% enddetails %}
## 8. Creating Functions

{% details Abstract: Objectives %}

- Define a function that takes parameters.
- Return a value from a function.
- Test and debug a function.
- Set default values for function parameters.
- Explain why we should divide programs into small, single-purpose functions.

{% enddetails %}
{% details Questions %}

- How can I define new functions?
- What's the difference between defining and calling a function?
- What happens when I call a function?

{% enddetails %}
{% details note Overview %}

At this point, we've seen that code can have Python make decisions about what it sees in our data. What if we want to convert some of our data, like taking a temperature in Fahrenheit and converting it to Celsius. We could write something like this for converting a single number

```python
fahrenheit_val = 99
celsius_val = ((fahrenheit_val - 32) * (5/9))
```

and for a second number we could just copy the line and rename the variables

```python
fahrenheit_val = 99
celsius_val = ((fahrenheit_val - 32) * (5/9))

fahrenheit_val2 = 43
celsius_val2 = ((fahrenheit_val2 - 32) * (5/9))
```

But we would be in trouble as soon as we had to do this more than a couple times.
Cutting and pasting it is going to make our code get very long and very repetitive,
very quickly.
We'd like a way to package our code so that it is easier to reuse,
a shorthand way of re-executing longer pieces of code. In Python we can use 'functions'.
Let's start by defining a function `fahr_to_celsius` that converts temperatures
from Fahrenheit to Celsius:

```python
def explicit_fahr_to_celsius(temp):
    # Assign the converted value to a variable
    converted = ((temp - 32) * (5/9))
    # Return the value of the new variable
    return converted

def fahr_to_celsius(temp):
    # Return converted value more efficiently using the return
    # function without creating a new variable. This code does
    # the same thing as the previous function but it is more explicit
    # in explaining how the return command works.
    return ((temp - 32) * (5/9))
```

{% include figure.liquid path="assets/img/courses/workshops/python_programming/python-function.svg" max-width="50%" zoomable=true alt='Labeled parts of a Python function definition' %}

The function definition opens with the keyword `def` followed by the
name of the function (`fahr_to_celsius`) and a parenthesized list of parameter names (`temp`). The
body of the function --- the
statements that are executed when it runs --- is indented below the
definition line.  The body concludes with a `return` keyword followed by the return value.

When we call the function,
the values we pass to it are assigned to those variables
so that we can use them inside the function.
Inside the function,
we use a return statement to send a result
back to whoever asked for it.

Let's try running our function.

```python
fahr_to_celsius(32)
```

This command should call our function, using "32" as the input and return the function value.

In fact, calling our own function is no different from calling any other function:

```python
print('freezing point of water:', fahr_to_celsius(32), 'C')
print('boiling point of water:', fahr_to_celsius(212), 'C')
```

```output
freezing point of water: 0.0 C
boiling point of water: 100.0 C
```

We've successfully called the function that we defined,
and we have access to the value that we returned.

{% enddetails %}
{% details note Composing Functions %}


Now that we've seen how to turn Fahrenheit into Celsius,
we can also write the function to turn Celsius into Kelvin:

```python
def celsius_to_kelvin(temp_c):
    return temp_c + 273.15

print('freezing point of water in Kelvin:', celsius_to_kelvin(0.))
```

```output
freezing point of water in Kelvin: 273.15
```

What about converting Fahrenheit to Kelvin?
We could write out the formula,
but we don't need to.
Instead,
we can compose the two functions we have already created:

```python
def fahr_to_kelvin(temp_f):
    temp_c = fahr_to_celsius(temp_f)
    temp_k = celsius_to_kelvin(temp_c)
    return temp_k

print('boiling point of water in Kelvin:', fahr_to_kelvin(212.0))
```

```output
boiling point of water in Kelvin: 373.15
```

This is our first taste of how larger programs are built:
we define basic operations,
then combine them in ever-larger chunks to get the effect we want.
Real-life functions will usually be larger than the ones shown here --- typically half a dozen
to a few dozen lines --- but they shouldn't ever be much longer than that,
or the next person who reads it won't be able to understand what's going on.

{% enddetails %}
{% details note Variable Scope %}

In composing our temperature conversion functions, we created variables inside of those functions,
`temp`, `temp_c`, `temp_f`, and `temp_k`.
We refer to these variables as local variables
because they no longer exist once the function is done executing.
If we try to access their values outside of the function, we will encounter an error:

```python
print('Again, temperature in Kelvin was:', temp_k)
```

```error
---------------------------------------------------------------------------
NameError                                 Traceback (most recent call last)
<ipython-input-1-eed2471d229b> in <module>
----> 1 print('Again, temperature in Kelvin was:', temp_k)

NameError: name 'temp_k' is not defined
```

If you want to reuse the temperature in Kelvin after you have calculated it with `fahr_to_kelvin`,
you can store the result of the function call in a variable:

```python
temp_kelvin = fahr_to_kelvin(212.0)
print('temperature in Kelvin was:', temp_kelvin)
```

```output
temperature in Kelvin was: 373.15
```

The variable `temp_kelvin`, being defined outside any function,
is said to be global.

Inside a function, one can read the value of such global variables:

```python
def print_temperatures():
print('temperature in Fahrenheit was:', temp_fahr)
print('temperature in Kelvin was:', temp_kelvin)

temp_fahr = 212.0
temp_kelvin = fahr_to_kelvin(temp_fahr)

print_temperatures()
```

```output
temperature in Fahrenheit was: 212.0
temperature in Kelvin was: 373.15
```

{% enddetails %}
{% details note Tidying up %}

Now that we know how to wrap bits of code up in functions,
we can make our inflammation analysis easier to read and easier to reuse.
First, let's make a `visualize` function that generates our plots:

```python
def visualize(filename):

    data = numpy.loadtxt(fname=filename, delimiter=',')

    fig = matplotlib.pyplot.figure(figsize=(10.0, 3.0))

    axes1 = fig.add_subplot(1, 3, 1)
    axes2 = fig.add_subplot(1, 3, 2)
    axes3 = fig.add_subplot(1, 3, 3)

    axes1.set_ylabel('average')
    axes1.plot(numpy.mean(data, axis=0))

    axes2.set_ylabel('max')
    axes2.plot(numpy.amax(data, axis=0))

    axes3.set_ylabel('min')
    axes3.plot(numpy.amin(data, axis=0))

    fig.tight_layout()
    matplotlib.pyplot.show()
```

and another function called `detect_problems` that checks for those systematics
we noticed:

```python
def detect_problems(filename):

    data = numpy.loadtxt(fname=filename, delimiter=',')

    if numpy.amax(data, axis=0)[0] == 0 and numpy.amax(data, axis=0)[20] == 20:
        print('Suspicious looking maxima!')
    elif numpy.sum(numpy.amin(data, axis=0)) == 0:
        print('Minima add up to zero!')
    else:
        print('Seems OK!')
```

Wait! Didn't we forget to specify what both of these functions should return? Well, we didn't.
In Python, functions are not required to include a `return` statement and can be used for
the sole purpose of grouping together pieces of code that conceptually do one thing. In such cases,
function names usually describe what they do, *e.g.* `visualize`, `detect_problems`.

Notice that rather than jumbling this code together in one giant `for` loop,
we can now read and reuse both ideas separately.
We can reproduce the previous analysis with a much simpler `for` loop:

```python
filenames = sorted(glob.glob('data/inflammation*.csv'))

for filename in filenames[:3]:
    print(filename)
    visualize(filename)
    detect_problems(filename)
```

By giving our functions human-readable names,
we can more easily read and understand what is happening in the `for` loop.
Even better, if at some later date we want to use either of those pieces of code again,
we can do so in a single line.

{% enddetails %}
{% details note Testing and Documenting %}


Once we start putting things in functions so that we can re-use them,
we need to start testing that those functions are working correctly.
To see how to do this,
let's write a function to offset a dataset so that it's mean value
shifts to a user-defined value:

```python
def offset_mean(data, target_mean_value):
    return (data - numpy.mean(data)) + target_mean_value
```

We could test this on our actual data,
but since we don't know what the values ought to be,
it will be hard to tell if the result was correct.
Instead,
let's use NumPy to create a matrix of 0's
and then offset its values to have a mean value of 3:

```python
z = numpy.zeros((2, 2))
print(offset_mean(z, 3))
```

```output
[[ 3.  3.]
[ 3.  3.]]
```

That looks right,
so let's try `offset_mean` on our real data:

```python
data = numpy.loadtxt(fname='data/inflammation-01.csv', delimiter=',')
print(offset_mean(data, 0))
```

```output
[[-6.14875 -6.14875 -5.14875 ... -3.14875 -6.14875 -6.14875]
[-6.14875 -5.14875 -4.14875 ... -5.14875 -6.14875 -5.14875]
[-6.14875 -5.14875 -5.14875 ... -4.14875 -5.14875 -5.14875]
...
[-6.14875 -5.14875 -5.14875 ... -5.14875 -5.14875 -5.14875]
[-6.14875 -6.14875 -6.14875 ... -6.14875 -4.14875 -6.14875]
[-6.14875 -6.14875 -5.14875 ... -5.14875 -5.14875 -6.14875]]
```

It's hard to tell from the default output whether the result is correct,
but there are a few tests that we can run to reassure us:

```python
print('original min, mean, and max are:', numpy.amin(data), numpy.mean(data), numpy.amax(data))
offset_data = offset_mean(data, 0)
print('min, mean, and max of offset data are:',
    numpy.amin(offset_data),
    numpy.mean(offset_data),
    numpy.amax(offset_data))
```

```output
original min, mean, and max are: 0.0 6.14875 20.0
min, mean, and max of offset data are: -6.14875 2.842170943040401e-16 13.85125
```

That seems almost right:
the original mean was about 6.1,
so the lower bound from zero is now about -6.1.
The mean of the offset data isn't quite zero, but it's pretty close.
We can even go further and check that the standard deviation hasn't changed:

```python
print('std dev before and after:', numpy.std(data), numpy.std(offset_data))
```

```output
std dev before and after: 4.613833197118566 4.613833197118566
```

Those values look the same,
but we probably wouldn't notice if they were different in the sixth decimal place.
Let's do this instead:

```python
print('difference in standard deviations before and after:',
    numpy.std(data) - numpy.std(offset_data))
```

```output
difference in standard deviations before and after: 0.0
```

Everything looks good,
and we should probably get back to doing our analysis.
We have one more task first, though:
we should write some documentation for our function
to remind ourselves later what it's for and how to use it.

The usual way to put documentation in software is
to add comments like this:

```python
# offset_mean(data, target_mean_value):
# return a new array containing the original data with its mean offset to match the desired value.
def offset_mean(data, target_mean_value):
    return (data - numpy.mean(data)) + target_mean_value
```

There's a better way, though.
If the first thing in a function is a string that isn't assigned to a variable,
that string is attached to the function as its documentation:

```python
def offset_mean(data, target_mean_value):
    """Return a new array containing the original data
    with its mean offset to match the desired value."""
    return (data - numpy.mean(data)) + target_mean_value
```

This is better because we can now ask Python's built-in help system to show us
the documentation for the function:

```python
help(offset_mean)
```

```output
Help on function offset_mean in module __main__:

offset_mean(data, target_mean_value)
    Return a new array containing the original data with its mean offset to match the desired value.
```

A string like this is called a docstring.
We don't need to use triple quotes when we write one,
but if we do,
we can break the string across multiple lines:

```python
def offset_mean(data, target_mean_value):
    """Return a new array containing the original data
    with its mean offset to match the desired value.

    Examples
    --------
    >>> offset_mean([1, 2, 3], 0)
    array([-1.,  0.,  1.])
    """
    return (data - numpy.mean(data)) + target_mean_value

help(offset_mean)
```

```output
Help on function offset_mean in module __main__:

offset_mean(data, target_mean_value)
    Return a new array containing the original data
    with its mean offset to match the desired value.

    Examples
    --------
    >>> offset_mean([1, 2, 3], 0)
    array([-1.,  0.,  1.])
```

{% enddetails %}
{% details note Defining Defaults %}

We have passed parameters to functions in two ways:
directly, as in `type(data)`,
and by name, as in `numpy.loadtxt(fname='something.csv', delimiter=',')`.
In fact,
we can pass the filename to `loadtxt` without the `fname=`:

```python
numpy.loadtxt('data/inflammation-01.csv', delimiter=',')
```

```output
array([[ 0.,  0.,  1., ...,  3.,  0.,  0.],
    [ 0.,  1.,  2., ...,  1.,  0.,  1.],
    [ 0.,  1.,  1., ...,  2.,  1.,  1.],
    ...,
    [ 0.,  1.,  1., ...,  1.,  1.,  1.],
    [ 0.,  0.,  0., ...,  0.,  2.,  0.],
    [ 0.,  0.,  1., ...,  1.,  1.,  0.]])
```

but we still need to say `delimiter=`:

```python
numpy.loadtxt('data/inflammation-01.csv', ',')
```

```error
Traceback (most recent call last):
File "<stdin>", line 1, in <module>
File "/Users/username/anaconda3/lib/python3.6/site-packages/numpy/lib/npyio.py", line 1041, in loa
dtxt
    dtype = np.dtype(dtype)
File "/Users/username/anaconda3/lib/python3.6/site-packages/numpy/core/_internal.py", line 199, in
_commastring
    newitem = (dtype, eval(repeats))
File "<string>", line 1
    ,
    ^
SyntaxError: unexpected EOF while parsing
```

To understand what's going on,
and make our own functions easier to use,
let's re-define our `offset_mean` function like this:

```python
def offset_mean(data, target_mean_value=0.0):
    """Return a new array containing the original data
    with its mean offset to match the desired value, (0 by default).

    Examples
    --------
    >>> offset_mean([1, 2, 3])
    array([-1.,  0.,  1.])
    """
    return (data - numpy.mean(data)) + target_mean_value
```

The key change is that the second parameter is now written `target_mean_value=0.0`
instead of just `target_mean_value`.
If we call the function with two arguments,
it works as it did before:

```python
test_data = numpy.zeros((2, 2))
print(offset_mean(test_data, 3))
```

```output
[[ 3.  3.]
[ 3.  3.]]
```

But we can also now call it with just one parameter,
in which case `target_mean_value` is automatically assigned
the default value of 0.0:

```python
more_data = 5 + numpy.zeros((2, 2))
print('data before mean offset:')
print(more_data)
print('offset data:')
print(offset_mean(more_data))
```

```output
data before mean offset:
[[ 5.  5.]
[ 5.  5.]]
offset data:
[[ 0.  0.]
[ 0.  0.]]
```

This is handy:
if we usually want a function to work one way,
but occasionally need it to do something else,
we can allow people to pass a parameter when they need to
but provide a default to make the normal case easier.
The example below shows how Python matches values to parameters:

```python
def display(a=1, b=2, c=3):
    print('a:', a, 'b:', b, 'c:', c)

print('no parameters:')
display()
print('one parameter:')
display(55)
print('two parameters:')
display(55, 66)
```

```output
no parameters:
a: 1 b: 2 c: 3
one parameter:
a: 55 b: 2 c: 3
two parameters:
a: 55 b: 66 c: 3
```

As this example shows,
parameters are matched up from left to right,
and any that haven't been given a value explicitly get their default value.
We can override this behavior by naming the value as we pass it in:

```python
print('only setting the value of c')
display(c=77)
```

```output
only setting the value of c
a: 1 b: 2 c: 77
```

With that in hand,
let's look at the help for `numpy.loadtxt`:

```python
help(numpy.loadtxt)
```

```output
Help on function loadtxt in module numpy.lib.npyio:

loadtxt(fname, dtype=<class 'float'>, comments='#', delimiter=None, converters=None, skiprows=0, use
cols=None, unpack=False, ndmin=0, encoding='bytes')
    Load data from a text file.

    Each row in the text file must have the same number of values.

    Parameters
    ----------
...
```

There's a lot of information here,
but the most important part is the first couple of lines:

```output
loadtxt(fname, dtype=<class 'float'>, comments='#', delimiter=None, converters=None, skiprows=0, use
cols=None, unpack=False, ndmin=0, encoding='bytes')
```

This tells us that `loadtxt` has one parameter called `fname` that doesn't have a default value,
and eight others that do.
If we call the function like this:

```python
numpy.loadtxt('data/inflammation-01.csv', ',')
```

then the filename is assigned to `fname` (which is what we want),
but the delimiter string `','` is assigned to `dtype` rather than `delimiter`,
because `dtype` is the second parameter in the list. However `','` isn't a known `dtype` so
our code produced an error message when we tried to run it.
When we call `loadtxt` we don't have to provide `fname=` for the filename because it's the
first item in the list, but if we want the `','` to be assigned to the variable `delimiter`,
we *do* have to provide `delimiter=` for the second parameter since `delimiter` is not
the second parameter in the list.

{% enddetails %}
{% details note Readable functions %}

Consider these two functions:

```python
def s(p):
    a = 0
    for v in p:
        a += v
    m = a / len(p)
    d = 0
    for v in p:
        d += (v - m) * (v - m)
    return numpy.sqrt(d / (len(p) - 1))

def std_dev(sample):
    sample_sum = 0
    for value in sample:
        sample_sum += value

    sample_mean = sample_sum / len(sample)

    sum_squared_devs = 0
    for value in sample:
        sum_squared_devs += (value - sample_mean) * (value - sample_mean)

    return numpy.sqrt(sum_squared_devs / (len(sample) - 1))
```

The functions `s` and `std_dev` are computationally equivalent (they
both calculate the sample standard deviation), but to a human reader,
they look very different. You probably found `std_dev` much easier to
read and understand than `s`.

As this example illustrates, both documentation and a programmer's
*coding style* combine to determine how easy it is for others to read
and understand the programmer's code. Choosing meaningful variable
names and using blank spaces to break the code into logical "chunks"
are helpful techniques for producing *readable code*. This is useful
not only for sharing code with others, but also for the original
programmer. If you need to revisit code that you wrote months ago and
haven't thought about since then, you will appreciate the value of
readable code!

{% enddetails %}
{% details Challenge 1: Combining Strings %}

"Adding" two strings produces their concatenation:
`'a' + 'b'` is `'ab'`.
Write a function called `fence` that takes two parameters called `original` and `wrapper`
and returns a new string that has the wrapper character at the beginning and end of the original.
A call to your function should look like this:

```python
print(fence('name', '*'))
```

```output
*name*
```

{% details success Solution %}

```python
def fence(original, wrapper):
    return wrapper + original + wrapper
```


{% enddetails %}
{% enddetails %}
{% details Challenge 2: Return versus print %}


Note that `return` and `print` are not interchangeable.
`print` is a Python function that *prints* data to the screen.
It enables us, *users*, see the data.
`return` statement, on the other hand, makes data visible to the program.
Let's have a look at the following function:

```python
def add(a, b):
    print(a + b)
```

**Question**: What will we see if we execute the following commands?

```python
A = add(7, 3)
print(A)
```

{% details success Solution %}

Python will first execute the function `add` with `a = 7` and `b = 3`,
and, therefore, print `10`. However, because function `add` does not have a
line that starts with `return` (no `return` "statement"), it will, by default, return
nothing which, in Python world, is called `None`. Therefore, `A` will be assigned to `None`
and the last line (`print(A)`) will print `None`. As a result, we will see:

```output
10
None
```

{% enddetails %}
{% enddetails %}
{% details Challenge 3: Selecting Characters From Strings %}

If the variable `s` refers to a string,
then `s[0]` is the string's first character
and `s[-1]` is its last.
Write a function called `outer`
that returns a string made up of just the first and last characters of its input.
A call to your function should look like this:

```python
print(outer('helium'))
```

```output
hm
```

{% details success Solution %}

```python
def outer(input_string):
    return input_string[0] + input_string[-1]
```


{% enddetails %}
{% enddetails %}
{% details Challenge 4: Rescaling an Array %}

Write a function `rescale` that takes an array as input
and returns a corresponding array of values scaled to lie in the range 0.0 to 1.0.
(Hint: If `L` and `H` are the lowest and highest values in the original array,
then the replacement for a value `v` should be `(v-L) / (H-L)`.)

{% details success Solution %}

```python
def rescale(input_array):
    L = numpy.amin(input_array)
    H = numpy.amax(input_array)
    output_array = (input_array - L) / (H - L)
    return output_array
```


{% enddetails %}
{% enddetails %}
{% details Challenge 5: Testing and Documenting Your Function %}

Run the commands `help(numpy.arange)` and `help(numpy.linspace)`
to see how to use these functions to generate regularly-spaced values,
then use those values to test your `rescale` function.
Once you've successfully tested your function,
add a docstring that explains what it does.

{% details success Solution %}

```python
"""Takes an array as input, and returns a corresponding array scaled so
that 0 corresponds to the minimum and 1 to the maximum value of the input array.

Examples:
>>> rescale(numpy.arange(10.0))
array([ 0.        ,  0.11111111,  0.22222222,  0.33333333,  0.44444444,
    0.55555556,  0.66666667,  0.77777778,  0.88888889,  1.        ])
>>> rescale(numpy.linspace(0, 100, 5))
array([ 0.  ,  0.25,  0.5 ,  0.75,  1.  ])
"""
```

{% enddetails %}
{% enddetails %}
{% details Challenge 6: Defining Defaults %}


Rewrite the `rescale` function so that it scales data to lie between `0.0` and `1.0` by default,
but will allow the caller to specify lower and upper bounds if they want.
Compare your implementation to your neighbor's:
do the two functions always behave the same way?

{% details success Solution %}

```python
def rescale(input_array, low_val=0.0, high_val=1.0):
    """rescales input array values to lie between low_val and high_val"""
    L = numpy.amin(input_array)
    H = numpy.amax(input_array)
    intermed_array = (input_array - L) / (H - L)
    output_array = intermed_array * (high_val - low_val) + low_val
    return output_array
```


{% enddetails %}
{% enddetails %}
{% details Challenge 7: Variables Inside and Outside Functions %}

What does the following piece of code display when run --- and why?

```python
f = 0
k = 0

def f2k(f):
    k = ((f - 32) * (5.0 / 9.0)) + 273.15
    return k

print(f2k(8))
print(f2k(41))
print(f2k(32))

print(k)
```

{% details success Solution %}

```output
259.81666666666666
278.15
273.15
0
```

`k` is 0 because the `k` inside the function `f2k` doesn't know
about the `k` defined outside the function. When the `f2k` function is called,
it creates a local variable
`k`. The function does not return any values
and does not alter `k` outside of its local copy.
Therefore the original value of `k` remains unchanged.
Beware that a local `k` is created because `f2k` internal statements
*affect* a new value to it. If `k` was only `read`, it would simply retrieve the
global `k` value.


{% enddetails %}
{% enddetails %}
{% details Challenge 8: Mixing Default and Non-Default Parameters %}

Given the following code:

```python
def numbers(one, two=2, three, four=4):
    n = str(one) + str(two) + str(three) + str(four)
    return n

print(numbers(1, three=3))
```

what do you expect will be printed?  What is actually printed?
What rule do you think Python is following?

1. `1234`
2. `one2three4`
3. `1239`
4. `SyntaxError`

Given that, what does the following piece of code display when run?

```python
def func(a, b=3, c=6):
    print('a: ', a, 'b: ', b, 'c:', c)

func(-1, 2)
```

1. `a: b: 3 c: 6`
2. `a: -1 b: 3 c: 6`
3. `a: -1 b: 2 c: 6`
4. `a: b: -1 c: 2`

{% details success Solution %}

Attempting to define the `numbers` function results in `4. SyntaxError`.
The defined parameters `two` and `four` are given default values. Because
`one` and `three` are not given default values, they are required to be
included as arguments when the function is called and must be placed
before any parameters that have default values in the function definition.

The given call to `func` displays `a: -1 b: 2 c: 6`. -1 is assigned to
the first parameter `a`, 2 is assigned to the next parameter `b`, and `c` is
not passed a value, so it uses its default value 6.


{% enddetails %}
{% enddetails %}
{% details note Readable Code %}

Revise a function you wrote for one of the previous exercises to try to make
the code more readable. Then, collaborate with one of your neighbors
to critique each other's functions and discuss how your function implementations
could be further improved to make them more readable.



{% enddetails %}
{% details tip Keypoints %}


- Define a function using `def function_name(parameter)`.
- The body of a function must be indented.
- Call a function using `function_name(value)`.
- Numbers are stored as integers or floating-point numbers.
- Variables defined within a function can only be seen and used within the body of the function.
- Variables created outside of any function are called global variables.
- Within a function, we can access global variables.
- Variables created within a function override global variables if their names match.
- Use `help(thing)` to view help for something.
- Put docstrings in functions to provide help for that function.
- Specify default values for parameters when defining a function using `name=value` in the parameter list.
- Parameters can be passed by matching based on name, by position, or by omitting them (in which case the default value is used).
- Put code whose parameters change frequently in a function, then call it with different parameter values to customize its behavior.



{% enddetails %}
## 9. Errors and Exceptions

{% details Abstract: Objectives %}


- To be able to read a traceback, and determine where the error took place and what type it is.
- To be able to describe the types of situations in which syntax errors, indentation errors, name errors, index errors, and missing file errors occur.



{% enddetails %}
{% details Questions %}


- How does Python report errors?
- How can I handle errors in Python programs?


{% enddetails %}
{% details note Overview %}

Every programmer encounters errors, both those who are just beginning,
and those who have been programming for years. Encountering errors and exceptions can be very frustrating at times,
and can make coding feel like a hopeless endeavour. However, understanding what the different types of errors are
and when you are likely to encounter them can help a lot. Once you know *why* you get certain types of errors,
they become much easier to fix.

Errors in Python have a very specific form, called a traceback.
Let's examine one:

```python
# This code has an intentional error. You can type it directly or
# use it for reference to understand the error message below.
def favorite_ice_cream():
    ice_creams = [
        'chocolate',
        'vanilla',
        'strawberry'
    ]
    print(ice_creams[3])

favorite_ice_cream()
```

```error
---------------------------------------------------------------------------
IndexError                                Traceback (most recent call last)
<ipython-input-1-70bd89baa4df> in <module>()
    9     print(ice_creams[3])
    10
----> 11 favorite_ice_cream()

<ipython-input-1-70bd89baa4df> in favorite_ice_cream()
    7         'strawberry'
    8     ]
----> 9     print(ice_creams[3])
    10
    11 favorite_ice_cream()

IndexError: list index out of range
```

This particular traceback has two levels.
You can determine the number of levels by looking for the number of arrows on the left hand side.
In this case:

1. The first shows code from the cell above,
with an arrow pointing to Line 11 (which is `favorite_ice_cream()`).

2. The second shows some code in the function `favorite_ice_cream`,
with an arrow pointing to Line 9 (which is `print(ice_creams[3])`).

The last level is the actual place where the error occurred.
The other level(s) show what function the program executed to get to the next level down.
So, in this case, the program first performed a
function call to the function `favorite_ice_cream`.
Inside this function,
the program encountered an error on Line 6, when it tried to run the code `print(ice_creams[3])`.


{% enddetails %}
{% details note Long Tracebacks %}

Sometimes, you might see a traceback that is very long
\-- sometimes they might even be 20 levels deep!
This can make it seem like something horrible happened,
but the length of the error message does not reflect severity, rather,
it indicates that your program called many functions before it encountered the error.
Most of the time, the actual place where the error occurred is at the bottom-most level,
so you can skip down the traceback to the bottom.

So what error did the program actually encounter?
In the last line of the traceback,
Python helpfully tells us the category or type of error (in this case, it is an `IndexError`)
and a more detailed error message (in this case, it says "list index out of range").

If you encounter an error and don't know what it means,
it is still important to read the traceback closely.
That way, if you fix the error, but encounter a new one,
you can tell that the error changed. Additionally, sometimes knowing *where* the error occurred is enough to fix it,
even if you don't entirely understand the message.

If you do encounter an error you don't recognize, try looking at the
[official documentation on errors](https://docs.python.org/3/library/exceptions.html).
However, note that you may not always be able to find the error there,
as it is possible to create custom errors. In that case,
hopefully the custom error message is informative enough to help you figure out what went wrong.

{% enddetails %}
{% details Challenge 1: Reading Error Messages %}

Read the Python code and the resulting traceback below, and answer the following questions:

1. How many levels does the traceback have?
2. What is the function name where the error occurred?
3. On which line number in this function did the error occur?
4. What is the type of error?
5. What is the error message?

```python
# This code has an intentional error. Do not type it directly;
# use it for reference to understand the error message below.
def print_message(day):
    messages = [
        'Hello, world!',
        'Today is Tuesday!',
        'It is the middle of the week.',
        'Today is Donnerstag in German!',
        'Last day of the week!',
        'Hooray for the weekend!',
        'Aw, the weekend is almost over.'
    ]
    print(messages[day])

def print_sunday_message():
    print_message(7)

print_sunday_message()
```

```error
---------------------------------------------------------------------------
IndexError                                Traceback (most recent call last)
<ipython-input-7-3ad455d81842> in <module>
    16     print_message(7)
    17 
---> 18 print_sunday_message()
    19 

<ipython-input-7-3ad455d81842> in print_sunday_message()
    14 
    15 def print_sunday_message():
---> 16     print_message(7)
    17 
    18 print_sunday_message()

<ipython-input-7-3ad455d81842> in print_message(day)
    11         'Aw, the weekend is almost over.'
    12     ]
---> 13     print(messages[day])
    14 
    15 def print_sunday_message():

IndexError: list index out of range
```

{% details success Solution %}

1. 3 levels
2. `print_message`
3. 13
4. `IndexError`
5. `list index out of range` You can then infer that
`7` is not the right index to use with `messages`.

{% enddetails %}
{% enddetails %}
{% details info Better errors on newer Pythons %}

Newer versions of Python have improved error printouts.  If you are debugging errors, it is often
helpful to use the latest Python version, even if you support older versions of Python.

{% enddetails %}
{% details note Syntax Errors %}


When you forget a colon at the end of a line,
accidentally add one space too many when indenting under an `if` statement,
or forget a parenthesis,
you will encounter a syntax error.
This means that Python couldn't figure out how to read your program.
This is similar to forgetting punctuation in English:
for example,
this text is difficult to read there is no punctuation there is also no capitalization
why is this hard because you have to figure out where each sentence ends
you also have to figure out where each sentence begins
to some extent it might be ambiguous if there should be a sentence break or not

People can typically figure out what is meant by text with no punctuation,
but people are much smarter than computers.
If Python doesn't know how to read the program,
it will give up and inform you with an error.
For example:

```python
def some_function()
    msg = 'hello, world!'
    print(msg)
    return msg
```

```error
File "<ipython-input-3-6bb841ea1423>", line 1
    def some_function()
                    ^
SyntaxError: invalid syntax
```

Here, Python tells us that there is a `SyntaxError` on line 1,
and even puts a little arrow in the place where there is an issue.
In this case the problem is that the function definition is missing a colon at the end.

Actually, the function above has *two* issues with syntax.
If we fix the problem with the colon,
we see that there is *also* an `IndentationError`,
which means that the lines in the function definition do not all have the same indentation:

```python
def some_function():
    msg = 'hello, world!'
    print(msg)
    return msg
```

```error
File "<ipython-input-4-ae290e7659cb>", line 4
    return msg
    ^
IndentationError: unexpected indent
```

Both `SyntaxError` and `IndentationError` indicate a problem with the syntax of your program,
but an `IndentationError` is more specific:
it *always* means that there is a problem with how your code is indented.

{% enddetails %}
{% details note Tabs and Spaces %}

Some indentation errors are harder to spot than others.
In particular, mixing spaces and tabs can be difficult to spot
because they are both whitespace.
In the example below, the first two lines in the body of the function
`some_function` are indented with tabs, while the third line — with spaces.
If you're working in a Jupyter notebook, be sure to copy and paste this example
rather than trying to type it in manually because Jupyter automatically replaces
tabs with spaces.

```python
def some_function():
    msg = 'hello, world!'
    print(msg)
        return msg
```

Visually it is impossible to spot the error.
Fortunately, Python does not allow you to mix tabs and spaces.

```error
File "<ipython-input-5-653b36fbcd41>", line 4
    return msg
            ^
TabError: inconsistent use of tabs and spaces in indentation
```

{% enddetails %}
{% details note Variable Name Errors %}

Another very common type of error is called a `NameError`,
and occurs when you try to use a variable that does not exist.
For example:

```python
print(a)
```

```error
---------------------------------------------------------------------------
NameError                                 Traceback (most recent call last)
<ipython-input-7-9d7b17ad5387> in <module>()
----> 1 print(a)

NameError: name 'a' is not defined
```

Variable name errors come with some of the most informative error messages,
which are usually of the form "name 'the\_variable\_name' is not defined".

Why does this error message occur?
That's a harder question to answer,
because it depends on what your code is supposed to do.
However,
there are a few very common reasons why you might have an undefined variable.
The first is that you meant to use a string, but forgot to put quotes around it:

```python
print(hello)
```

```error
---------------------------------------------------------------------------
NameError                                 Traceback (most recent call last)
<ipython-input-8-9553ee03b645> in <module>()
----> 1 print(hello)

NameError: name 'hello' is not defined
```

The second reason is that you might be trying to use a variable that does not yet exist.
In the following example,
`count` should have been defined (e.g., with `count = 0`) before the for loop:

```python
for number in range(10):
    count = count + number
print('The count is:', count)
```

```error
---------------------------------------------------------------------------
NameError                                 Traceback (most recent call last)
<ipython-input-9-dd6a12d7ca5c> in <module>()
    1 for number in range(10):
----> 2     count = count + number
    3 print('The count is:', count)

NameError: name 'count' is not defined
```

Finally, the third possibility is that you made a typo when you were writing your code.
Let's say we fixed the error above by adding the line `Count = 0` before the for loop.
Frustratingly, this actually does not fix the error.
Remember that variables are case-sensitive,
so the variable `count` is different from `Count`. We still get the same error,
because we still have not defined `count`:

```python
Count = 0
for number in range(10):
    count = count + number
print('The count is:', count)
```

```error
---------------------------------------------------------------------------
NameError                                 Traceback (most recent call last)
<ipython-input-10-d77d40059aea> in <module>()
    1 Count = 0
    2 for number in range(10):
----> 3     count = count + number
    4 print('The count is:', count)

NameError: name 'count' is not defined
```

{% enddetails %}
{% details note Index Errors %}

Next up are errors having to do with containers (like lists and strings) and the items within them.
If you try to access an item in a list or a string that does not exist,
then you will get an error.
This makes sense:
if you asked someone what day they would like to get coffee,
and they answered "caturday",
you might be a bit annoyed.
Python gets similarly annoyed if you try to ask it for an item that doesn't exist:

```python
letters = ['a', 'b', 'c']
print('Letter #1 is', letters[0])
print('Letter #2 is', letters[1])
print('Letter #3 is', letters[2])
print('Letter #4 is', letters[3])
```

```output
Letter #1 is a
Letter #2 is b
Letter #3 is c
```

```error
---------------------------------------------------------------------------
IndexError                                Traceback (most recent call last)
<ipython-input-11-d817f55b7d6c> in <module>()
    3 print('Letter #2 is', letters[1])
    4 print('Letter #3 is', letters[2])
----> 5 print('Letter #4 is', letters[3])

IndexError: list index out of range
```

Here,
Python is telling us that there is an `IndexError` in our code,
meaning we tried to access a list index that did not exist.

{% enddetails %}
{% details note File Errors %}

The last type of error we'll cover today
are those associated with reading and writing files: `FileNotFoundError`.
If you try to read a file that does not exist,
you will receive a `FileNotFoundError` telling you so.
If you attempt to write to a file that was opened read-only, Python 3
returns an `UnsupportedOperationError`.
More generally, problems with input and output manifest as
`OSError`s, which may show up as a more specific subclass; you can see
[the list in the Python docs](https://docs.python.org/3/library/exceptions.html#os-exceptions).
They all have a unique UNIX `errno`, which is you can see in the error message.

```python
file_handle = open('myfile.txt', 'r')
```

```error
---------------------------------------------------------------------------
FileNotFoundError                         Traceback (most recent call last)
<ipython-input-14-f6e1ac4aee96> in <module>()
----> 1 file_handle = open('myfile.txt', 'r')

FileNotFoundError: [Errno 2] No such file or directory: 'myfile.txt'
```

One reason for receiving this error is that you specified an incorrect path to the file.
For example,
if I am currently in a folder called `myproject`,
and I have a file in `myproject/writing/myfile.txt`,
but I try to open `myfile.txt`,
this will fail.
The correct path would be `writing/myfile.txt`.
It is also possible that the file name or its path contains a typo.

A related issue can occur if you use the "read" flag instead of the "write" flag.
Python will not give you an error if you try to open a file for writing
when the file does not exist.
However,
if you meant to open a file for reading,
but accidentally opened it for writing,
and then try to read from it,
you will get an `UnsupportedOperation` error
telling you that the file was not opened for reading:

```python
file_handle = open('myfile.txt', 'w')
file_handle.read()
```

```error
---------------------------------------------------------------------------
UnsupportedOperation                      Traceback (most recent call last)
<ipython-input-15-b846479bc61f> in <module>()
    1 file_handle = open('myfile.txt', 'w')
----> 2 file_handle.read()

UnsupportedOperation: not readable
```

These are the most common errors with files,
though many others exist.
If you get an error that you've never seen before,
searching the Internet for that error type
often reveals common reasons why you might get that error.

{% enddetails %}
{% details Challenge 1: Identifying Syntax Errors %}

1. Read the code below, and (without running it) try to identify what the errors are.
2. Run the code, and read the error message. Is it a `SyntaxError` or an `IndentationError`?
3. Fix the error.
4. Repeat steps 2 and 3, until you have fixed all the errors.

```python
def another_function
print('Syntax errors are annoying.')
print('But at least Python tells us about them!')
print('So they are usually not too hard to fix.')
```

{% details success Solution %}

`SyntaxError` for missing `():` at end of first line,
`IndentationError` for mismatch between second and third lines.
A fixed version is:

```python
def another_function():
    print('Syntax errors are annoying.')
    print('But at least Python tells us about them!')
    print('So they are usually not too hard to fix.')
```

{% enddetails %}
{% enddetails %}
{% details Challenge 2: Identifying Variable Name Errors %}


1. Read the code below, and (without running it) try to identify what the errors are.
2. Run the code, and read the error message.
What type of `NameError` do you think this is?
In other words, is it a string with no quotes,
a misspelled variable,
or a variable that should have been defined but was not?
3. Fix the error.
4. Repeat steps 2 and 3, until you have fixed all the errors.

```python
for number in range(10):
    # use a if the number is a multiple of 3, otherwise use b
    if (Number % 3) == 0:
        message = message + a
    else:
        message = message + 'b'
print(message)
```

{% details success Solution %}

3 `NameError`s for `number` being misspelled, for `message` not defined,
and for `a` not being in quotes.

Fixed version:

```python
message = ''
for number in range(10):
    # use a if the number is a multiple of 3, otherwise use b
    if (number % 3) == 0:
        message = message + 'a'
    else:
        message = message + 'b'
print(message)
```

{% enddetails %}
{% enddetails %}
{% details Challenge 3: Identifying Index Errors %}


1. Read the code below, and (without running it) try to identify what the errors are.
2. Run the code, and read the error message. What type of error is it?
3. Fix the error.

```python
seasons = ['Spring', 'Summer', 'Fall', 'Winter']
print('My favorite season is ', seasons[4])
```

{% details success Solution %}

`IndexError`; the last entry is `seasons[3]`, so `seasons[4]` doesn't make sense.
A fixed version is:

```python
seasons = ['Spring', 'Summer', 'Fall', 'Winter']
print('My favorite season is ', seasons[-1])
```


{% enddetails %}
{% enddetails %}
{% details tip Keypoints %}

- Tracebacks can look intimidating, but they give us a lot of useful information about what went wrong in our program, including where the error occurred and what type of error it was.
- An error having to do with the 'grammar' or syntax of the program is called a `SyntaxError`. If the issue has to do with how the code is indented, then it will be called an `IndentationError`.
- A `NameError` will occur when trying to use a variable that does not exist. Possible causes are that a variable definition is missing, a variable reference differs from its definition in spelling or capitalization, or the code contains a string that is missing quotes around it.
- Containers like lists and strings will generate errors if you try to access items in them that do not exist. This type of error is called an `IndexError`.
- Trying to read a file that does not exist will give you an `FileNotFoundError`. Trying to read a file that is open for writing, or writing to a file that is open for reading, will give you an `IOError`.

{% enddetails %}
## 10. Defensive Programming

{% details Abstract: Objectives %}

- Explain what an assertion is.
- Add assertions that check the program's state is correct.
- Correctly add precondition and postcondition assertions to functions.
- Explain what test-driven development is, and use it when creating new functions.
- Explain why variables should be initialized using actual data values rather than arbitrary constants.

{% enddetails %}
{% details Questions %}

- How can I make my programs more reliable?

{% enddetails %}
{% details note Overview %}

Our previous lessons have introduced the basic tools of programming:

- variables and lists,
- file I/O,
- loops,
- conditionals, and
- functions.

What they *haven't* done is show us how to tell whether a program is getting the right answer,
and how to tell if it's *still* getting the right answer as we make changes to it.

To achieve that, we need to:

- Write programs that check their own operation.
- Write and run tests for widely-used functions.
- Make sure we know what "correct" actually means.

The good news is, doing these things will speed up our programming,
not slow it down. As in real carpentry --- the kind done with lumber --- the time saved
by measuring carefully before cutting a piece of wood is much greater than the time that measuring takes.

{% enddetails %}
{% details note Assertions %}

The first step toward getting the right answers from our programs
is to assume that mistakes *will* happen and to guard against them.
This is called defensive programming,
and the most common way to do it is to add
assertions to our code
so that it checks itself as it runs.
An assertion is simply a statement that something must be true at a certain point in a program.
When Python sees one, it evaluates the assertion's condition.
If it's true, Python does nothing, but if it's false,
Python halts the program immediately and prints the error message if one is provided.
For example, this piece of code halts as soon as the loop encounters a value that isn't positive:

```python
numbers = [1.5, 2.3, 0.7, -0.001, 4.4]
total = 0.0
for num in numbers:
    assert num > 0.0, 'Data should only contain positive values'
    total += num
print('total is:', total)
```

```error
---------------------------------------------------------------------------
AssertionError                            Traceback (most recent call last)
<ipython-input-19-33d87ea29ae4> in <module>()
    2 total = 0.0
    3 for num in numbers:
----> 4     assert num > 0.0, 'Data should only contain positive values'
    5     total += num
    6 print('total is:', total)

AssertionError: Data should only contain positive values
```

Programs like the Firefox browser are full of assertions:
10-20% of the code they contain are there to check that the other 80–90% are working correctly.
Broadly speaking, assertions fall into three categories:

- A precondition
is something that must be true at the start of a function in order for it to work correctly.

- A postcondition
is something that the function guarantees is true when it finishes.

- An invariant
is something that is always true at a particular point inside a piece of code.

For example, suppose we are representing rectangles using a tuple
of four coordinates `(x0, y0, x1, y1)`,
representing the lower left and upper right corners of the rectangle.
In order to do some calculations,
we need to normalize the rectangle so that the lower left corner is at the origin
and the longest side is 1.0 units long.
This function does that,
but checks that its input is correctly formatted and that its result makes sense:

```python
def normalize_rectangle(rect):
    """Normalizes a rectangle so that it is at the origin and 1.0 units long on its longest axis.
    Input should be of the format (x0, y0, x1, y1).
    (x0, y0) and (x1, y1) define the lower left and upper right corners
    of the rectangle, respectively."""
    assert len(rect) == 4, 'Rectangles must contain 4 coordinates'
    x0, y0, x1, y1 = rect
    assert x0 < x1, 'Invalid X coordinates'
    assert y0 < y1, 'Invalid Y coordinates'

    dx = x1 - x0
    dy = y1 - y0
    if dx > dy:
        scaled = dx / dy
        upper_x, upper_y = 1.0, scaled
    else:
        scaled = dx / dy
        upper_x, upper_y = scaled, 1.0

    assert 0 < upper_x <= 1.0, 'Calculated upper X coordinate invalid'
    assert 0 < upper_y <= 1.0, 'Calculated upper Y coordinate invalid'

    return (0, 0, upper_x, upper_y)
```

The preconditions on lines 6, 8, and 9 catch invalid inputs:

```python
print(normalize_rectangle( (0.0, 1.0, 2.0) )) # missing the fourth coordinate
```

```error
---------------------------------------------------------------------------
AssertionError                            Traceback (most recent call last)
<ipython-input-2-1b9cd8e18a1f> in <module>
----> 1 print(normalize_rectangle( (0.0, 1.0, 2.0) )) # missing the fourth coordinate

<ipython-input-1-c94cf5b065b9> in normalize_rectangle(rect)
    4     (x0, y0) and (x1, y1) define the lower left and upper right corners
    5     of the rectangle, respectively."""
----> 6     assert len(rect) == 4, 'Rectangles must contain 4 coordinates'
    7     x0, y0, x1, y1 = rect
    8     assert x0 < x1, 'Invalid X coordinates'

AssertionError: Rectangles must contain 4 coordinates
```

```python
print(normalize_rectangle( (4.0, 2.0, 1.0, 5.0) )) # X axis inverted
```

```error
---------------------------------------------------------------------------
AssertionError                            Traceback (most recent call last)
<ipython-input-3-325036405532> in <module>
----> 1 print(normalize_rectangle( (4.0, 2.0, 1.0, 5.0) )) # X axis inverted

<ipython-input-1-c94cf5b065b9> in normalize_rectangle(rect)
    6     assert len(rect) == 4, 'Rectangles must contain 4 coordinates'
    7     x0, y0, x1, y1 = rect
----> 8     assert x0 < x1, 'Invalid X coordinates'
    9     assert y0 < y1, 'Invalid Y coordinates'
    10

AssertionError: Invalid X coordinates
```

The post-conditions on lines 20 and 21 help us catch bugs by telling us when our
calculations might have been incorrect.
For example,
if we normalize a rectangle that is taller than it is wide everything seems OK:

```python
print(normalize_rectangle( (0.0, 0.0, 1.0, 5.0) ))
```

```output
(0, 0, 0.2, 1.0)
```

but if we normalize one that's wider than it is tall,
the assertion is triggered:

```python
print(normalize_rectangle( (0.0, 0.0, 5.0, 1.0) ))
```

```error
---------------------------------------------------------------------------
AssertionError                            Traceback (most recent call last)
<ipython-input-5-8d4a48f1d068> in <module>
----> 1 print(normalize_rectangle( (0.0, 0.0, 5.0, 1.0) ))

<ipython-input-1-c94cf5b065b9> in normalize_rectangle(rect)
    19
    20     assert 0 < upper_x <= 1.0, 'Calculated upper X coordinate invalid'
---> 21     assert 0 < upper_y <= 1.0, 'Calculated upper Y coordinate invalid'
    22
    23     return (0, 0, upper_x, upper_y)

AssertionError: Calculated upper Y coordinate invalid
```

Re-reading our function,
we realize that line 14 should divide `dy` by `dx` rather than `dx` by `dy`.
In a Jupyter notebook, you can display line numbers by typing <kbd>Ctrl</kbd>\+<kbd>M</kbd>
followed by <kbd>L</kbd>.
If we had left out the assertion at the end of the function,
we would have created and returned something that had the right shape as a valid answer,
but wasn't.
Detecting and debugging that would almost certainly have taken more time in the long run
than writing the assertion.

But assertions aren't just about catching errors:
they also help people understand programs.
Each assertion gives the person reading the program
a chance to check (consciously or otherwise)
that their understanding matches what the code is doing.

Most good programmers follow two rules when adding assertions to their code.
The first is, *fail early, fail often*.
The greater the distance between when and where an error occurs and when it's noticed,
the harder the error will be to debug,
so good code catches mistakes as early as possible.

The second rule is, *turn bugs into assertions or tests*.
Whenever you fix a bug, write an assertion that catches the mistake
should you make it again.
If you made a mistake in a piece of code,
the odds are good that you have made other mistakes nearby,
or will make the same mistake (or a related one)
the next time you change it.
Writing assertions to check that you haven't regressed
(i.e., haven't re-introduced an old problem)
can save a lot of time in the long run,
and helps to warn people who are reading the code
(including your future self)
that this bit is tricky.

{% enddetails %}
{% details note Test-Driven Development %}

An assertion checks that something is true at a particular point in the program.
The next step is to check the overall behavior of a piece of code, i.e.,
to make sure that it produces the right output when it's given a particular input.
For example, suppose we need to find where two or more time series overlap.
The range of each time series is represented as a pair of numbers,
which are the time the interval started and ended. The output is the largest range that they all include:

{% include figure.liquid path="assets/img/courses/workshops/python_programming/python-overlapping-ranges.svg" max-width="50%" zoomable=true alt='Graph showing three number lines and, at the bottom, the interval that they overlap.' %}

Most novice programmers would solve this problem like this:

1. Write a function `range_overlap`.
2. Call it interactively on two or three different inputs.
3. If it produces the wrong answer, fix the function and re-run that test.

This clearly works --- after all, thousands of scientists are doing it right now --- but
there's a better way:

1. Write a short function for each test.
2. Write a `range_overlap` function that should pass those tests.
3. If `range_overlap` produces any wrong answers, fix it and re-run the test functions.

Writing the tests *before* writing the function they exercise
is called test-driven development (TDD).
Its advocates believe it produces better code faster because:

1. If people write tests after writing the thing to be tested,
they are subject to confirmation bias,
i.e.,
they subconsciously write tests to show that their code is correct,
rather than to find errors.
2. Writing tests helps programmers figure out what the function is actually supposed to do.

We start by defining an empty function `range_overlap`:

```python
def range_overlap(ranges):
    pass
```

Here are three test statements for `range_overlap`:

```python
assert range_overlap([ (0.0, 1.0) ]) == (0.0, 1.0)
assert range_overlap([ (2.0, 3.0), (2.0, 4.0) ]) == (2.0, 3.0)
assert range_overlap([ (0.0, 1.0), (0.0, 2.0), (-1.0, 1.0) ]) == (0.0, 1.0)
```

```error
---------------------------------------------------------------------------
AssertionError                            Traceback (most recent call last)
<ipython-input-25-d8be150fbef6> in <module>()
----> 1 assert range_overlap([ (0.0, 1.0) ]) == (0.0, 1.0)
    2 assert range_overlap([ (2.0, 3.0), (2.0, 4.0) ]) == (2.0, 3.0)
    3 assert range_overlap([ (0.0, 1.0), (0.0, 2.0), (-1.0, 1.0) ]) == (0.0, 1.0)

AssertionError:
```

The error is actually reassuring: we haven't implemented any logic into `range_overlap` yet,
so if the tests passed, it would indicate that we've written
an entirely ineffective test.

And as a bonus of writing these tests,
we've implicitly defined what our input and output look like:
we expect a list of pairs as input,
and produce a single pair as output.

Something important is missing, though.
We don't have any tests for the case where the ranges don't overlap at all:

```python
assert range_overlap([ (0.0, 1.0), (5.0, 6.0) ]) == ???
```

What should `range_overlap` do in this case:
fail with an error message,
produce a special value like `(0.0, 0.0)` to signal that there's no overlap,
or something else?
Any actual implementation of the function will do one of these things;
writing the tests first helps us figure out which is best
*before* we're emotionally invested in whatever we happened to write
before we realized there was an issue.

And what about this case?

```python
assert range_overlap([ (0.0, 1.0), (1.0, 2.0) ]) == ???
```

Do two segments that touch at their endpoints overlap or not?
Mathematicians usually say "yes",
but engineers usually say "no".
The best answer is "whatever is most useful in the rest of our program",
but again,
any actual implementation of `range_overlap` is going to do *something*,
and whatever it is ought to be consistent with what it does when there's no overlap at all.

Since we're planning to use the range this function returns
as the X axis in a time series chart,
we decide that:

1. every overlap has to have non-zero width, and
2. we will return the special value `None` when there's no overlap.

`None` is built into Python,
and means "nothing here".
(Other languages often call the equivalent value `null` or `nil`).
With that decision made,
we can finish writing our last two tests:

```python
assert range_overlap([ (0.0, 1.0), (5.0, 6.0) ]) == None
assert range_overlap([ (0.0, 1.0), (1.0, 2.0) ]) == None
```

```error
---------------------------------------------------------------------------
AssertionError                            Traceback (most recent call last)
<ipython-input-26-d877ef460ba2> in <module>()
----> 1 assert range_overlap([ (0.0, 1.0), (5.0, 6.0) ]) == None
    2 assert range_overlap([ (0.0, 1.0), (1.0, 2.0) ]) == None

AssertionError:
```

Again,
we get an error because we haven't written our function,
but we're now ready to do so:

```python
def range_overlap(ranges):
    """Return common overlap among a set of [left, right] ranges."""
    max_left = 0.0
    min_right = 1.0
    for (left, right) in ranges:
        max_left = max(max_left, left)
        min_right = min(min_right, right)
    return (max_left, min_right)
```

Take a moment to think about why we calculate the left endpoint of the overlap as
the maximum of the input left endpoints, and the overlap right endpoint as the minimum
of the input right endpoints.
We'd now like to re-run our tests,
but they're scattered across three different cells.
To make running them easier,
let's put them all in a function:

```python
def test_range_overlap():
    assert range_overlap([ (0.0, 1.0), (5.0, 6.0) ]) == None
    assert range_overlap([ (0.0, 1.0), (1.0, 2.0) ]) == None
    assert range_overlap([ (0.0, 1.0) ]) == (0.0, 1.0)
    assert range_overlap([ (2.0, 3.0), (2.0, 4.0) ]) == (2.0, 3.0)
    assert range_overlap([ (0.0, 1.0), (0.0, 2.0), (-1.0, 1.0) ]) == (0.0, 1.0)
    assert range_overlap([]) == None
```

We can now test `range_overlap` with a single function call:

```python
test_range_overlap()
```

```error
---------------------------------------------------------------------------
AssertionError                            Traceback (most recent call last)
<ipython-input-29-cf9215c96457> in <module>()
----> 1 test_range_overlap()

<ipython-input-28-5d4cd6fd41d9> in test_range_overlap()
    1 def test_range_overlap():
----> 2     assert range_overlap([ (0.0, 1.0), (5.0, 6.0) ]) == None
    3     assert range_overlap([ (0.0, 1.0), (1.0, 2.0) ]) == None
    4     assert range_overlap([ (0.0, 1.0) ]) == (0.0, 1.0)
    5     assert range_overlap([ (2.0, 3.0), (2.0, 4.0) ]) == (2.0, 3.0)

AssertionError:
```

The first test that was supposed to produce `None` fails,
so we know something is wrong with our function.
We *don't* know whether the other tests passed or failed
because Python halted the program as soon as it spotted the first error.
Still,
some information is better than none,
and if we trace the behavior of the function with that input,
we realize that we're initializing `max_left` and `min_right` to 0.0 and 1.0 respectively,
regardless of the input values.
This violates another important rule of programming:
*always initialize from data*.

{% enddetails %}
{% details Challenge 1: Pre- and Post-Conditions %}

Suppose you are writing a function called `average` that calculates
the average of the numbers in a list.
What pre-conditions and post-conditions would you write for it?
Compare your answer to your neighbor's:
can you think of a function that will pass your tests but not his/hers or vice versa?

{% details success Solution %}

```python
# a possible pre-condition:
assert len(input_list) > 0, 'List length must be non-zero'
# a possible post-condition:
assert numpy.amin(input_list) <= average <= numpy.amax(input_list),
'Average should be between min and max of input values (inclusive)'
```

{% enddetails %}
{% enddetails %}
{% details Challenge 2: Testing Assertions %}


Given a sequence of a number of cars, the function `get_total_cars` returns
the total number of cars.

```python
get_total_cars([1, 2, 3, 4])
```

```output
10
```

```python
get_total_cars(['a', 'b', 'c'])
```

```output
ValueError: invalid literal for int() with base 10: 'a'
```

Explain in words what the assertions in this function check,
and for each one,
give an example of input that will make that assertion fail.

```python
def get_total(values):
    assert len(values) > 0
    for element in values:
        assert int(element)
    values = [int(element) for element in values]
    total = sum(values)
    assert total > 0
    return total
```

{% details success Solution %}

{% enddetails %}
- The first assertion checks that the input sequence `values` is not empty.
An empty sequence such as `[]` will make it fail.
- The second assertion checks that each value in the list can be turned into an integer.
Input such as `[1, 2, 'c', 3]` will make it fail.
- The third assertion checks that the total of the list is greater than 0.
Input such as `[-10, 2, 3]` will make it fail.




{% enddetails %}
{% details tip Keypoints %}


- Program defensively, i.e., assume that errors are going to arise, and write code to detect them when they do.
- Put assertions in programs to check their state as they run, and to help readers understand how those programs are supposed to work.
- Use preconditions to check that the inputs to a function are safe to use.
- Use postconditions to check that the output from a function is safe to use.
- Write tests before writing code in order to help determine exactly what that code is supposed to do.



{% enddetails %}
## 11. Debugging

{% details Abstract: Objectives %}


- Debug code containing an error systematically.
- Identify ways of making code less error-prone and more easily tested.



{% enddetails %}
{% details Questions %}


- How can I debug my program?

Once testing has uncovered problems, the next step is to fix them.
Many novices do this by making more-or-less random changes to their code
until it seems to produce the right answer, but that's very inefficient
(and the result is usually only correct for the one case they're testing).
The more experienced a programmer is, the more systematically they debug,
and most follow some variation on the rules explained below.

{% enddetails %}
{% details note Know What It's Supposed to Do %}


The first step in debugging something is to
*know what it's supposed to do*.
"My program doesn't work" isn't good enough:
in order to diagnose and fix problems,
we need to be able to tell correct output from incorrect.
If we can write a test case for the failing case --- i.e.,
if we can assert that with *these* inputs,
the function should produce *that* result ---
then we're ready to start debugging.
If we can't,
then we need to figure out how we're going to know when we've fixed things.

But writing test cases for scientific software is frequently harder than
writing test cases for commercial applications,
because if we knew what the output of the scientific code was supposed to be,
we wouldn't be running the software:
we'd be writing up our results and moving on to the next program.
In practice,
scientists tend to do the following:

1. *Test with simplified data.*
Before doing statistics on a real data set,
we should try calculating statistics for a single record,
for two identical records,
for two records whose values are one step apart,
or for some other case where we can calculate the right answer by hand.

2. *Test a simplified case.*
If our program is supposed to simulate
magnetic eddies in rapidly-rotating blobs of supercooled helium,
our first test should be a blob of helium that isn't rotating,
and isn't being subjected to any external electromagnetic fields.
Similarly,
if we're looking at the effects of climate change on speciation,
our first test should hold temperature, precipitation, and other factors constant.

3. *Compare to an oracle.*
A test oracle
is something whose results are trusted,
such as experimental data, an older program, or a human expert.
We use test oracles to determine if our new program produces the correct results.
If we have a test oracle,
we should store its output for particular cases
so that we can compare it with our new results as often as we like
without re-running that program.

4. *Check conservation laws.*
Mass, energy, and other quantities are conserved in physical systems,
so they should be in programs as well.
Similarly,
if we are analyzing patient data,
the number of records should either stay the same or decrease
as we move from one analysis to the next
(since we might throw away outliers or records with missing values).
If "new" patients start appearing out of nowhere as we move through our pipeline,
it's probably a sign that something is wrong.

5. *Visualize.*
Data analysts frequently use simple visualizations to check both
the science they're doing
and the correctness of their code.
This should only be used for debugging as a last resort,
though,
since it's very hard to compare two visualizations automatically.

{% enddetails %}
{% details note Make It Fail Every Time %}

We can only debug something when it fails,
so the second step is always to find a test case that
*makes it fail every time*.
The "every time" part is important because
few things are more frustrating than debugging an intermittent problem:
if we have to call a function a dozen times to get a single failure,
the odds are good that we'll scroll past the failure when it actually occurs.

As part of this,
it's always important to check that our code is "plugged in",
i.e.,
that we're actually exercising the problem that we think we are.
Every programmer has spent hours chasing a bug,
only to realize that they were actually calling their code on the wrong data set
or with the wrong configuration parameters,
or are using the wrong version of the software entirely.
Mistakes like these are particularly likely to happen when we're tired,
frustrated,
and up against a deadline,
which is one of the reasons late-night (or overnight) coding sessions
are almost never worthwhile.

{% enddetails %}
{% details note Make It Fail Fast %}

If it takes 20 minutes for the bug to surface,
we can only do three experiments an hour.
This means that we'll get less data in more time and that
we're more likely to be distracted by other things as we wait for our program to fail,
which means the time we *are* spending on the problem is less focused.
It's therefore critical to *make it fail fast*.

As well as making the program fail fast in time,
we want to make it fail fast in space,
i.e.,
we want to localize the failure to the smallest possible region of code:

1. The smaller the gap between cause and effect,
the easier the connection is to find.
Many programmers therefore use a divide and conquer strategy to find bugs,
i.e.,
if the output of a function is wrong,
they check whether things are OK in the middle,
then concentrate on either the first or second half,
and so on.

2. N things can interact in N! different ways,
so every line of code that *isn't* run as part of a test
means more than one thing we don't need to worry about.

{% enddetails %}
{% details note Change One Thing at a Time, For a Reason %}

Replacing random chunks of code is unlikely to do much good.
(After all,
if you got it wrong the first time,
you'll probably get it wrong the second and third as well.)
Good programmers therefore
*change one thing at a time, for a reason*.
They are either trying to gather more information
("is the bug still there if we change the order of the loops?")
or test a fix
("can we make the bug go away by sorting our data before processing it?").

Every time we make a change,
however small,
we should re-run our tests immediately,
because the more things we change at once,
the harder it is to know what's responsible for what
(those N! interactions again).
And we should re-run *all* of our tests:
more than half of fixes made to code introduce (or re-introduce) bugs,
so re-running all of our tests tells us whether we have regressed.

{% enddetails %}
{% details note Keep Track of What You've Done %}

Good scientists keep track of what they've done
so that they can reproduce their work,
and so that they don't waste time repeating the same experiments
or running ones whose results won't be interesting.
Similarly,
debugging works best when we
*keep track of what we've done*
and how well it worked.
If we find ourselves asking,
"Did left followed by right with an odd number of lines cause the crash?
Or was it right followed by left?
Or was I using an even number of lines?"
then it's time to step away from the computer,
take a deep breath,
and start working more systematically.

Records are particularly useful when the time comes to ask for help.
People are more likely to listen to us
when we can explain clearly what we did,
and we're better able to give them the information they need to be useful.

{% enddetails %}
{% details note Version Control Revisited %}

Version control is often used to reset software to a known state during debugging,
and to explore recent changes to code that might be responsible for bugs.
In particular,
most version control systems (e.g. git, Mercurial) have:

1. a `blame` command that shows who last changed each line of a file;
2. a `bisect` command that helps with finding the commit that introduced an
issue.

{% enddetails %}
{% details note Be Humble %}

And speaking of help:
if we can't find a bug in 10 minutes,
we should *be humble* and ask for help.
Explaining the problem to someone else is often useful,
since hearing what we're thinking helps us spot inconsistencies and hidden assumptions.
If you don't have someone nearby to share your problem description with, get a
[rubber duck](https://en.wikipedia.org/wiki/Rubber_duck_debugging)!

Asking for help also helps alleviate confirmation bias.
If we have just spent an hour writing a complicated program,
we want it to work,
so we're likely to keep telling ourselves why it should,
rather than searching for the reason it doesn't.
People who aren't emotionally invested in the code can be more objective,
which is why they're often able to spot the simple mistakes we have overlooked.

Part of being humble is learning from our mistakes.
Programmers tend to get the same things wrong over and over:
either they don't understand the language and libraries they're working with,
or their model of how things work is wrong.
In either case,
taking note of why the error occurred
and checking for it next time
quickly turns into not making the mistake at all.

And that is what makes us most productive in the long run.
As the saying goes,
*A week of hard work can sometimes save you an hour of thought*.
If we train ourselves to avoid making some kinds of mistakes,
to break our code into modular, testable chunks,
and to turn every assumption (or mistake) into an assertion,
it will actually take us *less* time to produce working programs,
not more.

{% enddetails %}
{% details Challenge 1: Debug With a Neighbor %}

Take a function that you have written today, and introduce a tricky bug.
Your function should still run, but will give the wrong output.
Switch seats with your neighbor and attempt to debug
the bug that they introduced into their function.
Which of the principles discussed above did you find helpful?


{% enddetails %}
{% details Challenge 2: Not Supposed to be the Same %}

You are assisting a researcher with Python code that computes the
Body Mass Index (BMI) of patients.  The researcher is concerned because
all patients seemingly have unusual and identical BMIs, despite having different
physiques.  BMI is calculated as **weight in kilograms**
divided by the square of **height in metres**.

Use the debugging principles in this exercise and locate problems
with the code. What suggestions would you give the researcher for
ensuring any later changes they make work correctly? What bugs do you spot?

```python
patients = [[70, 1.8], [80, 1.9], [150, 1.7]]

def calculate_bmi(weight, height):
    return weight / (height ** 2)

for patient in patients:
    weight, height = patients[0]
    bmi = calculate_bmi(height, weight)
    print("Patient's BMI is:", bmi)
```

```output
Patient's BMI is: 0.000367
Patient's BMI is: 0.000367
Patient's BMI is: 0.000367
```

{% details success Solution %}

- Suggestions for debugging
    - Add printing statement in the `calculate_bmi` function, like `print('weight:', weight, 'height:', height)`, to make clear that what the BMI is based on.
    - Change `print("Patient's BMI is: %f" % bmi)` to `print("Patient's BMI (weight: %f, height: %f) is: %f" % (weight, height, bmi))`, in order to be able to distinguish bugs in the function from bugs in the loop.
- Bugs found
    - The loop is not being utilised correctly. `height` and `weight` are always
    set as the first patient's data during each iteration of the loop.
    - The height/weight variables are reversed in the function call to
    `calculate_bmi(...)`, the correct BMIs are 21.604938, 22.160665 and 51.903114.

{% enddetails %}
{% enddetails %}
{% details tip Keypoints %}


- Know what code is supposed to do *before* trying to debug it.
- Make it fail every time.
- Make it fail fast.
- Change one thing at a time, and for a reason.
- Keep track of what you've done.
- Be humble.

{% enddetails %}
## 12. Command-Line Programs

{% details Abstract: Objectives %}


- Use the values of command-line arguments in a program.
- Handle flags and files separately in a command-line program.
- Read data from standard input in a program so that it can be used in a pipeline.

{% enddetails %}
{% details Questions %}


- How can I write Python programs that will work like Unix command-line tools?


{% enddetails %}
{% details note Overview %}

The Jupyter Notebook and other interactive tools are great for prototyping code and exploring data,
but sooner or later we will want to use our program in a pipeline
or run it in a shell script to process thousands of data files.
In order to do that in an efficient way,
we need to make our programs work like other Unix command-line tools.
For example,
we may want a program that reads a dataset
and prints the average inflammation per patient.

{% enddetails %}
{% details note Switching to Shell Commands %}

In this lesson we are switching from typing commands in a Python interpreter to typing
commands in a shell terminal window (such as bash). When you see a `$` in front of a
command that tells you to run that command in the shell rather than the Python interpreter.

This program does exactly what we want - it prints the average inflammation per patient
for a given file.

```bash
$ python ../code/readings_04.py --mean inflammation-01.csv
```

```output
5.45
5.425
6.1
...
6.4
7.05
5.9
```

We might also want to look at the minimum of the first four lines

```bash
$ head -4 inflammation-01.csv | python ../code/readings_06.py --min
```

or the maximum inflammations in several files one after another:

```bash
$ python ../code/readings_04.py --max inflammation-*.csv
```

Our scripts should do the following:

1. If no filename is given on the command line, read data from
standard input.
2. If one or more filenames are given, read data from them and report statistics for each file
separately.
3. Use the `--min`, `--mean`, or `--max` flag to determine what statistic to print.

To make this work,
we need to know how to handle command-line arguments in a program,
and understand how to handle standard input.
We'll tackle these questions in turn below.

{% enddetails %}
{% details note Command-Line Arguments %}

We are going to create a file with our python code in, then use the bash shell to run the code. Using the text editor of your choice,
save the following in a text file called `sys_version.py`:

```python
import sys
print('version is', sys.version)
```

The first line imports a library called `sys`,
which is short for "system".
It defines values such as `sys.version`,
which describes which version of Python we are running.
We can run this script from the command line like this:

```bash
$ python sys_version.py
```

```output
version is 3.4.3+ (default, Jul 28 2015, 13:17:50)
[GCC 4.9.3]
```

Create another file called `argv_list.py` and save the following text to it.

```python
import sys
print('sys.argv is', sys.argv)
```

The strange name `argv` stands for "argument values".
Whenever Python runs a program,
it takes all of the values given on the command line
and puts them in the list `sys.argv`
so that the program can determine what they were.
If we run this program with no arguments:

```bash
$ python argv_list.py
```

```output
sys.argv is ['argv_list.py']
```

the only thing in the list is the full path to our script,
which is always `sys.argv[0]`.
If we run it with a few arguments, however:

```bash
$ python argv_list.py first second third
```

```output
sys.argv is ['argv_list.py', 'first', 'second', 'third']
```

then Python adds each of those arguments to that magic list.

With this in hand, let's build a version of `readings.py` that always prints
the per-patient mean of a single data file.
The first step is to write a function that outlines our implementation,
and a placeholder for the function that does the actual work.
By convention this function is usually called `main`,
though we can call it whatever we want:

```bash
$ cat ../code/readings_01.py
```

```python
import sys
import numpy


def main():
    script = sys.argv[0]
    filename = sys.argv[1]
    data = numpy.loadtxt(filename, delimiter=',')
    for row_mean in numpy.mean(data, axis=1):
        print(row_mean)
```

This function gets the name of the script from `sys.argv[0]`,
because that's where it's always put,
and the name of the file to process from `sys.argv[1]`.
Here's a simple test:

```bash
$ python ../code/readings_01.py inflammation-01.csv
```

There is no output because we have defined a function,
but haven't actually called it.
Let's add a call to `main`:

```bash
$ cat ../code/readings_02.py
```

```python
import sys
import numpy

def main():
    script = sys.argv[0]
    filename = sys.argv[1]
    data = numpy.loadtxt(filename, delimiter=',')
    for row_mean in numpy.mean(data, axis=1):
        print(row_mean)

if __name__ == '__main__':
main()
```

and run that:

```bash
$ python ../code/readings_02.py inflammation-01.csv
```

```output
5.45
5.425
6.1
5.9
5.55
6.225
5.975
6.65
6.625
6.525
6.775
5.8
6.225
5.75
5.225
6.3
6.55
5.7
5.85
6.55
5.775
5.825
6.175
6.1
5.8
6.425
6.05
6.025
6.175
6.55
6.175
6.35
6.725
6.125
7.075
5.725
5.925
6.15
6.075
5.75
5.975
5.725
6.3
5.9
6.75
5.925
7.225
6.15
5.95
6.275
5.7
6.1
6.825
5.975
6.725
5.7
6.25
6.4
7.05
5.9
```

{% enddetails %}
{% details note Running Versus Importing %}

Running a Python script in bash is very similar to
importing that file in Python.
The biggest difference is that we don't expect anything
to happen when we import a file,
whereas when running a script, we expect to see some
output printed to the console.

In order for a Python script to work as expected
when imported or when run as a script,
we typically put the part of the script
that produces output in the following if statement:

```python
if __name__ == '__main__':
    main()  # Or whatever function produces output
```

When you import a Python file, `__name__` is the name
of that file (e.g., when importing `readings.py`,
`__name__` is `'readings'`). However, when running a
script in bash, `__name__` is always set to `'__main__'`
in that script so that you can determine if the file
is being imported or run as a script.

{% enddetails %}
{% details note The Right Way to Do It %}

If our programs can take complex parameters or multiple filenames,
we shouldn't handle `sys.argv` directly.
Instead,
we should use Python's `argparse` library,
which handles common cases in a systematic way,
and also makes it easy for us to provide sensible error messages for our users.
We will not cover this module in this lesson
but you can go to Tshepang Lekhonkhobe's
[Argparse tutorial](https://docs.python.org/3/howto/argparse.html)
that is part of Python's Official Documentation.

We can also use the `argh` library, a wrapper around the `argparse` library that simplifies
its usage (see [the argh documentation](https://pythonhosted.org/argh/) for more information).

{% enddetails %}
{% details note Handling Multiple Files %}

The next step is to teach our program how to handle multiple files.
Since 60 lines of output per file is a lot to page through,
we'll start by using three smaller files,
each of which has three days of data for two patients:

```bash
$ ls small-*.csv
```

```output
small-01.csv small-02.csv small-03.csv
```

```bash
$ cat small-01.csv
```

```output
0,0,1
0,1,2
```

```bash
$ python ../code/readings_02.py small-01.csv
```

```output
0.333333333333
1.0
```

Using small data files as input also allows us to check our results more easily:
here,
for example,
we can see that our program is calculating the mean correctly for each line,
whereas we were really taking it on faith before.
This is yet another rule of programming:
*test the simple things first*.

We want our program to process each file separately,
so we need a loop that executes once for each filename.
If we specify the files on the command line,
the filenames will be in `sys.argv`,
but we need to be careful:
`sys.argv[0]` will always be the name of our script,
rather than the name of a file.
We also need to handle an unknown number of filenames,
since our program could be run for any number of files.

The solution to both problems is to loop over the contents of `sys.argv[1:]`.
The '1' tells Python to start the slice at location 1,
so the program's name isn't included;
since we've left off the upper bound,
the slice runs to the end of the list,
and includes all the filenames.
Here's our changed program
`readings_03.py`:

```bash
$ cat ../code/readings_03.py
```

```python
import sys
import numpy

def main():
    script = sys.argv[0]
    for filename in sys.argv[1:]:
        data = numpy.loadtxt(filename, delimiter=',')
        for row_mean in numpy.mean(data, axis=1):
            print(row_mean)

if __name__ == '__main__':
main()
```

and here it is in action:

```bash
$ python ../code/readings_03.py small-01.csv small-02.csv
```

```output
0.333333333333
1.0
13.6666666667
11.0
```

{% enddetails %}
{% details note The Right Way to Do It %}


At this point, we have created three versions of our script called `readings_01.py`,
`readings_02.py`, and `readings_03.py`.
We wouldn't do this in real life: instead, we would have one file called `readings.py` that we committed to version control
every time we got an enhancement working. For teaching,
though, we need all the successive versions side by side.

{% enddetails %}
{% details note Handling Command-Line Flags %}


The next step is to teach our program to pay attention to the `--min`, `--mean`, and `--max` flags.
These always appear before the names of the files,
so we could do this:

```bash
$ cat ../code/readings_04.py
```

```python
import sys
import numpy

def main():
    script = sys.argv[0]
    action = sys.argv[1]
    filenames = sys.argv[2:]

    for filename in filenames:
        data = numpy.loadtxt(filename, delimiter=',')

        if action == '--min':
            values = numpy.amin(data, axis=1)
        elif action == '--mean':
            values = numpy.mean(data, axis=1)
        elif action == '--max':
            values = numpy.amax(data, axis=1)

        for val in values:
            print(val)

if __name__ == '__main__':
main()
```

This works:

```bash
$ python ../code/readings_04.py --max small-01.csv
```

```output
1.0
2.0
```

but there are several things wrong with it:

1. `main` is too large to read comfortably.

2. If we do not specify at least two additional arguments on the
command-line, one for the **flag** and one for the **filename**, but only
one, the program will not throw an exception but will run. It assumes that the file
list is empty, as `sys.argv[1]` will be considered the `action`, even if it
is a filename. Silent failures like this
are always hard to debug.

3. The program should check if the submitted `action` is one of the three recognized flags.

This version pulls the processing of each file out of the loop into a function of its own.
It also checks that `action` is one of the allowed flags
before doing any processing,
so that the program fails fast:

```bash
$ cat ../code/readings_05.py
```

```python
import sys
import numpy

def main():
    script = sys.argv[0]
    action = sys.argv[1]
    filenames = sys.argv[2:]
    assert action in ['--min', '--mean', '--max'], \
        'Action is not one of --min, --mean, or --max: ' + action
    for filename in filenames:
        process(filename, action)

def process(filename, action):
    data = numpy.loadtxt(filename, delimiter=',')

    if action == '--min':
        values = numpy.amin(data, axis=1)
    elif action == '--mean':
        values = numpy.mean(data, axis=1)
    elif action == '--max':
        values = numpy.amax(data, axis=1)

    for val in values:
        print(val)

if __name__ == '__main__':
main()
```

This is four lines longer than its predecessor,
but broken into more digestible chunks of 8 and 12 lines.

{% enddetails %}
{% details note Handling Standard Input %}


The next thing our program has to do is read data from standard input if no filenames are given
so that we can put it in a pipeline,
redirect input to it,
and so on.
Let's experiment in another script called `count_stdin.py`:

```bash
$ cat ../code/count_stdin.py
```

```python
import sys

count = 0
for line in sys.stdin:
    count += 1

print(count, 'lines in standard input')
```

This little program reads lines from a special "file" called `sys.stdin`,
which is automatically connected to the program's standard input.
We don't have to open it --- Python and the operating system
take care of that when the program starts up ---
but we can do almost anything with it that we could do to a regular file.
Let's try running it as if it were a regular command-line program:

```bash
$ python ../code/count_stdin.py < small-01.csv
```

```output
2 lines in standard input
```

A common mistake is to try to run something that reads from standard input like this:

```bash
$ python ../code/count_stdin.py small-01.csv
```

i.e., to forget the `<` character that redirects the file to standard input.
In this case,
there's nothing in standard input,
so the program waits at the start of the loop for someone to type something on the keyboard.
Since there's no way for us to do this,
our program is stuck,
and we have to halt it using the `Interrupt` option from the `Kernel` menu in the Notebook.

We now need to rewrite the program so that it loads data from `sys.stdin`
if no filenames are provided.
Luckily,
`numpy.loadtxt` can handle either a filename or an open file as its first parameter,
so we don't actually need to change `process`.
Only `main` changes:

```bash
$ cat ../code/readings_06.py
```

```python
import sys
import numpy

def main():
    script = sys.argv[0]
    action = sys.argv[1]
    filenames = sys.argv[2:]
    assert action in ['--min', '--mean', '--max'], \
        'Action is not one of --min, --mean, or --max: ' + action
    if len(filenames) == 0:
        process(sys.stdin, action)
    else:
        for filename in filenames:
            process(filename, action)

def process(filename, action):
    data = numpy.loadtxt(filename, delimiter=',')

    if action == '--min':
        values = numpy.amin(data, axis=1)
    elif action == '--mean':
        values = numpy.mean(data, axis=1)
    elif action == '--max':
        values = numpy.amax(data, axis=1)

    for val in values:
        print(val)

if __name__ == '__main__':
main()
```

Let's try it out:

```bash
$ python ../code/readings_06.py --mean < small-01.csv
```

```output
0.333333333333
1.0
```

That's better. In fact, that's done: the program now does everything we set out to do.

{% enddetails %}
{% details Challenge 1: Arithmetic on the Command Line %}

Write a Python program that adds, subtracts, multiplies, or divides two numbers provided on the command line:

```bash
$ python arith.py --add 1 2
```

```output
3.0
```

```bash
$ python arith.py --subtract 3 4
```

```output
-1.0
```

{% details success Solution %}


```python
import sys

def main():
    assert len(sys.argv) == 4, 'Need exactly 3 arguments'

    operator = sys.argv[1]
    assert operator in ['--add', '--subtract', '--multiply', '--divide'], \
        'Operator is not one of --add, --subtract, --multiply, or --divide: bailing out'
    try:
        operand1, operand2 = float(sys.argv[2]), float(sys.argv[3])
    except ValueError:
        print('cannot convert input to a number: bailing out')
        return

    do_arithmetic(operand1, operator, operand2)

def do_arithmetic(operand1, operator, operand2):

    if operator == 'add':
        value = operand1 + operand2
    elif operator == 'subtract':
        value = operand1 - operand2
    elif operator == 'multiply':
        value = operand1 * operand2
    elif operator == 'divide':
        value = operand1 / operand2
    print(value)

main()
```

{% enddetails %}
{% enddetails %}
{% details Challenge 2: Finding Particular Files %}

Using the `glob` module introduced earlier, write a simple version of `ls` that shows files in the current directory
with a particular suffix.
A call to this script should look like this:

```bash
$ python my_ls.py py
```

```output
left.py
right.py
zero.py
```

{% details success Solution %}


```python
import sys
import glob

def main():
    """prints names of all files with sys.argv as suffix"""
    assert len(sys.argv) >= 2, 'Argument list cannot be empty'
    suffix = sys.argv[1] # NB: behaviour is not as you'd expect if sys.argv[1] is *
    glob_input = '*.' + suffix # construct the input
    glob_output = sorted(glob.glob(glob_input)) # call the glob function
    for item in glob_output: # print the output
        print(item)
    return

main()
```


{% enddetails %}
{% enddetails %}
{% details Challenge 3: Changing Flags %}

Rewrite `readings.py` so that it uses `-n`, `-m`, and `-x`
instead of `--min`, `--mean`, and `--max` respectively.
Is the code easier to read?
Is the program easier to understand?

{% details success Solution %}


```python
# this is code/readings_07.py
import sys
import numpy

def main():
    script = sys.argv[0]
    action = sys.argv[1]
    filenames = sys.argv[2:]
    assert action in ['-n', '-m', '-x'], \
        'Action is not one of -n, -m, or -x: ' + action
    if len(filenames) == 0:
        process(sys.stdin, action)
    else:
        for filename in filenames:
            process(filename, action)

def process(filename, action):
    data = numpy.loadtxt(filename, delimiter=',')

    if action == '-n':
        values = numpy.amin(data, axis=1)
    elif action == '-m':
        values = numpy.mean(data, axis=1)
    elif action == '-x':
        values = numpy.amax(data, axis=1)

    for val in values:
        print(val)

main()
```


{% enddetails %}
{% enddetails %}
{% details Challenge 4: Adding a Help Message %}


Separately, modify `readings.py` so that if no parameters are given
(i.e., no action is specified and no filenames are given), it prints a message explaining how it should be used.

{% details success Solution %}


```python
# this is code/readings_08.py
import sys
import numpy

def main():
    script = sys.argv[0]
    if len(sys.argv) == 1:  # no arguments, so print help message
        print("Usage: python readings_08.py action filenames\n"
            "Action:\n"
            "    Must be one of --min, --mean, or --max.\n"
            "Filenames:\n"
            "    If blank, input is taken from standard input (stdin).\n"
            "    Otherwise, each filename in the list of arguments is processed in turn.")
        return

    action = sys.argv[1]
    filenames = sys.argv[2:]
    assert action in ['--min', '--mean', '--max'], (
        'Action is not one of --min, --mean, or --max: ' + action)
    if len(filenames) == 0:
        process(sys.stdin, action)
    else:
        for filename in filenames:
            process(filename, action)

def process(filename, action):
    data = numpy.loadtxt(filename, delimiter=',')

    if action == '--min':
        values = numpy.amin(data, axis=1)
    elif action == '--mean':
        values = numpy.mean(data, axis=1)
    elif action == '--max':
        values = numpy.amax(data, axis=1)

    for val in values:
        print(val)

if __name__ == '__main__':
    main()

```

{% enddetails %}
{% enddetails %}
{% details Challenge 5: Adding a Default Action %}


Separately,
modify `readings.py` so that if no action is given
it displays the means of the data.

{% details success Solution %}


```python
# this is code/readings_09.py
import sys
import numpy

def main():
    script = sys.argv[0]
    action = sys.argv[1]
    if action not in ['--min', '--mean', '--max']: # if no action given
        action = '--mean'    # set a default action, that being mean
        filenames = sys.argv[1:] # start the filenames one place earlier in the argv list
    else:
        filenames = sys.argv[2:]

    if len(filenames) == 0:
        process(sys.stdin, action)
    else:
        for filename in filenames:
            process(filename, action)

def process(filename, action):
    data = numpy.loadtxt(filename, delimiter=',')

    if action == '--min':
        values = numpy.amin(data, axis=1)
    elif action == '--mean':
        values = numpy.mean(data, axis=1)
    elif action == '--max':
        values = numpy.amax(data, axis=1)

    for val in values:
        print(val)

main()
```



{% enddetails %}
{% enddetails %}
{% details Challenge 6: A File-Checker %}


Write a program called `check.py` that takes the names of one or more
inflammation data files as arguments
and checks that all the files have the same number of rows and columns.
What is the best way to test your program?

{% details success Solution %}


```python
import sys
import numpy

def main():
    script = sys.argv[0]
    filenames = sys.argv[1:]
    if len(filenames) <=1: #nothing to check
        print('Only 1 file specified on input')
    else:
        nrow0, ncol0 = row_col_count(filenames[0])
        print('First file %s: %d rows and %d columns' % (filenames[0], nrow0, ncol0))
        for filename in filenames[1:]:
            nrow, ncol = row_col_count(filename)
            if nrow != nrow0 or ncol != ncol0:
                print('File %s does not check: %d rows and %d columns' % (filename, nrow, ncol))
            else:
                print('File %s checks' % filename)
        return

def row_col_count(filename):
    try:
        nrow, ncol = numpy.loadtxt(filename, delimiter=',').shape
    except ValueError:
        # 'ValueError' error is raised when numpy encounters lines that
        # have different number of data elements in them than the rest of the lines,
        # or when lines have non-numeric elements
        nrow, ncol = (0, 0)
    return nrow, ncol

main()
```


{% enddetails %}
{% enddetails %}
{% details Challenge 7: Counting Lines %}

Write a program called `line_count.py` that works like the Unix `wc` command:

- If no filenames are given, it reports the number of lines in standard input.
- If one or more filenames are given, it reports the number of lines in each,
followed by the total number of lines.

{% details success Solution %}


```python
import sys

def main():
    """print each input filename and the number of lines in it,
    and print the sum of the number of lines"""
    filenames = sys.argv[1:]
    sum_nlines = 0 #initialize counting variable

    if len(filenames) == 0: # no filenames, just stdin
        sum_nlines = count_file_like(sys.stdin)
        print('stdin: %d' % sum_nlines)
    else:
        for filename in filenames:
            nlines = count_file(filename)
            print('%s %d' % (filename, nlines))
            sum_nlines += nlines
        print('total: %d' % sum_nlines)

def count_file(filename):
    """count the number of lines in a file"""
    f = open(filename, 'r')
    nlines = len(f.readlines())
    f.close()
    return(nlines)

def count_file_like(file_like):
    """count the number of lines in a file-like object (eg stdin)"""
    n = 0
    for line in file_like:
        n = n+1
    return n

main()

```


{% enddetails %}
{% enddetails %}
{% details Challenge 8: Generate an Error Message %}


Write a program called `check_arguments.py` that prints usage
then exits the program if no arguments are provided.
(Hint: You can use `sys.exit()` to exit the program.)

```bash
$ python check_arguments.py
```

```output
usage: python check_argument.py filename.txt
```

```bash
$ python check_arguments.py filename.txt
```

```output
Thanks for specifying arguments!
```

{% enddetails %}
{% details tip Keypoints %}


- The `sys` library connects a Python program to the system it is running on.
- The list `sys.argv` contains the command-line arguments that a program was run with.
- Avoid silent failures.
- The pseudo-file `sys.stdin` connects to a program's standard input.



{% enddetails %}
