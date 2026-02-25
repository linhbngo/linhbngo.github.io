---
layout: lecture
pretty_table: true
collection: csc466
course: CSC 466: Distributed and Parallel Computing
title: "The demand for computational speed"
toc:
  - name: What is computational speed?
  - name: Why do we need this much speed?
---

# The demand for computational speed

## What is computational speed?

{% details How do we measure speed in computation? %}


- Floating-Point Operation per Second (FLOPS)
    - Count number of floating-point calculations (arithmetic operations) per second.
- Not MIPS (millions of instructions per second) as MIPS also count non-arithmetic
operations such as data movement or condition.  

$FLOPS = sockets \times \frac{cores}{socket} \times \frac{cycles}{second} \times \frac{FLOPS}{cycle}$  

- MFLOPS (megaFLOPS) = 1,000,000 FLOPS
- GFLOPS (gigaFLOPS) = 1,000,000,000 FLOPS


{% enddetails %}
{% details Modern measurement of speed %}

- TFLOPS (teraFLOPS) = 1,000,000,000,000 FLOPS
    - Intel's ASCI Red for Sandia National Laboratory (DOE) was the first supercomputer in the world 
    to achieve 1 TFLOPS in 1997. 
    - ASCI Red is used for large-scale simulation in nuclear weapon development and material analysis. 
- PFLOPS (petaFLOPS) = 1,000,000,000,000,000 FLOPS
    - IBM RoadRunner for Los Alamos National Laboratory (DOE) was the first supercomputer to achieve 
    1 PFLOPS in 2008. 
    - Oak Ridge National Laboratory’s Summit (DOE) is the second fastest supercomputer in the world at 
    148.6 PFLOPS.
    - Fugaku of RIKEN Center for Computational Science (Japan) is the current fastest supercomputer at 
    415 PFLOPS. 
- EFLOPS (exaFLOPS)  = 1,000,000,000,000,000,000 FLOPS
    - November 2024
        - Aurora:  1.9 EFLOPS, Argonne National Lab, Intel
        - Frontier: 2.0 EFLOPS, Oak Ridge National Lab, AMD
        - El Capitan: 2.7 EFLOPS, Lawrence Livermore National Lab, AMD
    - Tianhe 3 (first China Exascale computer, 2020, National University of Defense Technology)
        - China no longer participates in the TOP500 list reporting
    - Subsequent update to Fugaku (first Japan Exascale computer, 2026, RIKEN Center for Computational Science)
    - Europe's Jupiter, hosted at Julich Supercomputing Center, Germany, will be the first Exascale supercomputer 
    for Europe. 

{% enddetails %}
{% details The bragging list (The TOP500 Project) %}

- List the 500 most powerful computers in the world.
- Count FLOPS by having supercomputer runs well-known computationally intensive tasks
    - Solve $Ax=b$, dense random matrix problem. 
    - Primarily dense matrix-matrix multiplications. 
- Updated twice a year:
    - International Supercomputing conference (June, Germany)
    - Supercomputing conference (November, US). 
- Website: http://www.top500.org


{% enddetails %}
## Why do we need this much speed?

{% details Modern scientific discovery %}

- The four modern paradigms of science
    - Theory
    - Experiment
    - Simulation
    - Data analysis
- Simulation: study things that are too big, too small, too fast, too slow, too expensive, or too dangerous. 
- Data analysis: study data that are too big, too complex, too fast (streaming data), too noisy. 



{% enddetails %}
{% details Faster computer gives more details %}


<iframe width="560" height="315" src="https://www.youtube.com/embed/cNyftYdjt-Q" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>



{% enddetails %}
{% details Hurricane Sandy (2012) %}


- the deadliest and most destructive, as well as the strongest hurricane of the 2012 Atlantic hurricane season, 
- the second-costliest hurricane on record in the United States (nearly $70 billion in damage in 2012),
- affected 24 states, with particularly severe damage in New Jersey and New York,
- hit New York City on October 29, flooding streets, tunnels and subway lines and cutting power in and around the city.

{% include figure.liquid path="assets/img/courses/csc466/01-introduction/sandy.png" width="50%" zoomable=true alt="Forecast of hurricane sandy on October 26, 2012" %}

{% enddetails %}
{% details Various forecasts of Sandy %}


{% include figure.liquid path="assets/img/courses/csc466/01-introduction/computer_models_sandy.png" width="50%" zoomable=true alt="Various predictions model for Sandy" %}

- Geophysical Fluid Dynamic Laboratory hurricane model (National Oceanic and Atmospheric Administration)
- Hurricane Weather Research and Forecasting model (NOAA/Naval Research Laboratory/Florida State University)
- European Centre for Medium Range Weather Forecast model (ECMWF)
- Global Forecast Model (National Weather Service) 
- **Which model is closest to reality?**


{% enddetails %}
{% details One of the contributing factors %}


{% include figure.liquid path="assets/img/courses/csc466/01-introduction/weathercomputernw.gif" width="50%" zoomable=true alt="Computational power for weather forecast in 2013" %}

- *http://blogs.agu.org/wildwildscience/2013/02/17/seriously-behind-the-numerical-weather-prediction-gap/*



{% enddetails %}
{% details The US has caught up %}


- [NOAA Weather Computer upgrade](http://www.noaa.gov/noaa-completes-weather-and-climate-supercomputer-upgrades)
- Two new supercomputers, Luna and Surge
- 2.89 PFLOPS each for a total of 5.78 PFLOPS (previous generation is only 776 TFLOPS)
- Increase water quantity forecast from 4000 locations to 2.7 million locations (700-fold increase in spatial density)
- Can track and forecast 8 storms at any given time
- 44.5 million dollars investment


{% enddetails %}
{% details Covid and HPC %}


- US HPC Consortium to contribute to Covid research
    - [Toward explaining signs of COVID symptoms](https://www.hpcwire.com/2020/07/28/supercomputer-powered-research-uncovers-signs-of-bradykinin-storm-that-may-explain-covid-19-symptoms/)
- Many other work (published in Nature) include supercomputing usages for molecular dynamic simulation/data analysis. 


{% enddetails %}
{% details Manufacturing and HPC %}


- For 767 development, Boeing built and tested 77 physical prototypes for wing design. 
- For 787 development, only 11 prototypes were built.
    - Optimized via more than 800,000 hours of computer simulation. 

{% enddetails %}
{% details Oil and Gas Exploration improvement with HPC %}


- Los Alamos National Lab
- Development of large-scale data analytic techniques to simulate and predict subsurface fluid distribution, temperature, and pressure
- This reduces the need for observation wells (has demonstrated commercial success)


{% enddetails %}
{% details Fraud Detection at PayPal %}


- 10M+ logins, 13M+ transactions, 300 variables per events
- ~4B inserts, ~8B selects
- MPI-like applications, Lustre Parallel File Systems, Hadoop
Saved over $700M in fraudulent transactions during first year of deployment


{% enddetails %}
