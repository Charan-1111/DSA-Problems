# Sort Colors (Dutch National Flag) - Complete Handbook

## Approaches

### 1. Brute Force

Use `std::sort()`. - Time: O(n log n) - Space: O(log n)

### 2. Counting Sort

Count the number of 0s, 1s and 2s, then overwrite the array. - Time:
O(n) - Space: O(1)

### 3. Dutch National Flag (Optimal)

Maintain three pointers: - `l`: next position for 0 - `m`: current
element - `r`: next position for 2 from the end

Regions:

    [0..l-1] -> 0s
    [l..m-1] -> 1s
    [m..r] -> Unknown
    [r+1..n-1] -> 2s

Rules: - If nums\[m\]==0: swap(l,m), l++, m++ - If nums\[m\]==1: m++ -
If nums\[m\]==2: swap(m,r), r-- (do NOT increment m)

Reason: the swapped element at m is unprocessed.

Time: O(n) Space: O(1)

## Similar Problems

-   Move Zeroes
-   Partition Array
-   Quick Sort Partition
-   Wiggle Sort
-   Sort K Colors

## Key Notes

-   Famous three-pointer algorithm.
-   Each element is processed at most once.
-   Maintain the four invariant regions throughout execution.
