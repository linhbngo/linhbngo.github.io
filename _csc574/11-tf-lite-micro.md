---
layout: lecture
pretty_table: true
collection: csc574
title: "Tensorflow Lite Micro"
toc:
  - name: Overview
  - name: How to use TFL Micro
  - name: Key structures of TFL Micro
---
# Tensorflow Lite Micro

## Overview

{% details note What is TensorFlow Lite Micro %}

- TensorFlow: Deep learning framework
    - ~400MB in size on average
    - ~1-2G in random memory
- TensorFlow Lite (TensorFlow Mobile)
    - ~1MB in size (binary)
    - still not enough
- TensorFlow Lite Micro (TFL Micro)
    - extreme compression of TF Lite
    - Core runtime size is ~16KB

{% enddetails %}
{% details note Constraints of TF Lite Micro %}


{% include figure.liquid path="assets/img/courses/csc574/tf-lite-micro/limits.png" max-width="50%" zoomable=true %}

{% details note Hardware %}

- Tought requirements (power, cost, form factor, performance) for embedded
systems result in diverse sets of hardware products with different tradeoffs. 
    - Therefore, the framework has to be radically portable, able to 
    compile and run with no errors across a wide range of computer architectures.
    - There has to be an easy way to optimizing code for each type of platform. 
- Tough requirements also result in small amount of memory and low clock rates. 

{% enddetails %}
{% details note Software %}

- The constraints of embedded requirements also extend to the system software that's available.
    - Lack of heap and dynamic memory allocation on embedded systems
    - Memory allocation has to be explicit and carefully done. 
- Lack of operating system/OS support. 


{% enddetails %}
- Result: 
    - TFL Micro can run across a wide variety of different boards
    with very little memory and no operating system facilities. 
    - TFL Micro focuses on memory size optimization, avoiding dynamic memory allocation, using a very minimal set of standard library functions,
    and keeping its code as portable as possible.
{% enddetails %}
## How to use TFL Micro

{% details note Overview %}


{% include figure.liquid path="assets/img/courses/csc574/tf-lite-micro/usage.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% details note Example: hello, world %}


- File/Examples/Harvard_TinyMLx/hello_world
    - hello_world.ino
    - arduino_constants.cpp
    - arduino_main.cpp
    - arduino_output_handler.cpp
    - constants.h
    - main_functions.h
    - model.cpp
    - model.h
    - output_handler.h
- `hello_world.ino`
    - General idea: takes an input value and calculates 
    an estimate of the sine function on that value.
        - Emulating: input, interpreter, output
        - Physical output (LED) depends on outpt. 
- Main operation happens in `loop`

{% enddetails %}
## Key structures of TFL Micro

{% details note Interpreter %}

{% include figure.liquid path="assets/img/courses/csc574/tf-lite-micro/interpreter.gif" max-width="50%" zoomable=true %}

- TFL Micro uses an interpreter design
    - Store the model as data and loop through its ops at runtime

- On Desktop, compiler is generally faster than interpreted code (see Python vs. C/C++)

{% include figure.liquid path="assets/img/courses/csc574/tf-lite-micro/compiler.png" max-width="50%" zoomable=true %}

- However, for Machine Learning task, it is different.
    - Each layer like Conv or Softwmax can take tens of thousands 
    or even millions of cycles to complete execution. 
- How to implement an interpreted model
    - The model itself contains a list of operators and arguments
    - The interpreter looks through this list of runtime and calls
    the appropriate operator implementations or kernels. 

    ```c
    if (op_type == CONV2D) {
        Convolution2d(conv_size, input, output, weights);
    } else if (op_type == FULLY_CONNECTED) {
        FullyConnected(input, output, weights);
    }
    ```

{% enddetails %}
{% details note Model Format and FlatBuffer %}

- Interpreters needs operators, weights, etc to run a model
- How is this information stored?

```c
model = tflite::GetModel(g_model);
if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                        "Model provided is schema version %d not equal "
                        "to supported version %d.",
                        model->version(), TFLITE_SCHEMA_VERSION);
    return;
}
```

- In `hello_world`: `g_model` is declared in `model.cpp`
    - Is an array of bytes, and act as the equivalent of a file on disk (but is actually stored in memory)
    - Holds all of the information about the model: its operators, their connections, and the trained weights. 

- From Python, `g_model` is originally a data structure. 
    - Serialization turns a data structure into a form that can be stored as an array of bytes, 
    and then understood by many other languages.
    - Other ways of serializing data,
        - JSON
        - ProtoBuf
        - FlatBuffer

    {% include figure.liquid path="assets/img/courses/csc574/tf-lite-micro/serialization.png" max-width="50%" zoomable=true %}

- TFL Micro uses FlatBuffers due to:
    - Memory efficiency
    - Does not require copies to be made before using the data inside the model
    - Works without requiring any unpacking
    - The format is formally specified as a schema file, which then can be used 
    to automatically generate code to access the information in the model byte array. 

{% enddetails %}
{% details note Hands-on: FlatBuffers %}

- [Colab Research Notebook](https://colab.research.google.com/drive/1C626YCyQnN3OfwNoZyXj5zdrR_Isp6qu?usp=sharing)


{% enddetails %}
{% details note Memory allocation: Tensor Arena %}

- Easy to hit memory limits on embedded systems: need control over memory usage. 
- Embedded devices are expected to run over months or years
    - Challenges for memory allocations
    - Needs guarantee on having no fragmentation due to contiguous memory allocation over time:
        - No dynamic memory allocation at all!
- No OS support: no `malloc` and `new`.
- Solution:
    - A predefined contiguous area of memory is given to the interpreter, and no other memory 
    allocation is requested in the future. 
    - Framework guarantees that this area is reserved and not allocated from (prevent fragmentation).
    - No dependency on `malloc` or `new`. 

- `hello_world`: global namespace declaration

```c
constexpr int kTensorArenaSize = 2000;
uint8_t tensor_arena[kTensorArenaSize];
```

{% include figure.liquid path="assets/img/courses/csc574/tf-lite-micro/tensor_arena.png" max-width="50%" zoomable=true %}

- How to determine area size?
    - It depends!
    - Depends on what ops are in model, their sizes, and the sizes of the operator inputs and outputs platform. 
- Solution:
    - Create as large an arena as possible, 
    - Use `arena_used_bytes()` to get the actual size used. 
    - Resize/rebuild/retest. 

{% enddetails %}
{% details note OpResolver %}

- TF library:
    - ~1400 and growing number of operators in TF
    - Not all are used or even needed for inference

{% include figure.liquid path="assets/img/courses/csc574/tf-lite-micro/op_resolvers_all.png" max-width="50%" zoomable=true %}

- Help reduce the amount of space that library code takes up:
    - Not all operators are used or
    - Only load operations that are absolutely necessary.

{% include figure.liquid path="assets/img/courses/csc574/tf-lite-micro/op_resolvers.png" max-width="50%" zoomable=true %}

- Allow developers to specify which ops they want to be included in the library

{% include figure.liquid path="assets/img/courses/csc574/tf-lite-micro/simple_kws.png" max-width="50%" zoomable=true %}

- How to know: [https://netron.app](https://netron.app/)
- You can also load everything if memory is not an issue!

```c
static tflite::AllOpsResolver resolver;
```



{% enddetails %}
