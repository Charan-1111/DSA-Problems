# Find the Smallest Letter Greater Than the Target

## Problem Statement

You are given:

- A character array `letters`
- The array is sorted in non-decreasing order
- A character called `target`

You must return the smallest character in `letters` that is strictly greater than `target`.

The letters wrap around.

This means:

- If a greater letter exists, return the smallest such letter.
- If no letter is greater than the target, return the first letter in the array.

---

## Example 1

```text
letters = ['c', 'f', 'j']
target  = 'a'
```

The letters greater than `'a'` are:

```text
'c', 'f', 'j'
```

The smallest one is:

```text
'c'
```

Therefore:

```text
Answer = 'c'
```

---

## Example 2

```text
letters = ['c', 'f', 'j']
target  = 'c'
```

The problem asks for a letter strictly greater than `'c'`.

Therefore, `'c'` itself cannot be returned.

The letters greater than `'c'` are:

```text
'f', 'j'
```

The smallest one is:

```text
'f'
```

Therefore:

```text
Answer = 'f'
```

---

## Example 3

```text
letters = ['c', 'f', 'j']
target  = 'j'
```

There is no letter greater than `'j'`.

Because the letters wrap around, return the first letter:

```text
Answer = 'c'
```

---

## Example 4

```text
letters = ['c', 'f', 'j']
target  = 'k'
```

There is no letter greater than `'k'`.

Therefore, wrap around and return:

```text
Answer = 'c'
```

---

# 1. What Does the Problem Really Mean?

The problem is asking us to find:

> The first element in the sorted array that is strictly greater than the target.

The word **strictly** is very important.

We need:

```text
letters[i] > target
```

We do not need:

```text
letters[i] >= target
```

For example:

```text
letters = ['c', 'f', 'j']
target  = 'c'
```

Since the condition is:

```text
letter > target
```

The letter `'c'` is not a valid answer because:

```text
'c' > 'c' is false
```

The next valid letter is:

```text
'f'
```

---

## Another Way to Describe the Problem

The problem is asking us to find the **upper bound** of the target.

The upper bound means:

> The first position containing a value strictly greater than the target.

Therefore:

```text
next greatest letter = upper_bound(target)
```

---

## Understanding Character Comparison

Characters can be compared just like numbers.

For lowercase English letters:

```text
'a' < 'b' < 'c' < ... < 'z'
```

For example:

```cpp
'a' < 'c'   // true
'f' > 'd'   // true
'j' > 'j'   // false
```

So binary search can compare characters directly:

```cpp
if (letters[mid] > target)
```

---

# 2. Important Observations

## Observation 1: The Array Is Sorted

The characters are arranged in non-decreasing order.

For example:

```text
['c', 'f', 'j']
```

or:

```text
['c', 'c', 'f', 'j', 'j']
```

Because the array is sorted, once we encounter a character greater than the target, all characters after it will also be greater than the target.

For example:

```text
letters = ['a', 'c', 'f', 'h', 'k']
target  = 'e'
```

The comparison pattern is:

```text
'a' > 'e' → false
'c' > 'e' → false
'f' > 'e' → true
'h' > 'e' → true
'k' > 'e' → true
```

This creates a pattern:

```text
false, false, true, true, true
```

The required answer is the first `true`.

That is a strong binary-search pattern.

---

## Observation 2: The Comparison Is Strict

The required condition is:

```text
letters[i] > target
```

Not:

```text
letters[i] >= target
```

This difference determines whether we are implementing:

```text
Lower bound → first value >= target
Upper bound → first value > target
```

This problem requires an upper bound.

---

## Observation 3: Duplicate Letters May Exist

Consider:

```text
letters = ['c', 'c', 'f', 'f', 'j']
target  = 'c'
```

We cannot return either occurrence of `'c'` because the answer must be strictly greater.

The correct answer is:

```text
'f'
```

Our solution must skip all values equal to the target.

---

## Observation 4: The Array Wraps Around

If no element satisfies:

```text
letters[i] > target
```

we return:

```text
letters[0]
```

For example:

```text
letters = ['c', 'f', 'j']
target  = 'j'
```

No valid character exists after `'j'`, so we wrap around:

```text
'j' → 'c'
```

The answer is:

```text
'c'
```

---

# 3. Brute-Force Approach

## Idea

Check every element in the array and keep track of the smallest letter that is greater than the target.

Because we are treating this as a basic brute-force approach, we scan the complete array even after finding a possible answer.

---

## Step-by-Step Example

```text
letters = ['c', 'f', 'j']
target  = 'd'
```

Initialize:

```text
answerFound = false
answer      = letters[0]
```

Check every letter:

```text
'c' > 'd' → false
'f' > 'd' → true
'j' > 'd' → true
```

Between `'f'` and `'j'`, the smaller valid letter is:

```text
'f'
```

Therefore:

```text
Answer = 'f'
```

---

## Brute-Force Code

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        char answer = letters[0];
        bool found = false;

        for (char letter : letters) {
            if (letter > target) {
                if (!found || letter < answer) {
                    answer = letter;
                    found = true;
                }
            }
        }

        // If no greater letter exists, answer remains letters[0].
        return answer;
    }
};
```

---

## Complexity

```text
Time Complexity:  O(n)
Space Complexity: O(1)
```

We examine every letter in the array.

---

## Limitation

This approach does not use the fact that the array is sorted.

Because the array is sorted, we do not need to compare all valid letters to find the smallest one.

The first valid letter is automatically the smallest valid letter.

---

# 4. Better Approach: Linear Search With Early Return

## How Do We Improve the Brute-Force Approach?

We know that the array is sorted.

Therefore, while scanning from left to right:

- Letters appear from smaller to larger.
- The first letter greater than the target is automatically the smallest greater letter.
- We can return it immediately.

We do not need to scan the remaining array.

---

## Step-by-Step Reasoning

Suppose:

```text
letters = ['a', 'c', 'f', 'h', 'k']
target  = 'e'
```

We scan from left to right:

```text
'a' > 'e' → false
'c' > 'e' → false
'f' > 'e' → true
```

As soon as we reach `'f'`, we can return it.

Why?

Because the array is sorted:

```text
'f' <= 'h' <= 'k'
```

Any later valid character will be greater than or equal to `'f'`.

Therefore, `'f'` is the smallest valid answer.

---

## Better Approach Code

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        for (char letter : letters) {
            if (letter > target) {
                return letter;
            }
        }

        // No greater letter exists, so wrap around.
        return letters[0];
    }
};
```

---

## Complexity

### Best Case

If the first letter is greater than the target:

```text
Time Complexity: O(1)
```

### Worst Case

If the answer is near the end or no valid answer exists:

```text
Time Complexity: O(n)
```

Overall:

```text
Time Complexity:  O(n)
Space Complexity: O(1)
```

---

## Why Is This Better Than the Basic Brute Force?

The basic brute-force solution always scans every element.

The improved linear solution returns as soon as it finds the first valid character.

However, its worst-case complexity remains:

```text
O(n)
```

Since the array is sorted, we can improve it further using binary search.

---

# 5. Optimal Approach: Binary Search for the First Greater Letter

## Main Idea

We need to find:

```text
The first index where letters[index] > target
```

This is a boundary binary-search problem.

During binary search:

- If `letters[mid] > target`, then `mid` is a valid answer.
- However, a smaller valid index may exist on the left.
- Save `mid` and continue searching toward the left.

Otherwise:

- If `letters[mid] <= target`, then `mid` is not valid.
- Everything to the left is also less than or equal to the target.
- Search toward the right.

---

# 6. How We Arrive at the Optimal Solution

## Step 1: Identify the Required Condition

A letter is a valid answer when:

```cpp
letters[index] > target
```

---

## Step 2: Use the Sorted Nature of the Array

Consider:

```text
letters = ['a', 'c', 'f', 'h', 'k']
target  = 'e'
```

The validity of each index is:

```text
'a' > 'e' → false
'c' > 'e' → false
'f' > 'e' → true
'h' > 'e' → true
'k' > 'e' → true
```

So the search space looks like:

```text
false false true true true
            ↑
       first valid
```

We are looking for the boundary where the answers change from:

```text
false → true
```

---

## Step 3: Decide What to Do When `letters[mid] > target`

Suppose:

```cpp
letters[mid] > target
```

This means `mid` is a valid position.

But we need the first valid position.

There may be another valid character at a smaller index.

Therefore:

```cpp
result = mid;
right = mid - 1;
```

We:

1. Save the current valid index.
2. Continue searching toward the left.

---

## Step 4: Decide What to Do When `letters[mid] <= target`

Suppose:

```cpp
letters[mid] <= target
```

Then `mid` cannot be the answer.

Because the array is sorted, every index to the left of `mid` also contains a value less than or equal to `letters[mid]`.

Therefore, none of those positions can contain the first letter greater than the target.

We eliminate the left half:

```cpp
left = mid + 1;
```

---

## Step 5: Handle Wrap-Around

If no letter greater than the target is found, `result` remains:

```text
-1
```

In that case, return:

```cpp
letters[0]
```

Otherwise, return:

```cpp
letters[result]
```

---

# 7. Dry Run of the Optimal Solution

Consider:

```text
letters = ['c', 'f', 'j']
target  = 'c'
```

Initial values:

```text
left   = 0
right  = 2
result = -1
```

---

## Iteration 1

Calculate `mid`:

```text
mid = left + (right - left) / 2
mid = 0 + (2 - 0) / 2
mid = 1
```

The middle letter is:

```text
letters[1] = 'f'
```

Check:

```text
'f' > 'c' → true
```

Therefore, index `1` is a valid answer.

Save it:

```text
result = 1
```

But a smaller valid index might exist on the left.

Continue left:

```text
right = mid - 1
right = 0
```

Current state:

```text
left   = 0
right  = 0
result = 1
```

---

## Iteration 2

Calculate `mid`:

```text
mid = 0 + (0 - 0) / 2
mid = 0
```

The middle letter is:

```text
letters[0] = 'c'
```

Check:

```text
'c' > 'c' → false
```

Because equality is not allowed, index `0` is not valid.

Search toward the right:

```text
left = mid + 1
left = 1
```

Now:

```text
left  = 1
right = 0
```

The loop stops.

The saved result is:

```text
result = 1
```

Therefore:

```text
letters[result] = letters[1] = 'f'
```

Final answer:

```text
'f'
```

---

# 8. Dry Run When Wrap-Around Is Required

Consider:

```text
letters = ['c', 'f', 'j']
target  = 'j'
```

Initial state:

```text
left   = 0
right  = 2
result = -1
```

---

## Iteration 1

```text
mid = 1
letters[mid] = 'f'
```

Check:

```text
'f' > 'j' → false
```

Search right:

```text
left = 2
```

---

## Iteration 2

```text
left  = 2
right = 2
mid   = 2

letters[mid] = 'j'
```

Check:

```text
'j' > 'j' → false
```

Equality is not valid, so search right:

```text
left = 3
```

Now:

```text
left  = 3
right = 2
```

The loop stops.

No valid index was found:

```text
result = -1
```

Therefore, wrap around and return:

```text
letters[0] = 'c'
```

Final answer:

```text
'c'
```

---

# 9. Complete Optimal Solution

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int left = 0;
        int right = static_cast<int>(letters.size()) - 1;
        int result = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (letters[mid] > target) {
                // mid is a valid answer.
                result = mid;

                // Search for a smaller valid index.
                right = mid - 1;
            } else {
                // letters[mid] <= target, so it is not valid.
                left = mid + 1;
            }
        }

        // If there is no greater letter, wrap around.
        return result == -1 ? letters[0] : letters[result];
    }
};
```

---

# 10. Explanation of the Given Code

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int l = 0, r = letters.size()-1;

        int res = -1;

        while(l <= r) {
            int mid = l + ((r-l) >> 1);

            if(letters[mid] > target) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        return res == -1 ? letters[0] : letters[res];
    } 
};
```

---

## Initial Search Space

```cpp
int l = 0;
int r = letters.size() - 1;
```

Here:

```text
l → left boundary
r → right boundary
```

Initially, the entire array is the search space.

---

## Result Variable

```cpp
int res = -1;
```

`res` stores the index of the best valid answer found so far.

The value `-1` means:

```text
No letter greater than the target has been found yet.
```

---

## Midpoint Calculation

```cpp
int mid = l + ((r - l) >> 1);
```

The expression:

```cpp
(r - l) >> 1
```

means:

```cpp
(r - l) / 2
```

because shifting a non-negative integer one bit to the right divides it by `2`.

Therefore:

```cpp
int mid = l + ((r - l) >> 1);
```

is equivalent to:

```cpp
int mid = l + (r - l) / 2;
```

The division form is usually easier to read:

```cpp
int mid = l + (r - l) / 2;
```

---

## When the Middle Letter Is Valid

```cpp
if (letters[mid] > target) {
    res = mid;
    r = mid - 1;
}
```

If:

```text
letters[mid] > target
```

then `mid` is a possible answer.

We save it:

```cpp
res = mid;
```

But we need the smallest letter greater than the target.

Since the array is sorted, the smallest valid letter will be at the first valid index.

Therefore, we continue searching toward the left:

```cpp
r = mid - 1;
```

---

## When the Middle Letter Is Not Valid

```cpp
else {
    l = mid + 1;
}
```

This branch means:

```text
letters[mid] <= target
```

The current letter cannot be the answer.

Since the array is sorted, all letters to the left are also less than or equal to the target.

Therefore, we eliminate the left half:

```cpp
l = mid + 1;
```

---

## Returning the Answer

```cpp
return res == -1 ? letters[0] : letters[res];
```

This is a ternary expression.

It is equivalent to:

```cpp
if (res == -1) {
    return letters[0];
}

return letters[res];
```

If `res == -1`:

```text
No greater character exists.
```

Therefore, wrap around and return:

```cpp
letters[0]
```

Otherwise, return the saved valid character:

```cpp
letters[res]
```

---

# 11. Why Does the Optimal Solution Work?

The array can be viewed as two regions.

For a given target:

```text
Invalid region: letters[i] <= target
Valid region:   letters[i] > target
```

For example:

```text
letters = ['a', 'c', 'f', 'h', 'k']
target  = 'e'
```

The regions are:

```text
['a', 'c'] ['f', 'h', 'k']
 invalid       valid
```

Or as Boolean values:

```text
false false true true true
            ↑
      required boundary
```

Binary search finds the first index in the valid region.

Whenever the middle is valid:

```text
Save it and search left.
```

Whenever the middle is invalid:

```text
Search right.
```

This eventually gives the leftmost valid position.

---

# 12. Binary-Search Invariant

A useful invariant for this solution is:

```text
Every index before left has already been proven invalid.
result stores the smallest valid index found so far.
```

When:

```cpp
letters[mid] <= target
```

we know all indices from `left` through `mid` are invalid, so:

```cpp
left = mid + 1;
```

When:

```cpp
letters[mid] > target
```

`mid` is valid, so we save it.

However, an earlier valid index may exist, so:

```cpp
right = mid - 1;
```

When the loop finishes, `result` is either:

- The first valid index, or
- `-1` if no valid index exists.

---

# 13. Complexity Analysis

At every iteration, binary search removes approximately half of the remaining search space.

For an array of size `n`:

```text
n
n / 2
n / 4
n / 8
...
1
```

The number of divisions required is approximately:

```text
log₂(n)
```

Therefore:

```text
Time Complexity:  O(log n)
Space Complexity: O(1)
```

No additional data structure is used.

---

# 14. Comparison of All Approaches

| Approach | Idea | Time Complexity | Space Complexity |
|---|---|---:|---:|
| Brute force | Scan everything and track the smallest valid letter | `O(n)` | `O(1)` |
| Better | Scan left to right and return the first valid letter | `O(n)` | `O(1)` |
| Optimal | Binary search for the first letter greater than target | `O(log n)` | `O(1)` |

---

# 15. Alternative Optimal Solution Using `upper_bound`

C++ provides `upper_bound` in the standard library.

`upper_bound` returns an iterator pointing to:

> The first element strictly greater than the given target.

This is exactly what the problem requires.

---

## Code Using `upper_bound`

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        auto position =
            upper_bound(letters.begin(), letters.end(), target);

        if (position == letters.end()) {
            return letters[0];
        }

        return *position;
    }
};
```

---

## Compact Version

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        auto position =
            upper_bound(letters.begin(), letters.end(), target);

        return position == letters.end()
            ? letters[0]
            : *position;
    }
};
```

Complexity:

```text
Time Complexity:  O(log n)
Space Complexity: O(1)
```

---

# 16. Difference Between Lower Bound and Upper Bound

Understanding this difference is extremely important.

## Lower Bound

Finds the first value satisfying:

```text
value >= target
```

Condition:

```cpp
letters[mid] >= target
```

---

## Upper Bound

Finds the first value satisfying:

```text
value > target
```

Condition:

```cpp
letters[mid] > target
```

---

## Example

```text
letters = ['c', 'c', 'f', 'j']
target  = 'c'
```

Lower bound of `'c'`:

```text
Index 0 → 'c'
```

because:

```text
'c' >= 'c'
```

Upper bound of `'c'`:

```text
Index 2 → 'f'
```

because:

```text
'f' > 'c'
```

This problem requires:

```text
Upper bound
```

because the answer must be strictly greater than the target.

---

# 17. Mental Model

Use this mental model:

> I need to find the first position where the condition becomes true.

The condition is:

```cpp
letters[index] > target
```

The array can be imagined as:

```text
false false false true true true
                  ↑
             first true
```

The goal is to find that first `true`.

---

## When the Condition Is True

```cpp
if (letters[mid] > target)
```

Think:

```text
This is a valid answer.
Save it.
There may be an earlier valid answer.
Move left.
```

Implementation:

```cpp
result = mid;
right = mid - 1;
```

---

## When the Condition Is False

```cpp
letters[mid] <= target
```

Think:

```text
This is not a valid answer.
Everything to its left is also invalid.
Move right.
```

Implementation:

```cpp
left = mid + 1;
```

---

## Short Memory Cue

```text
Valid   → save and move left
Invalid → move right
```

Or:

```text
First greater element = upper bound
```

---

# 18. Boundary Binary Search Template

The general template for finding the first valid position is:

```cpp
int firstValidPosition(vector<T>& values) {
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;
    int answer = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (isValid(values[mid])) {
            answer = mid;

            // Try to find an earlier valid answer.
            right = mid - 1;
        } else {
            // The answer must be on the right.
            left = mid + 1;
        }
    }

    return answer;
}
```

For this problem:

```cpp
isValid(letters[mid]) = letters[mid] > target
```

Therefore:

```cpp
if (letters[mid] > target) {
    answer = mid;
    right = mid - 1;
} else {
    left = mid + 1;
}
```

---

# 19. How to Recognize the Correct Pattern

## Signal 1: The Input Is Sorted

The problem says that the letters are sorted.

A sorted search space is the first signal for binary search.

Ask:

```text
Can I eliminate half of the remaining elements?
```

For this problem, the answer is yes.

---

## Signal 2: The Problem Asks for the Smallest Greater Value

The phrase:

```text
smallest character greater than target
```

can be translated to:

```text
first value > target
```

That is the definition of upper bound.

---

## Signal 3: We Need a Boundary, Not Exact Equality

The problem is not asking:

```text
Find target
```

It is asking:

```text
Find the first value satisfying a condition.
```

This suggests boundary binary search.

---

## Signal 4: The Validity Pattern Is Monotonic

For a sorted array, the condition:

```cpp
letters[index] > target
```

produces:

```text
false false false true true true
```

It never changes back from `true` to `false`.

This monotonic behaviour makes binary search possible.

---

## Signal 5: Wrap-Around Is Only a Fallback

The wrap-around condition does not change the binary-search logic.

First, search normally for:

```text
first letter > target
```

If no such letter exists:

```text
return letters[0]
```

Treat wrap-around as a final fallback, not as part of the main search.

---

# 20. How to Derive the Solution Step-by-Step

## Step 1: Translate the English Statement

The problem says:

```text
Find the smallest letter greater than target.
```

Translate it into a precise condition:

```text
Find the first index where letters[index] > target.
```

---

## Step 2: Notice That the Array Is Sorted

Since the array is sorted, valid answers form a continuous region.

Example:

```text
letters = ['b', 'd', 'f', 'h', 'k']
target  = 'e'
```

Validity:

```text
'b' > 'e' → false
'd' > 'e' → false
'f' > 'e' → true
'h' > 'e' → true
'k' > 'e' → true
```

Pattern:

```text
false false true true true
```

---

## Step 3: Identify the Boundary

We do not want any `true`.

We want:

```text
The first true
```

That means:

```text
If mid is valid, save it and move left.
```

---

## Step 4: Determine the Invalid Case

If:

```cpp
letters[mid] <= target
```

then `mid` is invalid.

Everything to its left is also invalid because the array is sorted.

Therefore:

```cpp
left = mid + 1;
```

---

## Step 5: Store the Best Answer

When `mid` is valid:

```cpp
result = mid;
```

This keeps the best answer found so far.

Then continue left:

```cpp
right = mid - 1;
```

---

## Step 6: Handle the Missing Boundary

If no valid answer is found:

```text
result = -1
```

Then apply wrap-around:

```cpp
return letters[0];
```

---

# 21. Questions to Ask Yourself

When solving this problem, ask:

1. Is the input sorted?
2. What exact condition makes an element valid?
3. Does equality count?
4. Am I searching for any valid value or the first valid value?
5. If `mid` is valid, can a better answer exist on the left?
6. If `mid` is invalid, can anything on the left be valid?
7. What should happen if no valid value exists?

For this problem:

```text
Is the input sorted?
Yes.

What is the valid condition?
letters[index] > target.

Does equality count?
No.

Do we need any valid letter?
No, we need the smallest valid letter.

What does smallest mean in a sorted array?
The first valid index.

If mid is valid, where do we search?
Left.

If mid is invalid, where do we search?
Right.

What if no valid letter exists?
Return letters[0].
```

---

# 22. Common Mistakes

## Mistake 1: Using `>=` Instead of `>`

Incorrect:

```cpp
if (letters[mid] >= target)
```

This may return the target itself.

For example:

```text
letters = ['c', 'f', 'j']
target  = 'c'
```

Using `>=` may return:

```text
'c'
```

But the answer must be strictly greater:

```text
'f'
```

Correct:

```cpp
if (letters[mid] > target)
```

---

## Mistake 2: Returning Immediately When a Valid Letter Is Found

Incorrect:

```cpp
if (letters[mid] > target) {
    return letters[mid];
}
```

The current value is valid, but there may be a smaller valid value on the left.

Correct:

```cpp
if (letters[mid] > target) {
    result = mid;
    right = mid - 1;
}
```

---

## Mistake 3: Forgetting the Wrap-Around Rule

If the target is greater than or equal to the largest letter, binary search will not find a valid answer.

Incorrect:

```cpp
return letters[result];
```

If `result == -1`, this attempts to access an invalid index.

Correct:

```cpp
return result == -1 ? letters[0] : letters[result];
```

---

## Mistake 4: Searching Left When the Middle Is Invalid

If:

```cpp
letters[mid] <= target
```

the answer cannot be at `mid` or anywhere to its left.

Therefore, search right:

```cpp
left = mid + 1;
```

---

## Mistake 5: Confusing Lower Bound With Upper Bound

Remember:

```text
Lower bound → first value >= target
Upper bound → first value > target
```

This problem requires upper bound.

---

## Mistake 6: Overcomplicating Wrap-Around

Do not attempt to make the array physically circular.

You do not need:

- Circular-array traversal
- Modulo during every binary-search step
- Two separate array searches

Simply:

1. Find the first value greater than the target.
2. If it does not exist, return the first value.

---

# 23. Edge Cases

## Target Is Smaller Than Every Letter

```text
letters = ['c', 'f', 'j']
target  = 'a'
```

Every letter is greater than the target.

The smallest is the first letter:

```text
Answer = 'c'
```

---

## Target Equals the First Letter

```text
letters = ['c', 'f', 'j']
target  = 'c'
```

Equality is not valid.

```text
Answer = 'f'
```

---

## Target Lies Between Two Letters

```text
letters = ['c', 'f', 'j']
target  = 'd'
```

The first letter greater than `'d'` is:

```text
Answer = 'f'
```

---

## Target Equals the Largest Letter

```text
letters = ['c', 'f', 'j']
target  = 'j'
```

No greater letter exists.

Wrap around:

```text
Answer = 'c'
```

---

## Target Is Greater Than Every Letter

```text
letters = ['c', 'f', 'j']
target  = 'z'
```

No greater letter exists.

Wrap around:

```text
Answer = 'c'
```

---

## Duplicate Target Letters

```text
letters = ['c', 'c', 'f', 'f', 'j']
target  = 'c'
```

All occurrences of `'c'` must be skipped.

```text
Answer = 'f'
```

---

## Duplicate Valid Letters

```text
letters = ['c', 'f', 'f', 'f', 'j']
target  = 'd'
```

The first valid letter is:

```text
'f'
```

Returning any `'f'` gives the same character, but the boundary-search pattern still finds the first valid index.

---

# 24. Similar Problems

## Directly Related Problems

1. Find the first element greater than a target.
2. Find the first element greater than or equal to a target.
3. Find the last element smaller than a target.
4. Find the last element smaller than or equal to a target.
5. Find the floor and ceiling of a target.
6. Find the first and last occurrence of an element.
7. Search Insert Position.
8. Implement `lower_bound`.
9. Implement `upper_bound`.
10. Count occurrences in a sorted array.

---

## Recommended LeetCode Problems

```text
LeetCode 704  — Binary Search
LeetCode 35   — Search Insert Position
LeetCode 34   — Find First and Last Position of Element
LeetCode 744  — Find Smallest Letter Greater Than Target
LeetCode 278  — First Bad Version
LeetCode 69   — Sqrt(x)
LeetCode 153  — Find Minimum in Rotated Sorted Array
LeetCode 33   — Search in Rotated Sorted Array
LeetCode 162  — Find Peak Element
LeetCode 875  — Koko Eating Bananas
LeetCode 1011 — Capacity to Ship Packages Within D Days
```

---

# 25. Connection With Other Boundary Problems

## First Value Greater Than or Equal to Target

Condition:

```cpp
values[mid] >= target
```

This is lower bound.

---

## First Value Greater Than Target

Condition:

```cpp
values[mid] > target
```

This is upper bound.

This problem belongs to this category.

---

## First Occurrence of Target

Condition:

```cpp
values[mid] == target
```

When found:

```cpp
answer = mid;
right = mid - 1;
```

---

## Last Occurrence of Target

When found:

```cpp
answer = mid;
left = mid + 1;
```

---

## First Bad Version

Condition:

```cpp
isBadVersion(mid) == true
```

When valid:

```cpp
answer = mid;
right = mid - 1;
```

It uses the same first-true boundary pattern.

---

# 26. Pattern Comparison Table

| Problem | Valid condition | Required boundary |
|---|---|---|
| Lower bound | `value >= target` | First valid |
| Upper bound | `value > target` | First valid |
| First occurrence | `value == target` | Leftmost match |
| Last occurrence | `value == target` | Rightmost match |
| First bad version | `isBadVersion(mid)` | First `true` |
| Next greatest letter | `letter > target` | First valid |

---

# 27. Practice Strategy to Learn the Pattern

Do not focus only on remembering code.

For every problem, write these four things before coding:

```text
1. Search space:
   The indices from 0 to n - 1.

2. Valid condition:
   letters[index] > target.

3. Required boundary:
   The first valid index.

4. Missing-answer behaviour:
   Return letters[0].
```

Then derive the movement:

```text
If valid:
    Save mid
    Move left

If invalid:
    Move right
```

This is more reliable than memorizing individual solutions.

---

# 28. Pattern-Recognition Exercise

When reading:

```text
Find the smallest letter strictly greater than target
```

Translate each word:

```text
smallest
    ↓
leftmost or first

strictly greater
    ↓
value > target

sorted array
    ↓
binary search

first value > target
    ↓
upper bound
```

Final pattern:

```text
Binary search for the upper bound.
```

---

# 29. Final Summary

The problem asks for:

```text
The first letter strictly greater than the target.
```

Because the array is sorted, the validity pattern is:

```text
false false false true true true
```

We need to find the first `true`.

Binary-search decisions:

```text
letters[mid] > target
    → mid is valid
    → save mid
    → search left

letters[mid] <= target
    → mid is invalid
    → search right
```

If no valid letter exists:

```text
Return letters[0]
```

The final complexity is:

```text
Time Complexity:  O(log n)
Space Complexity: O(1)
```

Use this memory cue:

```text
First value > target
        ↓
Upper bound
        ↓
Valid: save and move left
Invalid: move right
No answer: wrap to letters[0]
```
