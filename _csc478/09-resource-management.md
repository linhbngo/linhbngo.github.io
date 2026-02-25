---
layout: lecture
pretty_table: true
collection: csc478
course: CSC478: Cloud Engineering
title: "Resource Units and Management in Kubernetes"
toc:
  - name: Logistics
  - name: What Is Resource Management?
  - name: Resource Units
  - name: Resource Requests and Limits
  - name: Namespaces
  - name: ResourceQuota
  - name: LimitRange
  - name: How Resource Enforcement Works Internally
  - name: Quality of Service (QoS) Classes
---
# Resource Units and Management in Kubernetes

---

## Logistics

- Last day of the course: Thursday December 4th 
  - Review
- Final presentation periods:
  - December 4th (4 presentation spots)
  - December 2nd (5 presentation spots)
  - Attendance: Mandatory for ALL member, whether your team presents or not. 

---

## What Is Resource Management?

In Docker, containers share all host resources without formal boundaries.  
In Kubernetes, **resource management** ensures that:

- No single Pod monopolizes CPU or memory (“noisy neighbor” problem).  
- Workloads get fair and predictable performance.  
- Nodes and clusters remain healthy under load.  

This is achieved using **requests**, **limits**, **quotas**, and **namespaces**.

---

## Resource Units

{% details CPU Units %}

- **1 CPU** = 1 Kubernetes CPU unit = one virtual core (1 vCPU).  
- Measured in *millicores*:
  - `500m` = 0.5 CPU
  - `1000m` = 1 CPU  
- Fractional values are expressed with the **m** suffix (milli).

**Behavior:**
- CPU is *compressible* — the container can use more than its request if the node has spare capacity, but it is *throttled* if it exceeds its limit.
- Throttling happens via Linux cgroups’ **CFS quota**.

{% enddetails %}
{% details Memory Units %}


- Memory is measured in bytes.
- Common suffixes:
  - SI (base-10): `k`, `M`, `G`, `T`  
  - Binary (base-2): `Ki`, `Mi`, `Gi`, `Ti`  
- Example:  
  - `256Mi` = 256 × 2²⁰ bytes ≈ 268 MB  
  - `1Gi` = 1024 × 1024 × 1024 bytes ≈ 1.07 GB  

{% details Abstract: Details %}

Memory is *incompressible* — if a container exceeds its limit, it is terminated with an **OOMKilled** (Out-of-Memory) event.

{% enddetails %}
{% enddetails %}
{% details Extended Resources %}


Kubernetes also supports:

| Type | Example Unit | Notes |
|------|---------------|-------|
| Ephemeral Storage | `ephemeral-storage: "1Gi"` | Temporary local disk |
| HugePages | `hugepages-2Mi: 128Mi` | For special workloads |
| Custom Resources | `nvidia.com/gpu: 1` | GPU or device-specific |

{% enddetails %}
---

## Resource Requests and Limits

Every container can specify **requests** (minimum) and **limits** (maximum) for CPU and memory.

```yaml
resources:
  requests:
    cpu: "250m"
    memory: "256Mi"
  limits:
    cpu: "500m"
    memory: "512Mi"

{% details Pod with Resource Requests and Limits %}


Create a file called pod-with-resources.yaml:

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: cpu-mem-demo
spec:
  containers:
  - name: stress-container
    image: polinux/stress
    command: ["stress"]
    args: ["--cpu", "1", "--vm", "1", "--vm-bytes", "200M", "--vm-hang", "1"]
    resources:
      requests:
        cpu: "250m"
        memory: "256Mi"
      limits:
        cpu: "500m"
        memory: "512Mi"
```

Deploy the pod:

```bash
kubectl apply -f pod-with-resources.yaml
kubectl get pods
kubectl describe pod cpu-mem-demo
kubectl top pods
```

Observe how the scheduler allocates CPU shares and memory quota to this Pod.

{% enddetails %}
---

## Namespaces

Namespaces organize resources logically within a cluster.
They act like virtual clusters on top of a single physical cluster.

{% details Built-in namespaces %}

- Run the following commands on the headnode to list all available namespaces. 
- You can use either `ns` or `namespace`. 

```bash
kubectl get namespace
kubectl get ns
```

{% include figure.liquid path="assets/img/courses/csc478/resource-management/namespaces.png" width="50%" zoomable=true %}

- `default`: Default namespace for user-created resources without namespace specified.
- `kube-system`: Special, reserved namespace for system components.
- `kube-public`: Name space for resources meant to be readable by all users.
- `kube-node-lease`: for Lease objects, which serves as node heartbeats.

{% enddetails %}
{% details Create a new namespace %}


Create a file named `namespace.yaml`:

```bash
apiVersion: v1
kind: Namespace
metadata:
  name: team-alpha
  labels:
    environment: development
```

Deploy the namespace manifest and check its availability. 

```bash
kubectl apply -f namespace.yaml
kubectl get namespaces
```

{% enddetails %}
## ResourceQuota

When multiple teams share a cluster, you can restrict total resource usage per namespace.

{% details quote Details %}

A resource quota, defined by a ResourceQuota object, provides constraints that limit aggregate resource consumption per namespace. A ResourceQuota can also limit the quantity of objects that can be created in a namespace by API kind, as well as the total amount of infrastructure resources that may be consumed by API objects found in that namespace.

{% enddetails %}
{% details Create namespace and quota %}


```bash
kubectl create namespace dev
```

Create a manifest file called `dev-quota.yaml`:

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
```

Apply the manifest file:

```bash
kubectl apply -f dev-quota.yaml
kubectl describe quota dev-quota -n dev
```

- Create and apply following deployment manifest called `quota-demo-deploy.yaml`

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: quota-demo
  namespace: dev
spec:
  replicas: 5
  selector:
    matchLabels:
      app: quota-demo
template:
  metadata:
    labels:
      app: quota-demo
  spec:
    containers:
    - name: busybox-demo
      image: busybox
      command: ["sh", "-c", "while true; do echo $(date) >> /tmp/date.log; sleep 10; done"]
      resources:
        requests:
          cpu: "500m"
          memory: "256Mi"
        limits:
          cpu: "1"
          memory: "256Mi"
```

- Confirm that we are not able to go above 4 replicas, as any Pod created in the `dev` namespace will be checked against this quota.
If usage exceeds these totals, new Pods are rejected.

```bash
# Verify quota
kubectl describe quota dev-quota -n dev

# Deploy workloads
kubectl apply -f quota-demo-deploy.yaml

# Observe results
kubectl get pods -n dev
kubectl describe deployment quota-demo -n dev
```

- Delete the quote-demo deployment!

{% enddetails %}
## LimitRange

- A `LimitRange` defines default, minimum, and maximum resources for containers within a namespace.

{% details Default Limits %}

- Create a manifest file called `default-limits.yaml`:

```yaml
apiVersion: v1
kind: LimitRange
metadata:
  name: default-limits
  namespace: dev
spec:
  limits:
  - default:
      cpu: 500m
      memory: 512Mi
    defaultRequest:
      cpu: 200m
      memory: 256Mi
    type: Container
```

- Apply these limits to the `dev` namespace:

```bash
kubectl apply -f default-limits.yaml
```

- Now, any Pod without explicit resource requests/limits will inherit these defaults.

{% enddetails %}
## How Resource Enforcement Works Internally


Layer	| Responsibility
----- | ------ 
Scheduler	| Uses requests to pick a node that can host the Pod
Kubelet	| Reserves node resources according to requests
Container | runtime (cgroups)	Enforces limits (CPU throttling or OOM kill)
Metrics server	| Reports usage (`kubectl top`)
Rancher UI / Dashboard	| Visualizes namespace-level usage

## Quality of Service (QoS) Classes

Kubernetes classifies Pods based on resource configuration:

QoS Class	 | Condition	                            | Behavior
---------- | -------------------------------------- | ---------------------------
Guaranteed |	All containers have requests = limits |	Highest priority, least likely to be evicted
Burstable	 | Requests < limits	                    | Medium priority
BestEffort | No requests or limits	                | Lowest priority, evicted first

You can check a Pod’s QoS with:

```bash
kubectl get pod cpu-mem-demo -o jsonpath='{.status.qosClass}'
```
