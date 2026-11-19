---
layout: lecture
pretty_table: true
collection: csc331

title: "A Gentle Introduction to ROS"
toc:
  - name: Overview
  - name: Core ROS 2 Concepts
  - name: Data Distribution Service
  - name: What Robots Use ROS 2?
---

## Overview

- A robot's kernel and a robot's software graph solve different problems.
  The kernel multiplexes CPU, memory, and devices. Above it, perception,
  planning, and control are separate programs, written by different people,
  running at different rates.
- [ROS](https://docs.ros.org/en/lyrical/index.html) (Robot Operating System)
  is middleware, libraries, and tools that connect those programs. The
  current long-term support release is **Lyrical Luth** (May 2026, supported
  through May 2031).

{% details Motivation %}

- A robot is a collection of components:
    - sensors and actuators
    - perception, planning, and control
- Those components are developed separately, updated separately, and produce
  data at different rates.
- ROS 2 gives them a common way to find each other, exchange typed messages,
  and agree on delivery rules.

{% enddetails %}

{% details What the name refers to %}

- ROS is middleware plus libraries, message definitions, and command-line
  tools. It runs on an operating system: commonly Linux, also Windows, and
  macOS at a lower support tier.
- The client libraries are layered. `rcl` is the common C library. `rclcpp`
  and `rclpy` wrap it for C++ and Python.
- **micro-ROS** is a client for microcontrollers, often on FreeRTOS, Zephyr,
  or NuttX. It is still a library sitting on that real-time operating system.

{% enddetails %}
{% details Why ROS exists %}

- Around 2006, Eric Berger and Keenan Wyrobek, then Ph.D. students in Kenneth
  Salisbury's lab at Stanford, started the Stanford Personal Robotics Program.
  Their complaint was practical: every project rebuilt drivers, message
  formats, and tools, so combining two labs' work was slow.
- Morgan Quigley's Switchyard, written for the Stanford AI Robot (STAIR),
  contributed much of the early communication design.
- Scott Hassan funded the effort at Willow Garage. The pitch that sold the
  project was "the Linux of robotics": a shared, open base that later robot
  software could build on.
- The first public ROS repository was created at Willow Garage on 7 November
  2007. ROS 1.0, named Box Turtle, was released on 2 March 2010.
- Earlier frameworks, including Player/Stage, CARMEN, and YARP, already
  existed. ROS spread because Willow Garage paired the software with a common
  robot, the PR2, and with reusable libraries.
- After Willow Garage closed, the Open Source Robotics Foundation (Open
  Robotics) became the steward of the project.
- Sources: [Wyrobek's origin story](https://spectrum.ieee.org/the-origin-story-of-ros-the-linux-of-robotics)
  and the [Willow Garage oral history](https://spectrum.ieee.org/wizards-of-ros-willow-garage-and-the-making-of-the-robot-operating-system)
  in IEEE Spectrum.

{% enddetails %}

{% details ROS 1 and ROS 2 %}

- ROS 2, begun in the mid-2010s, keeps the node-and-message model and replaces
  the custom transport and the central master.
- ROS 1 Noetic, the final ROS 1 release, reached end of life on 31 May 2025.

| Mechanism | ROS 1 | ROS 2 |
| --- | --- | --- |
| Discovery | A ROS Master, started by `roscore`, records publishers and subscribers. Data then flows peer to peer. | Participants announce themselves through the middleware, and data flows peer to peer. |
| Transport | TCPROS and UDPROS. | DDS/RTPS by default, through a replaceable middleware interface. |
| Parameters | One global parameter server. | Each node owns its parameters. |
| Real-time | Real-time behavior was outside the design. | The APIs, executors, and quality-of-service settings are built so a node can run on a real-time operating system. |
| Security | No standard security model in ordinary use. | Optional DDS-Security, configured with SROS 2. |
| Platforms | Centered on Ubuntu. | Lyrical's top tier is Ubuntu 26.04 and Windows 11. macOS is supported at a lower tier. |

{% enddetails %}

## Core ROS 2 Concepts

- A running ROS system is a graph of **nodes** connected by **topics**,
  **services**, and **actions**. **Parameters** configure a node without
  rewriting it.

{% details Nodes %}

- A node is one unit of ROS computation, usually with one job:
    - a camera node publishes images
    - a lidar node publishes scans
    - a planner computes a trajectory
    - a controller sends motor commands
- A node and an operating-system process are different objects. They often
  coincide: one program, one process, one node.
- In C++, several nodes can be composed into a single process. Messages
  between those nodes can stay inside the process instead of crossing the
  middleware. The process is still the kernel's unit of isolation and
  scheduling.
- A lifecycle node makes startup explicit, with states such as unconfigured,
  inactive, and active, so a system can bring up sensing before control.

{% enddetails %}
{% details Topics %}

- A topic is a named, typed channel. Publishers send messages; subscribers
  receive them. Communication is asynchronous, and many publishers and
  subscribers may share one topic.
- The type is declared in a `.msg` file. The `rosidl` tools generate the C
  and Python code for that layout.
- Names you will see on real robots:
    - `/camera/image_raw`, type `sensor_msgs/msg/Image`
    - `/scan`, type `sensor_msgs/msg/LaserScan`
    - `/cmd_vel`, type `geometry_msgs/msg/Twist`

{% enddetails %}
{% details Services %}

- A service is a request and a reply, declared in a `.srv` file.
- It fits a short question that has an answer: trigger a calibration, reset a
  sensor, or ask for the current map.
- Client libraries offer a call that waits for the reply and a call that
  returns control immediately and completes later.
- Services use reliable delivery and volatile durability. A restarted server
  therefore receives only requests issued after it is back.

{% enddetails %}
{% details Actions %}

- An action is the interface for a long task: navigate to a pose, move an
  arm, or follow a trajectory.
- The client sends a **goal**. The server sends **feedback** while the work
  continues, then a **result**. The client can **cancel** the goal.
- The interface is declared in an `.action` file. Underneath, ROS 2
  implements each action as three services (goal, cancel, and result) and two
  topics (feedback and status). Those endpoints are discovered like any other
  service or topic.
- Examples: `nav2_msgs/action/NavigateToPose` and
  `control_msgs/action/FollowJointTrajectory`.

{% enddetails %}
{% details Parameters %}

- Each node keeps named, typed values: a camera frame rate, a PID gain, or
  `use_sim_time`.
- `ros2 param list` and `ros2 param set` read and change them while the node
  is running.
- Parameter events travel through the middleware. The stored values belong to
  that node; another node reads them by querying it or by listening for
  parameter events.

{% enddetails %}

{% details The ROS graph %}

- The ROS graph is the set of live nodes and the topics, services, actions,
  and parameters that connect them.
- The graph changes as nodes start and stop. Each participant announces its
  endpoints, and the middleware distributes those announcements. On a shared
  local network, default DDS discovery does this by multicast.
- Separate subnets and isolated containers need explicit discovery
  configuration, such as a discovery server or a list of initial peers.
- Useful inspection commands:
    - `ros2 node list`
    - `ros2 topic list`
    - `ros2 topic echo /scan`
    - `rqt_graph`, which draws the same structure

{% enddetails %}

## Data Distribution Service

- ROS 2 application code talks to a **ROS middleware interface** (`rmw`).
  The default implementation in Lyrical is eProsima's **Fast DDS**
  (`rmw_fastrtps_cpp`). DDS is an OMG standard; RTPS is its wire protocol.

{% details The middleware is replaceable %}

- The nodes stay the same across implementations. Select an adapter with
  the `RMW_IMPLEMENTATION` environment variable.
- DDS implementations shipped or supported with current ROS 2:
    - eProsima Fast DDS, the default
    - Eclipse Cyclone DDS
    - RTI Connext DDS, installed separately from the ROS binaries
    - GurumNetworks GurumDDS, a community-supported DDS
- Eclipse **Zenoh** (`rmw_zenoh_cpp`) is a non-DDS middleware. It has been
  fully supported and packaged with the binaries since Kilted Kaiju. Lyrical
  kept Fast DDS as the default.
- Vendor list and status:
  [About different middleware vendors](https://docs.ros.org/en/lyrical/Concepts/Intermediate/About-Different-Middleware-Vendors.html).

{% enddetails %}
{% details What DDS provides %}

- Distributed discovery. Participants find each other by announcement, using
  multicast on a local network, rather than by registering with a master.
- A typed publish/subscribe transport.
- Quality-of-service policies that travel with the data.
- Communication among processes on one machine and among machines on one
  network.

{% enddetails %}
{% details Quality of service %}

- A quality-of-service profile is a contract between a sender and a receiver.
  ROS 2 exposes these policies on publishers, subscriptions, and service
  endpoints:
    - **History.** Keep the last *N* samples, or keep all samples subject to
      resource limits. *N* is the queue depth. The default depth is 10.
    - **Reliability.** Reliable delivery retries lost samples. Best effort
      may drop them. Camera and lidar streams often use best effort.
    - **Durability.** Volatile data exists only while it is in flight.
      Transient local means the publisher keeps samples for a subscriber that
      joins later. A map is a typical transient-local topic; this is the ROS 2
      version of a ROS 1 latched topic.
    - **Deadline.** The maximum expected time between messages on that topic.
    - **Lifespan.** How long a sample may sit before it is too old to deliver.
    - **Liveliness.** How a publisher shows that it is still alive, and how
      long a receiver will wait before treating it as gone.
- The default profile is keep-last, depth 10, reliable, and volatile.
- Reference:
  [About quality of service settings](https://docs.ros.org/en/lyrical/Concepts/Intermediate/About-Quality-of-Service-Settings.html).

{% enddetails %}
{% details warning Endpoints must be compatible %}

- Matching uses the topic name, the message type, and the quality-of-service
  profile.
- A subscriber that asks for reliable delivery connects only to a reliable
  publisher. A best-effort camera publisher and a reliable subscriber stay
  disconnected even when the name and type agree.
- `ros2 topic info /scan --verbose` shows the offered and requested profiles.

{% enddetails %}
{% details Real-time behavior and security %}

- A deadline in a quality-of-service profile records an expectation. The
  operating system enforces CPU time. Meeting a hard deadline takes a
  real-time kernel such as Linux with PREEMPT_RT or a separate RTOS, an
  executor built for that setting, and node code whose allocation and
  blocking are bounded.
- Emergency stops and actuator limits stay appropriate work for a small
  controller or a safety-rated component. A late high-level node is a bad
  place to discover that a motor must turn off.
- DDS-Security can authenticate participants, restrict which nodes may
  publish or subscribe, and encrypt traffic. SROS 2 creates that
  configuration. A default ROS 2 graph runs without it until someone turns
  it on.

{% enddetails %}

## What Robots Use ROS 2?

- Clearpath's Jackal, Husky, and Ridgeback, using ROS 2 drivers.
- TurtleBot 4, a teaching platform built around ROS 2.
- Mobile robots navigated with Nav2, and arms planned with MoveIt 2.
- Research platforms that reuse tf2 for coordinate frames, Nav2 for
  navigation, and MoveIt 2 for manipulation.

{% details NASA VIPER %}

- VIPER (Volatiles Investigating Polar Exploration Rover) splits its software
  across two stacks.
- The rover's own flight software is NASA's Core Flight System (cFS), running
  on radiation-hardened computers under VxWorks. It handles devices, basic
  mobility, and operational safety.
- ROS 2 runs off the rover, in the ground software: visual odometry, terrain
  mapping, hazard maps, and decision support for the human drivers. A Gazebo
  simulator exercises that stack.
- NASA cancelled the original VIPER project on 17 July 2024. In September
  2025 it selected Blue Origin to deliver the rover to the lunar south pole,
  with a landing targeted for late 2027.
- Sources: [NASA, "VIPER's Many Brains"](https://www.nasa.gov/technology/robotics/vipers-many-brains-are-better-than-one/),
  the [flight-software design](https://ntrs.nasa.gov/citations/20220000035),
  and the [Blue Origin delivery award](https://www.nasa.gov/news-release/nasa-selects-blue-origin-to-deliver-viper-rover-to-moons-south-pole/).

{% enddetails %}
{% details Active ROS 2 releases %}

- **Lyrical Luth**, 22 May 2026 through May 2031. Current long-term support
  release, and the documentation this lecture links to.
- **Jazzy Jalisco**, May 2024 through May 2029. Long-term support.
- **Humble Hawksbill**, May 2022 through May 2027. Long-term support.
- **Kilted Kaiju**, May 2025 through late 2026. A short-support release, so
  it is a poor target for new work now.
- **Rolling Ridley** is the moving development distribution.
- Foxy Fitzroy ended support in June 2023.

{% enddetails %}

{% details success Key takeaways %}

- ROS 2 is middleware for a modular robot. The kernel underneath it is still
  Linux, Windows, or a real-time operating system.
- Nodes communicate by topics, services, and actions. An action is a pattern
  built from services and topics, with a goal, feedback, a result, and
  cancellation.
- Discovery and delivery contracts come from the middleware. Fast DDS is the
  default; Zenoh and other implementations can replace it.
- The same questions show up in any distributed system:
    - Which messages may be dropped, and which must be retried?
    - What should a late joiner already know?
    - What happens when the process providing a service disappears?
    - Which loop is allowed to miss a deadline, and which component must
      still be able to stop the robot?

{% enddetails %}

- Further reading:
    - [ROS 2 Lyrical documentation](https://docs.ros.org/en/lyrical/index.html)
    - [ROS 2 design articles](https://design.ros2.org/)
    - [Middleware vendors](https://docs.ros.org/en/lyrical/Concepts/Intermediate/About-Different-Middleware-Vendors.html)
    - [Quality of service](https://docs.ros.org/en/lyrical/Concepts/Intermediate/About-Quality-of-Service-Settings.html)
