/*
 *  _    _            _                              _           
 * | | _| | ___ _ __ | |_ ___   __ _ _ __ __ _ _ __ | |__  _   _ 
 * | |/ / |/ _ \ '_ \| __/ _ \ / _` | '__/ _` | '_ \| '_ \| | | |
 * |   <| |  __/ |_) | || (_) | (_| | | | (_| | |_) | | | | |_| |
 * |_|\_\_|\___| .__/ \__\___/ \__, |_|  \__,_| .__/|_| |_|\__, |
 *             |_|             |___/          |_|          |___/ 
 *
 */

#include <bits/stdc++.h>

int main() {

    int N,M; std::cin >> N >> M;
    std::string known; std::cin >> known;
    std::string cipher; std::cin >> cipher;

    std::vector<int> X(N);
    std::vector<int> C(M);
    for (int i = 0; i < N; ++i) { X[i] = known[i] - 'a'; }
    for (int i = 0; i < M; ++i) { C[i] = cipher[i] - 'a'; }

    std::queue<int> q;
    for (int i = N-1; i >= 0; --i) { q.push(X[i]); }

    std::string ans(M, ' ');
    for (int i = M-1; i >= 0; --i) {
        ans[i] = q.front() + 'a';
        int key = (C[i] - q.front() + 52) % 26;
        q.pop();
        q.push(key);
    }

    std::cout << ans << std::endl;

    return 0;
}
