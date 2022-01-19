# 2022 ICPC Qualifier Solutions


## [Tarifa](https://open.kattis.com/problems/tarifa)
* Difficulty: Easy
* Categories: Ad-Hoc, Math

### Solution
Simulate the problem by iterating through the `N` months and computing the carryover.
The carryover into the next month is the sum of the previous carryover and `X` minus the data used in that month `Pi`.

There also exists a simple mathematical solution: The answer is `N+1` times `X` minus the sum of all `Pi`.


## [Kleptography](https://open.kattis.com/problems/kleptography)
* Difficulty: Easy
* Categories: Ad-Hoc, Math, Strings

### Solution
Starting from the back of the ciphertext, we can get the key that was used by subtracting known plaintext character from the ciphertext character.
As the problem is defined, this derived key is the plaintext character `n` characters prior.
Thus, as a plaintext character is revealed, it reveals a corresponding key which is the plaintext character of a previous character.


## [Musical Notation](https://open.kattis.com/problems/musicalnotation)
* Difficulty: Easy
* Categories: Ad-Hoc, Implemenation, Strings

### Solution
This is an implementation problem so there are a variety of different ways to approach this problem.
The key is write organized and well-structured code.
An example of a possible approach is to build the strings for each tone on the staff one note at a time.


## [Antenna Analysis](https://open.kattis.com/problems/antennaanalysis)
* Difficulty: Medium
* Categories: Array, Greedy, Math, Prefixes

### Solution
To understand the intuition for solving this problem, consider the naive bruteforce solution.
In the bruteforce, for every index `i`, you compute for every index `j < i` the stated formula `|xi-xj| - c|i-j|` and take the maximum.
What you can notice is that if, for an index `i`, the index which yields the maximum in this formula us `j`, then for `i+1` the index which yields the maximum is either `j` or `i`.
Thus, we can simply keep a running maximum as we iterate through the array.
As a small caveat, because we are taking the absolute value, we need to also keep a running minimum as we iterate through the array.
With these running maximums and minimums, every step through the array we need to add `C` to the minimum and subtract `C` from the maximum because of the `c|i-j|` term in the formula.
