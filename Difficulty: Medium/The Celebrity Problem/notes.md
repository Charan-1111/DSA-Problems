# Celebrity Problem Handbook

## Brute Force

Check every person's row and column. - Row: should know nobody. -
Column: everyone should know them.

Time: O(n²)

## Better Approach (Your Solution)

Count incoming edges for each person and validate only candidates. Still
O(n²).

## Optimal Approach

Candidate elimination: If A knows B, A cannot be celebrity. Else B
cannot be celebrity. After one pass, verify the remaining candidate.

Time: O(n) Space: O(1)

## Alternative

Stack elimination (O(n) time, O(n) space).

## Pattern Recognition

Use elimination when every comparison discards one candidate.

## Similar Problems

-   Find the Town Judge
-   Boyer-Moore Majority Element
-   Gas Station
-   Next Greater Element
-   Daily Temperatures
-   Online Stock Span

## Key Notes

-   Celebrity: out-degree 0, in-degree n-1.
-   Always verify the final candidate.
-   Candidate elimination is the preferred interview solution.
