/*
 *              _                                             _           _     
 *   __ _ _ __ | |_ ___ _ __  _ __   __ _    __ _ _ __   __ _| |_   _ ___(_)___ 
 *  / _` | '_ \| __/ _ \ '_ \| '_ \ / _` |  / _` | '_ \ / _` | | | | / __| / __|
 * | (_| | | | | ||  __/ | | | | | | (_| | | (_| | | | | (_| | | |_| \__ \ \__ \
 *  \__,_|_| |_|\__\___|_| |_|_| |_|\__,_|  \__,_|_| |_|\__,_|_|\__, |___/_|___/
 *                                                              |___/           
 *
 */

#include <bits/stdc++.h>

typedef long long LL;

int main() {

    LL N,C; std::cin >> N >> C;
    std::vector<LL> arr(N);
    for (int i = 0; i < N; ++i) std::cin >> arr[i];

    LL min = arr[0], max = arr[0];
    std::vector<LL> ans(N);
    for (int i = 0; i < N; ++i) {
        min = std::min(min, arr[i]);
        max = std::max(max, arr[i]);
        ans[i] = std::max(arr[i]-min, max-arr[i]);
        min += C;
        max -= C;
    }

    for (const LL &v : ans) { std::cout << v << ' '; }
    std::cout << std::endl;

    return 0;
}
