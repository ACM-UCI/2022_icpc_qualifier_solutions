/*
 *  _    _ _ _ _                    _                     
 * | | _(_) | (_)_ __   __ _    ___| |__   __ _  ___  ___ 
 * | |/ / | | | | '_ \ / _` |  / __| '_ \ / _` |/ _ \/ __|
 * |   <| | | | | | | | (_| | | (__| | | | (_| | (_) \__ \
 * |_|\_\_|_|_|_|_| |_|\__, |  \___|_| |_|\__,_|\___/|___/
 *                     |___/                              
 *
 */

#include <bits/stdc++.h>

typedef long long LL;

struct UnionFind {
private:
    static LL round(LL x) { return 10ll*(x/10ll) + (x%10ll ? 10ll : 0ll); }
private:
    int n;
    LL sum, numcars;
    std::vector<int> p; // parent tree
    std::vector<LL> s; // sum of each tree

    int find(int x) { return x == p[x] ? x : (p[x] = find(p[x])); }
    void merge(int a, int b) {
        int A = find(a), B = find(b);
        sum -= round(s[B]);
        sum -= round(s[A]);
        p[B] = A;
        s[A] += s[B];
        sum += round(s[A]);
        --numcars;
    }

public:
    UnionFind(int n) : n{n}, sum{0ll}, numcars{0ll}, p{std::vector<int>(n,-1)}, s{std::vector<LL>(n)} { }

    LL addCoach(int i, int occ) {
        p[i] = i;
        s[i] = occ;
        sum += round(occ);
        ++numcars;

        if (i-1 >= 0 && p[i-1] != -1) { merge(i, i-1); }
        if (i+1 < n && p[i+1] != -1) { merge(i, i+1); }

        return sum * numcars;
    }
};

int main() {

    int N; scanf("%d", &N);
    UnionFind uf(N);
    std::vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &arr[i]);
    }

    std::vector<int> steps(N);
    for (int i = N-1; i >= 0; --i) {
        scanf("%d", &steps[i]);
    }

    LL ans = 0;
    for (int i = 0; i < N; ++i) {
        LL res = uf.addCoach(steps[i]-1, arr[steps[i]-1]);
        ans = std::max(ans, res);
    }

    printf("%lld\n", ans);

    return 0;
}
