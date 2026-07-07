# Next Greater Element II (Circular Array)

## Brute Force

For every index, scan the next `n-1` elements (using modulo for circular
traversal) until a greater element is found.

Time: **O(n²)**, Space: **O(1)**.

## Better Approach

For the non-circular Next Greater Element problem, traverse from right
to left using a **monotonic decreasing stack**: - Remove all smaller or
equal elements. - The stack top becomes the next greater element. - Push
the current value.

This works in **O(n)** but does not handle circular arrays.

## Optimal Approach (Circular Array)

Treat the array as if it were traversed twice.

``` cpp
vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n);
    stack<int> st;

    for (int i = 2*n-1; i >= 0; i--) {
        int idx = i % n;

        while (!st.empty() && st.top() <= nums[idx])
            st.pop();

        if (i < n)
            res[idx] = st.empty() ? -1 : st.top();

        st.push(nums[idx]);
    }

    return res;
}
```

### Why `2*n`?

The second pass allows elements near the end of the array to see
elements at the beginning, simulating circularity.

### Why Right to Left?

When processing an element, all candidates to its right have already
been processed.

### Stack Invariant

The stack always stores values in **strictly decreasing order**. The top
is the nearest greater candidate.

## Complexity

-   Time: **O(n)**
-   Space: **O(n)**

Each element is pushed once and popped at most once.

## Similar Patterns

-   Next Greater Element I
-   Daily Temperatures
-   Stock Span
-   Remove K Digits
-   Largest Rectangle in Histogram
-   Trapping Rain Water
-   Previous Greater/Smaller Element

## Key Notes

-   Traverse from `2*n-1` to `0`.
-   Use `idx = i % n`.
-   Pop all `<=` elements.
-   Answer is recorded only during the first pass (`i < n`).
-   This is a classic **Monotonic Decreasing Stack** problem.
