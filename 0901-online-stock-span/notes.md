# Online Stock Span - Complete Handbook

## Problem

For each incoming stock price, return the span: the number of
consecutive days (including today) for which the price has been less
than or equal to today's price.

------------------------------------------------------------------------

# 1. Brute Force

For every new price, scan backwards until a greater price is found.

``` cpp
span = 1;
for(int j=i-1;j>=0 && prices[j]<=prices[i];j--)
    span++;
```

-   **Time:** O(n) per query
-   **Space:** O(1)

For `n` calls:

-   **Total Time:** O(n²)

------------------------------------------------------------------------

# 2. Better Approach

Maintain all previous prices in an array and scan backwards.

This is easier to implement than brute force but still has **O(n)**
worst-case time per query.

------------------------------------------------------------------------

# 3. Optimal Approach - Monotonic Stack

Your solution maintains a **monotonic decreasing stack** storing:

``` cpp
(price, index)
```

``` cpp
while(!st.empty() && st.top().first <= price)
    st.pop();

if(st.empty())
    span = index + 1;
else
    span = index - st.top().second;

st.push({price, index});
```

## Core Idea

The first previous price that is **strictly greater** than the current
price limits the span.

All previous prices that are less than or equal to the current price can
never limit any future span, so they are removed immediately.

------------------------------------------------------------------------

## Why a Monotonic Decreasing Stack?

The stack always satisfies:

    Bottom
    120
    100
    80
    60
    Top

Each element below the top is greater than the one above it.

This means the nearest previous greater price is always on the top after
popping smaller values.

------------------------------------------------------------------------

## Why Store Indices?

The span is the distance between:

-   today's index
-   previous greater price index

If no greater price exists:

    span = currentIndex + 1

Otherwise:

    span = currentIndex - previousGreaterIndex

------------------------------------------------------------------------

## Dry Run

Prices:

    100, 80, 60, 70, 60, 75, 85

    Price Stack After Processing     Span
  ------- ------------------------ ------
      100 100                           1
       80 100,80                        1
       60 100,80,60                     1
       70 100,80,70                     2
       60 100,80,70,60                  1
       75 100,80,75                     4
       85 100,85                        6

Output:

    1 1 1 2 1 4 6

------------------------------------------------------------------------

## Why `<=`?

Equal prices are included in the span.

Example:

    100 100 100

Spans:

    1 2 3

Using `<` would produce incorrect answers.

------------------------------------------------------------------------

## Complexity

Each price is:

-   pushed once
-   popped at most once

Amortized complexity:

-   **Time:** O(1) per call
-   **Total:** O(n)
-   **Space:** O(n)

------------------------------------------------------------------------

# Pattern Recognition

Think of a **Monotonic Stack** when you need:

-   Previous Greater Element
-   Next Greater Element
-   Nearest Smaller Element
-   Boundary computation
-   Online processing with nearest comparisons

------------------------------------------------------------------------

# Similar Problems

## Monotonic Stack

-   Next Greater Element I
-   Next Greater Element II
-   Daily Temperatures
-   Largest Rectangle in Histogram
-   Trapping Rain Water
-   Remove K Digits
-   Sum of Subarray Minimums
-   Asteroid Collision
-   Online Stock Span

## Monotonic Queue

-   Sliding Window Maximum
-   Sliding Window Minimum
-   Jump Game VI
-   Constrained Subsequence Sum

------------------------------------------------------------------------

# Common Mistakes

-   Using `<` instead of `<=`.
-   Storing only values when index is required.
-   Forgetting that the stack must remain decreasing.
-   Assuming worst-case O(n) per query; the amortized cost is O(1).

------------------------------------------------------------------------

# Key Takeaways

-   Maintain a monotonic decreasing stack of `(price, index)`.
-   Remove all prices less than or equal to the current price.
-   The remaining top is the previous greater price.
-   Span equals the distance to the previous greater index.
-   Every element is pushed once and popped once, giving an overall
    **O(n)** solution.
