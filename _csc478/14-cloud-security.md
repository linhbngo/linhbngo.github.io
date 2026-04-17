---
layout: lecture
pretty_table: true
collection: csc478
title: "Cloud Security"
toc:
  - name: Cloud Native Security
  - name: Cluster Security: Kubernetes
  - name: Container Security
---
# Cloud Security

## Cloud Native Security

{% details Overview %}

- Followed a layered approach that is based on [defense in depth](https://inldigitallibrary.inl.gov/sites/sti/sti/3375141.pdf) approach. 
- The 4C layers of Cloud Native Security
    - Cloud Datacenter
    - Cluster (Kubernetes)
    - Container
    - Code

{% enddetails %}
{% details Cloud Data Center %}

- Cloud Provider: Their hardware their policy
- In-house infrastructures
    - Physical security
    - Network access
    - Database access (`etcd` for Kubernetes)

{% enddetails %}
{% details Cluster (Kubernetes) %}

- **RBAC Authorization**
- **Authentication**
- Encryption
- Network Policies
- **TLS for Kubernetes Ingress**

{% enddetails %}
{% details Container %}

- Vulnerability Scanner/OS Dependencsy Security
- Privilege Control/Disabling
- Container runtime isolation 

{% enddetails %}
{% details Code %}

- Secure communication over TLS
- Port range limitation
- Security of external library dependency
- Static code analysis
- Dynamic code security (SQL injection, cross-site scripting, ...)

{% enddetails %}
---

## Cluster Security: Kubernetes

{% details Authentication %}

- Users: 
    - Normal users (managed by host system/remote management like LDAP)
    - Service accounts (internal to K8s)
- Users can present a valid certificate signed by the cluster's CA (Certificate Authority) 
are considered authenticated.  

{% enddetails %}
{% details Authentication hands-on %}


{% details info Confirms that Rancher setup is up and ready %}


```bash
kubectl get nodes
```

{% include figure.liquid path="assets/img/courses/csc478/cloud-security/get-nodes.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info Extract configuration information %}


```bash
cat ~/.kube/config
```

- Keep a record of the following fields (or do this in separate terminals)
    - `certificate-authority-data`
    - `server`
    - `client-certificate-data`
    - `client-key-data`

{% enddetails %}
{% details info Create a new user account %}

- New user account is called `student`:

```bash
sudo useradd -s /bin/bash -d /home/student -m -G docker student
sudo su - student
```

- Try running `kubectl` commands now:

```bash
kubectl get nodes
kubectl get svc
```

{% include figure.liquid path="assets/img/courses/csc478/cloud-security/student-not-auth.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info Setup authorization to access K8S %}

- As `student`, run the following command:

```bash
mkdir .kube
```

- Next, create a file called `config` inside `.kube` with the following 
contents:
    - Replace `COPY_FROM_ABOVE` with the corresponding values of the corresponding fields above. 

```yaml
apiVersion: v1
clusters:
- cluster:
    certificate-authority-data: COPY_FROM_ABOVE
    server: COPY_FROM_ABOVE
name: kubernetes
contexts:
- context:
    cluster: kubernetes
    user: student
  name: student@kubernetes
current-context: student@kubernetes
kind: Config
preferences: {}
users:
- name: student
user:
    client-certificate-data: COPY_FROM_ABOVE
    client-key-data: COPY_FROM_ABOVE
```

- Try running `kubectl` commands now:

```bash
kubectl get nodes
kubectl get svc
```

{% include figure.liquid path="assets/img/courses/csc478/cloud-security/student-auth.png" width="50%" zoomable=true %}

{% enddetails %}
{% enddetails %}
{% details Challenge %}

Adding at least another Kubernetes cluster from one of your classmates' experiment to your 
`student` account. In other words, one account can have access to multiple K8S cluster. 

{% enddetails %}
{% details RBAC Authorization %}

- Kubernetes uses the `rbac.authorization.k8s.io` API group to drive RBAC-based authorization decisions, 
- By default, Kubernetes clusters are often launched with RBAC:

```bash
kubectl describe pods kube-apiserver -n kube-system | grep authorization
```

- RBAC API: Role, ClusterRole, RoleBinding, ClusterRoleBinding. 
- Role: sets permissions within a particular namespace

```bash
kubectl get role --all-namespaces
kubectl describe role system::leader-locking-kube-controller-manager -n kube-system
```

- ClusterRole: set permission for non-namespaced resources

```bash
kubectl get clusterrole --all-namespaces
kubectl describe clusterrole cluster-admin
```

- RoleBinding binding grants the permissions defined in a role to a user or set of users. 
- ClusterRoleBinding grants that access cluster-wide.

```bash
kubectl get RoleBinding --all-namespaces
kubectl get ClusterRoleBinding
```

- What `resources` are available and what `verbs` are applicable?

```bash
kubectl api-resources --sort-by name -o wide
```

{% enddetails %}
{% details Kubernetes Ingress %}


- Ingress exposes HTTP and HTTPS routes from outside the cluster to services within the 
cluster. 
- Traffic routing is controlled by rules defined on the Ingress resource.
- Ingress is managed by Ingress Controllers. 
- There are many diffferent Ingress Controllers

{% enddetails %}
---

## Container Security

{% details Pod Security Standards %}

- Pod security will influence container security. 
- Three policies:
    - Privileged
    - Baseline
    - Restricted 
- Cummulative and range from highly permissive to highly restrictive

{% enddetails %}
{% details Privileged %}

- Purposely open, entirely unrestricted
- Enable system- and infrastructure-level workloads
    - Implied understanding that these workloads are run as privileged/trusted users. 
- Absence of restrictions and allow-by-default mechanism

{% enddetails %}
{% details Baseline %}

- Streamline adoption for common containerized workloads
- Prevent known privilege escalations
- Example capabilities (Linux capabilities) enabled in baseline
    - AUDIT_WRITE
    - CHOWN
    - DAC_OVERRIDE
    - FOWNER
    - FSETID
    - KILL
    - MKNOD
    - NET_BIND_SERVICE
    - SETFCAP
    - SETGID
    - SETPCAP
    - SETUID
    - SYS_CHROOT
- [Linux full capability list](https://man7.org/linux/man-pages/man7/capabilities.7.html)  

{% enddetails %}
{% details Restricted %}

- Enforce Pod hardening best practices at the expense of compatibility
- Target security-critical applications and lower-trust users
- Example policy:
    - Disable privilege escalation
    - Containers must run as non-root
    - Drop **ALL** capabilities and only allow `NET_BIND_SERVICE`. 



{% enddetails %}
