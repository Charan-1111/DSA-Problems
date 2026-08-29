# Fruit Into Baskets — Complete Explanation

## 1. What Does the Problem Really Mean?

You are given an array:

```cpp
fruits = [1, 2, 1, 3, 3, 2]
```

Each number represents a fruit type produced by a tree.

For example:

- Tree `0` produces fruit type `1`.
- Tree `1` produces fruit type `2`.
- Tree `2` produces fruit type `1`.
- Tree `3` produces fruit type `3`.

You have two baskets:

- Each basket can store only one type of fruit.
- Each basket can store any number of fruits.
- You must collect fruits from consecutive trees.
- You can start from any tree.
- You must stop when a fruit cannot fit into either basket.

### Converting the Story into a DSA Problem

Ignore the fruit-and-basket story for a moment.

```text
Consecutive trees
→ Contiguous subarray

Two baskets
→ At most two distinct fruit types

Maximum fruits
→ Longest valid subarray
```

Therefore, the real problem is:

> Find the longest contiguous subarray containing at most two distinct values.

### Example

```text
fruits = [1, 2, 1, 3, 3, 2]
```

Some possible subarrays are:

```text
[1, 2, 1]       → 2 distinct types → valid
[1, 2, 1, 3]    → 3 distinct types → invalid
[1, 3, 3]       → 2 distinct types → valid
[3, 3, 2]       → 2 distinct types → valid
```

The longest valid subarray has length `3`.

```text
Answer = 3
```

---

## 2. Brute-Force Approach

### Idea

Generate every possible subarray and count the number of distinct fruit types in it.

For every pair `(left, right)`:

1. Consider the subarray from `left` to `right`.
2. Traverse that complete subarray.
3. Insert its fruit types into a set.
4. If the set contains at most two types, update the answer.

### Code

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int maxFruitCnt = 0;

        for (int left = 0; left < n; left++) {
            for (int right = left; right < n; right++) {
                unordered_set<int> fruitTypes;

                for (int i = left; i <= right; i++) {
                    fruitTypes.insert(fruits[i]);
                }

                if (fruitTypes.size() <= 2) {
                    int currentLength = right - left + 1;
                    maxFruitCnt = max(maxFruitCnt, currentLength);
                }
            }
        }

        return maxFruitCnt;
    }
};
```

### Complexity

There are `O(n²)` possible subarrays.

For each subarray, we may traverse `O(n)` elements.

```text
Time Complexity:  O(n³)
Space Complexity: O(n)
```

This approach works, but it repeats a lot of work.

---

## 3. Better Approach

### Observation

In the brute-force solution, we repeatedly rebuild the set for very similar subarrays.

For example:

```text
[1]
[1, 2]
[1, 2, 1]
[1, 2, 1, 3]
```

Instead of rebuilding the set every time, we can maintain it while moving `right`.

For every starting position `left`:

1. Create an empty set.
2. Move `right` from `left` toward the end.
3. Insert `fruits[right]` into the set.
4. If there are at most two fruit types, update the answer.
5. If there are more than two types, stop.

### Why Can We Stop When We Find Three Types?

Consider:

```text
fruits = [1, 2, 1, 3, 2]
```

Starting from index `0`:

```text
[1]          → valid
[1, 2]       → valid
[1, 2, 1]    → valid
[1, 2, 1, 3] → invalid
```

Once the subarray contains three fruit types, extending it further cannot remove any existing type.

Therefore, all larger subarrays starting at the same `left` will also be invalid.

We can stop and try the next `left`.

### Code

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int maxFruitCnt = 0;

        for (int left = 0; left < n; left++) {
            unordered_set<int> fruitTypes;

            for (int right = left; right < n; right++) {
                fruitTypes.insert(fruits[right]);

                if (fruitTypes.size() > 2) {
                    break;
                }

                int currentLength = right - left + 1;
                maxFruitCnt = max(maxFruitCnt, currentLength);
            }
        }

        return maxFruitCnt;
    }
};
```

### Complexity

For every `left`, `right` can move across the array.

```text
Time Complexity:  O(n²)
Space Complexity: O(1)
```

The set temporarily contains at most three fruit types, so the auxiliary space is effectively constant.

This is better than `O(n³)`, but it still repeats work because `right` starts again for every `left`.

---

## 4. Optimal Sliding-Window Approach

### Important Observation

We need the:

> Longest contiguous subarray containing at most two distinct values.

This sentence provides the main sliding-window signals:

- Longest range
- Contiguous elements
- A validity condition
- Removing elements from the left can restore validity

The validity condition is:

```text
Number of distinct fruit types <= 2
```

---

### Core Idea

Maintain a window:

```text
[left ... right]
```

The window represents the trees from which we are currently collecting fruits.

Use a frequency map:

```cpp
unordered_map<int, int> frequency;
```

The map stores:

```text
fruit type → frequency inside the current window
```

For example:

```text
Window = [1, 2, 1]
```

The map contains:

```text
1 → 2
2 → 1
```

The number of entries in the map tells us the number of distinct fruit types:

```cpp
frequency.size()
```

---

### Step 1: Expand the Window

Move `right` forward and add the current fruit:

```cpp
frequency[fruits[right]]++;
```

---

### Step 2: Check Whether the Window Is Valid

The window is valid when:

```cpp
frequency.size() <= 2
```

The window is invalid when:

```cpp
frequency.size() > 2
```

---

### Step 3: Shrink an Invalid Window

If there are more than two fruit types, remove fruits from the left:

```cpp
frequency[fruits[left]]--;
```

If a fruit's frequency becomes zero, that fruit type is no longer present in the window:

```cpp
if (frequency[fruits[left]] == 0) {
    frequency.erase(fruits[left]);
}
```

Then move `left`:

```cpp
left++;
```

Continue shrinking until the window becomes valid again.

---

### Step 4: Calculate the Window Length

Once the window is valid:

```cpp
int currentLength = right - left + 1;
```

Update the maximum:

```cpp
maxFruitCnt = max(maxFruitCnt, currentLength);
```

---

## Dry Run

Consider:

```text
fruits = [1, 2, 1, 3, 3, 2]
```

### Add `1`

```text
Window: [1]
Map:    {1:1}
Types:  1
Length: 1
Answer: 1
```

### Add `2`

```text
Window: [1, 2]
Map:    {1:1, 2:1}
Types:  2
Length: 2
Answer: 2
```

### Add `1`

```text
Window: [1, 2, 1]
Map:    {1:2, 2:1}
Types:  2
Length: 3
Answer: 3
```

### Add `3`

```text
Window: [1, 2, 1, 3]
Map:    {1:2, 2:1, 3:1}
Types:  3
```

The window is invalid.

Remove the first `1`:

```text
Window: [2, 1, 3]
Map:    {1:1, 2:1, 3:1}
Types:  3
```

The window is still invalid.

Remove `2`:

```text
Window: [1, 3]
Map:    {1:1, 3:1}
Types:  2
```

The window is valid again.

### Add the next `3`

```text
Window: [1, 3, 3]
Map:    {1:1, 3:2}
Types:  2
Length: 3
Answer: 3
```

### Add `2`

```text
Window: [1, 3, 3, 2]
Map:    {1:1, 2:1, 3:2}
Types:  3
```

Remove `1`:

```text
Window: [3, 3, 2]
Map:    {2:1, 3:2}
Types:  2
Length: 3
Answer: 3
```

Final answer:

```text
3
```

---

## Clean Optimal Solution

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();

        int left = 0;
        int maxFruitCnt = 0;

        unordered_map<int, int> frequency;

        for (int right = 0; right < n; right++) {
            // Add the current fruit to the window.
            frequency[fruits[right]]++;

            // Restore validity when there are more than two types.
            while (frequency.size() > 2) {
                frequency[fruits[left]]--;

                if (frequency[fruits[left]] == 0) {
                    frequency.erase(fruits[left]);
                }

                left++;
            }

            // The current window is valid.
            int currentWindowLength = right - left + 1;

            maxFruitCnt = max(
                maxFruitCnt,
                currentWindowLength
            );
        }

        return maxFruitCnt;
    }
};
```

### Complexity

Both pointers move only from left to right:

- `right` moves at most `n` times.
- `left` moves at most `n` times.

Therefore:

```text
Time Complexity:  O(n)
Space Complexity: O(1)
```

It is sometimes described as `O(2n)`, but constants are ignored:

```text
O(2n) = O(n)
```

The map can temporarily contain at most three fruit types, so its space is effectively constant.

---

## Understanding My Solution

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();

        int left = 0, right = 0;

        unordered_map<int, int> mp;

        int fruitCnt = 0, maxFruitCnt = 0;

        while(right < n) {
            if(mp.find(fruits[right]) == mp.end() && mp.size() == 2) {
                while(left < right && mp.size() == 2) {
                    mp[fruits[left]]--;
                    fruitCnt--;

                    if(mp[fruits[left]] == 0) {
                        mp.erase(fruits[left]);
                    }

                    left++;
                }
            }

            fruitCnt++;
            maxFruitCnt = max(maxFruitCnt, fruitCnt);
            mp[fruits[right]]++;
            right++;
        }

        return maxFruitCnt;
    }
};
```

This is also a sliding-window solution.

The reasoning is:

1. Maintain a window containing at most two fruit types.
2. Before adding `fruits[right]`, check whether it is a new third type.
3. If it is a third type, remove fruits from the left.
4. Continue until one existing fruit type completely disappears.
5. Add the new fruit to the window.
6. Update the maximum answer.

This condition:

```cpp
mp.find(fruits[right]) == mp.end() && mp.size() == 2
```

means:

```text
The current fruit is not already present in the window
AND
the two baskets are already occupied.
```

Therefore, a third fruit type is about to enter the window.

This loop:

```cpp
while(left < right && mp.size() == 2)
```

removes fruits until one basket becomes available.

When a fruit frequency becomes zero, its type must be removed:

```cpp
if(mp[fruits[left]] == 0) {
    mp.erase(fruits[left]);
}
```

The solution is correct.

However, it can be simplified.

There is no need to maintain:

```cpp
int fruitCnt;
```

The current window length is always:

```cpp
right - left + 1
```

There is also no need to predict whether the new fruit will invalidate the window.

A simpler process is:

```text
Add the current fruit.
If the window becomes invalid, shrink it.
When the window is valid, calculate its length.
```

This gives the reusable structure:

```cpp
frequency[fruits[right]]++;

while (frequency.size() > 2) {
    // Remove fruits from the left.
}

maxFruitCnt = max(
    maxFruitCnt,
    right - left + 1
);
```

---

## 5. Similar Problems

### 1. Longest Substring Without Repeating Characters

Find the longest substring containing no repeated characters.

```text
Validity condition:
Every character frequency must be at most 1.
```

---

### 2. Longest Substring with At Most K Distinct Characters

This is the generalized version of Fruit Into Baskets.

```text
Fruit Into Baskets:
At most 2 distinct values

General problem:
At most K distinct values
```

---

### 3. Longest Substring with At Most Two Distinct Characters

This is almost the same problem, but it uses a string instead of an integer array.

---

### 4. Max Consecutive Ones III

Find the longest subarray containing at most `k` zeroes.

```text
Validity condition:
number of zeroes <= k
```

---

### 5. Longest Repeating Character Replacement

Find the longest substring that can be made identical using at most `k` replacements.

```text
Validity condition:
window size - maximum character frequency <= k
```

---

### 6. Minimum Window Substring

Find the smallest window containing all required characters.

This uses sliding window, but it asks for the minimum valid window instead of the maximum valid window.

---

### 7. Subarrays with K Different Integers

Count the subarrays containing exactly `k` distinct integers.

A common transformation is:

```text
Exactly K distinct
=
At most K distinct
-
At most K - 1 distinct
```

---

### 8. Binary Subarrays With Sum

Count subarrays having a particular sum.

For non-negative or binary arrays, a common transformation is:

```text
Exactly goal
=
At most goal
-
At most goal - 1
```

---

## 6. Mental Model

Think of the window as the fruits currently stored in the baskets:

```text
[left ................ right]
```

The right pointer adds fruits:

```text
right = producer
```

The left pointer removes fruits:

```text
left = cleaner
```

The frequency map describes the current contents of the baskets:

```text
frequency map = window state
```

The validity rule is:

```text
At most two distinct fruit types
```

The process is:

```text
1. Add from the right.
2. Check the rule.
3. If the rule is broken, remove from the left.
4. Once the rule is satisfied, record the answer.
```

A short mental template is:

```text
Expand → Validate → Shrink → Record
```

For Fruit Into Baskets:

```text
Expand:
Add fruits[right].

Validate:
Are there more than two fruit types?

Shrink:
Remove fruits[left] until there are at most two types.

Record:
Update the maximum window length.
```

---

## 7. How to Recognize the Correct Pattern

Pattern recognition comes from identifying signals in the problem statement.

### Signal 1: Contiguous or Consecutive Elements

The problem says that fruits must be collected from consecutive trees.

Words that suggest a window include:

```text
contiguous
consecutive
substring
subarray
continuous
from left to right
```

This tells us that the answer involves a range:

```text
[left ... right]
```

---

### Signal 2: Longest or Maximum

The problem asks for the maximum number of fruits.

Words such as these often suggest maintaining a window:

```text
longest
maximum length
maximum consecutive
largest contiguous range
```

---

### Signal 3: A Constraint Inside the Range

The selected range may contain at most two fruit types.

Common window constraints include:

```text
at most K distinct elements
at most K zeroes
sum <= K
no repeating characters
at most K replacements
```

A constraint tells us when the current window becomes invalid.

---

### Signal 4: Removing from the Left Restores Validity

Ask:

> If adding an element makes the range invalid, can I remove elements from the left until it becomes valid again?

For this problem:

```text
Adding a third fruit type makes the window invalid.

Removing fruits from the left can completely eliminate one fruit type.

The window then becomes valid again.
```

This is a strong sliding-window signal.

---

## Pattern-Recognition Checklist

When reading a new problem, ask the following questions.

### Question 1

Is the answer about a contiguous subarray or substring?

If yes, consider:

```text
Sliding window
Two pointers
Prefix sum
```

### Question 2

Is the problem asking for the longest or shortest valid range?

If yes, sliding window becomes a strong possibility.

### Question 3

Does the range have a validity condition?

For example:

```text
At most two distinct values
No repeated characters
Sum less than or equal to K
At most K zeroes
```

### Question 4

Can validity be restored by moving `left` forward?

If yes, variable-size sliding window is likely appropriate.

### Question 5

What information is needed to determine whether the window is valid?

For this problem, we need:

```text
The number of distinct fruit types in the current window.
```

Therefore, we use a frequency map.

---

## Reusable Sliding-Window Template

```cpp
int left = 0;
int answer = 0;

unordered_map<int, int> windowState;

for (int right = 0; right < n; right++) {
    // 1. Add the right element.
    windowState[arr[right]]++;

    // 2. Shrink while the window is invalid.
    while (windowIsInvalid(windowState)) {
        windowState[arr[left]]--;

        if (windowState[arr[left]] == 0) {
            windowState.erase(arr[left]);
        }

        left++;
    }

    // 3. Record the valid window.
    answer = max(answer, right - left + 1);
}
```

For Fruit Into Baskets:

```cpp
windowIsInvalid(windowState)
```

becomes:

```cpp
windowState.size() > 2
```

---

## How to Build Pattern-Recognition Ability

### Step 1: Ignore the Story

Translate the story into an array operation.

```text
Two baskets
→ At most two fruit types

Consecutive trees
→ Contiguous subarray

Maximum fruits
→ Longest valid subarray
```

The transformed problem is:

```text
Find the longest contiguous subarray containing at most two distinct values.
```

This version makes the sliding-window pattern much easier to recognize.

---

### Step 2: Write the Validity Condition

Before writing code, explicitly write:

```text
Valid window:
distinct fruit types <= 2

Invalid window:
distinct fruit types > 2
```

---

### Step 3: Select the Window State

Ask:

> What information do I need to know whether the current window is valid?

We need:

- The fruit types currently present.
- Their frequencies.
- Whether a type has completely left the window.

Therefore, use:

```cpp
unordered_map<int, int> frequency;
```

---

### Step 4: Write the Four Window Operations

For every sliding-window problem, identify:

```text
1. Add
2. Invalid condition
3. Remove
4. Answer
```

For this problem:

```text
Add:
frequency[fruits[right]]++;

Invalid:
frequency.size() > 2

Remove:
frequency[fruits[left]]--;

Answer:
max(answer, right - left + 1)
```

---

### Step 5: Trace One Invalid Transition

Instead of dry-running the entire input immediately, focus on the most important transition:

```text
Valid window
→ New element arrives
→ Window becomes invalid
→ Shrink
→ Window becomes valid
```

Example:

```text
Current window: [1, 2, 1]
New fruit:      3

After adding:
[1, 2, 1, 3]

Distinct types:
{1, 2, 3}

Invalid because:
3 > 2
```

Shrink from the left:

```text
[2, 1, 3] → still invalid
[1, 3]    → valid
```

If this transition works correctly, most of the algorithm is already understood.

---

## Common Mistakes

### Mistake 1: Removing the Frequency Instead of the Key

Incorrect:

```cpp
mp.erase(mp[fruits[left]]);
```

Correct:

```cpp
mp.erase(fruits[left]);
```

`erase()` expects the fruit type, which is the map key.

---

### Mistake 2: Forgetting to Remove Zero-Frequency Keys

This is not enough:

```cpp
mp[fruits[left]]--;
```

If the frequency becomes zero but the key remains in the map, `mp.size()` will still count that fruit type.

Correct:

```cpp
mp[fruits[left]]--;

if (mp[fruits[left]] == 0) {
    mp.erase(fruits[left]);
}
```

---

### Mistake 3: Shrinking Only Once

Incorrect:

```cpp
if (mp.size() > 2) {
    // Remove one element.
}
```

Removing one element may not restore validity.

For example:

```text
Window = [1, 1, 2, 3]
```

After removing one `1`:

```text
Window = [1, 2, 3]
```

The window still contains three distinct types.

Therefore, use:

```cpp
while (mp.size() > 2)
```

---

### Mistake 4: Maintaining an Unnecessary Counter

Instead of manually maintaining:

```cpp
fruitCnt++;
fruitCnt--;
```

calculate the current window length directly:

```cpp
right - left + 1
```

This reduces the number of variables and makes the solution less error-prone.

---

### Mistake 5: Updating the Answer While the Window Is Invalid

The answer should be updated only after restoring validity.

Correct order:

```text
1. Add the new element.
2. Shrink while the window is invalid.
3. Update the answer after the window becomes valid.
```

---

## Final Thought Process

When you see this problem, think:

```text
The fruits must come from consecutive trees.
Therefore, I need a contiguous subarray.

I need the maximum number of fruits.
Therefore, I need the longest valid subarray.

I have two baskets.
Therefore, the subarray can contain at most two distinct values.

Adding a third type makes the window invalid.

Removing elements from the left can restore validity.

Therefore, this is a variable-size sliding-window problem.

I need frequencies to know when a fruit type completely leaves the window.

Therefore, I will use an unordered_map.
```

Then apply:

```text
Expand → Shrink while invalid → Record the answer
```

That is the reusable pattern behind the Fruit Into Baskets problem.
