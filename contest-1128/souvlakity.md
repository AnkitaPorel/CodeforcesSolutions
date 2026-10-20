# Hey, It's Me, Souvlakity

- **Time complexity:** O(n) per test case to scan the string
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n) for storing the string, O(1) extra

## Problem Statement

The integers from 1 to n are distributed between two players, represented by a binary string `s` of length n: `si = 1` if integer `i` belongs to Souvlakity, `si = 0` if it belongs to Kalamakity (there is at least one `1`).

The game lasts 10^100 turns, with Souvlakity playing first and the players alternating. On each turn, a player must give exactly one of their integers to the other player. After all turns, Souvlakity's score is the range of the integers he owns: `max(S) - min(S)`, where `S` is his final set (he is guaranteed to own at least one integer). Souvlakity wants to maximize this score, Kalamakity wants to minimize it. What is the final score under optimal play?

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 ≤ t ≤ 100`).
- The description of each test case follows:
  - The first line contains an integer `n` (`2 ≤ n ≤ 100`).
  - The second line contains a binary string `s` of length `n` containing at least one `1`.

## Output

For each test case, output a single integer — Souvlakity's final score.

## Solution

The key insight is a parity argument: 10^100 is even, so both players make exactly 5 * 10^99 moves. Souvlakity loses one integer per his move and gains one per Kalamakity's move, so his final count equals his initial count `cnt` (the number of `1`s). This splits into three cases:

### cnt == 1

Souvlakity owns exactly one integer at the end, so his score is `0`.

### cnt == 2

On his first turn Souvlakity must give away one of his two integers, keeping a single integer `x`. From then on the game oscillates: Kalamakity gives him an integer, he must give one back. On the final turn (Kalamakity's), Souvlakity owns only `x`, so Kalamakity owns all other `n - 1` integers. Since `n ≥ 2`, `x` has a neighbor, and Kalamakity always replies with an integer adjacent to `x`. Souvlakity therefore ends with `{x, x±1}` and his score is exactly `1`.

### cnt >= 3

- **Achievability (Souvlakity):** On his first turn he gives away a non-extreme integer (one that is neither his smallest nor his largest — possible because `cnt ≥ 3`). After that he always returns whatever Kalamakity just gave him. His original minimum and maximum are never given away, so his final set contains both, giving score `max - min`.
- **Upper bound (Kalamakity):** The original `1`s span `[min1, max1]` with `max1 - min1 + 1 ≥ cnt` integers. Whenever it is Kalamakity's turn, Souvlakity owns only `cnt - 1` integers, so at least one integer of `[min1, max1]` is still owned by Kalamakity. He always replies with such an integer, keeping Souvlakity inside `[min1, max1]`, so the score can never exceed `max - min`.

Therefore the answer is:

```
cnt == 1 -> 0
cnt == 2 -> 1
cnt >= 3 -> max_ele - min_ele   (positions of '1', 1-indexed)
```

### How it works

1. Read `n` and the string `s`.
2. Scan `s`, counting the `1`s and tracking the largest and smallest 1-based position.
3. Print `0`, `1`, or `max_ele - min_ele` according to the count.

### Variables

- `cnt` - number of `1`s (Souvlakity's initial and final count of integers)
- `max_ele`, `min_ele` - largest and smallest 1-based position containing a `1`
