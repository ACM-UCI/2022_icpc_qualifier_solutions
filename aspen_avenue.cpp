/*
 *                                                                
 *   __ _ ___ _ __   ___ _ __     __ ___   _____ _ __  _   _  ___ 
 *  / _` / __| '_ \ / _ \ '_ \   / _` \ \ / / _ \ '_ \| | | |/ _ \
 * | (_| \__ \ |_) |  __/ | | | | (_| |\ V /  __/ | | | |_| |  __/
 *  \__,_|___/ .__/ \___|_| |_|  \__,_| \_/ \___|_| |_|\__,_|\___|
 *           |_|                                                  
 *
 */

#include <bits/stdc++.h>

int N;
double L,W;
std::vector<int> arr;
double sep;

std::vector<std::vector<double>> cache;

double dp(int i, int j) {
    if (i+j >= N) {
        if (i == j) {
            return 0.0;
        } else {
            return 1e6;
        }
    }

    if (cache[i][j] >= 0) {
        return cache[i][j];
    }

    double op1 = std::abs(arr[i+j] - (i*sep)) + dp(i+1, j);
    double op2 = std::hypot(arr[i+j] - (j*sep), W) + dp(i, j+1);
    return cache[i][j] = std::min(op1, op2);
}

int main() {

    scanf("%d", &N);
    scanf("%lf %lf", &L, &W);
    arr.assign(N, 0);
    cache.assign(N, std::vector<double>(N, -1));
    for (int i = 0; i < N; ++i) { scanf("%d", &arr[i]); }
    std::sort(std::begin(arr), std::end(arr));
    sep = L/((N/2) - 1);

    double res = dp(0, 0);

    printf("%.9lf\n", res);

    return 0;
}
