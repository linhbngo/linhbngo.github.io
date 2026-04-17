---
layout: lecture
pretty_table: true
collection: csc466

title: "Pleasantly parallel and workload allocation"
toc:
  - name: Overview
  - name: Accessing PSC
  - name: Workload assignment
---

# Pleasantly parallel and workload allocation

## Overview

{% details Definition %}


- Embarrassingly/naturally/pleasantly parallel. 
- A computation that can obviously be divided into a 
number of completely different parts, each of which can be 
executed by a separate process. 
- Each process can do its tasks without any interaction with 
the other processes, therefore, ...
    - No communication or very little communication among the processes.

{% enddetails %}
{% details Example: integral estimation using the trapezoid method %}


- A technique to approximate the integral of a function `f`.  
- Integral is defined as the area of the region bounded by the graph
`f`, the x-axis, and two vertical lines `x=a` and `x=b`. 
- We can estimate this area by dividing it into infinitesimal trapezoids.

{% include figure.liquid path="assets/img/courses/csc466/pleasantly-parallel/trapezoids.png" width="50%" zoomable=true alt="Trapezoid example" %}

- Divide the area under the curve into 8 trapezoids with equal base `h`. 
    - `N` = 8
    - `a` = 0
    - `b` = 2
- The base `h` can be calculated as: 
    - `h` = (`b` - `a`) / `N` = 0.25
- Which trapezoid (workload/task) goes to which process?
    - Start with small number of processes.
    - Calculation workload assignment manually for each count of processes.
    - Generalize assignment for process i based on sample calculations.

{% include figure.liquid path="assets/img/courses/csc466/pleasantly-parallel/trapezoids-processes.png" width="50%" zoomable=true alt="Trapezoid example with process division" %}

- 4 processes: `P0`, `P1`, `P2`, `P3`: `size` = 4
- `N` = 8
- `a` = 0
- `b` = 2
- The height `h` can be calculated as: 
    - `h` = (`b` - `a`) / `N` = 0.25
- The amount of trapezoid per process: 
    - `local_n` = `N` / `size` = 2;
- `local_a`: variable represent the starting point of the local interval
for each process. Variable `local_a` will change as processes finish 
calculating one trapezoid and moving to another. 
    - `local_a` for `P0`= 0 = 0 + 0 * 2 * 0.25
    - `local_a` for `P1`= 0.5 = 0 + 1 * 2 * 0.25
    - `local_a` for `P2`= 1 = 0 + 2 * 2 * 0.25
    - `local_a` for `P2`= 1.5 = 0 + 3 * 2 * 0.25

{% enddetails %}
{% details MPI implementation of trapezoid %}


<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=trapezoid.c"></script>

- Compile and run `trapezoid.c`:

~~~bash
mpicc -o trapezoid trapezoid.c
mpirun --host compute01:2,compute02:2 -np 4 ./trapezoid 0 1 10
mpirun --host compute01:2,compute02:2 -np 4 ./trapezoid 0 1 100
mpirun --host compute01:2,compute02:2 -np 4 ./trapezoid 0 1 1000
mpirun --host compute01:2,compute02:2 -np 4 ./trapezoid 0 1 10000
~~~

{% enddetails %}
## Accessing PSC

{% details Set up jobs on Pittsburg Supercomputing Center %}

- Access the [OnDemand online interface](https://ondemand.bridges2.psc.edu) of Pittsburgh Supercomputing Center. 
- Click on the home directory card.
- Go to `Ocean`/`projects`/`cis250077p`/*YOUR_PSC_USERNAME*
- Create a directory called `intro-mpi` using the `New Directory` button. 

{% enddetails %}
{% details Creating MPI file %}

- Click `+ New File`, and type in `trapezoid.c`
- Next to the file name, click on the three dot and then click `Edit`. 
- Copy the content of the trapezoid.c file above into the Edit windows. 
- Click `Save` to save the file. 
- Close the `Edit` browser tab. 
- If you click on the `Refresh` button (next to `New File`), you will see the updated size of trapezoid.c

{% enddetails %}
{% details Create submission file %}

- Click `+ New File`, and type in `trapezoid.sh`
- Next to the file name, click on the three dot and then click `Edit`. 
- Enter the following contents

```bash linenums="1"
#!/bin/bash
#SBATCH -N 1
#SBATCH -p RM
#SBATCH -t 1:00:00
#SBATCH --ntasks-per-node=128

# type 'man sbatch' for more information and options
# this job will ask for 1 full RM node (128 cores) for 1 hours
# this job would potentially charge 128 RM SUs

#echo commands to stdout
set -x

# move to working directory
# this job assumes:
# - all input data is stored in this directory
# - all output should be stored in this directory
# - please note that groupname should be replaced by your groupname
# - PSC-username should be replaced by your PSC username
# - path-to-directory should be replaced by the path to your directory where the executable is

echo ${PROJECT}
cd ${PROJECT}/intro-mpi

module load openmpi/4.1.1-gcc8.3.1

mpicc -o trapezoid trapezoid.c
mpirun -np 1 ./trapezoid 0 10 10000000000
mpirun -np 2 ./trapezoid 0 10 10000000000
mpirun -np 4 ./trapezoid 0 10 10000000000
mpirun -np 8 ./trapezoid 0 10 10000000000
mpirun -np 16 ./trapezoid 0 10 10000000000
mpirun -np 32 ./trapezoid 0 10 10000000000
```

- Click `Save` to save the file. 
- Close the `Edit` browser tab.

{% enddetails %}
{% details Submit and run %}

- From the main Dashboard, click `Bridges-2 Shell Access`
- Type in your PSC password to log in the in-browser terminal. 
- Run the followings:

```bash
cd ${PROJECT}/intro-mpi
dos2unix trapezoid.sh
sbatch trapezoid.sh
squeue -u $USER
```

- Observer your job in the queue. 
- Go back to the File Browser and study the slurm output file. 

{% enddetails %}
## Workload assignment

{% details Static workload assignment %}


{% include figure.liquid path="assets/img/courses/csc466/pleasantly-parallel/mandelbrot_static.png" width="50%" zoomable=true alt="Static workload assignment visualization via mandelbrot" %}

- Is this fair?
- On PSC, create a copy of `trapezoid.c` called `trapezoid_static.c` and modify `trapezoid_static.c`
to have the following contents

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=trapezoid_static.c"></script>

- Modify your submission script to compile and run `trapezoid_static.c`.
    - What do you observe?
- This is called `static workload assignment`. 

{% enddetails %}
{% details Cyclic workload assignment %}


{% include figure.liquid path="assets/img/courses/csc466/pleasantly-parallel/mandelbrot_cyclic.png" width="50%" zoomable=true alt="Cyclic workload assignment visualization via mandelbro" %}

- On PSC, create a copy of `trapezoid_static.c` called `trapezoid_cyclic.c` and modify `trapezoid_cyclic.c` 
to have the following contents

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=trapezoid_cyclic.c"></script>

- Modify your submission script to compile and run `trapezoid_cyclic.c`:
    - What do you observe?
- This is called `cyclic workload assignment`. 

{% enddetails %}
{% details Dynamic workload assignment %}


{% include figure.liquid path="assets/img/courses/csc466/pleasantly-parallel/mandelbrot_dynamic.png" width="50%" zoomable=true alt="Dynamic workload assignment visualization via mandelbro" %}

- Create a file called `trapezoid_dynamic_.c` with the following contents:

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=trapezoid_dynamic.c"></script>

    - Modify your submission script to compile and run `trapezoid_dynamic.c`:
    - What do you observe?

- This is called `dynamic workload assignment`. 





{% enddetails %}
