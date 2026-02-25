---
layout: lecture
pretty_table: true
collection: csc530
course: CSC 530: Data Structures
title: "Fibonacci Heap - Graph Shortest Path"
---
# Fibonacci Heap - Graph Shortest Path

This lecture is based on Standford CS106B: Programming Abstractions


{% details 1. Motivation %}

- A Google Maps image showing the directions from San Jose to San Francisco

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-google-maps.png" width="50%" zoomable=true %}

- You can go on the 101
- You can go on the 280
- You could go on El Camino Real if you wanted to, but Google doesn't even give you that 
choice because it would take so much longer
- Google priorizes by time to get to your destination, not distance, although often distance is minimized, too
- Google uses a tremendous amount of data, both historical and real-time to get you a good estimate
- Google knows all the speed limits, traffic (real-time, in many cases), stop lights, etc., and uses it all 
to weight their graph

{% enddetails %}
{% details 2. What is graph? %}

- A graph is a mathematical structure for representing relationships using nodes and edges.
- This is just like a tree, but without any rules! I like to call graphs the wild west of the node-based world.
- With graphs, we don't have any more notion of parents and children, and we allow cycles.

{% enddetails %}
{% details 3. Characteristics of graph %}

- It can have cycles
- It does not have root
- It could be weighted (edges have values)

{% enddetails %}
{% details 4. Graph terminologies %}

- node: the objects in a graph
- vertex: A vertex is another name for a node.
- edge: The connections between nodes.
- directed edge: An edge that only goes in one direction (e.g., from a to b) but 
not the other way. In a diagram directed edges are arrows.
- undirected edge: An edge that can go in both directions (e.g., from a to b and from b to a). In a 
diagram undirected edges are lines.
- path: A path from node a to node b is a sequene of edges that can be followed starting from a to reach b.
    - A path can be represented as nodes visited, or edges taken.
    - In the diagram below, one path from V to Z is {b, h} or `{V, X, Z}'
    - What are two paths from U to Y?
- path length: The number of nodes or edges contained in a path.

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/example-graph1.png" width="50%" zoomable=true %}

- neighbor or adjacent: Two nodes connected directly by an edge.
    - Example below: V and X are neighbors.

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/example-graph2.png" width="50%" zoomable=true %}

{% enddetails %}
{% details 4. Loops and circles %}

- cycle: A path that begins and ends at the same node.
    - Examples below:
        - {b, g, f, c, a} or {V, X, Y, W, U, V}
        - {c, d, a} or U, W, V, U
- acyclic graph: a graph that does not contain any cycles
- loop: an edge directly from a node to itself
    - Many graphs do not allow loops (you can't be friends with yourself on Facebook)

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/example-graph1.png" width="50%" zoomable=true %}
{% include figure.liquid path="assets/img/courses/csc530/shortest-path/example-graph2.png" width="50%" zoomable=true %}

{% enddetails %}
{% details 5. Breadth First Search %}

- The first graph searching algorithm we will look at is our old friend the 
Breadth First Search.
    - The big idea is to do the search by path-length: first, look at the neighbors of 
    the start and see if your destination is in one of those paths.
    - If not, search one more level away – the neighbors of your neighbors.
    - Continue with the neighbors-of-your-neighbors-neighbors until you eventually find a path
    - You will always find the shortest path in terms of number of hops, but this does not take into 
    consideration the weights of the edges.
- The BFS algorithm is exactly like it has been in the past for other types of searching: you enqueue 
the start node into a queue, then go into a while loop, dequeueing the first, checking for the destination, and then enqueue all neighbors.
- For the graph below, a BFS from A to D simply gives us A-D as the path:A very simple, 
unweighted, undirected graph with four nodes, A, B, C, and D. A is neighbors with B and D. B is 
neighbors with C and D, and D is neighbors with A and C.

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/a-b-c-d.png" width="50%" zoomable=true %}

- This is the shortest path:The same graph as above, with the path from A-D as the shortest path

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/a-b-c-d-shortest.png" width="50%" zoomable=true %}

- Once we add weights, though, BFS no longer finds us our shortest weighted path:
    - The same graph as above, with edge weights AB=10, AD=12345, BC=5, and CD=3

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/a-b-c-d-weights.png" width="50%" zoomable=true %}

- This is the path we want:The same graph as above, showing that the shortest path is 
actually A-B-C-D if weights are taken into consideration

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/a-b-c-d-weights-shortest.png" width="50%" zoomable=true %}

- BFS works great for finding the shortest path length without considering weights, but it can break 
miserably with weights.

{% enddetails %}
{% details 6. Dijkstra's Algorithm %}

- Dijkstra's Algorithm, named after the computer scientist Edsger Dijkstra.
- Dijkstra's algorithm is greedy (and one that works), and as it progresses, it attempts to 
find the shortest path by choosing the best path from the available choices at each step.
- Dijkstra's algorithm can be performed in a number of ways. One method is to use a priority queue 
instead of a queue (as in BFS), with the priorities as the total path length so far.
- This method is virtually identical to BFS, but does require keeping track of all paths 
in the priority queue.
- A different form of Dijkstra's algorithm uses a table of nodes, and keeps track of how far away 
from the start each node is, updating by looking at neighbors of unseen nodes. It also keeps track of 
enough information to create the shortest path after the table is filled in.

{% enddetails %}
{% details 7. Example with the table method %}

{% details info Setup %}

- Create a table of all nodes, with a distance to the start as one row. 
- A second row will be called previous, which will annotate which node we were looking at when 
we updated the node's distance. 
- A final row, seen starts out with all nodes as Not Seen, and gets updated after we analyze each 
node in turn. 
Here is an example graph, representing a map where we are trying to get from San Jose to San Francisco 
and we have nodes A-G as potential different paths to take.

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-graph.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Basic Dijkstra Algorithm %}

1. Find the shortest distance to the start from the un-seen nodes.
2. Look at this node's neighbors, and update the total distance to the neighbors 
based on their distance and the distance already to this node.
3. If the node visited is the destination, stop
1. Repeat from step 1.

{% enddetails %}
{% details info Starting table %}


|                 | SJ  | A | B | C | D | E | F | G | SF |
| --------------- | --- | - | - | - | - | - | - | - | -  |
| Distance to SJ  |  0  | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞  |
| Previous        |  -  |   |   |   |   |   |   |   |    |
| Seen?           |  N  | N | N | N | N | N | N | N | N  |

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-graph.png" width="50%" zoomable=true %}

- All the distances to SJ are listed as infinity, except for the distance from SJ to itself, which is 0. 
- We don't yet know the distance to SJ from the other nodes, because we haven't analyzed them yet formally 
    – we can see them in the graph, but for our table we haven't yet analyzed anything.
- The previous row is empty
- All nodes (including SJ) are listed as Not Seen (N).

{% enddetails %}
{% details info Step 1: SJ %}

- Find the shortest distance to the start from the un-seen nodes: that would be SJ (it has a 
distance of 0, and all others have a distance of ∞).
- Look at SJ's neighbors, A and B. Both can be reached from SJ by their respective distances, and 
both are less than ∞. 
    - Update the table, and then we mark SJ as visited. 
    - Update Previous to show that we got to A and B directly from SJ:

|                 | SJ  | A  | B  | C | D | E | F | G | SF |
| --------------- | --- | -- | -- | - | - | - | - | - | -  |
| Distance to SJ  |  0  | 5  | 10 | ∞ | ∞ | ∞ | ∞ | ∞ | ∞  |
| Previous        |  -  | SJ | SJ |   |   |   |   |   |    |
| Seen?           |  Y  | N  | N  | N | N | N | N | N | N  |

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-graph.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info Step 2: SJ-A %}

- Find the shortest distance to the start from the un-seen nodes: now this is A.
-  Look at A's neighbors, SJ, C, and E. SJ has been visited, so we ignore it. 
    -  Update E to have a distance of 5 + 40 from SJ (because we have already gone 5 to get to A). 
    -  Update C to be 205.

|                 | SJ  | A  | B  | C   | D | E  | F | G | SF |
| --------------- | --- | -- | -- | --- | - | -- | - | - | -  |
| Distance to SJ  |  0  | 5  | 10 | 205 | ∞ | 45 | ∞ | ∞ | ∞  |
| Previous        |  -  | SJ | SJ |  A  |   | A  |   |   |    |
| Seen?           |  Y  | Y  | N  | N   | N | N  | N | N | N  |

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-graph.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info Step 3: SJ-B %}

- Find the shortest distance to the start from the un-seen nodes: now this is B.
- Look at B's neighbors, SJ, C, and G. 
    - We recognize that SJ-B-C is going to be shorter than SJ-A-C becuase 10 + 8 = 18 is shorter than 205. 
    - So, we update C to have a distance of 18 and we modify its Previous to be from B. 
    - We update G to be 30.

|                 | SJ  | A  | B  | C  | D | E  | F | G  | SF |
| --------------- | --- | -- | -- | -- | - | -- | - | -- | -  |
| Distance to SJ  |  0  | 5  | 10 | 18 | ∞ | 45 | ∞ | 30 | ∞  |
| Previous        |  -  | SJ | SJ |  B |   | A  |   |  B |    |
| Seen?           |  Y  | Y  | Y  | N  | N | N  | N | N  | N  |

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-graph.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info Step 4: SJ-B-C %}

- Find the shortest distance to the start from the un-seen nodes: now this is C.
- Look at C's neighbors, A, B, D, and G. 
    - We ignore A and B (already seen). 
    - We make D 18 + 13 = 31 and 
    - We don't need to udpate G because 18 + 15 = 33 is greater than 30.

|                 | SJ  | A  | B  | C  | D  | E  | F | G  | SF |
| --------------- | --- | -- | -- | -- | -- | -- | - | -- | -  |
| Distance to SJ  |  0  | 5  | 10 | 18 | 31 | 45 | ∞ | 30 | ∞  |
| Previous        |  -  | SJ | SJ |  B |  C | A  |   |  B |    |
| Seen?           |  Y  | Y  | Y  | Y  | N  | N  | N | N  | N  |

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-graph.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info Step 5: SJ-B-C-G %}

- Find the shortest distance to the start from the un-seen nodes: now this is G.
- Look at G's neighbors, B, C, D, F, and SF. 
    - We ignore B and C. 
    - We don't update D (already smaller than 36), 
    - We update F to be 32, and 
    - We update SF to be 48. 
    - We can't stop yet, even though we have reached SF! This is because we may have a shorter path.

|                 | SJ  | A  | B  | C  | D  | E  | F  | G  | SF |
| --------------- | --- | -- | -- | -- | -- | -- | -- | -- | -- |
| Distance to SJ  |  0  | 5  | 10 | 18 | 31 | 45 | 32 | 30 | 48 |
| Previous        |  -  | SJ | SJ |  B |  C | A  |  G |  B | G  |
| Seen?           |  Y  | Y  | Y  | Y  | N  | N  | N  | Y  | N  |

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-graph.png" width="50%" zoomable=true %}


{% enddetails %}
{% details info Step 6: SJ-B-C-D %}

- Find the shortest distance to the start from the un-seen nodes: now this is D.
- Look at D's neighbors, C, E, F, and G. 
    - We ignore C and G. 
    - We update E to be 32, because 31 + 1 = 32 and this is less than 45. 
    - We don't update F (already shorter than 36).

|                 | SJ  | A  | B  | C  | D  | E  | F  | G  | SF |
| --------------- | --- | -- | -- | -- | -- | -- | -- | -- | -- |
| Distance to SJ  |  0  | 5  | 10 | 18 | 31 | 32 | 32 | 30 | 48 |
| Previous        |  -  | SJ | SJ |  B |  C | D  |  G |  B | G  |
| Seen?           |  Y  | Y  | Y  | Y  | Y  | N  | N  | Y  | N  |

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-graph.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info Step 7: SJ-B-C-D-E %}

- Find the shortest distance to the start from the un-seen nodes: now this is either E or F, 
and it doesn't matter which one we choose. Let's choose E.
- Look at E's neighbors, A, D, and F. 
    - We ignore A and D. We don't update F. 
    - Notice that we have to do less updating as we get further through the graph!

|                 | SJ  | A  | B  | C  | D  | E  | F  | G  | SF |
| --------------- | --- | -- | -- | -- | -- | -- | -- | -- | -- |
| Distance to SJ  |  0  | 5  | 10 | 18 | 31 | 32 | 32 | 30 | 48 |
| Previous        |  -  | SJ | SJ |  B |  C | D  |  G |  B | G  |
| Seen?           |  Y  | Y  | Y  | Y  | Y  | Y  | N  | Y  | N  |

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-graph.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info Step 8: SJ-B-C-G-F %}

- Find the shortest distance to the start from the un-seen nodes: now this is F.
- Look at F's neighbors, D, E, G, and SF. 
    - We ignore D, E, and G. 
    - We update SF because 32 + 1 = 33 is less than 48. So, we did need to update SF after all!

|                 | SJ  | A  | B  | C  | D  | E  | F  | G  | SF |
| --------------- | --- | -- | -- | -- | -- | -- | -- | -- | -- |
| Distance to SJ  |  0  | 5  | 10 | 18 | 31 | 32 | 32 | 30 | 33 |
| Previous        |  -  | SJ | SJ |  B |  C | D  |  G |  B | G  |
| Seen?           |  Y  | Y  | Y  | Y  | Y  | Y  | Y  | Y  | N  |     

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-graph.png" width="50%" zoomable=true %}


{% enddetails %}
{% details info Step 9: SJ-B-C-G-F-SF %}

- Find the shortest distance to the start from the un-seen nodes: now this is SF 
- Because we are visiting the destination, we know that we have found the shortest path. 
    - We are done, and the shortest path is 33.


|                 | SJ  | A  | B  | C  | D  | E  | F  | G  | SF |
| --------------- | --- | -- | -- | -- | -- | -- | -- | -- | -- |
| Distance to SJ  |  0  | 5  | 10 | 18 | 31 | 32 | 32 | 30 | 33 |
| Previous        |  -  | SJ | SJ |  B |  C | D  |  G |  B | G  |
| Seen?           |  Y  | Y  | Y  | Y  | Y  | Y  | Y  | Y  | N  |     

{% include figure.liquid path="assets/img/courses/csc530/shortest-path/sj-to-sf-shortest.png" width="50%" zoomable=true %}

- Now, to get the actual path, we simply follow the Previous nodes backwards from SF:
    - SF's previous was F
    - F's previous was G
    - G's previous was B
    - B's previous was SJ
    - Therefore, the shortest path is SJ -> B -> G -> F -> SF with a length of 33.



{% enddetails %}
{% enddetails %}
