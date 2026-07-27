# Merge Two Sorted Arrays Without Extra Space

## Problem

Given two **sorted** arrays, rearrange them so that after completion: -
`arr1` contains the first `n` smallest elements. - `arr2` contains the
remaining `m` largest elements. - **Do not use extra array space.**

------------------------------------------------------------------------

# Approach 1: Swap + Sort (Your Approach)

### Idea

1.  Compare the largest element of `arr1` with the smallest of `arr2`.
2.  If out of order, swap.
3.  Continue.
4.  Sort both arrays.

``` cpp
int i=n-1,j=0;
while(i>=0 && j<m){
    if(arr1[i]>arr2[j]){
        swap(arr1[i],arr2[j]);
        i--; j++;
    }else break;
}
sort(arr1.begin(),arr1.end());
sort(arr2.begin(),arr2.end());
```

### Complexity

-   Swaps: `O(min(n,m))`
-   Sorts: `O(n log n + m log m)`
-   Space: `O(1)`

### Pros

-   Easy to understand.
-   Works well.

### Cons

-   Sorting again is expensive.

------------------------------------------------------------------------

# Approach 2: Insertion Method

### Idea

Traverse `arr1`. Whenever `arr1[i] > arr2[0]`: - Swap them. - Insert the
swapped value into its correct position inside `arr2` (shift elements).

### Complexity

-   Worst Case: `O(n*m)`
-   Space: `O(1)`

### When to use

Educational only; rarely preferred.

------------------------------------------------------------------------

# Approach 3: Gap Method (Optimal)

Uses Shell Sort's gap concept.

## Algorithm

1.  Consider both arrays as one virtual array.
2.  Start with gap = ceil((n+m)/2).
3.  Compare elements gap apart.
4.  Swap if needed.
5.  Reduce gap until 1.

### Complexity

-   Time: `O((n+m) log(n+m))`
-   Space: `O(1)`

This is the most common interview solution.

------------------------------------------------------------------------

# Key Notes

-   Both arrays must already be sorted.
-   No extra arrays allowed.
-   `sort(arr1.begin(), arr2.end())` is invalid because iterators must
    belong to the same container.
-   Use `>` instead of `>=` to avoid unnecessary swaps for equal values.

------------------------------------------------------------------------

# Comparison

  Approach                        Time   Space Interview
  ------------- ---------------------- ------- -----------
  Swap + Sort     O(n log n + m log m)    O(1) Good
  Insertion                      O(nm)    O(1) Rare
  Gap Method         O((n+m) log(n+m))    O(1) Best

------------------------------------------------------------------------

# Similar Problems

1.  Merge Sorted Array (LeetCode 88)
2.  Merge Without Extra Space (GFG)
3.  Merge Intervals
4.  Sort an Array of 0s, 1s and 2s (Dutch National Flag)
5.  K-th Element of Two Sorted Arrays
6.  Median of Two Sorted Arrays
7.  Intersection of Two Sorted Arrays
8.  Union of Two Sorted Arrays
9.  Inversion Count
10. Count Reverse Pairs

------------------------------------------------------------------------

# Interview Tips

-   Mention the brute-force approach first.
-   Then explain Swap + Sort.
-   Finally present the Gap Method as the optimal solution.
-   Clearly state time and space complexity for every approach.
