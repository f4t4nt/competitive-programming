#include <vector>
// #include <bits/stdc++.h>
#include <map>

using namespace std;

/// @p runtimes The collection of movie runtimes. The same value may appear more than once, indicating that multiple
///   available movies have the same runtime.
/// @pre Each value in @p runtimes is positive (i.e. there are no movie whose runtime is 0).
/// @returns The length of the largets sequence of non-repeated movies that the group can watch, such that the Nth movie
///   in the sequence has the same runtime as, or is exactly one minute longer than, the (N-1)st movie. A return value of
///   0 indicates that it is not possible for the group to have a marathon at all.
int longestMarathon(const std::vector<int> &runtimes) {
    map<int, int> dp;
    for (auto &runtime : runtimes) {
        dp[runtime]++;
    }
    auto prev = dp.begin();
    auto it = next(prev);
    int rv = prev->second;
    while (it != dp.end()) {
        if (it->first == prev->first + 1) {
            dp[it->first] += dp[prev->first];
        }
        rv = max(rv, dp[it->first]);
        prev++;
        it++;
    }
    return rv;
}

#include <fstream>
#include <iostream>

int readInteger(bool wholeLine);


int main() {
    // read in test case
    std::vector<int> runtimes{};
    int numMovies = readInteger(true);
    for (int i = 0; i < numMovies; ++i) {
        runtimes.push_back(readInteger(true));
    }
    
    // execute function
    const int result = longestMarathon(runtimes);
    
    // write output to file
    constexpr auto PATH_ENV_VAR = "OUTPUT_PATH";
    const auto outputPath = getenv(PATH_ENV_VAR);
    std::ofstream outfile(outputPath);
    outfile << result << std::endl;
    
    // clean up
    outfile.close();
    
    // return
    return 0;
}


int readInteger(bool wholeLine) {
    int value{};
    std::cin >> value;
    if (wholeLine) { std::cin >> std::ws; }
    return value;
}