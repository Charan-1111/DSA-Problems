# Longest Substring Without Repeating Characters

## Problem Statement

Given a string `s`, find the length of the longest **substring** that contains no repeating characters.

---

# 1. What Does the Question Really Mean?

Suppose we are given:

```text
s = "abcabcbb"
```

We need to find a continuous portion of the string in which every character is unique.

Some possible substrings are:

```text
"a"
"ab"
"abc"
"abca"
"bcab"
```

Now check whether they contain duplicate characters:

```text
"a"    → No duplicates
"ab"   → No duplicates
"abc"  → No duplicates
"abca" → 'a' appears twice
"bcab" → 'b' appears twice
```

The longest valid substring is:

```text
"abc"
```

Its length is:

```text
3
```

Therefore:

```text
Input:  "abcabcbb"
Output: 3
```

---

## Important: Substring vs Subsequence

A **substring** must contain continuous characters from the original string.

For example:

```text
String: "abcde"

Valid substrings:
"abc"
"bcd"
"de"
```

But `"ace"` is not a substring because its characters are not continuous.

Therefore, this problem is asking:

> What is the longest continuous window in which every character appears only once?

---

# 2. Brute-Force Approach

The simplest approach is:

1. Generate every possible substring.
2. Check whether that substring contains duplicate characters.
3. If it has no duplicates, calculate its length.
4. Keep track of the maximum length.

---

## Example

For:

```text
s = "abc"
```

The possible substrings are:

```text
"a"
"ab"
"abc"
"b"
"bc"
"c"
```

For every substring, we use a set to check whether a character appears more than once.

---

## Brute-Force Code

```cpp
class Solution {
public:
    bool hasUniqueCharacters(string& s, int start, int end) {
        unordered_set<char> seen;

        for (int i = start; i <= end; i++) {
            if (seen.find(s[i]) != seen.end()) {
                return false;
            }

            seen.insert(s[i]);
        }

        return true;
    }

    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int result = 0;

        for (int start = 0; start < n; start++) {
            for (int end = start; end < n; end++) {
                if (hasUniqueCharacters(s, start, end)) {
                    int length = end - start + 1;
                    result = max(result, length);
                }
            }
        }

        return result;
    }
};
```

---

## Time Complexity

There are approximately `O(n²)` possible substrings.

For every substring, we may take `O(n)` time to check whether it contains duplicate characters.

Therefore:

```text
Time Complexity:  O(n³)
Space Complexity: O(n)
```

---

## Why Is the Brute-Force Approach Inefficient?

Consider:

```text
s = "abcdef"
```

While checking:

```text
"abcde"
```

we already checked:

```text
a, b, c, d, e
```

When checking:

```text
"abcdef"
```

we again start checking from the beginning.

Therefore, the same characters are checked repeatedly.

This suggests that we should reuse the information from the previous substring instead of starting again.

---

# 3. Better Approach: Sliding Window With a Set

The question asks for the longest continuous part of a string satisfying a condition:

```text
No character should appear more than once.
```

Whenever we see phrases such as:

```text
Longest substring
Shortest substring
Longest subarray
Continuous sequence
Contiguous elements
A condition that must remain valid
```

we should consider the **sliding-window pattern**.

---

## Basic Idea

Maintain a window using two pointers:

```text
left  → beginning of the window
right → end of the window
```

The current window is:

```text
s[left ... right]
```

We also maintain a set containing the characters currently present in the window.

---

## What Should We Do for Every Character?

### Case 1: The Character Is Not in the Set

If `s[right]` is not present in the set:

1. Add it to the set.
2. Expand the window.
3. Calculate the window length.
4. Update the maximum length.

### Case 2: The Character Is Already in the Set

If `s[right]` is already present:

1. The current window has become invalid.
2. Remove characters from the left side.
3. Continue removing until the duplicate character is removed.
4. Add the current character.
5. Continue expanding the window.

---

## Step-by-Step Example

Consider:

```text
s = "abcabcbb"
```

### Step 1

```text
Window: "a"
Set:    {a}
Length: 1
```

### Step 2

```text
Window: "ab"
Set:    {a, b}
Length: 2
```

### Step 3

```text
Window: "abc"
Set:    {a, b, c}
Length: 3
```

### Step 4

The next character is `a`.

But `a` is already present in the window:

```text
Current window: "abc"
New character:  'a'
```

Therefore, remove characters from the left until the old `a` is removed:

```text
Remove old 'a'

New window: "bca"
```

The window is valid again.

The maximum length remains:

```text
3
```

---

## Better Approach Code

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window;

        int left = 0;
        int result = 0;

        for (int right = 0; right < s.length(); right++) {
            while (window.find(s[right]) != window.end()) {
                window.erase(s[left]);
                left++;
            }

            window.insert(s[right]);

            int currentLength = right - left + 1;
            result = max(result, currentLength);
        }

        return result;
    }
};
```

---

## Time Complexity

At first, the inner `while` loop may make the solution look like `O(n²)`.

However, every character is:

```text
Added to the set at most once
Removed from the set at most once
```

Therefore, the total number of operations is approximately `2n`.

```text
Time Complexity:  O(n)
Space Complexity: O(n)
```

---

## Can We Improve This Approach?

The time complexity is already `O(n)`.

However, when a duplicate appears, we move `left` one position at a time.

For example:

```text
Current window: "abcd"
New character:  'c'
```

Using a set, we perform:

```text
Remove 'a'
Remove 'b'
Remove old 'c'
```

But if we know that the previous `c` was at index `2`, we can directly move `left` to:

```text
2 + 1 = 3
```

That leads us to the map-based optimal approach.

---

# 4. Optimal Approach: Sliding Window With Last-Seen Index

Instead of only remembering whether a character is present, we remember the last index where it appeared.

We use:

```cpp
unordered_map<char, int> lastSeen;
```

The map stores:

```text
character → latest index
```

For example:

```text
'a' → 4
'b' → 2
'c' → 3
```

This means:

```text
'a' was most recently seen at index 4
'b' was most recently seen at index 2
'c' was most recently seen at index 3
```

---

## How Did We Come to This Idea?

In the set-based solution, when we encounter a duplicate, we remove characters one by one from the left.

Suppose:

```text
Current window: "abcd"
New character:  'c'
```

The previous `c` is at index `2`.

Instead of performing:

```text
Remove 'a'
Remove 'b'
Remove old 'c'
```

we can directly move the left pointer to:

```text
previous index of 'c' + 1
```

Therefore:

```cpp
left = lastSeen[s[right]] + 1;
```

This immediately removes the previous occurrence of the duplicate from the current window.

---

# Understanding Your Variables

Your code uses:

```cpp
int res = 0;
int len = 0;
int lastIdx = 0;
```

## `res`

Stores the maximum valid substring length found so far.

```cpp
res = max(res, len);
```

## `len`

Stores the length of the current valid window.

```cpp
len = i - lastIdx + 1;
```

The general formula for an inclusive window is:

```text
window length = right - left + 1
```

## `lastIdx`

The name `lastIdx` is slightly confusing.

It actually represents the **left boundary of the current window**.

A clearer name would be:

```cpp
int left = 0;
```

## `mp`

The map stores the latest index where every character was seen.

```cpp
unordered_map<char, int> mp;
```

---

# Your Corrected Optimal Solution

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        int len = 0;
        int lastIdx = 0;

        unordered_map<char, int> mp;

        for (int i = 0; i < s.length(); i++) {
            if (mp.find(s[i]) == mp.end()) {
                // The character has never been seen before
                mp[s[i]] = i;
            } else {
                // Move the left boundary only if the previous occurrence
                // is inside the current window
                if (lastIdx <= mp[s[i]]) {
                    lastIdx = mp[s[i]] + 1;
                }
            }

            // Always store the latest index of the character
            mp[s[i]] = i;

            len = i - lastIdx + 1;
            res = max(res, len);
        }

        return res;
    }
};
```

---

# Cleaner Version of the Same Solution

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0;
        int result = 0;

        unordered_map<char, int> lastSeen;

        for (int right = 0; right < s.length(); right++) {
            char current = s[right];

            if (lastSeen.find(current) != lastSeen.end()) {
                left = max(left, lastSeen[current] + 1);
            }

            lastSeen[current] = right;

            int currentLength = right - left + 1;
            result = max(result, currentLength);
        }

        return result;
    }
};
```

The most important line is:

```cpp
left = max(left, lastSeen[current] + 1);
```

---

# Why Do We Need `max()`?

The left pointer must never move backwards.

Consider:

```text
s = "abba"
```

---

## Index 0: Character `a`

```text
Window: "a"
left = 0
```

Map:

```text
a → 0
```

---

## Index 1: Character `b`

```text
Window: "ab"
left = 0
```

Map:

```text
a → 0
b → 1
```

---

## Index 2: Character `b`

The previous `b` is at index `1`.

Therefore:

```text
left = 1 + 1
left = 2
```

The new window is:

```text
"b"
```

---

## Index 3: Character `a`

The previous `a` is at index `0`.

If we blindly do:

```cpp
left = lastSeen['a'] + 1;
```

then:

```text
left = 0 + 1
left = 1
```

But the current value of `left` is already `2`.

This would move `left` backwards from `2` to `1`.

The resulting window would be:

```text
"bba"
```

This window contains duplicate `b` characters and is invalid.

Therefore, we use:

```cpp
left = max(left, lastSeen[current] + 1);
```

For the last `a`:

```text
left = max(2, 0 + 1)
left = max(2, 1)
left = 2
```

The left pointer stays at index `2`.

The current valid window is:

```text
"ba"
```

Therefore:

> The `max()` prevents the left pointer from moving backwards.

---

# Detailed Dry Run for `"ccbbcc"`

Consider:

```text
s = "ccbbcc"
```

The indices are:

```text
Index:      0 1 2 3 4 5
Character:  c c b b c c
```

| `right` | Character | Previous index | `left` before | `left` after | Current window | Length | Maximum |
|---:|:---:|---:|---:|---:|:---:|---:|---:|
| 0 | `c` | Not found | 0 | 0 | `"c"` | 1 | 1 |
| 1 | `c` | 0 | 0 | 1 | `"c"` | 1 | 1 |
| 2 | `b` | Not found | 1 | 1 | `"cb"` | 2 | 2 |
| 3 | `b` | 2 | 1 | 3 | `"b"` | 1 | 2 |
| 4 | `c` | 1 | 3 | 3 | `"bc"` | 2 | 2 |
| 5 | `c` | 4 | 3 | 5 | `"c"` | 1 | 2 |

Therefore:

```text
Answer = 2
```

The longest valid substrings include:

```text
"cb"
"bc"
```

---

# Why Must We Always Update the Map?

This line must execute during every iteration:

```cpp
mp[s[i]] = i;
```

The map must always store the character's latest occurrence.

Consider index `4` in:

```text
s = "ccbbcc"
```

At that point:

```text
left = 3
previous index of 'c' = 1
```

The previous `c` is outside the current window because:

```text
previous index < left
1 < 3
```

Therefore, we should not move `left`.

However, we must still update:

```cpp
mp['c'] = 4;
```

Otherwise, when we encounter the next `c` at index `5`, the map would still contain:

```text
'c' → 1
```

It would not know that `c` was most recently seen at index `4`.

That could create the incorrect window:

```text
"bcc"
```

and produce the incorrect answer:

```text
3
```

The important rule is:

> Moving the left pointer is conditional, but updating the latest index is unconditional.

---

# Complexity of the Optimal Approach

Each character is processed once.

The `right` pointer moves from the beginning to the end exactly once.

The `left` pointer only moves forward.

Average map lookup and insertion take `O(1)` time.

Therefore:

```text
Time Complexity:  O(n)
Space Complexity: O(n)
```

More precisely, the space complexity is `O(k)`, where `k` is the number of distinct characters.

---

# Alternative Using an Array

If the string contains ASCII characters, we can store the last-seen indices in an array instead of an unordered map.

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> lastSeen(256, -1);

        int left = 0;
        int result = 0;

        for (int right = 0; right < s.length(); right++) {
            unsigned char current = s[right];

            left = max(left, lastSeen[current] + 1);

            lastSeen[current] = right;

            int currentLength = right - left + 1;
            result = max(result, currentLength);
        }

        return result;
    }
};
```

Because the array always contains exactly `256` entries:

```text
Time Complexity:  O(n)
Space Complexity: O(1)
```

---

# 5. Similar Problems

The following problems use similar sliding-window ideas.

---

## 1. Longest Repeating Character Replacement

Find the longest substring that can be made of the same character after replacing at most `k` characters.

Pattern:

```text
Longest substring
+ at most K operations
+ frequency map
```

---

## 2. Minimum Window Substring

Find the smallest substring of one string containing all the required characters from another string.

Pattern:

```text
Smallest substring
+ character-frequency condition
```

---

## 3. Permutation in String

Determine whether one string contains a permutation of another string.

Pattern:

```text
Fixed-size window
+ character-frequency comparison
```

---

## 4. Find All Anagrams in a String

Find every starting position where an anagram of another string occurs.

Pattern:

```text
Fixed-size window
+ matching frequency maps
```

---

## 5. Fruit Into Baskets

Find the longest subarray containing at most two distinct values.

Pattern:

```text
Longest subarray
+ at most K distinct elements
```

Here:

```text
K = 2
```

---

## 6. Longest Substring With At Most K Distinct Characters

Find the longest substring containing at most `k` different characters.

Pattern:

```text
Longest substring
+ at most K distinct characters
```

---

## 7. Max Consecutive Ones III

Find the longest sequence of `1`s after changing at most `k` zeroes.

Pattern:

```text
Longest subarray
+ at most K invalid elements
```

---

## 8. Subarrays With K Different Integers

Count the number of subarrays containing exactly `k` distinct integers.

A common transformation is:

```text
Exactly K
=
At most K
-
At most (K - 1)
```

---

# 6. Mental Map for Recognizing This Pattern

Pattern recognition does not mean immediately knowing the complete solution.

It means noticing clues that suggest a family of possible solutions.

Use the following mental map.

---

## Step 1: Is the Question About a Continuous Portion?

Look for words such as:

```text
substring
subarray
continuous
contiguous
consecutive
window
segment
```

This problem asks for a:

```text
substring
```

Therefore, the answer must be a continuous portion of the string.

This gives us the first clue:

```text
This may be a sliding-window problem.
```

---

## Step 2: Is It Asking for Longest, Shortest, Maximum or Minimum?

Look for phrases such as:

```text
longest substring
shortest subarray
maximum continuous sequence
minimum-length window
```

This problem asks for:

```text
longest substring
```

This gives us the second clue:

```text
Try expanding a window while maintaining its validity.
```

---

## Step 3: Can the Window Be Checked Incrementally?

Ask:

> If I add one new character to the window, can I determine whether the window is valid without checking the complete substring again?

In this problem, we only need to know whether the newly added character already exists in the current window.

This information can be maintained using:

```text
A set
A frequency map
A last-seen index map
```

Therefore, we do not need to generate and validate every substring separately.

---

## Step 4: What Makes the Window Invalid?

For this problem, the window becomes invalid when:

```text
A character appears more than once.
```

Write the validity condition clearly:

```text
Valid window:
Every character has a frequency of at most 1.

Invalid window:
At least one character has a frequency greater than 1.
```

Once we know what makes the window invalid, we know when to move the left pointer.

---

## Step 5: What Should Happen When the Window Is Valid?

For longest-window problems:

```text
If the window is valid:
1. Update the answer.
2. Continue expanding the right pointer.
```

In code:

```cpp
result = max(result, right - left + 1);
```

---

## Step 6: What Should Happen When the Window Is Invalid?

Usually:

```text
If the window is invalid:
Move the left pointer until the window becomes valid again.
```

Set-based version:

```cpp
while (window is invalid) {
    remove s[left];
    left++;
}
```

Last-seen-index version:

```cpp
left = max(left, lastSeen[s[right]] + 1);
```

---

## Step 7: Can the Left Pointer Jump Directly?

In the set-based solution, the left pointer moves one position at a time.

But if we know the previous index of the duplicate character, we can directly move the left pointer after that position.

```cpp
left = previousIndex + 1;
```

This tells us that we need:

```text
character → latest index
```

Therefore, we use a map.

---

# General Sliding-Window Template

For a variable-size sliding window:

```cpp
int left = 0;
int result = 0;

for (int right = 0; right < n; right++) {
    // Add the right element to the window

    while (window is invalid) {
        // Remove the left element from the window
        left++;
    }

    // The window is valid here
    result = max(result, right - left + 1);
}
```

For this particular problem:

```cpp
int left = 0;
int result = 0;

for (int right = 0; right < s.length(); right++) {
    while (s[right] already exists in the window) {
        remove s[left] from the window;
        left++;
    }

    add s[right] to the window;

    result = max(result, right - left + 1);
}
```

---

# Fixed-Size vs Variable-Size Sliding Window

## Fixed-Size Sliding Window

Use a fixed-size window when the problem gives an exact window length.

Examples:

```text
Maximum sum of a subarray of size K
Find all anagrams of a pattern of length K
Find the average of every subarray of size K
```

Mental cue:

```text
The window size is already given.
```

A general fixed-size-window template is:

```cpp
for (int right = 0; right < n; right++) {
    // Add arr[right] to the window

    if (right - left + 1 > k) {
        // Remove arr[left] from the window
        left++;
    }

    if (right - left + 1 == k) {
        // Process the window
    }
}
```

---

## Variable-Size Sliding Window

Use a variable-size window when the window grows or shrinks depending on a condition.

Examples:

```text
Longest substring without repeating characters
Longest subarray with at most K distinct values
Minimum window containing all required characters
```

Mental cue:

```text
The window size is not given.
Its size depends on whether the window is valid.
```

This problem uses a variable-size sliding window.

---

# Pattern-Recognition Checklist

Whenever you see a new problem, ask these questions:

```text
1. Is the answer a continuous substring or subarray?

2. Is the problem asking for the longest, shortest,
   maximum or minimum range?

3. Can I maintain information about the current range
   using a set, map or frequency array?

4. What exactly makes the current window invalid?

5. When should I expand the right pointer?

6. When should I move the left pointer?

7. Can the left pointer jump directly instead of moving
   one position at a time?

8. What information must I store about previous elements?

9. Does the left pointer only move forward?

10. When should I update the answer?
```

For this problem, the answers are:

```text
1. Yes, it asks for a substring.

2. It asks for the longest one.

3. Yes, we can store character positions in a map.

4. A repeated character inside the current window
   makes the window invalid.

5. The right pointer expands during every iteration.

6. The left pointer moves when the current character
   already exists inside the current window.

7. Yes, left can jump to previousIndex + 1.

8. We store the latest index of every character.

9. Yes, left must never move backwards.

10. We update the answer after making sure that the
    current window is valid.
```

This reasoning naturally leads to the optimal solution.

---

# Short Mental Formula

Remember this:

```text
Longest continuous valid range
            ↓
Try a sliding window
            ↓
Expand the right pointer
            ↓
If invalid, move the left pointer
            ↓
Once valid, update the maximum
```

For character-related sliding-window problems:

```text
Need to know whether a character exists?
→ Use a set

Need to know how many times it appears?
→ Use a frequency map

Need to jump beyond its previous occurrence?
→ Use a last-seen index map
```

---

# Final Optimal Code

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0;
        int result = 0;

        unordered_map<char, int> lastSeen;

        for (int right = 0; right < s.length(); right++) {
            char current = s[right];

            if (lastSeen.find(current) != lastSeen.end()) {
                left = max(left, lastSeen[current] + 1);
            }

            lastSeen[current] = right;

            int currentLength = right - left + 1;
            result = max(result, currentLength);
        }

        return result;
    }
};
```

---

# Final Takeaway

Do not memorize only this line:

```cpp
left = max(left, lastSeen[current] + 1);
```

Instead, remember the reasoning:

```text
1. We need a continuous substring.

2. We need the longest valid substring.

3. Expanding right explores longer substrings.

4. A duplicate character makes the window invalid.

5. The previous duplicate must be excluded from the window.

6. Since we know its previous position, left can jump
   directly after that position.

7. The left pointer must never move backwards.

8. The latest position of every character must always
   be updated.

9. Once the window is valid, calculate its length using:

   right - left + 1

10. Keep track of the maximum length.
```

The most important lesson is:

> Sliding window is useful when a problem asks about a continuous range and we can efficiently maintain whether that range is valid while expanding and shrinking it.
