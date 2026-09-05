---
layout: lecture
pretty_table: true
collection: csc231

title: "Gate and Circuit"
toc:
  - name: In the beginning ...
  - name: Logic Gates
  - name: Circuits
  - name: The Processor's Execution of Program Instructions
---
# Gate and Circuit

{% details Relevant Reading %}

{% enddetails %}

This lecture will cover sections 5.1 through 5.4 
from [Chapter 5](https://diveintosystems.org/book/C5-Arch/index.html) of the book. 


## In the beginning ...

- `computer` = `the one who computes`

### Origin of modern computing architectures

- Jacquard Loom

<iframe width="560" height="315" src="https://www.youtube.com/embed/MQzpLLhN0fY" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

- Charles Babbage's Analytical Machine

<iframe width="560" height="315" src="https://www.youtube.com/embed/XSkGY6LchJs" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

- Hollerith Census Machine (eventually becomes IBM)

<iframe width="560" height="315" src="https://www.youtube.com/embed/9HXjLW7v-II" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

- ENIAC: First computer

<iframe width="560" height="315" src="https://www.youtube.com/embed/k4oGI_dNaPc" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

### Modern computer architecture

- von Neuman architecture
  - General purpose
  - A binary computer instead of a decimal computer
  - Stored-program

## Logic Gates

- Building blocks of the digital circuitry that implements arithmetic, 
control, and storage functionality in a digital computer.
- Logic gates are created from transistors that are etched into a 
semiconductor material (e.g. silicon chips). 
- Transistors act as switches that control electrical flow through the chip. 
A transistor can switch its state between on or off (between a high or low 
voltage output). Its output state depends on its current state plus its input 
state (high or low voltage).

### 2.1 Basic Logic Gates

- AND, OR, and NOT form a set of basic logic gates from which 
any circuit can be constructed. 


{% details Truth table for AND, OR, and NOT %}


{% enddetails %}
| A | B | A AND B  | A OR B  | NOT A | NOT B |
| - | - | -------- | ------- | ----- | ----- | 
| 0 | 0 | 0        | 0       | 1     | 1     |
| 0 | 1 | 0        | 1       | 1     | 0     |
| 1 | 0 | 0        | 1       | 0     | 1     |
| 1 | 1 | 1        | 1       | 0     | 0     |  


### 2.2 Electronic Circuit

- Transistors
- Electrical currents activate/deactivate other current flows. 
- Example of AND gate

{% include figure.liquid path="assets/img/courses/csc231/04-gate-circuit/and-circuit.png" max-width="50%" zoomable=true alt="word-oriented memory organization" %}

### 2.3 Other gates

{% details Truth table for AND, OR, and NOT %}


{% enddetails %}
| A | B | A NAND B  | A NOR B  | A XOR B |
| - | - | --------- | -------- | ------- | 
| 0 | 0 |     1     |    1     |   0     |
| 0 | 1 |     1     |    0     |   1     |
| 1 | 0 |     1     |    0     |   1     |
| 1 | 1 |     0     |    0     |   0     |  

## Circuits

- Core functionality of the architecture
  - Instruction Set Architecture (ISA)
- Categories
  - Arithmetic/logic
  - Control
  - Storage
- All three are contained in a standard processor

### 3.1. Arithmetic: Addition


{% details Binary addition %}


{% enddetails %}
- Mathematical operations:
  - Bit-wise with carry
  - $0 + 0 = 0$
  - $0 + 1 = 1$
  - $1 + 0 = 1$
  - $1 + 1 = 0$ and carry $1$ to the next bit operation (or add 1 to left of the most significant bit position)
- This works for both unsigned and 2's complement notation
- Example 1: 4-bit unsigned $2+6=8$

$$
\ 0010 \\
+\ 0110 \\
\hline
\ 1000
$$  

- Example 2: 4-bit unsigned $11+12=23$

$$
\ 1011 \\
+\ 1100 \\
\hline
\ 10111
$$

- Example 3: 4-bit signed $5-7=5+(-7)=(-2)$
  - Positive to negative conversion in 2's complement: flipped bit and add 1. 
  - $7$: $0111$
  - $-7$: $1000 + 1=1001$

$$
\ 0101 \\
+\ 1001 \\
\hline
\ 1110
$$

$1110=(-1)*(1)*(8)+(1)*(4)+(1)*(2)+(0)*1=(-8)+4+2=(-2)$

{% details Unsigned addition %}


{% enddetails %}
- Given `w` bits operands
 - True sum can have `w + 1` bits (carry bit). 
 - Carry bit is discarded. 
- Implementation:
 - s = (u + v) mod 2<sup>w</sup>


{% details Hands on: unsigned addition %}


{% enddetails %}
- Create a file named `unsigned_addition.c` with the following contents:

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=unsigned_addition.c"></script>

- Compile and run `unsigned_addition.c`.
- Confirm that calculated values are correct. 


{% details 2's complement addition %}


{% enddetails %}
- Almost similar bit-level behavior as unsigned addition
  - True sum of `w`-bit operands will have `w+1`-bit, but
  - Carry bit is discarded. 
  - Remainding bits are treated as 2's complement integers. 
-  Overflow behavior is different
  - $TAdd_{w}(u, v) = u + v + 2^{w}$ if $u + v < TMin_{w}$ (**Negative Overflow**)
  - $TAdd_{w}(u, v) = u + v$ if $TMin_{w} \leq u + v \leq TMax_{w}$
  - $TAdd_{w}(u, v) = u + v - 2^{w}$ if $u + v TMax_{w}$ (**Positive Overflow**)


{% details Hands on: signed addition %}


{% enddetails %}
- Create a file named `signed_addition.c` with the following contents:

<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=signed_addition.c"></script>

- Compile and run `signed_addition.c`.
- Confirm that calculated values are correct. 

### 3.2. Arithmetic: Multiplication

{% details Multiplication %}


{% enddetails %}
- Compute product of `w`-bit numbers x and y. 
- Exact results can be bigger than `w` bits. 
  - Unsigned: up to `2w` bits: $0 \leq x * y \leq (2^{w} - 1)^{2}$
  - 2's complement (negative): up to `2w - 1` bits: $x * y \geq (-2)^{2w-2} + 2^{2w-1}$
  - 2's complement (positive): up to `2w` bits: $x * y \leq 2^{2w-2}$
- To maintain exact results:
  - Need to keep expanding word size with each product computed. 
  - Is done by software if needed ([arbitrary precision arithmetic packages](https://en.wikipedia.org/wiki/List_of_arbitrary-precision_arithmetic_software)).
- **Trust your compiler**: Modern CPUs and OSes will most likely know to select the optimal method
to multiply. 


{% details Multiplication and Division by power-of-2 %}


{% enddetails %}
- Power-of-2 multiply with left shift
  - $u << k$ gives $u * 2^{k}$
  - True product has `w + k` bits: discard `k` bits. 
- Unsigned power-of-2 divide with right shift
  - $u >> k$ gives $floor(u / 2^{k})$
  - Use logical shift.
- Signed power-of-2 divide with shift
  - x > 0: $x >> k$ gives $floor(u / 2^{k})$
  - x < 0: $(x + (1 << k) - 1) >> k$ gives ceiling $u / 2^{k}$
  - C statement: `(x < 0 ? x + (1 << k) - 1: x) >k`

```

### 3.3. Negation

{% details Negation: complement and increase %}


{% enddetails %}
- Negate through complement and increment:
  - `~x + 1 == -x`


{% details Challenge %}

{% enddetails %}
- Implement a C program called `negation.c` that implements and validates
the equation in slide 24. The program should take in a command line argument
that takes in a number of type `short` to be negated. 
- What happens if you try to negate `-32768`?

:::{dropdown} Solution
<script src="https://gist.github.com/linhbngo/d1e9336a82632c528ea797210ed0f553.js?file=negation.c"></script>
:::
```

## The Processor's Execution of Program Instructions

- Performed in several stages.
- Key stages:
  - Fetch
  - Decode
  - Execute
  - WriteBack

{% include figure.liquid path="assets/img/courses/csc231/04-gate-circuit/instruction-format.png" max-width="50%" zoomable=true alt="Add instruction example" %}
*https://diveintosystems.org/book/C5-Arch/instrexec.html*

- PC: Program Counter
- IR: Instruction Register

{% include figure.liquid path="assets/img/courses/csc231/04-gate-circuit/fetch.png" max-width="50%" zoomable=true alt="Fetch" %}

{% include figure.liquid path="assets/img/courses/csc231/04-gate-circuit/decode.png" max-width="50%" zoomable=true alt="Decode" %}

{% include figure.liquid path="assets/img/courses/csc231/04-gate-circuit/execution.png" max-width="50%" zoomable=true alt="Execution" %}

{% include figure.liquid path="assets/img/courses/csc231/04-gate-circuit/writeback.png" max-width="50%" zoomable=true alt="WriteBack" %}
