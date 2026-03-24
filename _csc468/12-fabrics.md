---
layout: lecture
pretty_table: true
order: 1
title: Introduction to FABRIC
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
last_updated: 2026-03-22

toc:
  - name: "Beyond CloudLab: FABRIC"
  - name: "Working with Slices and Sites"
  - name: "Hands-on: Provisioning a Simple FABRIC Slice"
---

## Beyond CloudLab: FABRIC




???note "From Reconfigurable Clusters to Programmable Infrastructure"
    - CloudLab taught us an important model: reserve bare-metal machines, install what we want, and treat the testbed as a reproducible research cluster.
    - **FABRIC** keeps that spirit, but extends the experiment boundary beyond a local cluster.
    - Instead of viewing the network as background plumbing, FABRIC treats the **wide-area network itself** as part of the experiment.
    - A more accurate description is this:
        - **CloudLab**: build and study cloud/distributed systems on reconfigurable bare-metal clusters.
        - **FABRIC**: build and study distributed systems on a **programmable end-to-end fabric** spanning multiple sites.

???note "Deep Programmability"
    - In earlier lectures, we defined **Deep Programmability** as the ability to influence the behavior of computing, storage, and routing components deep inside the infrastructure [2].
    - FABRIC is a good example of that idea because it combines:
        - compute nodes at multiple sites,
        - programmable network services between sites,
        - optional accelerators and specialized components,
        - and experiment slices that can span a national research network.
    - This is why FABRIC should be narrated as a **conceptual shift**, not merely as "CloudLab with newer hardware."

???note "The Right Teaching Narrative"
    - Avoid saying: "FABRIC replaces CloudLab."
    - Prefer saying:
        - "FABRIC extends the testbed model from reconfigurable clusters to programmable, cross-site infrastructure."
        - "CloudLab emphasizes cluster and cloud construction; FABRIC emphasizes distributed experiments whose network paths also matter."

## Working with Slices and Sites

???note "The Core Abstraction: The Slice"
    - In FABRIC, an experiment is packaged as a **slice**.
    - A slice contains the resources reserved for one experiment, such as:
        - nodes,
        - interfaces,
        - storage/components,
        - and network services.
    - This is the unit students create, submit, inspect, renew, and delete.

???note "Does FABRIC Eliminate Site Selection?"
    - **No.** FABRIC makes cross-site experiments more natural, but it does **not** make site placement irrelevant.
    - In fact, site choice is often part of the experiment design:
        - for reproducibility,
        - for geographic latency differences,
        - for special hardware availability,
        - or for building a specific multi-site topology.
    - FABRIC can place a node on a random site if no site is specified, but serious experiments usually choose sites intentionally.

???note "What 'Programmable End-to-End Infrastructure' Actually Means"
    - The phrase **programmable end-to-end infrastructure involving networking, slicing, acceleration, and cross-site experiments** does **not** mean:
        - "you never have to think about sites again."
    - It **does** mean:
        - the platform already understands nodes, links, and network services as first-class resources,
        - cross-site links are part of the testbed design rather than an afterthought,
        - and the API lets you describe a topology instead of manually stitching together independent machines.
    - So FABRIC is **more convenient for launching multi-site experiments**, but it is **not fully site-agnostic**.

???note "A Practical Rule of Thumb"
    - If you are teaching a simple single-site lab, you may allow FABRIC to choose a site automatically.
    - If you are teaching a reproducible experiment, a latency-sensitive system, or a WAN/networking topic, you should specify the sites explicitly.
    - In other words:
        - **site omitted** = convenient default,
        - **site specified** = clearer intent and better reproducibility.

## Infrastructure as Code with FABRIC

???note "Why FABlib is the Better Introductory Tool"
    - In practice, the student-facing FABRIC workflow is usually built around **FABlib** in Python notebooks or scripts.
    - FABlib lets us create slices, add nodes, inspect resources, and connect services programmatically.
    - For this lecture, FABlib is a better first step than jumping directly into lower-level orchestration ideas.

???note "Resource Graph Thinking Still Applies"
    - Even though we are not focusing on Terraform here, the same systems idea still matters:
        - a node must exist before its interfaces can be attached,
        - interfaces must exist before a network service can connect them,
        - and a slice must be submitted before students can SSH into the nodes.
    - The dependency graph is still there; FABRIC simply exposes it through slice operations rather than through a generic Terraform lesson.

???note "Immutable Mindset"
    - Traditional administration says: log into the machine and repair it by hand.
    - Experimental infrastructure says: define the desired topology, recreate it cleanly, and keep the experiment reproducible.
    - That mindset still maps well to modern cloud engineering [2, 4].

## Hands-on: Provisioning a Simple FABRIC Slice

???note "What We Will Build"
    - A minimal first experiment should be small:
        - two nodes,
        - optionally at two different sites,
        - connected as part of one slice.
    - The goal is not to use every FABRIC feature at once.
    - The goal is to help students understand the workflow:
        - inspect resources,
        - create a slice,
        - place nodes,
        - submit,
        - and then log in.

???note "Example with FABlib"
    - In a Python notebook or script:
    ~~~python
    from fabrictestbed_extensions.fablib.fablib import FablibManager as fablib_manager

    fablib = fablib_manager()

    # Create a new slice
    slice = fablib.new_slice(name="intro-fabric")

    # Option 1: let FABRIC choose sites automatically
    n1 = slice.add_node(name="n1")
    n2 = slice.add_node(name="n2")

    # Option 2: choose sites explicitly for reproducibility
    # n1 = slice.add_node(name="n1", site="STAR")
    # n2 = slice.add_node(name="n2", site="MASS")

    # Submit the request to the testbed
    slice.submit()

    # Later, inspect the running slice
    slice.list_nodes()
    ~~~
    - Notice the central vocabulary:
        - `new_slice()`
        - `add_node()`
        - `submit()`
        - `list_nodes()`

???note "Interpretation"
    - This example also answers an important conceptual question:
        - FABRIC can choose a site **by default**,
        - but the API still gives us the ability to specify sites when site placement matters.
    - Therefore, FABRIC is **streamlined for multi-site experimentation**, but it does **not hide topology design from the user**.

???note "Where We Go Next"
    - In later lectures or labs, we can extend this simple slice by:
        - adding explicit network services,
        - comparing single-site versus cross-site latency,
        - attaching specialized components,
        - or building a small routed topology across several sites.
    - That is where FABRIC really begins to differ from the simpler "reserve a few machines in one place" mindset.
