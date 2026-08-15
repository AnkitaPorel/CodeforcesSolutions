# Three Numbers on the Blackboard

- **Time complexity:** O(1) per test case (O(t) overall) - a constant number of operations per test case after reading the three integers
- **Memory limit:** 256 megabytes
- **Space complexity:** O(1) - only the fixed-size array of three integers is used

## Problem Statement

Ithea writes three non-negative integers `a`, `b`, and `c` on a blackboard.

Chtholly may perform the following operation an arbitrary number of times (possibly zero):

- Choose one of the three current integers and replace it with the sum of the other two current integers. The other two integers remain unchanged.

For example, starting from `(3, 5, 11)`, she can replace `11` with `3 + 5`, obtaining `(3, 5, 8)`.

Nephren wants to know the minimum range of the three integers that Chtholly can obtain. (The range of a collection of numbers is its maximum value minus its minimum value.)

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 100`).
- The description of each test case follows:
  - The only line contains three integers `a`, `b`, and `c` (`0 <= a, b, c <= 10^9`) - the integers initially written on the blackboard.

## Output

For each test case, output a single integer - the minimum possible range of the three integers.

## Solution

Sort the three numbers so that `a[0] <= a[1] <= a[2]`. Only two replacements are ever worth considering, and both are captured by one formula.

### How it works

1. Replace the largest number `a[2]` with `a[0] + a[1]`, yielding `(a[0], a[1], a[0] + a[1])`. Its range is `a[0] + a[1] - a[0] = a[1]`.
2. Replace the middle number `a[1]` with `a[0] + a[2]`, yielding `(a[0], a[2], a[0] + a[2])`. Its range is `a[2] - a[0]`.
3. Replacing the smallest number always increases the spread and repeating operations cannot beat the better of these two outcomes, so the answer is `min(a[1], a[2] - a[0])`.

### Variables

- `a` - the array of three integers, sorted in non-decreasing order
- `a[0]`, `a[1]`, `a[2]` - the smallest, middle, and largest of the three numbers
- Final answer: `min(a[1], a[2] - a[0])` - the minimum range obtainable by either shrinking the largest element down to `a[0] + a[1]` or raising the middle element up to `a[0] + a[2]`
