---
layout: lecture
pretty_table: true
collection: csc331

title: "Microkernels versus monolithic kernels: MINIX, Linux, and robotics"
toc:
  - name: "From UNIX to MINIX and Linux"
  - name: "What belongs in the kernel?"
  - name: "MINIX: what is it?"
  - name: "MINIX: architecture"
  - name: "MINIX: pros and cons"
  - name: "Why kernel design matters for robots"
  - name: "Linux vs MINIX: the flame war of 1992"
---

## Logistics

- Final Exam: Thursday December 10, 10:30AM - 12:30PM. 

## From UNIX to MINIX and Linux

- **1965:** MIT, Bell Labs, and General Electric began developing Multics, an
  ambitious time-sharing system. Bell Labs withdrew from the project in 1969,
  but Multics influenced UNIX ideas such as a hierarchical file system,
  protection, and interactive computing.
- **1969:** Ken Thompson, Dennis Ritchie, and colleagues created UNIX at Bell
  Labs on a PDP-7.
- **1973:** UNIX Fourth Edition was rewritten in C. Keeping only a relatively
  small hardware-dependent layer in assembly made the system unusually
  portable.
- **1975:** UNIX Version 6 became the first version widely available outside
  Bell Labs. Its source code helped operating-systems research and teaching
  spread through universities.
- **1977–1979:** Berkeley's BSD family emerged, and Bell Labs released UNIX
  Version 7. V7 became an important ancestor of later commercial and academic
  Unix systems.
- **1983–1988:** GNU, System V, BSD, and POSIX shaped the Unix ecosystem.
  POSIX standardized the programming interface without requiring one kernel
  implementation.
- **1987:** Andrew S. Tanenbaum released MINIX 1 with *Operating Systems:
  Design and Implementation* so students could study a complete Unix-like
  system whose source was available.
- **1991:** Linus Torvalds announced Linux after learning from and experimenting
  with MINIX. Linux reused the Unix interface and many Unix ideas, but not the
  MINIX kernel.

{% details UNIX, Unix, and Unix-like %}

- **UNIX** is a trademark and a formal specification. A system may be certified
  against the Single UNIX Specification.
- **Unix** is often used historically for the family descended from the
  original Bell Labs system.
- **Unix-like** systems implement many Unix ideas and interfaces without
  necessarily containing original UNIX code or carrying UNIX certification.
  Linux and MINIX are Unix-like.

{% enddetails %}

- Sources: [The Open Group's UNIX history](https://www.unix.org/unix_history.html)
  and Dennis Ritchie's
  [The Evolution of the Unix Time-sharing System](https://www.nokia.com/bell-labs/about/dennis-m-ritchie/hist.pdf).

---

## What belongs in the kernel?

- A **kernel** runs in privileged mode and mediates access to CPU time, memory,
  devices, and other hardware.
- **Monolithic kernel**
    - Core services such as scheduling, virtual memory, file systems, network
      stacks, and many device drivers execute in kernel space.
    - Calls between kernel components are usually ordinary procedure calls,
      which can be fast.
    - A memory-safety bug in one kernel component can corrupt the entire kernel.
    - Monolithic does **not** mean inflexible or literally one source file.
      Linux is a *modular monolithic kernel*: many components can be loaded and
      unloaded as kernel modules, but loaded modules still share privileged
      kernel address space.
- **Microkernel**
    - Keeps only fundamental mechanisms—typically scheduling, low-level memory
      management, interrupt handling, and interprocess communication (IPC)—in
      privileged mode.
    - Services such as drivers, file systems, and network stacks can run as
      isolated user-space processes and communicate by messages.
    - Isolation can reduce the trusted computing base and contain faults, but
      crossing protection boundaries, copying data, scheduling another process,
      and message coordination can add overhead and design complexity.
- **Hybrid kernel**
    - Uses microkernel ideas but retains substantial services in kernel space
      for compatibility or performance. XNU (macOS/iOS) and Windows NT are
      commonly described as hybrid, although these labels are not precise
      standards.
- Architecture alone does not guarantee speed, security, reliability, or
  real-time behavior. Implementation quality, hardware support, scheduling,
  driver design, workload, and certification evidence all matter.

---

## MINIX: what is it?

- Development began with Dr. Andrew Tanenbaum in 1984; MINIX 1 and its
  accompanying textbook were released in 1987.
    - A small Unix-like operating system for teaching.
- Design goals:
    - Build a UNIX V7-like system that ran on an IBM PC with only a single
      360-kB floppy disk;
    - Build and maintain the system using itself, or "self-hosting";
    - Make the full source code available for study;
    - Have a clean design students could easily understand;
    - Make the (micro) kernel as small as possible, since kernel failures are fatal;
    - Break the rest of the operating system into independent user-mode processes;
    - Hide interrupts at a very low level;
    - Communicate only by synchronous message passing with clear protocols; and
    - Try to make the system port easily to future hardware.
- The name has covered substantially different systems:
    - **MINIX 1 and 2** primarily supported education.
    - **MINIX 3** (2005/2006) moved drivers into user space and emphasized
      reliability, fault isolation, and self-healing for embedded systems.

---

## MINIX: architecture

- The following describes **MINIX 3**, not every historical MINIX release.
- Microkernel:
    - Small
    - Handles interrupts, scheduling, low-level process management, and message
      passing.
    - Checks whether a caller is authorized to perform a privileged kernel
      operation.
- Device drivers:
    - **Run as isolated user-space processes.**
    - Each controls an I/O device but requests privileged operations through
      controlled kernel calls.
    - A faulty driver is less able to overwrite unrelated kernel memory.
- Server processes:
    - Implement services such as process management, virtual memory, and file
      systems.
    - A user process requests a service such as `open`, `read`, `write`, or
      `close`; libraries and servers exchange messages to perform it.
    - Servers may then communicate with the appropriate device driver.
    - The reincarnation server monitors other servers and drivers and can
      restart many failed components without rebooting the whole system.

{% include figure.liquid path="assets/img/courses/csc331/minix/01.png" max-width="50%" zoomable=true alt="MINIX" %}

---

## MINIX: pros and cons

- Advantages
    - Modularity: the system is well structured and the relationship between the 
    various components is equally well defined.
    - Security and fault isolation: the layered structure and microkernel design
      make it possible to give each service only the authority it needs. Most
      operating-system services run in user mode; only the microkernel runs with
      full kernel privileges.
    - Extensibility: in order to have a functional system, one needs the kernel setup 
    as well as the key services that are needed to start off. All the other functions 
    can be added as and when needed. This makes it simpler to extend and/or specialize 
    the function of the system.
    - Reliability: device drivers are a major source of operating-system faults.
      Isolating them from the kernel can prevent a driver failure from becoming
      a system-wide failure. MINIX 3 can restart some failed services.
- Disadvantages
    - IPC overhead: a service may require multiple messages, context switches,
      protection checks, and data transfers. The actual cost depends on the
      microkernel and workload; it is not one fixed number.
    - Distributed coordination: independent servers must agree on protocols,
      ordering, cancellation, recovery, and shared state.
    - Recovery is not automatic for every failure. Restarting a stateful file
      system or a service that controls physical hardware can require restoring
      or reconstructing state.
    - Ecosystem and drivers: a well-established monolithic system such as Linux
      may support more hardware and applications, regardless of architectural
      elegance.


## Why kernel design matters for robots

- A robot commonly contains several computing layers:
    - A microcontroller closes a motor-control loop under an RTOS or firmware.
    - A more capable computer runs perception, planning, logging, and networking,
      often on Linux or a real-time OS such as QNX.
    - ROS 2 connects application components through middleware.
- **ROS is not the kernel.** ROS 2 is a robotics software development platform
  and middleware ecosystem that runs *on top of* an operating system. A graph of
  isolated ROS nodes resembles a multiserver design, but it does not turn the
  underlying Linux kernel into a microkernel.
- ROS 1 relied on a central ROS Master for naming and discovery. ROS 2 normally
  uses DDS (Data Distribution Service)/RTPS (Real Time Publish/Subscribe) with distributed discovery and configurable quality of service. Its ROS Middleware (RMW) interface also allows multiple middleware
  implementations.
- **micro-ROS is not a microkernel.** It brings ROS 2 concepts to
  microcontrollers, commonly on FreeRTOS, Zephyr, or NuttX. A lightweight
  Micro XRCE-DDS client communicates with a micro-ROS Agent that represents the
  microcontroller's entities on the larger DDS network.

{% details A robot-design thought experiment %}

Consider a mobile robot with motor control, a safety lidar, cameras, localization,
and cloud telemetry:

- If a camera driver fails inside a monolithic kernel, the failure may panic or
  corrupt the entire system. Linux nevertheless offers high performance, mature
  drivers, loadable modules, process isolation for applications, and real-time
  improvements such as PREEMPT_RT.
- A microkernel can place the camera and network drivers in separate protection
  domains. Restarting one may preserve localization and motor control, but only
  if dependencies, hardware state, and recovery protocols were designed for it.
- Hard safety deadlines should not depend solely on a high-level ROS node.
  Emergency stops and actuator limits are often enforced by a separate
  controller, safety-certified component, or small real-time subsystem.
- A practical robot can therefore be **heterogeneous**: Linux and ROS 2 for
  compute-intensive autonomy, an RTOS and micro-ROS for constrained devices,
  and an independently engineered safety path.

{% enddetails %}

- Questions to ask when choosing an OS:
    - What is the worst-case response time, not just the average throughput?
    - Which failures must be contained, detected, and recovered?
    - Can a component restart safely while the robot is moving?
    - Which code belongs in the trusted or safety-critical computing base?
    - Are drivers, tooling, hardware support, and certification artifacts
      available?
    - What is the cost of IPC and isolation for this specific workload?
- A microkernel can improve fault containment; a monolithic kernel can simplify
  fast in-kernel communication. Neither architecture by itself proves that a
  robot is safe or real-time.
- Further reading:
    - [ROS 2 design](https://design.ros2.org/)
    - [ROS 2 and DDS middleware](https://docs.ros.org/en/rolling/Concepts/Intermediate/About-Different-Middleware-Vendors.html)
    - [micro-ROS features and architecture](https://micro.ros.org/docs/overview/features/)
    - [QNX microkernel architecture](https://www.qnx.com/developers/docs/8.0/com.qnx.doc.neutrino.sys_arch/topic/intro.html)

---

## Linux vs MINIX: the flame war of 1992

- Dr. Tanenbaum started it!
    - [Linux is obsolete](https://groups.google.com/g/comp.os.minix/c/wlhw16QWltI)
- The flame war has its [own wiki page!](https://en.wikipedia.org/wiki/Tanenbaum%E2%80%93Torvalds_debate).
- Dr. Ngo was in 7th grade.   
- At that time, Linux:
    - was designed by Linus Torvalds, then a university student in Finland;
    - was inspired in part by Torvalds's experience using MINIX;
    - used a monolithic kernel design; and
    - competed conceptually with MINIX's microkernel design.
- Andrew Tanenbaum (AT)
- Linus Torvalds (LT)

{% details AT %}

- Most older operating systems are monolithic, that is, the whole operating system 
is a single a.out file that runs in 'kernel mode' (UNIX, MS-DOS, VMS, MVS, OS/360, 
MULTICS …).
- In a microkernel-based system, in which most of the OS runs as separate processes, 
mostly outside the kernel.  (RC4000, Amoeba, Chorus, Mach, and the not-yet-released 
**Windows/NT**).
- ... among the people who actually design operating systems, the debate is essentially 
over. **Microkernels have won**. The only real argument for monolithic systems was 
performance, and there is now enough evidence showing that microkernel systems can be 
just as fast as monolithic systems. 
- MINIX is a microkernel-based system. LINUX is a monolithic style system.  This is a 
giant step back into the 1970s. That is like taking an existing, working C program and 
rewriting it in BASIC.  To me, writing a monolithic system in 1991 is a truly poor idea.
MINIX was designed to be reasonably portable, and has been ported from the Intel line 
to the 680x0 (Atari, Amiga, Macintosh), SPARC, and NS32016. LINUX is tied fairly 
closely to the 80x86.  Not the way to go.

{% enddetails %}
{% details LT %}

- **Well, with a subject like this, I'm afraid I'll have to reply.**
- True, linux is monolithic, and I agree that microkernels are nicer. From a 
theoretical (and aesthetical) standpoint Linux looses. What you (AT) don't mention is 
that minix doesn't do the micro-kernel thing very well, and has problems with real 
multitasking (in the kernel).  
- The fact is that linux is more portable than minix.  It's true - but not in the sense 
that ast (AT) means: I made linux as conformant to standards as I knew how (without 
having any POSIX standard in front of me).  Porting things to linux is generally /much/ 
easier than porting them to minix.
- I agree that portability is a good thing: but only where it actually has some 
meaning.  There is no idea in trying to make an operating system overly portable: 
adhering to a portable API is good enough.  The very /idea/ of an operating system is 
to use the hardware features, and hide them behind a layer of high-level calls.  That 
is exactly what linux does: it just uses a bigger subset of the 386 features than other 
kernels seem to do.  Of course this makes the kernel proper unportable, but it also 
makes for a /much/ simpler design.  An acceptable trade-off, and one that made linux 
possible in the first place.

{% enddetails %}
{% details AT %}

- A multithreaded file system is only a performance hack.  When there is only one 
job active, the normal case on a small PC, it buys you nothing and adds complexity to 
the code.  On machines fast enough to support multiple users, you probably have enough 
buffer cache to insure a hit cache hit rate, in which case multithreading also buys you 
nothing.  It is only a win when there are multiple processes actually doing real disk 
I/O.  Whether it is worth making the system more complicated for this case is at least 
debatable.
- MINIX was designed before POSIX, and is now being (slowly) POSIXized as everyone who 
follows this newsgroup knows.  Everyone agrees that user-level standards are a good 
idea.  As an aside, I congratulate you for being able to write a POSIX-conformant 
system without having the POSIX standard in front of you. I find it difficult enough 
after studying the standard at great length.
- My point is that writing a new operating system that is closely tied to any 
particular piece of hardware, especially **a weird one like the Intel line**, 
is basically wrong.  An OS itself should be easily portable to new hardware platforms.  
When OS/360 was written in assembler for the IBM 360 25 years ago, they probably could 
be excused.  When MS-DOS was written specifically for the 8088 ten years ago, this was 
less than brilliant, as IBM and Microsoft now only too painfully realize.

{% enddetails %}
{% details LT %}

- You (AT) admit that some of the errors of minix were that it was too portable: 
including machines that weren't really designed to run unix. That assumption lead to 
the fact that minix now cannot easily be extended to have things like paging, even for 
machines that would support it.  **Yes, minix is portable, but you can rewrite that as 
doesn't use any features", and still be right**.
- `A multithreaded file system is only a performance hack`. Not true.  It's a 
performance hack /on a microkernel/, but it's an automatic feature when you write a 
monolithic kernel - one area where microkernels don't work too well.  When writing a 
unix the "obsolete" way, you automatically get a multithreaded kernel: every process 
does it's own job, and you don't have to make ugly things like message queues to make 
it work efficiently. 
- The operating system /isn't/ tied to any processor line: UNIX runs on most real 
processors in existence.  Yes, the /implementation/ is hardware-specific, but there's a 
HUGE difference.  You mention OS/360 and MS-DOG as examples of bad designs as they were 
hardware-dependent, and I agree.  But there's a big difference between these and linux: 
linux API is portable (not due to my clever design, but due to the fact that I decided 
to go for a fairly-well-thought-out and tested OS: unix.) If you write programs for 
linux today, you shouldn't have too many surprises when you just recompile them for 
Hurd in the 21st century.  

{% enddetails %}
{% details The bigger picture %}

- "The way the world was thinking about OS design at the time".
- "UNIX: A history and memoir" by Brian Kernighan. 
    - "It's important to understand the evolution of the technology that we use
    and take for granted. The decisions that shaped  how that technology developed 
    and thus defined the paths that we took were made by real people, working under
    the pressures and constraints of the time. The more we know about the history, the 
    the more we can appreciate the inventive genius that led to Unix and perhaps 
    better understand why modern computer systems are as they are. If nothing else, 
    choices that might seem wrong-headed or perverse today can often be seen as 
    natural consequences of what was understood and could be accomplished with the 
    resources available at that time."

- The argument did not produce a universal winner. Linux became enormously
  successful while retaining a modular monolithic kernel. Microkernels such as
  QNX and seL4 became important where isolation, verification, or critical
  embedded operation justified their engineering trade-offs. Modern systems
  also borrow ideas across categories.
- The lasting question is not "Which label won?" but "Which mechanisms and
  failure boundaries fit this system's requirements?"

{% enddetails %}
