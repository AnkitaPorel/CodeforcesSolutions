# What's the Capital of France?

- **Time complexity:** O(n) per test case - one pass to read the array, one pass to find the maximum, one pass to check every smaller rating (each bit computation is a single instruction)
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n) for storing the array, O(1) extra

## Problem Statement

There are `n` restaurants in a line, the `i`-th one has rating `a[i]`. In one operation Obesity chooses an index `i` (`1 ≤ i < n`):

- If `a[i] < a[i+1]`, increase `a[i]` by `1`.
- If `a[i] == a[i+1]`, do nothing.
- If `a[i] > a[i+1]`, increase `a[i+1]` by `1`.

So in every operation the **smaller** of the two adjacent ratings is bumped by `1` (nothing happens when they are equal). The *delicacy* of the restaurants is the bitwise OR of all ratings. What is the maximum delicacy achievable after zero or more operations?

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 ≤ t ≤ 10^4`).
- The description of each test case follows:
  - The first line contains an integer `n` (`1 ≤ n ≤ 2·10^5`).
  - The second line contains `n` integers `a[1], a[2], ..., a[n]` (`0 ≤ a[i] ≤ 10^9`).

It is guaranteed that the sum of `n` over all test cases does not exceed `2·10^5`.

## Output

For each test case, print a single integer - the maximum delicacy of all restaurants.

## Solution

Let `M = max(a)`. Two observations about the operation shape the whole solution:

### 1. No rating ever exceeds `M`, and a rating equal to `M` never changes

The operation only ever increments the *smaller* of two adjacent ratings, so that value becomes at most the larger one - it can never jump over it. Hence every rating stays `≤ M` forever. A rating equal to `M` is never strictly smaller than a neighbour, so it is frozen: `M` is a permanent part of every achievable OR.

### 2. Any rating `x` can be raised to any value in `[x, M]`

`M` can be spread along the line: the neighbour of an element valued `M` is always strictly smaller, so it can be incremented again and again until it also reaches `M`; repeating this outwards fills the whole array with `M`. Since every single operation adds exactly `1`, we can stop halfway and leave an element at **any** value in `[x, M]`.

### The bit that matters

For a rating `x < M`, let `d(x)` be the highest bit position where `x` and `M` differ. Since `x < M`, `M` has a `1` there and `x` has a `0`; above that bit the two numbers are identical.

Therefore **every** value in the interval `[x, M]` shares the same prefix (bits above `d(x)`) with `M`: a number smaller than `M` but at least `x` cannot fall outside that prefix block. So after any operations, the element `x` only contributes bits `≤ d(x)` on top of `M`'s own bits.

Let `k = max over all x < M of d(x)`. Two consequences:

- **Upper bound.** Every final element agrees with `M` on all bits above `k` (elements equal to `M` obviously do), and bits `≤ k` can contribute at most all ones:

  ```
  answer ≤ M | (2^(k+1) - 1)
  ```

- **Achievability.** Take an element `x*` with `d(x*) = k`, let `H` be `M` with bits `0..k` cleared, and let

  ```
  v = H + (2^k - 1)      // prefix of M, bit k = 0, all lower bits = 1
  ```

  We have `x* ≤ v < M`: `x*` shares the prefix `H` with `M` and has bit `k = 0`, so `x* ≤ H + 2^k - 1 = v`, while `M ≥ H + 2^k > v`. Spread `M` over the whole array, then raise `x*` back up to `v` (the neighbour holding `M` keeps bumping it, since `v < M`). Now

  ```
  v | M = H | (2^k - 1) | 2^k | (lower bits of M) = M | (2^(k+1) - 1)
  ```

  which is exactly the upper bound.

If every rating already equals `M` (e.g. `n = 1`), nothing can change and the answer is simply `M`.

### The formula

```
ans = max( M,  max over x < M of ( M | ( (1 << (d(x) + 1)) - 1 ) ) )
```

The highest bit where two *different* numbers differ is found in O(1) with `d(x) = 31 - __builtin_clz(x ^ M)`.

### How it works

1. Read `n` and the array `a`.
2. Compute `max_ele` = the largest rating `M`.
3. Start with `ans = max_ele` (doing nothing is always allowed).
4. For every rating `it < max_ele`: find `bit = 31 - __builtin_clz(it ^ max_ele)`, the highest bit where it differs from `M`, and update `ans = max(ans, max_ele | ((1 << (bit + 1)) - 1))`.
5. Print `ans`.

### Variables

- `a` - the array of ratings
- `max_ele` - `M`, the largest rating; a frozen value that is part of every achievable OR
- `ans` - the best delicacy found so far, initialised with `M`
- `it` - the current rating being checked against `M`
- `bit` - index of the highest bit where `it` and `max_ele` differ

### Example

For `a = [4, 6]`: `M = 6` (`110`). The only smaller rating `4` (`100`) differs from `M` at bit `1`, so `ans = 6 | ((1 << 2) - 1) = 6 | 3 = 7`. Indeed, operating on the pair raises `4` to `5` (`101`), and `5 | 6 = 7`.
