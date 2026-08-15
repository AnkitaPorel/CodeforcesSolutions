# Domino Tiles

- **Time complexity:** O(n) per test case (O(Σn) overall) - for each of the 4 fixed patterns, one pass over the string
- **Memory limit:** 256 megabytes
- **Space complexity:** O(1) - only the fixed patterns and the current string

## Problem Statement

There is a row of `n` tiles, each marked with `0`, `1`, or `?`. Replace every `?` with either `0` or `1`. For every `1 <= i < n`, the two neighboring tiles `s[i]` and `s[i+1]` form a domino of weight `s[i] + s[i+1]`; two consecutive dominoes share exactly one tile. The completed row is **valid** if every two consecutive dominoes have different weights.

Count the number of different replacements that produce a valid row, modulo `998244353`. Two ways are different if the resulting strings differ.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 10^4`).
- The description of each test case follows:
  - The first line contains one integer `n` (`2 <= n <= 2 * 10^5`) - the number of tiles.
  - The second line contains the string `s` of length `n`, where `s[i]` is `0`, `1`, or `?`.
- It is guaranteed that the sum of `n` over all test cases does not exceed `2 * 10^5`.

## Output

For each test case, output one integer - the number of valid ways to replace all `?` characters, modulo `998244353`.

## Solution

A domino has weight `0`, `1`, or `2`. Whenever the pair `(s[i], s[i+1])` is fixed, the next tile `s[i+2]` is forced by the requirement that the weight of the next domino differs from the current one:

- `(0,0)` (weight `0`) forces `s[i+2] = 1`;
- `(0,1)` (weight `1`) forces `s[i+2] = 1`;
- `(1,0)` (weight `1`) forces `s[i+2] = 0`;
- `(1,1)` (weight `2`) forces `s[i+2] = 0`.

So the whole row is uniquely determined by its first two tiles and repeats with period 4. The four possible starts produce exactly the four patterns `0011`, `0110`, `1001`, `1100` (each repeated to length `n`). Hence the answer is simply the number of these four patterns that are compatible with `s`.

### How it works

1. Every valid row equals one of the four period-4 patterns repeated: `0011`, `0110`, `1001`, `1100`.
2. For each pattern, scan the string: `s[i]` must be `?` or equal to `pattern[i % 4]`.
3. Count how many patterns are compatible; that count is the answer (at most 4, so the modulo never changes it).

### Variables

- `patterns` - the four period-4 valid patterns
- `cnt` - the number of patterns compatible with the input string
- `flag` - whether the current pattern matches `s` everywhere
- Compatibility check: `s[i] == '?' || s[i] == pattern[i % 4]` must hold for every index `i`
