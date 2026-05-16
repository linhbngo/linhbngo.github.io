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
  - name: CNN in Tensorflow
  - name: Visualizing CNN
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

{% include figure.liquid path="assets/img/courses/csc574/06-convolutions/sneaker_monochrome.png" max-width="50%" zoomable=true %}

{% include figure.liquid path="assets/img/courses/csc574/06-convolutions/boots-181744_1280.jpg" max-width="50%" zoomable=true %}

```python
import tensorflow as tf
mnist = tf.keras.datasets.fashion_mnist
(training_images, training_labels), (val_images, val_labels) = mnist.load_data()
training_images=training_images / 255.0
val_images=val_images / 255.0
model = tf.keras.models.Sequential([
  tf.keras.layers.Flatten(),
  tf.keras.layers.Dense(20, activation=tf.nn.relu),
  tf.keras.layers.Dense(10, activation=tf.nn.softmax)
])
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
model.fit(training_images, training_labels, validation_data=(val_images, val_labels), epochs=20)
```

- After 20 training iteration (`epoch`), the training result parameters are:
  - accuracy: 0.8932 
  - loss: 0.2944 
  - val_accuracy: 0.8675 
  - val_loss: 0.3820
- This means that at the end of the training data set, the model achieves approximately 89% on the training dataset and 
86% on the validation dataset. 


{% enddetails %}


{% details Convolutional Neural Networks (CNN) %}

- [Convolutional Neural Network](http://yann.lecun.com/exdb/publis/pdf/lecun-89e.pdf) is a NN design that 
significantly improves both performance quality and processing speed compared to a standard fully connected 
neural network (Multi-Layer Perceptron, or MLP) for image tasks.
- The concept of CNN is somewhat similar to the idea of doing [image processing using a filter](https://en.wikipedia.org/wiki/Kernel_(image_processing)). 
- The core idea is to take a matrix (`kernel`) of size 3x3 or 5x5 and pass it over the image. Based on the contents of the kernel 
matrix, it is possible to enhance specific features of the images such as edges or contours. As a result, this helps making these 
features more `notable` and `estimatables` by the weights and biases of the subsequent neuron layers. 
  - The convolutional passing will also help reducing raw data and focusing on feature data only. 

{% include figure.liquid path="assets/img/courses/csc574/06-convolutions/lab3-fig1.png" max-width="50%" zoomable=true %}

{% enddetails %}

{% details Example: manual convolution %}

To demonstrate the operation of CNN, let's look at a [stairwell image](https://pixnio.com/people/accent-to-the-top)

We will start with the following filter. This filter will emphasize horizontal edges. 

$$
\begin{bmatrix}
-1 & -2 & -1 \\
 0 &  0 &  0 \\
 1 &  2 &  1 
\end{bmatrix} 
$$

```python
import numpy as np
from scipy import datasets
import matplotlib.pyplot as plt

i = datasets.ascent() 
i = i.astype(np.int16)
i_transformed = np.copy(i)
size_x = i_transformed.shape[0]
size_y = i_transformed.shape[1]

filter = [[-1, -2, -1], [0, 0, 0], [1, 2, 1]] 
weight = 1

for x in range(1,size_x-1):
  for y in range(1,size_y-1):
      convolution = 0.0
      convolution = convolution + ((i[x-1,y-1]) * filter[0][0])
      convolution = convolution + (i[x, y-1] * filter[1][0])
      convolution = convolution + (i[x + 1, y-1] * filter[2][0])
      convolution = convolution + (i[x-1, y] * filter[0][1])
      convolution = convolution + (i[x, y] * filter[1][1])
      convolution = convolution + (i[x+1, y] * filter[2][1])
      convolution = convolution + (i[x-1, y+1] * filter[0][2])
      convolution = convolution + (i[x, y+1] * filter[1][2])
      convolution = convolution + (i[x+1, y+1] * filter[2][2])
      convolution = convolution * weight
      if(convolution<0):
        convolution=0
      if(convolution>255):
        convolution=255
      i_transformed[x, y] = convolution

fig, axes = plt.subplots(1, 2, figsize=(12, 6))
axes[0].imshow(i, cmap='gray')
axes[0].set_title("Original Stairwell")
axes[1].imshow(i_transformed, cmap='gray')
axes[1].set_title("Stairwell with Convolution Applied")
plt.tight_layout()
plt.show()
```

- Lines 5-6: Import the image data and convert data type to 16-bit integer.
- Lines 7-9: Make a numpy copy to be modified with the convolutional filter. 
- Line 11: Declare the filter. 
- Line 12: Set the weight to ensure the convolutional value is normalized (weighted) to an acceptable range. 
- Lines 14-32: The double nested loops iterate through all pixels (except for the edge) of the image and 
calculate the new value (the convolutional process). 

We display the original and new images next to one another to observe the impact of the filter (lines 33-39). 

You can try out another filter to highlight the vertical lines:

$$
\begin{bmatrix}
-1 & 0 & 1 \\
-2 & 0 & 2 \\
-1 & 0 & 1 
\end{bmatrix} 
$$

{% enddetails %}

{% details Example: manual pooling %}

- [Pooling layer](https://en.wikipedia.org/wiki/Pooling_layer) is a type of layer in neural network that downsamples and 
aggregates data to help removing redundant information. 
- Pooling is often used in conjunction with convolutional layer of CNN to help reducing the overall amount of information 
in an image, while maintaining the features that are detected as present.
  - This is important from the perspective of machine learning on embedded devices. 
- There are a number of different types of pooling (average, max, ...), but we will use max pooling:
  - Identify the cell (pixel) that has the highest value within the neighboring area. 

{% include figure.liquid path="assets/img/courses/csc574/06-convolutions/lab3-fig4.png" max-width="50%" zoomable=true %}

Run this next code in a cell and observe the outcome. This code will show (4, 4) pooling. 

```python
import numpy as np
from scipy import datasets
import matplotlib.pyplot as plt

i = datasets.ascent() 
i = i.astype(np.int16)
i_transformed = np.copy(i)
size_x = i_transformed.shape[0]
size_y = i_transformed.shape[1]

filter = [[-1, -2, -1], [0, 0, 0], [1, 2, 1]] 
weight = 1

for x in range(1,size_x-1):
  for y in range(1,size_y-1):
      convolution = 0.0
      convolution = convolution + ((i[x-1,y-1]) * filter[0][0])
      convolution = convolution + (i[x, y-1] * filter[1][0])
      convolution = convolution + (i[x + 1, y-1] * filter[2][0])
      convolution = convolution + (i[x-1, y] * filter[0][1])
      convolution = convolution + (i[x, y] * filter[1][1])
      convolution = convolution + (i[x+1, y] * filter[2][1])
      convolution = convolution + (i[x-1, y+1] * filter[0][2])
      convolution = convolution + (i[x, y+1] * filter[1][2])
      convolution = convolution + (i[x+1, y+1] * filter[2][2])
      convolution = convolution * weight
      if(convolution<0):
        convolution=0
      if(convolution>255):
        convolution=255
      i_transformed[x, y] = convolution

new_x = int(size_x/4)
new_y = int(size_y/4)
newImage = np.zeros((new_x, new_y))
for x in range(0, size_x, 4):
  for y in range(0, size_y, 4):
    pixels = []
    pixels.append(i_transformed[x, y])
    pixels.append(i_transformed[x+1, y])
    pixels.append(i_transformed[x+2, y])
    pixels.append(i_transformed[x+3, y])
    pixels.append(i_transformed[x, y+1])
    pixels.append(i_transformed[x+1, y+1])
    pixels.append(i_transformed[x+2, y+1])
    pixels.append(i_transformed[x+3, y+1])
    pixels.append(i_transformed[x, y+2])
    pixels.append(i_transformed[x+1, y+2])
    pixels.append(i_transformed[x+2, y+2])
    pixels.append(i_transformed[x+3, y+2])
    pixels.append(i_transformed[x, y+3])
    pixels.append(i_transformed[x+1, y+3])
    pixels.append(i_transformed[x+2, y+3])
    pixels.append(i_transformed[x+3, y+3])
    pixels.sort(reverse=True)
    newImage[int(x/4),int(y/4)] = pixels[0]

fig, axes = plt.subplots(1, 3, figsize=(12, 6))
axes[0].imshow(i, cmap='gray')
axes[0].set_title("Original Stairwell")
axes[1].imshow(i_transformed, cmap='gray')
axes[1].set_title("Stairwell with Convolution Applied")
axes[2].imshow(newImage, cmap='gray')
axes[2].set_title("Downsampled Image")
plt.tight_layout()
plt.show()
```

{% enddetails %}


## CNN in Tensorflow

{% details Implementation %}

```python
import tensorflow as tf
mnist = tf.keras.datasets.fashion_mnist
(training_images, training_labels), (val_images, val_labels) = mnist.load_data()
training_images=training_images.reshape(60000, 28, 28, 1)
training_images=training_images / 255.0
val_images=val_images.reshape(10000, 28, 28, 1)
val_images=val_images/255.0
model = tf.keras.models.Sequential([
  tf.keras.layers.Conv2D(64, (3,3), activation='relu', input_shape=(28, 28, 1)),
  tf.keras.layers.MaxPooling2D(2, 2),
  tf.keras.layers.Conv2D(64, (3,3), activation='relu'),
  tf.keras.layers.MaxPooling2D(2,2),
  tf.keras.layers.Flatten(),
  tf.keras.layers.Dense(20, activation='relu'),
  tf.keras.layers.Dense(10, activation='softmax')
])
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
model.summary()
model.fit(training_images, training_labels, validation_data=(val_images, val_labels), epochs=20)
```
{% enddetails %}

{% details Data maniplulation (3-7) %}

- We load data directly from datasets made available through the Tensorflow library. 
- The data has to be reshaped, unlike the original DNN. 
  - We do this step **after** we split data into training/validation. 
  - This step is neccessary because [Conv2D](https://www.tensorflow.org/api_docs/python/tf/keras/layers/Conv2D) expects input data as a ` a single spatial (or temporal) dimension to produce a tensor of outputs`/ 
  - Instead of 60,000 28x28x1 items in a list, `reshape` will produce a single 4D list that is *60,000x28x28x1*.

{% enddetails %}


{% details Model definition (8-16) %}

- `Conv2D` is the implementation of CNN for two dimensional images in TensorFlow as another possible layer to 
be added to the model  (Line 9).
  - `64` is the number of filters/convolutions we want to use in this layer. This is randomly selected but 
  should be in the order of 64. 
  - `(3,3)` is the size of each convolution, in this case a 3x3 grid
  - The activation function to use, `relu` in this case (returning x when x is posistive, else returning 0)
  - `(28,28,1)` is the shape of the input data (for each image). 
- `MaxPooling2D` is designed to compress the image, while maintaining the content of the features that were 
highlighted by the convolution (Line 10).  
- These two layer types are added one more time (Lines 11 and 12)
- After these two layers, the outputs are flattened (Line 13). 
- The remaining two layers are similar to the original DNN structure (Lines 14 and 15).
- You can call model.summary() to see the size and shape of the network, and you'll notice that after every MaxPooling layer, the image size is reduced in this way.
{% enddetails %}

- Line 17: The model is compiled with optimizer and loss functions specified. 
- Line 18: We can view the summarized version of the model. 
- Line 19: The model is trained. 
- Running the above code will show that:
  - At the final epoch (20), the performance is 
    - accuracy: 0.9659 
    - loss: 0.0901 
    - val_accuracy: 0.9065 
    - val_loss: 0.3361
  - While individual epoch for CNN takes longer than DNN (7ms versus 1ms in my case), CNN performance surpassed DNN performance only after 4 epochs. 

## Visualizing CNN

More technical details about CNN can be found at [Visualizing and Understanding Convolutional Networks]( https://arxiv.org/pdf/1311.2901)

```python
import matplotlib.pyplot as plt
import tensorflow as tf

fig, axarr = plt.subplots(3, 3, figsize=(10, 10))

LABEL = 9
CONVOLUTION_NUMBER = 1

# Get the first three unique image indices matching the label
image_nine = [i for i in range(len(val_labels)) if val_labels[i] == LABEL]
selected_images = [image_nine[0], image_nine[1], image_nine[2]]

# Create the activation extraction model
layer_outputs = [layer.output for layer in model.layers]
activation_model = tf.keras.models.Model(inputs=model.inputs, outputs=layer_outputs)

for row_idx, img_idx in enumerate(selected_images):
    input_img = val_images[img_idx].reshape(1, 28, 28, 1)
    activations = activation_model.predict(input_img)

    # Column 0: Original Image (28x28)
    axarr[row_idx, 0].imshow(val_images[img_idx].reshape(28, 28), cmap='gray')
    
    # Column 1: Layer 0 (Conv2D - 26x26)
    f1 = activations[0]
    axarr[row_idx, 1].imshow(f1[0, :, :, CONVOLUTION_NUMBER], cmap='inferno')
    
    # Column 2: Layer 1 (MaxPooling2D - 13x13)
    f2 = activations[1]
    axarr[row_idx, 2].imshow(f2[0, :, :, CONVOLUTION_NUMBER], cmap='inferno')

    for col_idx in range(3):
        axarr[row_idx, col_idx].set_xlim(0, 28)
        axarr[row_idx, col_idx].set_ylim(28, 0)  # Flipped to keep image right-side up
        axarr[row_idx, col_idx].grid(False)
plt.tight_layout()
plt.show()
```

- Lines 10 and 11: First three images from the validation set that have the same label `LABEL` are selected. 
- Line 14 and 15: An activation model is created with the parameters from just the layers of the model. 
- Loop in line 17: For each row of the graph
  - The original image is displayed (line 22)
  - The image created from the output from the first convolutional layer is displayed (lines 25 and 26)
  - The image craeted from the output from the second max pooling layer is displayed (lines 29 and 30). 

