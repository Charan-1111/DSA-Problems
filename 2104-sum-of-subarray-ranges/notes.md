# Sum of Subarray Ranges Handbook

## Brute Force

Generate every subarray while maintaining the running minimum and
maximum.

Time: **O(n²)**, Space: **O(1)**.

## Key Observation

Instead of computing the range of every subarray, compute each element's
contribution as a maximum and as a minimum.

Contribution: - Maximum = `nums[i] * (i-PGE) * (NGE-i)` - Minimum =
`nums[i] * (i-PSE) * (NSE-i)`

Answer = Σ(Max Contribution − Min Contribution).

## Optimal Approach

Use four monotonic-stack helpers: - Previous Smaller (`>`) - Next
Smaller (`>=`) - Previous Greater (`<`) - Next Greater (`<=`)

The asymmetric comparisons correctly handle duplicate values.

## Complexity

-   Time: **O(n)**
-   Space: **O(n)**

## Similar Problems

-   Sum of Subarray Minimums
-   Sum of Subarray Maximums
-   Largest Rectangle in Histogram
-   Daily Temperatures
-   Next Greater Element I & II
-   Online Stock Span
-   Trapping Rain Water
-   Remove K Digits
-   Asteroid Collision

## Common Mistakes

-   Forgetting `1LL` for multiplication.
-   Using symmetric comparisons for duplicates.
-   Using values instead of indices.
-   Incorrect sentinel values (`-1` and `n`).

## Key Takeaways

-   Convert subarray problems into contribution problems.
-   Count left and right choices independently.
-   Each index is pushed and popped at most once, giving O(n)
    complexity.
