/*
 *   __ _                  __               
 *  / _| | _____      __  / _|_ __ ___  ___ 
 * | |_| |/ _ \ \ /\ / / | |_| '__/ _ \/ _ \
 * |  _| | (_) \ V  V /  |  _| | |  __/  __/
 * |_| |_|\___/ \_/\_/   |_| |_|  \___|\___|
 *                                          
 *
 */

#include <bits/stdc++.h>

std::vector<std::string> board(4, std::string(4, ' '));
std::map<char, std::pair<int,int>> start, end;
std::vector<char> colors;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

bool dfs(int colidx, int r, int c, int used) {
    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nc >= 0 && nr < 4 && nc < 4) {
            if (nr == end[colors[colidx]].first && nc == end[colors[colidx]].second) {
                if (colidx+1 == static_cast<int>(colors.size())) {
                    if (used == 16) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    std::pair<int,int> next = start[colors[colidx+1]];
                    if (dfs(colidx + 1, next.first, next.second, used)) {
                        return true;
                    }
                }
            } else if (board[nr][nc] == 'W') {
                char old = board[nr][nc];
                board[nr][nc] = colors[colidx] + 32;
                if (dfs(colidx, nr, nc, used+1)) {
                    return true;
                }
                board[nr][nc] = old;
            }
        }
    }
    return false;
}

int main() {

    for (int r = 0; r < 4; ++r) {
        std::cin >> board[r];
    }

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            if (board[r][c] != 'W') {
                if (start.count(board[r][c])) {
                    end[board[r][c]] = {r,c};
                } else {
                    start[board[r][c]] = {r,c};
                    colors.push_back(board[r][c]);
                }
            }
        }
    }

    bool res = dfs(0, start[colors[0]].first, start[colors[0]].second, static_cast<int>(colors.size()) * 2);

    if (res) {
        std::cout << "solvable" << std::endl;
    } else {
        std::cout << "not solvable" << std::endl;
    }


    return 0;
}
