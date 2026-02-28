---
layout: lecture
pretty_table: true
collection: csc574
title: "Visual Wake Word (VWW)"
toc:
  - name: Overview
  - name: Challenges
  - name: VWW Model
  - name: Hands-on notebook
---
# Visual Wake Word (VWW)

## Overview

{% details note Motivating examples of use cases %}

- Common image recognition examples
    - Ring door bell
        - Detect when someone shows up at the door, or
        - Recognize whether a specific person is at the door. 
    - Facial recognition on iPhone/iPad/Surface
- Can we untether the device?
    - Small power/computation consumptions, no wiring necessary
    - No construction licensing/permit needed for deployment. 
    - Example: 
        - Recognize whether there are no people in the room in order to 
        turn off the lights. to deploy a TinyML device in an office which
        - Smart glasses that can process the interesting visual cues that are coming
        in (catching rare items when shopping, noticing hard-to-detect road signs, ...) 

{% enddetails %}
{% details note Challenges %}

- Performance-related aspects: 
    - Latency 
    - Bandwidth.
- Capabilities:
    - Accuracy
    - Personalization
- Data security and privacy
- Resource constrains

{% include figure.liquid path="assets/img/courses/csc574/vww/challenges.png" width="50%" zoomable=true %}


{% enddetails %}
## Challenges

{% details note Bandwidth and Latency %}

- In a cascading architecture, a tinyML device can perform 
the initial `interesting item` detection, then offload the subsequently 
more compute intenstive task to the cloud if an `interesting item` is detected. 

{% details Example: Is there a cat knocking on my door? %}

- How much data are we sending?
    - An image in neural networks is around 224 by 224, sometimes 300 by 300 pixels.
    - Three channels (R, B, G) per pixel. 
    - Each channel requires 4 bytes for representation. 

{% include figure.liquid path="assets/img/courses/csc574/vww/cat.png" width="50%" zoomable=true %}

- How long does it takes?
    - Ping: 25ms (the latency just to be able to send something to the local 
    gateway and be able to get a response back)
    - Download speed: 35 megabits per second.
    - Upload speed: 4.62 megabits per second ~ `570 KBytes per second`
    - Image size: 602,000 bytes of data ~ `602 Kbytes`
    - Take one second!

- Actual performance

{% include figure.liquid path="assets/img/courses/csc574/vww/checkcat.png" width="50%" zoomable=true %}

- The cat could be gone!!!!
- Comparing to keyword spotting
    - KWW is at least two order of magnitudes smaller

{% include figure.liquid path="assets/img/courses/csc574/vww/kws-vww.png" width="50%" zoomable=true %}

- Audio signal produces significantly more data than audio signal.
    - Higher latency
    - Higher power consumption
    - Lower user satisfaction

{% enddetails %}
{% enddetails %}
{% details note Capability constraints %}

- What if we don't go to the cloud (no more latency and bandwidth issue!!!)

{% include figure.liquid path="assets/img/courses/csc574/vww/local.png" width="50%" zoomable=true %}

- Constraints:
    - Microcontroller = processing latency (need smaller models)
    - Microcontroller = memory limits (need smaller models) 
- How do these constraints impact performance:
    - False positive
    - False negative

{% enddetails %}
{% details note Data collection and processing %}

- Be very careful with collecting images
    - This means anyone else cannot use this data to build the AI model as well. 

{% include figure.liquid path="assets/img/courses/csc574/vww/nonono.png" width="50%" zoomable=true %}

- If data is clean/legal/valid, it is possible to reuse existing data to 
generate a subset of specific training data. 

{% details Example: Visual Wake Words Dataset %}

- [Google Research's Paper: Visual Wake Words Dataset](https://arxiv.org/pdf/1906.05721)
- Relabeling instances of [COCO dataset](https://cocodataset.org/#explore)
    - "Each image is assigned a label 1 or 0. The label 1 is assigned 
    as long as it has at least one bounding box corresponding to the 
    object of interest (e.g. person) with the box area greater than 
    0.5% of the image area."
    - `Person`: 1
    - `Not-person`: 0

    {% include figure.liquid path="assets/img/courses/csc574/vww/vww_datasets.png" width="50%" zoomable=true %}

- Somewhat similar to KWS, but you don't have to create datasets from scratch!!!

{% enddetails %}
- Powerful concept, as long as data usage license is permissive!!!
- Is that data set really going to meet the needs of your particular 
TinyML application?
    - Balanced
    - Relevant
    - Quality
    - Quantity

{% enddetails %}
## VWW Model

{% details note Recall: constraints and trade-offs %}


{% include figure.liquid path="assets/img/courses/csc574/vww/model_evolution.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Recall: convolutions %}


{% include figure.liquid path="assets/img/courses/csc574/vww/convolutions1.png" width="50%" zoomable=true %}

- Convolutions on gray-scale pictures

{% include figure.liquid path="assets/img/courses/csc574/vww/convo-1channel.png" width="50%" zoomable=true %}

- Convolutions on colored images
    - Depthwise
    - Input Feature Map: 8x8x3 (widthxheightxchannels)
    - Kernel: 3x3x3 (each channel uses 1 filter)
    - Final output: 7x7x1 tensor
- Math generalization
    - $D_F$ : dimension of a square input feature map
    - M: number of input channel
    - $D_K$ : dimension of filter matrix (square)
    - N: number of output channel
    - Total number of multiplication: ${D_K}^2 * M * {D_F}^2 * N$ (a lot!!!)

{% include figure.liquid path="assets/img/courses/csc574/vww/convo-3channels.png" width="50%" zoomable=true %}

- Depthwise separable convolutions
    - [MobileNets: Efficient Convolutional Neural Networks for Mobile Vision Application](https://arxiv.org/pdf/1704.04861)
    - Run time: $M * {D_K}^2 * ({D_F}^2 + N)$
    - The more filters we use and the larger the kernels are, more multiplications we can save.
        - Far fewer parameters to store. 

    {% include figure.liquid path="assets/img/courses/csc574/vww/dsc-3channels.png" width="50%" zoomable=true %}

- Performance tradeoff
    - Depth multiplier to reduce model size further: $\alpha * M * {D_K}^2 * ({D_F}^2 + N)$

{% include figure.liquid path="assets/img/courses/csc574/vww/mac.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Training model %}


- Training from scratch is expensive. 

{% details note Neural network of a model %}

{% include figure.liquid path="assets/img/courses/csc574/vww/training1.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Neural network of a model: earlier layers %}

{% include figure.liquid path="assets/img/courses/csc574/vww/training2.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Neural network of a model: latter layers %}

{% include figure.liquid path="assets/img/courses/csc574/vww/training3.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Conclusion %}

- Reuse (freeze general feature extraction)
- Train only last few layers for task-specific features

{% include figure.liquid path="assets/img/courses/csc574/vww/training4.png" width="50%" zoomable=true %}

{% enddetails %}
- [A comprehensive survey on transfer learning](https://arxiv.org/pdf/1911.02685)

{% enddetails %}
## Hands-on notebook

- Make a copy of the following notebook [Visual Wake Word](https://colab.research.google.com/drive/1R-id7WlDFlEca7mox4Ftbllb4y0al9Ex?usp=sharing) by going to File/Save a copy in Drive. 


