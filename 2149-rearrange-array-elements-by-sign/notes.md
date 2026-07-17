# Rearrange Array Elements by Sign - Complete Visual Handbook

## Problem

Arrange positive and negative numbers alternately while preserving
relative order.

Example:

\[3,1,-2,-5,2,-4\]

Output:

\[3,-2,1,-5,2,-4\]

------------------------------------------------------------------------

## Approach 1: Two Arrays (Your Solution)

Store positives separately.

Positive: \[3,1,2\]

Store negatives separately.

Negative: \[-2,-5,-4\]

Merge alternately:

3 3,-2 3,-2,1 3,-2,1,-5 3,-2,1,-5,2 3,-2,1,-5,2,-4

Time: O(n) Space: O(n)

------------------------------------------------------------------------

## Approach 2: Direct Placement (Optimal Interview Solution)

Observation:

Positive positions: 0,2,4,6,...

Negative positions: 1,3,5,7,...

Create answer array.

Place positives directly at even indices.

Place negatives directly at odd indices.

Example:

Answer:

------------------------------------------------------------------------

Place 3

3 \_ \_ \_ \_ \_

Place -2

3 -2 \_ \_ \_ \_

Place 1

3 -2 1 \_ \_ \_

Continue until filled.

Time: O(n) Space: O(n)

------------------------------------------------------------------------

## Approach 3: In-Place Rearrangement

Possible using rotations and stable partitioning.

Usually not expected in interviews.

Time: O(n²) or O(n log n)

Space: O(1)

------------------------------------------------------------------------

## Complexity Comparison

  Approach           Time             Space
  ------------------ ---------------- -------
  Two Arrays         O(n)             O(n)
  Direct Placement   O(n)             O(n)
  In-Place           O(n²)/O(nlogn)   O(1)

------------------------------------------------------------------------

## Pattern Recognition

Use this pattern when:

-   Alternate positives and negatives
-   Alternate even/odd positions
-   Alternate categories

Think:

Category A -\> Even Indices

Category B -\> Odd Indices

------------------------------------------------------------------------

## Similar Problems

-   Sort Array By Parity
-   Sort Array By Parity II
-   Wiggle Sort
-   Wiggle Sort II
-   Move Zeroes
-   Sort Colors
-   Dutch National Flag
-   Shuffle the Array

------------------------------------------------------------------------

## Common Mistakes

-   Forgetting relative order.
-   Mixing positive and negative target indices.
-   Not handling unequal counts.

------------------------------------------------------------------------

## Why Your Solution Works

Positive:

\[3,1,2\]

Negative:

\[-2,-5,-4\]

Alternating merge preserves the original order within both groups.

This guarantees a valid rearrangement.

------------------------------------------------------------------------

## Key Notes

-   Separate categories first.
-   Place elements into predetermined positions.
-   Direct placement is the cleanest interview solution.
-   The standard problem guarantees equal positive and negative counts.
