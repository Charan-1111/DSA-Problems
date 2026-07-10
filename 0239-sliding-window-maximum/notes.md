# Sliding Window Maximum - Complete Handbook

## Brute Force

Scan every window of size k to find the maximum.

-   Time: O(n\*k)
-   Space: O(1)

## Better Approach (Max Heap)

Maintain a max heap of (value,index). Remove expired indices from the
heap top.

-   Time: O(n log k)
-   Space: O(k)

## Optimal Approach (Monotonic Deque)

Store indices in a monotonic decreasing deque. - Remove expired indices
from the front. - Remove smaller values from the back. - Front always
stores the maximum.

Your implementation follows this optimal approach.

Complexity: - Time: O(n) - Space: O(k)

## Pattern Recognition

Use a monotonic deque when a window slides and you need the
maximum/minimum for every window.

## Similar Problems

-   Sliding Window Minimum
-   Jump Game VI
-   Constrained Subsequence Sum
-   Shortest Subarray with Sum at Least K
-   Daily Temperatures
-   Largest Rectangle in Histogram
-   Remove K Digits
-   Trapping Rain Water

## Key Notes

-   Store indices, not values.
-   Remove expired indices.
-   Maintain decreasing order.
-   Each index is pushed and popped at most once.
