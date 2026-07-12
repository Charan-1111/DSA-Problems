# Rotate List - Complete Handbook

## Problem

Rotate a singly linked list to the right by `k` positions.

Example:

    1 -> 2 -> 3 -> 4 -> 5

    k = 2

    Output

    4 -> 5 -> 1 -> 2 -> 3

------------------------------------------------------------------------

## Approach 1: Array + Build New List (Your Solution)

### Steps

1.  Store all node values in a vector.
2.  Compute `k %= length`.
3.  Split the array at `length - k`.
4.  Perform the three-reversal algorithm.
5.  Build a new linked list.

### Three-Reversal Visualization

Original

    1 2 3 | 4 5

Reverse first part

    3 2 1 | 4 5

Reverse second part

    3 2 1 | 5 4

Reverse entire array

    4 5 1 2 3

Time: **O(n)**

Space: **O(n)**

------------------------------------------------------------------------

## Approach 2: Rewrite Existing Node Values

Store values in an array, rotate the array, then overwrite the values in
the original nodes.

Time: **O(n)**

Space: **O(n)**

------------------------------------------------------------------------

## Approach 3: Optimal - Circular Linked List

### Step 1

Find the length.

### Step 2

Compute:

    k = k % length

### Step 3

Connect the tail to the head.

    1 -> 2 -> 3 -> 4 -> 5
    ^                  |
    |__________________|

The list becomes circular.

### Step 4

Find the new tail.

    length = 5
    k = 2

    newTailIndex = length - k - 1 = 2

    1 -> 2 -> 3 -> 4 -> 5
              ^
          New Tail

### Step 5

The new head is:

    newHead = newTail->next

### Step 6

Break the circle.

    4 -> 5 -> 1 -> 2 -> 3

Time: **O(n)**

Space: **O(1)**

------------------------------------------------------------------------

## Complexity Comparison

  Approach                 Time   Space
  ---------------------- ------ -------
  Array + New List         O(n)    O(n)
  Rewrite Values           O(n)    O(n)
  Circular Linked List     O(n)    O(1)

------------------------------------------------------------------------

## Pattern Recognition

Use this pattern whenever you see: - Rotate a linked list - Tail becomes
head - Circular traversal

Think: **Convert to a Circular Linked List**.

------------------------------------------------------------------------

## Similar Problems

### Linked Lists

-   Reverse Linked List
-   Reverse Linked List II
-   Reorder List
-   Remove Nth Node From End
-   Sort List
-   Merge Two Sorted Lists

### Circular Structures

-   Josephus Problem
-   Circular Queue
-   Circular Deque

### Arrays

-   Rotate Array
-   Shift 2D Grid

------------------------------------------------------------------------

## Common Mistakes

-   Forgetting `k %= length`.
-   Not handling `k == 0`.
-   Forgetting to break the circular list.
-   Creating unnecessary new nodes.

------------------------------------------------------------------------

## Key Notes

-   Your solution correctly applies the three-reversal idea to values.
-   The interview-preferred solution rotates pointers instead of values.
-   Converting the list into a temporary circle makes the solution
    elegant and uses only O(1) extra space.
