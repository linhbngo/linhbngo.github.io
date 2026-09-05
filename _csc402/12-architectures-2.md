---
layout: lecture
pretty_table: true
order: 14
title: "More Architectures Styles"
mermaid:
  enabled: true
  zoomable: true
code_diff: true
map: true
chart:
  chartjs: true
  echarts: true
  vega_lite: true
tikzjax: true
typograms: true

toc:
  - name: Three-tier architecture
  - name: Model-view-controller
  - name: Publish-Subscribe
---

# More Architectures Styles

## Three-tier architecture

{% details Overview %}

- Extension of client/server model
- Commonly used for small-medium web sites
    - Example: LAMP stack

{% enddetails %}
{% details Example %}

- Naive client/server

{% include figure.liquid path="assets/img/courses/csc402/client_server.png" max-width="50%" zoomable=true %}

- Data store extension

{% include figure.liquid path="assets/img/courses/csc402/client_server_data.png" max-width="50%" zoomable=true %}

- Data store extension with component diagrams:
    - Any web browser can access the website
    - Database can be replaced by another that supports the same interface

{% include figure.liquid path="assets/img/courses/csc402/3_tier.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% details Architectural style %}


{% include figure.liquid path="assets/img/courses/csc402/3_tier_architecture.png" max-width="50%" zoomable=true %}


{% enddetails %}
{% details Presentation tier complexity %}

- As long as same interface, this is still a binary-replaceable component

{% include figure.liquid path="assets/img/courses/csc402/3_tier_presentation.png" max-width="50%" zoomable=true %}


{% enddetails %}
## Model-view-controller

{% details Component diagram %}


{% include figure.liquid path="assets/img/courses/csc402/mvc_diagram.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% details Features %}


- Separated presentation
    - Decoupled model and view (replaceable components)
    - Multiple (possibly simultaneous) views supported

{% enddetails %}
{% details Example %}

- Mission Control terminal
    - A vehicle (unmanned aircraft) is flown by a pilot interfacing 
    with a computer terminal on the ground
    - Vehicle communicates with ground station via radio signals
        - Actuation commands (uplink): change throttle, angle flaps, etc.
        - Sensor measurements (downlink): air speed, GPS position, actuator 
        settings, etc.
- View
    - Graphical user interface shows model properties (sensor readings, 
    derived state) as instrument dials and provides input widgets for commanding actuators
- Model
    - Maintain record of state of vehicle 
    - Computes derived properties of vehicle (rate of turn, predicted 
    trajectory, ...)
    - Updates state in response to actions from controller (e.g. new 
    telemetry received)
    - Provides view with information to be displayed to user
    - Different vehicles will need different models but might not require new 
    views or controllers.
- Controller: Pilot wishes to change flap angle to 20 deg to increase lift 
and accommodate a slower speed for landing.
    - View sends message to controller: setFlaps(20)
    - Controller sends radio command to vehicle: setFlaps(20)
    - Vehicle acts on command and replies to controller: flapsSet(20)
    - Controller relays telemetry to model: flapsSet(20)
    - Model updates state and recomputes stall speed
    - Model notifies view of new state (flap setting, stall speed)
    - View displays new state in user interface

{% enddetails %}
{% details View %}

- Presents application state and controls to user
- Typically subscribes to model for notifications of state changes
- "Observer pattern"
- Responsible for rendering to a particular interface
- Drawing graphics, generating HTML, printing text
- Sends user input to controller
- A single model can support multiple views
- Example: web app, native app

{% enddetails %}
{% details Model %}

- Records state of application and notifies subscribers
- Responds to instructions to change state (from controller)
- Does not depend on either controller or view
- State may be stored in objects or databases
- May be responsible for some application logic (e.g. input validation)

{% enddetails %}
{% details Controller %}

- Manages user input and navigation
- Defines application behavior
- Maps user actions to changes in state (model) or view
- May interact with external services via APIs
- May be responsible for some application logic (e.g. input validation)
- Variety in distribution of duties between model and controller

{% enddetails %}
## Publish-Subscribe

{% details Overview %}

- Event-driven control
    - Application responds to external stimuli and timeouts
    - No centralized orchestration
- Very loose coupling – components communicate via message broker
    - Easy to extend
    - Difficult to analyze (observer pattern)
        - No control over what (if any) code responds to an event
        - Potential for conflicts (multiple components respond in incompatible ways)
        - Potential for silently dropped events
        - Call stacks may not reflect causality
{% enddetails %}
