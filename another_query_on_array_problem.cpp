/* _   _                                             
 *   __ _ _ __   ___ | |_| |__   ___ _ __    __ _ _   _  ___ _ __ _   _ 
 *  / _` | '_ \ / _ \| __| '_ \ / _ \ '__|  / _` | | | |/ _ \ '__| | | |
 * | (_| | | | | (_) | |_| | | |  __/ |    | (_| | |_| |  __/ |  | |_| |
 *  \__,_|_| |_|\___/ \__|_| |_|\___|_|     \__, |\__,_|\___|_|   \__, |
 *                                             |_|                |___/ 
 *                                           
 *   ___  _ __     __ _ _ __ _ __ __ _ _   _ 
 *  / _ \| '_ \   / _` | '__| '__/ _` | | | |
 * | (_) | | | | | (_| | |  | | | (_| | |_| |
 *  \___/|_| |_|  \__,_|_|  |_|  \__,_|\__, |
 *                                     |___/ 
 *                  _     _                
 *  _ __  _ __ ___ | |__ | | ___ _ __ ___  
 * | '_ \| '__/ _ \| '_ \| |/ _ \ '_ ` _ \ 
 * | |_) | | | (_) | |_) | |  __/ | | | | |
 * | .__/|_|  \___/|_.__/|_|\___|_| |_| |_|
 * |_|                                     
 *
 */

#include <bits/stdc++.h>

typedef long long LL;

constexpr LL MOD        = 1e9 + 7;

constexpr LL inverse_mod(LL b, LL k) {
    if (k == 0LL) return 1LL;
    else if (k == 1LL) return b % MOD;
    else {
        LL res = inverse_mod(b, k/2LL);
        return (((res * res) % MOD) * inverse_mod(b, k%(2LL))) % MOD;
    }
}

constexpr LL i_mod2 = inverse_mod(2LL, MOD-2);
constexpr LL i_mod6 = inverse_mod(6LL, MOD-2);
constexpr LL i_mod4 = inverse_mod(4LL, MOD-2);

class SegTree {
private:
    static int left(int x) { return (x<<1) + 1; }
    static int right(int x) { return (x<<1) + 2; }
    static int mid(int l, int r) { return (r-l)/2 + l; }

    static LL pow(LL b, LL k) {
        if (k == 0) return 1;
        else if (k == 1) return b % MOD;
        else {
            LL res = SegTree::pow(b, k/2);
            return (((res * res) % MOD) * SegTree::pow(b, k%(2))) % MOD;
        }
    }

    static LL divide_modulo(LL a, LL b) {
        return (a * SegTree::pow(b, MOD-2)) % MOD;
    }

    // the following functions compute closed form sums from x = 1 to x = n inclusive
    static LL sum_t0(LL coef, LL n) {
        return (coef * n) % MOD;
    }

    static LL sum_t1(LL coef, LL n) {
        LL num = (n * (n+1)) % MOD;
        return (((coef * num) % MOD) * i_mod2) % MOD;
    }

    static LL sum_t2(LL coef, LL n) {
        LL num = (((n * (n+1)) % MOD) * (((2*n) % MOD) + 1)) % MOD;
        return (((coef * num) % MOD) * i_mod6) % MOD;
    }

    static LL sum_t3(LL coef, LL n) {
        LL num = (((n*n) % MOD) * (((n+1)*(n+1)) % MOD)) % MOD;
        return (((coef * num) % MOD) * i_mod4) % MOD;
    }

    struct Node {
        LL t0,t1,t2,t3; // terms, t3 refers to x^3 term
        Node() : t0{0ll}, t1{0ll}, t2{0ll}, t3{0ll} { }
        Node(LL t0, LL t1, LL t2, LL t3) : t0{t0}, t1{t1}, t2{t2}, t3{t3} { }

        Node get_shift(LL c) const {
            // k(x + c) = kx + kc

            // k(x + c)^2 = kx^2 + k2cx + kc^2
            
            // k(x + c)^3 = k(x^2 + 2cx + c^2)(x + c)
            //           = k(x^3 + 2cx^2 + (c^2)x + cx^2 + 2(c^2)x + c^3)
            //           = kx^3 + (k3c)x^2 + (k3c^2)x + kc^3

            return Node(
                    (((((((t3*c)%MOD)*c)%MOD)*c)%MOD) + ((((t2*c)%MOD)*c)%MOD) + ((t1*c)%MOD) + t0)%MOD,
                    (((((((3*t3)%MOD)*c)%MOD)*c)%MOD) + ((((2*t2)%MOD)*c)%MOD) + t1)%MOD,
                    ((((3*t3)%MOD)*c)%MOD + t2)%MOD,
                    t3
            );
        }

        LL evaluate(LL len) const {
            return (SegTree::sum_t0(t0, len) + SegTree::sum_t1(t1, len-1) + SegTree::sum_t2(t2, len-1) + SegTree::sum_t3(t3, len-1))%MOD;
        }

        void add(const Node &other) {
            t0 = (t0 + other.t0) % MOD;
            t1 = (t1 + other.t1) % MOD;
            t2 = (t2 + other.t2) % MOD;
            t3 = (t3 + other.t3) % MOD;
        }
    };


    int size;
    LL st[400000];
    Node lz[400000];
    bool pr[400000];

    void propagate(int x, int lx, int rx) {
        if (rx-lx == 1) {
            lz[x] = Node();
            pr[x] = false;
        } else if (pr[x]) {
            int mx = SegTree::mid(lx, rx);

            lz[SegTree::left(x)].add(lz[x]);
            st[SegTree::left(x)] = (st[SegTree::left(x)] + lz[x].evaluate(mx-lx)) % MOD;
            pr[SegTree::left(x)] = true;

            Node shift = lz[x].get_shift(mx-lx);
            lz[SegTree::right(x)].add(shift);
            st[SegTree::right(x)] = (st[SegTree::right(x)] + shift.evaluate(rx-mx)) % MOD;
            pr[SegTree::right(x)] = true;

            lz[x] = Node();
            pr[x] = false;
        }
    }

    void add(int l, int r, Node n, int x, int lx, int rx) {
        this->propagate(x, lx, rx);
        if (rx <= l || r <= lx) {
            return;
        } else if (l <= lx && rx <= r) {
            st[x] = (st[x] + n.evaluate(rx-lx)) % MOD;
            lz[x] = n;
            pr[x] = true;
        } else {
            int mx = SegTree::mid(lx, rx);
            add(l, r, n, SegTree::left(x), lx, mx);
            add(l, r, n.get_shift(mx-lx), SegTree::right(x), mx, rx);
            st[x] = (st[SegTree::left(x)] + st[SegTree::right(x)]) % MOD;
        }
    }

    LL rsq(int l, int r, int x, int lx, int rx) {
        this->propagate(x, lx, rx);
        if (rx <= l || r <= lx) {
            return 0ll;
        } else if (l <= lx && rx <= r) {
            return st[x];
        } else {
            int mx = SegTree::mid(lx, rx);
            LL r1 = rsq(l, r, SegTree::left(x), lx, mx);
            LL r2 = rsq(l, r, SegTree::right(x), mx, rx);
            return (r1 + r2) % MOD;
        }
    }

public:
    SegTree(int N) : size{1} {
        while (size < N) { size <<= 1; }
        std::fill(st, st + (size<<1), 0LL);
        std::fill(lz, lz + (size<<1), Node());
        std::fill(pr, pr + (size<<1), false);
    }

    void print() {
        std::queue<std::array<int,3>> q; q.push(std::array<int,3>({0,0,size}));
        while (!q.empty()) {
            int lvl = q.size();
            for (int i = 0; i < lvl; ++i) {
                std::array<int,3> curr = q.front(); q.pop();
                this->propagate(curr[0], curr[1], curr[2]);
                printf("%lld ", st[curr[0]]);
                if (curr[2]-curr[1] != 1) {
                    int mid = SegTree::mid(curr[1], curr[2]);
                    q.push(std::array<int,3>({SegTree::left(curr[0]), curr[1], mid}));
                    q.push(std::array<int,3>({SegTree::right(curr[0]), mid, curr[2]}));
                }
            } printf("\n");
        }
    }

    void add(int l, int r) {
        add(l, r, SegTree::Node(6LL, 11LL, 6LL, 1LL).get_shift((MOD-l)%MOD), 0, 0, size);
    }

    void sub(int l, int r) {
        add(l, r, SegTree::Node(MOD-6LL, MOD-11LL, MOD-6LL, MOD-1LL).get_shift((MOD-l)%MOD), 0, 0, size);
    }

    LL rsq(int l, int r) {
        return rsq(l, r, 0, 0, size) % MOD;
    }
};


int main() {
    int N,M; scanf("%d %d", &N, &M);
    SegTree st(N);
    while (M--) {
        int t,x,y; scanf("%d %d %d", &t, &x, &y);
        assert(x <= y);
        if (t == 0) {
            printf("%lld\n", st.rsq(x-1, y));
        } else if (t == 1) {
            st.add(x-1, y);
        } else if (t == 2) {
            st.sub(x-1, y);
        }
    }

    return 0;
}
