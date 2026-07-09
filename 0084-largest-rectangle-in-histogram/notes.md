# Largest Rectangle in Histogram

## Brute Force

For each bar, expand left and right until a smaller bar is found.

-   Time: O(n²)
-   Space: O(1)

## Better Approach (Previous & Next Smaller Element)

Treat every bar as the limiting height. Compute Previous Smaller Element
(PSE) and Next Smaller Element (NSE) using a monotonic increasing stack.

Width = NSE - PSE - 1

Area = Width × Height

This matches your implementation.

-   Time: O(n)
-   Space: O(n)

## Optimal Single Stack

Compute areas while popping from the stack. The current index is the NSE
and the new stack top is the PSE.

-   Time: O(n)
-   Space: O(n)

## Key Points

-   Use a monotonic increasing stack.
-   Use `>=` while popping to handle duplicates.
-   Default NSE = n, PSE = -1.
-   Width = nse - pse - 1.
-   Every bar becomes the limiting height exactly once.

## Similar Problems

-   Maximal Rectangle
-   Trapping Rain Water
-   Sum of Subarray Minimums
-   Daily Temperatures
-   Next Greater Element I & II
-   Previous Smaller Element
-   Online Stock Span
-   Remove K Digits
-   Asteroid Collision

## Complexity

  Approach          Time   Space
  -------------- ------- -------
  Brute Force      O(n²)    O(1)
  PSE + NSE         O(n)    O(n)
  Single Stack      O(n)    O(n)
