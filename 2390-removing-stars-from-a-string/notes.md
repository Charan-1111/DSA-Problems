# Why `res = res + ch` Can Lead to Memory Limit Exceeded

## General Solution

``` cpp
string removeStars(string s) {
    string res;

    for (char ch : s) {
        if (ch != '*') {
            res = res + ch;
        } else {
            res.pop_back();
        }
    }

    return res;
}
```

This approach works correctly for small strings. However, as the input
size grows, it can eventually result in a **Memory Limit Exceeded
(MLE)** or poor performance.

## Why Does This Happen?

The statement:

``` cpp
res = res + ch;
```

creates a **new temporary string** every time a character is appended.

Internally, the following steps occur:

1.  Allocate a new block of memory on the heap.
2.  Copy all characters from `res` into the new string.
3.  Append the new character `ch`.
4.  Assign the new string back to `res`.
5.  Destroy the old temporary object.

As the string grows larger, each append operation may require copying
the entire existing string.

If the string has length `n`, the total work becomes:

-   1st append → copy 0 characters
-   2nd append → copy 1 character
-   3rd append → copy 2 characters
-   ...
-   nth append → copy `n - 1` characters

Total copies:

    0 + 1 + 2 + ... + (n - 1) = O(n²)

This results in **O(n²)** time complexity due to repeated copying. It
also creates many temporary allocations, increasing peak memory usage
and potentially causing **Memory Limit Exceeded** for large inputs.

## Better Approach

Use `push_back()` instead:

``` cpp
string removeStars(string s) {
    string res;

    for (char ch : s) {
        if (ch != '*') {
            res.push_back(ch);
        } else {
            res.pop_back();
        }
    }

    return res;
}
```

### Why is `push_back()` Better?

`push_back()` appends the character directly to the existing string.

Instead of creating a new string on every append, the string maintains
an internal **capacity**. When there is sufficient capacity:

-   No new allocation is required.
-   No copying of the entire string is required.
-   The character is appended in constant time.

When the capacity is exhausted, the string allocates a larger buffer
(typically doubling its capacity), copies the existing characters once,
and continues appending.

Because these reallocations happen infrequently, the amortized cost of
each `push_back()` is **O(1)**.

## Complexity Comparison

  Method                Time Complexity   Extra Allocations
  --------------------- ----------------- ------------------------
  `res = res + ch`      O(n²)             Many temporary strings
  `res.push_back(ch)`   O(n) amortized    Very few reallocations

## Key Takeaway

Avoid using:

``` cpp
res = res + ch;
```

inside a loop when repeatedly appending characters to a string.

Instead, use:

``` cpp
res.push_back(ch);
```

It avoids unnecessary temporary string creation, reduces memory
allocations, and improves the overall complexity from **O(n²)** to
**O(n)** (amortized).
