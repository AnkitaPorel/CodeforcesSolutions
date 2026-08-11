# Threshold Movement

- **Time complexity:** O(n) per test case (O(Σn) overall) - one pass to read the array and one pass to compute the min/max on the two parity groups
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n) - the input array of weights

## Problem Statement

There are `n + 2` positions numbered from `0` to `n + 1`. Initially, position `i` contains an element of weight `w[i]` for every `1 <= i <= n`, while positions `0` and `n + 1` are empty.

An integer `k` is chosen. Then every element moves exactly once, simultaneously:

- If `w[i] < k`, the element at position `i` moves to position `i - 1`;
- If `w[i] > k`, the element at position `i` moves to position `i + 1`;
- If `w[i] == k`, the entire movement process fails immediately.

An integer `k` is **perfect** if the movement does not fail and, upon completion, every position from `1` to `n` contains exactly one element.

Determine whether a perfect integer `k` exists.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 500`).
- The description of each test case follows:
  - The first line contains one integer `n` (`1 <= n <= 100`).
  - The second line contains `n` integers `w1, w2, ..., wn` (`1 <= wi <= 10^9`).

## Output

For each test case, print `YES` if a perfect integer `k` exists, and `NO` otherwise.

The answer may be printed in any case (upper or lower); e.g., `yEs`, `yes`, `Yes`, and `YES` are all accepted.

## Solution

Position `1` can only receive an element from position `2`, so the element at position `2` must move left (`w[2] < k`). Position `n` can only receive from position `n - 1`, so that element must move right (`w[n-1] > k`). Chaining this reasoning through every position shows that all elements on odd positions must move right and all elements on even positions must move left, which is only consistent when `n` is even.

### How it works

1. If `n` is odd, the movement constraints at the two ends contradict each other, so no perfect `k` exists - print `NO`.
2. Otherwise, all even-position weights must satisfy `w < k` and all odd-position weights must satisfy `w > k`, and `k` must not equal any weight.
3. This means an integer `k` must fit strictly between the largest even-position weight and the smallest odd-position weight: `max(w_even) < k < min(w_odd)`.
4. Such an integer exists exactly when `min(w_odd) - max(w_even) >= 2`.

### Variables

- `a` - the array of weights, indexed from `0` (0-based index `i` corresponds to position `i + 1`)
- `mini` - the minimum weight among 0-based even indices (positions `1, 3, 5, ...`), which must be strictly greater than `k`
- `maxi` - the maximum weight among 0-based odd indices (positions `2, 4, 6, ...`), which must be strictly less than `k`
- Final condition: `YES` if `n` is even and `mini - maxi >= 2`, otherwise `NO`
