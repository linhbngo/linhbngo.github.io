---
layout: lecture
pretty_table: true
collection: csc478
title: "Configuration as Code (CaC): Helms"
toc:
  - name: Configuration as Code in the Cloud Stack
  - name: Helm Fundamentals
  - name: Nginx Chart Components
  - name: Hands-on
---
# Configuration as Code (CaC): Helms

## Configuration as Code in the Cloud Stack

- IaC: clusters, networks, VMs (Terraform, Crossplan)
- CaC: runtime app/platform configuration (Helm, Kustomize, YAML overlays)
- Why CaC:
    - Reproducibility
    - Reviewability
    - "Diff-able" ops
    - Promotion across environments

---

## Helm Fundamentals

{% details What Helm does? %}

- packaging (charts), 
- templating (Go templates), 
- release management (history/rollback)

{% enddetails %}
{% details Helm as a Packaging System %}

- Helm packages Kubernetes manifests into reusable bundles called `charts`. 
- Charts contains
    - Metadata
    - Templates
    - Default Configurations


{% enddetails %}
{% details Key objects of a Chart %}

- Chart.yaml
- templates/
- values.yaml
- values.schema.json

{% enddetails %}
{% details Release lifecycle %}

- Install 
- Upgrade --reuse-values 
- Rollback 
- Uninstall

{% enddetails %}
---

## Nginx Chart Components
    
Chart: [Bitnami Secure Images Helm chart for NGINX Open Source](https://github.com/bitnami/charts/tree/main/bitnami/nginx)

{% details Chart.yaml %}


The Helm manifest defining the chart (identity, version, dependencies, and metadata)

{% details note annotations %}


```yaml
annotations:
  images: |
    - name: git
      image: docker.io/bitnami/git:2.51.0-debian-12-r0
    - name: nginx
      image: docker.io/bitnami/nginx:1.29.1-debian-12-r0
    - name: nginx-exporter
      image: docker.io/bitnami/nginx-exporter:1.4.2-debian-12-r9
  licenses: Apache-2.0
  tanzuCategory: clusterUtility
```

- `images`: a list of container images used by this chart
- `licenses`: declares the chart’s open-source license.
- `tanzuCategory`: a VMware Tanzu-specific tag grouping the chart (here: cluster utilities).

{% enddetails %}
{% details note apiVersion %}


```yaml
apiVersion: v2
```

- Helm chart API version (v2 for Helm 3+)

{% enddetails %}
{% details note appVersion %}


```yaml
appVersion: 1.29.1
```

- Version of the application (in this case NGINX) being deployed. 

{% enddetails %}
{% details note dependencies %}


```yaml
dependencies:
- name: common
  repository: oci://registry-1.docker.io/bitnamicharts
  tags:
  - bitnami-common
  version: 2.x.x
```

- This means the NGINX chart depends on another chart called [common](https://github.com/bitnami/charts/tree/main/bitnami/common) from Bitnami. 
- This is not an application, but it is a library chart, which defines a collection of 
reusable template helpers, functions, and YAML snippets. 
- This is for Bitnami only, and is not applicable for charts created by others. 

{% enddetails %}
- Other items in `Chart.yaml`, `description`, `home`, `icon`, `keywords` are more 
for descriptive/categorical purposes. 


{% enddetails %}
{% details templates/ %}

- Helm templates are the **parameterized YAML manifests** that define Kubernetes objects (like Deployments, Services, ConfigMaps, etc.) for your application.
- They live under the templates/ directory inside a Helm chart and use Go’s templating language (`{{ ... }}`) to inject dynamic values.

{% details Rendering final manifests from templates %}


```bash
helm template my-nginx oci://registry-1.docker.io/bitnamicharts/nginx
```

{% enddetails %}
- The structure inside the `templates` directory depends on how the application needs to 
be deployed. 
- [Structure for Bitname's NGINX templates](https://github.com/bitnami/charts/tree/main/bitnami/nginx/templates)

{% details Portion of templates/deployment.yaml %}


```yaml
{{- /*
Copyright Broadcom, Inc. All Rights Reserved.
SPDX-License-Identifier: APACHE-2.0
*/}}

apiVersion: {{ include "common.capabilities.deployment.apiVersion" . }}
kind: Deployment
metadata:
  name: {{ include "common.names.fullname" . }}
  namespace: {{ include "common.names.namespace" . | quote }}
  labels: {{- include "common.labels.standard" ( dict "customLabels" .Values.commonLabels "context" $ ) | nindent 4 }}
  {{- if .Values.commonAnnotations }}
  annotations: {{- include "common.tplvalues.render" ( dict "value" .Values.commonAnnotations "context" $ ) | nindent 4 }}
  {{- end }}
```

- `labels:`: Standard YAML key, indicating that the following lines will define `labels`.
- `{{- ... }}`: Go template syntax for an action or function call. 
    - `-`: tells the template engine to remove any extra white space (like blank lines or spaces) immediately before or after this command to keep the final output clean.
    - `include "common.labels.standard"`: fetches pre-defined text from another part 
    (a "partial template") of the Helm chart named "common.labels.standard". This is a way to reuse the same set of labels across many different files. 
        - This is how Bitnami's `common` chart is used. 
    - `( dict "customLabels" .Values.commonLabels "context" $ )`: Creates a new, specific package of data (a dictionary or map) for that template to use. This package contains two items:
        - `"customLabels" .Values.commonLabels`: Creates a field named "customLabels" and fills it with 
        values found in the main configuration under `.Values.commonLabels` (See `values.yaml`). 
        - `"context" $`: Creates a field named "context" and assigns it the value of `$`. In Helm, the dollar sign ($) is a special variable that always refers to the main, top-level set of all data in the chart (the "root context"). This ensures the included template can still access global information like the Chart name or Release name, even though we are primarily passing it a limited dictionary.
    - `| nindent 4`: Is a "pipe" command that takes the output of the include function and applies 
    an operation to it. 
        - The `nindent 4` function adds a new line before the included text and indents every single line of that text by 4 spaces. 
        - This is crucial for making sure the output is valid YAML, as indentation matters in YAML

{% enddetails %}
{% enddetails %}
{% details values.yaml %}

- Configuration file that provides default values for the chart's templates. 
- Help customizting how the application should be deployed. 
- Steps:
    - Create a custom yaml file,
    - Specify this file when launching Helm using `--values` flag. 

{% enddetails %}
{% details values.schema.json %}

- Optional
- Containing schematic of `values.yaml`. 
- Ensuring the custom yaml file match the keys in `values.yaml` prior to deployment. 

{% enddetails %}
---

## Hands-on

{% details info Details %}

Helm is already installed in CloudLab's class profile. The installation script is 
located in `install_helm.sh`. This script needs to be run as `root`. 

{% enddetails %}
{% details Check Helm version %}


```bash
helm version
```

{% enddetails %}
{% details Deploy Nginx from Helm as-is %}


- Update repo

```bash
helm repo add bitnami https://charts.bitnami.com/bitnami
helm repo update
```

- Create a namespace

```bash
kubectl create namespace web
```

- Preview the chart template (no installation yet)
    - Examine manifests for deployment and service

```bash
mkdir my-nginx
cd my-nginx
helm template my-nginx bitnami/nginx -n web > nginx-template.yaml
cat nginx-template.yaml
```

- Install chart

```bash
helm install my-nginx bitnami/nginx -n web
```

- Check chart status

```bash
helm status my-nginx -n web
```

- Read the status message and find out how to test the my-nginx server from a browser. 
- Check Kubernetes Services and Pods

```bash
kubectl get pods -n web
kubectl get svc -n web
```

- Uninstall Helm chart

```bash
helm uninstall my-nginx -n web
```

{% enddetails %}
{% details Deploy customed Nginx from Helm %}


- Inside `my-nginx` directory, create a file called `my-values.yaml` with 
the following content

```bash
image:
  registry: docker.io
  repository: nginx
  tag: "1.25.5"
  pullPolicy: IfNotPresent

containerPorts:
  http: 80

service:
  type: NodePort
  ports:
    http: 8080        # Service port inside cluster (arbitrary)
  nodePorts:
    http: 32080       # External NodePort (within default range)

containerSecurityContext:
  enabled: true
  runAsNonRoot: false
  runAsUser: 0
```

- Regenerate template file

```bash
helm template my-nginx bitnami/nginx -n web -f my-values.yaml > nginx-rendered.yaml
```

- Compare the differences between the two templates

```bash
diff nginx-template.yaml nginx-rendered.yaml
```

- Install the new nginx with the customized environment

```bash
helm install my-nginx bitnami/nginx -n web -f my-values.yaml
```

- Confirm that the new nginx is accessible via a custom predefined port 32080

```bash
kubectl get svc my-nginx -n web
```
{% enddetails %}
