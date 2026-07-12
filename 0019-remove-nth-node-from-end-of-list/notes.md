# Remove Nth Node From End of List Handbook

## Approach 1: Two Traversals (Your Solution)

1.  Traverse the list to compute its length.
2.  Convert the problem into deleting the `(length - n)`th node from the
    front.
3.  Traverse again and remove the node.

Time: **O(n)**

Space: **O(1)**

------------------------------------------------------------------------

## Approach 2: Optimal - Fast & Slow Pointer

Use a dummy node before the head.

-   Move `fast` ahead by `n + 1` nodes.
-   Move `fast` and `slow` together.
-   When `fast` reaches `NULL`, `slow` is just before the node to
    delete.

This avoids computing the length and completes the task in one
traversal.

Time: **O(n)**

Space: **O(1)**

### Why It Works

A fixed gap of `n` nodes is maintained between `fast` and `slow`.

When `fast` reaches the end, `slow` is exactly one node before the
target, allowing deletion in constant time.

------------------------------------------------------------------------

## Complexity Comparison

  Approach                      Time   Space
  --------------------------- ------ -------
  Length + Second Traversal     O(n)    O(1)
  Fast & Slow Pointer           O(n)    O(1)

------------------------------------------------------------------------

## Pattern Recognition

Use the Fast & Slow Pointer technique whenever you see: - Nth node from
the end - Middle of a linked list - Detecting cycles - Fixed distance
between two pointers

------------------------------------------------------------------------

## Similar Problems

### Fast & Slow Pointer

-   Middle of the Linked List
-   Linked List Cycle
-   Linked List Cycle II
-   Palindrome Linked List
-   Happy Number
-   Find the Duplicate Number

### Linked List

-   Delete Node in a Linked List
-   Delete the Middle Node
-   Reorder List
-   Rotate List
-   Reverse Linked List

------------------------------------------------------------------------

## Common Mistakes

-   Forgetting the case where the head must be removed.
-   Not using a dummy node in the one-pass solution.
-   Off-by-one errors while advancing `fast`.
-   Losing the rest of the list after deletion.

------------------------------------------------------------------------

## Key Notes

-   Your two-pass solution is correct and efficient.
-   The interview-preferred solution is the one-pass Fast & Slow Pointer
    approach.
-   A dummy node greatly simplifies edge cases.
-   Maintaining a fixed gap between pointers is the core idea behind the
    optimal solution.
