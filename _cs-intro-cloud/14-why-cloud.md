---
layout: lecture
pretty_table: true
order: 1
title: Why Cloud
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
  - name: What services does Cloud offer?
  - name: "SaaS: Software-as-a-Service"
  - name: "PaaS: Platform-as-a-Service"
  - name: "IaaS: Infrastructure-as-a-Service"
  - name: Comparing service models
  - name: "NIST: Four deployment models"
  - name: Computer Security
---

# Why Cloud

---

## 1. What services does Cloud offer?

- Before we can evaluate the necessity of moving to the cloud, we need to 
  to know what services are available. 
    - SaaS: Software-as-a-Service
    - PaaS: Platform-as-a-Service
    - IaaS: Infrastructure-as-a-Service
    - AaaS: Anything-as-a-Service
- Vendor: cloud service provider. 

---

## 2. SaaS: Software-as-a-Service

{% details Overview %}


- Vendor controlled applications that are accessed over the network by users.
- Characteristics:
    - Network-based access
    - Multi-tenancy
    - Single software release for all
- Examples:
    - Applications in the Google Suite
    - Dropbox
    - Cisco WebEx

{% enddetails %}
{% details Application Design %}


- Net native
    - Cloud-specific design, development, and deployment
    - Multi-tenant data
    - Built-in metering and management
    - Browser-based
    - Customization via configuration
- High degree of configurability, efficiency, and scalability

{% enddetails %}
{% details Disadvantages %}


- SaaS providers are dependent on network and cloud service providers.
    - [A Dropbox story](https://www.wired.com/2016/03/epic-story-dropboxs-exodus-amazon-cloud-empire/)
- Performance is dependent on individual client's bandwidth.
- Security
    - Good: Better security than personal computers
    - Bad: SaaS vendors (and cloud providers) are in charge of the data
    - Ugly: Privacy

{% enddetails %}
{% details Privacy: Google Drive ToS %}

- Who owns your data in SaaS?
- [Google Drive ToS](https://support.google.com/drive/answer/2450387?hl=en)


{% enddetails %}
{% details Privacy: Google ToS %}


- Who has access to your data in SaaS?
- [Google ToS](https://policies.google.com/terms?hl=en&gl=us)

{% enddetails %}
---

## 3. PaaS: Platform-as-a-Service

{% details Overview %}


- Vendors provide development environment.
    - Tools and technologies are selected by vendors.
    - Users maintain control over data (application) life-cycle.
- Examples:
    - Google App Engine
    - AWS Elastic Beanstalk
    - Heroku

{% enddetails %}
{% details PaaS: Architectural characteristics %}


- Support multi-tenancy at various scale: sessions, processes, and data.
    - Isolation at: physical, virtual, and logical levels
    - [Microsoft’s offerings of isolation choices](https://docs.microsoft.com/en-us/azure/security/fundamentals/isolation-choices)
- Native scalability
    - Load balancing and fail-over (AWS Elastic Beanstalk)
- Native integrated management
    - Performance
    - Resource consumption/utilization
    - Load

{% enddetails %}
{% details PaaS: Disadvantages %}


- Inherits all from SaaS
- Options on technologies and tools are limited by the PaaS vendors

{% enddetails %}
---

## 4. IaaS: Infrastructure-as-a-Service

{% details Overview %}


- Vendors provide computing resources.
- Users provision computing resources.
    - Compute resources include processing, storage, memory, network etc.
    - Users are provided with customized virtual machines.
- Users maintain control over:
    - Operating system, memory
    - Storage,
    - Servers and deployment configurations, and
    - Some limited control over network resources via software-defined networking

{% enddetails %}
{% details Advantages %}


- Infrastructure scalability
- Native-integrated management via vendors' utilities
    - Performance, resource consumption/utilization, load
- Economical cost
    - Hardware, IT support

{% enddetails %}
{% details Disadvantages %}


- Require more technical efforts than SaaS and PaaS. 

{% enddetails %}
---

## 5. Comparing service models

{% details Flexibility-effort-constraints %}


{% include figure.liquid path="assets/img/courses/csc468/why-cloud/service-models.png" width="50%" zoomable=true alt="Comparing service models" %}

{% enddetails %}
{% details Sharing of controls: Organization versus Provider %}


{% include figure.liquid path="assets/img/courses/csc468/why-cloud/control-levels.png" width="50%" zoomable=true alt="Comparing control level of various service models" %}

{% enddetails %}
{% details XaaS: Everything-as-a-Service %}

- Composite second level services
- [NIST Evaluation of Cloud Computing Services (2018) p. 20](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.500-322.pdf)

{% enddetails %}
---

## 6. NIST: Four deployment models

{% details Four deployment models %}


- Private Cloud
- Community Cloud
- Public Cloud
- Hybrid Cloud

{% enddetails %}
{% details Private cloud %}


- Infrastructure is organized solely for an organization
- Infrastructure is managed by the organization or by a third party

{% enddetails %}
{% details Community cloud %}


- Supports a specific community
- Infrastructure is shared by several organizations
- Examples: CloudLab

{% enddetails %}
{% details Public cloud %}


- Infrastructure is made available to the general public
- Infrastructure is owned by an organization selling cloud services
- Example: Azure Notebook free tier. 

{% enddetails %}
{% details Hybrid cloud %}


- Infrastructure is a composition of two or more clouds deployment models.
- Enables data and application portability

{% enddetails %}
---

## 7. Computer Security

{% details Who is doing what %}


- The cloud provider is responsible for the security **OF** the Cloud.
- The cloud consumer (users) is responsible for the security **IN** the Cloud.

{% include figure.liquid path="assets/img/courses/csc468/why-cloud/aws_shared_responsibility.jpg" width="50%" zoomable=true %}

- Responsibility scale according to control level

{% include figure.liquid path="assets/img/courses/csc468/why-cloud/aws_shared_responsibility_2.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Cloud consumer %}


- SaaS/PaaS:
    - Standard security procedure for online presences.
- IaaS:
    - Standard security procedure as any on-premise infrastructures.
    - Benefits from native administrative tools from the Cloud Provider.

{% enddetails %}
{% details Cloud provider: SaaS security %}


- SaaS:
    - Web application security: [OWASP's Top 10](https://owasp.org/www-project-top-ten/)
    - Multi-tenancy: data isolation/leakage
    - Data security: accessibility versus security trade-off

{% enddetails %}
{% details Cloud provider: PaaS security %}


- Similar security concerns as SaaS
- Complex security schemes due to potential third-party relationships.
- Development Lifecycle
    - Users depend on PaaS providers to patch security issues of the individual tools.


{% enddetails %}
{% details Cloud provider: IaaS security %}


- Standard security measures.
    - To Cloud Provider, cloud resources are on-premise.
- Concerns with virtual machines' security
- Concerns with virtual networking security
{% enddetails %}
