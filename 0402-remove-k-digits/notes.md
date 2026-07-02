# Remove K Digits - Greedy + Monotonic Stack

## Core Idea

If a larger digit appears before a smaller digit, removing the larger
digit produces a smaller number. We use a monotonic increasing stack to
greedily remove such digits.

## Algorithm

1.  Iterate through each digit.
2.  While the stack is not empty, removals remain, and the top digit is
    greater than the current digit, pop the stack.
3.  Push the current digit.
4.  If removals remain after traversal, pop from the end.
5.  Build the answer by popping the stack.
6.  Remove leading zeros (they appear at the end before reversing).
7.  Reverse and return `0` if empty.

## Code

``` cpp
string removeKdigits(string num, int k) {
    stack<char> st;
    for(char ch: num){
        while(!st.empty() && k>0 && st.top()>ch){ st.pop(); k--; }
        st.push(ch);
    }
    while(k>0){ st.pop(); k--; }
    string res;
    while(!st.empty()){ res.push_back(st.top()); st.pop(); }
    while(!res.empty() && res.back()=='0') res.pop_back();
    reverse(res.begin(), res.end());
    return res.empty()?"0":res;
}
```

## Why `while`?

Multiple previous digits may need to be removed (e.g. `7654`).

## Why `>` and not `>=`?

Equal digits should not be removed; otherwise `112, k=1` incorrectly
becomes `12` instead of `11`.

## Complexity

-   Time: O(n)
-   Space: O(n)
