# Carrot Chopdown (Easy Version - k=1)

- **Time complexity:** O(n + m) per test case
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n + m) for the map and suffix sum array

## Problem Statement

Given `n` carrots of sizes `a1, a2, ..., an` and a cutting machine, perform exactly **one** operation:

- Choose a set of carrots and a positive integer `x`.
- For each chosen carrot with length `l`: if `l ≤ x`, it is unaffected; otherwise, it is divided into two carrots of sizes `x` and `l - x`.

After the operation, find the **maximum number of carrots of the same length** that can be sold.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 ≤ t ≤ 10^4`).
- The description of each test case follows:
  - The first line contains `n` and `m` (`1 ≤ n, m ≤ 2·10^5`) — the number of carrots and the maximum possible length.
  - The second line contains `n` integers `a1, a2, ..., an` (`1 ≤ ai ≤ m`) — the initial carrot sizes.

## Output

For each test case, output a single integer — the maximum number of same-length carrots after exactly one cut.

## Solution

For a given cut position `x = i`, determine how many pieces of size `i` we can obtain:

- **Carrots with size ≥ i** (`cnt[i]`): Each produces exactly **1** piece of size `i` (either unaffected if size = i, or cut into `i` and `l - i` if size > i).
- **Carrots with size exactly 2i** (`mp[2i]`): Each produces an **additional** piece of size `i` (cut into `i` and `i`), giving **2** total pieces per carrot.

Total pieces of size `i` = `cnt[i] + mp[2i]`

The answer is the maximum over all possible cut positions `i` from 1 to `m`.

### How it works

1. Count occurrences of each carrot size using a map.
2. Build a suffix sum array `cnt` where `cnt[i]` = number of carrots with size ≥ i.
3. For each `i` from 1 to `m`, compute `cnt[i] + mp[2*i]` and track the maximum.

### Variables

- `mp` — map counting occurrences of each carrot size
- `cnt` — suffix sum array; `cnt[i]` = number of carrots with size ≥ i
- `ans` — maximum number of same-length carrots achievable
