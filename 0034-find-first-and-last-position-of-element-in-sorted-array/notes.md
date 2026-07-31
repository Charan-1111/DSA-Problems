# Find First and Last Position of Element in Sorted Array (LeetCode 34)

## Problem

Given a sorted array, return the first and last occurrence of a target.
If absent return `[-1,-1]`.

## Approaches

### 1. Brute Force

Scan entire array. - Time: O(n) - Space: O(1)

### 2. Two Binary Searches (Optimal)

Use one binary search for the first occurrence and another for the last
occurrence. - Time: O(log n) - Space: O(1)

## Lower Bound (First Occurrence)

When target is found, store index and continue searching left.

``` cpp
if(nums[mid]==target){ res=mid; r=mid-1; }
```

## Upper Bound / Last Occurrence

When target is found, store index and continue searching right.

``` cpp
if(nums[mid]==target){ res=mid; l=mid+1; }
```

## Notes

-   Sorted array is required.
-   Use `mid = l + (r-l)/2`.
-   Save answer before shrinking search.
-   Your `findUpperBound` returns the **last occurrence**, not STL
    `upper_bound`.

## Similar Problems

-   LC 35 Search Insert Position
-   LC 704 Binary Search
-   LC 744 Find Smallest Letter Greater Than Target
-   LC 33 Search in Rotated Sorted Array
-   LC 81 Search in Rotated Sorted Array II
-   LC 153 Find Minimum in Rotated Sorted Array
-   LC 162 Find Peak Element
-   LC 875 Koko Eating Bananas
-   LC 1011 Capacity To Ship Packages Within D Days
-   LC 1482 Minimum Number of Days to Make m Bouquets
