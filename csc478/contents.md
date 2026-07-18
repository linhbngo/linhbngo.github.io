# CSC 478 Course Improvement Suggestions

This file captures suggestions for improving the quality, hands-on depth,
and currency of the Cloud Engineering course. No existing lecture files are
modified here — all changes are proposals only.

---

## 1. Structural / Scheduling Gaps

### 1.1 Schedule is incomplete
The syllabus (`00-syllabus.md`) lists only 10 weeks. A Fall semester runs
roughly 15 weeks. At minimum, five weeks of planned content are missing.
Suggested additions to fill the gap:

| Week | Proposed Topic |
|------|---------------|
| 11   | Helm — Kubernetes package management |
| 12   | CI/CD with GitHub Actions + Kubernetes |
| 13   | Observability: Prometheus + Grafana |
| 14   | GitOps with ArgoCD |
| 15   | Review, project presentations buffer |

### 1.2 Mismatched lecture (16-programmatic-deployment.md)
This lecture covers OpenStack GUI operations (image upload, volume attach,
Alpine Linux install) that were carried over from CSC 468. It does not
connect to the Kubernetes theme of CSC 478. Two options:

- **Replace** it with an Infrastructure-as-Code lecture using Terraform or
  Pulumi to provision cloud resources that back a Kubernetes cluster.
- **Repurpose** it as a week-1 refresh ("where we came from") and clearly
  frame it as contrast material, not new content.

### 1.3 FABRIC reference is never followed up
Week 1 of the schedule says "Introduction to FABRIC" but no FABRIC lecture
file exists. Either add a FABRIC lecture or replace the schedule entry with
CloudLab (which is already used throughout the course).

---

## 2. Missing Hands-on Activities

### 2.1 Kubernetes RBAC lab (supplement to 13-core-rbac.md)
The RBAC lecture covers academic taxonomy (Core, Hierarchical, SoD) but
contains no Kubernetes-specific RBAC hands-on. Students leave without
knowing how to create a Role, RoleBinding, or ServiceAccount in Kubernetes.

**Suggested lab steps:**
1. Create a namespace `team-dev`.
2. Create a `ServiceAccount` called `dev-user`.
3. Create a `Role` that allows `get`, `list`, `watch` on Pods and Services
   inside `team-dev`.
4. Bind the role with a `RoleBinding`.
5. Use `kubectl auth can-i` to verify what `dev-user` can and cannot do.
6. Attempt a forbidden action (e.g., `delete pod`) and observe the error.
7. Extend to a `ClusterRole` and discuss when to use each.

### 2.2 Network Policy hands-on (supplement to 14-cloud-security.md)
The security lecture discusses concepts but has no NetworkPolicy exercise.
Students should be able to restrict pod-to-pod traffic.

**Suggested lab steps:**
1. Deploy a frontend and a backend Deployment in namespace `netpol-demo`.
2. Confirm frontend can reach backend with `curl`.
3. Apply a `NetworkPolicy` that denies all ingress to the backend.
4. Confirm the curl now fails.
5. Apply a second policy that allows ingress only from pods labeled
   `app: frontend`.
6. Confirm the frontend can reach backend again but a third pod cannot.

### 2.3 Ingress controller lab (supplement to 14-cloud-security.md or standalone)
Ingress is mentioned but never hands-on. Students only see NodePort.

**Suggested lab steps (using NGINX Ingress Controller on CloudLab):**
1. Install the NGINX Ingress Controller via `kubectl apply -f` (official manifest).
2. Deploy two services: `app-a` (nginx showing "App A") and `app-b`.
3. Write an `Ingress` resource that routes `/a` to `app-a` and `/b` to `app-b`.
4. Test routing with `curl -H "Host: demo.local" http://<node-ip>/a`.
5. Discuss how this maps to AWS ALB / GCP HTTP(S) LB concepts already in
   `10-load-balancer.md`.

### 2.4 Horizontal Pod Autoscaler (HPA) lab
Scaling is discussed in the project spec but never taught hands-on.

**Suggested lab steps:**
1. Deploy a PHP/Apache stress image with resource requests set.
2. Install `metrics-server` (already referenced by `kubectl top` in lecture 09).
3. Create an HPA targeting 50% CPU utilization, min 1 replica, max 5.
4. Run a load generator (`kubectl run -it load-gen --image=busybox ...`) to
   trigger scaling.
5. Watch `kubectl get hpa -w` and `kubectl get pods -w` to see pods appear.
6. Stop the load and watch pods scale back down.

### 2.5 ConfigMaps and Secrets lab (missing topic)
Neither ConfigMaps nor Secrets appear anywhere in the course. These are
day-one production concepts.

**Suggested lab steps:**
1. Create a `ConfigMap` from a file and from literal values.
2. Mount the ConfigMap as environment variables and as a volume.
3. Create a `Secret` (base64-encoded), mount it into a pod.
4. Discuss never storing Secrets in Git; introduce `sealed-secrets` or
   `external-secrets` as a follow-up pointer.

---

## 3. Up-to-Date Content Additions

### 3.1 Helm (new lecture — Week 11)
Helm v3 is the industry standard for packaging Kubernetes applications.
Every real-world K8s deployment uses it. The project milestone deliverables
would benefit from a Helm chart instead of raw YAML folders.

**Suggested content:**
- Why Helm: template reuse, versioning, release management.
- Helm concepts: Chart, Release, Values, Templates.
- Hands-on: `helm install`, `helm upgrade`, `helm rollback`.
- Convert the Quote-of-the-Day app from lecture 06 into a Helm chart.
- Introduce ArtifactHub.io as the public chart registry.

### 3.2 CI/CD with GitHub Actions + Kubernetes (new lecture — Week 12)
The course teaches students to deploy manually with `kubectl apply`. Modern
cloud engineering is driven by automated pipelines.

**Suggested content:**
- Push a code change → GitHub Actions builds Docker image → pushes to
  registry → updates the Kubernetes deployment via `kubectl` or Helm.
- Use `kustomize` overlays for dev vs. prod configuration differences.
- Introduce image tagging strategy (SHA-pinning vs. `latest`).
- Connect back to the course project: students' project pipelines should
  not require manual `kubectl apply` steps.

### 3.3 Observability: Prometheus + Grafana (new lecture — Week 13)
`kubectl top` is used in resource management lecture but never explained.
Real-world cloud engineers must be able to monitor their clusters.

**Suggested content:**
- Install the `kube-prometheus-stack` Helm chart on CloudLab.
- Explore pre-built Grafana dashboards for cluster health.
- Write a simple PromQL query for pod CPU usage.
- Set up one alert rule (e.g., pod restart count > 5).
- Connect liveness/readiness probes (already in lecture 10) to Prometheus
  scraping.

### 3.4 GitOps with ArgoCD (new lecture — Week 14)
GitOps is now the dominant operational model in cloud-native shops.

**Suggested content:**
- GitOps principle: Git is the single source of truth for cluster state.
- Install ArgoCD on CloudLab cluster.
- Connect ArgoCD to a student GitHub repo.
- Demonstrate: push a YAML change to GitHub → ArgoCD detects drift →
  syncs the cluster automatically.
- Relate to CI/CD lecture: CI builds and tests; CD (GitOps) deploys.

### 3.5 Gateway API (update to 10-load-balancer.md and Ingress content)
Kubernetes Gateway API is now GA (v1.0 reached GA in October 2023, v1.2 in
October 2024) and is the official successor to Ingress. The current lecture
only covers NodePort and theoretical LoadBalancer. Add a section explaining:
- Why Gateway API replaces Ingress.
- `GatewayClass`, `Gateway`, and `HTTPRoute` resources.
- A comparison table: Ingress vs. Gateway API.

### 3.6 Supply chain security basics (supplement to 14-cloud-security.md)
The current security lecture covers pod security standards and RBAC but
misses the supply chain — one of the top real-world concerns in 2024-2026.

**Suggested content (conceptual + short demo):**
- What is an SBOM (Software Bill of Materials) and why it matters.
- Image signing with `cosign` (Sigstore project, CNCF graduated).
- `kubectl` admission webhooks that reject unsigned images (concept only).
- Reference: SLSA framework levels.

### 3.7 StatefulSets (missing topic)
Volumes and PVCs are taught, but StatefulSets — the workload type that uses
them in production databases — are never introduced. The project spec
mentions them as an option but students have no lecture material.

**Suggested lab steps:**
1. Deploy a 3-replica MongoDB StatefulSet with a `volumeClaimTemplate`.
2. Observe stable network identities (`mongo-0`, `mongo-1`, `mongo-2`).
3. Delete `mongo-1` and watch it re-create with the same name and PVC.
4. Compare behavior to a regular Deployment pod deletion.

---

## 4. Improvements to Existing Lectures

### 4.1 01-introduction.md
- The Borg paper (2015) and 2020 analysis are well-cited. Add a pointer
  to the Kubernetes 2023 steering committee annual report or CNCF survey
  to show how K8s has grown since.
- Add a brief section on Kubernetes release cadence (3 releases/year) and
  how to check `kubectl version` for client/server skew.

### 4.2 02-rancher.md
- Rancher Desktop 1.x is the current version. Add version confirmation
  step (`rdctl version`) so students know what to expect.
- The hands-on sends students back to CSC 468 Docker lecture. Convert this
  into a self-contained `nerdctl` exercise (build → push → run) so CSC 478
  is standalone.

### 4.3 03-pod-service-deployment.md
- Step 2 YAML (nginx-deployment.yaml) has incorrect indentation — the
  `spec` and sub-fields are not properly indented under their parent keys.
  This will fail `kubectl apply` as written. Verify and fix the YAML
  before students use it.
- Add a `kubectl rollout` exercise: update the nginx image to a specific
  version and perform a rollback with `kubectl rollout undo`.

### 4.4 09-resource-management.md
- The YAML code block for `Resource Requests and Limits` is missing the
  closing triple-backtick, so the fence is not closed properly. This will
  render incorrectly on the site.
- Add a `kubectl top nodes` step alongside `kubectl top pods` so students
  see node-level resource usage.
- Mention Vertical Pod Autoscaler (VPA) as a contrast to manual
  requests/limits.

### 4.5 13-core-rbac.md
- This lecture currently teaches academic RBAC theory (from what appears
  to be a graduate security course, referencing `csc603` image paths).
  For an undergraduate cloud engineering course the theory is disproportionate.
- Recommend trimming the academic taxonomy to 20% of the lecture and
  expanding the Kubernetes RBAC hands-on (see Section 2.1 above) to 80%.
- The image paths reference `csc478/csc603/09-core-rbac/` which suggests
  these slides were imported from a different course. Verify the images
  exist and display correctly.

### 4.6 16-programmatic-deployment.md
- See Section 1.2 above. The OpenStack content does not align with the
  Kubernetes curriculum. Reframe or replace.
- If kept as historical context, add a paragraph explicitly connecting it
  to Kubernetes: "OpenStack is what many CloudLab profiles use under the
  hood; Kubernetes clusters run on top of VMs like the one you just
  provisioned."

---

## 5. Project Improvements (04-project.md)

### 5.1 Require Helm charts in Milestone 2+
Currently students submit raw YAML files. Requiring a Helm chart by
Milestone 2 ties the project to industry practice and pairs with the
proposed Helm lecture.

### 5.2 Add an observability deliverable to Milestone 3
Milestone 3 asks for health/readiness probes but no monitoring. Add:
- A Prometheus `ServiceMonitor` or annotation to expose custom metrics.
- A Grafana dashboard screenshot showing at least one application-level
  metric.

### 5.3 Add a security deliverable
Require at least one `NetworkPolicy` that limits inter-pod traffic, and
at least one `Role`/`RoleBinding` scoped to the project namespace.

### 5.4 Require a `kustomize` overlay or Helm values file for multi-env
Ask students to demonstrate deploying to two namespaces (e.g., `dev` and
`prod`) using different replica counts or resource limits via
`kustomize overlays` or Helm `--values`.

---

## 6. Tooling Suggestions

| Tool | Why | Lecture tie-in |
|------|-----|---------------|
| `k9s` | Terminal UI for Kubernetes — dramatically speeds up cluster inspection | All hands-on labs |
| `stern` | Multi-pod log tailing | Debugging sessions in every lab |
| `kubectx` / `kubens` | Fast context/namespace switching | CloudLab multi-cluster work |
| `helm` v3 | Package management | Proposed Week 11 lecture |
| `kustomize` | Built into `kubectl` — overlay-based config management | CI/CD lecture |
| `cosign` | Image signing (Sigstore) | Security lecture |
| `argocd` CLI | GitOps workflow | Proposed Week 14 lecture |

All of these are free, open-source, and run on the CloudLab environment.

---

## 7. Assessment Improvements

### 7.1 Add a "deploy and verify" assignment per major topic
Currently assignments are described loosely ("carrying out manual steps").
For each major lecture block, add one graded assignment with a concrete
deliverable:

| Week | Assignment deliverable |
|------|----------------------|
| 2    | Submit `nginx-deployment.yaml` and a screenshot of `kubectl get pods -o wide` |
| 4    | Submit Quote-of-the-Day manifests + screenshot of `curl` output |
| 5    | Submit NFS PV/PVC manifests + screenshot showing data persists after pod delete |
| 7    | Submit Namespace + ResourceQuota + proof of pod rejection |
| 8    | Submit NodePort manifest + screenshot showing node-local failure behavior |
| 11   | Submit a working Helm chart for the multi-service app |
| 13   | Submit Prometheus query output + Grafana screenshot |

### 7.2 Replace or supplement written exams with a practical component
A 20-minute "cluster debugging" practical (broken YAML, mis-labeled
selectors, wrong port mappings) better assesses cloud engineering skills
than written questions about theory.
