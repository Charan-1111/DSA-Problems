# Search Insert Position (LeetCode 35)

## Problem

Given a sorted array `nums` and a `target`, return: - the index if the
target exists. - otherwise, the index where it should be inserted to
keep the array sorted.

------------------------------------------------------------------------

# Approach 1: Linear Search

Traverse from left to right.

``` cpp
for (int i = 0; i < nums.size(); i++) {
    if (nums[i] >= target) return i;
}
return nums.size();
```

### Complexity

-   Time: **O(n)**
-   Space: **O(1)**

Pros: - Very easy. - Works for small arrays.

Cons: - Doesn't use the sorted property.

------------------------------------------------------------------------

# Approach 2: Classic Binary Search (Lower Bound)

Find the first index where `nums[i] >= target`.

``` cpp
int l = 0, r = nums.size() - 1;
int ans = nums.size();

while (l <= r) {
    int mid = l + (r - l) / 2;

    if (nums[mid] >= target) {
        ans = mid;
        r = mid - 1;
    } else {
        l = mid + 1;
    }
}

return ans;
```

### Complexity

-   Time: **O(log n)**
-   Space: **O(1)**

This is the most common interview solution.

------------------------------------------------------------------------

# Approach 3: Upper Bound Style (Your Code)

Your code finds the **last index whose value is \<= target**.

``` cpp
int l = 0;
int r = nums.size()-1;
int res = -1;

while(l <= r){
    int mid = l + ((r-l)>>1);

    if(nums[mid] <= target){
        res = mid;
        l = mid + 1;
    }else{
        r = mid - 1;
    }
}

if(res==-1) return 0;
return nums[res]==target ? res : res+1;
```

## Idea

Maintain:

-   `res` = last position satisfying `nums[mid] <= target`.

After the loop:

### Case 1

Target found.

Return `res`.

### Case 2

Target doesn't exist.

Insert after the last smaller element.

Return `res + 1`.

### Case 3

Every element is greater than target.

`res == -1`

Return `0`.

------------------------------------------------------------------------

# Dry Run

Example:

    nums = [1,3,5,6]
    target = 2

  l   r   mid   nums\[mid\]   res
  --- --- ----- ------------- -----
  0   3   1     3             -1
  0   0   0     1             0

Loop ends.

Last element \<=2 is 1.

Insert after it.

Answer = 1.

------------------------------------------------------------------------

# Binary Search Pattern

## Lower Bound

Find first element

    >= target

Move left when condition is true.

------------------------------------------------------------------------

## Upper Bound

Find last element

    <= target

Move right when condition is true.

Your solution uses this pattern.

------------------------------------------------------------------------

# Key Notes

-   Always compute mid safely:

``` cpp
mid = l + (r-l)/2;
```

-   Binary search requires sorted data.
-   Learn to identify:
    -   first true
    -   last true
    -   first \>= target
    -   last \<= target
-   Many problems reduce to these patterns.

------------------------------------------------------------------------

# Similar Problems

1.  LeetCode 34 --- Find First and Last Position of Element in Sorted
    Array
2.  LeetCode 704 --- Binary Search
3.  LeetCode 744 --- Find Smallest Letter Greater Than Target
4.  LeetCode 852 --- Peak Index in a Mountain Array
5.  LeetCode 153 --- Find Minimum in Rotated Sorted Array
6.  LeetCode 33 --- Search in Rotated Sorted Array
7.  LeetCode 875 --- Koko Eating Bananas
8.  LeetCode 1011 --- Capacity To Ship Packages Within D Days
9.  LeetCode 1482 --- Minimum Number of Days to Make m Bouquets
10. LeetCode 410 --- Split Array Largest Sum

------------------------------------------------------------------------

# Takeaways

-   Think in terms of a monotonic condition.
-   Decide whether you're searching for the **first valid** or **last
    valid** position.
-   Lower-bound and upper-bound templates solve a large class of
    interview problems.
