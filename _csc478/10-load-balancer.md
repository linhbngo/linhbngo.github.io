---
layout: lecture
pretty_table: true
collection: csc478
title: "LoadBalancer and Ingress"
toc:
  - name: LoadBalancer
  - name: Load Balancing Algorithms
  - name: Load Balancing: AWS, GCP, and Kubernetes
  - name: Hands-on
  - name: References
---

# LoadBalancer and Ingress


## LoadBalancer

{% details Overview %}

Load balancing is the method of distributing network traffic equally across a pool of 
resources that support an application.

{% enddetails %}
{% details Benefits %}

Load balancers improves an application's availability, scalability, security, and performance. 

{% details note Application availability %}

Increase the fault tolerance of systems by automatically detecting server problems and redirecting 
client traffic to available servers.

- Run application server maintenance or upgrades without application downtime (rolling actions)
- Provide automatic disaster recovery to backup sites
- Perform health checks and prevent issues that can cause downtime

{% enddetails %}
{% details note Application scalability %}

Direct network traffic intelligently among multiple servers

- Prevents traffic bottlenecks at any one server
- Predicts application traffic so that servers can be added or removed if needed
- Adds redundancy to support dynamic scaling

{% enddetails %}
{% details note Application security %}

Can contain built-in security features to add another layer of security to Internet applications. 

- Monitor traffic and block malicious content
- Automatically redirect attack traffic to multiple backend servers to minimize impact
- Route traffic through a group of network firewalls for additional security

{% enddetails %}
{% details note Application performance %}

Improve application performance by increasing response time and reducing network latency.

- Distribute the load evenly between servers to improve application performance
- Redirect client requests to a geographically closer server to reduce latency
- Ensure the reliability and performance of physical and virtual computing resources

{% enddetails %}
{% enddetails %}
## Load Balancing Algorithms

{% details Static load balancing %}

Static load balancing algorithms follow fixed rules and are independent of the current server state. 

{% details note Round-robin method %}

In the round-robin method, an authoritative name server does the load balancing by returning the IP addresses of different 
servers in the server farm turn by turn or in a round-robin fashion.

{% enddetails %}
{% details note Weighted round-robin method %}

In weighted round-robin load balancing, administrators can assign different weights to each server based on their 
priority or capacity. Servers with higher weights will receive more incoming application traffic from the name server.

{% enddetails %}
{% details note IP hash method %}

In the IP hash method, the load balancer performs a mathematical computation, called hashing, on the client IP address. It converts the client IP address to a number, which is then mapped to individual servers.

{% enddetails %}
{% enddetails %}
{% details Dynamic load balancing %}

Dynamic load balancing algorithms examine the current state of the servers before distributing traffic. 

{% details note Least connection method %}

A connection is an open communication channel between a client and a server. When the client sends the first request to the server, they authenticate and establish an active connection between each other. In the least connection method, the load balancer checks which servers have the fewest active connections and sends traffic to those servers. This method assumes that all connections require equal processing power for all servers.

{% enddetails %}
{% details note Weighted least connection method %}

Weighted least connection algorithms assume that some servers can handle more active connections than others. Therefore, 
different weights can be assigned to each server, and the load balancer sends the new client requests to the server with the least connections by capacity.

{% enddetails %}
{% details note Least response time method %}

The response time is the total time that the server takes to process the incoming requests and send a response. The least response time method combines the server response time and the active connections to determine the best server. Load balancers use this algorithm to ensure faster service for all users.

{% enddetails %}
{% details note Resource-based method %}

In the resource-based method, load balancers distribute traffic by analyzing the current server load. Specialized software called an agent runs on each server and calculates usage of server resources, such as its computing capacity and memory. Then, the load balancer checks the agent for sufficient free resources before distributing traffic to that server.

{% enddetails %}
{% enddetails %}
{% details Kubernetes scheduling %}

- Done via kube control plane using `ipvs`.
- [IPVS proxy mode](https://kubernetes.io/docs/reference/networking/virtual-ips/#proxy-mode-ipvs)

{% enddetails %}
## Load Balancing: AWS, GCP, and Kubernetes

{% details Overview %}


| Cloud / System | Component                               | Purpose                                                                     | Kubernetes Equivalent                                                | Where It Runs                                  |
| -------------- | --------------------------------------- | --------------------------------------------------------------------------- | -------------------------------------------------------------------- | ---------------------------------------------- |
| **AWS**        | **Listener**                            | Accepts external connections on port 80/443 and forwards to a target group  | `Service` port definition                                            | Inside cluster via **kube-proxy**              |
| **GCP**        | **Forwarding Rule**                     | Maps an external IP and port to a backend service (similar to AWS Listener) | `Service` port definition                                            | Managed by **GCP load-balancer control plane** |
| **AWS**        | **Target Group**                        | Defines backend EC2 instances or Pods (via EKS integration)                 | Service **endpoints** (Pod IPs)                                      | Managed by **kube-controller-manager**         |
| **GCP**        | **Backend Service**                     | Defines backends (VMs, MIGs, or GKE Pods) and load balancing behavior       | Service **endpoints** (Pod IPs)                                      | Managed by **GKE controller**                  |
| **AWS**        | **Health Check**                        | Checks targets’ health via HTTP/TCP pings                                   | Pod **readiness/liveness probes**                                    | Runs inside Pods                               |
| **GCP**        | **Health Check Probe**                  | Similar to AWS, integrated with backend service                             | Pod **readiness/liveness probes**                                    | Runs inside Pods                               |
| **AWS**        | **Elastic Load Balancer (NLB / ALB)**   | Front-end L4/L7 routing to healthy targets                                  | `Service` type=`LoadBalancer` (via **AWS Cloud Controller Manager**) | In AWS Cloud                                   |
| **GCP**        | **Network / HTTP(S) Load Balancer**     | Front-end L4 (Network) or L7 (HTTP(S)) routing                              | `Service` type=`LoadBalancer` (via **GCP Cloud Controller Manager**) | In GCP Cloud                                   |
| **AWS**        | **Failover / Auto Scaling**             | Replaces unhealthy nodes using EC2 Auto Scaling groups                      | K8s control plane (**scheduler**, **replicasets**)                   | Cluster-wide                                   |
| **GCP**        | **Managed Instance Group + Autoscaler** | Replaces failed nodes / Pods using GCE or GKE autoscaling                   | K8s control plane (**Horizontal Pod Autoscaler**, **replicasets**)   | Cluster-wide                                   |


- AWS and GCP LBs both act at the edge of the VPC.
- Kubernetes load balancing happens inside the cluster, so these are complementary, not redundant.
    - AWS Listener ≈ GCP Forwarding Rule ≈ K8s Service Port.
    - AWS Target Group ≈ GCP Backend Service ≈ K8s Endpoints.
    - AWS NLB/ALB ≈ GCP Network/HTTP(S) LB ≈ K8s LoadBalancer Service.

{% enddetails %}
{% details NodePort: The Proto-LoadBalancer %}

NodePort has load-balancing behavior, but with important caveats.
    - DIY Load Balancing

{% details success What it does %}

- Opens the same TCP/UDP port (e.g., 30080) on every node.
- `kube-proxy` evenly distributes incoming connections across all ready Pods, regardless of which node the traffic lands on.
- From a client’s point of view, any node’s `IP:NodePort` works as a gateway to all Pods.

{% enddetails %}
{% details What it does not do %}

- No built-in external IP or DNS endpoint (you must choose a node manually).
- No health checks on nodes (only Pods).
- No HA routing if an entire node fails — clients must retry a different node.


{% enddetails %}
{% enddetails %}
## Hands-on

This should be done on a Kubernetes cluster with two worker nodes (3 in total at least for CloudLab)


{% details NodePort with per-node failure visibility %}

- We set `externalTrafficPolicy` to local for NodePort so that a node only 
serves traffic if it has a ready pod for the Service
- Create a manifest called `nodeport.yaml` with the following contents:

```yaml
# A1) Namespace
apiVersion: v1
kind: Namespace
metadata:
    name: lb-nodeport

---

# A2) NGINX Deployment with 2 replicas and hard anti-affinity to split nodes
apiVersion: apps/v1
kind: Deployment
metadata:
    name: web
    namespace: lb-nodeport
    labels: { app: web } # We can do this on single line with curly bracket
spec:
  replicas: 2
  selector:
    matchLabels: { app: web }
  template:
    metadata:
      labels: { app: web }
    spec:
      affinity:
        podAntiAffinity:
          requiredDuringSchedulingIgnoredDuringExecution:
            - labelSelector:
                matchLabels: { app: web }
              topologyKey: "kubernetes.io/hostname"
      containers:
        - name: nginx
          image: nginx:1.27-alpine
          ports: [{ containerPort: 80 }]
          # Make the default page show which node/hostname served it
          args: ["sh","-c","echo \"Node: $(NODE_NAME) | Pod: $(hostname)\" > /usr/share/nginx/html/index.html && nginx -g 'daemon off;'"]
          env:
            - name: NODE_NAME
              valueFrom:
                fieldRef: { fieldPath: spec.nodeName }
          readinessProbe:
            httpGet: { path: "/", port: 80 }
            initialDelaySeconds: 2
            periodSeconds: 3
          livenessProbe:
            httpGet: { path: "/", port: 80 }
            initialDelaySeconds: 10
            periodSeconds: 10

---
# A3) NodePort Service (L4), externalTrafficPolicy=Local to bind traffic to local pod only
apiVersion: v1
kind: Service
metadata:
  name: web-np
  namespace: lb-nodeport
spec:
  type: NodePort
  externalTrafficPolicy: Local
  selector: { app: web }
  ports:
    - name: http
      port: 80
      targetPort: 80
      nodePort: 30080
```

- First, apply the manifest

```bash
kubectl apply -f nodeport.yaml`
kubectl -n lb-nodeport get pods -o wide
```
- Confirm that the two pod are on different nodes by checking the `NODE` column. 
- Hit each node directly:

```bash
# Replace with your node IPs (not the pod IPs)
curl -s http://<NODE1_IP>:30080/
curl -s http://<NODE2_IP>:30080/
```

- You should see which node served the page: Node: <node> | Pod: <podname>
- Simulate a replica failure on NODE1:

```bash
# Find the pod that sits on NODE1
kubectl -n lb-nodeport get pods -o wide
kubectl -n lb-nodeport delete pod <pod-on-NODE1>
```

- Kubernetes will eventually reschedule a new pod (possibly on NODE2 first). During that window,

```bash
curl -s --max-time 2 http://<NODE1_IP>:30080/   # likely times out / connection refused
curl -s --max-time 2 http://<NODE2_IP>:30080/   # still serves traffic
```

- Because `externalTrafficPolicy: Local`, NODE1 no longer has a ready endpoint, therefore its NodePort fails. NODE2 still works.

{% enddetails %}
{% details Challenge %}

Attempt to recreate the above example in a different namespace, this time without `externalTrafficPolicy: Local` and 
observe what happens when a pod replica fails. 


{% enddetails %}
## References

- [AWS: What is LoadBalancing](https://aws.amazon.com/what-is/load-balancing/)
