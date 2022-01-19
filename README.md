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
