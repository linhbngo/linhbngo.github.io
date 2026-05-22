---
layout: lecture
pretty_table: true
title: Course Project

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
  - name: Available Onboard Capabilities
  - name: Suggested Project Options
  - name: Required Submission
---


In this final project, you will design, build, evaluate, and demonstrate a small machine learning system that uses data from the **Arduino Nano 33 BLE Sense Rev2**. Your project must use one or more onboard sensors from the board. It should be designed around what the board can actually sense.

## Available Onboard Capabilities

You may design your project using one or more of the following onboard capabilities:

| Sensor / Feature     | Suitable Project Uses                                                        |
| -------------------- | ---------------------------------------------------------------------------- |
| Accelerometer        | Motion, tilt, gesture, activity recognition                                  |
| Gyroscope            | Rotation, gesture recognition, movement patterns                             |
| Magnetometer         | Orientation, rough heading, sensor fusion                                    |
| Microphone           | Sound level, voice activity, clap/tap detection, simple sound classification |
| Proximity sensor     | Hand-near/hand-far detection, contactless interaction                        |
| Color / light sensor | Light condition, color/object context, covered/uncovered detection           |
| Temperature sensor   | Slow-changing environmental context                                          |
| Humidity sensor      | Environmental context, covered/uncovered, breath/near-hand experiments       |
| Pressure sensor      | Environmental context, rough altitude/pressure change                        |
| BLE                  | Communication with another device, phone, laptop, or dashboard               |
| RGB LED              | Simple output for classification results                                     |


## Suggested Project Options

{% details IMU Gesture Recognition %}

In this project, you will build a system that recognizes hand or device gestures using the accelerometer and gyroscope. The user holds or moves the Arduino board in specific ways. Your system should classify the motion into one of several gesture classes.

Example gesture classes:

| Class         | Description                          |
| ------------- | ------------------------------------ |
| Idle          | Board is not moving                  |
| Shake         | Board is shaken repeatedly           |
| Tilt left     | Board is tilted left                 |
| Tilt right    | Board is tilted right                |
| Circle        | Board is moved in a circular pattern |
| Punch forward | Board is moved quickly forward       |
| Raise         | Board is lifted upward               |
| Lower         | Board is moved downward              |

You should choose **3 to 5 classes**. More classes are allowed, but only if you can collect enough clean data.

{% details info Minimum Version %}
A minimum successful version should:
- Collect labeled accelerometer and/or gyroscope data.
- Train a classifier to recognize at least three gestures.
- Evaluate the model using a separate test set.
- Demonstrate live or recorded prediction results.
- Show the predicted class using Serial output, BLE, or the onboard LED.
{% enddetails %}

{% details info Strong Version %}
A strong version should:
- Use both accelerometer and gyroscope data.
- Collect data across multiple sessions or multiple users.
- Use fixed-size time windows.
- Include a confusion matrix.
- Deploy the model to the board or explain clearly why inference is performed on the host computer.
- Demonstrate both successful and failed predictions.
{% enddetails %}

{% details info Data Collection Requirements %}
Your report must describe:
- Sampling rate.
- Window size, such as 1 second or 2 seconds.
- Number of samples per gesture.
- Number of people who performed the gestures.
- Whether the board was held in the same orientation each time.
- How labels were assigned.
- How incomplete or incorrect samples were handled.
{% enddetails %}

This is one of the best project options because the board’s motion sensors are well-suited for TinyML.

{% enddetails %}

{% details Wearable Activity Recognition %}

In this project, you will treat the Arduino board as a simple wearable device. The system should recognize what physical activity or device state is occurring based on IMU data.

Example classes:

| Class            | Description                                         |
| ---------------- | --------------------------------------------------- |
| On desk          | Board is stationary on a table                      |
| Held in hand     | Board is held but mostly still                      |
| Walking          | User walks while carrying the board                 |
| Running in place | User runs or jogs in place while carrying the board |
| Picked up        | Board transitions from table to hand                |
| Backpack         | Board is carried inside a backpack                  |
| Rotating         | Board is being turned or spun                       |

You should choose **3 to 4 classes*- for a realistic project.

{% details info Minimum Version %}

A minimum successful version should:

- Collect labeled IMU data for several activities.
- Train a classifier.
- Evaluate accuracy on held-out data.
- Demonstrate predictions on new activity samples.

{% enddetails %}

{% details info Strong Version %}

A strong version should:

- Test whether the model works for more than one person.
- Compare performance when the board is held differently.
- Analyze which classes are confused with each other.
- Discuss whether the model is learning true activity or simply board orientation.

{% enddetails %}

{% details info Data Collection Requirements %}

Your report must describe:

- Where the board was placed: hand, pocket, backpack, table, etc.
- How long each activity was recorded.
- How the data was segmented into windows.
- Whether all data came from one person or multiple people.
- Whether testing data was collected in a different session from training data.
{% enddetails %}

This project is realistic because many embedded and wearable systems rely on motion data.

{% enddetails %}

{% details Sound Event or Voice Activity Detection %}

In this project, you will use the onboard microphone to classify simple sound events.

This is *not* full speech recognition. The goal is to recognize a small number of simple sound categories.

Example classes:

| Class            | Description                          |
| ---------------- | ------------------------------------ |
| Silence          | No significant sound                 |
| Voice            | Human speech is present              |
| Clap             | A hand clap                          |
| Tap              | Tapping near the board               |
| Snap             | Finger snap                          |
| Background noise | Fan, music, room noise               |
| Loud noise       | Sound exceeds a high intensity level |

You should choose **3 to 5 sound classes**.

{% details info Minimum Version %}

A minimum successful version should:

- Record labeled sound samples.
- Extract meaningful audio features.
- Train a classifier or compare a classifier against threshold-based logic.
- Demonstrate live or recorded sound classification.

{% enddetails %}
### Possible Features

You may use:

- RMS energy.
- Peak amplitude.
- Zero-crossing rate.
- FFT frequency bins.
- Simple spectrogram features.
- Short-window statistical features.

You do not need to implement a large neural network. A small model with good features is often better for embedded use.

{% details info Strong Version %}

A strong version should:

- Collect audio in more than one environment.
- Test the model under different background noise conditions.
- Compare simple threshold detection with a trained ML model.
- Report which sounds are easiest and hardest to classify.

{% enddetails %}

{% details info Data Collection Requirements %}

Your report must describe:

- Recording duration per sample.
- Number of samples per class.
- Distance between sound source and board.
- Background noise conditions.
- Whether sounds were recorded by one person or multiple people.
- How raw audio was converted into features.
- Whether any recordings were discarded.

{% enddetails %}
This project is good, but students must avoid overclaiming. “Detects claps and voice in a quiet room” is believable. “Understands speech in all conditions” is not.

{% enddetails %}

{% details Noise-Level Monitor with Classification %}

In this project, you will build a system that classifies the sound environment into categories such as quiet, normal, and loud.

This project may use a simple machine learning model, a rule-based system, or a hybrid approach.

Example classes:

| Class           | Description                       |
| --------------- | --------------------------------- |
| Quiet           | Little or no sound                |
| Normal voice    | Human voice or moderate sound     |
| Loud noise      | Excessive sound level             |
| Sustained noise | Noise that remains high over time |

The output could use the onboard LED:

| Prediction   | LED Behavior     |
| ------------ | ---------------- |
| Quiet        | LED off          |
| Normal voice | Green            |
| Loud noise   | Red              |
| Uncertain    | Blue or blinking |

{% details info Minimum Version %}

A minimum successful version should:

- Measure audio features from the microphone.
- Classify sound level into at least three categories.
- Demonstrate real-time response.
- Explain how thresholds or model boundaries were chosen.
{% enddetails %}

{% details info Strong Version %}

A strong version should:

- Compare threshold-based detection with a trained classifier.
- Evaluate false positives and false negatives.
- Test in multiple rooms or noise conditions.
- Display results using LED and Serial/BLE output.
{% enddetails %}

{% details info Data Collection Requirements %}

Your report must describe:

- How “quiet,” “normal,” and “loud” were defined.
- How many samples were collected per category.
- What sounds were used.
- Where the data was collected.
- Whether the same thresholds work in different environments.
{% enddetails %}

This is a good project for students who want a practical embedded sensing system without making the ML problem too large.

{% enddetails %}

{% details Contactless Gesture or Proximity Controller %}

In this project, you will use the proximity/light/color sensor to build a contactless interaction system.

The user moves a hand near the sensor, covers the sensor, or performs simple gestures. The board responds by changing LED state, sending a command, or updating a dashboard.

Example classes:

| Class            | Description                       |
| ---------------- | --------------------------------- |
| No hand          | Nothing near the sensor           |
| Hand near        | Hand is close to the sensor       |
| Covered          | Sensor is covered                 |
| Swipe left/right | Hand moves across the sensor      |
| Swipe up/down    | Hand moves vertically             |
| Bright light     | Sensor sees strong light          |
| Dark             | Sensor is covered or in low light |

{% details info Minimum Version %}

A minimum successful version should:

- Read raw proximity/light/color data.
- Collect labeled samples.
- Train a simple classifier or create a documented decision rule.
- Demonstrate a contactless control behavior.
{% enddetails %}

{% details info Strong Version %}

A strong version should:

- Use raw sensor readings instead of only relying on a built-in gesture function.
- Compare performance under different lighting conditions.
- Demonstrate the system controlling something meaningful, such as LED state, serial command, or BLE output.
- Explain failure cases caused by distance, hand speed, or lighting.
{% enddetails %}

{% details info Data Collection Requirements %}

Your report must describe:

- Distance between hand/object and sensor.
- Lighting conditions.
- Gesture speed.
- Number of trials per class.
- Whether different users performed gestures.
- Whether the system works in different rooms.
{% enddetails %}

This project is good for interaction design, but students must show real data. Simply calling a built-in gesture API and printing the result is not enough for a final project.

{% enddetails %}


{% details Multi-Sensor Device Context Classifier %}

In this project, you will combine multiple onboard sensors to classify the state or context of the device.

This is one of the strongest project options because it requires systems thinking.

Example classes:

| Class             | Possible Sensor Evidence                             |
| ----------------- | ---------------------------------------------------- |
| On desk           | Low IMU motion, stable light                         |
| Picked up         | IMU motion, orientation change                       |
| Covered by hand   | Low light, high proximity, slight temperature change |
| Inside backpack   | Low light, limited motion pattern, muffled sound     |
| Noisy environment | Audio features indicate noise                        |
| Near user         | Proximity, sound, humidity/temperature changes       |

{% details info Minimum Version %}

A minimum successful version should:

- Use at least two different sensor types.
- Collect synchronized or approximately aligned data.
- Train a classifier.
- Evaluate the model.
- Demonstrate live predictions.
{% enddetails %}

{% details info Strong Version %}

A strong version should:

- Compare single-sensor and multi-sensor models.
- Explain which sensors helped most.
- Discuss sensor timing differences.
- Show failure cases where one sensor alone is misleading.
{% enddetails %}

{% details info Data Collection Requirements %}

Your report must describe:

- Which sensors were used.
- Sampling rate or reading interval for each sensor.
- How sensor readings were combined into one sample/window.
- How labels were assigned.
- Whether slow sensors like humidity were useful.
- Whether any sensors were removed because they did not help.
{% enddetails %}

This is a good advanced project. It is also where students learn that blindly throwing more columns into a model is not “sensor fusion.” It is just making a spreadsheet nervous.

{% enddetails %}


{% details TinyML Model Deployment Comparison %}

In this project, you will compare different versions of a model for embedded deployment.

This option is appropriate for students who want a more technical ML/deployment project.

Possible comparisons:

| Comparison                          | Example                                                |
| ----------------------------------- | ------------------------------------------------------ |
| Full model vs. smaller model        | Larger neural network vs. compact neural network       |
| Float vs. quantized                 | TensorFlow Lite float model vs. int8 quantized model   |
| Raw signal vs. features             | Raw IMU window vs. extracted mean/std/min/max features |
| Host inference vs. device inference | Python model vs. embedded model                        |
| Accuracy vs. size                   | More accurate model may be too large                   |

{% details info Minimum Version %}

A minimum successful version should:

- Use a real dataset collected from the board.
- Train at least two model variants.
- Compare accuracy, size, and deployment feasibility.
- Demonstrate one working model.
{% enddetails %}

{% details info Strong Version %}

A strong version should:

- Measure or estimate memory usage.
- Compare inference latency.
- Discuss why one model is better suited for embedded deployment.
- Include model conversion details.
{% enddetails %}

This is a very good project for students interested in the engineering tradeoffs of TinyML. The best model is not always the most accurate model. It is the one that actually fits and runs.

{% enddetails %}

## Required Submission

Submit one `.zip` file containing all project materials.

Use the following structure unless your project requires a justified alternative:

```text
final_project.zip
├── README.md
├── report/
│   └── technical_report.pdf
├── firmware/
│   ├── platformio.ini
│   ├── src/
│   ├── include/
│   └── README.md
└── notebooks/
    ├── data_collection.ipynb
    ├── training.ipynb
    └── evaluation.ipynb
```

{% details README Requirement %}

Your `README.md` must explain how to inspect or reproduce the project.

It should include:

- Project title.
- Team members.
- Short project summary.
- Hardware used.
- Sensors used.
- Software requirements.
- Setup instructions.
- How to collect data.
- How to train the model.
- How to upload firmware.
- How to run the final demo.
- Link to the YouTube video.

The README should be written for another student who wants to understand your project without guessing.

{% enddetails %}

{% details Technical Report Requirement %}

Submit a polished PDF technical report (6-8 pages, single-space, 10 pts font).

- Project Overview
    - Explain what your system does.
    - Problem statement.
    - Motivation.
    - Project option selected.
    - Board and sensors used.
- Detailed Data Collection Description: Describe your dataset in enough detail that another person could understand how it was created.
- Data Preprocessing: Explain how raw data became model input.
- Model or Algorithm Design: Describe the model or detection method.
- Training Process: Describe how the model was trained.
- Evaluation: Report how well the system worked.
- Embedded Deployment or Near-Device Inference: Explain where inference happens.
- Final Demonstration: Describe the final working prototype.
- Limitations and Future Work: Be honest and specific.
    - Possible limitations:
    - Possible future work:
- References
    - Arduino documentation.
    - Libraries used.
    - Tutorials used.
    - Example code used.
    - Datasets, if any.
    - AI tools, if used.
    - External sources.

{% enddetails %}

{% details YouTube Video Requirement %}
- Submit a YouTube video with a maximum length of **10 minutes**.
- The video should explain the technical work and demonstrate the final product.
- Recommended structure:

```text
0:00–1:00    Project overview
1:00–2:00    Hardware and sensors used
2:00–3:30    Data collection process
3:30–5:00    Preprocessing and model design
5:00–6:30    Training and evaluation results
6:30–8:30    Final demonstration
8:30–10:00   Limitations and future work
```

The video must include:

- Clear explanation of the problem.
- Board and sensors used.
- Data collection process.
- Model or algorithm explanation.
- Evaluation results.
- Demonstration of the final system.
- Brief discussion of limitations.

{% enddetails %}
