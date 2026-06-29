---
layout: lecture
pretty_table: true
collection: csc466

title: "Point-to-point, data types, and communicators"
toc:
  - name: Overview
  - name: Point-to-point communication
---

# Point-to-point, data types, and communicators

## Overview

{% details Addresses in MPI %}


Data messages (objects) being sent/received (passed around) in MPI 
are referred to by their addresses:

- Memory location to read from to send
- Memory location to write to after receiving.

{% enddetails %}
{% details Parallel workflow %}


Individual processes rely on communication (message passing) to enforce workflow

- Point-to-point communication: 
    - `MPI_Send`
    - `MPI_Recv`
- Collective communication: 
    - `MPI_Broadcast`
    - `MPI_Scatter`
    - `MPI_Gather`
    - `MPI_Reduce`
    - `MPI_Barrier`.


{% enddetails %}
## Point-to-point communication

{% details MPI_Send %}


- `int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)`
    - `*buf`: pointer to the address containing the data elements to be sent. 
    - `count`: how many data elements will be sent.
    - `MPI_Datatype`: `MPI_BYTE`, `MPI_PACKED`, `MPI_CHAR`, `MPI_SHORT`, `MPI_INT`, 
    `MPI_LONG`, `MPI_FLOAT`, `MPI_DOUBLE`, `MPI_LONG_DOUBLE`, `MPI_UNSIGNED_CHAR`, 
    and other user-defined types.
    - `dest`: rank of the process these data elements are sent to.
    - `tag`: an integer identify the message. Programmer is responsible for managing tag.
    - `comm`: communicator (typically just used MPI_COMM_WORLD)

{% enddetails %}
{% details MPI_Recv %}


- `int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)`
    - `*buf`: pointer to the address containing the data elements to be written to. 
    - `count`: how many data elements will be received.
    - `MPI_Datatype`: `MPI_BYTE`, `MPI_PACKED`, `MPI_CHAR`, `MPI_SHORT`, `MPI_INT`, 
    `MPI_LONG`, `MPI_FLOAT`, `MPI_DOUBLE`, `MPI_LONG_DOUBLE`, `MPI_UNSIGNED_CHAR`, 
    and other user-defined types.
    - `dest`: rank of the process from which the data elements to be received.
    - `tag`: an integer identify the message. Programmer is responsible for managing tag.
    - `comm`: communicator (typically just used MPI_COMM_WORLD)
    - `*status`: pointer to an address containing a special `MPI_Status` struct that 
    carries additional information about the send/receive process. 

{% enddetails %}
{% details Hands-on: send_recv.c %}


- We want to write a program called send_recv.c that allows two processes to 
exchange their ranks: 
    - Process 0 receives 1 from process 1.
    - Process 1 receives 0 from process 0. 
- Inside `intro-mpi`, create a file named `send_recv.c` with the following
contents

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=send_recv.c"></script>

- Compile and run `send_recv.c`:

```bash
mpicc -o send_recv send_recv.c
mpirun --host compute01:1,compute02:1 -np 2 ./send_recv
```

- Did we get what we want? Why?
- Correction: separate sending and receiving buffers. 

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=send_recv_fixed.c"></script>


{% enddetails %}
{% details Hands-on: p2p communication at scale %}


- Rely on rank and size and math.  
- We want to shift the data elements with only message passing among 
adjacent processes. 
- Inside `intro-mpi`, create a file named `multi_send_recv.c` with the following
contents

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=multi_send_recv.c"></script>

- Compile and run `multi_send_recv.c`:

```bash
mpicc -o multi_send_recv multi_send_recv.c
mpirun --host compute01:2,compute02:2 -np 4 ./multi_send_recv
```

- Did we get what we want? Why?

{% enddetails %}
{% details Hands-on: blocking risk %}


- `MPI_Recv` is a blocking call.  
- Meaning the process will stop until it receives the message. 
    - What if the message never arrives?
- Inside `intro-mpi`, create a file named `deadlock_send_recv.c` with the following
contents

<script src="https://gist.github.com/linhbngo/05955842d2a7ce40c9723292a2ded118.js?file=deadlock_send_recv.c"></script>

- Compile and run `deadlock_send_recv.c`:

```bash
mpicc -o deadlock_send_recv deadlock_send_recv.c
mpirun --host compute01:1,compute02:1 -np 2 ./deadlock_send_recv
```

- What happens?
- To get out of deadlock, press `Ctrl-C`. 
- Correction:
    - Pay attention to send/receive pairs. 
    - The numbers of `MPI_Send` must always equal to the number of `MPI_Recv`. 
    - `MPI_Send` should be called first (preferably).




{% enddetails %}
