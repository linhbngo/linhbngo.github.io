---
layout: lecture
pretty_table: true
collection: csc402
course: CSC 402: Software Engineering.
title: "Architectures"
toc:
  - name: System Design
  - name: UML
  - name: Architectural styles
---
# Architectures

## System Design

{% details Design steps %}

- Given requirements, must `design` a system to meet them
    - System architecture
    - User experience
    - Program design
- Ideal: requirements are independent of design (avoid implementation bias)
- Reality: working on design clarifies requirements
    - Methodology should allow feedback (strength of iterative & 
    agile methods)

{% enddetails %}
{% details Design principles %}

- Design is an especially creative part of the software development process
    - More a "craft" than a science
    - Many tools are available; must select appropriate ones for a given project
- Strive for simplicity
    - Use modeling, abstraction to (hopefully) find simple 
    ways to achieve complex requirements
    - Designs should be easy to implement, test, and maintain
- Easy to use correctly, hard to use incorrectly
- Low coupling, high cohesion

{% enddetails %}
{% details What is architecture %}

- Brooks: Conceptual integrity is key to usability and 
maintainability; architect maintains conceptual integrity
- Johnson: The shared understanding that expert developers have of the 
system / The decisions you wish you could get right early in a project
- Sommerville: Dominant influence on non-functional system characteristics
- `Highest level` organization of system

{% enddetails %}
{% details Levels of abstraction %}

- Requirements
    - High level `what`
- Architecture
    - High-level `how`
    - Mid-level `what`
- Program design
    - Mid-level `how`
    - Low-level `what`
- Code
    - Low-level `how`
- Documentation for each step should respect its level of abstraction
    - Avoid biasing later steps
    - Avoid redundancy

{% enddetails %}
{% details Example %}

- Requirements:
    - Drone can hover
- Architecture
    - Sensing → navigation → control → actuation
    - Radio input
- Program design
    - PID controller, low-pass filter
    - Gain registry
- Code
    ```python
    def lpf(x1, y0, a):
        """exp filter w/ smoothing factor a"""
        return a*x1 + (1-a)*y0
    ```

{% enddetails %}
{% details Architectural considerations %}

- Infrastructure
    - Hardware
    - Operating systems
    - Virtualization
- Interfaces
    - Networks/buses
    - Protocols
- Services
    - Databases
    - Authentication
- Operations
    - Testing
    - Logging/monitoring
    - Backups
    - Rolling deployment
- Product line

{% enddetails %}
{% details Architectural models %}

- Diagram and supporting specification
    - Be specific with notation
- Multiple perspectives
    - Conceptual
    - Static (subsystems)
    - Dynamic (data flow)
    - Physical (deployment)
- Appropriate level of detail
    - A single diagram should fit cleanly on one page
- Distinct from program models
    - Inheritance diagrams don’t show interactions

{% enddetails %}
{% details Subsystems %}

- Improve comprehensibility of system by decomposing into subsystems
- Group elements into subsystems to minimize coupling while 
maintaining cohesion
- Coupling: Dependencies between two subsystems
    - If coupling is high, can't change one without affecting the other
- Cohesion: Dependencies within a subsystem
    - High cohesion implies closely-related functionality

{% enddetails %}
## UML

{% details UML: Package %}

- General grouping of system elements
- Appropriate for denoting subsystem at conceptual level

{% include figure.liquid path="assets/img/courses/csc402/uml_package.png" width="50%" zoomable=true %}

{% enddetails %}
{% details UML: Component %}

- Replaceable part of a system
    - Conforms to and realizes a set of interfaces
    - An implementation of a subsystem
    - Could be replaced by another component that realizes the 
    same interfaces, and system would still function
- Distinct from classes
    - Classes may have fields, are assembled into programs
    - Components realize interfaces, are assembled into systems

{% include figure.liquid path="assets/img/courses/csc402/uml_component.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Interface diagram %}

{% include figure.liquid path="assets/img/courses/csc402/uml_interface_diagram.png" width="50%" zoomable=true %}

{% enddetails %}
{% details UML: Node %}

- Physical element that exists at runtime, provides a computational resource
    - Computer
    - Smartphone
    - Network router
- Components live on nodes

{% include figure.liquid path="assets/img/courses/csc402/uml_node.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Example: deployment diagram %}

{% include figure.liquid path="assets/img/courses/csc402/deployment_diagram.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Deployment environments %}

- Development
- Production
- Staging
- (Acceptance testing)

{% enddetails %}
## Architectural styles

{% details Client/sever %}

- Control flow in client and server are independent
- Communication follows a protocol
- If protocol is fixed, either side can be replaced independently
- Peer-to-peer: same component can act as both client and server
{% include figure.liquid path="assets/img/courses/csc402/server_client.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Layered %}

- Partition subsystems into stack of layers
    - Layer provides services to layer directly above
    - Layer relies on services to layer directly below
- Advantage: constrains coupling
- Danger: leaky abstractions
    - May need services of multiple lower layers

{% enddetails %}
{% details Pipe and filter %}

- Transformation components process inputs to produce outputs
    - Subsystems coupled via data exchange
    - Good match for data flow models
    - May be dynamically assembled
- Applications:
    - Streaming media
    - Graphics shaders
    - Signal processing
- Caveats:
    - Awkward to handle events (interactive systems)
    - Rate mismatches if branches merge

{% enddetails %}
{% details Example: Oscillatory %}

- Problem statements: 
    - develop a reusable system architecture for oscilloscopes. 
    - An oscilloscope is an instrumentation system that 
        - samples electrical signals and displays pictures (called traces) of them on 
        a screen,
        - perform measurements on the signals, and 
        - display these on the screen.
    - Modern oscilloscopes rely primarily on digital technology and 
    have quite complex software: 
        - perform dozens of measurements, 
        - supply megabytes of internal storage, 
        - interface to a network of workstations and other instruments,
        - provide sophisticated user interface including a touch panel 
        screen with menus, built-in help facilities, and color displays.
    - Problem 1: there was little reuse across different oscilloscope products. 
    - Problem 2: there were increasing performance problems because the 
    software was not rapidly configurable within the instrument. 
- User requirements: 
    - develop an architectural framework for oscilloscopes that would address
     these problems. 
    - a domain-specific software architecture that formed the basis of 
    the next generation of Tektronix oscilloscopes. 

{% enddetails %}
{% details Oscillatory: layered model %}

{% include figure.liquid path="assets/img/courses/csc402/layered_models.png" width="50%" zoomable=true %}

- Model design
    - The core layer represented the signal manipulation functions that 
    filter signals as they enter the oscilloscope. 
    - The next layer represented waveform acquisition where signals are 
    digitized and stored internally for later processing. 
    - The third layer consisted of waveform manipulation, including measurement, 
    waveform addition, Fourier transformation, etc. 
    - The fourth layer consisted of display functions
    - The outermost layer was the user interface. 
- Analysis
    - Intuitively appealing since it partitioned the functions of an oscilloscope 
    into well-defined groupings. 
    - Wrong model for the application domain. 
        - The boundaries of abstraction enforced by the layers conflicted 
        with the needs for interaction between the various functions. 
        - For example, the model suggests that all user interactions with an oscilloscope 
        should be in terms of the visual representations. 
        - In practice real oscilloscope users need to directly affect the functions in 
        all layers. 

{% enddetails %}
{% details Oscillatory: pipe and filter %}

{% include figure.liquid path="assets/img/courses/csc402/pipeline.png" width="50%" zoomable=true %}

- Model design
    - Oscilloscope functions were viewed as incremental transformers of data. 
        - Signal transformers serve to condition external signals. 
        - Acquisition transformers derive digitized waveforms from these signals. 
        - Display transformers convert these waveforms into visual data.
        - Accounted for user inputs by associating with each filter a 
        control interface that allows an external entity to set parameters of 
        operation for the filter.
- Analysis
    - Pipe and filter computational model led to poor performance. 
        - Waveforms can occupy a large amount of internal storage
        - Different filters may run at radically different speeds
    - To handle these problems the model was further specialized. 
        - Several `colors` of pipes were introduced. 
        - Some of these allowed data to be processed without copying. 
        - Others permitted data to be ignored by slow filters if they were 
        in the middle of processing other data.

{% enddetails %}
{% details Repository %}

- Couple subsystems via shared data
    - Repository may need to support atomic transactions
- Advantages:
    - Components are independent (low coupling)
    - Centralized state storage (good for backups)
- Dangers:
    - Bottleneck / single point of failure

{% include figure.liquid path="assets/img/courses/csc402/repository.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Repository: flexibility through indirection %}

- Repository is highly coupled – difficult to change data store
- By defining higher-level storage access interface, data store is now lightly coupled

{% include figure.liquid path="assets/img/courses/csc402/repository_indirection.png" width="50%" zoomable=true %}
{% enddetails %}
