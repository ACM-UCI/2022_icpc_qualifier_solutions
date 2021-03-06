# [2022 ICPC Qualifier Solutions](https://open.kattis.com/contests/iyekmv)


## [Tarifa](https://open.kattis.com/problems/tarifa)
* Difficulty: Easy
* Categories: Ad-Hoc, Math
* Complexity: O(N)

### Solution
Simulate the problem by iterating through the `N` months and computing the carryover.
The carryover into the next month is the sum of the previous carryover and `X` minus the data used in that month `Pi`.

There also exists a simple mathematical solution: The answer is `N+1` times `X` minus the sum of all `Pi`.


## [Kleptography](https://open.kattis.com/problems/kleptography)
* Difficulty: Easy
* Categories: Ad-Hoc, Math, Strings
* Complexity: O(M)

### Solution
Starting from the back of the ciphertext, we can get the key that was used by subtracting known plaintext character from the ciphertext character.
As the problem is defined, this derived key is the plaintext character `n` characters prior.
Thus, as a plaintext character is revealed, it reveals a corresponding key which is the plaintext character of a previous character.


## [Musical Notation](https://open.kattis.com/problems/musicalnotation)
* Difficulty: Easy
* Categories: Ad-Hoc, Implementation, Strings
* Complexity: O(N)

### Solution
This is an implementation problem so there are a variety of different ways to approach this problem.
The key is write organized and well-structured code.
An example of a possible approach is to build the strings for each tone on the staff one note at a time.


## [Antenna Analysis](https://open.kattis.com/problems/antennaanalysis)
* Difficulty: Medium
* Categories: Array, Greedy, Math, Prefixes
* Complexity: O(N)

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
* Complexity: Technically O(1), but if you consider number of empty cells `N` it is O(4^N).

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
* Complexity: O(N * inverse ackermans)

### Solution
If you reframe the question from one about removing coaches and instead one about adding coaches, it becomes obvious that it can be reduced to a connected components problem.
This reframing is achieved by reversing the order in which the coaches are removed.
Then, using the [Union Find](https://cp-algorithms.com/data_structures/disjoint_set_union.html) data structure, keep track of the sums of each connected component and the number of connected components.
Components can be merged which consequently updates the sum and reduces the number of cars.


## [Aspen Avenue](https://open.kattis.com/problems/aspenavenue)
* Difficulty: Medium
* Categories: DP, Geometry, Sorting
* Complexity: O(N^2)

### Solution
For this problem it can be observed that if `i` trees in the first row and `j` trees in the second row have been placed, no matter how they were placed, the minimum cost to plant the remaining trees will be the same.
Thus, there is a topological ordering on the recurrence relation meaning dynamic programming can be applied.
A key observation that needs to be made is that if it is known which row each tree belongs in, you can greedily know that the relative ordering in each row must be the same as given in the input.
An informal proof can be seen from swap argument: if the relative ordering of two trees are swapped it will always result in cost greater than or equal to what it was intially.
A quick note about Python: unfortunately, the bounds on the problem prevent top-down recursive dp; bottom-up dp must be used instead.


## [Slow Leak](https://open.kattis.com/problems/slowleak)
* Difficulty: Medium
* Categories: All Pairs Shortest Path, Dijkstra's, Floyd-Warshall's, Graph, Single Source Shortest Path
* Complexity: O(N^3)

### Solution
A reduction can be made on the problem by first finding the shortest path between every pair of vertices.
This can easily be done with [Floyd-Warshall's](https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html).
By finding the shortest path between every pair of vertices, you can know which refill stations are reachable from which refill stations.
Thus, a simplified graph between the start, end, and all refill stations can be created.
Once this simplified graph is created, it is trivial to run [Dijksta's](https://cp-algorithms.com/graph/dijkstra.html) single-source-shortest-path.


## [Association for the Country of Mubaba](https://open.kattis.com/problems/mububa)
* Difficulty: Hard
* Categories: DP, Two Pointers
* Complexity: O(N^2)

### Solution
The first observation that must be made about this problem is that a greedy approach is not sufficient as you cannot know how many suitcases to give to an executive without knowing information about future suitcases.
Instead, dynamic programming must be used.
However, naive dynamic programming --- where, starting from a specific suitcase, you try all possible number of suitcases to give to an executive --- will not work as that would be O(N^3).
This O(N^3) occurs because at an index `i` you must search `N-i` future indices against `i` past indices to ensure the next executive gets more bananas than the previous.
But each suitcase carries a positive number of bananas so there is a monotonic property that can be taken advantage.
If you are considering adding a range of suitcases to one executive, it is sufficient to choose amongst the previous ranges that had equal or less bananas.
A segment tree could be used here but even better amortized O(1) can be achieved with a two pointer approach.


## [Blowing Candles](https://open.kattis.com/problems/blowingcandles)
* Difficulty: Hard
* Categories: Geometry, Linear Algrebra, Sorting
* Complexity: O(N logN)

### Solution
This problem can be simplified as the task of finding the minimum width across a set of cartesian points.
It is hopefully intuitively obvious that this minimum width will be the distance from one point to the line formed by two other points.
This is because you want to line up the two points forming a line on one side of the strip and thus the width will inevitably be constrained by the other point.
To find this triple pair of points you can find the [convex hull](https://cp-algorithms.com/geometry/convex-hull.html).
The convex hull has several nice properties: any side of the convex hull is always the furthest side in the direction perpendicular and outside the polygon, all corners of the convex hull are always the furthest point in som direction.
Thus, if you find the convex hull, you can iterate through every side and find the furthest point from that side (which will also be on the convex hull).
The maximum of these distances is the answer.
To find the furthest point from a side a ternary search can be used as a unimodal distribution is formed with the convex hull.
A faster approach would be to use a two point technique because if you move from one side to another in a certain direction around the polygon the furthest point from the second side will always be in the same direction from the furthest point from the first side.
This faster method is what is implemented in the provided solution file.


## [Another Query on Array Problem](https://open.kattis.com/problems/queryonarray)
* Difficulty: Hard
* Categories: Lazy Propagation, Math, Range Sum Query, Segment Tree
* Complexity: O(M logN)

### Solution
It should hopefully be obvious that a naive bruteforce solution is insufficient here as the complexity would be O(MN).
Instead, a range query data structure must be used.
Probably the easiest to implement and understand is a [segment tree](https://cp-algorithms.com/data_structures/segment_tree.html).

It is, however, initially unclear how you would implement a segment tree for this specific problem.
First notice that you are adding a sequence to a range of the form s(x) = x(x+1)(x+2).
This can be expanded to a polynomial.
The nice thing about adding polynomial sequences to ranges is that we only need to care about the coefficients of the polynomial.
To find the sum of a polynomial over a range is simple in O(1) with the closed form sums over constants, x, x^2, and x^3.
Take a look at Sum Over Sqares and Sum Over Cubes for this in the [ACM@UCI Handbook](https://github.com/ACM-UCI/DSA_Library/blob/master/acm_uci_handbook/main.pdf).
The problem is that, using a segment tree, we need a way split a polynomial into two subtrees.
This can be done by shifting the polynomial.
Notice how s(x-k) = (x-k)(x+1-k)(x+2-k) yields a different polynomial.
Thus, we can compute the resulting coefficients of a shift to get the new polynomial.
Finally, it would still be inefficient to naively add polynomials to the segment tree.
Instead, we must use a technique called lazy propagation which only pushes elements down the tree as is necessary.
With all of this combined, you can solve this problem is O(M logN).
