# Maximum Subarray (Kadane's Algorithm) - Visual Handbook

## Visual Intuition

Think of carrying a **bag** that stores the sum of your current
subarray.

If the bag becomes **negative**, throw it away and start a new one.

Why?

    Current Bag = -6

    Next Number = 8

    Keep bag:
    -6 + 8 = 2

    Start fresh:
    8

Starting fresh is always better.

------------------------------------------------------------------------

## Brute Force (O(n³))

Generate every possible subarray.

    [-2,1,-3]

    Subarrays

    [-2]
    [-2,1]
    [-2,1,-3]

    [1]
    [1,-3]

    [-3]

Compute every sum.

------------------------------------------------------------------------

## Better Brute Force (O(n²))

Fix the left boundary and extend the right boundary.

    i = 0

    -2
    -2+1
    -2+1-3
    ...

    i = 1

    1
    1-3
    ...

Reuse the running sum instead of recomputing.

------------------------------------------------------------------------

# Kadane's Algorithm (O(n))

Algorithm:

``` cpp
sum += nums[i];
best = max(best,sum);

if(sum<0)
    sum=0;
```

------------------------------------------------------------------------

## Complete Visual Walkthrough

Array

    [-2, 1, -3, 4, -1, 2, 1, -5, 4]

    Start

    sum = 0
    best = -INF

### Step 1

    Take -2

    sum = -2
    best = -2

    sum < 0

    Throw away the bag

    sum = 0

------------------------------------------------------------------------

### Step 2

    Take 1

    sum = 1
    best = 1

Keep carrying.

------------------------------------------------------------------------

### Step 3

    Take -3

    sum = -2
    best = 1

    Negative

    Discard

    sum = 0

------------------------------------------------------------------------

### Step 4

    Take 4

    sum = 4
    best = 4

------------------------------------------------------------------------

### Step 5

    Take -1

    sum = 3
    best = 4

Still positive, so continue.

------------------------------------------------------------------------

### Step 6

    Take 2

    sum = 5
    best = 5

------------------------------------------------------------------------

### Step 7

    Take 1

    sum = 6
    best = 6

Maximum found.

------------------------------------------------------------------------

### Step 8

    Take -5

    sum = 1
    best = 6

Still positive.

------------------------------------------------------------------------

### Step 9

    Take 4

    sum = 5
    best = 6

Finished.

Answer

    Maximum Sum = 6

    Subarray

    [4,-1,2,1]

------------------------------------------------------------------------

## Why Reset?

    Current Sum

    <------------- Negative ------------->

    Future Positive Numbers

             5  8  2

Adding a negative prefix always reduces the future sum.

So:

    Negative Prefix

    ↓

    Discard

    ↓

    Start New Subarray

------------------------------------------------------------------------

## All Negative Case

    [-8,-3,-6]

Never return 0.

Initialize

    best = INT_MIN

Update best **before** resetting.

Answer = -3.

------------------------------------------------------------------------

## Complexity

  Approach         Time   Space
  ------------- ------- -------
  Brute Force     O(n³)    O(1)
  Better          O(n²)    O(1)
  Kadane           O(n)    O(1)

------------------------------------------------------------------------

## Similar Problems

-   Maximum Product Subarray
-   Maximum Circular Subarray
-   Best Time to Buy and Sell Stock
-   Maximum Sum Rectangle
-   House Robber

------------------------------------------------------------------------

## Key Notes

-   Kadane is a greedy algorithm.
-   The running sum represents the best subarray ending at the current
    index.
-   Negative prefixes are never useful.
-   Every element is processed exactly once.
