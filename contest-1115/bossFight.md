# Boss Fight

- **Time complexity:** O(n) per test case (O(Σn) overall) — one pass to sum damages and count frequencies, then one pass over the frequency map (at most n distinct values)
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n) — the input array and the frequency map (at most n distinct values)

## Problem Statement

You are fighting a boss with an unknown amount of health. You have a sequence of `n` spell cards, where the `i`-th card deals `a[i]` damage. You can rearrange your hand and play the cards in any order you choose.

The boss has an adaptive shield. If you ever play two cards in a row that deal the exact same amount of damage, the shield permanently activates. The card that triggers the shield still deals its normal damage, but all subsequent cards you play will deal `0` damage.

Find the **maximum total health** the boss can have such that you will defeat him if you arrange and play your cards optimally.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 100`).
- The description of each test case follows:
  - The first line contains a single integer `n` (`1 <= n <= 50`) — the number of spell cards.
  - The second line contains `n` integers `a1, a2, ..., an` (`1 <= ai <= 1000`) — the damage dealt by each card.

## Output

For each test case, output a single integer — the maximum total health the boss can have such that you will defeat him.

## Solution

The answer is the maximum total damage that can be dealt. If the cards can be ordered so that no two adjacent cards deal equal damage, the shield never activates and all cards deal full damage. This is possible whenever no single damage value appears more than half the time. Otherwise, some cards of the most frequent value are forced to sit next to each other and their damage is lost.

### How it works

1. Compute the total damage `ans` (sum of all `a[i]`) as the baseline, assuming all cards deal damage.
2. Count the frequency of each damage value. Find the most frequent value `mx` and its frequency `fmax`.
3. If `fmax > n - fmax`, a majority value exists. The other `n - fmax` cards can act as separators between majority cards, so at most `n - fmax + 1` majority cards can be played without triggering the shield. The first two cards of the unavoidable consecutive run still deal damage, so the number of majority cards that lose their damage is `fmax - (n - fmax) - 2` (clamped to 0). Subtracting this count times `mx` from the baseline gives the answer.
4. If `fmax <= n - fmax`, the loss is 0 and the full sum is the answer.

### Variables

- `ans` — baseline total damage, i.e., the sum of all `a[i]`
- `mp` — frequency map: each distinct damage value mapped to how many cards deal it
- `fmax` — the highest frequency among all damage values
- `mx` — the damage value that occurs `fmax` times (the majority value)
- `res` — the number of majority-value cards that must be played after the shield activates and therefore deal `0` damage; computed as `max(0, fmax - (n - fmax) - 2)` and multiplied by `mx` to get the damage lost
