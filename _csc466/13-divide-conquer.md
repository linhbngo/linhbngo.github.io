---
layout: lecture
pretty_table: true
collection: csc466

title: "Partitioning: Divide and Conquer"
toc:
  - name: Overview
  - name: Bucket Sort
  - name: Complex Parallel Bucket Sort
  - name: N-Body Problem
---
# Partitioning: Divide and Conquer

{% details Final Exam %}

- Final Exam: May 7, 1:00PM - 3:00PM

{% enddetails %}
## Overview

{% details Partitioning %}


Partitioning simply divides the problem into parts and then compute the parts 
and combine results.

- The basis of all parallel programming, in one form or another. 
- Pleasantly parallel used partitioning without any interaction between the parts.
- Most partitioning  formulation require the results of the parts to be combined 
to obtain the desired results. 
- Partitioning can be applied to the program data. 
    - This is call data partitioning or domain decomposition.
- Partitioning can also be applied to the functions of a program. 
    - This is called functional decomposition. 

{% enddetails %}
{% details Divide and Conquer %}


- Characterized by dividing problem into sub-problems of same form as larger 
problem. Further divisions into still smaller sub-problems, usually done by recursion.
- Recursive divide and conquer amenable to parallelization because separate processes 
can be used for divided pairs. Also usually data is naturally localized.

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/dc01.png" width="50%" zoomable=true alt="Divide process" %}

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/divide.png" width="50%" zoomable=true alt="Divide process with process ID" %}


{% enddetails %}
{% details Divide %}


Create a file called `divide.c`

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=divide.c"></script>

- Compile and run

~~~bash
mpicc -lm -o divide divide.c
mpirun -np 8 divide
~~~

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/divide_mpi.png" width="50%" zoomable=true alt="Run divide" %}

{% enddetails %}
{% details Conquer %}


- Create a file called `conquer.c`

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=conquer.c"></script>

~~~bash
mpicc -lm -o conquer conquer.c
mpirun -np 8 conquer
~~~

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/conquer_mpi.png" width="50%" zoomable=true alt="Run conquer" %}


**Many sorting algorithms can be parallelized by partitioning using divide and conquer**

{% enddetails %}
## Bucket Sort

{% details Overview %}


{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/bucketsort1.png" width="50%" zoomable=true alt="Overview of Bucket Sort" %}


{% enddetails %}
{% details Simple approach %}


{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/bucketsort2.png" width="50%" zoomable=true alt="A simple approach to Bucket Sort" %}

- Broadcast data
- Sort only those elements that fit in local interval bucket (determined by rank)
- Gather sorted bucket

{% enddetails %}
{% details Scatter and Scatterv Syntax %}


~~~c
int MPI_Scatter(
    void *sendbuf, 
    int sendcount, 
    MPI_Datatype sendtype, 
    void *recvbuf,
    int recvcnt,
    MPI_Datatype recvtype,
    int root, 
    MPI_Comm comm);
~~~

~~~c
int MPI_Scatterv(
  void *sendbuf,
  int *sendcount,
  int *displs,
  MPI_Datatype sendtype,
  void *recvbuf,
  int recvcnt,
  MPI_Datatype recvtype,
  int root,
  MPI_Comm comm
);
~~~

- `sendbuf`: address of send buffer (choice, significant only at root)
- `sendcount`: integer array (of length group size) specifying the number of elements to send to each processor
- `displs`: integer array (of length group size). Entry i specifies the displacement (relative to sendbuf from which to take the outgoing data to process i
- `sendtype`: data type of send buffer elements
- `recvbuf`: address of receive buffer (choice)
- `recvcnt`: number of elements in receive buffer (integer)
- `recvtype`: data type of receive buffer elements 
- `root`: rank of sending process (integer)
- `comm`: communicator

{% enddetails %}
{% details Hands-on: Scatterv %}


<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=scatterv.c"></script>

~~~bash
mpicc -o scatterv scatterv.c
mpirun -np 4 scatterv
~~~

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/scatterv.png" width="50%" zoomable=true alt="Run Scatterv" %}


{% enddetails %}
{% details Gather and Gatherv Syntax %}


~~~c
int MPI_Gather(
    void *sendbuff, 
    int sendcount, 
    MPI_Datatype sendtype, 
    void *recvbuff,
    int recvcnt,
    MPI_Datatype recvtype,
    int root, 
    MPI_Comm comm);
~~~

~~~c
int MPI_Gatherv(
  void *sendbuf,
  int sendcount,
  MPI_Datatype sendtype,
  void *recvbuf,
  int *recvcnts,
  int *displs,
  MPI_Datatype recvtype,
  int root,
  MPI_Comm comm
);
~~~

- `sendbuf`: starting address of send buffer (choice)
- `sendcount`: number of elements in send buffer (integer)
- `sendtype`: data type of send buffer elements 
- `recvbuf`: address of receive buffer (choice, significant only at root)
- `recvcnts`: integer array (of length group size) containing the number of elements that are received from each process (significant only at root)
- `displs`: integer array (of length group size). Entry i specifies the displacement relative to recvbuf at which to place the incoming data from process i (significant only at root)
- `recvtype`: data type of recv buffer elements (significant only at root)
- `root`: rank of receiving process (integer)
- `comm`: communicator

{% enddetails %}
{% details Hands-on: Gatherv %}


<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=gatherv.c"></script>

~~~bash
mpicc -o gatherv gatherv.c
mpirun -np 4 gatherv
~~~

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/gatherv.png" width="50%" zoomable=true alt="Run Gatherv" %}


{% enddetails %}
{% details Simple approach implementation %}


<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=bucket1.c"></script>

~~~bash
mpicc -o bucket1 bucket1.c
mpirun -np 8 bucket1
~~~


{% enddetails %}
## Complex Parallel Bucket Sort

{% details Overview %}


- The data might be too large to be distributed via MPI_Bcast

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/bucketsort3.png" width="50%" zoomable=true alt="Complex approach to Bucket Sort" %}

- The necessary communication pattern: all to all

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/all2all.png" width="50%" zoomable=true alt="All to all" %}

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/all2all_2.png" width="50%" zoomable=true alt="All to all explanation" %}


{% enddetails %}
{% details Alltoall %}


~~~c
int MPI_Alltoall(
  void *sendbuf,
  int sendcount,
  MPI_Datatype sendtype,
  void *recvbuf,
  int recvcount,
  MPI_Datatype recvtype,
  MPI_Comm comm
);
~~~

- `sendbuf`: starting address of send buffer (choice)
- `sendcount`: number of elements to send to each process (integer)
- `sendtype`: data type of send buffer elements
- `recvbuf`: address of receive buffer (choice)
- `recvcount`: number of elements received from any process (integer)
- `recvtype`: data type of receive buffer elements
- `comm`: communicator

{% enddetails %}
{% details Hands-on: Alltoall %}


<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=alltoall.c"></script>

~~~bash
mpicc -o alltoall alltoall.c 
mpirun -np 4 alltoall
~~~

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/all2all_mpi.png" width="50%" zoomable=true alt="Run All to all" %}


{% enddetails %}
{% details Alltoallv %}


~~~c
int MPI_Alltoallv(
  void *sendbuf,
  int *sendcounts,
  int *sdispls,
  MPI_Datatype sendtype,
  void *recvbuf,
  int *recvcounts,
  int *rdispls,
  MPI_Datatype recvtype,
  MPI_Comm comm
);
~~~

- `sendbuf`: starting address of send buffer (choice)
- `sendcounts`: integer array equal to the group size specifying the number of elements to send to each processor
- `sdispls`: integer array (of length group size). Entry j specifies the displacement (relative to sendbuf from which to take the outgoing data destined for process j
- `sendtype`: data type of send buffer elements
- `recvbuf`: address of receive buffer (choice)
- `recvcounts`: integer array equal to the group size specifying the maximum number of elements that can be received from each processor
- `rdispls`: integer array (of length group size). Entry i specifies the displacement (relative to recvbuf at which to place the incoming data from process i
- `recvtype`: data type of receive buffer elements
- `comm`: communicator

{% enddetails %}
{% details Hands-on: Alltoallv %}


<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=alltoallv.c"></script>

~~~bash
mpicc -o alltoallv alltoallv.c 
mpirun -np 4 alltoallv
~~~

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/all2allv_mpi.png" width="50%" zoomable=true alt="Run All to allv" %}


{% enddetails %}
{% details Complex approach implementation %}


<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=bucket2.c"></script>

~~~bash
mpicc -o bucket2 bucket2.c
mpirun -np 8 bucket2
~~~

{% enddetails %}
## N-Body Problem

{% details Overview %}


**Fundamental settings for most, if not all, of computational simulation problems:**

- Given a space
- Given a group of entities whose activities are (often) bounded within this space
- Given a set of equation that governs how these entities react to one another and to attributes of the containing space
- Simulate how these reactions impact all entities and the entire space overtime

- Computation requires parallelization
- Experimental spaces are simulated at massive scale (millions of entities)
- Individual time steps are significantly smaller than the total simulation time. 
- Time complexity can be reduced by approximating a cluster of distant bodies as a single distant body with mass sited at the center of the mass of the cluster

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/mass-bodies.png" width="50%" zoomable=true alt="Mass of multiple bodies" %}

{% enddetails %}
{% details Barnes-Hut Algorithm (2-D) %}


Start with whole region in which one square contains the bodies (or particles).
- First, this cube is divided into four subregions.
- If a subregion contains no particles, it is deleted from further consideration.
- If a subregion contains one body, it is retained.
- If a subregion contains more than one body, it is recursively divided until every subregion contains one body.
- Create an quadtree – a tree with up to four edges from each node
- The leaves represent cells each containing one body.
- After the tree has been constructed, the total mass and center of mass of the subregion is stored at each node.

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/barnes-hut.png" width="50%" zoomable=true alt="Barnes-Hut algorithm" %}

{% enddetails %}
{% details Orthogonal Recursive Bisection %}


- First, a vertical line found that divides area into two areas each with equal number of bodies. 
- For each area, a horizontal line found that divides it into two areas, each with equal number of bodies. 
- Repeated as required. 

{% include figure.liquid path="assets/img/courses/csc466/divide-conquer/orthogonal.png" width="50%" zoomable=true alt="Orthogonal bisection" %}

{% enddetails %}
