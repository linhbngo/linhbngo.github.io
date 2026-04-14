---
layout: lecture
pretty_table: true
order: 1
title: Container Security
mermaid:
  enabled: true
  zoomable: true
code_diff: true
map: true
chart:
  chartjs: true
  echarts: true
  vega_lite: true
tikzjax: true
typograms: true
last_updated: 2026-04-14

toc:
  - name: Security Foundations from Previous Lectures
  - name: Threat Model and Security Layers
  - name: Build and Supply-Chain Security
  - name: Runtime, Storage, Network, and Secrets
  - name: Swarm / Compose Security
  - name: Hands-on Hardening
  - name: Best Practices Summary
---

## Security Foundations

{% details Recap: what Docker is really securing %}

- Security through isolation mechanisms
  - **Namespaces** decide what a process can **see**.
  - **Cgroups** decide what a process can **consume**.
  - **Chroot / pivot_root / mount isolation** decide what filesystem tree a process can **reach**.
- A secure container deployment also needs:
  - safe image construction,
  - safe runtime configuration,
  - safe networking,
  - safe storage choices,
  - safe secret handling,
  - and a patched host kernel.

{% enddetails %}

{% details A useful mental model %}

- Container security is best understood in layers:
  1. **Host security**
  2. **Image / supply-chain security**
  3. **Runtime hardening**
  4. **Network and storage controls**
  5. **Orchestration and secret management**
- If the host is weak, containers inherit that weakness.
- If the image is weak, runtime hardening is limited by the inherent weakness.

{% enddetails %}

## Threat Model and Security Layers

{% details Containers versus virtual machines %}

- Virtual machines package:
  - a guest kernel,
  - guest user space,
  - and hardware virtualization through a hypervisor.
- Containers package:
  - application code and user space,
  - but they **share the host kernel**.
- Consequence:
  - containers are lighter and faster,
  - but kernel compromise is more dangerous because the host kernel is shared.

{% enddetails %}

{% details Linux primitives that support container security %}

- **Namespaces**
  - isolate process trees, mount tables, hostnames, IPC, networks, and user IDs.
- **cgroups**
  - limit CPU, memory, and I/O to reduce denial-of-service impact.
- **seccomp**
  - filters system calls and reduces kernel attack surface.
- **AppArmor / SELinux**
  - apply mandatory access-control policies beyond ordinary UNIX permissions.
- **Capabilities**
  - split root privilege into smaller units so that containers can run with fewer privileges.

{% enddetails %}

{% details The big misconception: isolation is not immunity %}

- A container can be isolated and still be insecure.
- Common reasons:
  - the process runs as root,
  - the container is privileged,
  - broad Linux capabilities are left enabled,
  - dangerous host paths are bind-mounted,
  - unnecessary ports are published,
  - secrets are baked into the image,
  - the host or runtime is out of date.

{% enddetails %}

{% details Rootless mode vs. container non-root users %}

- Rootless Docker (**recommended**) 
  - The Docker daemon and its containers run as a `non-root` user on the host.
- Default Docker
  - The daemon usually runs as `root`, even if the app inside the container does not.
- User namespace remapping: 
  Lets a container appear to run as root internally while mapping that root user to an 
  unprivileged UID on the host.
- `USER` in Dockerfile 
  - Controls which user the containerized application runs as.

{% enddetails %}

{% details Hands-on: verify Rootless Docker %}

- Documentation:
  - [Docker Rootless mode](https://docs.docker.com/engine/security/rootless/)
  - [Docker post-install: non-root docker group](https://docs.docker.com/engine/install/linux-postinstall/)

- Install prerequisites on Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install -y uidmap docker-ce-rootless-extras
grep "^$USER:" /etc/subuid
grep "^$USER:" /etc/subgid
```

- Make sure that Docker is not running

```bash
sudo systemctl disable --now docker.service docker.socket
sudo rm -f /var/run/docker.sock
```

- Install rootless Docker for the current user:

```bash
dockerd-rootless-setuptool.sh install
systemctl --user start docker
sudo loginctl enable-linger $USER
export DOCKER_HOST=unix:///run/user/$(id -u)/docker.sock
```

- Verify that Docker is running in rootless mode:

```
docker info
docker context ls
docker run --rm hello-world
```

- Observations:
  - `docker info` should show security options including rootless
  - the active Docker context is often rootless
  - the socket should be under /run/user/<uid>/docker.sock

{% enddetails %}

## Build and Supply-Chain Security

{% details Minimal base images and multistage builds %}

- Preference
  - minimal base images,
  - only the runtime dependencies you actually need,
  - **multi-stage builds** so compilers, package managers, and test tools do not appear in the final image.
- Smaller images usually reduce:
  - package count,
  - attack surface,
  - patching burden,
  - and scan noise.

{% enddetails %}

{% details Pin what you build from %}

- Tags are mutable.
  - `latest` is especially slippery.
- For reproducibility and supply-chain control:
  - pin important base images to versioned tags,
  - and for stronger guarantees, pin by **digest**.
- This matters even more in multi-node systems, where different replicas must not silently drift to different image contents.

{% enddetails %}

{% details Do not leak secrets into the build %}

- Avoid putting secrets into:
  - `COPY`ed files,
  - `ENV`,
  - or `ARG`.
- Build arguments are not a safe secret mechanism.
- Use **BuildKit secret mounts** during builds instead.
- Remember:
  - if a secret enters an image layer, students can often recover it later with image history, layer inspection, or accidental push to a registry.

{% enddetails %}

{% details Use .dockerignore aggressively %}

- Everything in the build context is a candidate for accidental disclosure.
- A careless build context can send:
  - `.git`,
  - test fixtures,
  - SSH keys,
  - local `.env` files,
  - notebook outputs,
  - and grading artifacts
  to the builder.
- Use `.dockerignore` the same way you use `__pycache__` cleanup in a tidy repo:
  - not glamorous,
  - but it prevents dumb leaks.

{% enddetails %}

{% details Scan images and attach metadata %}

- Image scanning should be part of CI, not a special ritual performed only after something catches fire.
- Modern best practice is to produce and store:
  - **SBOMs** (Software Bills of Materials),
  - and **provenance attestations**.
- These support:
  - vulnerability scanning,
  - software inventory,
  - reproducibility,
  - and policy enforcement.
- In other words: not just “Is this image bad?” but also “What exactly is inside it, and where did it come from?”

{% enddetails %}

{% details Image trust %}

- Older Docker guidance often recommended [Docker Content Trust (DCT)](https://docs.docker.com/engine/security/trust/)
  - let publishers sign image **tags**,
  - le clients with `DOCKER_CONTENT_TRUST=1` to only pull/run/build with signed tagged images. 
  - This is being retired. 
- DCT was mainly about **“is this tag signed?”**
- Modern container trust asks a broader set of questions:
  - **Who signed this image?**
  - **What claims are attached to it?**
  - **How was it built, and from what source?**
- A better modern vocabulary is:

  - **Signature**
    - proves that a trusted identity signed a specific artifact.
    - Example tools: **Sigstore Cosign** and **Notation**. :contentReference[oaicite:2]{index=2}

  - **Attestation**
    - signed metadata attached to an image, such as an **SBOM**, vulnerability/exemption data, or custom policy claims.
    - Docker BuildKit generates attestations and stores them with the image; Sigstore Cosign can also sign and verify in-toto attestations. :contentReference[oaicite:3]{index=3}

  - **Provenance**
    - a specific kind of attestation describing **how the image was built**:
      - build timestamps,
      - build parameters,
      - source repository and revision,
      - build materials,
      - platform,
      - reproducibility metadata. :contentReference[oaicite:4]{index=4}

- Practical course guidance:
  - teach students to pin and deploy by **digest** when possible,
  - treat signatures as **identity and integrity** checks,
  - treat attestations and provenance as **supply-chain evidence**,
  - and present **Sigstore** or **Notation** as forward-looking verification workflows. :contentReference[oaicite:5]{index=5}

- Example of current Docker-era build metadata:
```bash
docker buildx build --provenance=true --sbom=true --push -t myrepo/app:1.0 .
```

BuildKit can attach provenance and SBOM attestations to the image,
and Docker documents that provenance attestations at mode=min are added by default.
Bottom line:
Do not teach DCT as the future.
Teach signed images + signed metadata + build provenance instead.

{% enddetails %}

## Runtime, Storage, Network, and Secrets

{% details Run as a non-root user %}

- In Dockerfile:
  - create and use an application user with `USER`.
  - see example in the Dockerfile for our `fabric-examples` repo. 
- At runtime:
  - assume compromise will happen eventually,
    - What can the attacker receives?
    - **Not a good answer:** `root inside the container plus writable host paths`. 

{% enddetails %}

{% details Least privilege at runtime %}

- Good hardening defaults for many application containers:
  - `--cap-drop=ALL`
  - add back only the few capabilities that are truly needed,
  - `--security-opt no-new-privileges=true`
  - `--read-only`
  - explicit writable volumes or `tmpfs` for only the required paths.
- Why?
  - fewer capabilities,
  - fewer privilege transitions,
  - smaller filesystem mutation surface.

{% enddetails %}


{% details Dangerous mounts %}

- High-risk examples:
  - mounting `/` from the host,
  - mounting `/var/run/docker.sock`,
  - broad writable bind mounts into sensitive host directories.
- The Docker socket is especially dangerous:
  - if a container can talk to the daemon, it can often control other containers and effectively control the host.
- Treat writable host mounts as attack paths.

{% enddetails %}

{% details Security in storage choices %}

- **Volumes** are better for persistent application data.
- **Bind mounts** are more appropriate for development or deliberate host integration.
- **tmpfs** is useful for temporary sensitive data.
- Security interpretation:
  - prefer **volumes** for databases and persistent service data,
  - use **bind mounts** sparingly and preferably read-only,
  - use **tmpfs** for secrets or scratch data that should not persist to disk.

{% enddetails %}

{% details Port publishing and network exposure %}

- Publishing ports is not neutral.
- Published ports are reachable from outside by default unless you bind them to localhost.
- Good habits:
  - publish only what you need,
  - bind admin/debug ports to `127.0.0.1` when possible,
  - do not use host networking unless you truly need it,
  - segment services on dedicated bridge or overlay networks.

{% enddetails %}

{% details Secrets: files over environment variables %}

- Environment variables are convenient, but they are also easy to leak:
  - logs,
  - accidental dumps,
  - debugging output,
  - screenshots,
  - student copy-paste.
- Prefer secret files mounted at runtime.
- In Compose and Swarm, secrets are mounted under `/run/secrets/...`.
- This is cleaner and safer than putting passwords into `.env` files.

{% enddetails %}

## Compose Security

{% details Compose as policy %}

- Security benefit:
  - Compose lets you encode runtime policy into version-controlled files.
- Instead of relying on memory:
  - “Did I remember `--read-only` this time?”
- you can declare:
  - `read_only: true`
  - `cap_drop:`
  - `security_opt:`
  - `tmpfs:`
  - `secrets:`
  - `user:`
  - `ports:`
  in the service definition.

{% enddetails %}


## Hands-on Hardening

{% details Exercise 1: Observe default privilege versus least privilege %}

- Start a container and install `iputils-ping`:

```bash
docker run -it --rm ubuntu bash
apt update
apt install -y iputils-ping libcap2-bin
ping -c 2 8.8.8.8
capsh --print
exit
```

- Now drop all capabilities:

```bash
docker run -it --rm --cap-drop=ALL ubuntu bash
apt update
apt install -y iputils-ping libcap2-bin
ping -c 2 8.8.8.8
capsh --print
exit
```

- Discussion:
  - Why did `ping` fail?
  - Which capability did it need?
  - Why is “drop all, add back the minimum” a stronger default?

{% enddetails %}

{% details Exercise 2: Read-only root filesystem %}

- Launch a container with a read-only root filesystem:

```bash
docker run -it --rm --read-only ubuntu bash
touch /tmp/test
exit
```

- What fails?
- Now give it a safe writable scratch area:

```bash
docker run -it --rm --read-only --tmpfs /tmp ubuntu bash
touch /tmp/test
ls /tmp
exit
```

- Discussion:
  - Why is this safer than leaving the full root filesystem writable?

{% enddetails %}

{% details Exercise 3: Non-root container image %}

- Create the following Dockerfile:

```dockerfile
FROM ubuntu:24.04
RUN useradd -m -u 10001 appuser
WORKDIR /app
COPY hello.sh .
RUN chmod +x hello.sh
USER appuser
CMD ["./hello.sh"]
```

- Create `hello.sh`:

```bash
#!/bin/sh
id
whoami
touch /root/nope
echo "hello from non-root container"
```

- Build and run:

```bash
docker build -t nonroot-demo .
docker run --rm nonroot-demo
```

- Discussion:
  - What changes compared to running as root?
  - What errors are actually desirable here?

{% enddetails %}

{% details Exercise 4: Writable bind mount versus read-only bind mount %}

- Create a host directory and a file:

```bash
mkdir -p demo-config
echo "safe_config=true" > demo-config/app.conf
```

- Run with a writable bind mount:

```bash
docker run -it --rm -v $(pwd)/demo-config:/config ubuntu bash
echo "safe_config=false" > /config/app.conf
exit
cat demo-config/app.conf
```

- Reset the file, then run read-only:

```bash
echo "safe_config=true" > demo-config/app.conf
docker run -it --rm --mount type=bind,src=$(pwd)/demo-config,dst=/config,readonly ubuntu bash
echo "safe_config=false" > /config/app.conf
exit
cat demo-config/app.conf
```

- Discussion:
  - How does this connect back to Lecture 8’s inode story?
  - Why is read-only mounting a security feature, not just a storage option?

{% enddetails %}

{% details Exercise 5: Compose hardening template %}

- Example service definition:

```yaml
services:
  web:
    image: nginx:1.27
    user: "101:101"
    read_only: true
    cap_drop:
      - ALL
    security_opt:
      - no-new-privileges:true
    tmpfs:
      - /var/cache/nginx
      - /var/run
    ports:
      - "127.0.0.1:8080:80"
    volumes:
      - type: bind
        source: ./nginx.conf
        target: /etc/nginx/nginx.conf
        read_only: true
```

- Ask:
  - Which settings reduce attack surface?
  - Which settings would break a typical app if applied blindly?
  - What would need to change for production deployment on multiple nodes?

{% enddetails %}

---

## Best Practices Summary

{% details Secure-by-default checklist %}

- Keep the **host kernel**, Docker Engine, and runtime up to date.
- Prefer **rootless mode** when feasible.
- Otherwise use **user namespace remapping** when applications insist on root.
- Use **minimal base images** and **multi-stage builds**.
- Pin important images to **versions** and preferably **digests**.
- Run containers as **non-root**.
- Drop unnecessary **capabilities**.
- Use `no-new-privileges`.
- Use a **read-only root filesystem** whenever possible.
- Prefer **volumes** over broad writable bind mounts.
- Use **read-only bind mounts** for config files.
- Use **tmpfs** for sensitive temporary data.
- Publish only required ports, and bind to **localhost** when external access is not needed.
- Avoid `--privileged`, host networking, and dangerous host mounts.
- Keep secrets **out of images**, **out of build args**, and preferably **out of environment variables**.
- Use **Compose / Swarm secrets** and **BuildKit secret mounts**.
- Add **image scanning**, **SBOMs**, and **provenance attestations** to CI.
- Treat image trust as a **signing / provenance** problem, not a “just enable DCT” checkbox.

{% enddetails %}
