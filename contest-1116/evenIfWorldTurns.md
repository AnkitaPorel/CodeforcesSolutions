# Even If the World Turns

- **Time complexity:** O(n²) per test case - reading the picture, counting the minority color, accumulating the centroid sums, and locating the swap pair are each a single pass over the n² cells
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n²) for the stored picture

## Problem Statement

This is a **run-twice** problem: the same program is executed once as Chtholly and once as Willem, with no information shared between the runs except what the jury passes.

1. Chtholly is shown an `n × n` black-and-white picture with `w` black cells (`gcd(n, w) = 1`) and a target cell `x`. She must flip the colors of two cells (possibly the same) and output nothing else.
2. Nygglatho then secretly transforms the picture any number of times: cyclic shifts, 90° clockwise rotations, reflections across the vertical axis, and color inversions. The target cell moves with every geometric transformation and never with an inversion.
3. Willem sees only the final picture and must output the final position of the target.

Chtholly and Willem agree on a strategy beforehand; the whole secret is to **encode the target into the picture itself** via the swap, in a way that survives every transformation.

## Input

- First run: the line `first`, then `t` test cases. Each case has `n`, then `n` picture rows (# = black, . = white), then the target `rx cx`.
- Second run: the line `second`, then `t` test cases (same set, possibly reordered). Each case has `n` and the `n` rows of the transformed picture; no target is given.
- `t <= 10^4`, `2 <= n <= 800`, sum of `n²` over all test cases `<= 800²`.

## Output

- First run: four integers `r1 c1 r2 c2` - the cells to swap.
- Second run: two integers `r'x c'x` - final target position.

## Solution

The trick is to mark the target cell `x` into the picture by steering the **centroid of the minority-colored cells** onto it. Then Willem recovers the target simply by computing that centroid - the transformations move it in exactly the same way they move the target.

### The centroid of the minority color

Pick the scarcer color: if `w · 2 < n²` the marked color is `#` (black count `w`), otherwise `.` (white count `n² - w`). Let `m` be its count. Accumulate `sumR` and `sumC` over marked cells and define the centroid

```
Rc = (sumR · m⁻¹) mod n,   Cc = (sumC · m⁻¹) mod n
```

Because `gcd(n, w) = 1` and `gcd(n, n² - w) = gcd(n, w) = 1`, the count `m` is always coprime to `n`, so the **modular inverse of `m` modulo `n` exists and is unique** - the centroid is well defined even though we only know things modulo `n`.

### On Fermat's little theorem

The inverse `m⁻¹` is the whole engine of this solution. When the modulus is a prime `p`, Fermat's little theorem says `aᵖ ≡ a (mod p)`, i.e. `a^(p-1) ≡ 1 (mod p)` for `a` not divisible by `p`, which yields the inverse directly as `a^(p-2) mod p`. Here, however, `n ≤ 800` is composite (e.g. `n = 4, 6, ...`), so Fermat's little theorem does not apply. The code therefore uses the **extended Euclidean algorithm** (`ext_gcd`), which computes `x` in `m·x ≡ 1 (mod n)` for any modulus - exactly the general tool Fermat's theorem is the special (prime-modulus) instance of.

### How Chtholly encodes the target

Let the target be `(xr0, xc0)` (0-indexed). The swap should move the centroid there:

```
diffR = (xr0 - Rc) mod n        diffC = (xc0 - Cc) mod n
Dr = diffR · m mod n            Dc = diffC · m mod n
```

Find a marked cell `(i, j)` whose shifted spot `(i + Dr, j + Dc) mod n` is **not** marked, and swap them. Removing `(i, j)` and adding `(i + Dr, j + Dc)` changes the sum by `(Dr, Dc)`, so the new centroid becomes `(Rc + diffR, Cc + diffC) = (xr0, xc0)` - **the centroid now equals the target**. If the target already coincides with the centroid (`Dr = Dc = 0`) she swaps a cell with itself; such a pair always exists because an invariant non-empty shift whose order exceeds 1 would force `gcd(n, m) > 1`.

### Why every transformation preserves the message

Let `G` be the geometric transform (shift/rotate/reflect) and `C` the current centroid = target.

- **Shifts/rotations/reflections** are linear on coordinates modulo `n`, so they carry the centroid `C` exactly onto the target's new position - the two stay locked together.
- **Color inversion** swaps which color is the minority. The new marked cells are the complement of the old set. Their centroid `C'` satisfies `m·C + (n²-m)·C' ≡ 0 (mod n)`. Since `n² ≡ 0 (mod n)` we have `n² - m ≡ -m (mod n)`, so `C' ≡ -m·C·(-m)⁻¹ ≡ C (mod n)`. The complement's centroid equals the original centroid - and inversion never moves the target.

So whatever combination of shifts, rotations, reflections, and inversions Nygglatho applies, the centroid of the resulting minority color stays glued to the transformed target.

### How it works

1. Mark the minority color (`markedChar`) and count `m`; `blackMinority` records whether `#` is the scarcer color.
2. Reduce `mm = m mod n`, take `minv = modinv(mm, n)` via the extended Euclidean algorithm, and compute `Rc = (sumR mod n) · minv mod n`, `Cc = (sumC mod n) · minv mod n`.
3. **First run:** compute `Dr, Dc` from the target, locate a marked cell whose `(Dr, Dc)`-offset is unmarked, and output the pair; if already aligned, output a self-swap `1 1 1 1`.
4. **Second run:** print `Rc + 1, Cc + 1` - the recovered target.

### Variables

- `image` - the picture rows (`#` / `.`)
- `isFirst` - run mode (`first` = Chtholly, `second` = Willem)
- `rx`, `cx` - target cell given only on the first run
- `w` - number of black cells in the picture
- `total` - `n²`, the number of all cells
- `blackMinority` - whether `#` is the scarcer color; `markedChar` - the scarcer color itself
- `m` - count of marked cells (minority color)
- `sumR`, `sumC` - accumulated row/column indices of marked cells
- `minv` - modular inverse of `m` modulo `n`
- `Rc`, `Cc` - centroid of the marked cells (0-indexed), the encoded target on the second run
- `xr0`, `xc0`, `diffR`, `diffC`, `Dr`, `Dc` - target position and the offset needed to steer the centroid onto it
- `pr, pc` - a marked cell to remove; `qr, qc` - the unmarked cell to add