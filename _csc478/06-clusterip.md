---
layout: lecture
pretty_table: true
collection: csc478
title: "ClusterIP, NodePort, and Multi-Service Communication"
toc:
  - name: Motivation
  - name: Services Overview
  - name: ClusterIP Services
  - name: NodePort Services
  - name: Multi-Service Communication
  - name: Kubernetes Networking Theory
---
# ClusterIP, NodePort, and Multi-Service Communication

---

## Motivation

- We learned about Pods and Deployments, the unit of execution and how to scale/manage them.
- We also briefly touched on Services. 
    - How do we move move from `running apps` to  `connecting apps`.
- Services in Kubernetes provide stable networking endpoints for ephemeral pods.
- Two important service types:
    - ClusterIP: Internal access within the cluster.
    - NodePort: External access to services from outside the cluster.

---

## Services Overview

- Pods get dynamic IPs that can change when restarted.
- Services provide:
    - Stable DNS names (e.g., my-service.default.svc.cluster.local)
    - Load balancing across pod replicas
- Service types:
    - ClusterIP: Internal only (default).
    - NodePort: Exposes service on a static port on each node.
    - LoadBalancer: Cloud provider managed (beyond today’s scope).


```mermaid
flowchart TB
    subgraph Cluster["Kubernetes Cluster"]
        subgraph Pods["Pods"]
            B1["Backend Pod 1"]
            B2["Backend Pod 2"]
        end
        subgraph ClusterIPService["Service: ClusterIP"]
            C1["Virtual IP\n(10.x.x.x)"]
        end
        subgraph NodePortService["Service: NodePort"]
            N1["ClusterIP\n+ NodePort"]
        end
    end

    %% ClusterIP flow
    ClientIn["Internal Pod (curl)"] -->|"DNS: backend-svc"| C1 --> B1
    C1 --> B2

    %% NodePort flow
    ExternalClient["External Client\n(Browser or curl)"] -->|"http://NodeIP:Port"| N1 --> B1
    N1 --> B2

    %% Styling
    classDef cluster fill:#f0f8ff,stroke:#4682b4,stroke-width:2px;
    classDef service fill:#ffe4b5,stroke:#d2691e,stroke-width:2px;
    class Cluster,Pods cluster
    class ClusterIPService,NodePortService service

```

---

## ClusterIP Services

{% details Concept %}

- Internal communication between pods.
- Example: Frontend pod calls a backend service by DNS.

{% enddetails %}
{% details ClusterIP Demo %}

- Create and deploy a backend Pod Deployment (simple HTTP echo app) called `echo-deployment.yaml`:

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: backend
spec:
  replicas: 2
selector:
  matchLabels:
    app: backend
template:
  metadata:
    labels:
        app: backend
  spec:
    containers:
    - name: backend
      image: nginxdemos/hello:plain-text
      ports:
      - containerPort: 80
```

```bash
kubectl apply -f echo-deployment.yaml
```

- Let's expose it with a ClusterIP service. 
    - Create and deploy a service manifest called `echo-svc.yaml`. 

```yaml
apiVersion: v1
kind: Service
metadata:
  name: backend-svc
spec:
  selector:
    app: backend
  ports:
    - port: 80
    targetPort: 80
```

```bash
kubectl apply -f echo-deployment.yaml
```

- Verify DNS-based resolution inside the cluster:
    - Calling the servce `backend-svc` links us to the Pod. 

```bash
kubectl run curl --image=alpine -it --rm
# inside pod:
apk update
apk add curl
curl backend-svc
```

- Observe how curl can return results from different pods. 

{% include figure.liquid path="assets/img/courses/csc478/clusterip/multi-pods.png" width="50%" zoomable=true %}

{% enddetails %}
---

## NodePort Services

{% details Concept %}


- Makes service accessible from outside cluster.
- Kubernetes opens a static port (30000–32767) on all nodes.

{% enddetails %}
{% details NodePort %}


- Manually expose the backend service externally:

```bash
kubectl expose deployment backend --name=backend-nodeport --type=NodePort --port=80 --target-port=80
```

- Check service details:

```bash
kubectl get svc backend-nodeport
```

- You wil be assigned a random port between 30000 and 32767. An example output could be:

{% include figure.liquid path="assets/img/courses/csc478/clusterip/expose-nodeport.png" width="50%" zoomable=true %}

- On a different node, or even a node from a different experiment, runs:

```bash
# NODE_IP should be the hostname/IP address of the CloudLab node you are on. 
# NODE_PORT is the value between 30000 and 32767 that Kubernetes give your backend-nodeport service
curl NODE_IP:NODE_PORT
```

{% enddetails %}
---

## Multi-Service Communication

{% details Concept %}

- In a real apps, multiple services are talking to each other.

{% enddetails %}
{% details Quote of the Day App %}

{% details info Architecture %}

- API Service: returns some random quotes
- Time Service: return current server time
- Frontend Service: aggregate both responses and presents a combined message to the user. 

{% enddetails %}
{% details info API Service: quote %}


- Create and deploy a deployment manifest called `quote-deployment.yaml`

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: quote
spec:
  replicas: 2
  selector:
    matchLabels:
      app: quote
  template:
    metadata:
      labels:
        app: quote
    spec:
      containers:
      - name: quote
        image: ealen/echo-server
        env:
        - name: QUOTES
          value: |
            "The journey of a thousand miles begins with a single step."
            "What you do today can improve all your tomorrows."
            "In the middle of difficulty lies opportunity."
        ports:
        - containerPort: 80
---
apiVersion: v1
kind: Service
metadata:
  name: quote-svc
spec:
  selector:
    app: quote
  ports:
  - port: 80
    targetPort: 80
```

{% enddetails %}
{% details info Time Service %}

- Create and deploy a deployment manifest called `time-deployment.yaml`

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: time
spec:
  replicas: 1
  selector:
    matchLabels:
      app: time
template:
    metadata:
      labels:
        app: time
    spec:
      containers:
      - name: time
        image: busybox
        command: ["sh","-c"]
        args:
          - |
            while true; do
            printf "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n$(date)\n" \
            | nc -l -p 8080 -s 0.0.0.0;
            done
        ports:
        - containerPort: 8080
---
apiVersion: v1
kind: Service
metadata:
  name: time-svc
spec:
  selector:
    app: time
  ports:
  - port: 80
    targetPort: 8080
```

{% enddetails %}
{% details info Frontend Service %}


- Create and deploy a deployment manifest called `time-deployment.yaml`

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: frontend
spec:
  replicas: 1
  selector:
    matchLabels:
      app: frontend
  template:
    metadata:
      labels:
        app: frontend
    spec:
      containers:
      - name: frontend
        image: busybox
        command: ["sh","-c"]
        args:
          - |
            while true; do
            Q=$(wget -qO- http://quote-svc);
            T=$(wget -qO- http://time-svc);
            printf "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nQuote: $Q\nTime: $T\n" \
            | nc -l -p 8080 -s 0.0.0.0 ;
            done
        ports:
        - containerPort: 8080
---
apiVersion: v1
kind: Service
metadata:
  name: frontend-svc
spec:
  type: NodePort
  selector:
    app: frontend
  ports:
  - port: 80
    targetPort: 8080
```

{% enddetails %}
Test these services with the following:

```bash
kubectl get svc frontend-svc
curl http://<NODE-IP>:<NODEPORT>
```

```mermaid
flowchart TB
%% User
U["External User<br/>curl http://NodeIP:NodePort"]

%% NodePort Service
subgraph Node["frontend-svc (Service: NodePort)"]
    NP["NodePort: 31080<br/>(maps → targetPort 8080)"]
end

%% Frontend Pod
subgraph Frontend["Frontend Pod"]
    FE["containerPort: 8080<br/>(aggregator)"]
end

%% ClusterIP Services
subgraph Services["ClusterIP Services (internal only)"]
    QS["quote-svc<br/>targetPort 80"]
    TS["time-svc<br/>targetPort 80"]
end

%% Quote Pods
subgraph QuotePods["Quote Pods"]
    Q1["containerPort: 80"]
    Q2["containerPort: 80"]
end

%% Time Pod
subgraph TimePod["Time Pod"]
    T1["containerPort: 80"]
end

%% Connections
U --> NP --> FE
FE --> QS
FE --> TS
QS --> Q1
QS --> Q2
TS --> T1

%% Styling
classDef user fill:#f0f8ff,stroke:#4169e1,stroke-width:2px;
classDef service fill:#fffacd,stroke:#daa520,stroke-width:2px;
classDef pod fill:#f0fff0,stroke:#2e8b57,stroke-width:2px;
class U user
class Node,Services service
class Frontend,QuotePods,TimePod pod
```

{% enddetails %}
---

## Kubernetes Networking Theory

{% details Review: NAT %}

- Network Address Translation (NAT) is a technique where a network device (typically a router or firewall) rewrites the source or destination IP address of packets as they pass through.
- Why it exists:
    - IPv4 has a limited address space: NAT lets many internal devices share a single public IP.
    - Provides a layer of isolation/security by hiding internal addresses.
- Types of NAT:
    - SNAT (Source NAT): Rewrites the source IP of outbound traffic (e.g., your laptop 192.168.1.10 to public IP 203.0.113.5).
    - DNAT (Destination NAT): Rewrites the destination IP of inbound traffic (e.g., packets to 203.0.113.5 to 192.168.1.10).
- PAT (Port Address Translation, aka `masquerading`): Multiple devices share one public IP by mapping connections to different ports.   
- In Kubernetes context:
    - Kube-proxy may use NAT (via iptables/ipvs) to redirect Service ClusterIP to Pod IP.
    - The Kubernetes networking model tries to minimize NAT inside the cluster: every Pod gets a unique, routable IP so pods can talk directly, no hidden rewrites. NAT is mostly used only at the cluster boundary (e.g., NodePort, LoadBalancer, egress to the Internet).

```mermaid
flowchart LR
subgraph Private["Private Network (LAN)"]
    A["Pod / Host<br/>192.168.1.10"]
    B["Pod / Host<br/>192.168.1.11"]
end

subgraph Router["Router / NAT Device"]
    N1["Source NAT (SNAT)<br/>Change source 192.168.x.x → 203.0.113.5"]
    N2["Destination NAT (DNAT)<br/>Change destination 203.0.113.5 → 192.168.1.10"]
end

subgraph Internet["Public Internet"]
    S["Public Server<br/>198.51.100.20"]
end

%% Outbound
A -->|"Outbound packet<br/>Src=192.168.1.10, Dst=198.51.100.20"| N1
N1 -->|"Translated packet<br/>Src=203.0.113.5, Dst=198.51.100.20"| S

%% Inbound
S -->|"Inbound packet<br/>Dst=203.0.113.5"| N2
N2 -->|"Translated packet<br/>Dst=192.168.1.10"| A

%% Styling
classDef private fill:#f0fff0,stroke:#2e8b57,stroke-width:2px;
classDef nat fill:#fffacd,stroke:#daa520,stroke-width:2px;
classDef internet fill:#f0f8ff,stroke:#4169e1,stroke-width:2px;
class Private private
class Router nat
class Internet internet
```

{% enddetails %}
{% details The Four Networking Requirements %}

- NAT: Network Address Translation
- [Per K8s design](https://kubernetes.io/docs/concepts/cluster-administration/networking/#the-kubernetes-network-model), Kubernetes assumes a flat, non-NATted network between all entities:
    - All pods can communicate with all other pods without NAT.
    - All nodes can communicate with all pods without NAT.
    - Pod IPs are the same inside and outside the pod. (No masquerading from the pod’s perspective).
    - Services (ClusterIP, NodePort, LoadBalancer) are implemented via virtual IPs and iptables/ipvs rules that redirect traffic to backing pods.
- This model makes things simple at the app level: each pod just gets an IP and DNS name, no special networking code.

{% enddetails %}
{% details How Services Work Under the Hood %}

- ClusterIP: The kube-proxy component sets up iptables or ipvs rules to redirect traffic from the service’s virtual IP to one of the pod IPs behind it.
- NodePort: Kube-proxy additionally opens a port (30000–32767) on each node, then DNATs traffic to the service ClusterIP.

{% enddetails %}
{% details Container Networking Interface (CNI) %}

- Kubernetes itself does not implement networking.
- It relies on CNI plugins to configure pod networking.
- CNI is a specification: containers call CNI when they’re created, and CNI sets up network interfaces, IP assignment, and routing.
    - kubelet launches a pod and calls the configured CNI plugin.
    - The plugin sets up a veth pair (virtual Ethernet) to connect the pod’s network namespace to the host.
    - IP address is assigned (via IPAM plugin or cluster-wide allocator).
    - Routes and bridges are created to connect pod-to-pod and pod-to-node traffic.

{% enddetails %}
{% details Popular CNI Implementations %}

- Flannel: Simple overlay network (VXLAN), flat layer-3 fabric.
- Calico: Pure layer-3 networking with BGP; supports network policies.
- Cilium: Uses eBPF for dataplane efficiency and fine-grained security.
- Weave Net: Simple mesh overlay, encrypted by default.

{% enddetails %}
{% details Suggested Readings %}

- [The CNI Spec (Container Network Interface, CNCF project)](https://github.com/containernetworking/cni)
{% enddetails %}
