# Merge Intervals (LeetCode 56)

- **Difficulty:** Medium
- **Topic:** Arrays, Sorting, Intervals
- **Pattern:** Merge Overlapping Intervals

---

# Problem Statement

You are given an array of intervals where:

```
intervals[i] = [starti, endi]
```

Merge all overlapping intervals and return an array of the non-overlapping intervals that cover all the intervals in the input.

### Example

**Input**

```
[[1,3],[2,6],[8,10],[15,18]]
```

**Output**

```
[[1,6],[8,10],[15,18]]
```

Explanation:

```
[1,3]
    [2,6]
---------
[1,6]
```

---

# Understanding the Problem

Each interval represents a range.

For example,

```
[2,5]
```

means

```
2 ---- 3 ---- 4 ---- 5
```

If another interval begins before this interval ends, they overlap.

Example:

```
[1,4]
    [2,5]
```

These become

```
[1,5]
```

---

# Visual Understanding

Suppose we have

```
[1,3]
[2,6]
[8,10]
[15,18]
```

Visualize them as

```
1------3
   2---------6

8------10

15------18
```

First two overlap.

Result becomes

```
1-------------6

8------10

15------18
```

---

# Brute Force Approach

## Idea

For every interval,

- compare it with every other interval
- merge whenever overlap occurs
- repeat until no more merges are possible

Pseudo steps

```
Repeat
    merged = false

    for every pair
        if overlap
            merge
            remove one interval
            merged = true

Until merged == false
```

---

## Complexity

Time

```
O(N²)
```

Space

```
O(1)
```

Very inefficient because every interval is compared multiple times.

---

# Better Observation

Suppose intervals are

```
[8,10]
[1,3]
[2,6]
```

Without sorting,

we don't know which intervals should be merged first.

If we sort them,

```
[1,3]
[2,6]
[8,10]
```

Now we only need to compare with the previous merged interval.

Sorting converts a difficult problem into a simple linear scan.

---

# Key Observation

After sorting by starting point,

if

```
current.start <= previous.end
```

then they overlap.

Otherwise,

they never will.

This is because all future intervals start even later.

---

# Why Sorting Works

Suppose

```
[1,4]
[2,5]
[7,9]
```

Sorted order guarantees

```
1 <= 2 <= 7
```

If

```
2 <= 4
```

merge them.

Now merged interval becomes

```
[1,5]
```

Next,

```
7 > 5
```

No overlap.

Start a new interval.

Notice that we never need to look backward again.

---

# Optimal Approach

## Step 1

Sort intervals.

```
sort(intervals.begin(), intervals.end());
```

After sorting

```
[1,3]
[2,6]
[8,10]
[15,18]
```

---

## Step 2

Initialize

```
start = first interval start
end = first interval end
```

Current merged interval

```
[start,end]
```

---

## Step 3

Traverse remaining intervals.

If overlap exists

```
current.start <= end
```

extend the interval.

```
end = max(end,current.end)
```

Otherwise,

store current interval.

```
res.push_back({start,end})
```

and begin a new interval.

---

## Step 4

After traversal,

don't forget to insert the final interval.

---

# Dry Run

Input

```
[[1,3],[2,6],[8,10],[15,18]]
```

Initially

```
start = 1
end = 3
```

Result

```
[]
```

---

Current interval

```
[2,6]
```

Check

```
2 <= 3

Yes
```

Merge

```
end = max(3,6)

=6
```

Current merged interval

```
[1,6]
```

---

Current interval

```
[8,10]
```

Check

```
8 <= 6

No
```

Store

```
[1,6]
```

Now

```
start=8
end=10
```

---

Current interval

```
[15,18]
```

Check

```
15 <=10

No
```

Store

```
[8,10]
```

Current

```
start=15
end=18
```

Traversal ends.

Store last interval

```
[15,18]
```

Final answer

```
[[1,6],[8,10],[15,18]]
```

---

# Complete Code

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        vector<vector<int>> res;

        sort(intervals.begin(), intervals.end());

        int n = intervals.size();

        int start = intervals[0][0];
        int end = intervals[0][1];

        for(int i = 1; i < n; i++) {

            if(intervals[i][0] <= end) {

                end = max(end, intervals[i][1]);

            } else {

                res.push_back({start, end});

                start = intervals[i][0];
                end = intervals[i][1];
            }
        }

        res.push_back({start, end});

        return res;
    }
};
```

---

# Line-by-Line Explanation

## Create answer

```cpp
vector<vector<int>> res;
```

Stores merged intervals.

---

## Sort

```cpp
sort(intervals.begin(), intervals.end());
```

Sorts according to

- start
- then end

Automatically because vector comparison is lexicographical.

---

## Initialize

```cpp
start = intervals[0][0];
end = intervals[0][1];
```

Current merged interval.

---

## Traverse

```cpp
for(...)
```

Process every interval once.

---

## Overlap

```cpp
if(intervals[i][0] <= end)
```

Example

```
Current merged

[1,6]

Next

[4,8]
```

Since

```
4 <= 6
```

they overlap.

---

## Merge

```cpp
end = max(end, intervals[i][1]);
```

Example

```
[1,6]

[4,8]
```

becomes

```
[1,8]
```

---

## No overlap

```cpp
res.push_back({start,end});
```

Store current interval.

Begin new interval.

---

## Store final interval

After loop,

the current interval hasn't been stored.

Hence

```cpp
res.push_back({start,end});
```

---

# Why We Compare Only With Current Interval

Suppose

```
Sorted

[1,4]
[2,7]
[5,8]
```

Merge first two

```
[1,7]
```

Now compare only

```
[1,7]

with

[5,8]
```

Result

```
[1,8]
```

No need to compare

```
[5,8]

with

[1,4]
```

because

```
[1,4]

already became

[1,7]
```

---

# Correctness Proof (Greedy)

After sorting,

the current merged interval always contains every interval processed so far.

If next interval overlaps,

merging is always optimal because

```
Union(A,B)
```

must be represented by one interval.

If next interval doesn't overlap,

no future interval can overlap with the current interval because future intervals start even later.

Therefore storing it is safe.

Hence algorithm is correct.

---

# Complexity Analysis

## Sorting

```
O(N log N)
```

---

## Traversal

```
O(N)
```

---

Total

```
O(N log N)
```

---

Extra Space

Ignoring output,

```
O(1)
```

Output array

```
O(N)
```

---

# Edge Cases

## Single interval

```
[[5,8]]
```

Output

```
[[5,8]]
```

---

## Already merged

```
[[1,2],[3,4]]
```

Output

```
[[1,2],[3,4]]
```

---

## Everything overlaps

```
[[1,5],[2,6],[3,7]]
```

Output

```
[[1,7]]
```

---

## Same intervals

```
[[1,4],[1,4]]
```

Output

```
[[1,4]]
```

---

## Touching intervals

```
[1,4]

[4,5]
```

They merge because

```
4 <= 4
```

Output

```
[1,5]
```

---

# Common Mistakes

## Forgetting to sort

The algorithm only works after sorting.

---

## Forgetting final push

Many people return

```
res
```

without inserting the last interval.

---

## Wrong overlap condition

Wrong

```cpp
current.start < end
```

Correct

```cpp
current.start <= end
```

Because

```
[1,4]

[4,5]
```

should merge.

---

## Updating start during merge

Never do

```cpp
start = current.start;
```

while merging.

Only update

```
end
```

---

# Pattern Recognition

Whenever the question contains

- intervals
- ranges
- meeting times
- schedules
- segments
- overlapping events

Think

```
Sort + Linear Scan
```

This is one of the most common interview patterns.

---

# Interview Tips

If you see

```
Merge
Overlap
Union
Meeting
Ranges
Intervals
```

Immediately think

```
1. Sort

2. Maintain current merged interval

3. Expand if overlap

4. Store otherwise
```

---

# Similar Problems

## Easy

- Insert Interval
- Meeting Rooms

---

## Medium

- Meeting Rooms II
- Non-overlapping Intervals
- Minimum Number of Arrows to Burst Balloons
- Partition Labels
- Video Stitching

---

## Hard

- Employee Free Time
- Data Stream as Disjoint Intervals
- Range Module

---

# Key Takeaways

- Sorting simplifies interval problems.
- Compare only with the current merged interval.
- Extend the end when overlap exists.
- Store the interval only when overlap stops.
- Never forget the last interval.
- Time complexity is dominated by sorting.
- "Sort + Greedy Scan" is the standard pattern for interval merging.

---

# Template for Merge Interval Problems

```cpp
sort(intervals.begin(), intervals.end());

vector<vector<int>> ans;

int start = intervals[0][0];
int end = intervals[0][1];

for(int i = 1; i < intervals.size(); i++)
{
    if(intervals[i][0] <= end)
    {
        end = max(end, intervals[i][1]);
    }
    else
    {
        ans.push_back({start, end});

        start = intervals[i][0];
        end = intervals[i][1];
    }
}

ans.push_back({start, end});

return ans;
```

This template works for a large class of interval-merging problems and is one of the most important greedy patterns to master.
