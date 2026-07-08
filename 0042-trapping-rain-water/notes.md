# Trapping Rain Water Handbook (Expanded)

## Problem

Given an elevation map, compute the total amount of water trapped after
raining.

## 1. Brute Force

For each index, scan left to find the tallest bar and scan right to find
the tallest bar.

Water at index: `min(leftMax, rightMax) - height[i]`

-   Time: **O(n²)**
-   Space: **O(1)**

------------------------------------------------------------------------

## 2. Better: Prefix & Suffix Maximum Arrays

Precompute:

-   `leftMax[i]` = tallest bar from `0..i`
-   `rightMax[i]` = tallest bar from `i..n-1`

Then:

`water += min(leftMax[i], rightMax[i]) - height[i]`

-   Time: **O(n)**
-   Space: **O(n)**

------------------------------------------------------------------------

## 3. Monotonic Stack

Maintain a decreasing stack of indices.

When a taller bar arrives: 1. Pop the valley. 2. Current index becomes
the right boundary. 3. New stack top becomes the left boundary. 4. Water
height: `min(leftHeight, rightHeight) - bottomHeight` 5. Width:
`right - left - 1`

-   Time: **O(n)**
-   Space: **O(n)**

------------------------------------------------------------------------

## 4. Optimal: Two Pointers

Maintain: - `left`, `right` - `leftMax`, `rightMax`

Observation:

-   If `leftMax <= rightMax`, the water at `left` is fully determined by
    `leftMax`.

-   Otherwise, the water at `right` is determined by `rightMax`.

-   Time: **O(n)**

-   Space: **O(1)**

------------------------------------------------------------------------

## Your Approach

Your solution propagates the tallest greater boundary from both
directions using monotonic-stack-derived arrays (`pge` and `nge`).

The final computation is still:

`min(leftBoundary, rightBoundary) - height[i]`

The idea is valid, although interviews typically expect the
Prefix/Suffix or Two-Pointer solution because they are simpler to
explain.

------------------------------------------------------------------------

# Pattern Recognition

Think about this problem when you see:

-   Water trapped between boundaries.
-   Need the highest element on both sides.
-   Previous/Next Greater relationships.
-   Range boundary computation.

------------------------------------------------------------------------

# Related Problems

## Prefix/Suffix Maximum Pattern

-   Best Time to Buy and Sell Stock
-   Product of Array Except Self
-   Maximum Difference Between Increasing Elements
-   Maximum Width Ramp

## Monotonic Stack Pattern

-   Next Greater Element I
-   Next Greater Element II
-   Daily Temperatures
-   Stock Span
-   Largest Rectangle in Histogram
-   Sum of Subarray Minimums
-   Remove K Digits
-   Asteroid Collision
-   Online Stock Span

## Two Pointer Pattern

-   Container With Most Water
-   3Sum
-   4Sum
-   Sort Colors
-   Move Zeroes
-   Squares of a Sorted Array
-   Valid Palindrome
-   Boats to Save People

## Sliding Window Pattern

-   Sliding Window Maximum
-   Longest Repeating Character Replacement
-   Minimum Size Subarray Sum
-   Maximum Consecutive Ones III
-   Permutation in String

------------------------------------------------------------------------

# How to Decide Which Pattern?

  Clue                           Pattern
  ------------------------------ ----------------------------------
  Need left/right maximum        Prefix/Suffix Arrays
  Need nearest greater/smaller   Monotonic Stack
  Window moves continuously      Sliding Window / Monotonic Queue
  Both ends can move             Two Pointers

------------------------------------------------------------------------

# Complexity Comparison

  Approach          Time    Space
  ----------------- ------- -------
  Brute Force       O(n²)   O(1)
  Prefix/Suffix     O(n)    O(n)
  Monotonic Stack   O(n)    O(n)
  Two Pointers      O(n)    O(1)

## Key Takeaways

-   Water above a bar depends on the shorter of the tallest boundaries.
-   Prefix/Suffix arrays precompute boundaries.
-   Monotonic stacks identify valleys efficiently.
-   Two pointers provide the optimal space solution.
-   Always identify whether the problem is about **boundaries**,
    **nearest greater elements**, or **moving windows** before choosing
    the technique.
