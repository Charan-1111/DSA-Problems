# Asteroid Collision Handbook

## Brute Force

Repeatedly simulate collisions until the array becomes stable.

-   Compare adjacent asteroids.
-   Remove destroyed asteroids.
-   Restart traversal after every collision.

**Time:** O(n²) or worse\
**Space:** O(n)

------------------------------------------------------------------------

## Key Observation

A collision can occur **only** when:

    positive asteroid
    followed by
    negative asteroid

All other combinations can never collide.

------------------------------------------------------------------------

## Optimal Approach (Stack)

Maintain a stack of surviving asteroids.

For every asteroid:

-   Positive → push.
-   Negative → repeatedly compare with positive asteroids on the top of
    the stack.

Cases: 1. Current asteroid is larger → pop the stack and continue. 2.
Stack asteroid is larger → current asteroid is destroyed. 3. Equal size
→ both are destroyed.

Your solution follows this logic by repeatedly resolving collisions
until the current asteroid either survives or is destroyed.

------------------------------------------------------------------------

## Why O(n)?

Although a `while` loop exists, each asteroid: - is pushed at most
once, - is popped at most once.

Therefore the total work is linear.

-   Time: **O(n)**
-   Space: **O(n)**

------------------------------------------------------------------------

## Pattern Recognition

Use a stack when: - Only the most recently processed element can
interact with the current one. - Chain reactions are possible. - Earlier
elements never need to be revisited once resolved.

------------------------------------------------------------------------

## Similar Problems

### Monotonic Stack

-   Next Greater Element I
-   Next Greater Element II
-   Daily Temperatures
-   Largest Rectangle in Histogram
-   Sum of Subarray Minimums
-   Remove K Digits
-   Trapping Rain Water

### Stack / Simulation

-   Robot Collisions
-   Push Dominoes
-   Car Fleet
-   Baseball Game

------------------------------------------------------------------------

## Common Mistakes

-   Letting two positive asteroids collide.
-   Letting two negative asteroids collide.
-   Forgetting to continue after popping a smaller asteroid.
-   Mishandling equal-sized asteroids.
-   Forgetting that only `(positive, negative)` pairs collide.

## Key Takeaways

-   Only opposite moving asteroids can collide.
-   A single asteroid may destroy multiple previous asteroids.
-   The stack always represents the surviving asteroids.
-   Every asteroid is processed at most twice, giving an optimal O(n)
    solution.
