---
layout: lecture
pretty_table: true
collection: csc588
course: CSC 603: Access Control in the Cloud
title: "Cloud Security"
toc:
  - name: Cloud Native Security
  - name: Cluster Security: Kubernetes
  - name: Container Security
---
# Cloud Security

## Cloud Native Security

{% details Overview %}

{% enddetails %}
- Followed a layered approach that is based on [defense in depth](https://inldigitallibrary.inl.gov/sites/sti/sti/3375141.pdf) approach. 
- The 4C layers of Cloud Native Security
  - Cloud Datacenter
  - Cluster (Kubernetes)
  - Container
  - Code

{% details Cloud Data Center %}

{% enddetails %}
- Cloud Provider: Their hardware their policy
- In-house infrastructures
  - Physical security
  - Network access
  - Database access (`etcd` for Kubernetes)


{% details Cluster (Kubernetes) %}

{% enddetails %}
  - **RBAC Authorization**
  - **Authentication**
  - Encryption
  - Network Policies
  - **TLS for Kubernetes Ingress**

{% details Container %}

{% enddetails %}
  - Vulnerability Scanner/OS Dependencsy Security
  - Privilege Control/Disabling
  - Container runtime isolation

{% details Code %}

{% enddetails %}
  - Secure communication over TLS
  - Port range limitation
  - Security of external library dependency
  - Static code analysis
  - Dynamic code security (SQL injection, cross-site scripting, ...)
```

## Cluster Security: Kubernetes

{% details Authentication %}


{% enddetails %}
- Users: 
  - Normal users (managed by host system/remote management like LDAP)
  - Service accounts (internal to K8s)
- Users can present a valid certificate signed by the cluster's CA (Certificate Authority) 
are considered authenticated.  


{% details Authentication hands-on %}


{% enddetails %}
- Instantiate from branch `k8s-helm` of the `csc603ngo` CloudLab profile 
- Once the experiment is fully deployed, **and all Startup Finished running**:
- SSH into the head node and run the followings

~~~
$ cat ~/.kube/config
~~~

- Keep a record of the following fields (or do this in separate terminals)
  - `certificate-authority-data`
  - `server`
  - `client-certificate-data`
  - `client-key-data`

- Create a new user called `student`:

~~~
$ sudo useradd -s /bin/bash -d /home/student -m -G docker student
$ sudo su - student
~~~

- Try running `kubectl` commands now:

~~~
$ kubectl get nodes
$ kubectl get svc
~~~

- As `student`, run the following command:

~~~
$ mkdir .kube
~~~

- Next, create a file called `config` inside `.kube` with the following 
contents:
  - Replace `COPY_FROM_ABOVE` with the corresponding values of the corresponding fields above. 

~~~
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
~~~

- Try running `kubectl` commands now:

~~~
$ kubectl get nodes
$ kubectl get svc
~~~

**Challenge** Adding at least another Kubernetes cluster from one of your 
classmates' experiment to your student account. In other words, one account 
can have access to multiple K8S cluster. 


{% details Namespace overview %}


{% enddetails %}
- Similar to Linux's namespaces, Kubernetes' namespaces allow the isolation 
of groups of resources withint a single cluster. 
  - Names of isolated resources within the same namespace need to be unique, 
  but not across namespaces. 
- Scope of namespace isolation is only applicable to namespaced objects like 
`Deployments` and `Services`, but not for cluster-wide objects like `StorageClass`, 
`Nodes`, and `PersistentVolumes`. 
- To check which Kubernetes resources are and aren't in a namespace:

~~~bash
# In a namespace
$ kubectl api-resources --namespaced=true

# Not in a namespace
$ kubectl api-resources --namespaced=false
~~~


{% details RBAC Authorization %}


{% enddetails %}
- Kubernetes uses the `rbac.authorization.k8s.io` API group to drive RBAC-based authorization decisions, 
- By default, Kubernetes clusters are often launched with RBAC:

~~~bash
$ kubectl describe pods kube-apiserver -n kube-system | grep authorization
~~~

- RBAC API: Role, ClusterRole, RoleBinding, ClusterRoleBinding. 
- Role: sets permissions within a particular namespace
  
~~~bash
$ kubectl get role --all-namespaces
$ kubectl describe role system::leader-locking-kube-controller-manager -n kube-system
~~~

- ClusterRole: set permission for non-namespaced resources

~~~bash
$ kubectl get clusterrole --all-namespaces
$ kubectl describe clusterrole cluster-admin
~~~

- RoleBinding binding grants the permissions defined in a role to a user or set of users. 
- ClusterRoleBinding grants that access cluster-wide.

~~~bash
$ kubectl get RoleBinding --all-namespaces
$ kubectl get ClusterRoleBinding

- What `resources` are available and what `verbs` are applicable?

~~~
$ kubectl api-resources --sort-by name -o wide
~~~


{% details RBAC Authorization hands-on %}

{% enddetails %}
- Run the following to deploy jenkins

~~~bash
$ bash /local/repository/jenkins/deploy_jenkins.sh
~~~

- Setup a single build pipeline

{% details A single build pipeline %}


{% enddetails %}
- Create a new repository called `hello_kube` with contents copied from [the instructor's hello repo's hello_kube branch](https://github.com/CSC603-WCU/hello/tree/hello_kube)
- In `Jenkins`, create a `New Item` of type `Pipeline` and name it `hello_kube`, click `OK`.
- Under `Pipeline` select `Pipeline script from SCM`. 
- Once `SCM` appears, select `Git` and provide the `Repository URL` for **your** hello_kube repo. 
- Under `Branch to build`, change `*/master` to `*/main`.
- Make sure that `Script Path`, enter `Jenkinsfile`. 
  - This is the `Jenkinsfile` in the `hello_kube` branch. 
  - Click `Apply`. 
- Click `Save`. 
- Inside the Pipeline `hello_kube`, select `Build Now`. 

:::{image} ../fig/csc603/08-cloud-security/rbac-01.png
:alt: Missing service account
:class: bg-primary mb-1
:height: 800px
:align: center
:::

- Let's create a service account, then rerun `Build Now`. 

~~~bash
$ kubectl create serviceaccount jenkins
~~~

- Has to be in the same namespace

~~~bash
$ kubectl delete serviceaccount jenkins
$ kubectl create namespace jenkins
$ kubectl create serviceaccount jenkins -n jenkins
~~~

- Try `Build Now` again, does it still work?


{% details Kubernetes Ingress %}


{% enddetails %}
- Ingress exposes HTTP and HTTPS routes from outside the cluster to services within the 
cluster. 
- Traffic routing is controlled by rules defined on the Ingress resource.
- Ingress is managed by Ingress Controllers. 
- There are many diffferent Ingress Controllers


{% details Kubernetes ingress hands-on %}


{% enddetails %}
- Deploy `nginx` ingress controller using NodePort

~~~bash
$ kubectl apply -f https://raw.githubusercontent.com/kubernetes/ingress-nginx/controller-v1.4.0/deploy/static/provider/baremetal/deploy.yaml
$ kubectl get svc -n ingress-nginx -o wide
~~~

- Go to the URL gotten from running `hostname -f` and use the port that is mapped to 
port 80 of `ingress-nginx-controller` to view:

:::{image} ../fig/csc603/08-cloud-security/ingress-01.png
:alt: Ingress controller with no back-end services
:class: bg-primary mb-1
:height: 200px
:align: center
:::


- Deploy an apache server and observe its opened ClusterIP port (internal to the cluster)

~~~bash
$ kubectl create deployment demo --image=httpd --port=80
$ kubectl expose deployment demo
$ kubectl get svc
~~~

- Visit the URL gotten from running `hostname -f` and see if you can view the default webpage. 
  - No you can't!
- Now let's redirect things via the ingress controller

~~~bash
kubectl create ingress demo-localhost --class=nginx --rule="$(hostname -f)/*=demo:80"
~~~

- Refresh the URL to the ingress controller above

:::{image} ../fig/csc603/08-cloud-security/ingress-02.png
:alt: Ingress controller with back-end services
:class: bg-primary mb-1
:height: 200px
:align: center
:::

- What about another apps?

~~~bash
kubectl run template-frontend --image=hashicorp/http-echo --labels=app=template,type=frontend -- -listen=:80 -text="Frontend"
kubectl run template-api --image=hashicorp/http-echo --labels=app=template,type=api -- -listen=:80 -text="API"
kubectl expose pod template-api --port=80
kubectl expose pod template-frontend --port=80
kubectl get svc
~~~

- Delete and recreate the demo-localhost rule
  - We need to add an `annotation` to the rule to provide alternative path options to different service end-points. 

~~~bash
kubectl delete ingress demo-localhost
kubectl create ingress demo-localhost --class=nginx   --rule="$(hostname -f)/demo/=demo:80" --rule="$(hostname -f)/api/=template-api:80" --rule="$(hostname -f)/frontend/=template-frontend:80"
kubectl annotate ingress demo-localhost nginx.ingress.kubernetes.io/rewrite-target="/"
~~~

- Refresh the URL to the ingress controller above with different paths: `/demo/`, `/api/`, and `/frontend/`.
- What about security?
- Need to deploy certificate manager

~~~bash
$ bash /local/repository/cert-manager/deploy_cert_manager.sh
~~~

- Check and find the corresponding node port for 443 (`HTTPS`) of the `nginx-controller`

~~~bash
$ kubectl get svc -n ingress-nginx
~~~

- Recreate the `demo-local` ingress with updated TLS rules

~~~bash
kubectl delete ingress demo-localhost
kubectl create ingress demo-localhost --class=nginx   --rule="$(hostname -f)/demo/=demo:80,tls=clemson.cloudlab.us-cert-secret" --rule="$(hostname -f)/api/=template-api:80" --rule="$(hostname -f)/frontend/=template-frontend:80"
kubectl annotate ingress demo-localhost nginx.ingress.kubernetes.io/rewrite-target="/"
~~~

- Confirm that URL to the ingress controller above with different paths: `/api/` and `/frontend/` still work with the `HTTP` 
NodePort, but `/demo/` requires `HTTPS` NodePort

:::{image} ../fig/csc603/08-cloud-security/ingress-03.png
:alt: Ingress controller with secured back-end services
:class: bg-primary mb-1
:height: 200px
:align: center
:::


```



## Container Security

{% details Pod Security Standards %}

{% enddetails %}
- Pod security will influence container security. 
- Three policies:
  - Privileged
  - Baseline
  - Restricted 
- Cummulative and range from highly permissive to highly restrictive


{% details Privileged %}

{% enddetails %}
- Purposely open, entirely unrestricted
- Enable system- and infrastructure-level workloads
  - Implied understanding that these workloads are run as privileged/trusted users. 
- Absence of restrictions and allow-by-default mechanism


{% details Baseline %}


{% enddetails %}
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



{% details Restricted %}

{% enddetails %}
- Enforce Pod hardening best practices at the expense of compatibility
- Target security-critical applications and lower-trust users
- Example policy:
  - Disable privilege escalation
  - Containers must run as non-root
  - Drop **ALL** capabilities and only allow `NET_BIND_SERVICE`. 
```

