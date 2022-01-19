# 2022 ICPC Qualifier Solutions

## [Tarifa](https://open.kattis.com/problems/tarifa)
* Difficulty: Easy
* Categories: Ad-Hoc, Math

### Solution
Simulate the problem by iterating through the `N` months and computing the carryover.
The carryover into the next month is the sum of the previous carryover and `X` minus the data used in that month `Pi`.

There also exists a simple mathematical solution: The answer is `N+1` times `X` minus the sum of all `Pi`.
