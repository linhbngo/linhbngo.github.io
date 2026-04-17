---
layout: lecture
pretty_table: true
collection: csc478
title: "Infrastructure As Code"
toc:
  - name: What is Infrastructure As Code (IaC)?
  - name: Principles of Cloud Age Infrastructure
---

# Infrastructure As Code

{% details info Details %}

This lecture is based partly on `Infrastructure as Code: Dynamic Systems for the Cloud Age` by 
Kief Morris. 

{% enddetails %}
## What is Infrastructure As Code (IaC)?

{% details The Iron Age vs. the Cloud Age %}


{% details note Technology changes in the Cloud Age %}

| Iron Age | Cloud Age |
| -------- | --------- |
| Physical hardware | Virtualized resources |
| Provisioning takes weeks | Provisioning takes minutes |
| Manual processes | Automated processes |

{% enddetails %}
{% details note Ways of working in the Cloud Age %}


|                | Iron Age  | Cloud Age |
| -------------- | --------- | --------- |
| Cost of change | high | low |
| Changes represent | failures (need to be managed/controlled) | learning and improvement |
| Optimization perspective | reduces opportunities to fail | maximize speed of improvement |
| Delivery                 | in batches | small changes |
| Testing                  | at the end | continuously |
| Release cycles           | long       | short |
| Architecture             | monolithic (fewer, larger moving parts) | microservices (more smaller parts) | 
| Configuration            | physical or GUI-driven | Configuration-as-Code | 

{% enddetails %}
{% enddetails %}
{% details Defining IaC %}


{% details Definition %}

"Infrastructure as Code means applying software engineering practices to the design and management 
of infrastructure." — Kief Morris

{% enddetails %}
{% details info Benefits of IaC %}

- Enable rapid delivery of value (`change` to add value)
- Reduce effort and risk of making `changes` to infrastructure.
- Enable users of infrastructure to customize (`change`) based on their need. 
- Improve speed to troubleshoot and resolve failures (that likely come from `changes`)

{% enddetails %}
{% details success Details %}

- Use IaC to optimize for change: the ability to make changes both rapidly and reliably. 
- The IaC Value Proposition
    - Speed → faster provisioning
    - Quality → fewer manual errors
    - Reliability → consistent environments
    - Transparency → code is documentation

{% enddetails %}
{% enddetails %}
{% details Common Objections & Responses %}


{% details Objection 1: We don’t make changes often enough %}

- Are systems built once and done?
- Are changes temporary?
- Is it a good thing to make it hard to change?

**Stability comes from making changes**.

{% enddetails %}
{% details Objection 2: We’ll automate later” %}

- It is true that IaC has a steep curve, but ...
- Automation enables faster delivery even for new things. 
- Automation makes it easier to write automated tests. 
- Automating an existing system is harder. 

{% enddetails %}
{% details Objection 3: We must choose between speed and quality %}

- Organizations can't choose between being good at change or being good at stability. 
- Either good at both or bad at both. 


{% enddetails %}
{% enddetails %}
{% details Four Key Metrics %}

- Based on DORA's Accelerate research (Google). 
- Delivery lead time: time it takes to implement, test, and deliver changes to production system. 
- Deployment Frequency: How often changes are deployed.
- Change Failure Rate: Percentage of changes that lead to impaired service (rollback or emergency patch)
- Mean Time to Recovery (MTTR)

{% enddetails %}
{% details Three Core Practices %}

- Define Everything as Code (scripts/config files/...)
- Continuously Test and Deliver All Work in Progress
- Build Small, Simple Pieces That You Can Change Independently


{% enddetails %}
{% details Key Takeaway %}

IaC transforms infrastructure from a cost center to a creative enabler.

{% enddetails %}
## Principles of Cloud Age Infrastructure

{% details Systems Are Unreliable %}

- Assume your system runs on unreliable hardware
- Design for uninterrupted service when underlying resources change. 
- Snowflake Systems
    - Unique, hand-crafted servers
    - Impossible to reproduce or rebuild: `The server that no one dares reboot`
    - Drift, downtime, untested recovery paths
    - Dependency fragility

{% enddetails %}
{% details Everything is Disposable %}

- Server as Pets vs. Server as Cattle

{% enddetails %}
{% details Minimize Variation %}

- Standardize stacks, avoid drift
- Golden images, module reuse

{% enddetails %}
{% details Ensure Repeatability %}

- Every process (build, deploy, rollback) should be repeatable by automation

{% enddetails %}
{% details How These Principles Interconnect %}

- Each principle supports automation, testability, and recovery
- Anti-Patterns to Watch
    - Manual patches
    - Untracked configuration changes
    - Environment drift

{% enddetails %}
{% details Key Takeaway %}

Infrastructure principles mirror modern software engineering principles — reproducibility, modularity, disposability.

{% enddetails %}
### 3. Hands-on: GitHub Actions Workflow for DockerHub

{% details Repository preparation %}

- Create a GitHub repository with the following file/directory structure

```pgsql
.
├─ app/
│  ├─ package.json
│  └─ server.js
├─ Dockerfile
├─ .dockerignore
└─ .github/workflows/docker-publish.yml

{% details app/server.js %}

```js
const http = require('http');
const port = process.env.PORT || 8080;
const server = http.createServer((req, res) => {
  res.end('Hello from CI-built container!\n');
});
server.listen(port, () => console.log(`Listening on ${port}`));
```

{% enddetails %}
{% details app/package.json %}

```json
{
  "name": "ci-demo",
  "version": "1.0.0",
  "main": "server.js",
  "license": "MIT",
  "scripts": { "start": "node server.js" },
  "dependencies": { }
}
```

{% enddetails %}
{% details Dockerfile %}

```dockerfile
# syntax=docker/dockerfile:1.7
FROM node:20-alpine AS base
WORKDIR /usr/src/app

# Copy only what’s needed first to maximize cache
COPY app/package.json ./

# If you had deps, you'd run: npm ci --only=production
# For this demo with no deps, just proceed
COPY app/ ./

EXPOSE 8080
CMD ["node", "server.js"]
```

{% enddetails %}
{% details .dockerignore %}

```bash
.git
.github
node_modules
*.log
Dockerfile
README.md
```

{% enddetails %}
{% details Sanity check %}

- Clone the repository and run the following inside:

```bash
docker build -t local/ci-demo:dev .
docker run -p 8080:8080 local/ci-demo:dev
curl -s localhost:8080
```

- Check that the output prints `Hello from CI-built container`. 

{% enddetails %}
{% enddetails %}
{% details One-file GitHub Actions Workflow %}


{% details note What it does %}

- Builds on PRs (no push to Hub).
- Pushes to Docker Hub on push to default branch and on Git tags (e.g., v1.2.3).
- Generates smart tags (latest, branch name, git SHA, and release version).
- Uses Buildx cache for speed.
- Optional multi-arch (commented line—enable when desired).

{% enddetails %}
{% details note Initial setup %}

- On your Docker Hub account:
    - Create a Docker Hub Access Token (PAT) (Account Settings → Security).
    - Scope: “Read, Write” for repos (keep minimal).
- In your GitHub repo → Settings → Secrets and variables → Actions → New repository secret:
    - `DOCKERHUB_USERNAME` = your Docker Hub username
    - `DOCKERHUB_TOKEN` = the PAT you created
- In GitHub repo → Settings → Actions → General:
    - Workflow permissions: Read and write (needed for cache).
    - Allow GitHub Actions to create and approve pull requests from workflows: off (not needed).

{% enddetails %}
{% details note Add .github/workflows/docker-publish.yml %}

```yaml
name: Build and Publish Docker Image

on:
  push:
    branches: [ "main" ]        # change if your default branch is different
    tags: [ "v*" ]              # pushes version tags like v1.2.3
  pull_request:
    branches: [ "main" ]

permissions:
  contents: read

jobs:
  docker:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v3

      # Login only when we intend to push (not on PRs)
      - name: Log in to Docker Hub
        if: github.event_name != 'pull_request'
        uses: docker/login-action@v3
        with:
          username: ${{ secrets.DOCKERHUB_USERNAME }}
          password: ${{ secrets.DOCKERHUB_TOKEN }}

      - name: Extract Docker metadata (tags, labels)
        id: meta
        uses: docker/metadata-action@v5
        with:
          images: ${{ secrets.DOCKERHUB_USERNAME }}/ci-demo
          tags: |
            type=ref,event=branch
            type=ref,event=tag
            type=raw,value=latest,enable={{is_default_branch}}
            type=sha
          labels: |
            org.opencontainers.image.title=ci-demo
            org.opencontainers.image.source=${{ github.server_url }}/${{ github.repository }}
            org.opencontainers.image.revision=${{ github.sha }}

      - name: Build (PR) or Build+Push (main/tags)
        uses: docker/build-push-action@v6
        with:
          context: .
          # platforms: linux/amd64,linux/arm64      # ← enable for multi-arch
          push: ${{ github.event_name != 'pull_request' }}
          tags: ${{ steps.meta.outputs.tags }}
          labels: ${{ steps.meta.outputs.labels }}
          cache-from: type=gha
          cache-to: type=gha,mode=max
```

- Push the above yaml file. 
- Open `GitHub` → `Actions tab` → watch the run.
- On success, check Docker Hub: image should appear with latest and main tags.

{% enddetails %}
{% details note Release a version %}

- Create a tag and push

```bash
git tag v1.0.0
git push origin v1.0.0
```


{% enddetails %}
{% enddetails %}
