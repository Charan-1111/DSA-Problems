# Find the First and Last Position of an Element in a Sorted Array

## Problem Statement

You are given:

- A sorted integer array `nums`
- An integer `target`

You must find:

1. The index of the first occurrence of `target`
2. The index of the last occurrence of `target`

Return the answer as:

```cpp
{firstOccurrence, lastOccurrence}
```

If the target does not exist, return:

```cpp
{-1, -1}
```

---

## Example

```text
Input:
nums = [5, 7, 7, 8, 8, 10]
target = 8

Output:
[3, 4]
```

Explanation:

```text
Index:  0  1  2  3  4   5
Array: [5, 7, 7, 8, 8, 10]
                  ↑  ↑
                first last
```

The first occurrence of `8` is at index `3`.

The last occurrence of `8` is at index `4`.

---

# 1. What Does the Problem Really Mean?

The problem is not simply asking:

> Does the target exist?

It is asking two separate questions:

1. Where does the target's range begin?
2. Where does the target's range end?

Consider:

```text
nums = [1, 2, 2, 2, 2, 3, 4]
```

All occurrences of `2` form one continuous range:

```text
Index:  0  1  2  3  4  5  6
Array: [1, 2, 2, 2, 2, 3, 4]
           └────────┘
          target range
```

Therefore:

```text
First occurrence = 1
Last occurrence  = 4
```

A normal binary search may return any one of these positions:

```text
1, 2, 3 or 4
```

But this problem requires the exact left and right boundaries.

---

# 2. Important Observations

## Observation 1: The Array Is Sorted

The sorted property is the strongest clue in this problem.

Because the array is sorted:

- Smaller values occur before the target.
- Larger values occur after the target.
- Duplicate target values stay together.
- We can eliminate half of the array at each step.

This suggests binary search.

---

## Observation 2: Duplicates May Exist

If duplicates exist, finding one occurrence is not sufficient.

For example:

```text
nums   = [2, 2, 2, 2]
target = 2
```

Normal binary search may return:

```text
index = 1
```

But the required answer is:

```text
[0, 3]
```

---

## Observation 3: We Need Two Boundaries

We can divide the original problem into two smaller problems:

```text
Problem 1: Find the first occurrence.
Problem 2: Find the last occurrence.
```

This decomposition makes the solution easier to understand.

---

# 3. Brute-Force Approach

## Idea

Traverse the complete array from left to right.

During traversal:

- When the target is seen for the first time, store its index in `first`.
- Every time the target is found, update `last`.

---

## Step-by-Step Example

```text
nums   = [5, 7, 7, 8, 8, 10]
target = 8
```

Initialize:

```text
first = -1
last  = -1
```

Traverse the array:

```text
Index 0:
nums[0] = 5
5 != 8
No changes

Index 1:
nums[1] = 7
7 != 8
No changes

Index 2:
nums[2] = 7
7 != 8
No changes

Index 3:
nums[3] = 8
Target found for the first time
first = 3
last  = 3

Index 4:
nums[4] = 8
Target found again
last = 4

Index 5:
nums[5] = 10
10 != 8
No changes
```

Final answer:

```text
[3, 4]
```

---

## Brute-Force Code

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = -1;
        int last = -1;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                if (first == -1) {
                    first = i;
                }

                last = i;
            }
        }

        return {first, last};
    }
};
```

---

## Complexity

```text
Time Complexity:  O(n)
Space Complexity: O(1)
```

In the worst case, we examine every element.

---

## Limitation

The brute-force approach does not use the most important property of the input:

```text
The array is sorted.
```

Whenever an array is sorted, we should consider whether binary search can reduce the time complexity.

---

# 4. Better Approach: Binary Search and Expand

## Idea

We can improve the initial search using normal binary search.

The steps are:

1. Use binary search to find any occurrence of the target.
2. From the found position, move left to find the first occurrence.
3. From the found position, move right to find the last occurrence.

---

## Step-by-Step Example

```text
nums   = [5, 7, 7, 8, 8, 10]
target = 8
```

Suppose normal binary search finds `8` at index `4`.

```text
Index:  0  1  2  3  4   5
Array: [5, 7, 7, 8, 8, 10]
                     ↑
                   found
```

Move left:

```text
Index 4 → value is 8
Index 3 → value is 8
Index 2 → value is 7, stop
```

Therefore:

```text
first = 3
```

Move right:

```text
Index 4 → value is 8
Index 5 → value is 10, stop
```

Therefore:

```text
last = 4
```

Final answer:

```text
[3, 4]
```

---

## Better Approach Code

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;
        int found = -1;

        // Find any occurrence using normal binary search.
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                found = mid;
                break;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (found == -1) {
            return {-1, -1};
        }

        int first = found;
        int last = found;

        // Expand toward the left.
        while (first > 0 && nums[first - 1] == target) {
            first--;
        }

        // Expand toward the right.
        while (
            last < static_cast<int>(nums.size()) - 1 &&
            nums[last + 1] == target
        ) {
            last++;
        }

        return {first, last};
    }
};
```

---

## Complexity

Binary search takes:

```text
O(log n)
```

Expanding across all target occurrences takes:

```text
O(k)
```

Here, `k` is the number of times the target appears.

Therefore:

```text
Time Complexity:  O(log n + k)
Space Complexity: O(1)
```

---

## Why Is This Not Optimal?

Consider:

```text
nums   = [2, 2, 2, 2, 2, 2, 2, 2]
target = 2
```

Binary search finds one occurrence in `O(log n)` time.

However, expanding left and right visits nearly every element.

In this case:

```text
k = n
```

Therefore:

```text
O(log n + k)
= O(log n + n)
= O(n)
```

The worst-case time complexity is still linear.

We need to use binary search for both boundaries.

---

# 5. Optimal Approach: Two Modified Binary Searches

The problem requires two boundaries:

```text
First occurrence → left boundary
Last occurrence  → right boundary
```

Therefore, perform:

1. One binary search for the first occurrence.
2. One binary search for the last occurrence.

The important modification is:

> Do not stop immediately when the target is found.

Instead:

1. Save the current position as a possible answer.
2. Continue searching for a better boundary.

---

# 6. Finding the First Occurrence

## Main Idea

When `nums[mid] == target`:

- `mid` is a valid occurrence.
- Save it in `answer`.
- There may be another occurrence at a smaller index.
- Continue searching toward the left.

```cpp
answer = mid;
right = mid - 1;
```

The mental question is:

> I found the target, but can I find the same target at a smaller index?

---

## First Occurrence Algorithm

```text
1. Set left = 0.
2. Set right = n - 1.
3. Set answer = -1.
4. While left <= right:
   a. Calculate mid.
   b. If nums[mid] == target:
      - Save mid in answer.
      - Search toward the left.
   c. If nums[mid] < target:
      - Search toward the right.
   d. If nums[mid] > target:
      - Search toward the left.
5. Return answer.
```

---

## Dry Run: First Occurrence

```text
nums   = [5, 7, 7, 8, 8, 10]
target = 8
```

Initial state:

```text
left   = 0
right  = 5
answer = -1
```

### Iteration 1

```text
mid = left + (right - left) / 2
mid = 0 + (5 - 0) / 2
mid = 2

nums[mid] = nums[2] = 7
```

Since:

```text
7 < 8
```

The target must be on the right:

```text
left = mid + 1
left = 3
```

Current state:

```text
left   = 3
right  = 5
answer = -1
```

### Iteration 2

```text
mid = 3 + (5 - 3) / 2
mid = 4

nums[mid] = nums[4] = 8
```

The target is found.

Save the current position:

```text
answer = 4
```

But there may be another `8` on the left.

Therefore:

```text
right = mid - 1
right = 3
```

Current state:

```text
left   = 3
right  = 3
answer = 4
```

### Iteration 3

```text
mid = 3 + (3 - 3) / 2
mid = 3

nums[mid] = nums[3] = 8
```

The target is found again at a smaller index.

Update:

```text
answer = 3
```

Continue searching toward the left:

```text
right = mid - 1
right = 2
```

Now:

```text
left  = 3
right = 2
```

Since:

```text
left > right
```

The loop stops.

Final first occurrence:

```text
3
```

---

## First Occurrence Code

```cpp
int firstOccurrence(vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    int answer = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            answer = mid;

            // Search for a smaller valid index.
            right = mid - 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return answer;
}
```

---

# 7. Finding the Last Occurrence

## Main Idea

When `nums[mid] == target`:

- `mid` is a valid occurrence.
- Save it in `answer`.
- There may be another occurrence at a larger index.
- Continue searching toward the right.

```cpp
answer = mid;
left = mid + 1;
```

The mental question is:

> I found the target, but can I find the same target at a larger index?

---

## Last Occurrence Algorithm

```text
1. Set left = 0.
2. Set right = n - 1.
3. Set answer = -1.
4. While left <= right:
   a. Calculate mid.
   b. If nums[mid] == target:
      - Save mid in answer.
      - Search toward the right.
   c. If nums[mid] < target:
      - Search toward the right.
   d. If nums[mid] > target:
      - Search toward the left.
5. Return answer.
```

---

## Dry Run: Last Occurrence

```text
nums   = [5, 7, 7, 8, 8, 10]
target = 8
```

Initial state:

```text
left   = 0
right  = 5
answer = -1
```

### Iteration 1

```text
mid = 2
nums[mid] = 7
```

Since:

```text
7 < 8
```

Search toward the right:

```text
left = mid + 1
left = 3
```

### Iteration 2

```text
left  = 3
right = 5
mid   = 4

nums[mid] = 8
```

Save the current valid position:

```text
answer = 4
```

There may be another `8` on the right.

Therefore:

```text
left = mid + 1
left = 5
```

### Iteration 3

```text
left  = 5
right = 5
mid   = 5

nums[mid] = 10
```

Since:

```text
10 > 8
```

Search toward the left:

```text
right = mid - 1
right = 4
```

Now:

```text
left  = 5
right = 4
```

The loop stops.

Final last occurrence:

```text
4
```

---

## Last Occurrence Code

```cpp
int lastOccurrence(vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    int answer = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            answer = mid;

            // Search for a larger valid index.
            left = mid + 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return answer;
}
```

---

# 8. Complete Optimal Solution

```cpp
class Solution {
public:
    int firstOccurrence(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;
        int answer = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                answer = mid;

                // Continue searching toward the left.
                right = mid - 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return answer;
    }

    int lastOccurrence(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;
        int answer = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                answer = mid;

                // Continue searching toward the right.
                left = mid + 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return answer;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int first = firstOccurrence(nums, target);

        // If there is no first occurrence, the target is absent.
        if (first == -1) {
            return {-1, -1};
        }

        int last = lastOccurrence(nums, target);

        return {first, last};
    }
};
```

---

# 9. Explanation of the Given Solution

The original solution contains three functions:

```cpp
first_occurance()
last_occurance()
searchRange()
```

## `first_occurance()`

This function finds the leftmost occurrence of the target.

```cpp
if (nums[mid] == target) {
    ans = mid;
    r = mid - 1;
}
```

When the target is found:

- `mid` is stored in `ans`.
- The search continues toward the left.
- If another target exists at a smaller index, `ans` is updated.

---

## `last_occurance()`

This function finds the rightmost occurrence of the target.

```cpp
if (nums[mid] == target) {
    ans = mid;
    l = mid + 1;
}
```

When the target is found:

- `mid` is stored in `ans`.
- The search continues toward the right.
- If another target exists at a larger index, `ans` is updated.

---

## `searchRange()`

This function combines the two answers:

```cpp
int fst = first_occurance(nums, target);
int lst = last_occurance(nums, target);
```

It returns:

```cpp
{fst, lst}
```

If the target is missing, both functions return `-1`, producing:

```cpp
{-1, -1}
```

---

# 10. Why Does the Optimal Solution Work?

For the first occurrence:

```text
When nums[mid] == target:
    Save mid
    Search left
```

For the last occurrence:

```text
When nums[mid] == target:
    Save mid
    Search right
```

The `answer` variable preserves the last valid position found.

Even if the next search does not find another occurrence, the saved answer remains correct.

For example:

```text
nums   = [1, 2, 3, 4, 5]
target = 3
```

Suppose we find `3` at index `2`.

For the first occurrence:

```text
answer = 2
Search left
No other 3 is found
Return saved answer 2
```

For the last occurrence:

```text
answer = 2
Search right
No other 3 is found
Return saved answer 2
```

Result:

```text
[2, 2]
```

---

# 11. Complexity Analysis

We perform two binary searches.

First occurrence:

```text
O(log n)
```

Last occurrence:

```text
O(log n)
```

Total:

```text
O(log n) + O(log n)
= O(2 log n)
= O(log n)
```

Big-O notation ignores constant factors.

Therefore:

```text
Time Complexity:  O(log n)
Space Complexity: O(1)
```

---

# 12. Comparison of Approaches

| Approach | Method | Time Complexity | Space Complexity |
|---|---|---:|---:|
| Brute force | Traverse the complete array | `O(n)` | `O(1)` |
| Better | Binary search, then expand | `O(log n + k)` | `O(1)` |
| Optimal | Two modified binary searches | `O(log n)` | `O(1)` |

Here, `k` is the number of target occurrences.

---

# 13. Alternative Solution Using `lower_bound` and `upper_bound`

C++ provides two useful standard-library functions:

```cpp
lower_bound()
upper_bound()
```

## `lower_bound`

`lower_bound` returns the first position where:

```text
value >= target
```

## `upper_bound`

`upper_bound` returns the first position where:

```text
value > target
```

Therefore:

```text
First occurrence = lower_bound(target)
Last occurrence  = upper_bound(target) - 1
```

---

## Example

```text
nums   = [5, 7, 7, 8, 8, 10]
target = 8
```

The first value greater than or equal to `8` is:

```text
Index 3
```

Therefore:

```text
lower_bound(8) = 3
```

The first value greater than `8` is `10`:

```text
Index 5
```

Therefore:

```text
upper_bound(8) = 5
```

The last occurrence is:

```text
upper_bound(8) - 1
= 5 - 1
= 4
```

Final answer:

```text
[3, 4]
```

---

## STL Solution

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first =
            lower_bound(nums.begin(), nums.end(), target) - nums.begin();

        if (
            first == static_cast<int>(nums.size()) ||
            nums[first] != target
        ) {
            return {-1, -1};
        }

        int last =
            upper_bound(nums.begin(), nums.end(), target) -
            nums.begin() -
            1;

        return {first, last};
    }
};
```

Complexity:

```text
Time Complexity:  O(log n)
Space Complexity: O(1)
```

---

# 14. Mental Model

The best mental model for this problem is:

> Find a valid answer, save it, and continue searching for a better answer.

A normal binary search asks:

```text
Does this target exist?
```

A boundary binary search asks:

```text
Where does the valid region begin or end?
```

---

## Mental Model for the First Occurrence

```text
I found the target.
This is a possible answer.
Save the current index.
A smaller valid index may exist.
Continue searching toward the left.
```

Code:

```cpp
answer = mid;
right = mid - 1;
```

---

## Mental Model for the Last Occurrence

```text
I found the target.
This is a possible answer.
Save the current index.
A larger valid index may exist.
Continue searching toward the right.
```

Code:

```cpp
answer = mid;
left = mid + 1;
```

---

## Short Memory Rule

```text
First occurrence → Save and go left
Last occurrence  → Save and go right
```

---

# 15. General Boundary Binary Search Template

Many binary-search problems are not asking whether an element exists.

They are asking for a boundary.

Examples:

```text
First occurrence
Last occurrence
First value >= target
First value > target
Last value <= target
Last value < target
Minimum valid answer
Maximum valid answer
```

A general template is:

```cpp
int answer = -1;

while (left <= right) {
    int mid = left + (right - left) / 2;

    if (mid is a valid answer) {
        answer = mid;

        if (we need a smaller answer) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    } else {
        // Eliminate the impossible half.
    }
}
```

---

# 16. How to Recognize This Pattern

## Signal 1: The Input Is Sorted

Look for words such as:

```text
sorted array
increasing order
non-decreasing order
sorted sequence
```

A sorted search space suggests binary search.

---

## Signal 2: The Problem Asks for a Position

Look for words such as:

```text
first position
last position
earliest occurrence
latest occurrence
leftmost position
rightmost position
insertion position
```

These indicate boundary binary search.

---

## Signal 3: Duplicate Values Are Present

If duplicates are possible, normal binary search may return any occurrence.

If the exact first or last occurrence is required, you must continue searching after finding the target.

---

## Signal 4: The Expected Complexity Is `O(log n)`

If the array is sorted and the problem expects `O(log n)`, binary search is almost certainly required.

---

## Signal 5: The Problem Asks for the Smallest or Largest Valid Answer

Phrases such as these suggest modified binary search:

```text
minimum possible
maximum possible
smallest value satisfying
largest value satisfying
first valid
last valid
```

---

# 17. How to Arrive at the Correct Pattern

Do not begin by trying to remember the entire code.

Derive it one decision at a time.

## Step 1: Recognize That the Array Is Sorted

Ask:

```text
Can I eliminate half of the search space?
```

Yes.

Therefore, binary search is useful.

---

## Step 2: Understand What Normal Binary Search Gives

Normal binary search gives:

```text
Any occurrence of the target
```

But the problem needs:

```text
The first and last occurrences
```

Therefore, normal binary search is not sufficient.

---

## Step 3: Split the Problem Into Two Smaller Problems

Think:

```text
Question 1: Where does the target range begin?
Question 2: Where does the target range end?
```

Now each subproblem has a clear goal.

---

## Step 4: Do Not Return Immediately After Finding the Target

Instead of:

```cpp
if (nums[mid] == target) {
    return mid;
}
```

Store the current answer:

```cpp
answer = mid;
```

---

## Step 5: Decide What “Better” Means

For the first occurrence:

```text
A better answer means a smaller index.
Search toward the left.
```

For the last occurrence:

```text
A better answer means a larger index.
Search toward the right.
```

---

## Step 6: Continue Until the Search Space Is Empty

The saved answer will contain the best boundary found.

If the target was never found:

```text
answer remains -1
```

---

# 18. Questions to Ask While Solving

When reading a binary-search problem, ask:

1. Is the input sorted?
2. Is there a monotonic condition?
3. Am I looking for a value or a boundary?
4. Can duplicates exist?
5. If I find a valid answer, should I stop?
6. Can a better answer exist on the left?
7. Can a better answer exist on the right?
8. Do I need the smallest valid answer?
9. Do I need the largest valid answer?
10. Should I save the current answer before continuing?

For this problem:

```text
Is the array sorted?
Yes.

Can duplicates exist?
Yes.

Do I need any occurrence?
No.

Do I need boundaries?
Yes.

How many boundaries?
Two.

For the first occurrence, where should I continue?
Left.

For the last occurrence, where should I continue?
Right.
```

---

# 19. Common Mistakes

## Mistake 1: Returning Immediately

Incorrect:

```cpp
if (nums[mid] == target) {
    return mid;
}
```

This returns an arbitrary occurrence.

Correct for the first occurrence:

```cpp
if (nums[mid] == target) {
    answer = mid;
    right = mid - 1;
}
```

Correct for the last occurrence:

```cpp
if (nums[mid] == target) {
    answer = mid;
    left = mid + 1;
}
```

---

## Mistake 2: Forgetting to Save the Answer

Incorrect:

```cpp
if (nums[mid] == target) {
    right = mid - 1;
}
```

If we continue searching without saving `mid`, we may lose a valid answer.

Correct:

```cpp
answer = mid;
right = mid - 1;
```

---

## Mistake 3: Moving in the Wrong Direction

For the first occurrence:

```cpp
right = mid - 1;
```

For the last occurrence:

```cpp
left = mid + 1;
```

Remember:

```text
First → Left
Last  → Right
```

---

## Mistake 4: Using Linear Expansion and Calling It `O(log n)`

Finding one occurrence takes `O(log n)`, but expanding through duplicates may take `O(n)`.

Therefore, binary search followed by expansion is not guaranteed to be `O(log n)`.

---

## Mistake 5: Unsafe Midpoint Calculation

Avoid:

```cpp
int mid = (left + right) / 2;
```

For extremely large indices, `left + right` might overflow.

Prefer:

```cpp
int mid = left + (right - left) / 2;
```

---

## Mistake 6: Mishandling an Empty Array

Use an integer for `right`:

```cpp
int right = static_cast<int>(nums.size()) - 1;
```

For an empty array:

```text
right = -1
left  = 0
```

Therefore, the loop does not run and the function returns `-1`.

---

# 20. Edge Cases

## Empty Array

```text
nums   = []
target = 5

Answer = [-1, -1]
```

---

## Target Is Missing

```text
nums   = [1, 2, 3, 4]
target = 5

Answer = [-1, -1]
```

---

## One Element and Target Exists

```text
nums   = [5]
target = 5

Answer = [0, 0]
```

---

## One Element and Target Is Missing

```text
nums   = [5]
target = 2

Answer = [-1, -1]
```

---

## Every Element Is the Target

```text
nums   = [2, 2, 2, 2]
target = 2

Answer = [0, 3]
```

---

## Target Appears Once

```text
nums   = [1, 2, 3, 4, 5]
target = 3

Answer = [2, 2]
```

---

## Target Is at the Beginning

```text
nums   = [2, 2, 3, 4, 5]
target = 2

Answer = [0, 1]
```

---

## Target Is at the End

```text
nums   = [1, 2, 3, 5, 5]
target = 5

Answer = [3, 4]
```

---

# 21. Similar Problems

## Directly Related Problems

1. Find the first occurrence of an element.
2. Find the last occurrence of an element.
3. Count occurrences in a sorted array.
4. Find the floor of a target.
5. Find the ceil of a target.
6. Find the insertion position.
7. Implement `lower_bound`.
8. Implement `upper_bound`.

---

## Count Occurrences

Once the first and last occurrences are known:

```text
count = last - first + 1
```

Example:

```text
first = 3
last  = 6

count = 6 - 3 + 1
count = 4
```

If the target is absent:

```text
count = 0
```

Code:

```cpp
int countOccurrences(vector<int>& nums, int target) {
    int first = firstOccurrence(nums, target);

    if (first == -1) {
        return 0;
    }

    int last = lastOccurrence(nums, target);

    return last - first + 1;
}
```

---

## Recommended LeetCode Problems

```text
LeetCode 704  — Binary Search
LeetCode 35   — Search Insert Position
LeetCode 34   — Find First and Last Position
LeetCode 69   — Sqrt(x)
LeetCode 278  — First Bad Version
LeetCode 153  — Find Minimum in Rotated Sorted Array
LeetCode 33   — Search in Rotated Sorted Array
LeetCode 162  — Find Peak Element
LeetCode 875  — Koko Eating Bananas
LeetCode 1011 — Capacity to Ship Packages Within D Days
LeetCode 1283 — Find the Smallest Divisor Given a Threshold
```

---

# 22. Pattern Practice Progression

## Level 1: Normal Binary Search

Goal:

```text
Learn how to find whether an element exists.
```

Practice:

```text
Binary Search
Search Insert Position
```

---

## Level 2: Boundary Binary Search

Goal:

```text
Learn how to find the first or last valid position.
```

Practice:

```text
First occurrence
Last occurrence
Count occurrences
Find First and Last Position
```

---

## Level 3: Lower Bound and Upper Bound

Goal:

```text
Learn where a condition begins or stops.
```

Practice:

```text
First value >= target
First value > target
Last value <= target
Last value < target
Floor and ceil
```

---

## Level 4: Binary Search on the Answer

Goal:

```text
Find the minimum or maximum value satisfying a condition.
```

Practice:

```text
Koko Eating Bananas
Capacity to Ship Packages
Allocate Minimum Pages
Aggressive Cows
Minimum Days to Make Bouquets
```

---

# 23. Final Summary

When you see:

```text
Sorted array + duplicates + first/last position
```

Think:

```text
Boundary binary search
```

Split the problem:

```text
First occurrence:
    Find the target
    Save the index
    Continue left

Last occurrence:
    Find the target
    Save the index
    Continue right
```

The most important lesson is:

> In boundary binary search, finding a valid answer does not mean the search is finished. Save it and continue searching for a better boundary.

Use this short memory cue:

```text
First → save and go left
Last  → save and go right
```
