# Bermuda Rectangle

- **Time complexity:** O(√S + q log d) per test case, where `S` is the rectangle area, `d` is the number of divisors of `S`, and `q` the number of queries - one loop up to √S factors `S`, then each query runs a `lower_bound` and a binary search, both O(log d)
- **Memory limit:** 256 megabytes
- **Space complexity:** O(d) for the divisor and prefix arrays

## Problem Statement

The Beaver is swimming across the ocean and explores the Bermuda Rectangle. Its area is exactly `S`, its sides are integers, and its bottom-left corner is at the point `(0, 0)`.

The Beaver wants to know, for a rectangle with integer sides `x` and `y` whose bottom-left corner is also at `(0, 0)`, how many of its cells can be located within the Bermuda Rectangle. A cell is considered within the Bermuda Rectangle if **there exists** some valid Bermuda Rectangle (with area `S` and integer sides) that contains that cell. Help the Beaver answer `q` such queries.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 10000`).
- The description of each test case follows:
  - The first line contains two integers `S` and `q` (`1 <= S <= 10^14`; `1 <= q <= 3 * 10^5`) - the area of the Bermuda Rectangle and the number of queries.
  - The next `q` lines each contain two integers `x, y` (`1 <= x, y <= S`) - a query.

It's guaranteed the sum of `q` over all test cases doesn't exceed `3 * 10^5`, and the sum of `√S` over all test cases doesn't exceed `10^7`.

## Output

For each query, output a single integer on a separate line - the answer to the query.

## Solution

A Bermuda Rectangle is any rectangle of integer side lengths `a`, `b` (with `a * b = S`) whose bottom-left corner is at the origin. Each such choice is fully described by a divisor of `S`. A cell `(u, v)` (with `0 <= u < x` and `0 <= v < y`) lies inside some Bermuda Rectangle precisely when there is a divisor `a | S` such that `a > u` and `S / a > v`.

The key observation is to sort the widths `a` in increasing order. For a fixed divisor `a` (width, so height `S/a`), the set of cells it covers is `[0, a) x [0, S/a)`. Cells in the strip `[a_prev, a) x [0, S/a)` are covered by this divisor and by no smaller divisor, so the answer can be computed by accumulating the contributions of disjoint horizontal strips.

### How it works

1. Factor `S` by iterating `i` from `1` up to `√S`, pushing both `i` and `S/i` (when distinct) into `factors`, then sorting - giving all possible rectangle widths in increasing order.
2. For each sorted divisor, compute its strip width `w[i]` (distance to the previous divisor) and height `h[i] = S / factors[i]`. Build prefix sums `preWidth` (sum of strip widths) and `preArea` (the area contributions of fully-covered strips).
3. For each query `(x, y)`:
   - `index` is the position of the first divisor `>= x` (`lower_bound`).
   - Binary search among divisors `[0, index)` for the largest divisor whose height `>= y`; this `pos` is the last fully-covered strip from below.
   - Strips `0..pos` are fully covered up to full height `y`, contributing `preWidth[pos+1] * y`.
   - Strips `pos+1..index-1` are covered only up to their own height `h[i]`, contributing their prefix area difference.
   - The partial strip from `factors[index-1]` up to `x` is covered up to `min(h[index], y)`, contributing `(x - prev) * min(h[index], y)`.

### Variables

- `factors` - sorted list of divisors of `S` (each a candidate rectangle width)
- `w` - width of the horizontal strip belonging to each divisor
- `h` - height `S / factors[i]` of each candidate Bermuda Rectangle
- `preWidth` / `preArea` - prefix sums of strip widths and strip area contributions
- `x`, `y` - query rectangle's width and height
- `index` - first divisor `>= x`
- `pos` - last fully-covered divisor (height `>= y`)
- `ans` - number of cells of the `(x, y)` rectangle covered by some Bermuda Rectangle
