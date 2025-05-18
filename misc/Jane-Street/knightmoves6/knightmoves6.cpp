#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int N = 6;
const int MAX_LEN = 16;
const int EXACT_LEN = 15;

int grid[N][N] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 2},
    {1, 1, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2}
};

const int knight_moves[8][2] = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

std::vector<std::pair<int, int>> neighbors[N][N];

void precompute_neighbors() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
            for (const auto& move : knight_moves) {
                int nx = x + move[0];
                int ny = y + move[1];
                if (0 <= nx && nx < N && 0 <= ny && ny < N) {
                    neighbors[x][y].emplace_back(nx, ny);
                }
            }
        }
    }
}

std::vector<std::string> stringify(const std::vector<std::pair<int, int>>& path) {
    std::vector<std::string> result;
    for (const auto& p : path) {
        char c = 'a' + p.first;
        int y = p.second + 1;
        result.push_back(std::string(1, c) + std::to_string(y));
    }
    return result;
}

std::vector<std::pair<int, int>> mirror(const std::vector<std::pair<int, int>>& path) {
    std::vector<std::pair<int, int>> result;
    for (const auto& p : path) {
        result.emplace_back(p.first, N - 1 - p.second);
    }
    return result;
}

class F {
public:
    int val;
    char type;
    F* child;

    F(const std::vector<std::pair<int, int>>& path, int idx) {
        int x = path[idx].first;
        int y = path[idx].second;
        val = grid[x][y];
        type = '.';
        child = nullptr;
        if (idx > 0) {
            int px = path[idx - 1].first;
            int py = path[idx - 1].second;
            int prv = grid[px][py];
            if (prv == val) {
                type = '+';
            } else {
                type = '*';
            }
            child = new F(path, idx - 1);
        }
    }

    int eval(const std::vector<int>& abc) {
        int res = 0;
        if (type == '.') {
            res = abc[val];
        } else if (type == '+') {
            res = child->eval(abc) + abc[val];
        } else if (type == '*') {
            res = child->eval(abc) * abc[val];
        }
        return res;
    }

    ~F() {
        delete child;
    }
};

void find_paths(int x, int y, int end_x, int end_y,
                bool visited[N][N],
                std::vector<std::pair<int, int>>& path,
                std::vector<std::pair<std::vector<std::string>, F*>>& paths_a1f6,
                std::vector<std::pair<std::vector<std::string>, F*>>& paths_a6f1) {
    if (path.size() > MAX_LEN || (EXACT_LEN != 0 && path.size() > EXACT_LEN)) {
        return;
    }
    if (x == end_x && y == end_y) {
        if (EXACT_LEN != 0 && path.size() != EXACT_LEN) {
            return;
        }
        std::vector<std::string> path_ = stringify(path);
        F* path_f = new F(path, path.size() - 1);
        paths_a1f6.emplace_back(path_, path_f);

        std::vector<std::pair<int, int>> mirror_path = mirror(path);
        F* mirror_f = new F(mirror_path, mirror_path.size() - 1);
        std::vector<std::string> mirror_ = stringify(mirror_path);
        paths_a6f1.emplace_back(mirror_, mirror_f);
        return;
    }
    for (const auto& next : neighbors[x][y]) {
        int nx = next.first;
        int ny = next.second;
        if (!visited[nx][ny]) {
            visited[nx][ny] = true;
            path.emplace_back(nx, ny);
            find_paths(nx, ny, end_x, end_y, visited, path, paths_a1f6, paths_a6f1);
            path.pop_back();
            visited[nx][ny] = false;
        }
    }
}

int main() {
    precompute_neighbors();

    bool visited[N][N] = {false};
    visited[0][0] = true;
    std::vector<std::pair<int, int>> path = {{0, 0}};
    std::vector<std::pair<std::vector<std::string>, F*>> paths_a1f6;
    std::vector<std::pair<std::vector<std::string>, F*>> paths_a6f1;

    find_paths(0, 0, 5, 5, visited, path, paths_a1f6, paths_a6f1);

    std::vector<std::vector<int>> abcs;
    for (int A = 1; A <= 50; ++A) {
        for (int B = 1; B <= 50 - A; ++B) {
            if (A == B) continue;
            for (int C = 1; C <= 50 - A - B; ++C) {
                if (A == C || B == C) continue;
                abcs.push_back({A, B, C});
            }
        }
    }
    std::sort(abcs.begin(), abcs.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[0] + a[1] + a[2] < b[0] + b[1] + b[2];
    });

    for (const auto& abc : abcs) {
        bool ok = false;
        std::string cur;
        for (const auto& p : paths_a1f6) {
            if (p.second->eval(abc) == 2024) {
                ok = true;
                cur = std::to_string(abc[0]) + ',' + std::to_string(abc[1]) + ',' + std::to_string(abc[2]) + ',';
                for (const auto& s : p.first) {
                    cur += s + ',';
                }
                break;
            }
        }
        if (!ok) continue;
        ok = false;
        for (const auto& p : paths_a6f1) {
            if (p.second->eval(abc) == 2024) {
                ok = true;
                for (const auto& s : p.first) {
                    cur += s + ',';
                }
                cur.pop_back();
                break;
            }
        }
        if (ok) {
            std::cout << cur << std::endl;
            break;
        }
    }

    for (auto& p : paths_a1f6) {
        delete p.second;
    }
    for (auto& p : paths_a6f1) {
        delete p.second;
    }

    return 0;
}

/*
3,2,1,a1,b3,a5,c4,a3,b5,c3,d1,b2,d3,e1,c2,e3,d5,f6,a6,c5,d3,c1,a2,c3,d1,b2,c4,a3,c2,d4,f5,e3,f1
*/