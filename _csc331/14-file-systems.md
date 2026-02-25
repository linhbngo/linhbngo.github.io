---
layout: lecture
pretty_table: true
collection: csc331
course: CSC 331: Operating Systems
title: "Introduction to file systems"
toc:
  - name: File systems
  - name: Abstraction: files and directories
  - name: File operations
  - name: Implementations of file systems
  - name: Mental model of a file system
  - name: 6 Multi-level index with indirect pointers
---

# Introduction to file systems

---

## File systems

{% details Overview %}

- Provide long-term information storage
- Challenges:
    - Store very large amounts of information
    - Multiple processes must be able to access ino concurrently
    - Information must survive (persist)
        - termination of process using it
        - computer crashes
        - disk failures
        - power outage
        - …
- Easy-to-use user interface

{% enddetails %}
{% details Files and directories %}

- It’s all illusion!
- CPU virtualization: a **process** that has its own processor.
- Memory virtualization: a big, contiguous, and private address space that 
can easily be accessed through virtual addresses. 
- Storage virtualization: a huge, persistent storage with files and directories 
which can be accessed using some easy-to-use APIs (ls, rm, cp …).

{% enddetails %}
---

## Abstraction: files and directories

{% details Overview %}

- File: a linear array of bytes, each of which you can read and write.
- A file has some high-level, user-readable name, e.g., `interceptor.c`.
    - One file may have multiple user-readable names, as we will see.
- Each file has a low-level name called the `inode` number.
    - This is the real identifier of a file.
- File system does NOT care about what type of file it is (C code, picture 
or video, it just makes sure to store all bytes in a file **persistently**.

{% include figure.liquid path="assets/img/courses/csc331/file-system/01.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Abstraction: files and directories %}

- Directory
    - Each directory also has an `inode` number
- Content of a directory:
    - a list of (user-readable name, `inode` number) pairs
    - which are the files and directories *under* this directory
- Directory tree / hierarchy

{% include figure.liquid path="assets/img/courses/csc331/file-system/02.png" width="50%" zoomable=true %}

{% enddetails %}
---

## File operations

{% details create %}

- **create**: `int fd = open(“foo”, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR)`
    - [open](http://man7.org/linux/man-pages/man2/open.2.html)
    - `O_CREAT`: creates the file if it does not exist.
    - `O_WRONLY`: the file can only be written to.
    - `O_TRUNC`: if the file already exists, truncates it to zero bytes, removing 
    any existing contents. 
    - `S_IRUSR`: readable by the owner,
    - `S_IWUSR`: writable by the owner.
    - `fd`: file descriptor, starts at 3 ( Reserved values: `0` for stdin, `1` for stdout, 
    `2` for stderr)

{% enddetails %}
{% details read %}

- **read**: `ssize_t read(int fd, void *buf, size_t count)`
    - [read](https://man7.org/linux/man-pages/man2/read.2.html)
    - `fd`: file descriptor value
    - `*bf`: memory address to store data read from file represented by `fd`. 
    - `count`: number of bytes to be read
    - A successful read will return the number of bytes read or a `-1` if there
    is an error. 

{% enddetails %}
{% details write %}

- **write**: `ssize_t write(int fd, const void *buf, size_t count)`
    - [write](https://man7.org/linux/man-pages/man2/write.2.html)
    - `fd`: file descriptor value
    - `*bf`: memory address containing data to be written to the file represented by `fd`.
    - `count`: number of bytes to be written. 
    - A successful write will return the number of bytes written or a `-1` if there 
    is an error.  

{% enddetails %}
{% details Non-sequential read/write: lseek %}

- `read()` and `write()` only do sequential read/write, there is no way to specify a 
particular read/write position (offset).
- For each file opened by a process, the OS keeps track of a *current* offset, which 
determines where the next read/write happens, `read()` and `write()` updates *current* 
offset according to how many bytes are read/written 
    - cannot update current to wherever they want
- If want to update *current* to wherever you want, use `lseek()`:  `off_t lseek(int fd, off_t offset, int whence)`
    - [lseek](https://man7.org/linux/man-pages/man2/lseek.2.html)
    - `fd`: file descriptor valur
    - `offset`: offset value. 
    - `whence`: 
        - if `whence` is `SEEK_SET`, the current offset is set to `offset` bytes
        - if `whence` is `SEEK_CUR`, the current offset is set to `current + offset` bytes
        - if `whence` is `SEEK_END`, the current offset is set to `size_of_file + offset` bytes

{% enddetails %}
---

## Implementations of file systems

{% details Overview %}

- There exist many, many file system implementations, literally from `AFS` to `ZFS`.
- [File system implementations](https://en.wikipedia.org/wiki/List_of_file_systems)
- Some famous ones: 
    - FAT32, NTFS used by Windows
    - HFS+ used by Mac OS X
    - UFS, ZFS used by BSD, Solaris
    - ext2, ext3, ext4, ReiserFS, XFS, JFS used by Linux
- We will study a very simple example file system named VSFS: Very Simple File System
- Analogy

{% include figure.liquid path="assets/img/courses/csc331/file-system/04.png" width="50%" zoomable=true %}

{% enddetails %}
{% details How to implement a simple file system? %}

- What structures are needed on the disk? 
- What do they need to track? 
- How are they accessed?

{% enddetails %}
---

## Mental model of a file system

- What on-disk structures store the file system’s data and metadata? 
- What happens when a process opens a file? 
- Which on-disk structures are accessed during a read or write?   

By working on and improving your mental model, you develop an abstract understanding of what is going on, 
instead of just trying to understand the specifics of some file-system code (though that is also useful, 
of course!).

{% details Unformatted raw disk %}


{% include figure.liquid path="assets/img/courses/csc331/file-system/05.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Overall organization %}


- The whole disk is divided into **fixed-sized blocks**.
- Block size: 4KB
- Number of blocks: 64
- Total size: 256KB

{% include figure.liquid path="assets/img/courses/csc331/file-system/06.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Data region %}


- Most of the disk should be used to actually store user data, while leaving a little space for storing 
other things like metadata
- In VSFS, we reserve the last 56 blocks as data region.

{% include figure.liquid path="assets/img/courses/csc331/file-system/07.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Metadata: inode table %}


- The FS need to track information about each file. 
- In VSFS, we keep the info of each file in a struct called inode. And we use 5 blocks for storing all the inodes.
- Maximum number of inodes it can hold: 5 * 4KB / 128B = 160, i.e., this VSFS can store at most 160 files.

{% include figure.liquid path="assets/img/courses/csc331/file-system/08.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Allocation structure %}


- For both data region and inode region, we need to keep track of which blocks are being used and which blocks are free. 
- We use a data structure called bitmap for this purpose, which is just a sequence of bits, and each bit indicates whether one block is free (0) or in-use (1).
- We have one bitmap for the data region and one bitmap for the inode region, and reserve one block for each bitmap. (4KB = 32K bits, can keep track of 32K blocks)

{% include figure.liquid path="assets/img/courses/csc331/file-system/09.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Superblock %}


- Superblock contains information about this particular file system, e.g., 
    - What type of file system it is (“VSFS” indicated by a magic number)
    - how many inodes and data blocks are there (160 and 56) 
    - Where the inode table begins (block 3)
    - etc. 
- When mounting a file system, the OS first reads the superblock, identify its type and other parameters, 
then attach the volume to the file system tree with proper settings.

{% include figure.liquid path="assets/img/courses/csc331/file-system/09.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Example implementations %}

- [xv6 file system](https://github.com/mit-pdos/xv6-public/blob/master/fs.h)
- [Linux ext2](https://github.com/torvalds/linux/blob/master/fs/ext2/ext2.h)


{% enddetails %}
{% details Reading a file with inode number 32 %}

- From superblock we know
    - inode table begins at Block 3, i.e., 12KB
    - inode size is 128B
- Calculate the address of inode 32
    - 12KB + 32 * 128B = 16K
So we have the inode, but which blocks have the data?

{% include figure.liquid path="assets/img/courses/csc331/file-system/09.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Data structure: the inode %}

- Short for index node
- In `vsfs` (and other simple file systems), given an `i-number`, you should directly be able 
to calculate where on the disk the corresponding inode is located.
    - `blk = (inumber * sizeof(inode_t)) / blockSize` 
    - `sector = ((blk * blockSize) + inodeStartAddr) / sectorSize`

{% include figure.liquid path="assets/img/courses/csc331/file-system/10.png" width="50%" zoomable=true %}

{% enddetails %}
---

## 6 Multi-level index with indirect pointers

{% details Overview %}

- Direct pointers to disk blocks do not support large files, so people came up with the 
idea of indirect pointer. 
- Instead of pointing to block of user data, it points to a block the contains more pointers.
- For the 15 pointers we have in an inode, use the first 14 pointers as direct pointers and the 
15th pointer as an indirect pointer. 
- How big a file can we support now?
    - 14 direct pointers in total: 14 data blocks
    - Indirect pointer points to a block (4KB) which can hold 1K pointers (each pointer is 4B), so 
    1K data blocks in addition. 
    - So total size supported: 4K * (14 + 1K) = 4152KB
- Bigger?

{% include figure.liquid path="assets/img/courses/csc331/file-system/11.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Reasoning %}

- Why use an imbalanced tree like this? Why not a different approach? 
- Many researchers have studied file systems and how they are used, and virtually every 
time they find certain “truths” that hold across the decades. 
- One such finding is that most files are small. 
    - This imbalanced design reflects such a reality: if most files are indeed small, it 
    makes sense to optimize for this case.
    - [A five-year study of file system metadata, 2007](http://static.usenix.org/event/fast07/tech/full_papers/agrawal/agrawal.pdf)

    {% include figure.liquid path="assets/img/courses/csc331/file-system/12.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Another approach: extent-based %}

- An extent is a disk pointer plus a length (in blocks), i.e., it allocates a 
few blocks in a row. 
- Instead of requiring a pointer to every block of a file, we just need a pointer to 
every several blocks (every extent).
- It is less flexible than the pointer-base approach, but uses smaller amount of metadata 
per file, and file allocation is more compact.
- Adopted by ext4, HFS+, NTFS, XFS.

{% enddetails %}
{% details Yet anther approach: linked-based %}

- Instead of having pointers to all blocks, the inode just has one pointer pointing to 
the first data block of the file, then the first block points to the second block, etc. 
- Works poorly if want to access the last block of a big file. To help, use an in memory file 
allocation table which is indexed by address of data block, so finding a block can be faster.
- This is the FAT file system, used by Windows before NTFS.

{% include figure.liquid path="assets/img/courses/csc331/file-system/13.png" width="50%" zoomable=true %}


{% enddetails %}
