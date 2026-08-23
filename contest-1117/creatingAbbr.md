# Creating Abbreviations

- **Time complexity:** O(L) per test case, where `L` is the total length of all strings - one pass marks the first letters of the ordinary words, then every character of every abbreviation is checked once against that mark array
- **Memory limit:** 256 megabytes
- **Space complexity:** O(n + m) for the stored strings, O(1) extra (a fixed 26-entry mark array)

## Problem Statement

The Beaver was given a set of words `S` that initially contained `n` lowercase words. He then performed the following operation `m` times:

- He forms a sequence of one or more words from `S` (the same word may appear several times). The **abbreviation** of the sequence is the word made of the first letters of its words (e.g. the sequence `birch OAK birch redwood` produces `BOBR`).
- He adds the resulting abbreviation to `S`, so it can be used as an ordinary word in subsequent operations.

Given the `n` initial words and the `m` abbreviations he formed (not necessarily in the order they were created), determine whether **all** of these abbreviations could really have appeared through the described process.

## Input

Each test contains multiple test cases.

- The first line contains the number of test cases `t` (`1 <= t <= 500`).
- The description of each test case follows:
  - The first line contains two integers `n` and `m` (`1 <= n, m <= 100`) - the number of ordinary words and the number of abbreviations.
  - The next `n` lines contain one string `wi` each (`1 <= |wi| <= 20`) - an ordinary word.
  - The next `m` lines contain one string `ai` each (`1 <= |ai| <= 20`) - an abbreviation formed by the Beaver.

All ordinary words consist of lowercase English letters, and all abbreviations consist of uppercase English letters. In each test case, all strings are pairwise distinct. The total length of all strings over all test cases does not exceed `50000`.

## Output

For each test case, print `YES` if there exists a suitable order in which the given abbreviations could have appeared, and `NO` otherwise.

## Solution

The whole task collapses into a single-letter reachability check: an abbreviation can be produced if and only if **every one of its letters matches the first letter of some initial word**.

*Necessity:* look at the chronologically first abbreviation that uses a letter `L` never seen as a first letter of an initial word. Letter `L` in its sequence must come from some word of `S`; tracing the chain of abbreviations that could supply `L` backwards always ends at the first abbreviation introducing `L` - but that one could only be built from initial words, a contradiction.

*Sufficiency:* if every letter is already available as the first letter of an initial word, the abbreviations can simply be created in **any** order: build each one directly out of the initial words supplying its letters (reusing a word is allowed), so intermediate abbreviations are never needed.

### How it works

1. Mark in `mp` the set of letters that occur as the **first letter of some ordinary word**: `mp[s[0] - 'a'] = 1`.
2. Scan every character of every abbreviation and require `mp[ch - 'A']` to be set; a single uncovered letter makes the whole test case invalid (`ok` becomes `0`).
3. Print `YES` when all letters of all abbreviations were covered, `NO` otherwise.

### Variables

- `w` - the initial ordinary words (lowercase)
- `a` - the abbreviations to verify (uppercase)
- `mp` - boolean table over the alphabet; `mp[c] = 1` means some ordinary word starts with the lowercase letter `c`
- `ok` - flag that stays `1` only while every seen abbreviation character maps to a marked first letter
