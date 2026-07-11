# Palindrome Linked List - Complete Handbook

## Problem

Given the head of a singly linked list, determine whether it is a
palindrome.

A palindrome reads the same from left to right and right to left.

Example:

    1 -> 2 -> 2 -> 1   ✓

    1 -> 2 -> 3 -> 2 -> 1   ✓

    1 -> 2 -> 3 -> 4   ✗

------------------------------------------------------------------------

# Approach 1: Copy Values into an Array (Your Solution)

## Intuition

A singly linked list cannot be traversed backwards efficiently.

Convert the linked list into an array.

Then the problem becomes identical to checking whether an array is a
palindrome.

### Algorithm

1.  Traverse the linked list.
2.  Store every value into a vector.
3.  Compare elements from both ends.

``` cpp
vector<int> nums;

while(head){
    nums.push_back(head->val);
    head=head->next;
}

int left=0;
int right=nums.size()-1;

while(left<right){
    if(nums[left]!=nums[right])
        return false;
    left++;
    right--;
}

return true;
```

### Complexity

Time: **O(n)**

Space: **O(n)**

------------------------------------------------------------------------

# Approach 2: Recursive Comparison

## Idea

Recursively reach the end of the list.

During backtracking, compare nodes from both ends.

Maintain a pointer from the front.

Time: **O(n)**

Space: **O(n)** (recursion stack)

------------------------------------------------------------------------

# Approach 3: Optimal - Reverse Second Half

This is the interview-preferred solution.

## Step 1

Find the middle using slow and fast pointers.

    slow -> moves 1 step

    fast -> moves 2 steps

When fast reaches the end,

slow points to the middle.

------------------------------------------------------------------------

## Step 2

Reverse the second half.

Example

Before

    1 -> 2 -> 3 -> 2 -> 1

                 ↑
                slow

After reversing

    1 -> 2 -> 3

    1 <- 2

------------------------------------------------------------------------

## Step 3

Compare first half and reversed second half.

    1 == 1

    2 == 2

    3 == 3

If all match,

the list is a palindrome.

------------------------------------------------------------------------

## Step 4 (Optional)

Restore the linked list by reversing the second half again.

Many interviewers appreciate restoring the original list.

------------------------------------------------------------------------

## Complexity

Time: **O(n)**

Space: **O(1)**

------------------------------------------------------------------------

# Why Reverse Only the Second Half?

The first half already exists in the correct order.

Reversing only the second half allows both pointers to move forward
while comparing corresponding elements.

No extra memory is required.

------------------------------------------------------------------------

# Dry Run

Input

    1 -> 2 -> 3 -> 2 -> 1

Find middle

    slow

    ↓

    1 -> 2 -> 3 -> 2 -> 1

Reverse second half

    First Half

    1 -> 2 -> 3

    Second Half

    1 -> 2

Compare

    1 == 1

    2 == 2

    3 == 3

Answer

    True

------------------------------------------------------------------------

# Complexity Comparison

  Approach              Time   Space
  --------------------- ------ -------
  Copy to Array         O(n)   O(n)
  Recursion             O(n)   O(n)
  Reverse Second Half   O(n)   O(1)

------------------------------------------------------------------------

# Pattern Recognition

Whenever the problem asks

-   Compare first half and second half
-   Mirror comparison
-   Middle of linked list
-   Reverse linked list

Think about

-   Slow & Fast pointers
-   Reverse Linked List

------------------------------------------------------------------------

# Similar Problems

## Fast & Slow Pointer

-   Middle of Linked List
-   Linked List Cycle
-   Linked List Cycle II
-   Happy Number
-   Find Duplicate Number

------------------------------------------------------------------------

## Reverse Linked List

-   Reverse Linked List
-   Reverse Linked List II
-   Reverse Nodes in k-Group
-   Reorder List
-   Swap Nodes in Pairs

------------------------------------------------------------------------

## Palindrome Problems

-   Valid Palindrome
-   Valid Palindrome II
-   Palindrome Number
-   Longest Palindromic Substring
-   Palindromic Substrings

------------------------------------------------------------------------

# Common Mistakes

❌ Comparing one extra element.

Instead of

``` cpp
for(int i=0;i<=n/2;i++)
```

use

``` cpp
for(int i=0;i<n/2;i++)
```

or

``` cpp
while(left<right)
```

------------------------------------------------------------------------

❌ Forgetting to restore the list after reversing.

------------------------------------------------------------------------

❌ Incorrect middle calculation for even-length lists.

------------------------------------------------------------------------

# Key Takeaways

-   Your solution is simple and perfectly acceptable in many interviews.
-   The optimal solution uses:
    -   Fast & Slow pointers
    -   Reverse Linked List
-   Only the second half needs to be reversed.
-   The optimal solution achieves **O(n)** time and **O(1)** extra
    space.
-   This problem is a combination of two classic linked-list patterns:
    -   Finding the middle
    -   Reversing a linked list
