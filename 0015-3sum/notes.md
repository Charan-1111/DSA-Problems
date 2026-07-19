# 3Sum --- Complete Long-Form Handbook

> **Pattern:** Sorting + Two Pointers

------------------------------------------------------------------------

# Problem

Given an integer array `nums`, return **all unique triplets** `[a,b,c]`
such that:

    a + b + c = 0

Each triplet should appear only once.

Example:

    Input:
    [-1,0,1,2,-1,-4]

    Output:
    [-1,-1,2]
    [-1,0,1]

------------------------------------------------------------------------

# Observation

We need **3 numbers**.

Instead of searching for 3 numbers simultaneously:

    3Sum

    ↓

    Fix one number

    ↓

    Solve Two Sum

This is the key observation.

------------------------------------------------------------------------

# Approach 1 --- Brute Force

Generate every triplet.

    for i
        for j
            for k

Check

    nums[i]+nums[j]+nums[k]==0

Store triplets in a set.

## Complexity

Time: **O(n³)**

Space: **O(number of answers)**

### Pros

-   Easy.

### Cons

-   Extremely slow.

------------------------------------------------------------------------

# Approach 2 --- Hashing

Fix one element.

Need remaining two.

    target = -nums[i]

Use hash set while scanning.

Time: **O(n²)**

Space: **O(n)**

Still need duplicate handling.

------------------------------------------------------------------------

# Approach 3 --- Sorting + Two Pointers + Set (Your Solution)

First sort.

    [-4,-1,-1,0,1,2]

Fix i.

Remaining problem:

    Find

    nums[left]+nums[right]

    =

    -nums[i]

## Why sorting?

Without sorting:

    Move left?

    Move right?

    Impossible to know.

After sorting

    small --------> large

Increasing left always increases the sum.

Decreasing right always decreases the sum.

This makes two pointers possible.

------------------------------------------------------------------------

## Visual Dry Run

    -4 -1 -1 0 1 2
     ^
     i

        L       R

Current sum

    -4 + (-1)+2 = -3

Need bigger value.

Move left.

Eventually

    -1 -1 2

Triplet found.

Insert into set.

The set automatically removes duplicates.

## Complexity

Sorting: O(n log n)

Scanning: O(n²)

Set insertion overhead.

Overall about O(n² log M).

------------------------------------------------------------------------

# Approach 4 --- Optimal

Exactly the same idea.

Difference:

No set.

Instead skip duplicates.

    if(i>0 && nums[i]==nums[i-1])
        continue;

After answer

    left++;
    right--;

    while(left<right && nums[left]==nums[left-1])
        left++;

    while(left<right && nums[right]==nums[right+1])
        right--;

Now duplicates never get generated.

Time: **O(n²)**

Extra Space: **O(1)** (excluding output)

------------------------------------------------------------------------

# Why Two Pointers Work

Sorted array:

    1 2 4 6 9

Need larger sum?

Move left.

    1→2→4

Need smaller sum?

Move right.

    9→6→4

No combinations are missed.

------------------------------------------------------------------------

# Proof

For every fixed i:

Two pointers examine every possible pair exactly once.

Because one pointer always moves inward.

Duplicate skipping guarantees uniqueness.

------------------------------------------------------------------------

# Complexity Comparison

  Approach                 Time    Space
  --------------- ------------- --------
  Brute                   O(n³)     O(1)
  Hashing                 O(n²)     O(n)
  Your Solution     O(n² log M)     O(n)
  Optimal                 O(n²)   O(1)\*

\*excluding output.

------------------------------------------------------------------------

# Common Mistakes

-   Forgetting to sort.
-   Not skipping duplicates.
-   Using two pointers on an unsorted array.
-   Moving both pointers incorrectly.

------------------------------------------------------------------------

# Interview Questions

-   Why must we sort?
-   Why do two pointers work?
-   Can this extend to 4Sum?
-   Why doesn't the optimal solution need a set?

------------------------------------------------------------------------

# Similar Problems

-   Two Sum
-   Two Sum II
-   3Sum Closest
-   4Sum
-   K-Sum
-   Valid Triangle Number
-   Container With Most Water

------------------------------------------------------------------------

# Revision Notes

    3Sum

    ↓

    Sort

    ↓

    Fix one element

    ↓

    Two Pointers

    ↓

    Skip Duplicates

This is the standard interview solution.
