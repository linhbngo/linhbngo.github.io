---
layout: lecture
pretty_table: true
collection: csc588
course: CSC 603: Access Control in the Cloud
title: "Kubernetes Application: CI/CD pipeline"
toc:
  - name: Introduction to Jenkins
  - name: Configure Jenkins
  - name: Launch pipelines
---

# Kubernetes Application: CI/CD pipeline

## Introduction to Jenkins

{% details Launching an experiment %}


{% enddetails %}
- Each student should find Dr. Ngo's `csc603ngo` CloudLab profile 
and launch an experiment from the `k8-cdci` branch. 
- Once the experiment is fully deployed, **and all Startup Finished running**:
- SSH into the head node and run the followings

~~~bash
$ cd
$ bash /local/repository/launch_network.sh
$ kubectl get nodes
~~~



{% details Introduction to Jenkins %}


{% enddetails %}
- [Jenkins](https://www.jenkins.io/)
- Open-source automation server that allows continuous integration:
  - Recognized whenever source code is changed and/or updated. 
  - Automatic building and testing of updated codes.  


{% details Deploy Jenkins on Kubernetes %}


{% enddetails %}
- SSH to the headnode of your Kubernetes cluster. 

~~~bash
$ bash /local/repository/launch_jenkins.sh
~~~

- What did we just deploy: [jenkins.yaml](https://github.com/CSC468-WCU/csc468cloud/blob/kubernetes-jenkins/jenkins.yaml).
  - [Kubernetes' deployment template](https://kubernetes.io/docs/concepts/workloads/controllers/deployment/).
  - `spec.replicas`: 1
  - `spec.containers`: `jenkins/jenkins:lts`
  - `spec.containers.ports`: `http-port`:8000 and `jnlp-port`:50000
  - ...
  - A `Service` is an abstraction that defines a logical set of Pods and a 
  policy by which to **access** them. 
  - The set of pods targeted by a service is determined by a `selector`. 
  - It allows the decoupling of the microservices provided by the pods and 
  the actual pods themselves (which could be created and destroyed as needed).
- [The service file for the Jenkins' pod.](https://github.com/CSC468-WCU/csc468cloud/blob/kubernetes-jenkins/jenkins-service.yaml)

~~~
$ kubectl get nodes -o wide
~~~

- Grab one of the values of `INTERNAL-IP`, open a browser 
and go to `INTERNAL-IP:30000`

- To get the `initialAdminPassword`, you can run the following
command on the head node:

~~~bash
$ kubectl exec $(kubectl get pods -n jenkins | grep jenkins | awk '{print $1}') -n jenkins -- cat /var/jenkins_home/secrets/initialAdminPassword
~~~

- `kubectl exec` allows users to run a bash command directly inside the specified pod.  
- `$(kubectl get pods -n jenkins | grep jenkins | awk '{print $1}')` is a sequence of pipe commands:
  - `$(kubectl get pods -n jenkins` get all pods
  - `| grep jenkins ` parses the line containing the jenkins pod names
  - `| awk '{print $1}')` gets the first column, which is the pod ID only. 

- Copy and paste the initial admin password to the Jenkins' page and hit 
`Continue`. 

```

## Configure Jenkins

{% details Installing plugins %}


{% enddetails %}
- Click on `Install selected plugins`

:::{image} ../fig/csc603/07-kubernetes/05.png
:alt: Install selected plugins for Kubernetes
:class: bg-primary mb-1
:height: 500px
:align: center
:::

- You can either try to create the first admin user or Skip and continue
as admin. 

:::{image} ../fig/csc603/07-kubernetes/06.png
:alt: Setup admin user
:class: bg-primary mb-1
:height: 500px
:align: center
:::

- Click `Save and Finish`,

:::{image} ../fig/csc603/07-kubernetes/07.png
:alt: Accept instance configuration 
:class: bg-primary mb-1
:height: 500px
:align: center
:::

- Click `Start using Jenkins`

:::{image} ../fig/csc603/07-kubernetes/08.png
:alt: Start using Jenkins
:class: bg-primary mb-1
:height: 500px
:align: center
:::

- This is the Jenkins Dashboard

:::{image} ../fig/csc603/07-kubernetes/09.png
:alt: Jenkins Dashboard
:class: bg-primary mb-1
:height: 500px
:align: center
:::


{% details Exercise %}


{% enddetails %}
- Explore the Jenkins Dashboard and figure out how to install two additional plugins:
  - Kubernetes
  - SSH Agent

:::{image} ../fig/csc603/07-kubernetes/jenkins-extra-agents.png
:alt: Installing additional Kubernetes and SSH Agent plugins
:class: bg-primary mb-1
:height: 200px
:align: center
:::



{% details Configure Jenkins: SSH credentials %}


{% enddetails %}
- On the CloudLab head node, run `ssh-keygen` (do not enter any password when asked). 
- Run `cat .ssh/id_rsa.pub >> .ssh/authorized_keys`
- Run `cat ~/.ssh/id_rsa` and copy the displayed text, including the starting 
and ending dashes without any extra spaces.  
- On Jenkins Dashboard, go to `Manage Jenkins`/`Manage Credentials`.
  - Click on `Jenkins` under `Stores scoped to Jenkins`, then `Global credentials (unrestricted)`.
  - Click on `Add Credentials`. 
- Fill in the boxes as follows:
  - `Kind`: SSH Username with private name
  - `Scope`: Global (Jenkins, nodes, items, all child items, etc)
  - `ID`: cloudlab
  - `Username`: Enter your CloudLab login username here. 
  - `Private Key`: Check `Enter directly`, click `Add`, then paster the previously
  copied private key to this box. 
  - Click `Create`. 


{% details Configure Jenkins: Single executor %}


{% enddetails %}
- On Jenkins Dashboard, go to `Manage Jenkins`/`Manage Nodes and Clouds`.
  - Click on the gear icon for `Built-In Node` 
- Fill in the boxes as follows:
  - `Number of executors`: 1
  - `Labels`: deploy
  - `Usage`: Only build jobs with label expressions matching this node


{% details Configure Jenkins: Kubernetes %}


{% enddetails %}
- On Jenkins Dashboard, go to `Manage Jenkins`/`Manage Nodes and Clouds`/`Configure Clouds`.
- Select `Kubernetes` from `Add a new cloud` dropbox. 
- Click on `Kubernetes Cloud Details`.
- Fill in the boxes as follows:
  - `Kubernetes Name`: kubernetes
  - `Kubernetes URL`: Information of the `Kubernetes control plane` gotten from 
  running `kubectl cluster-info` on the CloudLab head node.
  - Check `Direction Connection` box.
  - Click `Test Connection` to confirm connection. 



{% details Configure Jenkins: Pod Templates %}


{% enddetails %}
- Continue on the `Configure Clouds` from the previous slide.
- Click `Pod Templates` then `Add Pod Template` then `Pod Template details`
- Fill in the boxes as follows:
  - `Name`: agent-template
  - `Namespace`: jenkins
  - `Usage`: Only build jobs with label expressions matching this node
  - **Do not add container yet**
  - Click on `Add Volume`:
    - Select `Host Path Volume`
    - Enter `/var/run/docker.sock` for both `Host path` and `Mount path`. 
    - *This is to enable the building and pushing of Docker images*. 

{% details Configure Jenkins: Container Templates %}


{% enddetails %}
In the scope of `Pod Template`
- Click `Add Container`
- Fill in the boxes as follows:
  - `Container Template Name`: golang
  - `Docker image`: golang
- Click `Add Container`
- Fill in the boxes as follows:
  - `Container Template Name`: gcc
  - `Docker image`: gcc:latest
- Click `Add Container`
  - `Container Template Name`: docker
  - `Docker image`: docker
- Click `Add Environment Variable` for the `docker` container template
  - Prior to this, go to `hub.docker.com` and login to your Docker Hub account. 
    - Go to Account Settings
    - Go to `Security`. 
    - Click on `New Access Token`. 
    - Enter a short description for this token, allow `Access permission` to 
    be `Read, Write, Delete`, and then click `Generate`. 
    - Store this key some where safe. 
   - First environment variable:
     - `Key`: DOCKER_TOKEN
     - `Value`: the access token copied from before. 
   - Second environment variable:
     - `Key`: DOCKER_REGISTRY
     - `Value`: YOUR_DOCKERHUB_USERNAME/go_server
   - Third environment variable:
     - `Key`: DOCKER_USER
     - `Value`: YOUR_DOCKERHUB_USERNAME
>
- Click `Apply` and then `Save`. 
```


## Launch pipelines

{% details A single build pipeline %}


{% enddetails %}
- Create a new repository called `hello_kube` with contents copied from [the instructor's hello repo's hello_kube branch](https://github.com/CSC468-WCU/hello/tree/hello_kube)

- In `Jenkins`, create a `New Item` of type `Pipeline` and name it `hello_kube`, click `OK`.
- Under `Build Triggers` and check `GitHub hook trigger for GITScm polling`. 
- Under `Pipeline` select `Pipeline script from SCM`. 
- Once `SCM` appears, select `Git` and provide the `Repository URL` for **your** hello_kube repo. 
- Under `Branch to build`, change `*/master` to `*/main`.
- Make sure that `Script Path`, enter `Jenkinsfile`. 
  - This is the `Jenkinsfile` in the `hello_kube` branch. 
  - Click `Apply`. 
- Click `Save`. 



{% details Setup a CI/CD application %}


{% enddetails %}
- Create a branch called `go_app` on your `hello` repository (from the hands-on in the Jenkins' eposide).
- The `go_app` branch should have the same contents as https://github.com/CSC468-WCU/hello/tree/go_app
- Setup the `webhook` for the `go_app` to point to the Jenkins server in the previous slide. 
- The composition of the files in this branch is:
  - `main.go`: The Go file that serves as the web server (the application to be deployed).
  - `main_test.go`: The Go file that serves as the test file (part of the CD process).
  - `Jenkinsfile`: Setup the pipeline for Jenkins to build, test, and push and deploy (if test is passed) the 
  Go app. 
    - Edit the `registry` (line 4) to change to `YOUR_DOCKERHUB_USERNAME/go_server`. 
    - Edit the `registry` (line 5) to change to `YOUR_DOCKERHUB_USERNAME`. 
    - Edit the `registry` (line 73, 74, 75):
      - Change my username `lngo` to your CloudLab username. 
      - **Be careful of capitalization in your CloudLab username. It has to match exactly**.
      - Change the IP address to the correct IP address of your head node.  
  - `Dockerfile`: The Docker image that will package the web server. 
  - `deployment.yml` and `service.yml`: K8 configuration files. 



{% details Setup the CI/CD pipeline %}


{% enddetails %}
- Login to the Jenkins server. 
- Select `New Item`, and create a new `Pipeline`named `go_server`.
- On `Build Triggers` tab, select `GitHub hook trigger for GITScm polling`,
- On `Pipeline` tab, select the followings: 
  - `Definition`: Pipeline script from SCM (*this will open new options*)
  - `SCM`: Git
  - `Branch Specifier`: `go_app` 
- Click `Save`
- Click `Build Now` to activate the first build
- Open a new browser tab and visit the IP address of `head` at port 32000 to see the running server

{% details CI/CD in action %}


{% enddetails %}
- Edit `main.go` in `go_app` to introduce and error.
- Observe that the build failed, but the web server is still running. 
- Change `main.go` and also `main_test.go` so that the build and test can pass. 
- Observe the webserver updated after the build completes successfully. 

```
