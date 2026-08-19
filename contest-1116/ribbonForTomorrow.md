# Ribbon for Tomorrow

- **Time complexity:** O(n) per test case after precomputing factorials and inverse factorials in O(max_n)
- **Memory limit:** 256 megabytes
- **Space complexity:** O(max_n) for the precomputed factorials, inverse factorials, and modular powers

## Problem Statement

Nephren places `n` glass beads in a row, each either white (`0`) or black (`1`), represented by a binary string `s`.

She can perform the following operation any number of times:

- Choose two indices `l` and `r` (`1 <= l <= r <= n`) such that `s[l] = s[r]`, and reverse the substring `s[l..r]`.

Determine the number of different binary strings that can be obtained from `s`, modulo `998244353`.

### Example

If `s = 00110`, choosing `l=1` and `r=5` (both `0`) reverses the whole string, yielding `01100`.

## Input

- The first line contains `t` (`1 <= t <= 10^4`) - number of test cases.
- For each test case:
  - The first line contains one integer `n` (`1 <= n <= 10^6`).
  - The second line contains a binary string `s` of length `n`.
- The sum of `n` over all test cases does not exceed `10^6`.

## Output

For each test case, output a single integer - the number of different binary strings obtainable, modulo `998244353`.

## Solution

### Key Insight

The operation preserves the **number of contiguous segments** of `0`s and `1`s, but allows freely redistributing the **sizes** of those segments (each segment must still have at least 1 bead).

Consider the alternating segments of `0`s and `1`s. When you reverse a substring bounded by two equal characters, you swap the inner portion, which effectively redistributes bead counts among segments without changing the segment count.

Therefore, the number of distinct strings equals:

```
C(zeros - 1, seg0 - 1) * C(ones - 1, seg1 - 1)
```

where:
- `zeros` = total number of `0`s, `ones` = total number of `1`s
- `seg0` = number of contiguous segments of `0`s, `seg1` = number of contiguous segments of `1`s

This is a classic stars-and-bars result: distributing `k` identical items into `m` non-empty groups can be done in `C(k-1, m-1)` ways.

### Fermat's Little Theorem

The solution requires computing binomial coefficients `C(n, r) = n! / (r! * (n-r)!)` modulo `998244353`. Since division is not directly supported in modular arithmetic, we need modular inverses.

**Fermat's Little Theorem** states that for a prime `p` and an integer `a` not divisible by `p`:

$$ a^{p-1} \equiv 1 \pmod p $$


This implies:
$$a \cdot a^{p-2} \equiv 1 \pmod p$$
So the modular inverse of $a$ is $a^{p-2} \pmod p$.


In the code (`ribbonForTomorrow.cpp:40`), the inverse factorial array is computed as:

```cpp
ifact[n] = binexpo(fact[n], mod - 2, mod);  // fact[n]^(p-2) mod p
```

This is then used to efficiently compute `C(n, r)` in O(1) after O(n) precomputation:

```cpp
ll nCr(ll n, ll r) {
    return fact[n] * ifact[r] % mod * ifact[n - r] % mod;
}
```

### Variables

- `zeros`, `ones` - total counts of `0`s and `1`s in the string
- `seg0`, `seg1` - number of contiguous segments of `0`s and `1`s
- `ways0 = C(zeros - 1, seg0 - 1)` - ways to distribute `0`s across `0`-segments
- `ways1 = C(ones - 1, seg1 - 1)` - ways to distribute `1`s across `1`-segments
- Final answer: `ways0 * ways1 % MOD`
