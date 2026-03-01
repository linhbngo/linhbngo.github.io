---
layout: lecture
pretty_table: true
title: Introduction to tinyML
toc:
  - name: Overview
  - name: Why tinyML?
  - name: Enable tinyML
  - name: Challenges of tinyML
  - name: Course Hardware
---

## Overview


{% details info Embedded Systems %}

- Small, or tiny, 
- Low power, extremely low power.
- Can run for days, weeks, months, sometimes even years on tiny battery (cell).
- tinyML: Machine learning on embedded systems

{% enddetails %}

{% details info Machine Learning %}

- is a subfield of artificial intelligence, 
- uses a lot of data infer interesting patterns about new data

{% enddetails %}

{% details success tinyML %}

- is at the intersection of embedded systems and machine learning
- is a fast-growing field of machine learning technologies and applications that 
include algorithms, hardware, and software that 
are capable of performing on-device sensor data analytics at extremely low power, typically in the order of milliwatts,
- enables always-on machine learning use cases on battery-powered devices.

{% enddetails %}


{% details Examples of tinyML applications %}

- Siri, Alexa, Google?
    - Still requires wall power/big battery
- Smart drones
    - video surveillance 
    - go where humans cannot go
- Smart sensors on mobile robots
    - healthcare
- Smart glasses
    - Smart guidance

{% enddetails %}

{% details note Course Structure %}

- Based on Harvard's tinyML course
- Part 1: Machine Learning
- Part 2: Typical applications of tinyML
- Part 3: Physical deployment of tinyML

{% enddetails %}


## Why tinyML?

{% details note Machine Learning %}

- ML is a subfield of artificial intelligence that's focused on developing algorithms that 
can learn to solve problems by analyzing data for interesting patterns.
- DL is a type of ML that leverages neural networks and big data.

{% include figure.liquid path="assets/img/courses/csc574/01-introduction/ai_ml_dl.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note ML applications %}

- ML is embedded in all aspects of (digital) life nowadays. 
- Subfields of ML
    - Image classification: what is it
    - Object detection: where is it
    - Segmentation: where are these different things?
    - Machine translation
- Most of these applications of traditional ML require massive amount of 
computational power to train/inference: giant data centers

{% enddetails %}
{% details note Is bigger better? %}

- Problems!
    - Lacks interactivity.
    - Dependent on additional resources: power, network bandwidth, memory, computation power ...
- Numerous tiny devices instead of single massive center for large devices. 
    - Pervasive nowadays
    - On all the time
    - Collect **lots** of data
    - What if all of them are also smart and can analyze these data in-place?

{% enddetails %}
{% details tip Exercise %}

- What kinds of new TinyML applications do you wish existed today?
- What existing applications do you think could be improved by TinyML?
- What applications that others have posted about are you excited about?

{% enddetails %}
## Enable tinyML

{% details Example: OK, Google %}


{% include figure.liquid path="assets/img/courses/csc574/01-introduction/ok_google.jpg" width="50%" zoomable=true %}

- Google Assistant: Machine Learning
- HomiSmart: Physical device
- User says `OK Google` and the machine responds with `How can I help`

{% details info Step 1 %}

- Audio input from user' spoken voice.
- Picked up by device

{% enddetails %}
{% details info Step 2 %}

- Audio input is processed
- Did you say "Ok Google", "Alex", "Siri", or did you simply sneezed?

{% enddetails %}
{% details info Step 3 %}

- Device generates output responses


{% enddetails %}
{% enddetails %}

{% details note Step 1: data input %}

- Coming from sensors on device
    - Motion sensors,
    - Acoustic sensors,
    - Environmental sensors,
    - Biometric sensors,
    - Image sensors.
    - Force sensors, lots and lots of different kinds of sensors.

{% enddetails %}

{% details note Step 2: Data processing %}

- Typically require `big` processors.
- What about MCU (Micro-controller units) type of processors?

=== "Dimension"

    - CPU/GPU: $561\ {mm}^2$
    - Mobile (Apple 0778 Apple Watch): $33\ {mm}^2$
    - Kinetis KL03: $3.2\ {mm}^2$

    {% include figure.liquid path="assets/img/courses/csc574/01-introduction/kinetis.jpg" width="50%" zoomable=true %}

=== "Power consumption"

    - NVIDIA Tesla K80: 300W
    - Apple A12: 3.64W
    - Syntiant NDP100: **140 microW** (Always-on deep learning speech/audio recognition)

=== "Demand"

    {% include figure.liquid path="assets/img/courses/csc574/01-introduction/north-america-microcontroller-market.png" width="50%" zoomable=true %} 

{% enddetails %}

{% details note Step 3: Output %}

- Physical actuators
- Digital actuators

{% details Example: Face tracking device %}

<iframe width="560" height="315" src="https://www.youtube.com/embed/cy3QToyba4s?si=saP-s_a-9IKFiqfx" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

{% enddetails %}
{% enddetails %}
## Challenges of tinyML

{% details note Embedded Systems: Hardware %}


- Fundamental building blocks of computing systems:
    - Compute
    - Memory
    - Storage
- Differences between processors, micro-processors, and micro-controllers
    - Processors/micro-processors
        - Control other parts of computing devices (desktop/laptop)
        - Storage and memory are different physical components. 
    - Micro-controllers
        - Everything is integrated and tightly coupled
        - CPU, read-only memory (ROM), read-write memory, timer, I/O port, serial interface
        - Typically is preset in their functionality
- Comparison
    - Multiple magnitudes of difference

    {{ read_csv("docs/csc581/lectures/data/compare.csv") }}

- What does it mean to have less compute, memory, storage, and power consumption?
    - understand the task you want to run,
    - understand the requirements,
    - how long is the run time duration?

{% enddetails %}
{% details note Embedded Systems: Software %}

- What is software
    - High-level application
    - Supporting libraries
    - Operating systems (OSes)
- General-purpose OSes 
    - On desktop/laptop
        - Windows
        - MacOS
        - Linux distros
        - ...
    - On smartphones
      - iOS
      - Android
    - Provide supporting libraries to help run a wide variety of applications on desktop/laptop/smartphones
- OSes on embedded system
    - Specialize to perform one task.
        - FreeRTOS 
        - ARM Mbed OS.
    - Very lightweight with minimal libraries
    - Prioritize efficiency at cost of portability
    - Not easily portable 
        - To be portable, the OSes have to provide common library support. 

{% enddetails %}
{% details note ML Algorithms %}


{% include figure.liquid path="assets/img/courses/csc574/01-introduction/model_size.png" width="50%" zoomable=true %}

- Machine learning models are growing fast in complexity.
- The computing capability that is needed is growing accordingly.

{% include figure.liquid path="assets/img/courses/csc574/01-introduction/compute-needs.png" width="50%" zoomable=true %}

- What about tinyML
    - How to pack ML into tiny devices with resource constraints

- Performance trade-off
    - AlexNet (57.1% acc, 61MB)
    - VGGNet (71.5% acc, 528MB)
    - MobileNet (<70% acc, 16.9MB)

{% include figure.liquid path="assets/img/courses/csc574/01-introduction/benchmarks.png" width="50%" zoomable=true %}

- Bigger is not always better, especially in tinyML world. 
- MobileNet is still not good enough: MCU has a few KB of memory
- Solutions:
    - Compression through optimization and pruning

{% enddetails %}

## Course Hardware

{% details note Arduino Nano 33 BLE Sense (Rev1)  %}

- [Specification Sheet](https://docs.arduino.cc/resources/datasheets/ABX00031-datasheet.pdf)
    - Arm® Cortex®-M4F @ **64 MHz**, **1 MB flash**, **256 KB RAM**.
    - **MCU / radio module:** u-blox **NINA-B306** (Nordic **nRF52840**)
- Various [built-in sensors](https://docs.arduino.cc/resources/datasheets/ABX00031-datasheet.pdf#page=7.12) and enough headroom for small TensorFlow Lite Micro models, 
    - Optimization matters given limited CPU/memory.
    - IMU (motion): LSM9DS1 (9-axis) 
    - Pressure and temperature: LPS22HB
    - Gesture, light, and proximity: APDS-9960
    - Microphone: MP34DT05 
- **Important Reality Check:**
    - If purchased as part of the [Arduino Tiny Machine Learning Kit](https://store.arduino.cc/products/arduino-tiny-machine-learning-kit?srsltid=AfmBOoqoxmN3Tw2wdOp0CQ-ZtMw_QtIXWBsyEdtgN3DsehfZmGVaFBor0)
        - Carry the original **Nano 33 BLE Sense**
        - There is no humidity sensor (No HTS221)
    - Can only tolerate **3.3V** power (not 5V tolerant). 

{% enddetails %}
