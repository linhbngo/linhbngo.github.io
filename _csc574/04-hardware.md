---
layout: lecture
pretty_table: true
collection: csc574
title: Sensors
toc:
  - name: IMU
  - name: Microphone
  - name: Other Sensors
---

>In this lecture we look a bit more into the hardware available for the Nano 33 BLE Rev2. More specifically:
- IMU (accelerometer, gyroscope, and magnetometer)
- Microphone
- Temperature and Humidity

## IMU

- The three IMU sensors are accelererometer, gyroscope, and magnetometer. 
- All function calls to access these sensors are available in [the Arduino_BMI270_BMM150 API](https://github.com/arduino-libraries/Arduino_BMI270_BMM150/blob/master/docs/api.md).

{% details Accelerometer %}

- Looking at the figure below, you can see how the various dimensions (z, x, y) are measured relative to 
the MCU's position.
- The documented measurement range is set at `[-4, +4]g -/+0.122 mg`.
  - This means that the MCU can measure acceleration as high as 4g or decceleration as low as -4g. This is roughly equivalent to an acceleration from 0 to 60 in 3-4s. 
  - This also means that the MCU can measure acceleration changes as sensitive as 0.122mg (not perceptible by human).

{% include figure.liquid path="assets/img/courses/csc574/04-hardware/nano33BS_02_acceleration.png" max-width="50%" zoomable=true %}

{% enddetails %}

{% details Gyroscope %}

- Looking at the figure below and observe the rotating directions. 
  - The z rotation happens when the MCU is turned vertically. 
  - When the MCU is placed horizontally, rotating on the long side of MCU is the x rotation, and rotating on the short side of the MCU is the y rotation. 
- Gyroscope range is set at `[-2000, +2000] dps +/-70 mdps`.

{% include figure.liquid path="assets/img/courses/csc574/04-hardware/nano33BS_03_gyroscope.png" max-width="50%" zoomable=true %}

{% enddetails %}

{% details Magnetometer %}

- Looking at the figure below, we have the dimension of the magnetic forces that impacting the MCU (in vertical position). 
- We can use this information to detect magnetic fields affecting the MCU. 

{% include figure.liquid path="assets/img/courses/csc574/04-hardware/nano33BS_04_magnetometer.png" max-width="50%" zoomable=true %}

{% enddetails %}


## Microphone

{% details Overview %}

- Sound is a longitudinal mechanical wave that requires a medium (air, water, or solids) to travel. 
  - *If a tree fells in a vacuum, it makes no sound!*.
- Microphones act as transducers to capture sound. They typically use a thin diaphragm that mimics the human eardrum. When sound waves hit the diaphragm, it vibrates, and the microphone converts that physical movement into an analog electrical signal.
- The Analog-to-Digital Converter (ADC) unit measures the amplitude (voltage) of the analog signal at discrete, equal intervals of time and converts these measurements into binary format (bits). 
  - ADC could be placed external to the microphones (e.g. sound cards on PC)
  - For microphone components for edge devices like the Nano33BLE, the ADC component is built into the 
  microphone's silicon. 
- The higher the sampling rate, the more accurate the information about the sound can be captured. 
  - The [Nyquist-Shannon Sampling Theorem](https://en.wikipedia.org/wiki/Nyquist%E2%80%93Shannon_sampling_theorem) states 
  that a perfect reconstruction of a real time signal (*sound* in this case) can be capture with a sampling rate of at least 
  twice the highest frequency of the signal. 
  - Since human can generally hear up to 20,000 Hz (20kHz), standard audio uses a sampling rate of 44,100 Hz. 
- Sampling rate represents the capturing of **pitch**, how high or low the voices are. 
  - High pitch: whistle, bird chirping, high voices ...
  - Low pitch: bass drum, thunder, deep voices ...
- Typical sampling rate for edge devices can be set at 16,000 Hz. This means the device can capture sounds within 
standard pitches for voice recognition purposes. 

{% enddetails %}


{% details Programmatic design %}

- The microphone of Nano33BLE is a Pulse-density modulation type. 
- You can interact with this microphone via the [PDM API library](https://docs.arduino.cc/learn/built-in-libraries/pdm/).

{% enddetails %}



## Other Sensors

