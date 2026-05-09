---
layout: lecture
pretty_table: true
title: "Practical Introduction to C++ for Arduino"
toc:
  - name: Overview
  - name: Arduino Sketches
  - name: More Function
  - name: Objects and Member Functions
  - name: Arrays and sensor triples
  - name: Structs for sensor samples
---

## Overview


{% details note Disclaimer %}

- This is not a complete C++ programming lecture but a small practical quick-start guide to help students 
to immediately read, modify, and debug the kind of C++ code that appears in Arduino tinyML labs.
- We will use two programs throughout this lecture:
  - `Blink`: turn the built-in LED on and off.
  - `Sensor stream`: read accelerometer, gyroscope, and magnetometer data from the Nano 33 BLE Sense IMU.

- Arduino sketches are written in C++, but the Arduino framework hides much of the startup code.
  - On a laptop, a program often starts, performs a task, and exits.
  - On an Arduino, a program usually starts, configures hardware once, and then runs forever.

- Arduino sketches are organized around two functions:
  - `setup()` runs once.
  - `loop()` runs repeatedly.

{% enddetails %}


{% details Learning Objective %}

- In this lecture, we will introduce C++ through Arduino code.
- We will cover:
  - `#include` statements;
  - statements and semicolons;
  - `setup()` and `loop()`;
  - variables and types;
  - constants;
  - `if` statements;
  - `while` loops;
  - functions;
  - objects and member functions;
  - references;
  - arrays;
  - `struct` values for organizing sensor data;
  - basic embedded C++ safety practices;
  - MISRA C++ standard in professional embedded systems.

{% enddetails %}

## Arduino Sketches

{% details Blink %}

```cpp
#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```

- This file may have an `.ino` extension in the Arduino IDE, or it may be written as a `.cpp` file in PlatformIO.
- Either way, the code is compiled as C++ code for the target board.

{% details info #include %}
- An `#include` statement tells the compiler to bring in declarations from another file.
For this sketch, `Arduino.h` gives us access to names such as:
  - `pinMode`
  - `digitalWrite`
  - `delay`
  - `LED_BUILTIN`
  - `OUTPUT`
  - `HIGH`
  - `LOW`
{% enddetails %}


{% details tip setup() and loop() %}

- A traditional C++ program begins with `main()`:
- For Arduino, we write:

~~~cpp
void setup() {
  // runs once
}

void loop() {
  // runs repeatedly
}
~~~

- These two functions represent two major tasks in embedded systems:
  - Configure hardware
  - Execute tasks (read sensors, process data, write to serial connectors ...) forever. 
- Conceptually, Arduino behaves like this:

~~~cpp
int main() {
  initArduinoHardware();

  setup();

  while (true) {
    loop();
  }
}
~~~

> A microcontroller program maintains a continuous with hardware:
  - 1. configure pins and sensors;
  - 2. check whether new data is available;
  - 3. read inputs;
  - 4. compute something small;
  - 5. update outputs;
  - 6. repeat.
That is the `setup()` / `loop()` model.

{% enddetails %}

{% details info setup() %}
`setup()` is for one-time configuration

~~~cpp
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}
~~~

- [API for pinMode](pinMode)
- This configures the built-in LED pin as an output pin.

{% enddetails %}


{% details info loop() %}
- `loop()` is for repeated behavior

```c++
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```

- [API for digitalWrite](digitalWrite)
- In Blink, `loop()` repeatedly turns the LED on and off by `write` (send) a `HIGH` voltage value 
and a `LOW` voltage value to the `LED_BUILTIN` pin, with a delay of 1000ms between sends. 

{% enddetails %}

{% enddetails %}


{% details Sensor %}

```cpp
#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial monitor
  }

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1) {
      delay(1000);
    }
  }

  Serial.println("Serial ready. Initializing IMU...");
  Serial.println("IMU ready.");
  Serial.println("Ax Ay Az | Gx Gy Gz | Mx My Mz");
}

void loop() {
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);
  }

  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(mx, my, mz);
  }
 
  char line[160];

  snprintf(line,sizeof(line),
    "A:%.3f,%.3f,%.3f | G:%.3f,%.3f,%.3f | M:%.3f,%.3f,%.3f",
    ax, ay, az,
    gx, gy, gz,
    mx, my, mz
  );

  Serial.println(line);
  
  delay(200);
}
```

> For the IMU sensor sketch, we include another library:
```cpp
#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>
```
The second include gives us access to the `IMU` object and its sensor-reading functions.

{% details info setup() %}
- starts serial communication;
- waits for a serial monitor;
- initializes the IMU sensor.
{% enddetails %}


{% details info Variables and types %}

- A variable gives a name to a value.
- The sensor sketch declares variables as follows:

```cpp
float ax, ay, az;
float gx, gy, gz;
float mx, my, mz;
```

- In Arduino/C++, variables are associated with types: 
- Common types include:

| Type | Meaning | Example use |
|---|---|---|
| `int` | whole number | pin number, counter |
| `float` | decimal number | acceleration, gyroscope, magnetometer reading |
| `bool` | true/false | whether data is available |
| `char` | single character | simple serial command |
| `unsigned long` | large non-negative integer | time from `millis()` |

- In `Sensor`, sensor readings are not usually integers, so `float` is appropriate.

{% enddetails %} <!-- closes details variables -->

{% details info loop() %}
- declares sensor variables;
- checks whether data is available;
- reads acceleration, gyroscope, and magnetic-field values;
- prints the values;
- waits for 200ms and repeats.
{% enddetails %}


{% details info if statements %}

- The sensor sketch uses `if` statements.
- This means: If acceleration data is available, then read those values into the variables `ax`, `ay`, and `az`.

```cpp
if (IMU.accelerationAvailable()) {
  IMU.readAcceleration(ax, ay, az);
}
```

- Similar patterns are for the gyroscope and magnetometer:

```cpp
if (IMU.gyroscopeAvailable()) {
  IMU.readGyroscope(gx, gy, gz);
}

if (IMU.magneticFieldAvailable()) {
  IMU.readMagneticField(mx, my, mz);
}
```

{% enddetails %} 



{% details info while loop %}

The setup code uses a `while` loop:

```cpp
while (!Serial) {
  ; // wait for serial monitor
}
```

This means while the serial connection is not ready, keep waiting.

{% enddetails %}



{% details function calls %}

```cpp
readMagneticField(mx, my, mz)
```

- Calling a function means to run a named segment of code, possibly with input values.
- In this example:
  - `readMagneticField` is the function name. 
  - `mx`, `my`, `mz` are the variables where `readMagneticField` write the contents of the magnetic 
  sensors into. 
  - [readMagneticField API](https://docs.arduino.cc/libraries/arduino_bmi270_bmm150/#Methods)

{% enddetails %}

{% enddetails %} <!-- closes details Sensor -->



## More Functions

{% details tip Problem Statement %}

> Setup a pothole detector: If the sensor detects bounciness (`vertical acceleration`) that is greater than a certain value, change 
the LED light to `RED`. Otherwise, keep it as `GREEN`. 

- From the sensor code, we know that the accelerometer measures acceleration on three axis, x, y, and z. The vertical acceleration is 
on the z axis. 
- The LED light on the board is RBG, and [can be controlled](https://support.arduino.cc/hc/en-us/articles/360016724140-Control-the-RGB-LED-on-Nano-33-BLE-boards).
- The pseudocode is as follows.

```cpp
void setup() {
  initialize LED with OUTPUT using LEDR, LEDG, and LEDB;
  initialize IMU;
  possibly initialize Serial for debugging purposes;
}

void loop() {
  capture accelerometer values into ax, ay, az;
  if az is greaer than a certain value (1 means stationary), change LED to RED;
  else change LED to GREEN; 
  delay
}
```

{% enddetails %}

{% details First version %}

```cpp
#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

void setup() {
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1) {
      delay(1000);
    }
  }

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void loop() {
  float ax, ay, az;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }

  if (az > 2) {
     // Red
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
  } else {
    // Green
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, HIGH);
  }
  
  delay(200);
}
```

{% enddetails %}

{% details Creating a function %}

- We are going to change the code a bit so that the the code for setting the LED light to red and green. 
  - Since this function sends a signal to the chip directly, we will 
  use `void`, which means the function does not return a value.


```cpp
#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

void setred() {
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
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

void setup() {
  IMU.begin();
  beginLED();
}

void loop() {
  float ax, ay, az;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }

  if (az > 1.5) {
     setred();
  } else {
     setgreen();
  }
  
  delay(200);
}
```

{% enddetails %}



### Function parameters

A better helper function can accept input values:

~~~cpp
#include <Arduino.h>

constexpr int kLedPin = LED_BUILTIN;

void blinkOnce(unsigned long delayMs) {
  digitalWrite(kLedPin, HIGH);
  delay(delayMs);

  digitalWrite(kLedPin, LOW);
  delay(delayMs);
}

void setup() {
  pinMode(kLedPin, OUTPUT);
}

void loop() {
  blinkOnce(1000UL);
}
~~~

Now:

~~~cpp
void blinkOnce(unsigned long delayMs)
~~~

means:

> Define a function named `blinkOnce` that accepts one `unsigned long` parameter named `delayMs`.

When we call:

~~~cpp
blinkOnce(1000UL);
~~~

the value `1000UL` is copied into `delayMs`.

Try modifying the call:

~~~cpp
blinkOnce(250UL);
~~~

The LED should blink faster.

### Function declarations

In C++, a function must be declared before it is used.

This works:

~~~cpp
void blinkOnce(unsigned long delayMs) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(delayMs);
  digitalWrite(LED_BUILTIN, LOW);
  delay(delayMs);
}

void loop() {
  blinkOnce(1000UL);
}
~~~

This may fail in a `.cpp` file if the compiler sees the call before it sees the function:

~~~cpp
void loop() {
  blinkOnce(1000UL);
}

void blinkOnce(unsigned long delayMs) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(delayMs);
  digitalWrite(LED_BUILTIN, LOW);
  delay(delayMs);
}
~~~

The fix is a function declaration, also called a prototype:

~~~cpp
void blinkOnce(unsigned long delayMs);

void loop() {
  blinkOnce(1000UL);
}

void blinkOnce(unsigned long delayMs) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(delayMs);
  digitalWrite(LED_BUILTIN, LOW);
  delay(delayMs);
}
~~~


## Objects and Member Functions

C++ supports objects.

An object combines data and functions that operate on that data.

We already use objects in Arduino code:

~~~cpp
Serial.begin(9600);
Serial.println("IMU ready.");
IMU.begin();
IMU.readAcceleration(ax, ay, az);
~~~

Here:

- `Serial` is an object representing serial communication;
- `IMU` is an object representing the inertial measurement unit;
- `begin`, `println`, and `readAcceleration` are member functions.

A member function call uses the dot operator:

~~~cpp
objectName.memberFunction(arguments);
~~~

Examples:

~~~cpp
Serial.println("Hello");
IMU.accelerationAvailable();
~~~

{% details note Why this matters %}

This is one of the biggest reasons to call the lecture **Introduction to C++**, not **Introduction to C**.

In C, there are no objects or member functions.

In Arduino C++, we use objects almost immediately, even before they know the word "object."

{% enddetails %}

### A tiny class example

We do not need to write many classes yet, but a tiny example helps explain what `Serial` and `IMU` are doing conceptually.

~~~cpp
class LedBlinker {
public:
  LedBlinker(int pin, unsigned long delayMs)
      : pin_(pin), delayMs_(delayMs) {}

  void begin() {
    pinMode(pin_, OUTPUT);
  }

  void blinkOnce() {
    digitalWrite(pin_, HIGH);
    delay(delayMs_);
    digitalWrite(pin_, LOW);
    delay(delayMs_);
  }

private:
  int pin_;
  unsigned long delayMs_;
};

LedBlinker blinker(LED_BUILTIN, 1000UL);

void setup() {
  blinker.begin();
}

void loop() {
  blinker.blinkOnce();
}
~~~

This is more advanced than we need for the first lab, but it shows the idea:

- the object `blinker` stores the pin and delay;
- the member function `begin()` configures the hardware;
- the member function `blinkOnce()` performs the repeated behavior.


## Arrays and sensor triples

An array stores multiple values of the same type.

The sensor sketch currently uses separate variables:

~~~cpp
float ax = 0.0F;
float ay = 0.0F;
float az = 0.0F;
~~~

We can also store the three values in an array:

~~~cpp
constexpr int kAxisCount = 3;
float acceleration[kAxisCount] = {0.0F, 0.0F, 0.0F};
~~~

Array indices start at `0`:

~~~cpp
acceleration[0] // x
acceleration[1] // y
acceleration[2] // z
~~~

For simple Arduino sensor code, separate variables are often easier to read.

But arrays become useful when we want to loop over many values.

~~~cpp
for (int i = 0; i < kAxisCount; ++i) {
  Serial.println(acceleration[i]);
}
~~~

{% details warning Array safety %}

C++ does not automatically stop you from writing past the end of a basic C-style array.

This is wrong:

~~~cpp
float acceleration[3] = {0.0F, 0.0F, 0.0F};
acceleration[3] = 9.9F; // wrong: valid indices are 0, 1, 2
~~~

That kind of mistake may corrupt nearby memory.

This is one reason professional embedded teams use coding standards and static analysis tools.

{% enddetails %}

---

## Structs for sensor samples

A `struct` groups related data together.

Instead of keeping x, y, and z as separate variables, we can define a vector-like type:

~~~cpp
struct Vec3 {
  float x;
  float y;
  float z;
};
~~~

Then we can create variables:

~~~cpp
Vec3 acceleration = {0.0F, 0.0F, 0.0F};
Vec3 gyroscope = {0.0F, 0.0F, 0.0F};
Vec3 magnetometer = {0.0F, 0.0F, 0.0F};
~~~

We access fields using the dot operator:

~~~cpp
Serial.print(acceleration.x);
Serial.print(acceleration.y);
Serial.println(acceleration.z);
~~~

### A structured IMU sample

We can group all sensor values into one sample:

~~~cpp
struct Vec3 {
  float x;
  float y;
  float z;
};

struct ImuSample {
  Vec3 acceleration;
  Vec3 gyroscope;
  Vec3 magnetometer;
};
~~~

Then the loop can work with one `ImuSample` variable:

~~~cpp
void loop() {
  ImuSample sample = {
      {0.0F, 0.0F, 0.0F},
      {0.0F, 0.0F, 0.0F},
      {0.0F, 0.0F, 0.0F}
  };

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(sample.acceleration.x,
                         sample.acceleration.y,
                         sample.acceleration.z);
  }

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(sample.gyroscope.x,
                      sample.gyroscope.y,
                      sample.gyroscope.z);
  }

  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(sample.magnetometer.x,
                          sample.magnetometer.y,
                          sample.magnetometer.z);
  }

  delay(200);
}
~~~

This is longer at first, but the organization becomes valuable when programs grow.

{% details tip Why structs matter for tinyML %}

A machine learning dataset is not just a pile of numbers.

It is structured data.

For motion recognition, a single sample might include:

- acceleration x/y/z;
- gyroscope x/y/z;
- timestamp;
- label;
- device ID;
- sampling rate.

A `struct` is one of the first tools students can use to represent structured sensor data cleanly.

{% enddetails %}

