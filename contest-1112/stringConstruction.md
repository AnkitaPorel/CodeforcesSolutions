# String Construction

- **Time complexity:** O(n) per test case (O(Σn) overall) — the answer string of length `n` is built with a few linear loops
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n) — the constructed output string

## Problem Statement

Two integers `n` and `k` are given.

Construct a binary string `s` of length `n` such that both of the following conditions hold:

1. The absolute difference between the number of characters `0` and the number of characters `1` in `s` is at most `1`.
2. There are exactly `k` pairs of adjacent equal characters in `s`. Formally, there are exactly `k` indices `i` (`1 <= i <= n-1`) satisfying `s[i] == s[i+1]`.

Or determine that no such string exists. (A binary string is a string where each character is either `0` or `1`.)

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 1000`).
- The only line of each test case contains two integers `n` and `k` (`2 <= n <= 2 * 10^5`, `0 <= k <= n-1`).

It is guaranteed that the sum of `n` over all test cases does not exceed `2 * 10^5`.

## Output

For each test case, output a binary string `s` of length `n` — the string you constructed. Print `-1` if such a string does not exist.

If there are multiple answers, any of them may be output.

## Solution

For the counts of `0` and `1` to differ by at most `1`, the string must use roughly `n/2` zeros and `n/2` ones. With both characters present, the maximum number of adjacent equal pairs is `n - 2`, achieved by putting all zeros together and all ones together. So `k > n - 2` is impossible.

### How it works

1. If `k > n - 2`, print `-1`.
2. Otherwise, set `diff = n - k - 2`, the number of equal pairs that must be "removed" from the maximum `n - 2`.
3. Start with an alternating prefix of length `diff` (starting with `0`). An alternating block contributes no equal pairs.
4. Append the remaining characters as two equal-character blocks — all zeros then all ones, or the reverse depending on the prefix length's parity. This keeps the junction between blocks non-equal.
5. Total equal pairs become `(zeroCount - 1) + (oneCount - 1) = n - 2 - diff = k`, and the character counts stay balanced.

### Variables

- `n`, `k` — the length of the string and the required number of adjacent equal pairs
- `diff` — `n - k - 2`, the length of the alternating prefix; it determines how many equal pairs are dropped from the maximum `n - 2`
- `oneCount` — `n / 2`, the number of `1`s in the string
- `zeroCount` — `n - oneCount`, the number of `0`s in the string (ensures `|zeroCount - oneCount| <= 1`)
- `ans` — the constructed binary string; the alternating prefix is built first, then the leftover zeros and ones are appended as two blocks (zeros first when `diff` is even, ones first when `diff` is odd, so the boundary never creates an extra equal pair)
