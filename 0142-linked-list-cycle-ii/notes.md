# Linked List Cycle II Handbook

## Brute Force

Use a hash set to store visited nodes. The first repeated node is the
cycle start.

Time: O(n), Space: O(n).

## Optimal: Floyd's Tortoise and Hare

-   Slow moves 1 step.
-   Fast moves 2 steps.
-   If they meet, a cycle exists.

Reset one pointer to the head. Move both pointers one step at a time.
They meet at the cycle entry.

### Why?

Let L = distance from head to cycle start, C = cycle length, and x =
distance from cycle start to the meeting point.

Slow travels L+x. Fast travels 2(L+x).

Their difference is whole cycles: L+x = k*C. Therefore L = k*C - x = C -
x (mod C).

The pointer from the head needs L steps to reach the cycle entry. The
pointer from the meeting point needs C-x steps to reach the entry. Since
these distances are equal modulo C, moving both one step at a time
guarantees they meet exactly at the cycle start.

Time: O(n), Space: O(1).

## Similar Problems

-   Linked List Cycle
-   Happy Number
-   Find the Duplicate Number
-   Middle of Linked List
-   Palindrome Linked List
-   Reorder List

## Key Notes

-   Detect the cycle first.
-   Reset one pointer to the head.
-   Move both at equal speed.
-   Their next meeting point is always the cycle entry.
