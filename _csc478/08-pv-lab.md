---
layout: lecture
pretty_table: true
collection: csc478
title: "Kubernetes PV/PVC Hands-On Lab with NFS"
toc:
  - name: Pre-Check
  - name: Create a Namespace
  - name: PersistentVolume (PV)
  - name: PersistentVolumeClaim (PVC)
  - name: Pod with PVC
  - name: Multi-Pod RWX Proof
  - name: Reclaim Policy Demo
  - name: Cleanup
---
# Kubernetes PV/PVC Hands-On Lab with NFS

This lab demonstrates how to replace an `emptyDir` volume with a **PersistentVolume** (PV) 
and **PersistentVolumeClaim** (PVC) backed by an NFS export.

We will use the cluster’s NFS server (`192.168.1.1`) with exports under `/opt/{home,software,scratch}`. In this 
lab, we use `/opt/scratch`.

---

## Pre-Check

On the **head node**:

```bash
showmount -e 192.168.1.1
```

On **each Kubernetes node**:

```bash
mount | egrep '/opt/(home|software|scratch)'
```

---

## Create a Namespace

```bash
kubectl create ns pv-lab || true
```

---

## PersistentVolume (PV)

Save the following manifest as **pv-nfs-scratch.yaml**:

```yaml
apiVersion: v1
kind: PersistentVolume
metadata:
  name: pv-nfs-scratch
spec:
  capacity:
    storage: 1Gi
  accessModes:
    - ReadWriteMany
  persistentVolumeReclaimPolicy: Retain
  mountOptions:
    - nfsvers=4.2
    - nolock
  nfs:
    server: 192.168.1.1
    path: /opt/scratch
```

Apply and check

```bash
kubectl apply -f pv-nfs-scratch.yaml
kubectl get pv pv-nfs-scratch -o wide
```

---

## PersistentVolumeClaim (PVC)

Save the following manifest as **pvc-scratch.yaml**:

```yaml
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: scratch-pvc
  namespace: pv-lab
spec:
  accessModes:
    - ReadWriteMany
  resources:
    requests:
      storage: 512Mi
  volumeName: pv-nfs-scratch
```

Apply and test:

```bash
kubectl apply -f pvc-scratch.yaml
kubectl -n pv-lab get pvc scratch-pvc -o wide
```

---

## Pod with PVC

This pod has two containers sharing the same PVC, just like 
the `emptyDir` example.

Save as **pod-pvc.yaml**:

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: pvc-pod
  namespace: pv-lab
spec:
  securityContext:
    fsGroup: 2000
  containers:
  - name: my-app-container
    image: nginx
    volumeMounts:
    - name: shared-data
      mountPath: /var/data
  - name: my-sidecar-container
    image: busybox
    command: ["sh", "-c", "echo 'hello from sidecar' > /shared/file.txt && sleep 3600"]
    volumeMounts:
    - name: shared-data
      mountPath: /shared
  volumes:
  - name: shared-data
    persistentVolumeClaim:
      claimName: scratch-pvc
```

Apply:

```bash
kubectl apply -f pod-pvc.yaml
kubectl -n pv-lab get pod pvc-pod -o wide
```

Validate:

```bash
kubectl -n pv-lab exec pvc-pod -c my-sidecar-container -- cat /shared/file.txt
kubectl -n pv-lab exec pvc-pod -c my-app-container -- ls -l /var/data
ls /opt/scratch
```


---

## Multi-Pod RWX Proof

Deploy a second pod that appends to the same file.

Save as **pod-pvc-reader.yaml**:

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: pvc-pod-reader
  namespace: pv-lab
spec:
  containers:
  - name: tailer
    image: busybox
    command: ["sh","-c","while true; do date >> /mnt/file.txt; sleep 2; done"]
    volumeMounts:
    - name: shared-data
      mountPath: /mnt
  volumes:
  - name: shared-data
    persistentVolumeClaim:
      claimName: scratch-pvc
```

Apply:

```bash
kubectl apply -f pod-pvc-reader.yaml
```

Check from the first pod:

```bash
kubectl -n pv-lab exec pvc-pod -c my-sidecar-container -- tail -f /shared/file.txt
```

You should see timestamps being appended by the second pod.

---

## Reclaim Policy Demo

Delete the PVC:

```bash
kubectl -n pv-lab delete pvc scratch-pvc
kubectl get pv pv-nfs-scratch -o yaml | egrep 'phase:|claimRef'
```

The PV enters `Released` phase, but the data **remains** on NFS (`/opt/scratch`).

Clear the claim reference if you want to reuse the PV:

```bash
kubectl patch pv pv-nfs-scratch --type=json -p='[{"op":"remove","path":"/spec/claimRef"}]'
```

---

## Cleanup

```bash
kubectl -n pv-lab delete pod pvc-pod pvc-pod-reader --ignore-not-found
kubectl -n pv-lab delete pvc scratch-pvc --ignore-not-found
kubectl delete pv pv-nfs-scratch --ignore-not-found
kubectl delete ns pv-lab --ignore-not-found
```

{% details career A storage lab becomes operational experience when failure is tested %}

Creating a bound PVC proves configuration, but production storage work also
requires failure and recovery evidence. The Kubernetes
[PersistentVolume documentation](https://kubernetes.io/docs/concepts/storage/persistent-volumes/)
notes that the PV lifecycle is independent of a Pod and that backend
capabilities determine available access modes.

A public
[Kubernetes NFS failure report](https://github.com/kubernetes/kubernetes/issues/90593)
shows why that distinction matters: when an NFS server became unavailable,
broken mounts affected Pod lifecycle operations and kubelet behavior on client
nodes. The PVC object alone could not make the backend healthy.

For a portfolio or runbook, add:

- proof that data survives Pod replacement;
- the observed behavior when an NFS client node or server is unavailable;
- reclaim-policy results after deleting the claim;
- backup ownership and a tested restore procedure.

These checks connect Kubernetes YAML to storage operations and incident
response.

{% enddetails %}
