---
layout: lecture
pretty_table: true
collection: csc478
title: "Resource Units and Management in Kubernetes"
mermaid:
  enabled: true
  zoomable: true
toc:
  - name: From Observation to Control
  - name: Requests, Limits, and Slack
  - name: Namespaces, Quotas, and Defaults
  - name: Hardware Labels and Specialized Nodes
  - name: How Enforcement Reaches Linux
  - name: Quality of Service and Contention
---

## From Observation to Control

{% details info Overview %}

- One of Pod's specifications (`spec`) is a resource request. 
  - This value can influence scheduling decision, 
- On the other hands, resource limits can become a Linux kernel enforcement action.

Three separate decisions are involved in this process

| Decision | Question | Component that answers it |
| --- | --- | --- |
| Placement | Which node can take this Pod? | kube-scheduler, using requests, labels, taints, and extended resources |
| Admission | Is this namespace allowed to ask? | API server, using ResourceQuota and LimitRange |
| Enforcement | What happens if the container uses more? | Linux, programmed by the kubelet through the CRI |

{% enddetails %}

{% details info Resource Units %}

Kubernetes inherited Borg's resource vector: 

- CPU and memory are requested in fine units.
- Pod may also request devices that only some machines have.

{% enddetails %}

{% details CPU %}

- **1 CPU** is one Kubernetes CPU unit, corresponding to one hyperthread of allocatable capacity on the node.
- The API writes fractional CPU in **millicores**: `500m` is half a core, `1000m` is one core.
- CPU is **compressible**:
  - The kernel can slow a container down by giving it fewer slices of time even thought the process keeps running.
- Borg measured CPU in milli-cores for the same reason. 
  - This is an abstraction over heterogeneous hardware.

{% enddetails %}

{% details Memory %}

- Memory is measured in bytes.
- SI suffixes (`k`, `M`, `G`) are powers of 10.
- Binary suffixes (`Ki`, `Mi`, `Gi`) are powers of 2.
  - `256Mi` is $256 \times 2^{20}$ bytes. 
  - `1Gi` is $2^{30}$ bytes.
- Memory is **incompressible**. 
  - Reclaiming memory means discarding the contents of pages. 
  - Once a hard limit is reached, the kernel terminates a process in that cgroup (`OOMKilled`, as shown in the previous lecture)

{% enddetails %}

{% details Other resources the scheduler can count %}

| Resource | Example | What is being counted |
| --- | --- | --- |
| Ephemeral storage | `ephemeral-storage: "1Gi"` | Writable layer and logs on the node's local disk |
| Huge pages | `hugepages-2Mi: 128Mi` | Pre-reserved large pages |
| Extended resource | `nvidia.com/gpu: 1` | A device the node has advertised |

- CPU and memory limits become cgroup controllers. 
- Ephemeral-storage limits are enforced by the kubelet, which watches disk usage and evicts the Pod. 
- Extended resources are enforced by exclusive allocation done by the device plugin. 

{% enddetails %}


## Requests, Limits, and Slack

{% details info Overview %}

Every container can declare a **request** and a **limit** for each resource it uses.

```yaml
resources:
  requests:
    cpu: "250m"
    memory: "256Mi"
  limits:
    cpu: "500m"
    memory: "512Mi"
```

- The **request** is what the scheduler subtracts from the node's allocatable capacity. It is also the container's relative weight when the CPU is contended.
- The **limit** is the hard ceiling the runtime installs. 
  - For CPU, exceeding it causes throttling. 
  - For memory, exceeding it causes an OOM kill.
- The gap between usage and the limit is **slack**. 
  - Slack is capacity the container is allowed to burst into, and capacity the cluster cannot safely give to someone else unless that someone can be evicted.
- *This is different from typical supercomputing schedulers*:
  - Exceeding requests = allocation killed

{% details career %}
- Google Borg originally used the limit both to admit the job against quota and to test whether a machine had available resources. 
  - This led to users asked for more than they used, because exceeding RAM killed the task and exceeding CPU throttled it. 
- Borg then estimated a lower **reservation** from observed usage and packed other work into the difference. 
- Kubernetes makes that `difference` explicit: 
  - the request is the reservation, serviced by the scheduler, and 
  - the limit is the ceiling, enforced by the Linux kernel.

{% enddetails %}

{% enddetails %}

{% details The gap: request versus limit %}

[Google's Autopilot paper (EuroSys 2020)](https://research.google/pubs/autopilot-workload-autoscaling-at-google-scale/) measures slack as the difference between the limit and actual usage. Across their comparison, manually chosen limits left about 46% slack. Autopilot, which sets CPU and memory limits from historical usage, brought slack to about 23%, and reduced the number of jobs severely affected by OOM kills by about 10×. At the time of the paper, jobs under Autopilot accounted for over 48% of fleet-wide resource usage.

- In practice, an OOM or a throttle is visible to the job's owner, while wasted slack stays quiet
  - Therefore, users will always pad their limits. 
  - Closing the gap safely takes a history of usage. 
- In Kubernetes the same split appears as two controllers: 
  - the Horizontal Pod Autoscaler changes replica count from current metrics, and 
  - the Vertical Pod Autoscaler recommends requests from history. 

{% enddetails %}

{% details career Capacity Planning in Industry %}

- Requests and limits determine where a Pod can run, how it fails, and what the cluster appears to cost. 
- In [OpenAI's account of scaling Kubernetes to 7,500 nodes](https://openai.com/index/scaling-kubernetes-to-7500-nodes/), low-priority "balloon" Deployments occupied otherwise idle capacity and remained immediately evictable when real work arrived. That is slack, held by a workload the scheduler is allowed to throw away. 
- Borg did the same thing with batch tasks that were willing to use reclaimed memory and be sacrificed when a latency-sensitive task needed it back.
- Evidence for a capacity decision includes:
  - request, limit, and usage percentiles over a real time range;
  - throttling, OOM kills, and eviction history;
  - pending Pods, and which resource or hardware constraint left them pending;
  - the burst the service actually needs, and how quickly it must scale;
  - the reliability and cost of allocating too much or too little.
{% enddetails %}


## Namespaces, Quotas, and Defaults

{% details Namespace %}

- A namespace is the scope in which a team shares a cluster (API boundary). 

Kubernetes creates a few namespaces for its own infrastructure:

| Namespace | Role |
| --- | --- |
| `default` | Where objects go when the client names no namespace |
| `kube-system` | Control-plane add-ons, including the RKE2 Metrics Server from lecture 9 |
| `kube-public` | Objects intended to be readable cluster-wide |
| `kube-node-lease` | Node heartbeats |

{% enddetails %}

{% details ResourceQuota%}

- A ResourceQuota caps aggregate consumption in one namespace: 
  - total CPU and memory requests 
  - total CPU and memory limits, 
  - number of Pods, and 
  - counts of other object types. 
- It can also cap extended resources.

```yaml
apiVersion: v1
kind: ResourceQuota
metadata:
  name: dev-quota
  namespace: dev
spec:
  hard:
    requests.cpu: "2"
    requests.memory: 1Gi
    limits.cpu: "4"
    limits.memory: 1Gi
    pods: "4"
    requests.nvidia.com/gpu: "1"
```

- The API server checks the quota before it stores the object. 
  - A Deployment that would push the namespace over its request total is rejected

{% enddetails %}

{% details BestEffort and LimitRange %}

- A container that declares neither requests nor limits is `BestEffort`. 
  - It is scheduled as if it needed nothing, and it is the first to be evicted when the node is under pressure. 
- A `LimitRange` gives a namespace a default request, a default limit, a minimum, and a maximum, applied by admission to containers that omit the fields.

```yaml
apiVersion: v1
kind: LimitRange
metadata:
  name: default-limits
  namespace: dev
spec:
  limits:
  - type: Container
    defaultRequest:
      cpu: 200m
      memory: 256Mi
    default:
      cpu: 500m
      memory: 512Mi
    max:
      cpu: "2"
      memory: 2Gi
    maxLimitRequestRatio:
      cpu: "4"
```

`maxLimitRequestRatio` caps slack directly: 
  - the limit may be at most four times the request. 
- This impacts Admission of new jobs. 
- Actual enforcement still waits until a kubelet programs a cgroup.

{% enddetails %}


## Hardware Labels and Specialized Nodes

{% details Borg concept %}

- Aim to support a variety of data center (`cells`) with heterogeneous hardware configurations. 
- Users specify `job constraints` that can be used by the scheduler to match against machines' attributes and resource availability. 

{% enddetails %}

{% details Kubernetes concepts %}

{% details question %}

How do Kubernetes describe hardware attributes and resource availability?

{% enddetails %}

When matching workloads to infrastructure, Kubernetes evaluates a spectrum of hardware signals. These signals are not interchangeable, and they are split across different parts of the node API depending on how they are measured and consumed:

- Core Resources (Node Status): 
  - Ordinary CPU, memory, ephemeral-storage, and huge-page requests live natively in node.status. 
  - The scheduler uses these metrics to filter nodes based on remaining allocatable capacity.
• Dynamic Resource Allocation (DRA): 
  - For complex, modern hardware accelerators, 
  - Provides `DeviceClass`, `ResourceClaim`, and `ResourceSlice APIs`. Stable since Kubernetes v1.35, 
  DRA supports advanced Common Expression Language (CEL) attribute filtering, device sharing, and per-workload configurations. 
  - Replaces or complements legacy device plugins on supported drivers.

To target specific machines, specialized nodes break the scheduling problem down into three smaller 
questions using a combination of labels, extended resources, and taints:

| Signal | Question it answers | Producer | Workload-side API |
| --- | --- | --- | --- |
| Node label | What property or location does this node have? | kubelet, cloud controller, Node Feature Discovery, or an administrator | `nodeSelector` or node affinity |
| Extended resource | How many indivisible units are healthy and allocatable? | Usually a device plugin through the kubelet | Container `resources.requests` and `resources.limits` |
| Node taint | Which Pods should be repelled from this node? | RKE2 registration or an administrator | Pod toleration |

A specialized node commonly uses all three:

- Labels by themselves don't provide specifics on the devices (need Extended resource)
- Device requests cannot support the exclusion of non-device job requests (need Taint)

While the above form the baseline hardware signals, the complete scheduling API also factors in operational constraints:

- Pod affinity and anti-affinity place a Pod relative to other labeled Pods;
- topology-spread constraints distribute replicas across node-label domains
  such as zones or hostnames;
- priority and preemption decide which lower-priority workload may be displaced
  when eligible nodes are full;
- `nodeName` bypasses normal scheduler placement and should be reserved for
  exceptional administrative use;
- scheduler profiles and plugins can add organization-specific filtering and
  scoring;

{% enddetails %}


## How Enforcement Reaches Linux

1. **The Pod spec** is stored in etcd. 
2. **Admission** may rewrite defaults or reject the object for quota. 
3. **The scheduler** filters nodes by requests, extended resources, required affinity, and tolerations, then binds the Pod. It accounts for the request. 
  - Process creation happens later, in the kubelet.
4. **The kubelet** on the bound node creates a Pod sandbox and then each container. 
  - For container, a CRI `LinuxContainerResources` message is created and contains: 
    - CPU shares from the request, 
    - CPU quota from the limit, 
    - memory limit, and 
    - an OOM score adjustment from the QoS class.
5. **containerd**, prepares the container and invokes an OCI runtime. 
  - RKE2's default runtime is runc.
6. **runc** writes the cgroup and enters the namespaces. After it returns, the Linux kernel will enforce the parameters of this cgroup.


## Quality of Service and Contention

Kubernetes derives a QoS class from the relationship between requests and limits. The class selects a cgroup parent and an OOM score. It is the cluster's version of Borg's split between latency-sensitive and batch work.

| QoS class | Condition | Under node pressure |
| --- | --- | --- |
| Guaranteed | Every container sets requests equal to limits for CPU and memory | Highest protection. `oom_score_adj` −997. Evicted last. |
| Burstable | Some request is set, and some limit is higher than its request | Weight comes from the request. Burst is allowed up to the limit, then throttle or OOM. Evicted before Guaranteed Pods once it exceeds its request. |
| BestEffort | No container sets a request or a limit | Uses only slack. `oom_score_adj` 1000. Evicted first. |

Three different components can be used to stop a container:

| Actor | Trigger | What the container experiences |
| --- | --- | --- |
| Linux memory controller | Usage passed the cgroup memory limit | `OOMKilled`. The Pod may restart. The node can be otherwise healthy. |
| kubelet eviction | The node crossed a pressure threshold, such as low available memory | The kubelet deletes Pods in QoS and priority order to protect the node and the system daemons. |
| Scheduler preemption | A higher-priority Pod needs a node that is full of lower-priority requests | A lower-priority Pod is terminated so the new one can bind. |

{% details info Borg bands %}

- monitoring, 
- production, 
- batch, 
- best-effort

No preemption of production tasks to avoid preemption cascades. 

{% enddetails %}

{% details info Kubernetes PriorityClass %}

-  Pods in the same priority do not preempt one another. 
- A higher class may preempt a lower one. 
- QoS and priority are different axes: 
  - QoS comes from the resource fields, 
  - priority is an explicit ranking. 

- `Guaranteed`: the service needs predictable latency and the operator is willing to pay for the ceiling at all times, 
- `Burstable`: the service is usually small and sometimes spikes. 
- `BestEffort`: when the spec says nothing, to be used with LimitRange exists.

{% enddetails %}
