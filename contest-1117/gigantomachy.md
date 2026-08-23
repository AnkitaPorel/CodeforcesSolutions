# Gigantomachy

- **Time complexity:** O(n + m) per test case - two linear passes over the height arrays accumulate the survival totals of both ranges
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n + m) for the stored height arrays, O(1) extra

## Problem Statement

Two giants, **Bea** and **Ver**, each own a mountain range. The heights of Bea's mountains are `a1, a2, ..., an` (numbered from left to right), and Ver's are `b1, b2, ..., bm` (numbered from right to left). Both ranges are arranged in **non-increasing** order (`ai >= ai+1` and `bi >= bi+1`). At the beginning each giant stands on mountain `1` of his own range, so they face each other and can see every mountain of both ranges.

They alternate turns, with **Bea going first**. On his turn a giant:

- Throws a boulder at the mountain his opponent is currently standing on, decreasing its height by `1`.
- If the mountain directly in front of him (the one with the next number) is **higher** than the one he is standing on, he jumps to it.
- If he is standing on regular ground (height `0`) and there are no more mountains in front of him, he admits defeat.

Determine which giant wins the game.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 500`).
- The description of each test case follows:
  - The first line contains two integers `n` and `m` (`1 <= n, m <= 100`) - the number of mountains in Bea's and Ver's ranges.
  - The second line contains `n` integers `a1, a2, ..., an` (`1 <= ai <= 10^9`; `ai >= ai+1`) - the heights of Bea's mountains.
  - The third line contains `m` integers `b1, b2, ..., bm` (`1 <= bi <= 10^9`; `bi >= bi+1`) - the heights of Ver's mountains.

## Output

For each test case, output a single number - the number of the giant who will win (`1` for Bea, `2` for Ver).

## Solution

The key observation is that the messy-looking fight reduces to counting how many boulder hits each range can absorb before its owner runs out of mountains.

While Bea stands on mountain `i` (`i < n`), Ver only ever throws at that exact mountain, so mountain `i + 1` keeps its full height `a[i+1]`. Bea therefore jumps the moment `a[i]` drops to `a[i+1] - 1`, which costs exactly `a[i] - a[i+1] + 1` hits per step, and the final mountain absorbs `a[n]` hits before Bea is left on bare ground. Summing these gives `bea`, the total number of hits Bea's side survives; `ver` is computed symmetrically for Ver's side.

### How it works

1. Accumulate `bea` = `(a[i] - a[i+1] + 1)` over all `i < n`, plus `a[n]` for the last mountain - this is the total punishment Bea's range can take before Bea is eliminated.
2. Accumulate `ver` symmetrically over `b`.
3. Compare the totals using the turn order: Ver's hits on Bea land on even turns `2, 4, 6, ...` and Bea's hits on Ver on odd turns `1, 3, 5, ...`.
   - If `bea > ver`: Ver's last mountain is flattened by Bea's `ver`-th throw (turn `2*ver - 1`), and on Ver's very next turn he stands on ground of height `0` with nothing ahead - Ver loses.
   - If `bea == ver`: the finishing blow still lands on Bea's turn (`2*bea - 1 = 2*ver - 1`), so it is Ver who first begins his turn on bare ground - the tie goes to Bea.
4. Hence the answer is `1` iff `bea >= ver`, otherwise `2`.

As a side note, the accumulated sum telescopes to `a[1] + n - 1` (respectively `b[1] + m - 1`), so only the height of the first mountain and the range length actually matter.

### Variables

- `a`, `b` - the heights of Bea's and Ver's mountains (both given in non-increasing order)
- `bea` - total number of hits Bea's range absorbs before Bea runs out of mountains: the sum of `a[i] - a[i+1] + 1` over consecutive pairs, plus `a[n]` for the final mountain
- `ver` - the same survival total for Ver's range
