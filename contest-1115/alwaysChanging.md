# Always Changing

- **Time complexity:** O(n) per test case (O(Σn) overall) — the `solve` lambda scans the string once per start character (`'0'` and `'1'`), giving 2 passes = O(2n) ≈ O(n)
- **Memory limit:** 256 megabytes
- **Space complexity:** O(1) extra — only a constant number of integer variables are used

## Problem Statement

You are given a binary string `s` of length `n`.

A string is called **alternating** if no two adjacent characters are the same. For example, `0101`, `1`, and `01` are alternating, but `0110` is not.

You want to transform `s` into an alternating string by performing the following operation any number of times (possibly zero):

- Choose any character currently in the string and delete it.

However, your sequence of operations must follow a rule: the characters you delete must **strictly alternate**. This means if the last character you deleted was `0`, the next character you delete must be `1`, and vice versa. Your very first deleted character can be either `0` or `1`.

Find the **minimum number of operations** required to make `s` an alternating string. If it is impossible to achieve this, output `-1`.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 10^4`).
- The description of each test case follows:
  - The first line contains a single integer `n` (`1 <= n <= 2 * 10^5`) — the length of the string `s`.
  - The second line contains the binary string `s` of length `n`, consisting only of the characters `0` and `1`.

It is guaranteed that the sum of `n` over all test cases does not exceed `2 * 10^5`.

## Output

For each test case, output a single integer — the minimum number of operations required to make `s` an alternating string, or `-1` if it is impossible.

## Solution

The final alternating string can be of only two forms: `0101...` or `1010...`. The code tries both target patterns via `solve(start)` and keeps the pattern that requires the fewer deletions.

### How it works

1. Scan `s` once per pattern, keeping the characters that match the expected alternating sequence (`expected`) in order — these kept characters form the final alternating string.
2. Every character that does not match is deleted and counted in `numZeroDel` / `numOneDel`.
3. Deletions must strictly alternate, so the counts of deleted `0`s and deleted `1`s can differ by at most `1`. If the counts are imbalanced, extra characters at the boundaries of the kept sequence (tracked by `extraZero` / `extraOne`) may optionally be deleted to fix the balance.
4. The minimum valid total among all candidates is the answer; if no candidate is valid, output `-1`.

### Variables (in `solve`)

- `start` — the character the target pattern begins with (`'0'` → `0101...`, `'1'` → `1010...`)
- `d` — number of characters kept so far; its parity decides which character is `expected` next
- `expected` — the character that fits the target pattern at the current step (`start` when `d` is even, the opposite when `d` is odd)
- `f` — the first kept character (`0` or `1`), or `-1` if nothing has been kept yet
- `l` — the last kept character (`0` or `1`), or `-1` if nothing has been kept yet
- `numZeroDel`, `numOneDel` — total deleted `0`s and `1`s for this pattern
- `extraZero`, `extraOne` — additional `0` / `1` available for deletion at the start or end of the kept sequence, used to rebalance the deleted counts
- `ans` — the minimum operation count found for this pattern
