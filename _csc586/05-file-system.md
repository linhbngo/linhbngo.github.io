---
layout: lecture
pretty_table: true
collection: csc586
course: CSC 586: Linux System Administration and Security - Summer 2024 - 100% online asynchronous
title: "The Filesystem"
toc:
  - name: In Linux, everything is a file
  - name: Main components
  - name: Path names
  - name: Mouning and unmounting
  - name: Who is doing what on which file system?
  - name: Organizaion of the file system tree
  - name: Filetype encoding
  - name: File attributes
  - name: Access control lists
---
# The Filesystem


## In Linux, everything is a file

- Processes
- Audio devices
- Kernel data structures and tuning parameters
- Interprocess communication channels

---

## Main components

- A namespace
- An API
- Securiy models
- An implemenation

---

## Path names

- Single unified hierarchy start at root: `/`
- Absolute path: path name starts from root
- Relative path: path name starts from current directory: . or subdirectory name

---

## Mouning and unmounting

- The root filesystem is composed of smaller trunks (smaller filesystems)
- Smaller filesystems are attached to the tree with the mount command, which ...
    - Maps a directory within the existing filesystem tree, called the mount 
    point, to the root of the newly attached filesystem. 

## Who is doing what on which file system?

- [fuser](https://man7.org/linux/man-pages/man1/fuser.1.html)

~~~bash
man fuser
sudo fuser -cv /users
~~~

- Instead of rebooting, perhaps unmounting/remounting of offending device drivers.

---

## Organizaion of the file system tree

{% include figure.liquid path="assets/img/courses/csc586/06-file-system/filesystem.png" width="50%" zoomable=true %}

---

## Filetype encoding

- Character/block device file: standard communication interface 
provided by device drivers.
- Local domain sockets: connections between processes that allow them 
to communicate hygienically.
- Named pipes allow communication between two processes running 
on the same host. 
- Symbolic links: point to a file by name
- Hard links: create an illusion that a file exists in more than one 
place at the same time. 

[](fig//06-file-system/encoding.png)

---

## File attributes

- Traditionally 12 bits for each file: the file's mode (plus 4 more bits : 
file's type)
- 9 permission bits - read, write, execute for owner, group, others
- setuid & setgid bits (4000 , 2000)
    - setgid on directory - newly created file has group 
    ownership of the directory (not group ownership of a user creating it)
- sticky bit (1000)
    - on regular files ignored (original meaning: keep program text on swap device)
    - on directories - only the owner of the file and the owner of that directory may remove the file from that directory

[](fig/06-file-system/chmod-encoding.png)

[](fig/06-file-system/mnemonic-syntax.png)

---

## Access control lists

- supported for ext2, ext3, ext4, reiserfs, XFS, JFS: `mount -o [no]acl`
- allows rwx to be set independently for any user.group combination: `getfacl`, `setfacl` ( plus man acl)
- NFSv4 - superset of POSIX ACLs plus all permission bits and most semantics 
from Windows
