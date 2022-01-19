#include <iostream>

int main() {

    int X,N; std::cin >> X >> N;
    int carryover = 0;
    for (int i = 0; i < N; ++i) {
        int Pi; std::cin >> Pi;
        carryover = carryover + X - Pi;
    }
    std::cout << carryover + X << std::endl;

    return 0;
}
