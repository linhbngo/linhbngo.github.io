---
layout: lecture
pretty_table: true
collection: csc466

title: "MPI in Python: mpi4py"
toc:
  - name: Overview
  - name: Hands-on
---
# MPI in Python: mpi4py

{% details Final Exam %}

- Final Exam: May 7, 1:00PM - 3:00PM

{% enddetails %}
## Overview

{% details Similarity %}


- Workflow similar to C's interface
- Slightly different naming scheme (e.g. MPI.COMM_WORLD instead of MPI_COMM_WORLD)
- [Documentation](https://mpi4py.readthedocs.io/en/stable/)

{% enddetails %}
{% details Example %}


- Create a file named `first.py`

```python
#!/usr/bin/env /opt/env/python3/bin/python
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
name = MPI.Get_processor_name()

print (f"Hello world from process {rank} running on host {name} out of {size} processes") 
```

- To run:

```bash
chmod 755 first.py
mpirun --host compute01:2,compute02:2 ./first.py
```

{% enddetails %}
## Hands-on

- For all communication, the core MPI interface requires data to be written into a buffer. 
- This can be done via numpy.

| Array-protocol  | Description            |
| --------------- | ---------------------- | 
|      '?'        | boolean                |
|      'b'        | (signed) byte          |
|      'B'        | unsigned byte          |
|      'i'        | (signed) integer       |
|      'u'        | unsigned integer       |
|      'f'        | floating-point         |
|      'c'        | complex-floating point |
|      'm'        | timedelta              |
|      'M'        | datetime               |
|      'O'        | (Python) objects       |
|      'U'        | Unicode string         |
|      'V'        | raw data (void)        |

- Example:

```python
from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

buf = np.empty(1, dtype='d')
buf[0] = rank
tag = 0

print(f"Process {rank} has original value {buf}")
    
if rank == 0:
    comm.Send([buf, MPI.DOUBLE],1)
    comm.Recv([buf, MPI.DOUBLE],1)
  
if rank == 1:
    comm.Recv([buf, MPI.DOUBLE],0)
    comm.Send([buf, MPI.DOUBLE],0)  

print(f"Process {rank} now has value {buf}")
```


- [Point-to-point](https://github.com/linhbngo/cpsc-3620/blob/master/05-intro-to-mpi.ipynb)
- [Pleasantly parallel](https://github.com/linhbngo/cpsc-3620/blob/master/06-pleasantly-parallel.ipynb)

{% details Scatterv %}


```python
# scatterv_demo.py
from mpi4py import MPI
import numpy as np

comm  = MPI.COMM_WORLD
rank  = comm.Get_rank()
size  = comm.Get_size()

# ----- set-up on the root -----
if rank == 0:
    counts  = np.arange(1, size + 1, dtype='i')          # [1,2,3,...]
    displs  = np.insert(np.cumsum(counts), 0, 0)[:-1]    # starting offsets
    sendbuf = np.arange(counts.sum(), dtype='i')         # [0,1,2,…,N-1]
else:                                    # other ranks allocate nothing yet
    counts = displs = sendbuf = None

# everyone needs counts/displs to size their receive buffer
counts  = comm.bcast(counts,  root=0)
displs  = comm.bcast(displs,  root=0)
recvbuf = np.empty(counts[rank], dtype='i')

comm.Scatterv([sendbuf, counts, displs, MPI.INT], recvbuf, root=0)  # :contentReference[oaicite:0]{index=0}
print(f"Rank {rank} received {recvbuf}")
```

{% enddetails %}
{% details Gatherv %}


```python
from mpi4py import MPI
import numpy as np

comm  = MPI.COMM_WORLD
rank  = comm.Get_rank()
size  = comm.Get_size()

# each rank prepares different-size data
sendbuf = np.full(rank + 1, rank, dtype='i')   # length = rank+1
sendcnt = np.array(len(sendbuf), dtype='i')

# root gathers the individual counts
recvcounts = None
if rank == 0:
    recvcounts = np.empty(size, dtype='i')
comm.Gather(sendcnt, recvcounts, root=0)

if rank == 0:
    displs = np.insert(np.cumsum(recvcounts), 0, 0)[:-1]
    recvbuf = np.empty(recvcounts.sum(), dtype='i')
else:
    displs = None
    recvbuf = None

comm.Gatherv(sendbuf,[recvbuf, recvcounts, displs, MPI.INT] if rank == 0 else None,root=0)                                                
if rank == 0:
    print("Root collected:", recvbuf, "(counts", recvcounts.tolist(), ")")

```

{% enddetails %}
{% details Alltoallv %}


```python
from mpi4py import MPI
import numpy as np

comm  = MPI.COMM_WORLD
rank  = comm.Get_rank()
size  = comm.Get_size()

# send (rank+1) ints to *each* peer → total send count = (rank+1)*size
sendcounts = np.full(size, rank + 1, dtype='i')
senddispls = np.arange(size, dtype='i') * (rank + 1)
sendbuf    = np.full(sendcounts.sum(), rank, dtype='i')   # filled with my rank ID

# expect j+1 ints from sender j
recvcounts = np.arange(1, size + 1, dtype='i')
recvdispls = np.insert(np.cumsum(recvcounts), 0, 0)[:-1]
recvbuf    = np.empty(recvcounts.sum(), dtype='i')

comm.Alltoallv([sendbuf, sendcounts, senddispls, MPI.INT],[recvbuf, recvcounts, recvdispls, MPI.INT])        

print(f"Rank {rank} received {recvbuf}")
``` 
{% enddetails %}
- [Divide and conquer](https://github.com/linhbngo/cpsc-3620/blob/master/07-divide-and-conquer.ipynb)

