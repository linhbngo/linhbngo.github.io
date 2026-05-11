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


## Other Sensors

