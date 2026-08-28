# Maximum Consecutive Ones III — Complete Explanation

## Problem Statement

Given a binary array `nums` and an integer `k`, return the maximum number of consecutive `1`s in the array if you can flip at most `k` zeros.

Example:

```text
Input:
nums = [1, 1, 0, 0, 1, 1, 1, 0]
k = 2

Output:
7
```

---

## Optimal Solution

```cpp
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();

        int left = 0;
        int maxLength = 0;
        int zeroCount = 0;

        for (int right = 0; right < n; right++) {
            if (nums[right] == 0) {
                zeroCount++;
            }

            while (zeroCount > k) {
                if (nums[left] == 0) {
                    zeroCount--;
                }

                left++;
            }

            maxLength = max(
                maxLength,
                right - left + 1
            );
        }

        return maxLength;
    }
};
```

---

# 1. What Does the Problem Really Mean?

The problem says:

> Find the maximum number of consecutive `1`s after flipping at most `k` zeros.

Consider:

```text
nums = [1, 1, 0, 0, 1, 1, 1, 0]
k = 2
```

We can select this contiguous subarray:

```text
[1, 1, 0, 0, 1, 1, 1]
```

It contains two zeros.

Because `k = 2`, both zeros can be flipped:

```text
[1, 1, 1, 1, 1, 1, 1]
```

Therefore, the answer is:

```text
7
```

The most important transformation is:

```text
Maximum consecutive ones after flipping at most k zeros
                            ↓
Longest contiguous subarray containing at most k zeros
```

We do not actually need to modify the array.

We only need to find the longest contiguous window containing at most `k` zeros.

A window is valid when:

```text
number of zeros <= k
```

A window is invalid when:

```text
number of zeros > k
```

---

# 2. Brute-Force Approach

The most direct approach is:

1. Generate every possible subarray.
2. Count the zeros in each subarray.
3. If the number of zeros is at most `k`, update the maximum length.

## Brute-Force Code

```cpp
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int maxLength = 0;

        for (int start = 0; start < n; start++) {
            for (int end = start; end < n; end++) {
                int zeroCount = 0;

                for (int index = start; index <= end; index++) {
                    if (nums[index] == 0) {
                        zeroCount++;
                    }
                }

                if (zeroCount <= k) {
                    maxLength = max(
                        maxLength,
                        end - start + 1
                    );
                }
            }
        }

        return maxLength;
    }
};
```

## How It Works

For the array:

```text
[1, 0, 1]
```

The algorithm checks every possible subarray:

```text
[1]
[1, 0]
[1, 0, 1]
[0]
[0, 1]
[1]
```

For every subarray, it separately counts the number of zeros.

## Time and Space Complexity

There are approximately `O(n²)` possible subarrays.

For every subarray, we may scan up to `O(n)` elements to count the zeros.

Therefore:

```text
Time Complexity:  O(n³)
Space Complexity: O(1)
```

## Problem With This Approach

The same elements are processed repeatedly.

For example, while checking:

```text
[1, 0, 1]
```

we count all the zeros.

Later, while checking:

```text
[0, 1]
```

we count some of those elements again.

This repeated work makes the solution inefficient.

---

# 3. Better Approach — Incremental Zero Counting

We can improve the brute-force solution by avoiding repeated zero counting.

For each starting index:

1. Set `zeroCount = 0`.
2. Move the ending index forward.
3. If the newly added element is zero, increase `zeroCount`.
4. If `zeroCount > k`, stop expanding.
5. Otherwise, update the maximum length.

## Better Approach Code

```cpp
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int maxLength = 0;

        for (int start = 0; start < n; start++) {
            int zeroCount = 0;

            for (int end = start; end < n; end++) {
                if (nums[end] == 0) {
                    zeroCount++;
                }

                if (zeroCount > k) {
                    break;
                }

                maxLength = max(
                    maxLength,
                    end - start + 1
                );
            }
        }

        return maxLength;
    }
};
```

## How Did We Arrive at This Approach?

Suppose we already know the number of zeros in:

```text
nums[start ... end]
```

When we extend the subarray to:

```text
nums[start ... end + 1]
```

we do not need to recount every element.

We only need to check the newly added element:

```cpp
if (nums[end] == 0) {
    zeroCount++;
}
```

This eliminates the innermost loop from the brute-force solution.

## Why Can We Stop When `zeroCount > k`?

For a fixed `start`, suppose:

```text
nums[start ... end]
```

already contains more than `k` zeros.

If we extend `end` further, the number of zeros can:

- Stay the same.
- Increase.

It cannot decrease.

Therefore, all longer subarrays beginning at the same `start` will also be invalid.

That is why we can write:

```cpp
if (zeroCount > k) {
    break;
}
```

## Time and Space Complexity

There are still two nested loops.

Therefore:

```text
Time Complexity:  O(n²)
Space Complexity: O(1)
```

This is better than `O(n³)`, but overlapping subarrays are still processed repeatedly.

---

# 4. Optimal Approach — Sliding Window

We want the longest contiguous subarray satisfying:

```text
number of zeros <= k
```

Because the answer must be contiguous, we can represent the current subarray using two pointers:

```text
left  → beginning of the window
right → ending of the window
```

The current window is:

```text
nums[left ... right]
```

We also maintain:

```cpp
zeroCount
```

which stores the number of zeros inside the current window.

## Sliding-Window Algorithm

For every `right`:

1. Add `nums[right]` to the window.
2. If it is zero, increment `zeroCount`.
3. If `zeroCount > k`, the window is invalid.
4. Move `left` forward until the window becomes valid.
5. Calculate the current valid window length.
6. Update the maximum length.

## Optimal Code

```cpp
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();

        int left = 0;
        int maxLength = 0;
        int zeroCount = 0;

        for (int right = 0; right < n; right++) {
            if (nums[right] == 0) {
                zeroCount++;
            }

            while (zeroCount > k) {
                if (nums[left] == 0) {
                    zeroCount--;
                }

                left++;
            }

            maxLength = max(
                maxLength,
                right - left + 1
            );
        }

        return maxLength;
    }
};
```

---

# 5. Understanding Every Part of the Optimal Code

## The Left Pointer

```cpp
int left = 0;
```

`left` represents the beginning of the current window.

## The Maximum Length

```cpp
int maxLength = 0;
```

This stores the longest valid window found so far.

## The Zero Count

```cpp
int zeroCount = 0;
```

This stores the number of zeros currently present inside the window.

## Expanding the Window

```cpp
for (int right = 0; right < n; right++) {
```

The `right` pointer moves forward and adds new elements to the current window.

## Adding the New Element

```cpp
if (nums[right] == 0) {
    zeroCount++;
}
```

If the newly added element is zero, increase the number of zeros in the window.

## Detecting an Invalid Window

```cpp
while (zeroCount > k) {
```

The window becomes invalid when it contains more than `k` zeros.

## Removing an Element From the Window

```cpp
if (nums[left] == 0) {
    zeroCount--;
}
```

If the element leaving the window is zero, decrease `zeroCount`.

## Moving the Left Pointer

```cpp
left++;
```

This removes the current `nums[left]` from the window.

## Calculating the Window Length

```cpp
right - left + 1
```

The `+1` is required because both `left` and `right` are included in the window.

For example:

```text
left  = 2
right = 5
```

The included indices are:

```text
2, 3, 4, 5
```

Therefore:

```text
length = 5 - 2 + 1
       = 4
```

## Updating the Answer

```cpp
maxLength = max(
    maxLength,
    right - left + 1
);
```

After the shrinking process finishes, the current window is valid.

Therefore, we compare its length with the maximum length found so far.

---

# 6. Complete Dry Run

Consider:

```text
nums = [1, 1, 0, 0, 1, 1, 1]
k = 1
```

Initially:

```text
left = 0
zeroCount = 0
maxLength = 0
```

## Iteration 1

```text
right = 0
nums[right] = 1
```

Window:

```text
[1]
```

Zero count:

```text
0
```

The window is valid.

```text
currentLength = 0 - 0 + 1
              = 1

maxLength = 1
```

## Iteration 2

```text
right = 1
nums[right] = 1
```

Window:

```text
[1, 1]
```

Zero count:

```text
0
```

The window is valid.

```text
currentLength = 1 - 0 + 1
              = 2

maxLength = 2
```

## Iteration 3

```text
right = 2
nums[right] = 0
```

Window:

```text
[1, 1, 0]
```

Zero count:

```text
1
```

Because:

```text
zeroCount <= k
```

the window is valid.

```text
currentLength = 2 - 0 + 1
              = 3

maxLength = 3
```

## Iteration 4

```text
right = 3
nums[right] = 0
```

Window before shrinking:

```text
[1, 1, 0, 0]
```

Zero count:

```text
2
```

Because:

```text
2 > k
```

the window is invalid.

We begin moving `left`.

### Remove Index 0

```text
nums[left] = 1
```

Removing `1` does not change `zeroCount`.

```text
left = 1
zeroCount = 2
```

Window:

```text
[1, 0, 0]
```

It is still invalid.

### Remove Index 1

```text
nums[left] = 1
```

Removing `1` does not change `zeroCount`.

```text
left = 2
zeroCount = 2
```

Window:

```text
[0, 0]
```

It is still invalid.

### Remove Index 2

```text
nums[left] = 0
```

Because a zero is leaving the window:

```text
zeroCount = 1
left = 3
```

Window:

```text
[0]
```

It is now valid.

Current length:

```text
currentLength = 3 - 3 + 1
              = 1
```

Maximum remains:

```text
maxLength = 3
```

## Iteration 5

```text
right = 4
nums[right] = 1
```

Window:

```text
[0, 1]
```

Zero count:

```text
1
```

Current length:

```text
2
```

Maximum remains:

```text
3
```

## Iteration 6

```text
right = 5
nums[right] = 1
```

Window:

```text
[0, 1, 1]
```

Current length:

```text
3
```

Maximum remains:

```text
3
```

## Iteration 7

```text
right = 6
nums[right] = 1
```

Window:

```text
[0, 1, 1, 1]
```

Current length:

```text
4
```

Therefore:

```text
maxLength = 4
```

The final answer is:

```text
4
```

---

# 7. Why Do We Use `while` Instead of `if`?

We use:

```cpp
while (zeroCount > k)
```

instead of:

```cpp
if (zeroCount > k)
```

because moving `left` once may remove a `1`, while the extra zero may still remain inside the window.

Consider:

```text
Window = [1, 1, 0, 1, 0]
k = 1
```

There are two zeros, so the window is invalid.

Move `left` once:

```text
[1, 0, 1, 0]
```

There are still two zeros.

Move `left` again:

```text
[0, 1, 0]
```

There are still two zeros.

Move `left` one more time:

```text
[1, 0]
```

Now there is only one zero.

The window is valid again.

Therefore, we need:

```cpp
while (zeroCount > k)
```

It means:

> Continue shrinking until the window becomes valid again.

---

# 8. Time and Space Complexity of the Optimal Approach

The solution contains a `for` loop and a nested `while` loop:

```cpp
for (...) {
    while (...) {
    }
}
```

At first glance, this may look like `O(n²)`, but it is actually `O(n)`.

The `right` pointer moves only forward:

```text
0 → 1 → 2 → ... → n - 1
```

The `left` pointer also moves only forward:

```text
0 → 1 → 2 → ... → n
```

Neither pointer ever moves backward.

Every element is:

- Added to the window at most once.
- Removed from the window at most once.

Therefore, the total number of pointer movements is at most approximately:

```text
2n
```

Hence:

```text
Time Complexity:  O(n)
Space Complexity: O(1)
```

This type of analysis is known as amortized analysis.

---

# 9. Mental Model for Similar Problems

The sliding-window mental model is:

> Maintain a contiguous window. Expand the right side to include more elements. If the constraint is violated, shrink the left side until the window becomes valid again.

The process is:

```text
Expand right
     ↓
Update the window state
     ↓
Check the constraint
     ↓
Shrink left while invalid
     ↓
Record the answer
```

## Generic Sliding-Window Template

```cpp
int left = 0;
int answer = 0;

for (int right = 0; right < n; right++) {
    // Add nums[right] to the current window state

    while (windowIsInvalid()) {
        // Remove nums[left] from the window state
        left++;
    }

    answer = max(
        answer,
        right - left + 1
    );
}
```

For this problem:

```text
Window state       = number of zeros
Allowed constraint = at most k zeros
Invalid condition  = zeroCount > k
Answer             = maximum valid window length
```

---

# 10. The Budget Mental Model

Think of `k` as a budget.

Every zero costs one unit:

```text
1 → cost 0
0 → cost 1
```

For example:

```text
nums = [1, 0, 1, 0, 1]
cost = [0, 1, 0, 1, 0]
k = 1
```

The window can contain elements whose total cost is at most `1`.

You are looking for:

> The longest contiguous window whose total cost does not exceed the available budget.

This budget model appears in problems involving:

- At most `k` flips.
- At most `k` replacements.
- At most `k` deletions.
- At most `k` distinct values.
- Total cost at most `k`.
- At most `k` unwanted elements.
- At most `k` mismatches.

---

# 11. How We Move From Brute Force to Sliding Window

## Brute-Force Thinking

Generate every subarray:

```text
Choose a starting position
Choose an ending position
Check whether the subarray is valid
```

This performs repeated work.

## First Optimization

Instead of recounting zeros for every subarray, maintain a running count while extending the ending position.

This improves the time complexity:

```text
O(n³) → O(n²)
```

## Important Observation

Suppose we have a window:

```text
nums[left ... right]
```

After adding a new element, the window may become invalid.

Instead of discarding the entire window and restarting from the next index, move `left` forward until the window becomes valid.

This preserves the useful portion of the previous window.

The process becomes:

```text
Expand the window using right.
Shrink the window using left.
Never restart the search from the beginning.
```

Because both pointers move only forward:

```text
Time Complexity = O(n)
```

---

# 12. Important Window Invariant

An invariant is a condition that we intentionally maintain during an algorithm.

After the `while` loop finishes, this solution maintains:

```text
The current window nums[left ... right] contains at most k zeros.
```

In code:

```cpp
while (zeroCount > k) {
    if (nums[left] == 0) {
        zeroCount--;
    }

    left++;
}
```

After this loop:

```text
zeroCount <= k
```

Therefore, before updating `maxLength`, the window is guaranteed to be valid.

This is why the following statement is safe:

```cpp
maxLength = max(
    maxLength,
    right - left + 1
);
```

---

# 13. Similar Problems

Practice these problems in the following order.

## Beginner Level

### 1. LeetCode 485 — Max Consecutive Ones

Find the maximum number of consecutive ones without any flips.

Pattern:

```text
Simple consecutive-element counting
```

### 2. LeetCode 1004 — Max Consecutive Ones III

This is the current problem.

Pattern:

```text
Longest subarray containing at most k zeros
```

### 3. LeetCode 487 — Max Consecutive Ones II

Flip at most one zero.

This is the same pattern with:

```text
k = 1
```

### 4. LeetCode 1493 — Longest Subarray of 1’s After Deleting One Element

Find the longest subarray of ones after deleting exactly one element.

Pattern:

```text
Maintain a window containing at most one zero
```

## Intermediate Level

### 5. LeetCode 904 — Fruit Into Baskets

Find the longest subarray containing at most two distinct values.

Window state:

```text
Frequency map
```

Constraint:

```text
distinct values <= 2
```

### 6. LeetCode 3 — Longest Substring Without Repeating Characters

Find the longest substring without repeating characters.

Window state:

```text
Character frequency map
```

Constraint:

```text
No character frequency should exceed 1
```

### 7. LeetCode 340 — Longest Substring with At Most K Distinct Characters

Window state:

```text
Character frequency map
```

Constraint:

```text
distinct characters <= k
```

### 8. LeetCode 424 — Longest Repeating Character Replacement

Replace at most `k` characters to make all characters inside the window equal.

Constraint:

```text
windowLength - maximumFrequency <= k
```

### 9. LeetCode 1208 — Get Equal Substrings Within Budget

Every character conversion has a cost.

Window state:

```text
Current conversion cost
```

Constraint:

```text
currentCost <= maxCost
```

## Advanced Variations

### 10. LeetCode 209 — Minimum Size Subarray Sum

Find the shortest window whose sum is at least the target.

This is a minimum-window variation.

### 11. LeetCode 713 — Subarray Product Less Than K

Maintain the product of the current window.

Constraint:

```text
product < k
```

### 12. LeetCode 930 — Binary Subarrays With Sum

Count the number of binary subarrays having an exact sum.

This is a counting variation.

### 13. LeetCode 992 — Subarrays with K Different Integers

Count subarrays containing exactly `k` different integers.

It uses:

```text
exactly(k) = atMost(k) - atMost(k - 1)
```

---

# 14. Pattern-Recognition Steps

Use the following steps whenever you read a subarray or substring problem.

## Step 1: Check Whether the Problem Is About a Contiguous Region

Look for words such as:

```text
Subarray
Substring
Consecutive
Continuous
Contiguous
Segment
```

This problem says:

```text
Maximum consecutive 1s
```

Therefore, it is about a contiguous window.

## Step 2: Identify What Is Being Optimized

Look for words such as:

```text
Longest
Maximum
Shortest
Minimum
Count
```

This problem asks for the maximum length.

Therefore, we need to calculate:

```cpp
right - left + 1
```

and maximize it.

## Step 3: Find the Constraint or Budget

Look for phrases such as:

```text
At most k
No more than k
Can replace k elements
Can delete k elements
Can flip k elements
Within a cost of k
```

Here:

```text
Flip at most k zeros
```

Therefore, `k` is the allowed budget.

## Step 4: Translate the Story Into a Mathematical Condition

Do not remain stuck on the story:

```text
I can flip zeros.
```

Translate it into:

```text
The window can contain at most k zeros.
```

Therefore:

```text
Valid window   → zeroCount <= k
Invalid window → zeroCount > k
```

This translation is one of the most important problem-solving steps.

## Step 5: Decide What Window State Must Be Maintained

Ask:

> What information tells me whether the current window is valid?

For this problem:

```cpp
int zeroCount;
```

For other problems, the state may be:

```text
Current sum
Current product
Frequency map
Number of distinct elements
Number of duplicate characters
Replacement cost
Maximum frequency
```

## Step 6: Expand the Window

Move `right` forward:

```cpp
for (int right = 0; right < n; right++) {
```

Add the new element to the window state:

```cpp
if (nums[right] == 0) {
    zeroCount++;
}
```

## Step 7: Identify When the Window Becomes Invalid

For this problem:

```cpp
zeroCount > k
```

This condition tells us when shrinking must begin.

## Step 8: Shrink Until the Window Is Valid

```cpp
while (zeroCount > k) {
    if (nums[left] == 0) {
        zeroCount--;
    }

    left++;
}
```

Do not shrink a fixed number of times.

Shrink until the constraint is satisfied again.

## Step 9: Update the Answer at the Correct Time

For a longest valid window problem:

```cpp
while (window is invalid) {
    shrink the window;
}

answer = max(answer, window length);
```

The answer is updated after the window becomes valid.

For a minimum valid window problem, the structure is usually:

```cpp
while (window is valid) {
    answer = min(answer, window length);
    shrink the window;
}
```

This difference is important.

---

# 15. Maximum Window vs Minimum Window

## Longest Valid Window

When the problem asks for the longest window satisfying a condition:

```cpp
for (int right = 0; right < n; right++) {
    add(nums[right]);

    while (windowIsInvalid()) {
        remove(nums[left]);
        left++;
    }

    answer = max(answer, right - left + 1);
}
```

Examples:

- Longest substring without repeating characters.
- Longest subarray with at most `k` zeros.
- Longest substring with at most `k` distinct characters.

## Minimum Valid Window

When the problem asks for the smallest window satisfying a condition:

```cpp
for (int right = 0; right < n; right++) {
    add(nums[right]);

    while (windowIsValid()) {
        answer = min(answer, right - left + 1);

        remove(nums[left]);
        left++;
    }
}
```

Examples:

- Minimum size subarray sum.
- Minimum window substring.

The major difference is:

```text
Longest valid window:
Shrink while invalid, then update the answer.

Minimum valid window:
Update while valid, then keep shrinking.
```

---

# 16. Questions to Ask Yourself During an Interview

When you suspect sliding window, ask:

```text
1. Is the answer required to be contiguous?

2. Am I finding a longest, shortest or maximum-length segment?

3. Is there an "at most" constraint?

4. Can I maintain the validity of the window incrementally?

5. When I expand right, can the window become invalid?

6. Can I restore validity by moving left forward?

7. Do left and right only move forward?

8. What exact information must I store about the current window?

9. When should I update the answer?

10. Does adding an element change the constraint monotonically?
```

For this problem:

```text
Is it contiguous?
Yes, because the problem asks for consecutive ones.

Is there a budget?
Yes, at most k zero flips.

What must be tracked?
The number of zeros.

When is the window invalid?
When zeroCount > k.

How do we restore validity?
Move left forward and remove elements until zeroCount <= k.

When do we update the answer?
After the window becomes valid.
```

---

# 17. Common Mistakes

## Mistake 1: Moving `left` Directly to `right`

Incorrect:

```cpp
if (zeroCount > k) {
    left = right;
    zeroCount = 1;
}
```

This removes too many useful elements from the window.

We should only remove enough elements to make the window valid again.

Correct:

```cpp
while (zeroCount > k) {
    if (nums[left] == 0) {
        zeroCount--;
    }

    left++;
}
```

## Mistake 2: Using `if` Instead of `while`

Incorrect:

```cpp
if (zeroCount > k) {
    left++;
}
```

One movement may remove a `1`, so the window could remain invalid.

Correct:

```cpp
while (zeroCount > k) {
    if (nums[left] == 0) {
        zeroCount--;
    }

    left++;
}
```

## Mistake 3: Forgetting to Decrement the State

Incorrect:

```cpp
while (zeroCount > k) {
    left++;
}
```

The zero count would no longer represent the actual contents of the window.

Correct:

```cpp
while (zeroCount > k) {
    if (nums[left] == 0) {
        zeroCount--;
    }

    left++;
}
```

## Mistake 4: Updating the Answer Before Restoring Validity

Incorrect:

```cpp
maxLength = max(
    maxLength,
    right - left + 1
);

while (zeroCount > k) {
    // shrink
}
```

This could record an invalid window.

Correct:

```cpp
while (zeroCount > k) {
    // shrink
}

maxLength = max(
    maxLength,
    right - left + 1
);
```

## Mistake 5: Forgetting the `+1`

Incorrect:

```cpp
right - left
```

Correct:

```cpp
right - left + 1
```

Both endpoints are included.

---

# 18. Final Pattern-Recognition Formula

When you see:

```text
Longest or maximum
        +
Contiguous subarray or substring
        +
At most k violations, changes or unwanted elements
```

immediately consider:

```text
Variable-size sliding window
```

Think through these questions:

```text
1. What does my current window represent?

2. What state must I track?

3. What makes the window valid?

4. What makes the window invalid?

5. When should I expand right?

6. When should I shrink left?

7. When should I update the answer?
```

For this problem:

```text
Window:
    nums[left ... right]

State:
    Number of zeros in the window

Valid condition:
    zeroCount <= k

Invalid condition:
    zeroCount > k

Expansion:
    Move right and include nums[right]

Shrinking:
    Move left until zeroCount <= k

Window length:
    right - left + 1

Answer:
    Maximum valid window length
```

The complete mental shortcut is:

```text
Expand right
    ↓
Add the new element to the window state
    ↓
Check whether the budget is exceeded
    ↓
Shrink left until the window becomes valid
    ↓
Update the maximum length
```

That is the complete sliding-window pattern behind **Maximum Consecutive Ones III**.
