# Sliding Window Maximum - Monotonic Deque Pattern

## Core Idea

The brute-force approach checks every window independently, resulting in
**O(n × k)** time.

The optimal approach maintains a **monotonic decreasing deque** that
stores **indices**, not values.

The front of the deque always contains the index of the maximum element
of the current window.

## Why Store Indices?

We need to know when an element leaves the current window.

Example:

    nums = [4, 2, 3]
    k = 2

When the window moves from `[4,2]` to `[2,3]`, the index of `4` tells us
it has expired.

## Algorithm

``` cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> res;
    deque<int> dq;

    for (int i = 0; i < nums.size(); i++) {
        int windowStart = i - k + 1;

        while (!dq.empty() && dq.front() < windowStart)
            dq.pop_front();

        while (!dq.empty() && nums[dq.back()] < nums[i])
            dq.pop_back();

        dq.push_back(i);

        if (windowStart >= 0)
            res.push_back(nums[dq.front()]);
    }

    return res;
}
```

## Invariants

-   The deque stores indices inside the current window.
-   Values corresponding to those indices are in decreasing order.
-   The front always stores the maximum element.

## Why Remove Smaller Elements?

When a larger element arrives, any smaller element behind it can never
become the maximum while both remain inside the window.

Example:

    Deque values:
    5 4 2

    Current:
    6

    Deque becomes:
    6

## Complexity

Each index is:

-   pushed once,
-   popped from the front at most once,
-   popped from the back at most once.

Therefore:

-   Time: **O(n)**
-   Space: **O(k)**

## Pattern Recognition

Use a monotonic deque when:

-   the window slides,
-   elements expire from the left,
-   new elements enter from the right,
-   and you need the maximum or minimum efficiently.

Common problems: - Sliding Window Maximum - Sliding Window Minimum -
Jump Game VI - Constrained Subsequence Sum - Longest Continuous Subarray
with Absolute Difference
