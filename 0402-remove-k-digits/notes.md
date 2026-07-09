# Remove K Digits Handbook

## Brute Force

Generate all possibilities after removing k digits and choose the
minimum. Exponential time.

## Key Observation

Whenever a larger digit appears before a smaller digit, removing the
larger digit gives a smaller number.

## Optimal Solution

Use a monotonic increasing stack.

-   Pop while top \> current and k\>0.
-   Push current digit.
-   If k remains, remove from the end.
-   Strip leading zeros.

Time: O(n) Space: O(n)

## Why It Works

The stack maintains the smallest possible prefix at every step. Each
digit is pushed once and popped at most once.

## Common Mistakes

-   Forgetting remaining k removals.
-   Forgetting leading zeros.
-   Accessing beyond string while stripping zeros.
-   Using string concatenation instead of push_back.

## Similar Problems

-   Next Greater Element I & II
-   Daily Temperatures
-   Largest Rectangle in Histogram
-   Sum of Subarray Minimums
-   Sum of Subarray Ranges
-   Asteroid Collision
-   Trapping Rain Water
-   Online Stock Span

## Key Notes

-   Monotonic Increasing Stack + Greedy.
-   Greedily improve the leftmost digits.
-   Remove remaining digits from the end.
