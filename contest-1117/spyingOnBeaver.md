# Spying on the Beaver

- **Time complexity:** O(n + m) per test case - one DFS computes depths of all vertices in O(n), then a linear scan over the m dam vertices picks the shallowest one
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n) for the adjacency list and depth array

## Problem Statement

The Beaver starts at the root of a rooted tree with `n` vertices and travels to one of `m` dam vertices. You may place cameras on tree edges; when the Beaver traverses a camera-equipped edge, you observe it. After the trip, you receive the sequence of observed camera-edges. Determine the **minimum** number of cameras `k` needed so that every possible destination produces a distinct observation, and output which edges to monitor.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 20000`).
- The description of each test case follows:
  - The first line contains a single integer `n` (`2 <= n <= 100000`) - the number of vertices.
  - The second line contains `n - 1` integers `p2, ..., pn` (`1 <= pi < i`) - the parent of each vertex from 2 to n.
  - The third line contains a single integer `m` (`1 <= m <= n`) - the number of dam vertices.
  - The fourth line contains `m` distinct integers `a1, ..., am` (`1 <= ai <= n`) - the dam vertex numbers.

The sum of `n` across all test cases does not exceed `100000`.

## Output

For each test case, output exactly one line: the number `k` of cameras, followed by the `k` vertex numbers `u` identifying the edges `(u, pu)` where cameras are placed. If there are multiple valid answers, any one is accepted.

## Solution

The answer is always **m - 1** cameras. The strategy is to leave the **shallowest** dam (closest to the root) unmonitored and place one camera on the edge `(u, pu)` for every other dam `u`.

### Why this works

The observation for a destination `d` is the ordered sequence of camera-edges on the root-to-`d` path.

- **The shallowest dam `s`** has no camera on `(s, ps)`, and no other dam lies on the path from root to `s` (since `s` is shallowest among all dams). So its observation is the **empty** sequence - unique among all destinations.
- **Any other dam `d`** has a camera on `(d, pd)`, which appears in its observation. If `d` is an ancestor of another dam `d'`, then `d'`'s observation includes all of `d`'s cameras **plus** the camera on `(d', pd')`, making them distinct. Every non-shallowest dam's observation is non-empty and contains its own edge-camera, so no two destinations share the same observation.

### Why m - 1 is optimal

Each dam needs a unique observation. Placing a camera on `(u, pu)` is the only way to "mark" dam `u` individually - no combination of cameras on other edges can distinguish `u` from a sibling subtree's dam without also marking `u`'s own edge. Therefore at least `m - 1` cameras are required.

### How it works

1. Build the undirected adjacency list `g` from the parent array (0-indexed).
2. Run a DFS from the root (vertex 0) to compute `dp[v]` = depth of each vertex.
3. Among all `m` dam vertices, find the one with the **minimum depth** (`mn`).
4. Output `m - 1` cameras: for every dam vertex `x` except `mn`, output `x + 1` (the edge `(x, parent[x])`).

### Variables

- `g` - adjacency list of the tree (0-indexed)
- `dp` - depth array; `dp[v]` is the distance from root to vertex `v`
- `ans` - the list of dam vertices (0-indexed)
- `mn` - the shallowest dam vertex (minimum depth among all dams)
