#include <bits/stdc++.h>

const int bounds = 9;
const int side_length = 9;

std::map<std::pair<int, int>, int> posts = {
    {{-9, 3}, 1}, {{-2, 2}, 8}, {{-4, 8}, 7}, {{0, 6}, 3}, {{1, 1}, 4},
    {{3, 4}, 6}, {{5, 0}, 3}, {{9, -3}, 11}, {{2, -2}, 6}, {{4, -8}, 6},
    {{0, -6}, 19}, {{-1, -1}, 38}, {{-3, -4}, 6}, {{-5, 0}, 6}
};

std::map<std::pair<int, int>, std::vector<int>> max_lens;

const std::vector<std::pair<int, int>> directions = {
    {1, 0}, {0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}
};

bool out_of_bounds(int q, int r) {
    return (std::abs(q) > bounds || std::abs(r) > bounds || (std::abs(q + r) > bounds && q * r > 0));
}

class Hexagon {
public:
    int q, r;
    int side_length;
    int post;
    std::vector<std::pair<int, int>> neighbors;
    std::string color;

    Hexagon() = default;

    Hexagon(int q, int r, int side_length) : q(q), r(r), side_length(side_length) {
        post = posts.count({q, r}) ? posts[{q, r}] : 0;
        calculate_neighbors();
        color = get_color();
    }

private:
    void calculate_neighbors() {
        for (const auto& [dq, dr] : directions) {
            int nq = q + dq, nr = r + dr;
            if (!out_of_bounds(nq, nr)) {
                neighbors.push_back({nq, nr});
            }
        }
    }

    std::string get_color() {
        if (out_of_bounds(q, r)) return "black";
        if (q == 0 && r == 0) return "white";
        if (q < 0 && r > 0 && q + r <= 0) return "blue";
        if (q > 0 && r >= 0) return "yellow";
        if (q > 0 && r < 0 && q + r >= 0) return "orange";
        if (q >= 0 && r < 0 && q + r < 0) return "red";
        if (q < 0 && r <= 0) return "purple";
        if (q <= 0 && r >= 0 && q + r > 0) return "green";
        throw std::runtime_error("Invalid coordinates");
    }
};

class HexGrid {
public:
    int side_length;
    std::map<std::pair<int, int>, Hexagon> hexagons;
    std::set<std::pair<int, int>> occupied;

    HexGrid(int side_length) : side_length(side_length) {
        create_grid();
        get_max_lens();
    }

    bool check_fences(const std::map<std::pair<int, int>, std::vector<int>>& fences, bool raise_err = false, bool ret_early = true) {
        bool res = true;
        occupied.clear();

        for (const auto& [coords, lens] : fences) {
            auto [q, r] = coords;

            if (lens.size() != 6) {
                if (raise_err) throw std::runtime_error("Invalid number of fences");
                if (ret_early) return false;
                res = false;
            }

            if (std::accumulate(lens.begin(), lens.end(), 0) != posts[coords]) {
                if (raise_err) throw std::runtime_error("Sum of fences does not match post value");
                if (ret_early) return false;
                res = false;
            }

            for (int i = 0; i < 6; ++i) {
                int nq = q + directions[i].first;
                int nr = r + directions[i].second;
                for (int _ = 0; _ < lens[i]; ++_) {
                    if (out_of_bounds(nq, nr) || occupied.count({nq, nr})) {
                        if (ret_early) return false;
                        res = false;
                    }
                    occupied.insert({nq, nr});
                    nq += directions[i].first;
                    nr += directions[i].second;
                }
            }
        }

        return res;
    }

    bool check_connection(const std::map<std::pair<int, int>, std::vector<int>>& fences) {
        int total_sum = 0;
        for (const auto& [coords, lens] : fences) {
            total_sum += std::accumulate(lens.begin(), lens.end(), 0);
        }
        if (total_sum < 42) return true;
        
        std::set<std::pair<int, int>> occupied;
        for (const auto& [coords, lens] : fences) {
            auto [q, r] = coords;
            for (int i = 0; i < 6; ++i) {
                int nq = q + directions[i].first;
                int nr = r + directions[i].second;
                for (int _ = 0; _ < lens[i]; ++_) {
                    occupied.insert({nq, nr});
                    nq += directions[i].first;
                    nr += directions[i].second;
                }
            }
        }

        std::set<std::pair<int, int>> visited = occupied;
        for (const auto& [coords, hexagon] : hexagons) {
            auto [q, r] = coords;
            if (visited.count({q, r})) continue;
            if (hexagon.color == "black") continue;

            std::set<std::string> color_set;
            std::queue<std::pair<int, int>> queue;
            queue.push({q, r});

            while (!queue.empty()) {
                auto [curr_q, curr_r] = queue.front();
                queue.pop();
                visited.insert({curr_q, curr_r});
                color_set.insert(hexagons[{curr_q, curr_r}].color);

                for (const auto& [nq, nr] : hexagons[{curr_q, curr_r}].neighbors) {
                    if (visited.count({nq, nr}) == 0 && hexagons[{nq, nr}].color != "black") {
                        queue.push({nq, nr});
                    }
                }

                if (color_set.size() == 6) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    void create_grid() {
        for (int q = -side_length; q <= side_length; ++q) {
            for (int r = std::max(-side_length, -q - side_length); r <= std::min(side_length, -q + side_length); ++r) {
                hexagons[{q, r}] = Hexagon(q, r, side_length);
            }
        }
    }

    void get_max_lens() {
        for (const auto& [coords, post] : posts) {
            auto [q, r] = coords;
            max_lens[coords] = std::vector<int>(6);
            for (int i = 0; i < 6; ++i) {
                int nq = q + directions[i].first;
                int nr = r + directions[i].second;
                int length = 0;
                while (!out_of_bounds(nq, nr) && !posts.count({nq, nr}) && length < post) {
                    // to check if answer is troll
                    // bool ok = true;
                    // for (auto [dq, dr] : directions) {
                    //     if (nq == dq && nr == dr) {
                    //         ok = false;
                    //         break;
                    //     }
                    // }
                    // if (!ok) break;
                    ++length;
                    nq += directions[i].first;
                    nr += directions[i].second;
                }
                max_lens[coords][i] = length;
            }
        }
    }
};

std::vector<std::map<std::pair<int, int>, std::vector<int>>> results;

std::vector<std::vector<int>> generate_valid_fences(int target_sum, const std::vector<int>& max_lengths) {
    std::vector<std::vector<int>> valid_fences;
    std::vector<int> fence_config(6);

    std::function<void(int, int)> backtrack = [&](int index, int current_sum) {
        if (index == 6) {
            if (current_sum == target_sum) {
                valid_fences.push_back(fence_config);
            }
            return;
        }

        for (int i = 0; i <= max_lengths[index] && current_sum + i <= target_sum; ++i) {
            fence_config[index] = i;
            backtrack(index + 1, current_sum + i);
        }
    };

    backtrack(0, 0);
    return valid_fences;
}

void solve_fences(HexGrid& hex_grid) {
    std::cout << "Starting solve_fences function..." << std::endl;

    std::map<std::pair<int, int>, std::vector<std::vector<int>>> all_valid_fences;
    for (const auto& [post, value] : posts) {
        all_valid_fences[post] = generate_valid_fences(value, max_lens[post]);
    }
    std::cout << "Generated all valid fences for each post." << std::endl;

    std::map<std::pair<int, int>, std::map<std::vector<int>, std::map<std::pair<int, int>, std::set<std::vector<int>>>>> bad_pairs;
    int total_comparisons = 0;
    int invalid_configurations = 0;

    std::cout << "Starting to generate bad pairs..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();

    for (const auto& [post0, fence_configs0] : all_valid_fences) {
        for (const auto& fence_config0 : fence_configs0) {
            for (const auto& [post1, fence_configs1] : all_valid_fences) {
                if (std::tie(post1.first, post1.second) <= std::tie(post0.first, post0.second)) continue;
                for (const auto& fence_config1 : fence_configs1) {
                    std::map<std::pair<int, int>, std::vector<int>> tmp_fences = {{post0, fence_config0}, {post1, fence_config1}};
                    total_comparisons++;
                    if (!hex_grid.check_fences(tmp_fences, false, false)) {
                        bad_pairs[post0][fence_config0][post1].insert(fence_config1);
                        bad_pairs[post1][fence_config1][post0].insert(fence_config0);
                        invalid_configurations++;
                    }
                }
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Finished generating bad pairs." << std::endl;
    std::cout << "Total comparisons: " << total_comparisons << std::endl;
    std::cout << "Invalid configurations: " << invalid_configurations << std::endl;
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    std::function<void(int, std::map<std::pair<int, int>, std::vector<int>>&, std::map<std::pair<int, int>, std::vector<std::vector<int>>>&)> backtrack = 
    [&](int index, std::map<std::pair<int, int>, std::vector<int>>& fences, std::map<std::pair<int, int>, std::vector<std::vector<int>>>& valid_fences) {
        // if (!hex_grid.check_connection(fences)) return;

        if (index == posts.size()) {
            results.push_back(fences);
            std::cout << "Found valid configuration. Total valid configurations: " << results.size() << std::endl;

            if (1) {
                std::ofstream outfile("fences2.txt");
                for (const auto& result : results) {
                    outfile << "Configuration:\n";
                    for (const auto& [coords, fences] : result) {
                        outfile << "(" << coords.first << ", " << coords.second << "): [";
                        for (int i = 0; i < 6; ++i) {
                            outfile << fences[i];
                            if (i < 5) outfile << ", ";
                        }
                        outfile << "]\n";
                    }
                    outfile << "\n";
                }
            }

            // if (rand() % 10000 == 0) {
            //     for (const auto& [coords, fences] : fences) {
            //         std::cout << "(" << coords.first << ", " << coords.second << "): [";
            //         for (int i = 0; i < 6; ++i) {
            //             std::cout << fences[i];
            //             if (i < 5) std::cout << ", ";
            //         }
            //         std::cout << "]," << std::endl;
            //     }
            //     std::cout << std::endl;
            //     std::cin.get();
            // }
            return;
        }

        auto min_post = std::min_element(valid_fences.begin(), valid_fences.end(),
            [](const auto& a, const auto& b) { return a.second.size() < b.second.size(); })->first;

        for (const auto& fence_config : valid_fences[min_post]) {
            fences[min_post] = fence_config;
            auto new_valid_fences = valid_fences;
            new_valid_fences.erase(min_post);

            for (auto& pair : new_valid_fences) {
                const auto& post = pair.first;
                auto& configs = pair.second;
                configs.erase(std::remove_if(configs.begin(), configs.end(),
                    [&](const auto& config) { 
                        return bad_pairs[min_post][fence_config][post].count(config); 
                    }),
                    configs.end());
            }

            backtrack(index + 1, fences, new_valid_fences);
            fences.erase(min_post);
        }
    };

    std::cout << "Starting backtracking..." << std::endl;
    start_time = std::chrono::high_resolution_clock::now();

    std::map<std::pair<int, int>, std::vector<int>> fences;
    backtrack(0, fences, all_valid_fences);

    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Finished backtracking." << std::endl;
    std::cout << "Time taken for backtracking: " << duration.count() << " milliseconds" << std::endl;
}

int main() {
    std::cout << "Creating HexGrid..." << std::endl;
    HexGrid hex_grid(side_length);
    std::cout << "HexGrid created." << std::endl;

    std::cout << "Starting solve_fences..." << std::endl;
    solve_fences(hex_grid);
    std::cout << "solve_fences completed." << std::endl;

    std::cout << "Found " << results.size() << " valid fence configurations." << std::endl;

    /*
    std::cout << "Writing results to file..." << std::endl;
    std::ofstream outfile("fences2.txt");
    for (const auto& result : results) {
        outfile << "Configuration:\n";
        for (const auto& [coords, fences] : result) {
            outfile << "(" << coords.first << ", " << coords.second << "): [";
            for (int i = 0; i < 6; ++i) {
                outfile << fences[i];
                if (i < 5) outfile << ", ";
            }
            outfile << "]\n";
        }
        outfile << "\n";
    }
    outfile.close();
    std::cout << "Results written to fences2.txt" << std::endl;
    */

    return 0;
}