# Subarray Sum Equals K - Complete Handbook

## Problem

Given an integer array `nums` and integer `k`, count the number of
continuous subarrays whose sum equals `k`.

## Approach 1: Brute Force

For every starting index, extend to every ending index while maintaining
a running sum.

-   Time: O(n\^2)
-   Space: O(1)

## Approach 2: Prefix Sum + Hash Map (Optimal)

Maintain a running prefix sum. If current prefix sum is `sum`, then any
previous prefix sum equal to `sum-k` forms a valid subarray.

Algorithm: 1. Maintain `sum`. 2. If `sum==k`, increment answer (or
initialize `mp[0]=1` beforehand). 3. Add frequency of `sum-k` from the
map. 4. Store current prefix sum.

Example:

    nums=[1,1,1], k=2
    Prefix: 1,2,3
    At prefix=3, need prefix=1.

-   Time: O(n)
-   Space: O(n)

## Complexity Comparison

  Approach                     Time   Space
  ----------------------- --------- -------
  Brute Force               O(n\^2)    O(1)
  Prefix Sum + Hash Map        O(n)    O(n)

## Pattern Recognition

Use Prefix Sum + Hash Map for: - Count subarrays - Sum equals K -
Negative numbers present

## Why Sliding Window Fails

Sliding window is not reliable when negative numbers exist because the
window sum is not monotonic.

## Similar Problems

-   Binary Subarrays With Sum
-   Continuous Subarray Sum
-   Maximum Size Subarray Sum Equals K
-   Subarray Sums Divisible by K
-   Count Number of Nice Subarrays

## Key Notes

-   Store frequencies of prefix sums.
-   Prefix sums convert subarray problems into prefix differences.
-   Initializing `mp[0]=1` removes the explicit `sum==k` check.
