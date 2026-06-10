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
- Other sensors (temperature and humidity, proximity, rbg)

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

### Overview

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



### Programmatic design

- The microphone of Nano33BLE is a Pulse-density modulation type. 
- You can interact with this microphone via the [PDM API library](https://docs.arduino.cc/learn/built-in-libraries/pdm/).



### Example: Noise Detector

>Goal: 
We want to develop a noise detector. Some of the questions to consider:
- How does Nano33BLE distinguish level of noises?
  - Answer: measure collected data to determine ...
- How does Nano33BLE provide signal?
  - Answer: the LED, maybe ...
- We will use the header files for this example to better organize the structure of 
the sketch.

We will be reusing the `include/led_controller.h` and `src/led_controller.cpp` files. 

{% details include/led_controller.h %}

```cpp
void beginLED();
void emitColor(int color);
void setred();
void setyellow();
void setgreen();
```

{% enddetails %}


{% details src/led_controller.cpp %}

```cpp
#include <Arduino.h>
#include "led_controller.h"

void setred() {
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
}

void setyellow() {
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
}

void setgreen() {
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
}

void beginLED() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void emitColor(int color) {
    if (color == 0) {
        setgreen();
    } else if (color == 1) {
        setyellow();
    } else if (color == 2) {
        setred();
    }
}
```

{% enddetails %}

When activated, the Nano33BLE microphone component samples sound and stores the measurements in memory. 

- This implementation uses a dual buffer approach
  - There are two buffer, A and B. 
  - The microphone will start by storing sample on buffer A, then switch to B while A is being read, and vice versa. 
  - The size of these buffer can be set prior to `setup()` using [setBufferSize()](https://docs.arduino.cc/learn/built-in-libraries/pdm/#setbuffersize). 
    - Default size is 512 bytes. 
- The main source code of the sketch is as follows.

{% details src/main.cpp %}
```cpp
#include <Arduino.h>
#include <PDM.h>

#include "led_controller.h"
//#include "mic_controller.h"

short sampleBuffer[256]; 
volatile int samplesRead;

void onPDMdata() {
  int bytesAvailable = PDM.available();
  PDM.read(sampleBuffer, bytesAvailable);
  samplesRead = bytesAvailable / 2;
}

void setup() {
  // start the serial communication and wait for the port to open
  Serial.begin(9600); 
  while (!Serial) {
    ;
  }

  Serial.println("Serial ready. Initializing LED...");
  // initialize the LED pins as outputs, 
  beginLED();
  setoff();

  Serial.println("LED ready. Initializing PDM microphone...");
  // initialize the PDM microphoneand set the callback function to be called when data is available
  PDM.onReceive(onPDMdata);
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to initialize PDM!");
    while (1) {
      delay(1000);
    }
  }

}

void loop() {
  int voice = 120;
  int noise = 700;

  if (samplesRead > 0) {
    long sumSquares = 0;

    for (int i = 0; i < samplesRead; i++) {
      long sample = sampleBuffer[i];
      sumSquares += sample * sample;
    }

    int rms = sqrt(sumSquares / samplesRead);
    Serial.println("RMS: " + String(rms));
    if (rms >= noise) {
      setred();
    } else if (rms >= voice) {
      setgreen();
    } else {
      setyellow();
    }
    samplesRead = 0; // Reset for the next batch of samples
  }
}
```

{% enddetails %}

In `setup()`, to prior to initializing the microphone (*line 31*), we will need to setup a callback 
function called `onPDMdata` (*line 30*). 
- This function will be called when the data is available to be read. 
- How frequent this function is called depends on the size of the PDM buffer and the sampling rate defined in the `begin()` call (*line 31*). 
  - For example, with a default 512 bytes buffer and a sampling rate of 16,000:
    - As sample size is 16 bits, we will need a sampleBuffer array of size 256 and of type *short*.
    - The callback function `onPDMdata` will run every *256/16000 = 0.016 ms*


To measure loudness, we need to look at the entire `sampleBuffer` array (declared in *line 7*). 
- Each individual sample is a vertical (amplitude) measurement of the individual waves of the sound. 
- The density of these samples (how many with large absolute values within the array) represents the 
pitch of the sound. 
- The aggregation of these two components represent human's perception of `loudness`. This can be 
calculated using root-mean-square. 
- The `loop()` section of `main.cpp` implements the above approach. 

## Other Sensors

The remaining sensors of Nano33BLE include:
- Temperature and humidity sensor: HS3003
- Gesture, light, and proximity: APDS-9960

The approach to getting and analyzing data from these sensors are similar to that of the IMU and Microphone components. Documents and tutorials can be found at.
- [Temperature and Humidity](https://docs.arduino.cc/tutorials/nano-33-ble-sense-rev2/humidity-and-temperature-sensor/)
- [Proximity sensor](https://docs.arduino.cc/tutorials/nano-33-ble-sense-rev2/proximity-sensor/)
- [Color detection](https://docs.arduino.cc/tutorials/nano-33-ble-sense-rev2/rgb-sensor/)




