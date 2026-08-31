# Longest Repeating Character Replacement

## Problem

You are given:

- A string `s` containing uppercase English letters.
- An integer `k`.
- You can replace at most `k` characters with any uppercase English character.

Your task is to find the length of the longest substring that can be converted into a substring containing only one repeating character.

---

## Example

```text
Input:
s = "AABABBA"
k = 1

Output:
4
```

One possible substring is:

```text
AABA
```

Replace `B` with `A`:

```text
AABA → AAAA
```

Only one replacement is required, so the answer is `4`.

---

# 1. What Does the Problem Really Mean?

The problem is not directly asking:

> What is the longest substring containing identical characters?

Instead, it is asking:

> What is the longest substring that can be converted into identical characters using at most `k` replacements?

Consider the substring:

```text
AABBA
```

Character frequencies are:

```text
A → 3
B → 2
```

If we want the entire substring to contain the same character, the best choice is to keep the most frequent character and replace everything else.

Here, we keep the three `A`s and replace the two `B`s:

```text
AABBA → AAAAA
```

The number of replacements required is:

```text
substring length - frequency of the most frequent character
```

For this substring:

```text
5 - 3 = 2
```

Therefore, the central condition of the problem is:

```text
window length - maximum frequency in the window <= k
```

In code:

```cpp
(windowLength - maxFrequency) <= k
```

If this condition is true, the window is valid.

If it is false, the window requires more than `k` replacements.

---

# 2. The Most Important Observation

For every substring, we do not need to try replacing characters with every possible letter.

The best target character is always the character that already occurs most frequently in that substring.

Suppose the substring is:

```text
AABBC
```

Frequencies:

```text
A → 2
B → 2
C → 1
```

If we convert everything to `A`:

```text
Replacements = 5 - 2 = 3
```

If we convert everything to `B`:

```text
Replacements = 5 - 2 = 3
```

If we convert everything to `C`:

```text
Replacements = 5 - 1 = 4
```

Choosing the most frequent character minimizes the number of replacements.

Therefore:

```text
required replacements = substring length - max frequency
```

This equation is the foundation of every good solution to this problem.

---

# 3. Brute-Force Approach

## Idea

Generate every possible substring.

For each substring:

1. Count the frequency of every character.
2. Find the maximum character frequency.
3. Calculate how many replacements are required.
4. If the replacements are at most `k`, update the answer.

---

## Step-by-Step Example

Consider:

```text
s = "AABAB"
k = 1
```

We examine substrings such as:

```text
"A"
"AA"
"AAB"
"AABA"
"AABAB"
"AB"
"ABA"
...
```

For the substring:

```text
"AABA"
```

Frequencies:

```text
A → 3
B → 1
```

Required replacements:

```text
4 - 3 = 1
```

Since:

```text
1 <= k
```

the substring is valid.

For:

```text
"AABAB"
```

Frequencies:

```text
A → 3
B → 2
```

Required replacements:

```text
5 - 3 = 2
```

Since:

```text
2 > k
```

the substring is invalid.

---

## Brute-Force Code

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.length();
        int maxLen = 0;

        for (int start = 0; start < n; start++) {
            for (int end = start; end < n; end++) {
                unordered_map<char, int> frequency;

                for (int i = start; i <= end; i++) {
                    frequency[s[i]]++;
                }

                int maxFreq = 0;

                for (auto entry : frequency) {
                    maxFreq = max(maxFreq, entry.second);
                }

                int windowLength = end - start + 1;
                int replacementsNeeded = windowLength - maxFreq;

                if (replacementsNeeded <= k) {
                    maxLen = max(maxLen, windowLength);
                }
            }
        }

        return maxLen;
    }
};
```

---

## Complexity

There are approximately `O(n²)` substrings.

For every substring, we may traverse up to `O(n)` characters to calculate frequencies.

```text
Time Complexity:  O(n³)
Space Complexity: O(26) = O(1)
```

The space is considered constant because the string contains only uppercase English letters.

---

# 4. Better Approach Than Brute Force

## Main Improvement

The brute-force solution repeatedly calculates character frequencies from scratch.

For example, when processing:

```text
"AAB"
```

we already know the frequencies of:

```text
"AA"
```

Instead of recounting everything, we can extend the substring one character at a time and update the frequency map.

---

## Step-by-Step Derivation

Fix a starting index `left`.

Move `right` from `left` to the end of the string.

Whenever `right` moves:

1. Add `s[right]` to the frequency map.
2. Update `maxFreq`.
3. Calculate the window length.
4. Check whether the window requires at most `k` replacements.
5. Update the maximum answer if the window is valid.

---

## Better Code

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.length();
        int maxLen = 0;

        for (int left = 0; left < n; left++) {
            unordered_map<char, int> frequency;
            int maxFreq = 0;

            for (int right = left; right < n; right++) {
                frequency[s[right]]++;

                maxFreq = max(
                    maxFreq,
                    frequency[s[right]]
                );

                int windowLength = right - left + 1;
                int replacementsNeeded =
                    windowLength - maxFreq;

                if (replacementsNeeded <= k) {
                    maxLen = max(maxLen, windowLength);
                }
            }
        }

        return maxLen;
    }
};
```

---

## Complexity

The outer loop chooses the beginning of the substring.

The inner loop chooses the end of the substring.

Frequency updates take constant time.

```text
Time Complexity:  O(n²)
Space Complexity: O(26) = O(1)
```

This is better than `O(n³)`, but we are still considering every possible substring.

---

# 5. Moving From O(n²) to Sliding Window

The important question is:

> Do we really need to restart the search for every `left` position?

No.

Suppose the current window is:

```text
[left ... right]
```

If this window is valid, we should try to make it larger by moving `right`.

If the window becomes invalid, we should remove characters from the left until the window becomes usable again.

This naturally gives us a sliding-window approach.

---

## Why Sliding Window Works

The window condition is:

```text
window length - max frequency <= k
```

When `right` moves forward:

- The window becomes larger.
- The frequency of `s[right]` increases.
- The window may remain valid or become invalid.

If it becomes invalid:

```text
window length - max frequency > k
```

we shrink it from the left.

Therefore:

```text
Valid window   → expand right
Invalid window → move left
```

This is the sliding-window pattern.

---

# 6. Understanding Your Solution

Your solution correctly uses the following ideas:

- `left` and `right` define the current window.
- `mp` stores character frequencies inside the window.
- `maxFreq` stores the maximum frequency inside the window.
- The window is valid when:

```cpp
len - maxFreq <= k
```

Your validation function clearly expresses the core condition:

```cpp
bool isValidString(int len, int maxFreq, int k) {
    return len - maxFreq <= k;
}
```

When the window becomes invalid, you shrink it:

```cpp
while (!isValidString(right - left + 1, maxFreq, k)) {
    mp[s[left]]--;
    left++;

    maxFreq = obtainMaxFreq(mp);
}
```

Because removing the left character could reduce the true maximum frequency, you recalculate it using:

```cpp
maxFreq = obtainMaxFreq(mp);
```

---

## Your Complete Solution

```cpp
class Solution {
public:
    bool isValidString(int len, int maxFreq, int k) {
        return len - maxFreq <= k;
    }

    int obtainMaxFreq(unordered_map<char, int>& mp) {
        int maxVal = 0;

        for (auto x : mp) {
            maxVal = max(maxVal, x.second);
        }

        return maxVal;
    }

    int characterReplacement(string s, int k) {
        int n = s.length();

        int maxLen = 0;
        int maxFreq = 0;

        unordered_map<char, int> mp;

        int left = 0;
        int right = 0;

        while (right < n) {
            mp[s[right]]++;

            maxFreq = max(
                maxFreq,
                mp[s[right]]
            );

            if (isValidString(
                    right - left + 1,
                    maxFreq,
                    k
                )) {
                maxLen = max(
                    maxLen,
                    right - left + 1
                );
            } else {
                while (!isValidString(
                            right - left + 1,
                            maxFreq,
                            k
                       )) {
                    mp[s[left]]--;
                    left++;

                    maxFreq = obtainMaxFreq(mp);
                }

                maxLen = max(
                    maxLen,
                    right - left + 1
                );
            }

            right++;
        }

        return maxLen;
    }
};
```

---

## Complexity of Your Solution

The `right` pointer moves from left to right once.

The `left` pointer also moves from left to right at most once.

However, every time the window shrinks, this function scans the frequency map:

```cpp
int obtainMaxFreq(unordered_map<char, int>& mp)
```

Since the input contains only 26 uppercase English letters, this scan takes at most `O(26)` time.

Therefore:

```text
Time Complexity:  O(26 × n), which is effectively O(n)
Space Complexity: O(26), which is effectively O(1)
```

Your solution is already efficient.

It maintains the exact maximum frequency of the current window.

---

# 7. Cleaner Version of Your Approach

Because the input contains only uppercase letters, an array can be used instead of an `unordered_map`.

```cpp
class Solution {
public:
    int getMaxFrequency(const vector<int>& frequency) {
        int maxFreq = 0;

        for (int value : frequency) {
            maxFreq = max(maxFreq, value);
        }

        return maxFreq;
    }

    int characterReplacement(string s, int k) {
        vector<int> frequency(26, 0);

        int left = 0;
        int maxLen = 0;
        int maxFreq = 0;

        for (int right = 0; right < s.length(); right++) {
            frequency[s[right] - 'A']++;

            maxFreq = max(
                maxFreq,
                frequency[s[right] - 'A']
            );

            while ((right - left + 1) - maxFreq > k) {
                frequency[s[left] - 'A']--;
                left++;

                maxFreq = getMaxFrequency(frequency);
            }

            maxLen = max(
                maxLen,
                right - left + 1
            );
        }

        return maxLen;
    }
};
```

This solution still maintains the exact maximum frequency.

```text
Time Complexity:  O(26 × n) = O(n)
Space Complexity: O(26) = O(1)
```

---

# 8. Optimal Sliding-Window Solution

The optimal solution makes one subtle improvement:

> We do not recalculate `maxFreq` when the left side of the window moves.

At first, this can feel incorrect.

If we remove the character responsible for `maxFreq`, shouldn't `maxFreq` decrease?

For this problem, it does not need to decrease.

---

## Optimal Code

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> frequency(26, 0);

        int left = 0;
        int maxFreq = 0;
        int maxLen = 0;

        for (int right = 0; right < s.length(); right++) {
            frequency[s[right] - 'A']++;

            maxFreq = max(
                maxFreq,
                frequency[s[right] - 'A']
            );

            int windowLength = right - left + 1;
            int replacementsNeeded =
                windowLength - maxFreq;

            while (replacementsNeeded > k) {
                frequency[s[left] - 'A']--;
                left++;

                windowLength = right - left + 1;
                replacementsNeeded =
                    windowLength - maxFreq;
            }

            maxLen = max(
                maxLen,
                right - left + 1
            );
        }

        return maxLen;
    }
};
```

A more compact version is:

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> frequency(26, 0);

        int left = 0;
        int maxFreq = 0;
        int maxLen = 0;

        for (int right = 0; right < s.length(); right++) {
            frequency[s[right] - 'A']++;

            maxFreq = max(
                maxFreq,
                frequency[s[right] - 'A']
            );

            while ((right - left + 1) - maxFreq > k) {
                frequency[s[left] - 'A']--;
                left++;
            }

            maxLen = max(
                maxLen,
                right - left + 1
            );
        }

        return maxLen;
    }
};
```

---

# 9. Why Don't We Decrease `maxFreq`?

This is the trickiest part of the optimal solution.

`maxFreq` does not always represent the exact maximum frequency in the current window.

Instead, it represents:

> The highest frequency we have seen for a character while expanding the window.

Therefore, `maxFreq` can sometimes be stale.

---

## What Is a Stale `maxFreq`?

Suppose an earlier window contained four `A`s:

```text
maxFreq = 4
```

Later, the left pointer moves and removes one of those `A`s.

The current window might contain only three `A`s, but we still keep:

```text
maxFreq = 4
```

This means `maxFreq` is no longer the exact maximum frequency of the current window.

It is an older, larger value.

---

## Why Is This Still Safe?

Our goal is not to return the contents of one particular window.

Our goal is to find the maximum achievable window length.

The window condition can be rewritten as:

```text
window length <= maxFreq + k
```

This says that a useful window can contain:

- `maxFreq` copies of one character.
- At most `k` other characters.

Once we have previously seen a frequency of `maxFreq`, any better answer must either:

1. Use the same `maxFreq` with available replacements.
2. Discover a larger `maxFreq`.

Decreasing `maxFreq` would only cause the window to shrink earlier. It would not help us discover a longer answer.

A stale `maxFreq` may delay shrinking, but it cannot produce an answer longer than what is supported by a frequency that was genuinely observed earlier.

Therefore, keeping `maxFreq` non-decreasing is sufficient for finding the maximum length.

---

## Another Way to Think About It

We are looking for the largest possible window satisfying:

```text
window length <= maxFreq + k
```

If:

```text
maxFreq = 4
k = 2
```

the largest useful window supported by this frequency is:

```text
4 + 2 = 6
```

To find a window longer than `6`, we must discover a character with a frequency greater than `4`.

Therefore, there is no need to reduce `maxFreq`.

We only care when it increases because an increased `maxFreq` can support a larger answer.

---

# 10. Dry Run of the Optimal Solution

Consider:

```text
s = "AABABBA"
k = 1
```

Initially:

```text
left = 0
maxFreq = 0
maxLen = 0
```

---

## Add the First `A`

```text
Window: "A"
Frequency: A → 1
maxFreq: 1
Window length: 1
Replacements: 1 - 1 = 0
```

The window is valid:

```text
maxLen = 1
```

---

## Add the Second `A`

```text
Window: "AA"
Frequency: A → 2
maxFreq: 2
Window length: 2
Replacements: 2 - 2 = 0
```

The window is valid:

```text
maxLen = 2
```

---

## Add `B`

```text
Window: "AAB"

Frequency:
A → 2
B → 1

maxFreq: 2
Window length: 3
Replacements: 3 - 2 = 1
```

The window is valid because:

```text
1 <= k
```

Therefore:

```text
maxLen = 3
```

---

## Add `A`

```text
Window: "AABA"

Frequency:
A → 3
B → 1

maxFreq: 3
Window length: 4
Replacements: 4 - 3 = 1
```

The window is valid:

```text
maxLen = 4
```

---

## Add `B`

```text
Window: "AABAB"

Frequency:
A → 3
B → 2

maxFreq: 3
Window length: 5
Replacements: 5 - 3 = 2
```

The window is invalid because:

```text
2 > k
```

Remove the leftmost `A`:

```text
Window: "ABAB"
Window length: 4
```

The window size is brought back under control.

---

## Remaining Characters

As the remaining characters are processed, the window continues expanding and shrinking according to:

```text
window length - maxFreq <= k
```

The final maximum length is:

```text
4
```

---

# 11. Why This Is a Variable-Size Sliding Window Problem

There are two common types of sliding windows.

## Fixed-Size Sliding Window

The window size is already given.

Example:

> Find the maximum sum of any subarray of size `k`.

---

## Variable-Size Sliding Window

The window size is not given.

Instead, the problem gives a validity condition.

Example:

> Find the longest substring that can be made equal using at most `k` replacements.

Here, the validity condition is:

```text
window length - max frequency <= k
```

The words that signal this pattern are:

```text
Longest substring
At most k operations
Consecutive characters
```

These are strong signs of a variable-size sliding-window problem.

---

# 12. Mental Model

Use the following mental model:

> Keep the majority character and pay for everything else.

Inside any window:

```text
Majority characters → free
Other characters    → replacements required
```

For example:

```text
Window: A A B A C
```

Frequencies:

```text
A → 3
B → 1
C → 1
```

Keep the `A`s and replace `B` and `C`.

```text
Replacement cost = 2
```

Using the formula:

```text
window length - majority count
= 5 - 3
= 2
```

Therefore, while solving the problem, think:

```text
Window length = all characters
Max frequency = characters we keep
Difference    = characters we replace
```

---

# 13. How to Recognize the Correct Pattern

Do not try to recognize the entire solution immediately.

Instead, ask a sequence of small questions.

---

## Question 1: Are We Looking for a Contiguous Part?

The problem asks for a substring.

A substring is contiguous.

```text
Substring   → consider a sliding window
Subsequence → not necessarily a window problem
```

So sliding window becomes a candidate.

---

## Question 2: Are We Looking for the Longest or Shortest Valid Region?

The problem asks for the longest substring.

This suggests maintaining a window and trying to expand it.

```text
Longest valid window → expand whenever possible
```

---

## Question 3: What Makes a Window Valid?

We can perform at most `k` replacements.

Therefore, we must determine:

```text
How many replacements does this window require?
```

---

## Question 4: What Should All Characters Be Converted Into?

They should be converted into the most frequent character in the window.

Why?

Because this requires the fewest replacements.

---

## Question 5: How Many Characters Must Be Replaced?

```text
replacements = window length - max frequency
```

---

## Question 6: What Should We Do When the Window Becomes Invalid?

If:

```text
window length - max frequency > k
```

the window needs too many replacements.

Move `left` forward to reduce the window.

---

## Complete Recognition Chain

```text
Substring
    ↓
Contiguous region
    ↓
Longest valid region
    ↓
Variable-size sliding window
    ↓
Need a validity condition
    ↓
Keep the most frequent character
    ↓
Replace every other character
    ↓
window length - max frequency <= k
```

---

# 14. Sliding-Window Template for This Pattern

```cpp
int left = 0;
int answer = 0;

for (int right = 0; right < n; right++) {
    // Add s[right] to the current window.

    while (windowIsInvalid()) {
        // Remove s[left] from the current window.
        left++;
    }

    answer = max(
        answer,
        right - left + 1
    );
}
```

For this problem:

```cpp
windowIsInvalid()
```

means:

```cpp
(right - left + 1) - maxFreq > k
```

---

# 15. General Pattern Behind the Problem

This problem belongs to the following general family:

> Find the longest window whose adjustment cost is at most `k`.

The structure is:

```text
cost(window) <= k
```

For this problem:

```text
cost(window) = window length - maximum frequency
```

Other sliding-window problems use different costs:

```text
Number of zeroes in the window
Number of distinct characters
Sum of values in the window
Difference between maximum and minimum
Number of duplicate elements
```

The exact formula changes, but the window process remains similar:

```text
Expand
    ↓
Calculate cost
    ↓
Shrink if the cost exceeds the budget
    ↓
Update the answer
```

---

# 16. Similar Problems

## 1. Max Consecutive Ones III

You are allowed to flip at most `k` zeroes into ones.

Mental model:

```text
Keep all ones.
Pay one operation for every zero.
```

Validity condition:

```text
number of zeroes in the window <= k
```

This is the closest simpler version of Longest Repeating Character Replacement.

---

## 2. Longest Substring Without Repeating Characters

Find the longest substring containing no duplicate characters.

Validity condition:

```text
frequency of every character <= 1
```

When a duplicate appears, shrink the window.

---

## 3. Fruit Into Baskets

Find the longest subarray containing at most two distinct values.

Validity condition:

```text
number of distinct values <= 2
```

---

## 4. Longest Substring With At Most K Distinct Characters

Validity condition:

```text
number of distinct characters <= k
```

---

## 5. Minimum Window Substring

Find the smallest window containing all required characters.

This is a harder sliding-window problem because it asks for the minimum valid window instead of the maximum valid window.

---

## 6. Permutation in String

Determine whether a fixed-size window contains the required character frequencies.

This combines:

- Sliding window
- Frequency maps
- Fixed-size windows

---

## 7. Find All Anagrams in a String

Maintain a fixed-size window and compare character frequencies.

---

## 8. Frequency of the Most Frequent Element

After sorting, determine the longest range that can be converted to the same value using at most `k` increments.

Its cost calculation is different, but the mental model is similar:

```text
Choose one target value.
Calculate the cost of converting everything else.
```

---

# 17. Common Mistakes

## Mistake 1: Checking Only the Number of Distinct Characters

A window can contain several distinct characters and still be valid.

Example:

```text
Window: "ABCA"
k = 2
```

Frequencies:

```text
A → 2
B → 1
C → 1
```

Required replacements:

```text
4 - 2 = 2
```

The window is valid even though it contains three distinct characters.

The correct condition is not:

```text
distinct characters <= k
```

It is:

```text
window length - max frequency <= k
```

---

## Mistake 2: Replacing the Most Frequent Character

The most frequent character should be kept.

All the other characters should be replaced.

```text
Keep:    max frequency characters
Replace: window length - max frequency characters
```

---

## Mistake 3: Thinking We Need to Perform the Replacements

We do not need to construct the modified string.

We only need to calculate how many replacements would be required.

---

## Mistake 4: Forgetting That the Problem Requires a Substring

A substring is contiguous.

We cannot choose characters from unrelated positions.

---

## Mistake 5: Recomputing Too Much

In the brute-force approach, frequencies are repeatedly rebuilt.

Sliding window allows us to:

```text
Add one character from the right.
Remove one character from the left.
```

This avoids repeated work.

---

## Mistake 6: Becoming Confused by the Stale `maxFreq`

There are two valid versions.

### Exact-Frequency Version

Recalculate `maxFreq` after shrinking.

```text
Easier to reason about
Time: O(26 × n)
```

### Stale-Frequency Version

Never decrease `maxFreq`.

```text
More subtle
Time: O(n)
```

Since there are only 26 uppercase letters, both versions are practically linear.

It is completely acceptable to first master the exact-frequency solution before learning the stale-frequency optimization.

---

# 18. How to Build Pattern-Recognition Skill

When you encounter a new problem, do not immediately ask:

> Which algorithm should I use?

Instead, write down these facts:

```text
1. What am I searching for?
2. Is the answer contiguous?
3. Is the problem asking for the longest or shortest region?
4. What makes a candidate valid?
5. Can validity be updated when one element enters or leaves?
6. Is there an operation budget such as "at most k"?
```

For this problem:

```text
What am I searching for?
→ Longest substring

Is it contiguous?
→ Yes

Longest or shortest?
→ Longest

What makes a window valid?
→ It requires at most k replacements

How do I calculate replacements?
→ Window length - maximum frequency

Can frequencies be updated incrementally?
→ Yes

Pattern:
→ Variable-size sliding window with a frequency map
```

---

# 19. Reusable Sliding-Window Checklist

Whenever you see:

```text
Longest or shortest substring/subarray
At most k operations
Continuous or contiguous elements
```

check whether a variable-size sliding window can work.

Then identify the following.

## Window State

What information must be maintained?

For this problem:

```text
Character frequencies
Maximum character frequency
```

## Validity Condition

When is the window valid?

```text
window length - max frequency <= k
```

## Expansion

What changes when `right` moves?

```text
Increase the frequency of s[right]
Update maxFreq
```

## Shrinking

What changes when `left` moves?

```text
Decrease the frequency of s[left]
Move left forward
```

## Answer

When should the result be updated?

```text
After the window satisfies the validity condition
```

---

# 20. Final Optimal Solution With Explanatory Names

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> frequency(26, 0);

        int left = 0;
        int highestFrequencySeen = 0;
        int longestWindow = 0;

        for (int right = 0; right < s.length(); right++) {
            int rightCharacter = s[right] - 'A';

            frequency[rightCharacter]++;

            highestFrequencySeen = max(
                highestFrequencySeen,
                frequency[rightCharacter]
            );

            int windowLength = right - left + 1;
            int replacementsNeeded =
                windowLength - highestFrequencySeen;

            while (replacementsNeeded > k) {
                int leftCharacter = s[left] - 'A';

                frequency[leftCharacter]--;
                left++;

                windowLength = right - left + 1;
                replacementsNeeded =
                    windowLength - highestFrequencySeen;
            }

            longestWindow = max(
                longestWindow,
                right - left + 1
            );
        }

        return longestWindow;
    }
};
```

---

# 21. Complexity of the Optimal Solution

Each character enters the window once through `right`.

Each character leaves the window at most once through `left`.

```text
Time Complexity:  O(n)
Space Complexity: O(26) = O(1)
```

---

# 22. Final Takeaway

The entire problem can be reduced to one sentence:

> In every window, keep the most frequent character and replace all the remaining characters.

That produces the key equation:

```text
required replacements
= window length - maximum character frequency
```

The window is valid when:

```text
window length - maximum character frequency <= k
```

The complete mental pattern is:

```text
Longest contiguous region
+ at most k modifications
+ efficiently maintainable validity condition
= variable-size sliding window
```

When solving similar problems, focus first on discovering the validity equation.

Once that equation is clear, the sliding-window implementation usually becomes much easier.
