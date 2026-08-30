# Odd Eraser

- **Time complexity:** O(n) per test case to read the array; O(1) for the gcd computation
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n) for storing the array, O(1) extra

## Problem Statement

Given an array `a1, a2, ..., an`, you can apply the following operation any number of times (possibly zero):

Choose an integer `k ≥ 1` such that `2k + 1 ≤ m` (where `m` is the current length of the array) and `2k + 1` indices `i1, i2, ..., i2k+1` (sorted). Remove the `(k+1)`-th element (the middle one) from the array. The remaining elements are concatenated.

After all operations, the remaining array is `b1, b2, ..., bm`. Find the maximum possible value of `gcd(b1, b2, ..., bm)`.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 ≤ t ≤ 500`).
- The description of each test case follows:
  - The first line contains an integer `n` (`1 ≤ n ≤ 100`) — the size of the array.
  - The second line contains `n` integers `a1, a2, ..., an` (`1 ≤ ai ≤ 10^9`).

## Output

For each test case, output a single integer — the maximum possible GCD.

## Solution

The key insight is that the operation always removes a **middle** element from a selected group of odd length. This means the **first** and **last** elements of the array can never be removed (they are never in the middle of any valid selection).

By repeatedly removing middle elements, we can reduce the array down to just the first and last elements. Since the GCD of a two-element array is just `gcd(a, b)`, and keeping more elements can only decrease the GCD, the optimal answer is:

```
gcd(a1, an)
```

### Why can't we do better?

Any GCD `g` dividing all remaining elements must also divide both `a1` and `an`, since those are always preserved. Therefore the answer cannot exceed `gcd(a1, an)`.

### How it works

1. Read the array of `n` integers.
2. Compute and print `gcd(arr.front(), arr.back())`.

### Variables

- `arr` - the input array of integers
- The answer is simply `gcd(arr[0], arr[n-1])`
