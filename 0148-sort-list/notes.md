# Sort List Handbook

## Approach 1: Copy Values to an Array (Your Solution)

1.  Traverse the linked list and store values in a vector.
2.  Sort the vector using `std::sort`.
3.  Build a new sorted linked list (or rewrite existing node values).

Time: **O(n log n)**

Space: **O(n)**

Advantages: - Simple to implement. - Uses optimized library sort.

Disadvantages: - Extra memory. - Creating new nodes is unnecessary.

------------------------------------------------------------------------

## Approach 2: Copy Values and Rewrite Nodes

Store values, sort them, then overwrite the values in the original
linked list.

Time: **O(n log n)**

Space: **O(n)**

------------------------------------------------------------------------

## Approach 3: Optimal - Merge Sort on Linked List

1.  Find the middle using slow and fast pointers.
2.  Split the list into two halves.
3.  Recursively sort each half.
4.  Merge the two sorted lists.

Time: **O(n log n)**

Space: **O(log n)** (recursion stack)

Why Merge Sort? - Linked lists support sequential access. - Merge Sort
does not require random access. - Nodes can be reused without allocating
new ones.

------------------------------------------------------------------------

## Complexity Comparison

  Approach                 Time      Space
  ---------------- ------------ ----------
  Copy + Sort        O(n log n)       O(n)
  Rewrite Values     O(n log n)       O(n)
  Merge Sort         O(n log n)   O(log n)

------------------------------------------------------------------------

## Pattern Recognition

Use Merge Sort whenever you need to sort a linked list efficiently.

------------------------------------------------------------------------

## Similar Problems

-   Merge Two Sorted Lists
-   Merge k Sorted Lists
-   Middle of Linked List
-   Linked List Cycle
-   Palindrome Linked List
-   Reverse Linked List
-   Divide and Conquer problems

------------------------------------------------------------------------

## Common Mistakes

-   Forgetting to split the list.
-   Infinite recursion due to incorrect middle finding.
-   Losing the second half while splitting.
-   Using Quick Sort on a linked list.

------------------------------------------------------------------------

## Key Notes

-   Your solution is correct if extra memory is allowed.
-   The interview-preferred solution is Merge Sort.
-   Merge Sort reuses existing nodes and is the standard O(n log n)
    solution for linked lists.
