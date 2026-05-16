---
layout: lecture
pretty_table: true
title: "Convolution Neural Networks"

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
  - name: Overview
  - name: Convolutional Neural Networks
---

## Overview

- Previously, in the code that construct a neural network to estimate the output from single-valued input (*assume linear relation*), 
we use neuron with shape of `[1]`. 
- It is possible to create complex neural networks to estimate outputs from multi-dimensional inputs. 
    - Example of such input: images

{% details How does computers see images %}

- Human see images as colored blobs. 
- Machines `see` images as matrices of numbers, which in turn can be converted into colored pixels to be displayed on screen for human to see. 
- Open the `convlutions.ipynb` notebook and run the cell with the following code:

```python
import numpy as np
import matplotlib.pyplot as plt

# 1. CREATE A 2D MATRIX (Grayscale Image)
# 10x10 matrix: 0 is black, 255 is white
matrix_2d = np.array([
    [0,   0,   0,   0,   0,   0,   0,   0,   0,   0],
    [0, 255, 255,   0,   0,   0,   0, 255, 255,   0],
    [0, 255, 255,   0,   0,   0,   0, 255, 255,   0],
    [0,   0,   0,   0,   0,   0,   0,   0,   0,   0],
    [0,   0,   0,   0, 128, 128,   0,   0,   0,   0],
    [0,   0,   0,   0, 128, 128,   0,   0,   0,   0],
    [0, 255,   0,   0,   0,   0,   0,   0, 255,   0],
    [0,   0, 255,   0,   0,   0,   0, 255,   0,   0],
    [0,   0,   0, 255, 255, 255, 255,   0,   0,   0],
    [0,   0,   0,   0,   0,   0,   0,   0,   0,   0]
], dtype=np.uint8)

# Convert 2D matrix to a grayscale image plot
plt.figure(figsize=(4, 4))
plt.imshow(matrix_2d, cmap='gray')
plt.title("2D Matrix (Grayscale)")
plt.axis('off')
plt.show()

# 2. CREATE A 3D MATRIX (RGB Color Image)
# 3x3 pixels, 3 channels deep (Red, Green, Blue)
matrix_3d = np.zeros((3, 3, 3), dtype=np.uint8)

# Set pixel colors: [Row, Column] = [Red, Green, Blue]
matrix_3d[0, 0] = [255, 0, 0]     # Top-left: Pure Red
matrix_3d[1, 1] = [0, 255, 0]     # Center: Pure Green
matrix_3d[2, 2] = [0, 0, 255]     # Bottom-right: Pure Blue
matrix_3d[0, 2] = [255, 255, 0]   # Top-right: Yellow (Red + Green)

# Convert 3D matrix to a color image plot
plt.figure(figsize=(4, 4))
plt.imshow(matrix_3d)
plt.title("3D Matrix (RGB)")
plt.axis('off')
plt.show()

# 3. VICE VERSA: CONVERT AN IMAGE BACK TO A MATRIX
# Save the 3D plot image locally, then read it back as a raw matrix
plt.savefig('color_grid.png')
image_matrix = plt.imread('color_grid.png')

# Print the dimensions of the reconstructed matrix
print("Reconstructed Matrix Shape (Height, Width, Channels):", image_matrix.shape)
```

- The results from the cell show that the `matrix_2d` and `matrix_3d` are converted into images. 
- Vice versa, we can also examine images and view their matrix representation:

```python
import matplotlib.pyplot as plt
from skimage import data

# 1. DOWNLOAD & LOAD A WELL-KNOWN IMAGE
# skimage (scikit-image) has built-in iconic test images. We will use a small 100x100 thumbnail.
astronaut_image = data.astronaut()  # Original large image

# Slice the matrix to make it a tiny 64x64 pixel image for easy viewing
small_astronaut = astronaut_image[100:164, 200:264]

# 2. DISPLAY THE IMAGE
plt.figure(figsize=(4, 4))
plt.imshow(small_astronaut)
plt.title("64x64 Astronaut Thumbnail")
plt.axis('off')  # Hide pixel coordinate axes
plt.show()

# 3. CONVERT IT BACK TO A RAW MATRIX
# Converting a PIL or skimage image into a NumPy matrix is done via np.array()
image_matrix = bytearray(small_astronaut)  # Alternatively, np.array(small_astronaut)

# Print out the array specifications
print("--- MATRIX SPECS ---")
print("Matrix Type:", type(small_astronaut))
print("Matrix Dimensions (Height, Width, Color Channels):", small_astronaut.shape)
print("Total number of values:", small_astronaut.size)

# Print a tiny slice of the raw matrix data (Top-left 3x3 pixels)
# Each pixel contains 3 values: [Red, Green, Blue]
print("\n--- RAW RGB MATRIX VALUES (Top-Left 3x3 Grid) ---")
print(small_astronaut[0:3, 0:3])
```

{% enddetails %}

- As stated earlier, we can design complex neural networks to support multi-dimensional input data. 
    - Such as images (image recognition, pattern recognition, etc)

## Convolutional Neural Networks

{% details Limitation of previous Deep Neural Networks (DNN) %}

- Training images data from [MNIST-fashion dataset](https://keras.io/api/datasets/fashion_mnist/) has several significant constraints: 
    - The images were 28x28, grey scale, and 
    - The item was centered in the image.

- [Convolutional Neural Network](http://yann.lecun.com/exdb/publis/pdf/lecun-89e.pdf) is a NN design that 
significantly improves both performance quality and processing speed compared to a standard fully connected 
neural network (Multi-Layer Perceptron, or MLP) for image tasks.

{% include figure.liquid path="assets/img/courses/csc574/06-convolutions/sneaker_monochrome.png" max-width="50%" zoomable=true %}

{% include figure.liquid path="assets/img/courses/csc574/06-convolutions/boots-181744_1280.jpg" max-width="50%" zoomable=true %}

- Potential problems:
    - Image is not a 28x28 greyscale
    - The boot is not directly left-facing like the training data. 
- A convolution is a filter that passes over an image, processing it, and extracting features that show a commonalatity in the image. 

{% enddetails %}

More technical details about CNN can be found at [Visualizing and Understanding Convolutional Networks]( https://arxiv.org/pdf/1311.2901)