/*
 *                           _       _   _                __            
 *   __ _ ___ ___  ___   ___(_) __ _| |_(_) ___  _ __    / _| ___  _ __ 
 *  / _` / __/ __|/ _ \ / __| |/ _` | __| |/ _ \| '_ \  | |_ / _ \| '__|
 * | (_| \__ \__ \ (_) | (__| | (_| | |_| | (_) | | | | |  _| (_) | |   
 *  \__,_|___/___/\___/ \___|_|\__,_|\__|_|\___/|_| |_| |_|  \___/|_|   
 *                                                                      
 *  _   _                                  _                       __ 
 * | |_| |__   ___    ___ ___  _   _ _ __ | |_ _ __ _   _    ___  / _|
 * | __| '_ \ / _ \  / __/ _ \| | | | '_ \| __| '__| | | |  / _ \| |_ 
 * | |_| | | |  __/ | (_| (_) | |_| | | | | |_| |  | |_| | | (_) |  _|
 *  \__|_| |_|\___|  \___\___/ \__,_|_| |_|\__|_|   \__, |  \___/|_|  
 *                                                  |___/             
 *                  _           _           
 *  _ __ ___  _   _| |__   __ _| |__   __ _ 
 * | '_ ` _ \| | | | '_ \ / _` | '_ \ / _` |
 * | | | | | | |_| | |_) | (_| | |_) | (_| |
 * |_| |_| |_|\__,_|_.__/ \__,_|_.__/ \__,_|
 *                                          
 *
 */

#include <bits/stdc++.h>

typedef long long LL;

struct State {
    int max;
    LL req;
    State(int max, LL req) : max{max}, req{req} { }

    friend std::ostream &operator<<(std::ostream &os, const State &s) {
        os << '{' << s.max << ',' << s.req << '}';
        return os;
    }
};

int main() {

    int N; scanf("%d", &N);
    std::vector<LL> arr(N);
    for (int i = 0; i < N; ++i) {
        scanf("%lld", &arr[i]);
    }
    std::vector<std::vector<State>> opts(N+1);
    opts[0].push_back(State(0, 0));
    for (int i = 0; i < N; ++i) {
        LL sum = 0ll;
        int ptr = static_cast<int>(opts[i].size()) - 1;
        for (int j = i; j < N; ++j) {
            sum += arr[j];

            int best = -1;
            while (ptr >= 0 && sum >= opts[i][ptr].req) {
                best = std::max(best, opts[i][ptr].max + 1);
                --ptr;
            }
            ptr = std::min(ptr + 1, static_cast<int>(opts[i].size()) - 1);

            if (best >= 0) {
                if (opts[j+1].empty()) {
                    opts[j+1].push_back(State(best, sum));
                } else {
                    opts[j+1].push_back(State(std::max(opts[j+1].back().max, best), sum));
                }
            }
        }
    }

    printf("%d\n", opts.back().back().max);

    return 0;
}
