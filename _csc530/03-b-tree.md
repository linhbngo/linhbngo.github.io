---
layout: lecture
pretty_table: true
collection: csc530
title: "Balanced Tree"
toc:
  - name: Paper presentation dates
  - name: Balanced Tree Red-Black and B-tree
  - name: Balanced Tree Red-Black implementation
  - name: Dynamic Selection
---
# Balanced Tree


## Paper presentation dates:

- Oct 2:  [Segmented Tree](data/segmented_tree.pdf)
- Oct 16: [Balanced Tree](data/balanced_trees.pdf)
    - [Kth largest element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/description/)
- Oct 30: [Suffix Array](data/suffix_arrays.pdf)
    - [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/description/)
- Nov 13: [Binomial Heaps](data/binomial_heaps.pdf)
- Nov 20: [Fibonnaci Heaps](data/fibonacci_heaps.pdf)
- Dec 4:  [Cuckoo Hashing](data/cuckoo_hashing.pdf)

## Balanced Tree: Red-Black and B-tree

- [Presentation](data/slide01_bst.pdf)
- 

{% details Operations %}

- Insert
- Delete
- Split
- Search

{% enddetails %}
{% details Relevant algorithms %}

- Insert a key `k` into a B-tree `T` of height `h` 
- `B-TREE-INSERT(T,k)`

    {% include figure.liquid path="assets/img/courses/csc530/b-tree/b_tree_insert.png" width="50%" zoomable=true %}

    - Lines 3–9: if the root node r is full, the root splits 
    and a new node s (having two children) becomes the root. 
        - Splitting the root is the only way to increase the height of a B-tree. 
        - *Unlike the slide, we preemptively split before insert*.
        - The procedure finishes by calling `B-TREE-INSERT-NONFULL` to insert 
        key k into the tree rooted at the non-full root node. 
        - `B-TREE-INSERT-NONFULL` recurses as necessary down the tree, 
    at all times guaranteeing that the node to which it recurses is not 
    full by calling `B-TREE-SPLIT-CHILD` as necessary.

- `B-TREE-INSERT-NONFULL(x,k)`

    {% include figure.liquid path="assets/img/courses/csc530/b-tree/b_tree_insert_nonfull.png" width="50%" zoomable=true %}

    - Lines 3–8 handle the case in which x is a leaf node by 
    inserting key k into x.
    - If x is not a leaf node, then we must insert k into the appropriate 
    leaf node in the subtree rooted at internal node x. 
    - Lines 9–11 determine the child of x to which the recursion descends. Line 13 detects whether the recursion would descend to a full child, in which case line 14 uses `B-TREE-SPLIT-CHILD` to split that child into two non-full children, and lines 15–16 determine which of the two children is now the correct one to descend to. 
    - Lines 13–16 is to guarantee that the procedure never recurses to a full node. 
    - Line 17 then recurses to insert k into the appropriate subtree. 

- `B-TREE-SPLIT-CHILD(x,i)`

    {% include figure.liquid path="assets/img/courses/csc530/b-tree/b_tree_split_child.png" width="50%" zoomable=true %}

    - As the name suggested, this function split y, the child node of a node x. 
        - Node y originally has 2t children (2t - 1 keys) but is reduced to t children (t - 1 keys) 
        by this operation. 
        - Node z takes the t largest children (t - 1 keys) from y,and z becomes a new child of x, 
        positioned just after y in x's table of children. The median key of y moves up to become 
        the key in x that separates y and z.
    - Lines 1–9 create node z and give it the largest t - 1 keys and corresponding 
    t children of y. 
    - Line 10 adjusts the key count for y. 
    - Lines 11–17 insert z as a child of x, move the median key from y up to x in order to 
    separate y from z, and adjust x's key count. 

{% enddetails %}
{% details Implementation %}

- How do we code a B-tree containing integers?

{% enddetails %}
## Balanced Tree: Red-Black implementation

[Red Black Tree](data/slide02_bst_redblack.pdf)

{% details Overview %}

- A `red-black` tree is a binary search tree with one extra bit of 
storage per node: its color, which can be either `RED` or `BLACK`
- Each node of the tree contains:
    - `color`
    - `key`
    - `left`
    - `right`
    - `p`
- Rules:
    - Every node is either red or black.
    - The root is black.
    - Every leaf (NIL) is black.
    - If a node is red, then both its children are black.
    - For each node, all simple paths from the node to descendant leaves 
    contain the same number of black nodes.

{% enddetails %}
{% details Insertion %}

{% include figure.liquid path="assets/img/courses/csc530/b-tree/rb_insert.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Insertion Fixup %}

{% include figure.liquid path="assets/img/courses/csc530/b-tree/rb_insert_fixup.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Left Rotate %}

{% include figure.liquid path="assets/img/courses/csc530/b-tree/rb_left_rotate.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Right Rotate %}

- Symetric to left rotate

{% enddetails %}
## Dynamic Selection

[Dynamic Selection](data/slide03_bst_dynamic_selection.pdf)

{% details LeetCode problem %}

- [Kth largest element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/description/)
- Unsorted
- [RB implementation Java](https://github.com/williamfiset/Algorithms/blob/master/src/main/java/com/williamfiset/algorithms/datastructures/balancedtree/RedBlackTree.java)


{% enddetails %}
