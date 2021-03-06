---
layout: slide
title: Service and Deployment
category: presentation
---

<section data-markdown>
## <center> NIST: Three Service Models </center>

- SaaS: Software-as-a-Service
- PaaS: Platform-as-a-Service
- IaaS: Infrastructure-as-a-Service
</section>


<section data-markdown>
### SaaS: Software-as-a-Service

- Vendor controlled applications that are accessed over the network by users.
- Characteristics:
  - Network-based access
  - Multi-tenancy
  - Single software release for all
- Examples:
  - Applications in the Google Suite
  - Dropbox
  - Cisco WebEx
</section>


<section data-markdown>
### SaaS Application Design

- Net native
  - Cloud-specific design, development, and deployment
  - Multi-tenant data
  - Built-in metering and management
  - Browser-based
  - Customization via configuration
- High degree of configurability, efficiency, and scalability
</section>


<section data-markdown>
### SaaS Disadvantages

- SaaS providers are dependent on network and cloud service providers.
  - [A Dropbox story](https://www.wired.com/2016/03/epic-story-dropboxs-exodus-amazon-cloud-empire/)
- Performance is dependent on individual client's bandwidth.
- Security
  - Good: Better security than personal computers
  - Bad: SaaS vendors (and cloud providers) are in charge of the data
  - Ugly: Privacy
</section>


<section data-markdown>
### SaaS and Privacy

- Who owns your data in SaaS?
- [Google Drive ToS](https://support.google.com/drive/answer/2450387?hl=en)
</section>

<section data-markdown>
### SaaS and Privacy

- Who has access to your data in SaaS?
- [Google ToS](https://policies.google.com/terms?hl=en&gl=us)
</section>


<section data-markdown>
### PaaS: Platform-as-a-Service

- Vendors provide development environment.
  - Tools and technologies are selected by vendors.
  - Users maintain control over data (application) life-cycle.
- Examples:
  - Google App Engine
  - AWS Elastic Beanstalk
  - Heroku
</section>


<section data-markdown>
### PaaS Architectural Characteristics

- Support multi-tenancy at various scale: sessions, processes, and data.
  - Isolation at: physical, virtual, and logical levels
  - [Oracle multi-tenancy strategy for PaaS](https://www.oracle.com/technetwork/topics/cloud/paas-multi-tenancy-092593.html)
- Native scalability
  - Load balancing and fail-over (AWS Elastic Beanstalk)
- Native integrated management
  - Performance
  - Resource consumption/utilization
  - Load
</section>


<section data-markdown>
### PaaS Disadvantages

- Inherits all from SaaS
- Options on technologies and tools are limited by the PaaS vendors
</section>


<section data-markdown>
### IaaS: Infrastructure-as-a-Service

- Vendors provide computing resources.
- Users provision computing resources.
  - Compute resources include processing, storage, memory, network etc.
  - Users are provided with customized virtual machines.
- Users maintain control over:
  - Operating system, memory
  - Storage,
  - Servers and deployment configurations
  - Some limited control over network resources via software-defined networking
- Examples:
  - Amazon Elastic Compute Cloud (EC2)
  - Google Cloud Platform
</section>


<section data-markdown>
### IaaS Advantages

- Infrastructure scalability
- Native-integrated management via vendors' utilities
  - Performance, resource consumption/utilization, load
- Economical cost
  - Hardware, IT support
</section>


<section data-markdown>
### IaaS Disadvantages

- Require more technical efforts than SaaS and PaaS.
</section>


<section data-markdown>
### Comparing Services Models

![service-models]({{ "/assets/images/csc-496-2/intro_cloud/cloud-options.png" | prepend: site.baseurl | prepend: '/' | prepend: site.url }})
</section>


<section data-markdown>
### Comparing Services Models

*Visualization from https://kscottmorrison.com/2009/12/01/visualizing-the-boundaries-of-control-in-the-cloud/*

![cloud-boundary]({{ "/assets/images/csc-496-2/intro_cloud/cloud-boundary.png" | prepend: site.baseurl | prepend: '/' | prepend: site.url }})
</section>


<section data-markdown>
### XaaS: Everything-as-a-Service

- Composite second level services
- [NIST Evaluation of Cloud Computing Services (2018)](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.500-322.pdf)
</section>


<section data-markdown>
## <center> NIST: Four Deployment Models </center>

- Private Cloud
- Community Cloud
- Public Cloud
- Hybrid Cloud

</section>


<section data-markdown>
### Private Cloud

- Infrastructure is organized solely for an organization
- Infrastructure is managed by the organization or by a third party
</section>


<section data-markdown>
### Community Cloud

- Supports a specific community
- Infrastructure is shared by several organizations
</section>


<section data-markdown>
### Public Cloud

- Infrastructure is made available to the general public
- Infrastructure is owned by an organization selling cloud services
</section>


<section data-markdown>
### Hybrid Cloud

- Infrastructure is a composition of two or more clouds deployment models
- Enables data and application portability
</section>


<section data-markdown>
### Is It a Cloud?

[NIST Checklists](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.500-322.pdf)
</section>


<section data-markdown>
## <center> Security in the Cloud </center>
</section>


<section data-markdown>
### Who is doing what?

- The cloud provider is responsible for the security **OF** the Cloud.
- The cloud consumer (users) is responsible for the security **IN** the Cloud.
</section>


<section data-markdown>
### Cloud Consumer

- SaaS/PaaS:
  - Standard security procedure for online presences.
- IaaS:
  - Standard security procedure as any on-premise infrastructures.
  - Benefits from native administrative tools.
</section>


<section data-markdown>
### Cloud Provider: SaaS

- Web application security
  - [OWASP's Top 10](https://www.owasp.org/index.php/Category:OWASP_Top_Ten_Project)
- Multi-tenancy
  - Data isolation/leakage
- Data security
- Accessibility versus Security trade-off
</section>


<section data-markdown>
### Cloud Provider: PaaS

- Similar security concerns as SaaS
- Complex security schemes due to potential third-party relationships.
- Development Lifecycle
  - Users depend on PaaS providers to patch security issues of the individual tools.
</section>


<section data-markdown>
### Cloud Provider: IaaS

- Standard security measures.
  - To Cloud Provider, cloud resources are on-premise.
- Concerns with virtual machines' security
- Concerns with virtual networking security
- [An analysis of security issues for cloud computing (2013)](https://link.springer.com/article/10.1186/1869-0238-4-5)
</section>
