---
layout: lecture
pretty_table: true
title: Working with Image Data

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
  - name: Real Image Data
  - name: Horse or Human Classifier
  - name: Image Data Generators
  - name: Training and Prediction
  - name: Visualizing Model Layers
  - name: "Overfitting, Augmentation, and Dropout"
  - name: Bean Disease Classifier
---

## Overview

- In the previous lecture, we used convolutional neural networks (CNNs) with small, cleaned, built-in image datasets.
- Those datasets are useful because they remove many practical problems:
  - The images are already the same size.
  - The labels are already encoded as numbers.
  - The objects are usually centered.
  - The data is already split into training and validation sets.
- Real image projects are messier. 
- In this lecture, we move from built-in image arrays to real image folders.
- The main goal is to understand how TensorFlow can read image files from directories, convert them into batches, and feed them into a CNN.

## Real Image Data

{% details From cleaned datasets to realistic images %}

- Built-in image datasets are usually loaded directly as NumPy arrays.
- Realistic image datasets are often stored as image files on disk.
- Real image data may include:
  - Larger images
  - Color images with three channels: red, green, and blue
  - Different object poses
  - Background objects
  - Lighting differences
  - Images where the subject is not centered
- These differences matter because the model does not see a horse, a person, a leaf, or a disease. It sees arrays of pixel values.
- A CNN can learn useful patterns from those arrays, but only if the data is organized and processed consistently.

{% enddetails %}

{% details Directory-based labels %}

TensorFlow can infer labels from a directory structure. For example, a binary image dataset can be organized like this:

```text
data/
  horse-or-human/
    horses/
      horse01.png
      horse02.png
    humans/
      human01.png
      human02.png
  validation-horse-or-human/
    horses/
      horse01.png
      horse02.png
    humans/
      human01.png
      human02.png
```

- Each subdirectory name becomes a class label.
    - Images inside `horses/` are labeled as horses.
    - Images inside `humans/` are labeled as humans.
- The same structure is used for both training and validation data.

{% enddetails %}

## Horse or Human Classifier

We will use the [Horses or Humans dataset](https://laurencemoroney.com/datasets.html#horses-or-humans-dataset). This dataset contains color images of horses and humans in different poses and backgrounds.

{% details Data acquisition %}

- Use the `data` directory inside the main `tinyml` directory. The contents in here are gitignored 
so that it will not accidentally be uploaded if you decide to fork `tinyml`. 
- Download the training and validation zip files and unzip them inside these directories. 
    - [Training data](https://storage.googleapis.com/learning-datasets/horse-or-human.zip)
    - [Validation data](https://storage.googleapis.com/learning-datasets/validation-horse-or-human.zip)

{% include figure.liquid path="assets/img/courses/csc574/07-working-images/data-horses-humans.png" max-width="25%" zoomable=true %}

The following code segment in the `working-image.ipynb` notebook inside `python/notebooks/` will 
automatically extract the data

```python
import os
import zipfile

data_path = "../../data/"

with zipfile.ZipFile(os.path.join(data_path, "horse-or-human.zip"), "r") as zip_ref:
    zip_ref.extractall(os.path.join(data_path, "horse-or-human"))

with zipfile.ZipFile(os.path.join(data_path, "validation-horse-or-human.zip"), "r") as zip_ref:
    zip_ref.extractall(os.path.join(data_path, "validation-horse-or-human"))
```

We can confirm the existence of data in the next cell

```python
train_horse_dir = os.path.join(data_path,"horse-or-human/horses")
train_human_dir = os.path.join(data_path,"horse-or-human/humans")
validation_horse_dir = os.path.join(data_path,"validation-horse-or-human/horses")
validation_human_dir = os.path.join(data_path,"validation-horse-or-human/humans")

train_horse_names = os.listdir(train_horse_dir)
train_human_names = os.listdir(train_human_dir)
validation_horse_names = os.listdir(validation_horse_dir)
validation_human_names = os.listdir(validation_human_dir)

print("Training horse images:", train_horse_names[:10])
print("Training human images:", train_human_names[:10])
print("Validation horse images:", validation_horse_names[:10])
print("Validation human images:", validation_human_names[:10])
```

{% enddetails %}

{% details Define the CNN model %}

The model below is a CNN for binary image classification. It accepts `100x100` RGB images.

```python
import tensorflow as tf

model = tf.keras.models.Sequential([
    # The input shape is 100x100 pixels with 3 color channels.
    tf.keras.Input(shape=(100, 100, 3)),

    # First convolution block
    tf.keras.layers.Conv2D(32, (3, 3), activation="relu"),
    tf.keras.layers.MaxPooling2D(2, 2),

    # Second convolution block
    tf.keras.layers.Conv2D(64, (3, 3), activation="relu"),
    tf.keras.layers.MaxPooling2D(2, 2),

    # Third convolution block
    tf.keras.layers.Conv2D(128, (3, 3), activation="relu"),
    tf.keras.layers.MaxPooling2D(2, 2),

    # Fourth convolution block
    tf.keras.layers.Conv2D(256, (3, 3), activation="relu"),
    tf.keras.layers.MaxPooling2D(2, 2),

    # Flatten the feature maps before using dense layers.
    tf.keras.layers.Flatten(),

    # Dense classification layers
    tf.keras.layers.Dense(512, activation="relu"),
    tf.keras.layers.Dense(256, activation="relu"),

    # One output neuron for binary classification.
    # Values closer to 0 represent one class; values closer to 1 represent the other.
    tf.keras.layers.Dense(1, activation="sigmoid")
])

model.summary()
```

- `Conv2D` layers learn image features.
- `MaxPooling2D` layers reduce the width and height of the feature maps.
- `Flatten` converts the final feature maps into a vector.
- Dense layers use the extracted features to classify the image.
- The final `sigmoid` output is appropriate for binary classification.

{% enddetails %}

{% details Compile the model %}

```python
from tensorflow.keras.optimizers import RMSprop

optimizer = RMSprop(learning_rate=0.0001)

model.compile(
    loss="binary_crossentropy",
    optimizer=optimizer,
    metrics=["acc"]
)
```

- `binary_crossentropy` is used because this is a two-class problem.
- `RMSprop` is one possible optimizer.
- The learning rate is set to `0.0001` to make updates smaller and more stable.

{% enddetails %}

## Image Data Generators

{% details Why use an image data generator? %}

An image data generator solves a practical problem: the model needs tensors, but our data is stored as image files in folders.

`ImageDataGenerator` can:

- Read images from directories.
- Resize images to a common shape.
- Convert images into batches.
- Normalize pixel values.
- Infer class labels from subdirectory names.
- Optionally apply data augmentation.

In this example, each image is resized to `100x100`, and pixel values are rescaled from the range `0-255` to the range `0-1`.

{% enddetails %}

{% details Build the training and validation generators %}

```python
from tensorflow.keras.preprocessing.image import ImageDataGenerator

# All images will be augmented according to whichever lines are uncommented
# below. We can first try without any of the augmentation beyond the rescaling
train_datagen = ImageDataGenerator(
      rescale=1./255,
      #rotation_range=40,
      #width_shift_range=0.2,
      #height_shift_range=0.2,
      #shear_range=0.2,
      #zoom_range=0.2,
      #horizontal_flip=True,
      #fill_mode='nearest'
      )

# Flow training images in batches of 128 using train_datagen generator
train_generator = train_datagen.flow_from_directory(
        os.path.join(data_path, "horse-or-human"),  # This is the source directory for training images
        target_size=(100, 100),  # All images will be resized to 100x100
        batch_size=128,
        # Since we use binary_crossentropy loss, we need binary labels
        class_mode='binary')

validation_datagen = ImageDataGenerator(rescale=1./255)

validation_generator = validation_datagen.flow_from_directory(
        os.path.join(data_path, "validation-horse-or-human"),
        target_size=(100, 100),
        class_mode='binary')
```

- `rescale=1.0 / 255` normalizes pixel values.
- `target_size=(100, 100)` resizes every image.
- `batch_size=128` controls how many images are passed through the model at a time.
- `class_mode="binary"` tells TensorFlow that there are two classes.

{% enddetails %}

## Training and Prediction

{% details Train the model %}

Training this model may take a little while because we are now using a larger CNN and real image files.

```python
history = model.fit(
    train_generator,
    steps_per_epoch=8,
    epochs=100,
    verbose=1,
    validation_data=validation_generator
)
```

- `steps_per_epoch=8` means each epoch uses 8 batches from the generator.
- `epochs=100` trains for 100 passes through the configured training steps.
- The validation generator is used to estimate how well the model performs on data it did not train on.

{% enddetails %}

{% details Plot training history %}

```python
import matplotlib.pyplot as plt

plt.plot(history.history["acc"])
plt.plot(history.history["val_acc"])
plt.title("Model Accuracy")
plt.ylabel("Accuracy")
plt.xlabel("Epoch")
plt.legend(["train", "validation"], loc="upper left")
plt.show()
```

If the training accuracy keeps improving while validation accuracy stalls or drops, that is a warning sign for overfitting.

{% enddetails %}

{% details Run predictions on new images %}

The following code downloads several images and asks the model to classify them.

```python
import numpy as np
from io import BytesIO
import urllib.request
from tensorflow.keras import utils
from IPython.display import Image, display

base_url = "https://www.cs.wcupa.edu/LNGO/data/horse-human-confuse/"
file_list = ["a-horse.jpg", "horse-jockey.jpg", "horse-hindleg.jpg", "two-man.jpg"]

for image_name in file_list:
    image_url = base_url + image_name
    print(image_url)

    with urllib.request.urlopen(image_url) as response:
        img = utils.load_img(BytesIO(response.read()), target_size=(100, 100))

    display(Image(url=image_url))

    x = utils.img_to_array(img)
    x = x / 255.0
    x = np.expand_dims(x, axis=0)

    prediction = model.predict(x)
    print("Raw prediction:", prediction)

    if prediction[0] > 0.5:
        print("Prediction: human")
    else:
        print("Prediction: horse")
```

- A prediction close to `0` means the model leans toward one class.
- A prediction close to `1` means the model leans toward the other class.
- The threshold `0.5` is a simple decision boundary.
- Some images may confuse the model. That is useful because failure cases reveal what the model actually learned.

{% enddetails %}

## Visualizing Model Layers

{% details Why visualize intermediate layers? %}

A CNN does not jump directly from pixels to a final class label. Each convolution and pooling layer transforms the image into new feature maps.

Visualizing these feature maps can help us ask:

- What features are being emphasized?
- Are early layers detecting edges and textures?
- Are later layers becoming more abstract?
- Why might a confusing image be misclassified?

{% enddetails %}

{% details Visualize feature maps %}

```python
import matplotlib.pyplot as plt
import numpy as np
import random
from tensorflow.keras.preprocessing.image import img_to_array, load_img

%matplotlib inline

# Create a model that returns intermediate outputs from the trained model.
successive_outputs = [layer.output for layer in model.layers[1:]]
visualization_model = tf.keras.models.Model(
    inputs=model.inputs,
    outputs=successive_outputs
)

# Prepare a random input image from the training set.
horse_img_files = [os.path.join(train_horse_dir, f) for f in train_horse_names]
human_img_files = [os.path.join(train_human_dir, f) for f in train_human_names]
img_path = random.choice(horse_img_files + human_img_files)

# Uncomment this line to pick the first human image manually.
# img_path = human_img_files[0]

img = load_img(img_path, target_size=(100, 100))
x = img_to_array(img)
x = x.reshape((1,) + x.shape)
x = x / 255.0

successive_feature_maps = visualization_model.predict(x)
layer_names = [layer.name for layer in model.layers]

for layer_name, feature_map in zip(layer_names, successive_feature_maps):
    if len(feature_map.shape) == 4:
        # Only visualize convolution and pooling layers.
        n_features = feature_map.shape[-1]
        n_features = min(n_features, 5)
        size = feature_map.shape[1]

        display_grid = np.zeros((size, size * n_features))

        for i in range(n_features):
            feature = feature_map[0, :, :, i]
            feature -= feature.mean()
            feature /= feature.std() + 1e-8
            feature *= 64
            feature += 128
            feature = np.clip(feature, 0, 255).astype("uint8")
            display_grid[:, i * size : (i + 1) * size] = feature

        scale = 20.0 / n_features
        plt.figure(figsize=(scale * n_features, scale))
        plt.title(layer_name)
        plt.grid(False)
        plt.imshow(display_grid, aspect="auto", cmap="viridis")
        plt.show()
```

- The visualization model reuses the trained layers.
- Instead of returning only the final prediction, it returns outputs from intermediate layers.
- We limit each layer to five feature maps so the plot remains readable.
- The small `1e-8` value avoids division by zero when normalizing a flat feature map.

{% enddetails %}

{% details Exercise: confusing images %}

Rework the visualization code so that it visualizes the intermediate layers for the confusing images used during prediction.

Questions to answer:

- Which images are classified incorrectly?
- What visual patterns appear strongly in the early convolution layers?
- Do the confusing images contain features from both classes?
- Does the model appear to focus on the subject, the background, or both?

{% enddetails %}

## Overfitting, Augmentation, and Dropout

{% details Overfitting %}

Overfitting happens when a model becomes too specialized to the training data.

For image models, this can happen when the training images are too consistent. For example:

- If every cat image is upright, the model may associate upright ears with cats.
- If every horse image has a similar background, the model may learn the background instead of the horse.
- If the subject is always centered, the model may fail when the subject is shifted.

A model can have high training accuracy but poor validation accuracy. That is often a sign that the model is memorizing training patterns rather than learning more general features.

{% enddetails %}

{% details Data augmentation %}

Data augmentation creates modified versions of training images during training.

Common augmentation options include:

- Random rotations
- Width and height shifts
- Shearing
- Zooming
- Horizontal flipping
- Pixel filling after transformations

```python
train_datagen = ImageDataGenerator(
    rescale=1.0 / 255,
    rotation_range=40,
    width_shift_range=0.2,
    height_shift_range=0.2,
    shear_range=0.2,
    zoom_range=0.2,
    horizontal_flip=True,
    fill_mode="nearest"
)
```

- Augmentation can help the model generalize.
- Augmentation can also slow down training.
- More augmentation is not always better. If the transformation creates unrealistic examples, the model may learn noise.

{% enddetails %}

{% details Exercise: augmentation %}

Uncomment the augmentation settings in the training `ImageDataGenerator`.

Questions to answer:

- Does augmentation improve validation accuracy?
- Does augmentation improve predictions on the confusing images?
- What do the intermediate feature maps look like after augmentation?
- Does the model become more robust, or does training simply become slower?

{% enddetails %}

{% details Dropout regularization %}

Dropout is another technique for reducing overfitting.

During training, dropout randomly disables a percentage of neuron outputs. This reduces the chance that the model becomes too dependent on a small number of highly specialized neurons.

```python
tf.keras.layers.Dropout(0.2)
```

The value `0.2` means that 20% of the outputs from that layer are dropped during training.

Example:

```python
model = tf.keras.models.Sequential([
    tf.keras.layers.Flatten(input_shape=(28, 28)),
    tf.keras.layers.Dense(256, activation=tf.nn.relu),
    tf.keras.layers.Dropout(0.2),
    tf.keras.layers.Dense(128, activation=tf.nn.relu),
    tf.keras.layers.Dropout(0.2),
    tf.keras.layers.Dense(64, activation=tf.nn.relu),
    tf.keras.layers.Dropout(0.2),
    tf.keras.layers.Dense(10, activation=tf.nn.softmax)
])
```

- Dropout is applied during training.
- During prediction, the full network is used.
- The dropout value is a hyperparameter that should be tested.
- If training accuracy is much higher than validation accuracy, dropout may help.

Reference: [Nitish Srivastava et al. Dropout: A Simple Way to Prevent Neural Networks from Overfitting, 2014](https://www.cs.toronto.edu/~hinton/absps/JMLRdropout.pdf)

{% enddetails %}

{% details Optimizers and loss functions %}

TensorFlow provides many optimizer and loss function options:

- [Optimizers](https://www.tensorflow.org/api_docs/python/tf/keras/optimizers)
- [Loss functions](https://www.tensorflow.org/api_docs/python/tf/keras/losses)

The important habit is to match the final layer, loss function, and label format.

| Problem type | Final layer | Common loss | Label format |
|---|---|---|---|
| Binary classification | `Dense(1, activation="sigmoid")` | `binary_crossentropy` | `0` or `1` |
| Multi-class classification with integer labels | `Dense(num_classes, activation="softmax")` | `sparse_categorical_crossentropy` | `0`, `1`, `2`, ... |
| Multi-class classification with one-hot labels | `Dense(num_classes, activation="softmax")` | `categorical_crossentropy` | `[1,0,0]`, `[0,1,0]`, ... |

{% enddetails %}

## Bean Disease Classifier

In this activity, students adapt the image-classification workflow to a new dataset: bean leaf disease classification.

The dataset contains `224x224` color images of bean plants from Uganda. The goal is to classify leaves into three categories:

- Healthy
- Bean rust
- Angular leaf spot

Data downloads:

- [Training data](https://storage.googleapis.com/learning-datasets/beans/train.zip)
- [Validation data](https://storage.googleapis.com/learning-datasets/beans/validation.zip)
- [Test data](https://storage.googleapis.com/learning-datasets/beans/test.zip)

{% details Starter code: data generators %}

Fill in the missing values. The hint from the notebook still applies: we do not want abnormal data, so the first preprocessing step should normalize pixel values.

```python
from tensorflow.keras.preprocessing.image import ImageDataGenerator

train_datagen = ImageDataGenerator(
    # YOUR CODE HERE
)

validation_datagen = ImageDataGenerator(
    # YOUR CODE HERE
)

TRAIN_DIRECTORY_LOCATION = None  # YOUR CODE HERE
VAL_DIRECTORY_LOCATION = None  # YOUR CODE HERE
TARGET_SIZE = None  # YOUR CODE HERE
CLASS_MODE = None  # YOUR CODE HERE

train_generator = train_datagen.flow_from_directory(
    TRAIN_DIRECTORY_LOCATION,
    target_size=TARGET_SIZE,
    batch_size=128,
    class_mode=CLASS_MODE
)

validation_generator = validation_datagen.flow_from_directory(
    VAL_DIRECTORY_LOCATION,
    target_size=TARGET_SIZE,
    batch_size=128,
    class_mode=CLASS_MODE
)
```

{% enddetails %}

{% details One reasonable data-generator solution %}

Because this is a three-class classification problem, use `class_mode="categorical"` and `categorical_crossentropy` later.

```python
from tensorflow.keras.preprocessing.image import ImageDataGenerator

train_datagen = ImageDataGenerator(rescale=1.0 / 255)
validation_datagen = ImageDataGenerator(rescale=1.0 / 255)

TRAIN_DIRECTORY_LOCATION = 
VAL_DIRECTORY_LOCATION = 
TARGET_SIZE = (224, 224)
CLASS_MODE = "categorical"

train_generator = train_datagen.flow_from_directory(
    TRAIN_DIRECTORY_LOCATION,
    target_size=TARGET_SIZE,
    batch_size=128,
    class_mode=CLASS_MODE
)

validation_generator = validation_datagen.flow_from_directory(
    VAL_DIRECTORY_LOCATION,
    target_size=TARGET_SIZE,
    batch_size=128,
    class_mode=CLASS_MODE
)
```

{% enddetails %}

{% details Starter code: model %}

Define a CNN that can learn higher-level image features and then classify the three bean leaf categories.

```python
import tensorflow as tf

model = tf.keras.models.Sequential([
    # YOUR CODE HERE
])

model.summary()
```

{% enddetails %}

{% details One reasonable model solution %}

This is not the only correct answer. It is a reasonable starting point.

```python
import tensorflow as tf

model = tf.keras.models.Sequential([
    tf.keras.Input(shape=(224, 224, 3)),

    tf.keras.layers.Conv2D(32, (3, 3), activation="relu"),
    tf.keras.layers.MaxPooling2D(2, 2),

    tf.keras.layers.Conv2D(64, (3, 3), activation="relu"),
    tf.keras.layers.MaxPooling2D(2, 2),

    tf.keras.layers.Conv2D(128, (3, 3), activation="relu"),
    tf.keras.layers.MaxPooling2D(2, 2),

    tf.keras.layers.Conv2D(128, (3, 3), activation="relu"),
    tf.keras.layers.MaxPooling2D(2, 2),

    tf.keras.layers.Flatten(),
    tf.keras.layers.Dense(256, activation="relu"),
    tf.keras.layers.Dropout(0.2),
    tf.keras.layers.Dense(3, activation="softmax")
])

model.summary()
```

- The input shape is `224x224x3` because the bean images are color images.
- The final layer has three outputs because there are three classes.
- The final activation is `softmax` because this is multi-class classification.

{% enddetails %}

{% details Starter code: compile %}

```python
LOSS_FUNCTION = None  # YOUR CODE HERE
OPTIMIZER = None  # YOUR CODE HERE

model.compile(
    loss=LOSS_FUNCTION,
    optimizer=OPTIMIZER,
    metrics=["accuracy"]
)
```

{% enddetails %}

{% details One reasonable compile solution %}

```python
LOSS_FUNCTION = "categorical_crossentropy"
OPTIMIZER = tf.keras.optimizers.Adam(learning_rate=0.0001)

model.compile(
    loss=LOSS_FUNCTION,
    optimizer=OPTIMIZER,
    metrics=["accuracy"]
)
```

- `categorical_crossentropy` matches one-hot class labels from `class_mode="categorical"`.
- `Adam` is a common optimizer for CNNs.
- The learning rate is deliberately modest.

{% enddetails %}

{% details Train the bean classifier %}

```python
NUM_EPOCHS = 20

history = model.fit(
    train_generator,
    epochs=NUM_EPOCHS,
    verbose=1,
    validation_data=validation_generator
)
```

{% enddetails %}

{% details Plot accuracy %}

```python
import matplotlib.pyplot as plt

plt.plot(history.history["accuracy"])
plt.plot(history.history["val_accuracy"])
plt.title("Model Accuracy")
plt.ylabel("Accuracy")
plt.xlabel("Epoch")
plt.legend(["train", "validation"], loc="upper left")
plt.xlim([0, NUM_EPOCHS])
plt.ylim([0.4, 1.0])
plt.show()
```

Questions to answer:

- Does training accuracy improve steadily?
- Does validation accuracy improve with training accuracy?
- Is there evidence of overfitting?
- Would augmentation or dropout likely help?

{% enddetails %}

{% details Extension: evaluate with the test set %}

The original hands-on notebook includes a test data link. A responsible workflow should avoid using the test set while choosing model architecture and hyperparameters. Once the model is selected, use the test set for a final evaluation.

```python
test_datagen = ImageDataGenerator(rescale=1.0 / 255)

TEST_DIRECTORY_LOCATION = 

# For final evaluation, do not shuffle the test set.
test_generator = test_datagen.flow_from_directory(
    TEST_DIRECTORY_LOCATION,
    target_size=(224, 224),
    batch_size=128,
    class_mode="categorical",
    shuffle=False
)

test_loss, test_accuracy = model.evaluate(test_generator)
print("Test loss:", test_loss)
print("Test accuracy:", test_accuracy)
```

- Training set: used to learn model weights.
- Validation set: used to tune decisions during development.
- Test set: used at the end for a less-biased estimate of final performance.

{% enddetails %}

{% details Reflection questions %}

- What changed when moving from `horse-or-human` to `beans`?
- Which parts of the code stayed almost the same?
- Why did the final layer change from `Dense(1, activation="sigmoid")` to `Dense(3, activation="softmax")`?
- Why did the loss function change?
- What would be different if we wanted to deploy this model to a small embedded device?

{% enddetails %}
