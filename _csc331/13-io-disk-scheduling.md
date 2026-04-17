---
layout: lecture
pretty_table: true
collection: csc331

title: "I/O and Disks: Disk Scheduling"
toc:
  - name: Input/Output devices
  - name: A Canonical Device
  - name: Hardware interrupts
  - name: Programmed I/O overheads
  - name: Method of device interaction
  - name: Device driver
  - name: Disk Drive
  - name: Disk scheduling
---

# I/O and Disks: Disk Scheduling

---

## Input/Output devices

{% details Overview %}

- Critical to computer systems
    - Without input: Same results every time.
    - Without output: What’s the point?
- How should I/O be integrated into systems?
- What are the general mechanisms?
- How can we make them efficient?

{% enddetails %}
{% details Classical system architecture %}

- Hierarchical structure due to the relationship between physics and costs:
- The faster the bus, the shorter it is. 
- The faster the bus, the more complex it is to design and build (hence more costly). 

{% include figure.liquid path="assets/img/courses/csc331/io/01.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Modern system architecture %}

- Specialized chipsets and faster point-to-point interconnects. 

{% include figure.liquid path="assets/img/courses/csc331/io/02.png" width="50%" zoomable=true %}

{% enddetails %}
---

## A Canonical Device

{% details A common abstraction %}

- Conceptual model/template for all I/O devices. 
- Interface: allowing system software to control the device's operations
    - Initialize/configure
    - Start/stop operation
    - Check status/handle interrupts
    - Bridged with OS by `device driver`. 
- Internal structure: implementing the abstraction presented to the system.  
    - Controller/firmware
    - Registers
    - Buffer memory
    - Bus interface
- Common Abbreviations:
    - DMI: Direct Memory Interface
    - ATA: IBM's PC AT Attachment. 
    - SATA: Serial ATA
    - eSATA: External Serial ATA
    - PCIe: Peripheral Component Interconnect Express

{% include figure.liquid path="assets/img/courses/csc331/io/03.png" width="50%" zoomable=true %}

{% enddetails %}
{% details A simple canonical protocol %}

- Repeatedly read the register for READY status.
- Send data to register (Programmed I/O - PIO).
- Write a command to the command register to initiate device execution.
- Wait until the device is done.  
- What is a problem with this approach?

{% include figure.liquid path="assets/img/courses/csc331/io/04.png" width="50%" zoomable=true %}

{% enddetails %}
---

## Hardware interrupts

- Instead of polling the device, the OS can:
    - After issue an I/O request, put the calling process to sleep and context switch 
  to another.
    -  When the request is finished, the device will raised a hardware interrupt to 
    return CPU to the OS.
- Predetermined interrupt service routine (ISR) - interrupt handler.
    - This allows overlap of computation and I/O (recall CPU scheduling slides)
- To avoid interrupts all the time, a hybrid model is employed (scheduling). 

{% include figure.liquid path="assets/img/courses/csc331/io/05.png" width="50%" zoomable=true %}



## Programmed I/O overheads

- Programmed I/O: I/O instructions that move data from storage into register
for computation purposed. This requires the CPU's involvement in every transactions. 
- With programmed I/O, the CPU spends too much time moving data to and from devices. 
- How do we offload this work: Direct Memory Access (DMA) device
    - Orchestrate transfer between devices and main memory without much CPU intervention.
- Example: Intel Broadwell Crystal Beach DMA Application
    - Supports write operations from memory to I/O, but not from I/O to memory
    - Instantiated as a root complex integrated PCIe end-point device
    - Chipset DMA that is controllable by software executing on the processor
    - A standardized software interface for controlling and accessing DMA features
    - There are eight software visible CB DMA engines, visible as PCI functions. 
        - Each engine has one channel. 
        - Each can be independently operated. 
        - In a virtualized system, each can be independently assigned to a VM. 
- Copying of data is handled by DMA controller. 

{% include figure.liquid path="assets/img/courses/csc331/io/06.png" width="50%" zoomable=true %}

---

## Method of device interaction

- First method 
    - Explicit I/O instructions (privileged)
- Second method
    - Memory-mapped I/O
- The hardware makes the device registers available as if they were memory 
locations.
- No clear advantages on either method

---

## Device driver

- How to fit various I/O devices with different interfaces into the OS 
(which is supposed to be generic)?
- Abstraction, abstraction and abstraction: device driver
- 70% of OS code is found in device drivers.
- Unofficial device drivers are often the cause for kernel crashes. 
- Example:
    - [AMD Device Driver for Vulkan](https://gpuopen.com/amd-open-source-driver-for-vulkan/)
    - [API guide for Linux driver implementation](https://www.kernel.org/doc/html/v4.11/driver-api/index.html)

{% include figure.liquid path="assets/img/courses/csc331/io/07.png" width="50%" zoomable=true %}

## Disk Drive

{% details Overview %}

- Large number of sectors (512-byte blocks)
- Sectors are numbered 0 to n-1 on disks with n sectors. This is the address space of 
the drive. 
- Multi-sector operations are possible (read or write 4K bytes at a time). 
- Only a single 512-byte write is guaranteed atomic.

{% include figure.liquid path="assets/img/courses/csc331/io/08.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Seek, rotation, transfer %}


- Seek: move the disk arm to the correct cylinder
    - depends on how fast disk arm can move
    - typical time: 1-15ms, depending on distance (average 5-6ms)
    - improving very slowly: 7-10% per year
- Rotation: waiting for the sector to rotate under the head
    - depend on the rotation rate of the disk (7200 RPM SATA, 15K RPM SCSI)
    - average latency of ½ rotation (~4ms for 7200 RPM disk)
    - has not changed in recent years
- Transfer: transferring data from surface into disk controller 
electronics, or the other way around
    - depends on density, higher density, higher transfer rate
    - ~100MB/s, average sector transfer time of ~5 microseconds
    - improving rapidly (~40% per year)

{% enddetails %}
## Disk scheduling

{% details info Details %}

- The OS has a queue of disk requests, therefore there is a chance 
to schedule these requests
- We want to minimize seeking

{% enddetails %}
{% details FCFS (do nothing) %}

- reasonable when load is low, long waiting time when load is high

{% include figure.liquid path="assets/img/courses/csc331/io/09.png" width="50%" zoomable=true %}

{% enddetails %}
{% details SSTF (shortest seek time first) %}

- minimizes arm movement
- favors blocks in middle tracks, because they have more blocks nearby.

{% include figure.liquid path="assets/img/courses/csc331/io/10.png" width="50%" zoomable=true %}

{% enddetails %}
{% details SCAN (elevator) %}

- serve request in one direction until done, then reverse
- like an elevator, avoid going back and forth in the middle

{% include figure.liquid path="assets/img/courses/csc331/io/11.png" width="50%" zoomable=true %}

- C-SCAN (typewriter)
    - like SCAN, but only go in one direction (no reverse direction)
{% enddetails %}
{% details LOOK / C-LOOK %}

- like SCAN/C-SCAN, but only go as far as last request in each direction, 
instead of going full width of the disk. 

{% include figure.liquid path="assets/img/courses/csc331/io/12.png" width="50%" zoomable=true %}

{% enddetails %}
- Disk scheduling is important only when disk requests queue up
    - important for servers
    - not so much for PCs
- Modern disks often do disk scheduling themselves
    - Disks know their layout better than the OS, can optimize better
    - on-disk scheduling ignores, undoes any scheduling done by the OS

