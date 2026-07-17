# Best Time to Buy and Sell Stock - Visual Handbook

## Approaches

### 1. Brute Force

Try every buy/sell pair. Time: O(n\^2) Space: O(1)

### 2. Stack (Your Solution)

Traverse from right to left while maintaining the maximum future selling
price. For each day, compute futureMax-currentPrice. Time: O(n) Space:
O(n)

### 3. Optimal Running Minimum

Maintain the minimum price seen so far. For each price: - update minimum
price - compute current profit = price-minPrice - update best profit

Visual Example:

Prices: 7 1 5 3 6 4

Day Price Min Profit Best 0 7 7 0 0 1 1 1 0 0 2 5 1 4 4 3 3 1 2 4 4 6 1
5 5 5 4 1 3 5

Why it works: Always remember the cheapest buying opportunity so far.

Complexities: Brute Force: O(n\^2) Stack: O(n), O(n) Optimal: O(n), O(1)

Similar Problems: - Best Time to Buy and Sell Stock II - III - IV -
Cooldown - Transaction Fee - Maximum Difference Between Increasing
Elements

Key Notes: - One transaction only. - Buy before sell. - Running minimum
is the interview pattern.
