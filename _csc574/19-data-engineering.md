---
layout: lecture
pretty_table: true
collection: csc574
title: "Data Engineering"
toc:
  - name: Overview
  - name: Key steps in a data engineering process
  - name: Data Engineering for Key Word Spotting
---
# Data Engineering

## Overview

{% details note What is data engineering %}

- A supervised AI is trained on a corpus of training data

{% include figure.liquid path="assets/img/courses/csc574/data-engineering/01.png" width="50%" zoomable=true %}

- Data engineering in AI is all about datasets

{% enddetails %}
{% details note Good data is necessary for accuracy %}


{% details note What problem are you trying to solve %}

- Your data must contain useful features
- Can a human (expert) distinguish between examples of each class?
- How will you measure performance?

{% enddetails %}
{% details note Both quantity and quality wil influence your model's performance %}

- Wide distribution of training examples
- Accurate labels
- Sufficient class balance

{% enddetails %}
{% enddetails %}
## Key steps in a data engineering process

{% details note Requirements %}

- Problem definition
- Machine and human usable format
- **Permissions and rights**

{% details Question: Permissions and rights %}

- Where does your data **originate**?
    - Open?
    - Copyrighted?
    - Licensed?
    - Product users?

- What's yurs and what's **NOT** yours

{% include figure.liquid path="assets/img/courses/csc574/data-engineering/02.png" width="50%" zoomable=true %}

- Licenses:
    - Apache
    - BSD
    - Creative Commons

{% enddetails %}
{% enddetails %}
{% details note Gathering %}

- People
- Collection
- Labeling
- **Data sources**
    - Sensors
    - Crowdsourcing
    - Product users
    - Paid contributors

{% enddetails %}
{% details note Refinement %}

- Processing
- Augmentation
- **Validation**

{% details Question: Validation %}

- Some data is unusable
    - How will you **verify** the data you collected?
        - Manually (time, cost)
        - Automation
        - Domain expertise
            - disputes/disagreements?

{% enddetails %}
{% enddetails %}
{% details note Sustainment %}

- Storage
- Security
- Errors
- **Versioning**

{% details Question: Versioning %}

- Your dataset will evolve
    - Augment missing data
    - Expand user-base


{% enddetails %}
{% enddetails %}
{% details note Datasets require significant effort %}

- These massive ML datasets are constructed by hand
    - Common Voice: 5000+ hours of spoken audio
    - Common Objects in Context (COCO): 2.5M+ labeled images
    - ImageNet: 4M+ labeled images
    - Waymo: 1950 20-seond driving segments
    - KITTI 360: 73KM+ of annotated driving data
- How to build your own dataset?

{% enddetails %}
## Data Engineering for Key Word Spotting

{% details note Reminder: the data engineering process %}


{% include figure.liquid path="assets/img/courses/csc574/data-engineering/03.png" width="50%" zoomable=true %}

- [Speech Commands: A Dataset for Limited-Vocabulary Speech Recognition](https://arxiv.org/pdf/1804.03209)


{% enddetails %}
{% details note Requirements %}

- Collecting data based on usage

{% include figure.liquid path="assets/img/courses/csc574/data-engineering/04.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Gathering: Data Collection %}


- **2,618** volunteers
    - consented to have their voices redistributed
    - variety of accents
- More than 1000 samples for each keyword
- **Browser-based** recording

{% include figure.liquid path="assets/img/courses/csc574/data-engineering/05.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Refinement: Data Validation %}

- Some data is unusable
    - Too quiet, wrong word
- Started with automated tools
    - Remove low volume recordings
    - Extract loudest 1s (from 1.5s examples)
- All 1105,829 remaiing utterances mannually reviewed through crowdsourcing

{% enddetails %}
{% details note Sustainment %}

- Sources of bias

{% include figure.liquid path="assets/img/courses/csc574/data-engineering/06.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Collecting your custom dataset %}

- Requirements
    - How much data is needed?
    - What are accepteable false positive and false negative rates?
    - What are the impact of errors?
- Gathering
    - What are possible recording issues?
        - Too short or clipped utterances
        - Too quiet
    - Can we augment this with background noises?
        - Kitchen
        - Car
        - TV/Radio in the background
        - Crowded room

{% enddetails %}
{% details note Building your own dataset %}


{% details warning Plan B %}

- Use [Harvard's Open Speech Recording Link](https://tinyml.seas.harvard.edu/open_speech_recording/)
- Only use this if you are not able to setup the recording app locally. 

{% enddetails %}
{% details note Setup local recording app %}

- Run the following to setup and deploy the recording app
- For Windows users, replace `export` with `set`

```bash
git clone https://github.com/ngo-classes/open-speech-recording.git
cd open-speech-recording
git submodule update --init --recursive
pip install flask
export FLASK_APP=main.py
python -m flask run
```

- Visit **http://127.0.0.1:5000** on an **incognito browser window**

{% include figure.liquid path="assets/img/courses/csc574/data-engineering/07.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Collecting data %}


- Edit Box 1 to include the words you want to use
- Edit Box 2 to include the number of samples of each word
- Press Record to start the recording process

{% include figure.liquid path="assets/img/courses/csc574/data-engineering/08.png" width="50%" zoomable=true %}   

- **Practice a few times so that you can time the recording just right (red/gray record button)**

{% include figure.liquid path="assets/img/courses/csc574/data-engineering/09.png" width="50%" zoomable=true %}

- Press OK to download the data

{% include figure.liquid path="assets/img/courses/csc574/data-engineering/10.png" width="50%" zoomable=true %}

- Data are download as **.ogg** format inside the same directory

{% include figure.liquid path="assets/img/courses/csc574/data-engineering/11.png" width="50%" zoomable=true %}

{% enddetails %}
{% details note Clean up, convert, and retrain model (Google Colab) %}

[Open the following notebook](https://colab.research.google.com/drive/1kLWYUsF61jOIlbIspeQgR71Ig35zpicw?usp=sharing)
{% enddetails %}
{% enddetails %}
