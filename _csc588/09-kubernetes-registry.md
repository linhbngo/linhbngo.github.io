---
layout: lecture
pretty_table: true
collection: csc588
course: CSC 603: Access Control in the Cloud
title: "Kubernetes: Local Private Registry"
toc:
  - name: Setup local private registry
  - name: Deploy Jenkins
  - name: Launch pipelines
---

# Kubernetes: Local Private Registry

In this setup we use a more enhanced k8s deployment branch that has 
semi-automated Jenkins deployments, and also a local private 
registry. 


{% details Launching an experiment %}



{% enddetails %}
- Each student should find Dr. Ngo's `csc603ngo` CloudLab profile 
and launch an experiment from the `k8s-helm` branch. 
- Once the experiment is fully deployed, **and all Startup Finished running**:

```

## Setup local private registry


{% details Setup certifications %}



{% enddetails %}
- After the experiment is fully deployed, SSH into the head node and 
run the following:

~~~bash
$ bash /local/repository/registry/setup_registry.sh
$ cp /local/repository/registry/docker-compose.yml .
$ docker-compose up -d
$ docker container ps
~~~


{% details Setup and test certificates from nodes %}



{% enddetails %}
- SSH to **each node** of the experiment and run the followings

~~~bash
$ sudo cp -R /opt/keys/certs.d /etc/docker/
~~~

- Get the IP address from the head node using the following command

~~~bash
$ ip addr | grep eth0$ | awk -F ' ' '{print $2}' | awk -F '/' '{print $1'}
~~~

- On each node, test that the certificates are working by login 
to the local docker registry using the following command
  - You should see a "Login Suceeded" message. 

~~~bash
$ docker login -u admin -p registry https://IP_ADDRESS_FROM_ABOVE:443
~~~


{% details Setup Docker access for k8s %}



{% enddetails %}
- On the head node, run the following
  - **Assume that you already run docker login to the private local registry on head node**
  - If your app is deployed inside a namespace, the `regcred` generic secret 
  creation command needs to be specified with that specific namespace as well. 

~~~bash
$ ip_addr=$(ip addr | grep eth0$ | awk -F ' ' '{print $2}' | awk -F '/' '{print $1'})
$ kubectl create secret generic registry-ca --namespace kube-system --from-file=registry-ca=/opt/keys/certs.d/${ip_addr}\:443/ca.crt
$ kubectl create -f registry-ca-ds.yaml
$ kubectl create secret generic regcred --from-file=.dockerconfigjson=/users/${USER}/.docker/config.json --type=kubernetes.io/dockerconfigjson
~~~

```


## Deploy Jenkins

{% details Deploy Jenkins on Kubernetes %}



{% enddetails %}
- SSH to the headnode of your Kubernetes cluster. 

~~~bash
$ bash /local/repository/jenkins/deploy_jenkins.sh
$ bash /local/repository/jenkins/enable_sa.sh
~~~

- Run the following commands to get the URL for login to Jenkins

~~~bash
$ export NODE_PORT=$(kubectl get --namespace default -o jsonpath="{.spec.ports[0].nodePort}" services jenkins-1669147387)
$ export NODE_IP=$(kubectl get nodes --namespace default -o jsonpath="{.items[0].status.addresses[0].address}")
$ echo http://$NODE_IP:$NODE_PORT/login
~~~

- The login and password are: `pokemon`/`pikachu`.


{% details Configure Jenkins: SSH credentials %}



{% enddetails %}
- On the CloudLab head node, run `ssh-keygen` (do not enter any password when asked). 
- Run `cat ~/.ssh/id_rsa.pub >> .ssh/authorized_keys`
- Run `cat ~/.ssh/id_rsa` and copy the displayed text, including the starting 
and ending dashes without any extra spaces.  
- On Jenkins Dashboard, go to `Manage Jenkins`/`Manage Credentials`.
  - Click on domains `(global`) under `Stores scoped to Jenkins`.
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

```

## Launch pipelines

{% details Setup a CI/CD application %}



{% enddetails %}
- Fork the [`hello` repository](https://github.com/CSC603-WCU/hello) to your Git account
- Setup the API Token for `pikachu`:
  - On Jenkins main page, Go to `People`, then select `pokemon`, then go to `Configure`.
  - Scroll to `API Token`, `Add new Token` and generate one. You can name it `github`. 
  - Copy and store this token for today's class (`JENKINS_TOKEN`). 
- Setup the `webhook` for your repository. 
  - Go to your Git repository's `Settings`, and scroll to `Webhooks` 
  - Add a new webhook with the following configurations:
    - The Payload URL is of the following format: `http://pokemon:JENKINS_TOKEN@IP_ADDRESS:30000/github-webhook/` 
    - The Content type is `application/x-www-form-urlencoded`
- The composition of the files in the `go_app` branch includes:
  - `main.go`: The Go file that serves as the web server (the application to be deployed).
  - `main_test.go`: The Go file that serves as the test file (part of the CD process).
  - `Jenkinsfile`: Setup the pipeline for Jenkins to build, test, and push and deploy (if test is passed) the Go app. 
    - Edit the `registry` (line 6) to be the IP address of the `head` node. 
    - Change the `userid` value from `lngo` to your CloudLab username. 
    - **Be careful of capitalization in your CloudLab username. It has to match exactly**.
  - `Dockerfile`: The Docker image that will package the web server. 
  - `deployment.yml` and `service.yml`: K8 configuration files. 


{% details Setup the CI/CD pipeline %}



{% enddetails %}
- Login to the Jenkins server. 
- Select `New Item`, and create a new `Pipeline`named `go_server`.
- Scroll down to `Build Triggers`, select `GitHub hook trigger for GITScm polling`,
- Scroll down to `Pipeline`, select the followings: 
  - `Definition`: Pipeline script from SCM (*this will open new options*)
  - `Repository URL`: URL of the `hello` repository
  - `SCM`: Git
  - `Branches to build`: `go_app` 
- Click `Save`
- Click `Build Now` to activate the first build
- Open a new browser tab and visit the IP address of `head` at port 32000 to see the running server

{% details CI/CD in action %}



{% enddetails %}
- Edit `main.go` in `go_app` to introduce an error.
- Observe that the build failed, but the web server is still running. 
- Change `main.go` and also `main_test.go` so that the build and test can pass. 
- Observe the webserver updated after the build completes successfully. 

```
