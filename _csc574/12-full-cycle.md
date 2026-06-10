---
layout: lecture
pretty_table: true
collection: csc574
title: Full Cycle

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
  - name: "Stage 1: Data Generation"
  - name: "Stage 2: Data Engineering"
  - name: "Stage 3: Model Development"
  - name: "Stage 4: Live Validation"
  - name: "Stage 5: Deployment"
---

In this lecture, we revisit a full cycle of tinyML deployment. For the sake of simplicity, let's envision that 
this cycle is motivated by a need for sensors to detect swerving movement of drivers (sudden side-to-side). 

## Stage 1: Data Generation

We start by developing a firmware sketch for the Nano33BLE device that can detect side-to-side movement. Before we can detect something, we must be able to observe it. Let's start with observing the Nano33BLE's IMU sensors. 

- We will utilize Serial connection to observe the collected data via `pio device monitor`. 
- Since we are observing side-to-side only, for the sake of simplicity, we can 
    - Ignore gyroscope and magnetometer components of IMU
    - For accelerometer, we can
        - assume side to side movement is on the short side of the board (x), and
        - ignore the z-axis and focus only on x and y axes. 

{% include figure.liquid path="assets/img/courses/csc574/04-hardware/nano33BS_02_acceleration.png" max-width="50%" zoomable=true alt="Accelerometer axes" %}


{% details Initial firmware sketch for data collection %}

- Setup a project called `Swerve_data_collect` inside `firmware` directory with the following file contents:

- `platformio.ini`:

```bash
[env:nano33ble]
platform = nordicnrf52
board = nano33ble
framework = arduino
lib_deps = 
    arduino-libraries/Arduino_BMI270_BMM150
monitor_speed = 9600
```

- `main.cpp`:

```c
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
  Serial.println("Ax");
}

void loop() {
  float ax, ay, az;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }
 
  char line[10];
  snprintf(line,sizeof(line),"%.3f", ax);
  Serial.println(line);
  delay(100);
}
```
- Compile and upload.
- Data collected from an initial run of the above sketch are shown in the following Figure

{% include figure.liquid path="assets/img/courses/csc574/full-cycle/01-raw-data.png" max-width="15%" zoomable=true alt="Single entry data collection from sensors" %}

- The red rectangles indicate the moments when the chip was moved suddenly side-to-side. 
- **Problem:** individual data points do not seem to follow a monotonically increasing and decreasing, but there are *dips* within the side-to-side range. This means that the timing delay (`delay(100)`) for individual data points is not that great. 
- Reducing delay using the current code will cause more data to be emitted. 
    - Perhaps we need to report averaged time?

{% enddetails %}


{% details Firmware sketch for windowed data collection %}

- Update `main.cpp` with the following:

```c
#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

#define WINDOW_SIZE 8 
#define BUFFER_MASK (WINDOW_SIZE - 1)

float buffer[WINDOW_SIZE];
int head = 0;
float running_sum = 0.0;
float average = 0.0;

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
  Serial.println("Ax");
}

void loop() {
  float ax, ay, az;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }
 
  running_sum -= buffer[head];
  buffer[head] = ax * ax;
  running_sum += buffer[head];
  head = (head + 1) & BUFFER_MASK;
  average = running_sum / WINDOW_SIZE;

  char line[10];
  snprintf(line,sizeof(line),"%.3f", average);
  Serial.println(line);
  delay(10);
}
```
- Compile and upload.
- In the updated source code, the following changes are made:
    - We implement a circular buffer using a fixed size array (`float buffer[WINDOW_SIZE]`) of size `WINDOW_SIZE`. 
        - Once the buffer is full, the data will be wrapped around in a circular fashion. 
    - `WINDOW_SIZE` should be a power of 2 to help quickly calculate wrap-around using bitwise operation (`head = (head + 1) & BUFFER_MASK;`).  
    - We don't care about whether it is negative or positive, but we want to magnify the effect: `running_sum += ax * ax;`
- Data points appear in a less fluctuating fashion, but it is still challenging to identify data segments that match up with the side-to-side movement. 

{% include figure.liquid path="assets/img/courses/csc574/full-cycle/01-raw-avg.png" max-width="15%" zoomable=true alt="Single entry data collection from sensors" %}


{% enddetails %}


## Stage 2: Data Engineering

The board is generating data now, and it *looks reasonable* via the serial monitor. However, for data engineering purpose, 
we need to have a better way of observing data. The next step is therefore to move data over to a PC via USB serial for visual and analytical purpose. 
- We will actually report both individual data points and the moving averages. 
- We will collect 1000 data points. With a 10ms per point, we will need to move the board side to side several times within a 10s window. 

### Firmware sketch for data transfer to PC

- Update `main.cpp` with the following:

```c
#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

#define WINDOW_SIZE 8 
#define BUFFER_MASK (WINDOW_SIZE - 1)

float buffer[WINDOW_SIZE];
int head = 0;
float running_sum = 0.0;
float average = 0.0;

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
  Serial.println("Ax");
}

void loop() {
  float ax, ay, az;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }
 
  running_sum -= buffer[head];
  buffer[head] = ax * ax;
  running_sum += buffer[head];
  head = (head + 1) & BUFFER_MASK;
  average = running_sum / WINDOW_SIZE;

  char line[10];
  snprintf(line,sizeof(line),"%.3f|%.3f", ax, average);  Serial.println(line);
  delay(10);
}
```

### Python Notebook

- Create a new notebook called `data_engineering.ipynb` with the `tinyml` kernel. 
- This notebook is similar to the `serial_plot.ipynb` notebook, but we only implement the cells that we need. 
- Serial port selection is further automated as follows:

```python
from serial.tools import list_ports
ports = list(list_ports.comports())

if not ports:
    print("No serial ports found. Check the USB cable, board connection, and drivers.")
else:
    for p in ports:
        print(f"{p.device:20s} | {p.description} | {p.hwid}")

PORT = [p for p in ports if p.description == "Nano 33 BLE"][0].device
BAUD_RATE = 9600
READ_TIMEOUT_SECONDS = 1

print(f"Using port: {PORT}")
```

- The next cell helps us setup a function to parse the serial data that was sent via the format specified in `main.cpp`. 
    - A small test is added at the end of this cell. 

```python
import time
from datetime import datetime

SENSOR_DATA = ["accel_x", "avg_accel_x"]
def parse_sensor_line(line: str): 
    line = line.strip()
    numbers = [float(x) for x in line.split("|")]

    data_point = {
        "timestamp": datetime.now().isoformat(timespec="milliseconds"),
        "raw": line,
        "accel_x": 0.0,
        "avg_accel_x": 0.0,
    }

    if len(numbers) >= 2:
        for name, value in zip(SENSOR_DATA, numbers[:2]):
            data_point[name] = value
    return data_point

# Quick parser test
test_line = "0.045|0.001"
parse_sensor_line(test_line)
```

- With the function, we can now collect data from the board for 10 seconds. 
    - Attempt to shake the board side to side suddenly several times during this period. 
    
```python
import pandas as pd
import serial

def collect_sensor_data(port: str=PORT, baud_rate: int=BAUD_RATE, seconds: int=10):
    points = []
    print(f"Opening {port} at {baud_rate} baud...")

    with serial.Serial(port, baud_rate, timeout=READ_TIMEOUT_SECONDS) as ser:
        time.sleep(2)
        ser.reset_input_buffer()

        print("Collecting data. Press the stop button in Jupyter to interrupt.")
        start = time.time()
        while time.time() - start < seconds:
            raw = ser.readline()
            if not raw:
                continue

            line = raw.decode("utf-8", errors="replace").strip()
            if not line:
                continue

            data_point = parse_sensor_line(line)
            data_point["elapsed_seconds"] = time.time() - start
            points.append(data_point)

    df = pd.DataFrame(points)
    print(f"Collected {len(df)} data points.")
    return df

df = collect_sensor_data(seconds=10)
df.head()
```

- We can visualize the collected data (in Pandas DataFrame format) as follows:

```python
import matplotlib.pyplot as plt
from IPython.display import clear_output, display

columns=("accel_x", "avg_accel_x")
plt.figure(figsize=(10, 5))
for col in columns:
    plt.plot(df["elapsed_seconds"], df[col], label=col)
plt.xlabel("Elapsed time (seconds)")
plt.ylabel("Sensor value")
plt.title("Live Nano 33 BLE Sensor Stream")
plt.legend(loc="upper right")
plt.grid(True)
plt.show()
```

- The outcome of this cell provide a much clearer visual of the detected movement. 

{% include figure.liquid path="assets/img/courses/csc574/full-cycle/03-data-visualization.png" max-width="50%" zoomable=true alt="Visualizing collected sensor data" %}


- From the above graph, our data labeling strategy is as follows:
    - The label represents the occurence of significant side-to-side sudden movement and has two possible values:
        - `Y`: There is side-to-side sudden movement.
        - `N`: There is no side-to-side sudden movement. 
    - If the moving average sensor value is higher than 0.1, we will label the data point `Y`. 
    - Otherwise, we will label the data point `N`. 

```python
import numpy as np

# 1. Define the list of conditional checks
conditions = [df["avg_accel_x"] >= 0.1, df["avg_accel_x"] < 0.1]

# 2. Define the corresponding labels for those conditions
labels = ["Y", "N"]

# 3. Apply numpy select
df["Label"] = np.select(conditions, labels, default="Unknown")
df.head(50)
```

- We drop the first 10 and the last 10 entries of the dataframe to account for possible initial connection discrepancies, then save the data. 

```python
from pathlib import Path

DATA_DIR = Path("data")
DATA_DIR.mkdir(parents=True, exist_ok=True)
output_file = DATA_DIR / "nano33ble_sensor_capture.csv"

df_cleaned = df.iloc[10:-10]
df_cleaned.to_csv(output_file, index=False)

print(f"Saved {len(df_cleaned)} rows to {output_file}")
```


## Stage 3: Model Development

 - With the data from Stage 2, we will now build a model to predict the side-to-side movement based on the moving average. 
 - This model is fairly simple, given our feature and label. 
 - Create a notebook called `model_development.ipynb`.

 ```python
import pandas as pd
from sklearn.model_selection import train_test_split
from pathlib import Path

DATA_DIR = Path("data")
input_file = DATA_DIR / "nano33ble_sensor_capture.csv"

FEATURE_COL = "avg_accel_x"
LABEL_COL = "Label"

df = pd.read_csv(input_file)
df[FEATURE_COL] = pd.to_numeric(df[FEATURE_COL], errors="coerce")

X_data = df[[FEATURE_COL]].to_numpy()  # Shaped as (N, 1) for the network
y_data = df[LABEL_COL].map({"Y": 1, "N": 0}).to_numpy() # Shape (N,) for binary classification and ensure it's numeric

X_train, X_test, y_train, y_test = train_test_split(X_data, y_data, test_size=0.20, random_state=42)

# Calculate normalization constants from training data
X_mean = X_train.mean()
X_std = X_train.std()

# Manually scale the training and testing sets
X_train_scaled = (X_train - X_mean) / X_std
X_test_scaled = (X_test - X_mean) / X_std

print(f"Scaling Parameters: Mean: {X_mean}, Std: {X_std}")
print(f"Training samples: {len(X_train)} | Testing samples: {len(X_test)}")
```

- In this first cell, we load the data from the previous stage and extract the feature column (`avg_accel_x`) and the label column (`Label`).
- These Pandas columns are turned into single dimension Numpy array object via the `.to_numpy()` calls. 
- Training and testing sets are created with `train_test_split`. 
- We scale the values of training and testing Xs to between 0 and 1, since the accelerometer can be up to between -4 and 4. 
    - These values are printed out to be used later. 
- Next, we build and train a model

```python
import tensorflow as tf

model = tf.keras.Sequential([
        tf.keras.layers.Input(shape=(1,)),  # Explicitly declare input shape for TFLite
        tf.keras.layers.Dense(8, activation="relu"),  
        tf.keras.layers.Dense(1, activation="sigmoid"),  # Sigmoid activation since this is a binary classification problem
    ]
)

model.compile(
    optimizer="adam", loss="binary_crossentropy", metrics=["accuracy"]
)

model.fit(X_train_scaled, y_train, 
    epochs=20, batch_size=16, 
    validation_data=(X_test_scaled, y_test)
)

```

- After playing around a bit with `batch_size` and number of neurons in the hidden layer, this is the best result that I have so far:

{% include figure.liquid path="assets/img/courses/csc574/full-cycle/03-data-visualization.png" max-width="50%" zoomable=true alt="Visualizing collected sensor data" %}

- Next, we export the trained model to file. 

```python
import pathlib

model_dir = pathlib.Path("./models")
model_dir.mkdir(parents=True, exist_ok=True)

converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]    

tflite_model = converter.convert()

tflite_model_file = model_dir/'model.tflite'     
tflite_model_file.write_bytes(tflite_model)
```

## Stage 4: Live Validation

- A major part of a full TinyML deployment workflow is the validation of the model on real time data before actual deployment. 
- Create a notebook called `model_validation.ipynb`. 
- First, we load the saved model

```python
import tensorflow as tf
import numpy as np
import matplotlib.pylab as plt
from ai_edge_litert.interpreter import Interpreter
from pathlib import Path


model_dir = Path("./models")
tflite_model_file = model_dir/'model.tflite'   

interpreter = Interpreter(model_path=str(tflite_model_file))
interpreter.allocate_tensors()

input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

input_index = input_details[0]["index"]
output_index = output_details[0]["index"]

input_shape = input_details[0]["shape"]
input_dtype = input_details[0]["dtype"]

print("Input shape expected by TFLite:", input_shape)
print("Input dtype expected by TFLite:", input_dtype)
print("Output shape:", output_details[0]["shape"])
```

- This cell let you know what input/output dimension you need to setup when receiving data from the board. 
- Next, we open a Serial connection and attempt to generate a prediction based on the collected data

```python
import serial
from serial.tools import list_ports
import time
from datetime import datetime
import pandas as pd

ports = list(list_ports.comports())

if not ports:
    print("No serial ports found. Check the USB cable, board connection, and drivers.")
else:
    for p in ports:
        print(f"{p.device:20s} | {p.description} | {p.hwid}")

PORT = [p for p in ports if p.description == "Nano 33 BLE"][0].device
BAUD_RATE = 9600
READ_TIME = 10
READ_TIMEOUT_SECONDS = 1

print(f"Using port: {PORT}")

points = []
print(f"Opening {PORT} at {BAUD_RATE} baud for {READ_TIME} seconds...")

with serial.Serial(PORT, BAUD_RATE, timeout=READ_TIMEOUT_SECONDS) as ser:
    time.sleep(2)
    ser.reset_input_buffer()

    print("Collecting data. Press the stop button in Jupyter to interrupt.")
    start = time.time()

    while time.time() - start < READ_TIME:
        raw = ser.readline()
        if not raw:
            continue

        line = raw.decode("utf-8", errors="replace").strip()
        if not line:
            continue
        numbers = [float(x) for x in line.split("|")]
        if len(numbers) < 2:
            print(f"Unexpected data format: '{line}'")
            continue
        input_np = np.array(numbers[1], dtype=input_dtype).reshape(input_shape)
        interpreter.set_tensor(input_index, input_np)
        interpreter.invoke()
        pred = 1 if interpreter.get_tensor(output_index)[0][0] > 0.5 else 0
        
        data_point = {"timestamp": datetime.now().isoformat(timespec="milliseconds"),
                      "raw": line,
                      "accel_x": numbers[0],   
                      "avg_accel_x": numbers[1],
                      "elapsed_seconds": time.time() - start,
                      "prediction": pred
        }
        points.append(data_point)
    df = pd.DataFrame(points)
    print(f"Collected {len(df)} data points.")

df.head(100)
```

- Most of this code is similar to that of the data engineering notebook, with the functions broken down and integrated into the cell for ease of reading. 
- More importantly is the four statements after `line` has been split into a list of `numbers`. 
    - We setup the input dimension, which is just the second element in `numbers` (the first element is the raw x sensor value). 
    - We setup the tensor for the interpret. 
    - We run the inference. 
    - We interprets the results using a 0.5 threshold. 
- We graph the `prediction` along with the `avg_accel_x` and `accel_x` values

```python
import matplotlib.pyplot as plt
from IPython.display import clear_output, display

columns=("accel_x", "avg_accel_x", "prediction")
plt.figure(figsize=(10, 5))
for col in columns:
    plt.plot(df["elapsed_seconds"], df[col], label=col)
plt.xlabel("Elapsed time (seconds)")
plt.ylabel("Sensor value")
plt.title("Live Nano 33 BLE Sensor Stream")
plt.legend(loc="upper right")
plt.grid(True)
plt.show()
```

{% include figure.liquid path="assets/img/courses/csc574/full-cycle/05-real-validation.png" max-width="50%" zoomable=true alt="Visualizing sensor data and predictions" %}

- The results are not exciting yet, we are only able to predict two out of five possible side-to-side events, but it is a start!
- At this point, you can go back and continue refining your model for a better real world validation. 

## Stage 5: Deployment

- Deploying the model onto the board requires two steps:
    - First, we are to convert the tflite model into tflite micro format as a byte array. 
    - Second, we are to setup the sketch so that it can use this byte array to perform on-board inference. 
- Create a notebook called `model_conversion.ipynb`

```python
from pathlib import Path

model_dir = Path("./models")
tflite_path = model_dir/'model.tflite'   
cc_path = model_dir/'model.cc'

data = pathlib.Path(tflite_path).read_bytes()

lines = []

for i in range(0, len(data), 12):
    chunk = data[i:i + 12]
    hex_values = ", ".join(f"0x{byte:02x}" for byte in chunk)
    lines.append(f"  {hex_values},\n")

pathlib.Path(cc_path).write_text("".join(lines), encoding="utf-8")
print(f"Wrote C array to {cc_path} with {len(data)} bytes of data.")

print("Wrote:", tflite_path, "to", cc_path)
print("C array size:", pathlib.Path(cc_path).stat().st_size, "bytes")
```

- We load and convert the TFLite model created in the previous notebooks. 
    - Pay attention to the C array size. 
- Print out the byte array to use in the firmware sketch later. 

```python
# Print the end of the generated C source file.
lines = Path(cc_path).read_text(encoding="utf-8").splitlines()
print("\n".join(lines))
```

- Create a new Arduino project called `Swerve` with the following `platform.ini` file

```bash
[env:nano33ble]
platform = nordicnrf52
board = nano33ble
framework = arduino
monitor_speed = 9600

lib_deps =
    arduino-libraries/ArduinoBLE
    arduino-libraries/Arduino_BMI270_BMM150
    tinymlx/Harvard_TinyMLx
```

- Create a file called `model.cpp` inside `src`
    - Copy the byte array above into the `model_data[]`
    - Update `model_data_len` with the C array size above

```cpp
unsigned char model_data[] = {
  BYTE ARRAY GOES HERE
};
unsigned int model_data_len = 11422;
```

- Create a file called `main.cpp` inside `src`
    - This file has codes from `main.cpp` inside `Swerve_data_collect`, as we will continue collecting the side-to-side IMU sensor value. 
    - Some values inside `main.cpp` such as the `traning_mean` and `training_std` came from the Jupyter notebooks developed earlier. 
    - We only have two `op_resolver` for our model, since the model use just a Dense layer (FullyConnected) and a Dense layer with sigmoid activation (Logistic). 
    

```cpp
#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

#include <TensorFlowLite.h>

#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

#define WINDOW_SIZE 8 
#define BUFFER_MASK (WINDOW_SIZE - 1)

float buffer[WINDOW_SIZE];
int head = 0;
float running_sum = 0.0;
float average = 0.0;
float scaled_average = 0.0;

/* From model_development.ipynb
  Scaling Parameters: Mean: 0.0636779359430605, Std: 0.126740584005968
*/

#define training_mean 0.0636779359430605
#define training_std 0.126740584005968
  
constexpr int kTensorArenaSize = 30 * 1024;
uint8_t tensor_arena[kTensorArenaSize];
  
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
  
constexpr int label_count = 2;
const char* labels[label_count] = {"Y", "N"};

extern const unsigned char model_data[];
extern const int model_data_len;

void setup() {
  // Start serial
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Started");

  // Start IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialized IMU!");
    while (1);
  }

  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  static tflite::MicroMutableOpResolver<2> micro_op_resolver;  // NOLINT
  micro_op_resolver.AddFullyConnected(); // Dense Layer
  micro_op_resolver.AddLogistic(); // Sigmoid is considered a logistic function

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, micro_op_resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  interpreter->AllocateTensors();

  // Get model input tensor
  TfLiteTensor* model_input = interpreter->input(0);

  /* From model_validation.ipynb: 
    Input shape expected by TFLite: [1 1]
    Input dtype expected by TFLite: <class 'numpy.float32'>
    Output shape: [1 1]
  */
  if ((model_input->dims->size != 2) ||
      (model_input->dims->data[0] != 1) ||
      (model_input->dims->data[1] != 1) ||
      (model_input->type != kTfLiteFloat32)) {
    TF_LITE_REPORT_ERROR(error_reporter,"Bad input tensor parameters in model");
    return;
  }
  TfLiteTensor* model_output = interpreter->output(0);
  if ((model_output->dims->size != 2) ||
      (model_output->dims->data[0] != 1) ||
      (model_output->dims->data[1] != 1) ||
      (model_output->type != kTfLiteFloat32)) {
    TF_LITE_REPORT_ERROR(error_reporter, "Bad output tensor parameters in model");
    return;
  }
}

void loop() {
  float ax, ay, az;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }
 
  running_sum -= buffer[head];
  buffer[head] = ax * ax;
  running_sum += buffer[head];
  head = (head + 1) & BUFFER_MASK;
  average = running_sum / WINDOW_SIZE;
  scaled_average = (average - training_mean) / training_std;

  // Pass to the model and run the interpreter
  TfLiteTensor* model_input = interpreter->input(0);
  model_input->data.f[0] = scaled_average;  
  
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed");
    return;
  }
  TfLiteTensor* output = interpreter->output(0);

  // Parse and interpret the model output

  float probability = output->data.f[0];
  const int predicted_class = (probability >= 0.5f) ? 1 : 0;

  char line[30];
  snprintf(line,sizeof(line),"%.3f|%.3f|%s", ax, average, predicted_class == 1 ? "Y" : "N");
  Serial.println(line);
  delay(10);
}
```

- After compile and upload the sketch, you can observe the prediction via `pio device monitor`. 
- The screenshot below show the prediction (`Y` or `N`) as the moving average is calculated. 

{% include figure.liquid path="assets/img/courses/csc574/full-cycle/06-deploy.png" max-width="50%" zoomable=true alt="On-board prediction" %}
