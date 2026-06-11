---
layout: lecture
pretty_table: true
collection: csc331

title: "A Gentle Introduction to ROS"
toc:
  - name: Overview
  - name: Core ROS 2 Concept
  - name: Data Distribution Service
  - name: What Robots Use ROS 2?
---
# A Gentle Introduction to ROS

---

## Overview

{% details Motivation %}

- Robots have many components: 
    - sensors, actuators
    - perception, planning, action, control.
- These components are built by different teams, update independently, and communicate at different rates.
- ROS 2 solves the problem of coordinating them reliably.

{% enddetails %}
{% details ROS %}

- [Robot Operating System](https://docs.ros.org/en/foxy/index.html)
    - Is a `middleware` running on top of Linux
    - Is a communication framework for robotics
    - Uses message passing, publish–subscribe, services, actions
- [Latest documentation](https://docs.ros.org/en/kilted/index.html)
- Not an operating system, despite the name

{% enddetails %}
{% details Why ROS Exists %}

- [The origin story](https://spectrum.ieee.org/the-origin-story-of-ros-the-linux-of-robotics)
- Original Authors: Keenan Wyrobek and Eric Berger, Ph.D. students at Standford in 2010.

{% details Before ROS %}

- Every robotics team wrote bespoke drivers
- No shared message formats
- No common build system
- High integration cost

{% enddetails %}
{% details warning Vision %}

- A Linux of Robotics
- Initially considered a crazy idea!

{% enddetails %}
{% details success ROS standardized %}

- Node-based architecture
- Message definitions  
- Communication semantics
- Reusable libraries (TF, Nav2, MoveIt)

{% enddetails %}
{% enddetails %}
{% details Quic summary: ROS 1 vs ROS 2 %}

- DDS-based (Data Distribution Service) communication layer
- Real-time support
- Multi-robot and multi-host support
- Security (DDS-Security plugins)
- Better Windows/Mac support
- Modern C++ / Python APIs

{% enddetails %}
## Core ROS 2 Concept:

{% details Nodes %}

- A node is a single-purpose program.
- Examples:
    - `camera_node` produces images
    - `lidar_node` publishes scans
    - `planner_node` computes trajectories
    - `controller_node` sends motor commands
- Nodes can be written in C++ (rclcpp) or Python (rclpy).

{% enddetails %}
{% details Topics %}

- Topics implement publish–subscribe messaging.
    - Asynchronous broadcast
- **Topics are abstractions for message channels**.
- Properties:
    - Asynchronous
    - Multi-producer, multi-consumer
    - Typed messages via .msg files
    - Transported through DDS
- Example:
    - /camera/image_raw
    - /scan
    - /cmd_vel

{% enddetails %}
{% details Services %}

- Services implement synchronous request–reply.   
    - Synchronous request-responses (RPC)
- Used when a node needs an answer now.
- Example:
    - Resetting sensors
    - Requesting a map
    - Triggering calibration

{% enddetails %}
{% details Actions %}

- Actions support long-running tasks.
    - Somewhat similar to async Future (Javascript)
- Provides:
    - Goal
    - Feedback
    - Result
    - Cancellation
- Examples:
    - Move robot arm to position
    - Navigate to point
    - Execute motion trajectories

{% enddetails %}
{% details ROS Graph %}

- Is the runtime `connectivity structure` formed by:
    - Nodes, Topics, Services, Actions
    - Parameters, QoS relationships
- Is not static
- Is discovered dynamically through DDS:
    - All nodes announce themslves and their endpoints (topics/services) to DDS
        - Actions are invoked by Nodes
    - DDS automatically builds a discovery graph and informs all participants.
    - `zero configuration`.
- ROS Graph: Organizational blueprint of a robot's software mind.

{% enddetails %}
## Data Distribution Service

{% details External vendors %}

- FastDDS
- CycloneDDS

{% enddetails %}
{% details What does it provide? %}

- Discovery (no central master)
- QoS policies
- Transport reliability settings
- Multi-host communication

{% enddetails %}
{% details DDS: Quality of Service %}

- Critical in robotics.
- Key policies:
    - Reliability: Reliable vs Best-effort
    - History: Keep last N messages
    - Durability: Transient-local for late subscribers
    - Deadline: Expected publication frequency

{% enddetails %}
{% details Parameters %}

- Nodes have runtime parameters.  
- Example: camera resolution, update rate, PID gains.

{% enddetails %}
## What Robots Use ROS 2?

- Clearpath Jackal, Husky, Ridgeback
- TurtleBot 4
- Mobile manipulators using MoveIt 2
- NASA VIPER (prototype phases used ROS components)
- Many autonomous research platforms

{% details Key Takeaways %}

- ROS 2 is middleware for modular robotics
- Nodes communicate via DDS topics/services/actions
- Tools and conventions streamline complex systems
- Great platform for experimentation
- Concepts generalize to distributed systems, realtime, and event-driven architectures
{% enddetails %}
