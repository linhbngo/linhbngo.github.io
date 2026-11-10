---
layout: lecture
pretty_table: true
collection: csc478
title: "Load Balancing, Services, and Ingress"
toc:
  - name: Load Balancing
  - name: Load Balancing Algorithms
  - name: "Load Balancing: AWS, GCP, and Kubernetes"
  - name: RKE2 Service Exposure and Ingress
  - name: Hands-on
  - name: References
---

## Load Balancing

{% details Overview %}

- Load balancing distributes network traffic across a pool of resources that
support an application. 
- The goal is not always an equal split: routing can also
consider capacity, health, locality, connection state, or policy.

{% enddetails %}

{% details Benefits %}

Load balancers can improve an application's availability, scalability,
security, and performance.

{% details note Availability %}

Increase the fault tolerance of systems by automatically detecting server problems and redirecting 
client traffic to available servers.

- Run application server maintenance or upgrades without application downtime (rolling actions)
- Provide automatic disaster recovery to backup sites
- Perform health checks and prevent issues that can cause downtime

{% enddetails %}

{% details note Scalability %}

Direct network traffic intelligently among multiple servers

- Prevents traffic bottlenecks at any one server
- Predicts application traffic so that servers can be added or removed if needed
- Adds redundancy to support dynamic scaling

{% enddetails %}

{% details note Security %}

Can contain built-in security features to add another layer of security to Internet applications. 

- Monitor traffic and block malicious content
- Automatically redirect attack traffic to multiple backend servers to minimize impact
- Route traffic through a group of network firewalls for additional security

{% enddetails %}
{% details note Performance %}

Improve application performance by decreasing response time and reducing network latency.

- Distribute the load evenly between servers to improve application performance
- Redirect client requests to a geographically closer server to reduce latency
- Ensure the reliability and performance of physical and virtual computing resources

{% enddetails %}
{% enddetails %}


## Load Balancing Algorithms

{% details Static load balancing %}

Static load balancing algorithms follow fixed rules and are independent of the current server state. 

{% details note Round-robin method %}

In the round-robin method, the load balancer sends successive new requests or
connections to backends in turn. DNS round-robin is one implementation, but
round-robin is also used directly by network and application load balancers.

{% enddetails %}

{% details note Weighted round-robin method %}

In weighted round-robin load balancing, administrators assign weights based on
backend priority or capacity. Backends with higher weights receive a larger
share of new traffic.

{% enddetails %}

{% details note IP hash method %}

In the IP hash method, the load balancer performs a mathematical computation, called hashing, on the client IP address. It converts the client IP address to a number, which is then mapped to individual servers.

{% enddetails %}

{% enddetails %}

{% details Dynamic load balancing %}

Dynamic load balancing algorithms examine the current state of the servers before distributing traffic. 

{% details note Least connection method %}

A connection is an established communication channel between a client and a
server. In the least-connections method, the load balancer sends a new
connection to the backend with the fewest active connections. This method
usually assumes that connections have comparable cost.

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

{% details Kubernetes placement and Service forwarding %}

- `kube-scheduler` chooses a node for each unscheduled Pod.
- EndpointSlice controllers track the ready endpoints selected by a Service.
- `kube-proxy`, or a CNI dataplane that replaces it, programs node networking
  so Service traffic can reach those endpoints.

The current FABRIC RKE2 configuration uses the default Canal CNI and does not
select another kube-proxy mode. RKE2 v1.36 therefore uses kube-proxy's
`iptables` mode by default. 

- [Kubernetes: Virtual IPs and Service Proxies](https://kubernetes.io/docs/reference/networking/virtual-ips/)
- [RKE2: Network Options](https://docs.rke2.io/networking/basic_network_options)

{% enddetails %}


## Load Balancing: AWS, GCP, and Kubernetes

{% details Overview %}

| Layer | AWS | GCP | Closest Kubernetes concept |
| --- | --- | --- | --- |
| External frontend | Listener | Forwarding rule | A `Service` port or an Ingress listener, implemented by a controller |
| Backend set | Target group | Backend service | Service selectors and EndpointSlices are analogous, but cloud controllers manage the cloud backend objects |
| Backend health | Target-group health check | Load-balancer health check | Readiness controls whether a Pod is a Service endpoint; an external load balancer may separately probe nodes or backends |
| L4 load balancer | Network Load Balancer | Network Load Balancer | `Service` with `type: LoadBalancer`, when a provider or load-balancer controller implements it |
| L7 load balancer | Application Load Balancer | Application Load Balancer | Ingress or Gateway API plus a controller |
| Pod scaling | EKS/Kubernetes HPA | GKE/Kubernetes HPA | Horizontal Pod Autoscaler and workload controllers |
| Node scaling | EC2 Auto Scaling / Cluster Autoscaler | Managed Instance Group / Cluster Autoscaler | A node autoscaler; ReplicaSets do not create or replace nodes |

- Cloud load balancers provide externally reachable frontends and provider
  health checks.
- Kubernetes Services provide stable virtual addresses and endpoint selection
  inside the cluster.
- A cloud controller or another load-balancer controller connects these layers.
- A liveness probe restarts an unhealthy container. It is not equivalent to an
  external load-balancer health check.

{% enddetails %}

{% details NodePort: externally reachable Service port %}

NodePort exposes Service forwarding on a port from the configured NodePort
range, normally `30000-32767`.

{% details success What it does %}

- Opens the same TCP/UDP port on each eligible node.
- With the default `externalTrafficPolicy: Cluster`, a node can forward a new
  connection to any ready Service endpoint.
- Distribution is connection-oriented and is not guaranteed to be perfectly
  even.
- Session affinity, topology policy, proxy mode, and endpoint readiness can
  change which backend receives a connection.

{% enddetails %}

{% details What it does not do %}

- It does not allocate a stable external IP or DNS name.
- It does not choose a healthy node for an external client.
- If a node is unreachable, the client or an external load balancer must select
  another node.
- With `externalTrafficPolicy: Local`, a node forwards only to ready endpoints
  on that node. A node without a local endpoint drops that external traffic.

{% enddetails %}

{% enddetails %}

## Hands-on

Use the four-node FABRIC RKE2 slice created by the nodebook `11_rke2_lb.ipynb` inside `11_rke2_lb` directory. SSH to `node1` and run every command below there.

{% details Step 1: Preflight the actual cluster %}

SSH into `node1` and record the software version and node topology before relying on version-specific
behavior:

```bash
kubectl version
kubectl get nodes -o wide
kubectl get nodes \
  -o custom-columns='NAME:.metadata.name,ROLES:.metadata.labels.node-role\.kubernetes\.io/control-plane,TAINTS:.spec.taints'
kubectl get ingressclass
kubectl -n kube-system get pods | grep -E 'kube-proxy|traefik|ingress'
```

The RKE2 installation script used by the notebook is not version-pinned. A
newly created slice may therefore have a newer RKE2 release than a recorded
example.

Check whether a previous validation workload still owns the desired NodePort:

```bash
kubectl get svc -A | grep -E '30080|30081' || true
```

The provisioning playbook may briefly create `nginx-demo` on port 30080. This
lab uses port 30081 to avoid that known collision. If 30081 is already in use,
delete the stale lab Service or choose another unused port in the configured
NodePort range.

{% enddetails %}

{% details Step 2: Deploy a Local-policy NodePort Service %}

Create `nodeport.yaml`:

```yaml
apiVersion: v1
kind: Namespace
metadata:
  name: lb-nodeport

---
apiVersion: apps/v1
kind: Deployment
metadata:
  name: web
  namespace: lb-nodeport
spec:
  replicas: 2
  selector:
    matchLabels:
      app: web
  template:
    metadata:
      labels:
        app: web
    spec:
      affinity:
        podAntiAffinity:
          requiredDuringSchedulingIgnoredDuringExecution:
            - labelSelector:
                matchLabels:
                  app: web
              topologyKey: kubernetes.io/hostname
      containers:
        - name: nginx
          image: nginx:alpine
          command: ["/bin/sh", "-c"]
          args:
            - |
              echo "Node: ${NODE_NAME} | Pod: $(hostname)" \
                > /usr/share/nginx/html/index.html
              exec nginx -g 'daemon off;'
          env:
            - name: NODE_NAME
              valueFrom:
                fieldRef:
                  fieldPath: spec.nodeName
          ports:
            - name: http
              containerPort: 80
          readinessProbe:
            httpGet:
              path: /
              port: http
            initialDelaySeconds: 2
            periodSeconds: 3
          livenessProbe:
            httpGet:
              path: /
              port: http
            initialDelaySeconds: 10
            periodSeconds: 10

---
apiVersion: v1
kind: Service
metadata:
  name: web-np
  namespace: lb-nodeport
spec:
  type: NodePort
  externalTrafficPolicy: Local
  selector:
    app: web
  ports:
    - name: http
      port: 80
      targetPort: http
      nodePort: 30081
```

Apply it and wait for both replicas:

```bash
kubectl apply -f nodeport.yaml
kubectl -n lb-nodeport rollout status deployment/web --timeout=180s
kubectl -n lb-nodeport get pods -o wide
kubectl -n lb-nodeport get service web-np
kubectl -n lb-nodeport get endpointslice -l kubernetes.io/service-name=web-np
```

Hard Pod anti-affinity places the two replicas on different hostnames. It does
not mean "worker nodes only": in this FABRIC configuration, `node1` is also
schedulable.

{% enddetails %}

{% details Step 3: Observe externalTrafficPolicy Local %}

From `node1`, test all three **node** dataplane addresses:

```bash
for ip in 192.168.1.1 192.168.1.2 192.168.1.3; do
  printf '%s -> ' "$ip"
  curl --silent --show-error --connect-timeout 2 --max-time 3 \
    "http://${ip}:30081/" || echo "no local ready endpoint"
done
```

Expected result:

- the two nodes that host ready Pods return their node and Pod names;
- the third node fails because `externalTrafficPolicy: Local` prevents it from
  forwarding this external traffic to a Pod on another node.

A timeout, reset, or refusal can all represent failure here; the exact client
error depends on the node networking and packet path.

{% enddetails %}

{% details Step 4: Move one endpoint predictably %}

Deleting a Pod alone is not a node failure, and the replacement may return to
the same node too quickly to observe. Cordon its node first:

```bash
TARGET_POD=$(
  kubectl -n lb-nodeport get pods -l app=web \
    -o jsonpath='{.items[0].metadata.name}'
)
TARGET_NODE=$(
  kubectl -n lb-nodeport get pod "$TARGET_POD" \
    -o jsonpath='{.spec.nodeName}'
)

echo "Moving endpoint away from ${TARGET_NODE}"
kubectl cordon "$TARGET_NODE"
kubectl -n lb-nodeport delete pod "$TARGET_POD"
kubectl -n lb-nodeport rollout status deployment/web --timeout=180s
kubectl -n lb-nodeport get pods -o wide
```

With three schedulable FABRIC nodes, the cordon plus hard anti-affinity forces
the replacement onto the previously unused node. Test all addresses again:

```bash
for ip in 192.168.1.1 192.168.1.2 192.168.1.3; do
  printf '%s -> ' "$ip"
  curl --silent --show-error --connect-timeout 2 --max-time 3 \
    "http://${ip}:30081/" || echo "no local ready endpoint"
done
```

The cordoned node now has no local endpoint and should fail. The node receiving
the replacement should now answer.

Restore scheduling even if a later step fails:

```bash
kubectl uncordon "$TARGET_NODE"
```

This demonstrates endpoint locality and relocation. Cordon does not shut down
the node and should not be described as a complete node failure.

{% enddetails %}

{% details Step 5: Compare externalTrafficPolicy Cluster %}

Change the Service to the default cluster-wide policy:

```bash
kubectl -n lb-nodeport patch service web-np \
  --type merge \
  -p '{"spec":{"externalTrafficPolicy":"Cluster"}}'
kubectl -n lb-nodeport get service web-np \
  -o jsonpath='{.spec.externalTrafficPolicy}{"\n"}'
```

Test all three node IPs again:

```bash
for ip in 192.168.1.1 192.168.1.2 192.168.1.3; do
  printf '%s -> ' "$ip"
  curl --silent --show-error --connect-timeout 2 --max-time 3 \
    "http://${ip}:30081/" || echo "request failed"
done
```

All reachable nodes should now be able to forward to a ready endpoint,
including a node with no local Pod. This may add a cross-node hop and commonly
changes source-address preservation.

{% enddetails %}

{% details Step 6: Observe LoadBalancer behavior without a controller %}

Create a second Service:

```bash
kubectl -n lb-nodeport expose deployment web \
  --name web-lb \
  --port 80 \
  --target-port 80 \
  --type LoadBalancer
kubectl -n lb-nodeport get service web-lb -w
```

Exit the watch with `Ctrl-C`. In the course FABRIC configuration,
`EXTERNAL-IP` should remain `<pending>` because neither RKE2 ServiceLB nor
another load-balancer controller is enabled. If an address appears, inspect
the cluster: its configuration differs from the expected lab environment.

```bash
kubectl -n lb-nodeport delete service web-lb
```

{% enddetails %}

{% details Step 7: Route through RKE2 Traefik %}

Confirm that the cluster has a `traefik` IngressClass:

```bash
kubectl get ingressclass
kubectl -n kube-system get pods | grep traefik
```

Create `ingress.yaml`:

```yaml
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: web
  namespace: lb-nodeport
spec:
  ingressClassName: traefik
  rules:
    - host: web.lb.test
      http:
        paths:
          - path: /
            pathType: Prefix
            backend:
              service:
                name: web-np
                port:
                  number: 80
```

Apply the route and send the required HTTP `Host` header. No DNS record is
needed for this test:

```bash
kubectl apply -f ingress.yaml
kubectl -n lb-nodeport get ingress web

for ip in 192.168.1.1 192.168.1.2 192.168.1.3; do
  printf '%s -> ' "$ip"
  curl --silent --show-error --connect-timeout 2 --max-time 3 \
    -H 'Host: web.lb.test' "http://${ip}/" || echo "ingress request failed"
done
```

Traffic first reaches the RKE2 Traefik controller on port 80. Traefik then
routes by hostname and path to the Service and its ready endpoints.

If `traefik` is not present, do not install ingress-nginx for this exercise.
First check the RKE2 version, `IngressClass`, and server configuration to
determine which supported controller the cluster actually uses.

{% enddetails %}

{% details Cleanup %}

```bash
kubectl delete namespace lb-nodeport
```

Also confirm that any node cordoned during the exercise is schedulable:

```bash
kubectl get nodes
```

{% enddetails %}

{% details career Load balancing decisions express service objectives %}

Production load balancing is not simply “spread requests evenly.” Engineers
choose behavior based on latency, backend capacity, locality, failure
handling, connection state, and whether the original client address must be
preserved.

Google's
[SRE chapter on frontend load balancing](https://sre.google/sre-book/load-balancing-frontend/)
describes multiple layers, including DNS and virtual IPs, and explains why
proximity alone is insufficient: the selected location must also have capacity
and healthy infrastructure.

When evaluating the NodePort experiment, frame the result operationally:

- `externalTrafficPolicy: Local` preserves local routing properties but nodes
  without ready local endpoints cannot serve that traffic;
- cluster-wide forwarding improves endpoint reachability but may add a
  network hop and alter source-address behavior;
- health checks and draining determine whether failures become user-visible.

Explaining these tradeoffs is a common system-design interview and production
review skill.

{% enddetails %}

## References

- [AWS: What is LoadBalancing](https://aws.amazon.com/what-is/load-balancing/)
- [Kubernetes: Service](https://kubernetes.io/docs/concepts/services-networking/service/)
- [Kubernetes: Virtual IPs and Service Proxies](https://kubernetes.io/docs/reference/networking/virtual-ips/)
- [Kubernetes: Ingress](https://kubernetes.io/docs/concepts/services-networking/ingress/)
- [RKE2: Networking Services](https://docs.rke2.io/networking/networking_services)
- [RKE2: Network Options](https://docs.rke2.io/networking/basic_network_options)
- [RKE2: v1.36 Release Notes](https://docs.rke2.io/release-notes/v1.36.X)
- [Google SRE: Load Balancing at the Frontend](https://sre.google/sre-book/load-balancing-frontend/)
