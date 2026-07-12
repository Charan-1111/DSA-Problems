# Intersection of Two Linked Lists -- Complete Handbook

## Problem

Given the heads of two singly linked lists, return the node where they
intersect. If they do not intersect, return `NULL`.

> **Important:** Two linked lists intersect only if they share the
> **same node in memory**, **not** merely the same value.

Example:

    List A:
    1 → 2 → 3
              \
               8 → 9 → 10
              /
    List B:
         5 → 6

The intersection starts at node `8`.

------------------------------------------------------------------------

# Approach 1: Brute Force

For every node in List A, traverse the entire List B.

    for every node in A
        for every node in B
            if(nodeA == nodeB)
                return nodeA

### Graphical View

    A: 1 → 2 → 3 → 8 → 9
                   ↑
                   Compare with every node

    B: 4 → 5 → 8 → 9

### Complexity

-   Time: **O(N × M)**
-   Space: **O(1)**

------------------------------------------------------------------------

# Approach 2: Hash Map (Your Solution)

## Intuition

Store every node address from List A.

Then traverse List B.

The first node already present in the map is the intersection.

``` cpp
unordered_map<ListNode*, int> mp;
```

### Graphical Representation

Step 1

    List A

    1 → 2 → 3 → 8 → 9

    Store

    {1,2,3,8,9}

Step 2

    Traverse List B

    4 → 5 → 8 → 9

    4 ❌

    5 ❌

    8 ✅

    Return 8

### Complexity

Time:

    O(N+M)

Space:

    O(N)

------------------------------------------------------------------------

# Approach 3: Length Difference

## Idea

Compute both lengths.

    A length = 7

    B length = 5

    Difference = 2

Move the longer list ahead by the difference.

Then move both together.

### Graphically

    A

    1 → 2 → 3 → 4 → 8 → 9
            ↑

    B

    5 → 6 → 8 → 9

Skip

    1
    2

Now

    A

    3 → 4 → 8 → 9

    B

    5 → 6 → 8 → 9

Move together.

Eventually

    8 == 8

Return node 8.

### Complexity

Time:

    O(N+M)

Space:

    O(1)

------------------------------------------------------------------------

# Approach 4: Optimal Two-Pointer Switching

⭐ **Interview Preferred**

## Idea

When one pointer reaches the end, switch it to the other list.

    pA → List A → List B

    pB → List B → List A

Eventually both pointers travel exactly the same total distance.

### Graphical Explanation

    A

    1 → 2 → 3 → 8 → 9
              \
               10

    B

    4 → 5
         \
          8 → 9 → 10

Initially

    pA

    ↓

    1

    pB

    ↓

    4

When `pA` finishes List A

    NULL

    ↓

    Switch to List B

When `pB` finishes List B

    NULL

    ↓

    Switch to List A

Now both have traversed

    Length(A)+Length(B)

They become aligned automatically.

Eventually

    pA

    ↓

    8

    pB

    ↓

    8

Return node 8.

------------------------------------------------------------------------

## Why Does This Work?

Suppose

    Length A = a + c

    Length B = b + c

where

    a = unique part of A

    b = unique part of B

    c = common part

Pointer A travels

    a + c + b

Pointer B travels

    b + c + a

Both distances are equal.

Therefore they either

-   meet at the intersection

or

-   both become NULL.

------------------------------------------------------------------------

# Complexity Comparison

  Approach                Time     Space
  ----------------------- -------- -------
  Brute Force             O(N×M)   O(1)
  Hash Map                O(N+M)   O(N)
  Length Difference       O(N+M)   O(1)
  Two-Pointer Switching   O(N+M)   O(1)

------------------------------------------------------------------------

# Pattern Recognition

Whenever you see

-   Two linked lists
-   Alignment by distance
-   Shared suffix
-   Different starting points

Think about

✅ Two Pointer Switching

------------------------------------------------------------------------

# Similar Problems

## Two Pointer

-   Remove Nth Node From End
-   Middle of Linked List
-   Linked List Cycle
-   Linked List Cycle II
-   Palindrome Linked List

## Linked List

-   Merge Two Sorted Lists
-   Reverse Linked List
-   Sort List
-   Reorder List

## Hashing

-   Copy List with Random Pointer
-   Detect Cycle using Hash Set

------------------------------------------------------------------------

# Common Mistakes

❌ Comparing node values instead of node addresses.

Correct:

``` cpp
nodeA == nodeB
```

Not

``` cpp
nodeA->val == nodeB->val
```

❌ Forgetting to switch pointers after reaching `NULL`.

❌ Assuming equal values imply an intersection.

------------------------------------------------------------------------

# Key Notes

-   Two linked lists intersect only when they share the **same memory
    node**.
-   Your hash-map solution is correct and runs in **O(N+M)** time.
-   The optimal interview solution uses **Two-Pointer Switching** with
    **O(1)** extra space.
-   The switching trick automatically aligns both pointers without
    explicitly computing the lengths.
