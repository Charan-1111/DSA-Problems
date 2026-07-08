# Sum of Subarray Minimums Handbook

## Brute Force

Generate every subarray and maintain the running minimum.

-   Time: O(n²)
-   Space: O(1)

## Key Observation

Instead of finding the minimum for every subarray, count how many
subarrays consider each element as their minimum.

Contribution:

    arr[i] * (i-PSI[i]) * (NSI[i]-i)

## Optimal Approach

Use two monotonic stacks.

-   PSI (Previous Smaller Index): pop `>`
-   NSI (Next Smaller Index): pop `>=`

The asymmetric comparison correctly handles duplicates.

``` cpp
long long ways = 1LL * (nsi[i]-i) * (i-psi[i]);
ways %= mod;
long long contribution = ways * arr[i] % mod;
ans = (ans + contribution) % mod;
```

## Why left \* right?

Left choices = `i-PSI[i]`

Right choices = `NSI[i]-i`

Total subarrays = left × right.

## Complexity

-   Time: O(n)
-   Space: O(n)

## Similar Problems

-   Largest Rectangle in Histogram
-   Sum of Subarray Ranges
-   Trapping Rain Water (stack)
-   Daily Temperatures
-   Next Greater Element I & II
-   Stock Span
-   Remove K Digits
-   Previous/Next Smaller Element

## Common Mistakes

-   Using the same comparison on both sides.
-   Forgetting `1LL`.
-   Using values instead of indices.
-   Wrong sentinel values (`-1` and `n`).
