---
layout: lecture
pretty_table: true
collection: csc588
course: CSC 603: Access Control in the Cloud
title: "Cloud: Definition and Virtualization"
toc:
  - name: What services does Cloud offer?
  - name: SaaS: Software-as-a-Service
  - name: PaaS: Platform-as-a-Service
  - name: IaaS: Infrastructure-as-a-Service
  - name: Comparing service models
  - name: XaaS: Everything-as-a-Service
  - name: NIST: Four deployment models
  - name: Cloud Security: who is doing what
  - name: What is virtualization?
  - name: Types of virtualization
  - name: Network and storage virtualization
  - name: Virtualization: concept of overcommits
  - name: Virtualization hypervisors
  - name: Virtualization in the cloud
---

# Cloud: Definition and Virtualization


## What services does Cloud offer?

{% details note Details %}

{% enddetails %}
- Before we can evaluate the necessity of moving to the cloud, we need to 
to know what services are available. 
  - SaaS: Software-as-a-Service
  - PaaS: Platform-as-a-Service
  - IaaS: Infrastructure-as-a-Service
- Vendor: cloud service provider. 
```

## SaaS: Software-as-a-Service

{% details Definition %}

{% enddetails %}
- Vendor controlled applications that are accessed over the network by users.
- Characteristics:
  - Network-based access
  - Multi-tenancy
  - Single software release for all
- Examples:
  - Applications in the Google Suite
  - Dropbox
  - Cisco WebEx

{% details Application Design %}

{% enddetails %}
- Net native
  - Cloud-specific design, development, and deployment
  - Multi-tenant data
  - Built-in metering and management
  - Browser-based
  - Customization via configuration
- High degree of configurability, efficiency, and scalability

{% details Disadvantages %}

{% enddetails %}
- SaaS providers are dependent on network and cloud service providers.
  - [A Dropbox story](https://www.wired.com/2016/03/epic-story-dropboxs-exodus-amazon-cloud-empire/)
- Performance is dependent on individual client's bandwidth.
- Security
  - Good: Better security than personal computers
  - Bad: SaaS vendors (and cloud providers) are in charge of the data
  - Ugly: Privacy

{% details Privacy %}

{% enddetails %}
- Who owns your data in SaaS?
- [Google Drive ToS](https://support.google.com/drive/answer/2450387?hl=en)
- [Google ToS](https://policies.google.com/terms?hl=en&gl=us)
```

## PaaS: Platform-as-a-Service

{% details Definition %}

{% enddetails %}
- Vendors provide development environment.
  - Tools and technologies are selected by vendors.
  - Users maintain control over data (application) life-cycle.
- Examples:
  - Google App Engine
  - AWS Elastic Beanstalk
  - Heroku

{% details Architectural characteristics %}

{% enddetails %}
- Support multi-tenancy at various scale: sessions, processes, and data.
  - Isolation at: physical, virtual, and logical levels
  - [Microsoft’s offerings of isolation choices](https://docs.microsoft.com/en-us/azure/security/fundamentals/isolation-choices)
- Native scalability
  - Load balancing and fail-over (AWS Elastic Beanstalk)
- Native integrated management
  - Performance
  - Resource consumption/utilization
  - Load

{% details Disadvantages %}

{% enddetails %}
- Inherits all from SaaS
- Options on technologies and tools are limited by the PaaS vendors
```

## IaaS: Infrastructure-as-a-Service

{% details Definition %}

{% enddetails %}
- Vendors provide computing resources.
- Users provision computing resources.
  - Compute resources include processing, storage, memory, network etc.
  - Users are provided with customized virtual machines.
- Users maintain control over:
  - Operating system, memory
  - Storage,
  - Servers and deployment configurations, and
  - Some limited control over network resources via software-defined networking

{% details Advantages %}

{% enddetails %}
- Infrastructure scalability
- Native-integrated management via vendors' utilities
  - Performance, resource consumption/utilization, load
- Economical cost
  - Hardware, IT support

{% details Disadvantages %}

{% enddetails %}
- Require more technical efforts than SaaS and PaaS. 
```

## Comparing service models

{% details note Details %}


{% enddetails %}
:::{image} ../fig/csc603/03-services/01.png
:class: bg-primary mb-1
:height: 400px
:align: center
:::

:::{image} ../fig/csc603/03-services/02.png
:class: bg-primary mb-1
:height: 400px
:align: center
:::

```

## XaaS: Everything-as-a-Service

{% details note Details %}

{% enddetails %}
- Composite second level services
- [NIST Evaluation of Cloud Computing Services (2018) p. 20](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.500-322.pdf)
```



## NIST: Four deployment models

- Private Cloud
- Community Cloud
- Public Cloud
- Hybrid Cloud

{% details Private cloud %}

{% enddetails %}
- Infrastructure is organized solely for an organization
- Infrastructure is managed by the organization or by a third party

{% details Community cloud %}

{% enddetails %}
- Supports a specific community
- Infrastructure is shared by several organizations
- Examples: CloudLab

{% details Public cloud %}

{% enddetails %}
- Infrastructure is made available to the general public
- Infrastructure is owned by an organization selling cloud services
- Example: Azure Notebook free tier. 

{% details Hybrid cloud %}

{% enddetails %}
- Infrastructure is a composition of two or more clouds deployment models.
- Enables data and application portability
```



## Cloud Security: who is doing what

- The cloud provider is responsible for the security **OF** the Cloud.
- The cloud consumer (users) is responsible for the security **IN** the Cloud.

{% details Cloud consumer %}

{% enddetails %}
- SaaS/PaaS:
  - Standard security procedure for online presences.
- IaaS:
  - Standard security procedure as any on-premise infrastructures.
  - Benefits from native administrative tools from the Cloud Provider.

{% details Cloud provider: SaaS security %}

{% enddetails %}
  - Web application security: [OWASP's Top 10](https://owasp.org/www-project-top-ten/)
  - Multi-tenancy: data isolation/leakage
  - Data security: accessibility versus security trade-off

{% details Cloud provider: PaaS security %}

{% enddetails %}
- Similar security concerns as SaaS
- Complex security schemes due to potential third-party relationships.
- Development Lifecycle
  - Users depend on PaaS providers to patch security issues of the individual tools.

{% details Cloud provider: IaaS security %}

{% enddetails %}
- Standard security measures.
  - To Cloud Provider, cloud resources are on-premise.
- Concerns with virtual machines' security
- Concerns with virtual networking security
```


## What is virtualization?
 
- Operating System concept: The abstraction of available resources
- **Virtualization technologies encompass a variety of mechanisms and techniques used to address 
computer system problems such as security, performance, and reliability by decoupling the
architecture and user-perceived behavior of hardware and software resources from their physical 
implementation.** (*https:/www.computer.org/csdl/mags/co/2005/05/r5028.html/*)

:::{image} ../fig/csc603/04-virtualization/01.png
:class: bg-primary mb-1
:height: 150px
:align: center
:::

{% details Essential characteristics %}

{% enddetails %}
- [Formal requirements for virtualizeable third generation architectures](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.141.4815&rep=rep1&type=pdf)
- A virtual machine is taken to be an efficient, isolated duplicate  of the real machine.
- These notions can be explained through the idea of a **virtual machine monitor**. 
- Essential characteristics of VMM:
  - Essentially identical to the physical resource
  - Efficiency
  - Complete control of system resources (with regard to the processes running inside the VM)

:::{image} ../fig/csc603/04-virtualization/02.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::

{% details Virtualization Layer %}

{% enddetails %}
- Virtualization Layer: The Virtual Machine Monitor (or its modern name: **Hypervisor**) 
provides an interface between hardware and virtual operating systems.
- Type of hypervisors:
  - Bare-metal
  - Hosted

:::{image} ../fig/csc603/04-virtualization/03.png
:class: bg-primary mb-1
:height: 150px
:align: center
:::

{% details Issues that virtualization can help with %}

{% enddetails %}
- Under-utilized resources
- Complicated system management
- Limited access to shared resources
- Inefficient power consumption
- Tight coupling with underlying resources

{% details Virtualization versus multitasking versus multicore/hyperthreading %}


{% enddetails %}
:::{image} ../fig/csc603/04-virtualization/04.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::
```


## Types of virtualization

- Platform Virtualization
- Memory Virtualization
- Desktop Virtualization
- Application Virtualization
- Network Virtualization
- Storage Virtualization

{% details Platform virtualization %}

{% enddetails %}
- Full Virtualization
- Para Virtualization
- Hardware assisted virtualization
- OS level virtualization

{% details Without virtualization %}

{% enddetails %}
- x86 offers four levels of privilege (Ring 0 through 3)
- OS needs to have access to hardware and run on ring 0
- Application runs on ring 3, gain access to hardware by trapping into kernel mode for 
privileged instructions.
- Virtualizing x86 requires a layer under OS (which already at lowest level) to create 
and manage the VM
- Sensitive instructions must be executed in ring 0 

:::{image} ../fig/csc603/04-virtualization/05.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::

{% details Full virtualization %}

{% enddetails %}
- Guess OS is unaware of host OS.
  - VMM provides virtual BIOS, virtual devices, and virtual memory management.
- Non-critical instructions run directly on hardware.
- Runtime translation of critical non-virtualizable instructions happens in the hypervisor.
- Provide best isolation and security at the cost of performance.

:::{image} ../fig/csc603/04-virtualization/06.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::

{% details Para virtualization %}

{% enddetails %}
- Thin layer interfaces between each guest OS and underlying hardware.
- Need guest kernel modification.
- No need of runtime translation for critical instructions.
- Superior in performance.
- Requires expertise to patch the kernels.

:::{image} ../fig/csc603/04-virtualization/07.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::

{% details Hardware-assisted virtualization %}

{% enddetails %}
- Hardware provides support to run instructions independently.
  - Intel Virtualization Technology (VT-x)
  - AMD Virtualization Technology (AMD-V)
- No need to patch the kernels.
- Runtime translation not required.
- Better performance in comparison to other variants.
- Greater stability
:::{image} ../fig/csc603/04-virtualization/08.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::

{% details Virtualization at OS level %}

{% enddetails %}
- Same OS for both host and guest machines.
- User space is completely isolated.
- High performance.
- Extremely light-weight.


{% details Memory virtualization %}

{% enddetails %}
- How to share physical system memory and dynamically allocating it to virtual machines.
- Guess OS maps virtual memory space (of VM) to physical memory space (of VM).
- VMM translates physical memory space (of VM) to physical memory space (of main machine), 
but also enables direct mapping (shadow table) to avoid overhead.
:::{image} ../fig/csc603/04-virtualization/09.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::


{% details Summary %}


{% enddetails %}
|  | Full Virtualization with Binary Translation | Hardware Assisted Virtualization | OS Assisted Virtualization/Para Virtualization |  
| ----------- | -------------- | -------------- | ------- |  
| Guest modification/Compatibility | Unmodified Guest OS, excellent compatibility | Unmodified Guest OS, excellent compatibility | Guest OS codified to run Hypercall, cannot run of native hardware or other hypervisors. Poort compatibility |  
| Performance | Good              | Fair              | Better on certain cases       |  
| Guest OS Hypervisor Independent | Yes              | Yes              | Xen Linux runs only on Xen Hypervisor. VMI-Linux is Hypervisor agnostic       |  

{% details Desktop and application virtualization %}

{% enddetails %}
- Desktop and Applications run on servers.
- Stateless thin clients connected to servers.
- Efficient system management.
- Requires high-end servers for system stability
```


## Network and storage virtualization
{% details note Details %}

{% enddetails %}
- Similar idea of providing an abstraction layer to the physical infrastructures
- In networks, abstraction will
  - Be at the level of routers, switches, gateway, firewalls, load balancers, …
  - Enabled by software-defined networking
- In storage, single storage backends can be used for different requirements
  - Ephemeral
  - Persistent
  - Specialize storage backends
```


## Virtualization: concept of overcommits

- Allocating more than the available physical resources to the Guest OS
- Common types of overcommit:
  - CPU 
  - Memory 
  - Storage 

{% details Virtualization: concept of overcommits %}

{% enddetails %}
- Advantages:
  - Favorable economic model
  - Efficient resource utilization
  - Support green computing
- Disadvantages:
  - Performance loss or unstable system response
  - Complex system understanding
  - VM shutdown by the hypervisor

{% details CPU and memory overcommits %}

{% enddetails %}
- Allows more virtual CPUs than physically available
  - Openstack KVM: overcommit-number = 16.0
- Allow more memory than physically available
  - Overstack KVM: overcommit-number = 1.5GB
```


## Virtualization hypervisors
{% details note Details %}

{% enddetails %}
- Contribution from industry and academia
- Xen: Project from Cambridge Computer Laboratory
- VMware: Commercial product
  - Also comes from academic research (see Mendel Rosenblum ACM)
- KVM: Initiated by the Open Virtualization Alliance, later dissolved and is now managed 
by the Linux Foundation
- Qemu: Open source machine emulator and virtualizer
```


## Virtualization in the cloud

:::{image} ../fig/csc603/04-virtualization/10.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::

{% details Openstack: Compute %}


{% enddetails %}
:::{image} ../fig/csc603/04-virtualization/11.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::

:::{image} ../fig/csc603/04-virtualization/12.png
:class: bg-primary mb-1
:height: 500px
:align: center
:::



{% details Openstack: Cinder %}


{% enddetails %}
:::{image} ../fig/csc603/04-virtualization/13.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::



{% details Openstack: Neutron %}


{% enddetails %}
- Management: internal comm between OpenStack components, reachable only within the 
data center.
- Guest: Used for VM data communication within the Cloud Deployment.
- External: Provide VM with Internet access.
- API: Exposed all the Stack’s API to the public.

:::{image} ../fig/csc603/04-virtualization/14.png
:class: bg-primary mb-1
:height: 300px
:align: center
:::

```



