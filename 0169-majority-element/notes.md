# Majority Element - Complete Handbook

## Problem

Given an array of size `n`, find the element that appears more than
`n/2` times.

The problem guarantees that such an element exists.

------------------------------------------------------------------------

# Approach 1: Brute Force

For every element, count its occurrences by scanning the entire array.

    for each i:
        count = 0
        for each j:
            if nums[i] == nums[j]:
                count++

If `count > n/2`, return it.

**Time:** O(n²)

**Space:** O(1)

------------------------------------------------------------------------

# Approach 2: Hash Map

Store frequencies.

    unordered_map<int,int> freq;

    for(num : nums)
        freq[num]++;

Return the element whose frequency exceeds `n/2`.

**Time:** O(n)

**Space:** O(n)

------------------------------------------------------------------------

# Approach 3: Sorting

Sort the array.

The majority element must occupy the middle index.

Example

    2 2 1 2 3

    ↓

    1 2 2 2 3

    Middle = 2

**Time:** O(n log n)

**Space:** Depends on sort implementation.

------------------------------------------------------------------------

# Approach 4: Moore's Voting Algorithm (Optimal)

## Key Idea

Think of every occurrence of the majority element as a **+1 vote** and
every different element as a **-1 vote**.

Different elements cancel each other.

Since the majority element appears more than half the time, it can never
be completely cancelled.

------------------------------------------------------------------------

## Algorithm

Maintain

-   candidate
-   count

Rules:

-   If count becomes 0, choose current element as candidate.
-   Same element -\> count++
-   Different element -\> count--

------------------------------------------------------------------------

## Visual Example

    nums =

    2 2 1 1 1 2 2

  Element   Candidate     Count
  --------- ----------- -------
  2         2                 1
  2         2                 2
  1         2                 1
  1         2                 0
  1         1                 1
  2         1                 0
  2         2                 1

Answer = 2

------------------------------------------------------------------------

## Why It Works

Imagine cancelling one majority element with one non-majority element.

    2 2 2 2 1 1

    ↓

    2 2

No matter how cancellations happen, the majority survives because it
occurs more than all other elements combined.

------------------------------------------------------------------------

## Verification Step

If the problem **does not guarantee** a majority element, verify the
candidate:

    candidate = MooreVoting(nums)

    count occurrences of candidate

    if count > n/2:
        return candidate
    else:
        return -1

------------------------------------------------------------------------

# Complexity Comparison

  Approach               Time           Space
  -------------- ------------ ---------------
  Brute Force           O(n²)            O(1)
  Hash Map               O(n)            O(n)
  Sorting          O(n log n)   O(1)/O(log n)
  Moore Voting           O(n)            O(1)

------------------------------------------------------------------------

# Pattern Recognition

Use Moore Voting when:

-   One element appears more than half the time.
-   Need O(1) extra space.
-   Majority guarantees exist.

------------------------------------------------------------------------

# Similar Problems

-   Majority Element II (\> n/3)
-   Find All Elements Appearing More Than n/k Times
-   Boyer-Moore Voting Variants
-   Top K Frequent Elements
-   Frequency of the Most Frequent Element

------------------------------------------------------------------------

# Common Mistakes

-   Forgetting verification when majority isn't guaranteed.
-   Resetting candidate incorrectly.
-   Assuming the final candidate is always valid in arbitrary inputs.

------------------------------------------------------------------------

# Key Notes

-   Moore's Voting is a **cancellation algorithm**.
-   Majority element survives pairwise cancellation.
-   It is one of the most important interview algorithms because it
    achieves **O(n)** time and **O(1)** space.
-   Your implementation correctly follows Moore's Voting Algorithm.
