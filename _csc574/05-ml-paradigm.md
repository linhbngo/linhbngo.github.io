---
layout: lecture
pretty_table: true
title: "Machine Learning Paradigm"

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
  - name: Overview and motivation
  - name: Measure accuracy
  - name: Introductory Neural Network
---

## Overview and motivation

{% details note Example %}

- A new paradigm for programming
    - Explicitly coding a solution vs Implicitly learning a solution

{% details Example: Explicit coding: pong %}

- It is how we do it since the beginning of time!

{% include figure.liquid path="assets/img/courses/csc574/02-ml-paradigm/pong.png" max-width="25%" zoomable=true %}

- The ball moves along a path
    - Angle/velocity
- The ball hits
    - A paddle or a wall
    - Change of angle/velocity
- We can **code** these behaviors based on physical rules + game rules
    - Rules are predetermined by the programmer, then coded and tested. Everything needs to be figured out in advance.
    - Complexity scale with code amount

{% enddetails %}
{% details info Explicit coding %}

{% include figure.liquid path="assets/img/courses/csc574/02-ml-paradigm/explicit_coding.jpeg" max-width="50%" zoomable=true %}

- Powerful but can be limited

{% enddetails %}

{% details Explicit coding example: activity detection %}

- Write an app that uses sensors on a phone or a watch or something else to 
determine a person's activity.
    - Use the data about their speed and write a rule that determines 
    if the speed is below a certain amount, then they're probably walking.

{% details success Walking %}

- If less than 4 miles an hour, then they are walking.

{% include figure.liquid path="assets/img/courses/csc574/02-ml-paradigm/walking.png" max-width="50%" zoomable=true %}
 
```python
if speed < 4.0:
    print("Walking")
```

{% enddetails %}

{% details success Running %}

- If more than 4 miles an hour, then they are running. 

{% include figure.liquid path="assets/img/courses/csc574/02-ml-paradigm/running.jpg" max-width="50%" zoomable=true %}

```python
if speed < 4.0:
    print("Walking")
else:
    print("Running")
```

{% enddetails %}

{% details success Biking %}

- If more than 4 miles an hour but less than 12, then they are running. 
- Otherwise, they are biking

{% include figure.liquid path="assets/img/courses/csc574/02-ml-paradigm/biking.jpg" max-width="50%" zoomable=true %}

```python
if speed < 4.0:
    print("Walking")
elif speed < 12.0:
    print("Running")
else
    print("Biking")
``` 

{% enddetails %}

{% details failure Playing soccer %}

- How do we describe movements of soccer players? goal keeper?

{% include figure.liquid path="assets/img/courses/csc574/02-ml-paradigm/soccer.jpg" max-width="50%" zoomable=true %}

{% enddetails %}

- It is challenging to write rules for complex problems

{% enddetails %}

{% details info Implicit learning %}

{% include figure.liquid path="assets/img/courses/csc574/02-ml-paradigm/implicit_learning.jpeg" max-width="50%" zoomable=true %}

{% enddetails %}

{% enddetails %}

{% details note Machine Learning Paradigm %}

- In a nutshell:
    - Make a guess about the relationship between the data and its labels
        - `low speed` + `long distance or short distance` + `along road` + `few stops`  = `walking`
        - `low speed` + `long distance` + `on a field` + `regular stops` = `golfing`
        - `low or high speed` + `long distance` + `enclosed area` = `soccer`
    - Measures how good or how bad that guess is.
        - Terminology: `loss`
        - Higher loss implies lower accuracy.
        - Measure the results of your guess,
        - Use the data from the accuracy measurement to estimate next guess, optimizing
        based on what you already know.
    - Repeat the process
        - Assumption: each subsequent guess gets better than the previous one

{% enddetails %}

{% details Example: Relationship between two sets of numbers %}

- X: $-1,0,1,2,3,4$
- Y: $-3,-1,1,3,5,7$

{% details First guess %}

- $x_1=-1$ and $y_1=-3$
    - $y_1 = 3{x}_1$
- $Y = 3X$
    - Guess: $-3,0,3,6,9,12$ 
    - Expected: Y: $-3,-1,1,3,5,7$

{% enddetails %}

{% details Second guess %}

- $x_1=-1$ and $y_1=-3$
    - $y_1 = 3x_1$
- $x_2=0$ and $y_1=-1$
    - $y_2 = x_2 - 1$
- $Y = 3X - 1$
    - Guess: $-4,-1,2,5,8,11$ 
    - Expected: Y: $-3,-1,1,3,5,7$

{% enddetails %}

{% details Third guess %}

- $x_1=-1$ and $y_1=-3$
    - $y_1 = 3x_1$
- $x_2=0$ and $y_1=-1$
    - $y_2 = x_2 - 1$
- $x_3=1$ and $y_3=2$
    - $y_3 = 2x_3$
- $Y = 2X - 1$
    - Guess: $-3,-1,1,3,5,7$ 
    - Expected: Y: $-3,-1,1,3,5,7$

{% enddetails %}
{% enddetails %}


## Measure accuracy

{% details note Setting up programming environment %}

- Open the `ml-paradigm.ipynb` notebook from the tinyml Git repo (python/notebooks).
    - Select `tinyml` as the kernel for the notebook. 

{% enddetails %}


{% details Example: Coding hands on %}

- Run the following code segment in a cell and monitor different combinations of `w` and `b` to observe the loss value

```python
import math
import matplotlib.pyplot as plt
import numpy as np

w = 3
b = -1

x = [-1, 0, 1, 2, 3, 4]
y = [-3, -1, 1, 3, 5, 7]
myY = []

for thisX in x:
  thisY = (w*thisX)+b
  myY.append(thisY)

print(f"Real Y is {str(y)}")
print(f"My Y is   {str(myY)}")

# Sample data
x = np.array(x)
y = np.array(y)
myY = np.array(myY)

plt.plot(x, y, 'o')  # Plot points as circles
plt.plot(x, myY, 'o')  # Plot points as circles

# Add vertical lines
for i in range(len(x)):
    plt.vlines(x[i], y[i], myY[i], linestyles='dashed')
    length = y[i] - myY[i]
    plt.text(x[i], (y[i] + myY[i]) / 2, f"{length:.2f}", ha='center', va='center')

# Add gridlines
plt.grid(True)

plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Points with Vertical Lines')
plt.show()
```

{% enddetails %}

{% details note How good (or bad) are your guesses? %}

- We want to have a way to measure the loss values and their aggregation.
- Account for negative value (over/under guess)
- Run the following code in the next cell of your notebook

```python
import math

w = 3
b = -1

x = [-1, 0, 1, 2, 3, 4]
y = [-3, -1, 1, 3, 5, 7]
myY = []


for thisX in x:
  thisY = (w*thisX)+b
  myY.append(thisY)

print(f"Real Y is {str(y)}")
print(f"My Y is   {str(myY)}")

# let's calculate the loss
total_square_error = 0
for i in range(0, len(y)):
  square_error = (y[i] - myY[i]) ** 2
  total_square_error += square_error

print(f"My loss is: {str(math.sqrt(total_square_error))}")

```

{% enddetails %}


{% details note Loss function %}


Loss function: Mean Squared Error (MSE)

$J = \frac{1}{n}\sum(actual-predicted)^2$

- Given the following\
    - Set of X: $x_0,x_1,...,x_n$
    - Set of Y (actual): $y_0,y_1,...y_n$
    - A linear regression function that try to estimate Y from X: $Y=mX + c$

MSE loss function for linear regression

 $J = \frac{1}{n}\sum^{n}_{i=0} (y_i - (mx_i+c))^2$

{% enddetails %}

{% details Gradient descent %}

- Gradient: measure of change in all the weights (m and c in the case of linear regression) with regard to change in error.
    - Slope of a function
- Gradient descent:
    - Iterative function that applies a predefined rate of change (learning rate) to m and c 
    until a perceived minimal loss is realized. 

```python
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Generate some sample data
np.random.seed(0)
X = 2 * np.random.rand(100, 1)
y = 4 + 3 * X + np.random.randn(100, 1)

# Define a function to compute the loss
def compute_loss(w0, w1):
    y_pred = w0 + w1 * X
    return np.mean((y - y_pred) ** 2)

# Create a grid of parameter values
w0_range = np.linspace(-10, 10, 50)
w1_range = np.linspace(-10, 10, 50)
W0, W1 = np.meshgrid(w0_range, w1_range)

# Compute the loss for each combination of parameter values
loss = np.zeros_like(W0)
for i in range(len(w0_range)):
    for j in range(len(w1_range)):
        loss[i, j] = compute_loss(W0[i, j], W1[i, j])

# Plot the 3D surface
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(W0, W1, loss, cmap='viridis')
ax.set_xlabel('w0 (intercept)')
ax.set_ylabel('w1 (slope)')
ax.set_zlabel('Loss')
plt.show()
```

{% enddetails %}

{% details Gradient descent for linear regression %}

- $D_m = \frac{1}{n}\sum^{n}_{i=0} 2(y_i - (mx_i+c))^2(-x_i)$
- $D_c = \frac{-2}{n}\sum^{n}_{i=0} (y_i - (mx_i+c))$
- L = learning rate < 1
- $m = m - LD_m$
- $c = c - LD_c$

{% include figure.liquid path="assets/img/courses/csc574/02-ml-paradigm/ICLH_Diagram_Batch_03_21-AI-ML-GradientDescent.png" max-width="50%" zoomable=true %}

{% enddetails %}

{% details Gradient descent in tensorflow %}

- Download and launch the following notebook

[Minimizing Loss](codes/02-ml-paradigm/Mimimizing_Loss.ipynb)

- Change the learning rate and observe how that change the loss values

{% enddetails %}


## Introductory Neural Network

{% details note Preparation %}

- In the previous lecture, I showed the installation of in-person Anaconda/tensorflow

{% details info Alternative: Google Colab %}

- Visit [https://colab.research.google.com/](https://colab.research.google.com/)
- Sign in with your Gmail account, or with your West Chester University account (works 
for Google)
- Click `File` and select `New notebook in Drive`

{% enddetails %}
{% enddetails %}
{% details note Loading libraries %}

- In the first cell, run the following:

```python linenums="1"
import sys
import numpy as np
import tensorflow as tf
```

{% enddetails %}
{% details note Setup a simple neural network model %}


- In the second cell, run the following:

```python linenums="1"
model = tf.keras.Sequential([tf.keras.layers.Dense(units=1, input_shape=[1])])

model.compile(optimizer='sgd', loss='mean_squared_error')

xs = np.array([-1.0,  0.0, 1.0, 2.0, 3.0, 4.0], dtype=float)
ys = np.array([-3.0, -1.0, 1.0, 3.0, 5.0, 7.0], dtype=float)

model.fit(xs, ys, epochs=500)

```   

- Line 1 defines a very simple neural network model. 
    - `units= 1`: Dimensionality of the output space
    - `input_shape=[1]`: Dimensionality of the input data
    - We're training a neural network on single x's to predict single y's.

{% details Example: A neural network %}


{% include figure.liquid path="assets/img/courses/csc574/02-ml-paradigm/nn.jpg" max-width="50%" zoomable=true %}

- Hidden Layer 1: `units=4`
- Hidden Layer 2: `units=4`
- Output Layer: `units=1`

{% enddetails %}
- Line 2 compiles the model
    - Optimizer is defined as `sgd` - Stochastic Gradient Descent. 
    - Loss function is `mean_squared_error` - MSE.

- Lines 5 and 6 define the X and Y arrays to train the models. 
- The fitting process runs 500 times (500 epochs)
    - Each epoch is a step:
        - Guess
        - Measure the loss
        - Optimize and repeat

```python linenums="1"
print(model.predict(np.array([10.0])))
```

- By providing an array of test inputs, we can observe the predicted outputs

```python linenums="1"
print(model.predict(np.array([10.0, 11.0])))
```

{% enddetails %}
{% details note Common Layer Type %}

- Dense Layer: neurons from previous layer fully connected to neurons in the next layer
- Convolutional Layer: contain filters that can be used to transform data
- Recurrent Layer: allow learning about relationship between data points 
in a sequence. 

{% enddetails %}
{% details Question: Exercise %}


- Replace `SHAPE` and `LOSS` with relevance values for the following segment of code, 
then run it in a new cell

```python linenums="1"
import sys

import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense

predictions = []
class myCallback(tf.keras.callbacks.Callback):
def on_epoch_end(self, epoch, logs={}):
    predictions.append(model.predict(xs))
callbacks = myCallback()

# We then define the xs (inputs) and ys (outputs)
xs = np.array([-1.0, 0.0, 1.0, 2.0, 3.0, 4.0], dtype=float)
ys = np.array([-3.0, -1.0, 1.0, 3.0, 5.0, 7.0], dtype=float)

SHAPE = #YOUR CODE HERE#
LOSS = #YOUR CODE HERE#

model = Sequential([Dense(units=1, input_shape=SHAPE)])
model.compile(optimizer='sgd', loss=LOSS)
model.fit(xs, ys, epochs=300, callbacks=[callbacks], verbose=2)
EPOCH_NUMBERS=[1,25,50,150,300] # Update me to see other Epochs
plt.plot(xs,ys,label = "Ys")
for EPOCH in EPOCH_NUMBERS:
    plt.plot(xs,predictions[EPOCH-1],label = "Epoch = " + str(EPOCH))
plt.legend()
plt.show()
```
{% enddetails %}
