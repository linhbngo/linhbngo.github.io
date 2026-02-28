---
layout: lecture
pretty_table: true
collection: csc574
title: "Deployment of KWS"
toc:
  - name: Overview
  - name: Initialization
  - name: Pre-processing
  - name: Inference
  - name: Post-processing
  - name: Deployment
---
# Deployment of KWS

## Overview

{% details note Keyword Spotting Components %}

{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/kws-components.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Arduino Example %}

- - File/Examples/Harvard_TinyMLx/micro_speech

{% enddetails %}
## Initialization

{% details note Overview %}

- General steps that need to be done for any ML application deployment

{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/initialization.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Steps %}

- Declare variables
    - `micro_speech.ino`
        - `namespace`
        - TFL-related variables
        - Tensor Arena Size
        - ...
- Load model
    - `micro_features_model.cpp`
        - Byte array describing the model
    - `micro_speech.ino`
        - `setup()`
        - Load model into a `model` variable
- Resolve Operators
    - `micro_speech.ino`
        - `setup()`
        - Use `AddOPERATOR` with `OPERATOR` is the name of the operator to be added. 
        - [List of default Ops](https://github.com/tensorflow/tflite-micro/blob/main/tensorflow/lite/micro/micro_mutable_op_resolver.h)
- Allocate/instantiate the Interpreter
    - `micro_speech.ino`
        - `setup()`
- Allocate memory for the TensorArena
    - `micro_speech.ino`
        - `setup()`
- Define model inputs
    - `micro_speech.ino`
        - `setup()`
    - `model_input->dims->size`
        - See `kws-training-...` notebook. 
        - `model_input` is the `FLATTENED_SPECTROGRAM_SHAPE`
        - The input has two dimensions, and the first one is simply a wrapper with value of 1 (flattened)
        - The second dimension is the size of the spectrogram (see the kws-training notebook)
            - `FEATURE_BIN_COUNT = 40`: 40
            - `OVERLAPPING_WINDOWS = window_counter(CLIP_DURATION_MS, int(WINDOW_SIZE_MS), WINDOW_STRIDE)`: 49
        - `micro_features_micro_model_settings.h`
            - `constexpr int kFeatureSliceSize = 40;`
            - `constexpr int kFeatureSliceCount = 49;`
            - `FEATURE_BIN_COUNT`: kFeatureSliceSize
            - `OVERLAPPING_WINDOWS`: kFeatureSliceCount 
- Setup Main loop
    - `micro_speech.ino`
        - `setup()`
    - Setting up the feature provider: `static_feature_provider`
        - Accesses the audio buffer and generates spectrograms.
    - After inference, we go to recognize command: `static_recognizer`
        - Recognize commands based on inference results and facilitate device responses. 

{% enddetails %}
## Pre-processing

{% details note Overview %}

- `micro_speech.ino`
    - `void loop()`

{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/preprocessing_1.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Audio provider %}


{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/audio_provide_1.png" width="50%" zoomable=true %}

-  Continuously get audio signals in from the microphone on the Arduino
and convert that into a digital representation that can then be converted into a 
`spectrogram` that is consumed by neural network.
- `void loop()`/`PopulateFeatureData`: right click then go to definition
    - goal: get the audio samples in a spectrogram format.
    - Previous time is the last time PopulateFeatureData is called.
    - Current time is the actual time that records as of right now.
    - Identify (old) slices to drop.
    - Identify new slices to calculate information.
- `GetAudioSamples`
    - `InitAudioRecording`/`CaptureSamples`

{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/audio_provide_2.png" width="50%" zoomable=true %}


{% enddetails %}
{% details note Feature Extractor %}

- `GenerateMicroFeatures`
    - Unlikely need to be modified. 
- Perform FFT transform on audio sample data then generate the MFCC and extract the 
spectrogram data. 

{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/feature_extractor.png" width="50%" zoomable=true %}

{% enddetails %}
## Inference

{% details note Recall: MNIST data %}

{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/interpreter_mnist.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Spectrogram data %}

{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/interpreter_spectrogram.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Inference process %}


- Copy collected audio data into feature buffer
    - Manual loop (no fancy `memcopy`!)
- Invoke interpreter

{% enddetails %}
## Post-processing

{% details note Overview %}


{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/postprocessing_1.png" width="50%" zoomable=true %}

- Potential problems:

{% details note Is it Up? %}

{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/postprocessing_3.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Or is it Upward? %}

{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/postprocessing_2.png" width="50%" zoomable=true %}

{% enddetails %}
{% enddetails %}
{% details note Process Latest Results %}

- A solution to the false positive problem

{% include figure.liquid path="assets/img/courses/csc574/kws-deploy/postprocessing_4.png" width="50%" zoomable=true %}

- `micro_speech.ino`
    - `void loop()`:`recognizer->ProcessLatestResults`
- Calculate confidence score

{% enddetails %}
{% details note Respond to Command %}

- `micro_speech.ino`
    - `void loop()`:`RespondToCommand`
- Configure Lights
- Use `TF_LITE_REPORT_ERROR` to print out logs

{% enddetails %}
## Deployment

{% details note Preparation %}

-  Make sure that you used [https://netron.app](https://netron.app/) to identify and modify the Ops
-  Use the [Pretrained Notebook](https://colab.research.google.com/drive/1dvyTr0Tz3FgDXSRIlpivl0jY0KYrydFr?usp=sharing) to convert the tflite model file into `.cc` format. 
-  Open and copy the `.cc` format to replace the byte array of the model in `micro_speech`. 
- Save `micro_speech` as a new project on Arduino. 





{% enddetails %}
