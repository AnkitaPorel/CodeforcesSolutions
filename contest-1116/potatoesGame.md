# Hot Potatoes at the Fairy Warehouse

- **Time complexity:** O(n) per test case (O(sum of n) overall) - each of the `2n` positions is scanned once to build the final state and once to count the scores
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n) - a working array `arr` of size `2n`

## Problem Statement

On a quiet afternoon at the Fairy Warehouse, Ithea gathers Chtholly, Nephren, and the other leprechauns for one last game before dinner: Hot Potatoes.

There are `2n` leprechauns sitting in a circle, numbered from `1` to `2n` clockwise. They are divided into two teams: leprechauns with odd numbers belong to the Red Team, while those with even numbers belong to the Blue Team.

Initially, some leprechauns hold a potato. The game then lasts for `k` rounds.

At the beginning of each round, both teams know the current positions of all potatoes. Then, simultaneously, every leprechaun holding a potato does exactly one of the following:

- Keep the potato, or
- Pass the potato to the next leprechaun clockwise, provided that the next leprechaun does not hold a potato at the beginning of the round.

If the next leprechaun holds a potato at the beginning of the round, the current holder must keep their potato. Whether a potato can be passed depends only on the positions of the potatoes at the beginning of the round.

Under these rules, every leprechaun holds at most one potato at any time.

When all `k` rounds are over, the final bell rings. Every leprechaun still holding a potato is eliminated from the game. The score of each team is defined as the number of eliminated leprechauns on the other team. All members of each team cooperate and share all available information to maximize their team's score.

Find the scores of the Red Team and the Blue Team if both teams play optimally. It can be shown that the scores under optimal play are uniquely determined.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 10^4`).
- The description of each test case follows:
  - The first line contains two integers `n` and `k` (`1 <= n <= 10^5`, `1 <= k <= 10^9`) - half the number of leprechauns and the number of rounds.
  - The second line contains a binary string `s` of length `2n` (`s_i = 0` or `1`) describing the initial state of the game. If `s_i = 1`, leprechaun `i` initially holds a potato; otherwise, they do not.
- It is guaranteed that the sum of `n` over all test cases does not exceed `10^5`.

## Output

For each test case, print two integers - the scores of the Red Team and the Blue Team, respectively, if they play optimally.

## Solution

The exact value of `k` is irrelevant: for any `k >= 1` the final state under optimal play is exactly what you get from a single round of greedy passing applied to the initial string.

### How it works

1. **Only the tail of a run can move.** Split the cycle into maximal runs of consecutive `1`s. Every potato except the last one of a run is blocked by the next potato and can never move. Only the potato right before an empty seat is passable.
2. **Passing early never helps.** If a team passes a potato before the final round, the potato lands on an opponent and the opponent now controls it. The opponent simply keeps it until the final round and then passes it back onto the mover's side, cancelling the point - and the vacated seat may even enable another opponent potato. So the mover can never gain from passing early.
3. **Pass in the final round whenever possible.** In the last round a pass that places the potato on an opponent's seat scores a point that can no longer be answered, while keeping the potato leaves it on the team's own side and gives the point to the opponent. So the final round is a single greedy round of passing.
4. Since every potato is kept until the final round, the configuration at the start of the final round is the initial configuration, and the final configuration is: every `10` pair becomes `01` (the last potato of each run steps one seat clockwise) and every other potato stays still.
5. **Simulation.** Scan the string once. For every `i` with `s[i] = '1'`, let `idx = (i + 1) mod 2n` be the clockwise neighbour. If `s[idx] = '0'`, the potato moves to `idx`; otherwise it stays at `i`. Because all decisions use the initial string, this exactly reproduces one simultaneous round.
6. **Scoring.** A potato ending on an even-numbered seat eliminates a Blue leprechaun, so it increases the Red Team's score; a potato ending on an odd-numbered seat eliminates a Red leprechaun, so it increases the Blue Team's score.
7. **Edge case `k = 0`.** No rounds are played, so the final state equals the initial string `s` (count the initial potatoes directly).

### Variables

- `n`, `k` - half the number of leprechauns and the number of rounds; for `k >= 1` the outcome does not depend on `k`
- `s` - the binary string of length `2n` giving the initial potato positions
- `totalPlayers` - `2n`, the number of leprechauns on the circle
- `arr` - the final state after the game; `arr[i] = 1` means leprechaun `i` ends up holding a potato
- `idx` - the clockwise neighbour `(i + 1) mod 2n` of the current seat
- `redTeam`, `blueTeam` - the scores of the Red and Blue teams (counts of eliminated Blue and Red leprechauns respectively)
