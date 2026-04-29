---
layout: lecture
pretty_table: true
title: "Practical Introduction to C++ for Arduino"
toc:
  - name: Overview
  - name: Blink
  - name: Sensor
  - name: Blink as C++
  - name: Variables, types, and constants
  - name: Conditions and loops
  - name: Functions
  - name: Objects and member functions
  - name: References and sensor reads
  - name: Arrays and sensor triples
  - name: Structs for sensor samples
  - name: Safer embedded C++ and MISRA C++
  - name: Exercises
---

## Overview


{% details note Disclaimer %}

- This is not a complete C++ programming lecture but a small practical quick-start guide to help students 
to immediately read, modify, and debug the kind of C++ code that appears in Arduino tinyML labs.
- We will use two programs throughout this lecture:
  - `Blink`: turn the built-in LED on and off.
  - `Sensor stream`: read accelerometer, gyroscope, and magnetometer data from the Nano 33 BLE Sense IMU.

- Arduino sketches are written in C++, but the Arduino framework hides much of the startup code.

On a laptop, a program often starts, performs a task, and exits.

On an Arduino, a program usually starts, configures hardware once, and then runs forever.

That is why Arduino sketches are organized around two functions:

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

## Arduino sketches are C++ programs

{% details Blink sketch (source code) %}

~~~cpp
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
~~~

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

> A microcontroller program is often a never-ending conversation with hardware:
1. configure pins and sensors;
2. check whether new data is available;
3. read inputs;
4. compute something small;
5. update outputs;
6. repeat.
That is the `setup()` / `loop()` model.

{% enddetails %}

{% details info setup() %}
`setup()` is for one-time configuration

~~~cpp
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}
~~~

- [API for pinMode][pinMode]
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

- [API for digitalWrite][digitalWrite]
- In Blink, `loop()` repeatedly turns the LED on and off by `write` (send) a `HIGH` voltage value 
and a `LOW` voltage value to the `LED_BUILTIN` pin, with a delay of 1000ms between sends. 

{% enddetails %}

{% enddetails %}



For the IMU sensor sketch, we include another library:

~~~cpp
#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
~~~

The second include gives us access to the `IMU` object and its sensor-reading functions.

---



In the sensor sketch:

~~~cpp
void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial monitor
  }

  Serial.println("Serial ready. Initializing IMU...");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    while (1) {
      delay(1000);
    }
  }

  Serial.println("IMU ready.");
  Serial.println("Ax Ay Az | Gx Gy Gz | Mx My Mz");
}
~~~

This does three jobs:

1. starts serial communication;
2. waits for a serial monitor;
3. initializes the IMU sensor.



In the sensor sketch, `loop()` repeatedly:

1. declares sensor variables;
2. checks whether data is available;
3. reads acceleration, gyroscope, and magnetic-field values;
4. prints the values;
5. waits briefly.


## Blink as C++


### Function calls

This line is a function call:

~~~cpp
digitalWrite(LED_BUILTIN, HIGH);
~~~

A function call means:

> run a named piece of code, possibly with input values.

In this example:

- `digitalWrite` is the function name;
- `LED_BUILTIN` tells Arduino which pin to control;
- `HIGH` tells Arduino to set that pin high.

This line:

~~~cpp
delay(1000);
~~~

means:

> wait for 1000 milliseconds.

One second for us. Plenty of time for a microcontroller to contemplate existence.

---

## Variables, types, and constants

A variable gives a name to a value.

The sensor sketch uses variables like this:

~~~cpp
float ax, ay, az;
float gx, gy, gz;
float mx, my, mz;
~~~

The type `float` means a number with a decimal point.

Sensor readings are not usually nice whole numbers, so `float` is appropriate.

Common Arduino/C++ types include:

| Type | Meaning | Example use |
|---|---|---|
| `int` | whole number | pin number, counter |
| `float` | decimal number | acceleration, gyroscope, magnetometer reading |
| `bool` | true/false | whether data is available |
| `char` | single character | simple serial command |
| `unsigned long` | large non-negative integer | time from `millis()` |

### Initialize variables

A safer version of the sensor variables is:

~~~cpp
float ax = 0.0F;
float ay = 0.0F;
float az = 0.0F;

float gx = 0.0F;
float gy = 0.0F;
float gz = 0.0F;

float mx = 0.0F;
float my = 0.0F;
float mz = 0.0F;
~~~

The `F` suffix tells the compiler that the literal is a `float`, not a `double`.

{% details warning Why initialization matters %}

In C++, a local variable declared inside a function is not automatically initialized to zero.

This means the following code can be risky:

~~~cpp
float ax, ay, az;
~~~

If the sensor does not provide a new acceleration reading before the variables are printed, the program may print old or meaningless values.

A microcontroller will not politely raise its hand and say, "Professor, I am about to use undefined data." It will just do it.

{% enddetails %}

### Constants

The original Blink sketch uses `1000` directly:

~~~cpp
delay(1000);
~~~

This works, but the meaning is hidden.

A better version names the value:

~~~cpp
#include <Arduino.h>

constexpr int kLedPin = LED_BUILTIN;
constexpr unsigned long kBlinkDelayMs = 1000UL;

void setup() {
  pinMode(kLedPin, OUTPUT);
}

void loop() {
  digitalWrite(kLedPin, HIGH);
  delay(kBlinkDelayMs);

  digitalWrite(kLedPin, LOW);
  delay(kBlinkDelayMs);
}
~~~

`constexpr` means the value is known at compile time and should not change.

`1000UL` means the number is an `unsigned long`, which matches many Arduino timing functions.

{% details tip Naming convention %}

The `k` prefix in names such as `kLedPin` and `kBlinkDelayMs` is one common convention for constants.

The specific convention matters less than consistency.

The bigger idea is this:

> Give important hardware and timing values names.

Named values are easier to read, easier to change, and easier to review.

{% enddetails %}

---

## Conditions and loops

### `if` statements

The sensor sketch uses `if` statements:

~~~cpp
if (IMU.accelerationAvailable()) {
  IMU.readAcceleration(ax, ay, az);
}
~~~

This means:

> If acceleration data is available, then read it.

The condition goes inside parentheses:

~~~cpp
IMU.accelerationAvailable()
~~~

The body goes inside braces:

~~~cpp
{
  IMU.readAcceleration(ax, ay, az);
}
~~~

A similar pattern appears for the gyroscope and magnetometer:

~~~cpp
if (IMU.gyroscopeAvailable()) {
  IMU.readGyroscope(gx, gy, gz);
}

if (IMU.magneticFieldAvailable()) {
  IMU.readMagneticField(mx, my, mz);
}
~~~

### `while` loops

The setup code uses a `while` loop:

~~~cpp
while (!Serial) {
  ; // wait for serial monitor
}
~~~

This means:

> While the serial connection is not ready, keep waiting.

The `!` operator means not.

So:

~~~cpp
!Serial
~~~

means:

> Serial is not ready.

The body contains only a semicolon:

~~~cpp
;
~~~

That is an empty statement. It does nothing. This is a deliberate wait loop.

A more readable version is:

~~~cpp
while (!Serial) {
  delay(10);
}
~~~

This still waits, but it avoids a completely empty loop.

{% details warning Embedded-system concern %}

This code can block forever:

~~~cpp
while (!Serial) {
  ;
}
~~~

That may be fine in a classroom when students always open the Serial Monitor.

It is less appropriate for a deployed device. A device installed in a field, backpack, robot, or medical prototype should not stop forever just because nobody opened a serial console.

{% enddetails %}

### Add a timeout

A safer classroom/deployment compromise is:

~~~cpp
constexpr unsigned long kSerialTimeoutMs = 5000UL;

void waitForSerialOrTimeout() {
  const unsigned long startTime = millis();

  while (!Serial && (millis() - startTime < kSerialTimeoutMs)) {
    delay(10);
  }
}
~~~

Then `setup()` can call:

~~~cpp
Serial.begin(9600);
waitForSerialOrTimeout();
~~~

This still gives students time to open the Serial Monitor, but the board will not wait forever.

### Infinite loops as error traps

This part of the sensor sketch checks whether the IMU starts correctly:

~~~cpp
if (!IMU.begin()) {
  Serial.println("Failed to initialize IMU");
  while (1) {
    delay(1000);
  }
}
~~~

`IMU.begin()` tries to initialize the sensor.

If it fails, `!IMU.begin()` becomes true.

Then the code prints an error message and enters:

~~~cpp
while (1) {
  delay(1000);
}
~~~

In a condition, `1` means true. So `while (1)` means loop forever.

A C++-style version is:

~~~cpp
while (true) {
  delay(1000);
}
~~~

{% details note Why stop forever? %}

This is a common embedded systems pattern:

> If a required hardware component fails, stop the program in a safe and obvious way.

The board is not crashed. It is intentionally parked.

For a more advanced version, we might blink an error code on the LED.

{% enddetails %}

---

## Functions

A function packages repeated behavior into a named block.

The original Blink code repeats the same pattern every loop:

~~~cpp
digitalWrite(LED_BUILTIN, HIGH);
delay(1000);
digitalWrite(LED_BUILTIN, LOW);
delay(1000);
~~~

We can create our own function:

~~~cpp
#include <Arduino.h>

constexpr int kLedPin = LED_BUILTIN;
constexpr unsigned long kBlinkDelayMs = 1000UL;

void blinkOnce() {
  digitalWrite(kLedPin, HIGH);
  delay(kBlinkDelayMs);

  digitalWrite(kLedPin, LOW);
  delay(kBlinkDelayMs);
}

void setup() {
  pinMode(kLedPin, OUTPUT);
}

void loop() {
  blinkOnce();
}
~~~

This defines a new function:

~~~cpp
void blinkOnce() {
  // function body
}
~~~

`void` means the function does not return a value.

The function name is `blinkOnce`.

The parentheses are empty because this function does not take input parameters.

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

{% details note Arduino IDE versus PlatformIO %}

The Arduino IDE often generates function prototypes automatically for `.ino` sketches.

PlatformIO with `.cpp` files is closer to normal C++ compilation rules.

For teaching, it is better for students to see the real C++ rule:

> declare a function before calling it.

This avoids surprises when code moves from a small sketch to a larger project.

{% enddetails %}

---

## Objects and member functions

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

In Arduino C++, students use objects almost immediately, even before they know the word "object."

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

{% details warning Do not overuse this yet %}

For early Arduino labs, a class may be overkill.

A few constants and helper functions are usually clearer.

But students should recognize object-style calls because Arduino libraries use them constantly.

{% enddetails %}

---

## References and sensor reads

The following line is surprisingly important:

~~~cpp
IMU.readAcceleration(ax, ay, az);
~~~

At first glance, this looks like we are sending values into the function.

But after the function call, `ax`, `ay`, and `az` contain new sensor readings.

That means the function is not merely reading the values. It is modifying the variables.

In C++, this is commonly done using **references**.

A simple example:

~~~cpp
void resetToZero(float& x, float& y, float& z) {
  x = 0.0F;
  y = 0.0F;
  z = 0.0F;
}

void loop() {
  float ax = 1.0F;
  float ay = 2.0F;
  float az = 3.0F;

  resetToZero(ax, ay, az);

  Serial.println(ax); // prints 0.0
}
~~~

The `&` in this parameter list means reference:

~~~cpp
float& x
~~~

A reference parameter gives the function access to the caller's variable.

So when the function changes `x`, the original variable changes too.

{% details note Compare to C pointers %}

In C, the same idea is often expressed with pointers:

~~~c
void resetToZero(float* x) {
  *x = 0.0F;
}
~~~

In C++, references are often easier for beginners to read:

~~~cpp
void resetToZero(float& x) {
  x = 0.0F;
}
~~~

Both ideas are related to memory addresses, but references hide some of the pointer syntax.

{% enddetails %}

### Why `readAcceleration` uses references

A function can return one value directly:

~~~cpp
int getAnswer() {
  return 42;
}
~~~

But acceleration has three values:

- x-axis;
- y-axis;
- z-axis.

One practical C++ style is to pass three variables by reference:

~~~cpp
IMU.readAcceleration(ax, ay, az);
~~~

The function fills all three variables.

---

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

---

## Safer embedded C++ and MISRA C++

C++ is powerful. Embedded C++ is powerful in a smaller room with fewer exits.

On a laptop, a crash may mean restarting a program.

On an embedded device, a software defect may mean:

- a robot behaves incorrectly;
- a drone loses stability;
- a medical or assistive device gives a wrong signal;
- a deployed sensor silently collects bad data;
- a tinyML model receives garbage input and confidently produces garbage output.

This is why professional embedded software often follows coding standards.

### What is MISRA C++?

MISRA C++ is a set of coding guidelines for writing safer, more reliable C++ in critical systems.

The current modern version is **MISRA C++:2023**, whose full title is:

> MISRA C++:2023 Guidelines for the use of C++:17 in critical systems.

The practical idea is not "never use C++."

The practical idea is:

> Use a safer, more restricted subset of C++ and document the rare cases where a project must deviate from the rules.

{% details note Important distinction %}

This course is **not** claiming MISRA compliance.

MISRA compliance is a project-level engineering process. It involves selected guidelines, tool support, reviews, documentation, and formal handling of deviations.

In this course, we use MISRA C++ as a professional lens:

- write code that is easier to inspect;
- avoid undefined behavior;
- initialize variables;
- avoid unnecessary dynamic memory;
- avoid cleverness where clarity is safer;
- check whether hardware initialization succeeded;
- make constants explicit;
- limit global mutable state;
- keep functions small and purposeful.

{% enddetails %}

### MISRA-inspired rules for our Arduino labs

We will not teach the full MISRA C++ rule set here.

Instead, we will borrow a small set of habits that are appropriate for early Arduino work.

| Habit | Why it matters in embedded C++ |
|---|---|
| Initialize variables | Avoid printing or computing with undefined values |
| Use named constants | Avoid unexplained hardware and timing numbers |
| Check initialization results | Do not continue if required hardware failed |
| Prefer clear types | Reduce surprises from implicit conversions |
| Keep functions short | Make behavior easier to review and test |
| Avoid dynamic allocation in basic labs | Heap allocation can fail or fragment memory on small devices |
| Avoid blocking forever unless intentional | Deployed devices may not have a serial monitor attached |
| Keep sensor output format consistent | Python notebooks and data loggers depend on predictable data |

### Unsafe-ish sensor code

This version is common in quick demos:

~~~cpp
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

  Serial.print("A:");
  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.println(az);

  delay(200);
}
~~~

The problem is subtle:

- if acceleration data is available, `ax`, `ay`, and `az` are updated;
- if it is not available, they may still contain undefined values;
- the program prints them anyway.

### Safer version: initialize and track availability

~~~cpp
#include <Arduino.h>
#include <Arduino_LSM9DS1.h>

constexpr unsigned long kBaudRate = 9600UL;
constexpr unsigned long kSampleDelayMs = 200UL;
constexpr unsigned long kSerialTimeoutMs = 5000UL;

void waitForSerialOrTimeout() {
  const unsigned long startTime = millis();

  while (!Serial && (millis() - startTime < kSerialTimeoutMs)) {
    delay(10);
  }
}

void stopForever() {
  while (true) {
    delay(1000);
  }
}

void setup() {
  Serial.begin(kBaudRate);
  waitForSerialOrTimeout();

  Serial.println("Serial ready. Initializing IMU...");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    stopForever();
  }

  Serial.println("IMU ready.");
  Serial.println("Ax,Ay,Az,Gx,Gy,Gz,Mx,My,Mz");
}

void loop() {
  float ax = 0.0F;
  float ay = 0.0F;
  float az = 0.0F;

  float gx = 0.0F;
  float gy = 0.0F;
  float gz = 0.0F;

  float mx = 0.0F;
  float my = 0.0F;
  float mz = 0.0F;

  const bool hasAcceleration = IMU.accelerationAvailable();
  const bool hasGyroscope = IMU.gyroscopeAvailable();
  const bool hasMagnetometer = IMU.magneticFieldAvailable();

  if (hasAcceleration) {
    IMU.readAcceleration(ax, ay, az);
  }

  if (hasGyroscope) {
    IMU.readGyroscope(gx, gy, gz);
  }

  if (hasMagnetometer) {
    IMU.readMagneticField(mx, my, mz);
  }

  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.print(az);
  Serial.print(",");

  Serial.print(gx);
  Serial.print(",");
  Serial.print(gy);
  Serial.print(",");
  Serial.print(gz);
  Serial.print(",");

  Serial.print(mx);
  Serial.print(",");
  Serial.print(my);
  Serial.print(",");
  Serial.println(mz);

  delay(kSampleDelayMs);
}
~~~

This version is still beginner-friendly, but it is safer and more data-friendly:

- constants are named;
- variables are initialized;
- serial waiting has a timeout;
- IMU failure is handled explicitly;
- CSV output is easier for Python to parse;
- helper functions give names to repeated ideas.

{% details warning Constructive criticism %}

The variables `hasAcceleration`, `hasGyroscope`, and `hasMagnetometer` are computed, but this version still prints zeros when data is unavailable.

That may be acceptable for a first demo, but it is not ideal for real data collection.

For real data collection, we should either:

- print only complete samples;
- include availability flags in the output;
- carry forward the most recent valid value intentionally;
- timestamp each sample so missing values can be handled later.

Good embedded code is not merely code that compiles. Good embedded code tells the truth about the hardware state.

{% enddetails %}

### Safer version: print only complete samples

For data collection, this version is often better:

~~~cpp
void loop() {
  if (!IMU.accelerationAvailable() ||
      !IMU.gyroscopeAvailable() ||
      !IMU.magneticFieldAvailable()) {
    delay(kSampleDelayMs);
    return;
  }

  float ax = 0.0F;
  float ay = 0.0F;
  float az = 0.0F;

  float gx = 0.0F;
  float gy = 0.0F;
  float gz = 0.0F;

  float mx = 0.0F;
  float my = 0.0F;
  float mz = 0.0F;

  IMU.readAcceleration(ax, ay, az);
  IMU.readGyroscope(gx, gy, gz);
  IMU.readMagneticField(mx, my, mz);

  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.print(az);
  Serial.print(",");

  Serial.print(gx);
  Serial.print(",");
  Serial.print(gy);
  Serial.print(",");
  Serial.print(gz);
  Serial.print(",");

  Serial.print(mx);
  Serial.print(",");
  Serial.print(my);
  Serial.print(",");
  Serial.println(mz);

  delay(kSampleDelayMs);
}
~~~

The line:

~~~cpp
return;
~~~

exits the current call to `loop()` early.

Because Arduino calls `loop()` again and again, the program will check again on the next iteration.

### MISRA C++ and tinyML

MISRA C++ is not only about cars or aerospace systems.

The spirit applies naturally to tinyML:

- sensor input should be valid;
- preprocessing should be predictable;
- memory use should be controlled;
- model input layout should be explicit;
- failure modes should be visible;
- the code should be reviewable by someone other than the original author.

For classroom projects, this means we will prefer code that is clear and boring over code that is clever and fragile.

In embedded systems, boring is not an insult. Boring is often what keeps the robot from doing interpretive dance into a wall.

### References

- MISRA official release note: [MISRA C++:2023 released](https://misra.org.uk/misra-cpp2023-released-including-hardcopy/)
- MISRA official compliance page: [MISRA Compliance](https://misra.org.uk/compliance/)
- MISRA Compliance:2020 document: [PDF](https://misra.org.uk/app/uploads/2021/06/MISRA-Compliance-2020.pdf)

---

## Exercises

{% details tip Exercise 1: Change Blink timing %}

Start with this version:

~~~cpp
#include <Arduino.h>

constexpr int kLedPin = LED_BUILTIN;
constexpr unsigned long kBlinkDelayMs = 1000UL;

void setup() {
  pinMode(kLedPin, OUTPUT);
}

void loop() {
  digitalWrite(kLedPin, HIGH);
  delay(kBlinkDelayMs);
  digitalWrite(kLedPin, LOW);
  delay(kBlinkDelayMs);
}
~~~

Modify the constant so the LED blinks four times faster.

Question:

- What value should `kBlinkDelayMs` have?

{% enddetails %}

{% details tip Exercise 2: Create a helper function %}

Rewrite Blink so that `loop()` contains only this line:

~~~cpp
blinkOnce(500UL);
~~~

Your task:

- create a function named `blinkOnce`;
- give it one parameter named `delayMs`;
- use that parameter for both delays.

{% enddetails %}

{% details tip Exercise 3: Add a serial timeout %}

The following code can wait forever:

~~~cpp
while (!Serial) {
  ;
}
~~~

Modify it so that it waits at most 5 seconds.

Hint:

- use `millis()`;
- store the starting time;
- compare the elapsed time against a named constant.

{% enddetails %}

{% details tip Exercise 4: Fix uninitialized sensor variables %}

Start with this code:

~~~cpp
float ax, ay, az;

if (IMU.accelerationAvailable()) {
  IMU.readAcceleration(ax, ay, az);
}

Serial.println(ax);
~~~

Modify it so that `ax`, `ay`, and `az` are initialized safely.

Then answer:

- What value will be printed if acceleration is not available?
- Is that value truthful, or merely safe?

{% enddetails %}

{% details tip Exercise 5: Use a struct %}

Create a `struct` named `Vec3` with three fields:

- `x`
- `y`
- `z`

Then create a variable:

~~~cpp
Vec3 acceleration = {0.0F, 0.0F, 0.0F};
~~~

Modify the acceleration reading code so that it stores values into:

~~~cpp
acceleration.x
acceleration.y
acceleration.z
~~~

{% enddetails %}

{% details tip Exercise 6: MISRA-inspired code review %}

Review the original sensor sketch and identify at least four improvements inspired by safer embedded C++ practices.

Possible categories:

- uninitialized variables;
- magic numbers;
- blocking forever;
- inconsistent output format;
- repeated print code;
- unclear failure behavior;
- missing timestamp;
- unclear handling of unavailable sensor data.

{% enddetails %}

---

## Takeaways

- Arduino sketches are C++ programs, even though they look C-like.
- `setup()` runs once; `loop()` runs repeatedly.
- `Serial` and `IMU` are objects.
- `Serial.print(...)` and `IMU.readAcceleration(...)` are member function calls.
- C++ references help explain why `IMU.readAcceleration(ax, ay, az)` can modify variables.
- Constants make hardware and timing choices easier to read.
- Initialization matters because embedded programs should not compute or print undefined values.
- `struct` types help organize sensor data.
- MISRA C++ gives us a professional safety lens: clear, restricted, reviewable C++ is better than clever code that only works on a lucky Tuesday.

[pinMode](https://docs.arduino.cc/language-reference/en/functions/digital-io/pinMode/)
[digitalWrite](https://docs.arduino.cc/language-reference/en/functions/digital-io/digitalwrite/)