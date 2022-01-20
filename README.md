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
* Categories: Ad-Hoc, Implementation, Strings

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


## [Flow Free](https://open.kattis.com/problems/flowfree)
* Difficulty: Medium
* Categories: Backtracking, Bruteforce, DFS, Graph, Implementation

### Solution
To understand why a bruteforce approach works here you can analyze the complexity of the problem.
Because it is guaranteed that board will always be 4x4 and that there will be at least 3 colors, we know that there will be at most 10 unfilled squares.
If we were to bruteforce every possible filling of these squares, since there are at most 4 colors, there are `4^10 = 1048576` different ways to fill in the squares.
The math actually works out to a smaller number because this type of board would only have 3 colors.
The key, however, is to realize that this complexity is feasible for the problem.

There are a variety of ways to implement this problem, probably the most intuitive would be a recursively backtracking dfs were you search one color at a time for a feasible path from some starting cell to an ending cell.
There is an interconnected relationship between all the colors so the bruteforce cannot handle each color entirely separately; instead you must keep track of what cells have been taken by other colors.


## [Killing Chaos](https://open.kattis.com/problems/killingchaos)
* Difficulty: Medium
* Categories: Connected Components, Math, Offline Algorithms, Union Find

### Solution
If you reframe the question from one about removing coaches and instead one about adding coaches, it becomes obvious that it can be reduced to a connected components problem.
This reframing is achieved by reversing the order in which the coaches are removed.
Then, using the [Union Find](https://cp-algorithms.com/data_structures/disjoint_set_union.html) data structure, keep track of the sums of each connected component and the number of connected components.
Components can be merged which consequently updates the sum and reduces the number of cars.


## [Aspen Avenue](https://open.kattis.com/problems/aspenavenue)
* Difficulty: Medium
* Categories: DP, Geometry, Sorting

### Solution
For this problem it can be observed that if `i` trees in the first row and `j` trees in the second row have been placed, no matter how they were placed, the minimum cost to plant the remaining trees will be the same.
Thus, there is a topological ordering on the recurrence relation meaning dynamic programming can be applied.
A key observation that needs to be made is that if it is known which row each tree belongs in, you can greedily know that the relative ordering in each row must be the same as given in the input.
An informal proof can be seen from swap argument: if the relative ordering of two trees are swapped it will always result in cost greater than or equal to what it was intially.
A quick note about Python: unfortunately, the bounds on the problem prevent top-down recursive dp; bottom-up dp must be used instead.
