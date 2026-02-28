---
layout: lecture
pretty_table: true
collection: csc574
title: Hardware Setup
toc:
  - name: Setup the tinyML Kit
  - name: Setup Software
  - name: Blink Example
  - name: Tensorflow Test
  - name: Sensor Tests
---

## Setup the tinyML Kit

{% details note Slot the Nano 33 BLE Sense board into the Tiny Machine Learning Shield %}

{% include figure.liquid path="assets/img/courses/csc574/04-hardware/ss1.jpg" width="50%" zoomable=true %}

{% include figure.liquid path="assets/img/courses/csc574/04-hardware/ss2.jpg" width="50%" zoomable=true %}

{% enddetails %}
{% details note Slot the OV7675 camera module into the shield %}


- Pay attention to the orientation

{% include figure.liquid path="assets/img/courses/csc574/04-hardware/ss3.jpg" width="50%" zoomable=true %}

{% include figure.liquid path="assets/img/courses/csc574/04-hardware/ss4.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Connect the USB cable (type-A to microB) %}

- If you have a modern computer with USB-C only, you need to buy a USB-C to microB wire or an adaptor

{% include figure.liquid path="assets/img/courses/csc574/04-hardware/ss5.png" width="50%" zoomable=true %}


{% enddetails %}
## Setup Software

{% details note What is Arduino? %}

- “an open-source electronics platform based on easy-to-use hardware and software.”
    - designs and sells a collection of microcontroller development boards that simplify deployment 
    of embedded hardware alongside a software framework that abstracts away all, but the most 
    relevant considerations for your application. 
    - enables many plug-and-play experiences given the number and quality of auxiliary hardware modules, 
    support libraries, and tutorials that have and continue to be produced within Arduino’s ecosystem.

{% enddetails %}
{% details note What is the Arduino IDE? %}

- a light-weight development environment with features that permit 
you to very quickly manipulate microcontroller development boards. 
- This course uses the standard Arduino Desktop IDE

{% enddetails %}
{% details note Downloading and Installing the Arduino IDE %}

- Navigate to arduino.cc and at the top of the page select `Software` and click `Downloads`.
    - Click on the download link appropriate for your machine.
    - There is no obligation to contribute, you can click ‘Just Download’ to proceed.
- The instructor uses version 2.3.4 . 
- Specific installation instructions if you think it is necessary
    - [Windows](https://docs.arduino.cc/software/ide-v1/tutorials/Windows/)
    - [Mac OS X](https://docs.arduino.cc/software/ide-v1/tutorials/macOS/)
    - [Linux](https://docs.arduino.cc/software/ide-v1/tutorials/Linux/)

{% enddetails %}
{% details note Installing the Board Files for the Nano 33 BLE Sense %}

- One of the primary advantages that the Arduino ecosystem affords is the 
portability of code you write for one or another board within their line-up or 
even in porting code to affiliate boards. 
- This is made possible by the support files organized in the Boards Manager, 
which coordinates a download and installation of files that detail the Arduino functions 
(sometimes ‘core’) that are defined for that particular board (which is how hardware 
differences between boards are abstracted) as well as compiler or linker details specific to the given board.
- To install the board files for Arduino Nano 33 BLE Sense:
    - Open the Boards Manager: Tools/Board/Boards Manager. Note that the Board may be set to “Arduino UNO” by default.
    - Use the search bar at the top right to search for **Arduino MBED OS Nano Boards** version 2.3.1 or newer, then 
    click **Install**

    {% include figure.liquid path="assets/img/courses/csc574/04-hardware/boards_manager.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Installing the Needed Libraries %}

- Open the Library Manager:
    - Tools/Manage Libraries.
- Find and install the followings:
    - ArduinoBLE (1.3.7)
    - Arduino_LSM9DS1 (1.1.1)
    - Harvard_TinyMLx (1.2.3-Alpha) (this library includes the Tensorflow Lite Micro Library)

{% include figure.liquid path="assets/img/courses/csc574/04-hardware/libraries.png" width="50%" zoomable=true %}

{% enddetails %}
## Blink Example

{% details note Preparing for Deployment %}

- Use a USB cable to connect the Arduino Nano 33 BLE Sense to your machine. 
    - green LED power indicator come on when the board first receives power.
- Open the Blink.ino sketch:
    - File/Examples/01.Basics/Blink
- Use the Tools drop-down menu to select appropriate Port and Board. 
    - Tools/Board/Arduino Mbed OS Boards/Arduino Nano 33 BLE. 
    - *On different operating systems, the exact name of the board may vary but/and, it should include the word Nano at a minimum*
- Select the USB Port associated with the Nano 33 BLE board. 
    - This will appear differently on Windows, macOS, Linux, but will likely indicate ‘Arduino Nano 33 BLE” in parenthesis. 
    - Tools/Port: 
        - Windows → COM<#>
        - macOS → /dev/cu.usbmodem<#>
        - Linux → ttyUSB<#> or ttyACM<#>
    - Use the checkmark button at the top left of the UI to verify that the code within the example sketch is valid. 

{% enddetails %}
{% details note Deploying (Uploading) the Sketch %}

- After check is completed, we can upload/flash the code. 
- Use the rightward arrow next to the ‘compile’ checkmark to upload / flash the code.
    - This step will re-compile the sketch before flashing the code, 
    so that in the future if you intend to sequentially compile and flash a program, 
    you need to only press the ‘upload’ arrow.

{% enddetails %}
{% details note Understanding the Code in the Blink Example %}

- A standard setup for an Arduino sketch
    - setup (run once)
    - loop (run repeatedly)
- This works well for most tinyML applications as they are designed to 
respond to continuous sensor input. 
    - Initialize the neural network and the microphone and then in a loop we want to listen to audio and trigger (or not) depending upon the output of the neural network!

```c
// the setup function runs once when you press reset or power the board
void setup(){
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}
```

```c
// the loop function runs over and over again forever
void loop(){

  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);                     // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);                     // wait for a second
}
```

{% enddetails %}
## Tensorflow Test

{% details note Preparing for Deployment: %}

- Setup USB cable (done)
- Load `hello_word.ino` sketch
    - File → Examples → Harvard_tinyMLx → hello_world.
- Setup Board and Port
- Check, then Compile and Upload/Flash
- The orange LED opposite the green LED power indicator about the USB port should now 
be fading at the rate set by the sinusoidal model. 
    - Note that the default rate is quite fast so it should 
    almost appear to be blinking very quickly. 
    - However, if you look closely you’ll notice that it is fading in and out vs. blinking.

{% enddetails %}
## Sensor Tests

{% details note Testing the Sensors %}

- Live data streams for:
    - the on-board microphone, the STMicroelectronics, MP34DT05, 
    - the on-board internal measurement unit (IMU), the STMicroelectronics, LSM9DS1, 
- At least a static image return from the off-board OV7675 camera module, the OmniVision OV7675. 
- We will also detail the optional extensions you’ll need to do to obtain a live video feed from the camera as well.

{% enddetails %}
{% details note The Serial Monitor & Plotter %}

- Top right corner of the IDE
- Two core tools that you can use to get information from your Arduino 
when it is connected to your computer with a data USB cable. 
    - Serial.println() command in Arudino sketches can be used much like the print() function in Python or printf() 
    function in C++. 
- The primary function of the Serial Monitor (and the Serial Plotter) is to view data incoming from the MCU, 
    - the Serial Monitor also features a text entry field to issue pre-determined commands conveyed in the console.

{% enddetails %}
{% details note Testing the Microphone %}

- File → Examples → Harvard_TinyMLx → test_microphone.
- Open the Serial Monitor.
    - Use the on-shield button to start and stop an audio recording Open the Serial Plotter to view the corresponding waveform.
    - You can also control the starting and stopping of the waveform by sending the command `click `through the serial monitor.
        -  In the drop-down menu that reads “No line ending”, change to“Both NL & CR”. 
        - This tells the Serial Monitor to send both a NL = new line character as well as a CR = carriage return character every time you send a message. 
        - This is important for our application as our Arduino sketch is looking for that to differentiate between each input.
- Only Serial Monitor or Serial Plotter can be opened at any given time. 

{% enddetails %}
{% details note Testing the Inertial Measurement Unit %}

- File → Examples → Harvard_TinyMLx → test_IMU.
- Available commands:
    a - display accelerometer readings in g's in x, y, and z directions
    g - display gyroscope readings in deg / s in x, y, and z directions
    m - display magnetometer readings in uT in x, y, and z directions

{% enddetails %}
{% details note Testing the OV7675 Camera %}

- File → Examples → Harvard_TinyMLx → test_camera.
- Available commands:
    - single - take a single image and print out the hexadecimal for each pixel (default)
    - live - the raw bytes of images will be streamed live over the serial port
    - capture - when in single mode, initiates an image capture
- Type “single” in the text entry field and press send or hit the enter / return key. The camera is now primed to take a picture.    
    - Now, you can either text “capture” or press the on-shield button to take a selfie (or photo). 
    - To get the photo oriented correctly, make sure the “OV7675” text on the camera module (or the “Tiny Machine Learning Shield” on the shield) is oriented such that it would be readable by the subject of the photo (e.g., you if you are taking a selfie). The camera does not have a large field of view, so if you are taking a selfie, make sure to hold the camera far away from your face.
    - Copy the sequence of hexadecimal digits that will print to the Serial Monitor to replace the phrase `COPY_THE_EXADECIMALDIGITS_HERE` in the segment of code below, and run the code inside a notebook. 

    ```python
    from matplotlib import pyplot as plt
    import numpy as np
    import struct
    HEXADECIMAL_BYTES=[COPY_THE_EXADECIMALDIGITS_HERE]

    # Reformat the bytes into an image
    raw_bytes = np.array(HEXADECIMAL_BYTES, dtype="i2")
    image = np.zeros((len(raw_bytes),3), dtype=int)

    # Loop through all of the pixels and form the image
    for i in range(len(raw_bytes)):
        #Read 16-bit pixel
        pixel = struct.unpack('>h', raw_bytes[i])[0]

        #Convert RGB565 to RGB 24-bit
        r = ((pixel >> 11) & 0x1f) << 3;
        g = ((pixel >> 5) & 0x3f) << 2;
        b = ((pixel >> 0) & 0x1f) << 3;
        image[i] = [r,g,b]

    image = np.reshape(image,(144, 176,3)) #QCIF resolution

    # Show the image
    plt.imshow(image)
    plt.show()
    ```
{% enddetails %}
