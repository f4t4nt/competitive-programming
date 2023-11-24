#include <array>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

/// Calculates the probability of two independent events both occuring.
/// @param a The probability that the first event occurs.
/// @param b The probability that the second event occurs.
/// @pre a >= 0
/// @pre b >= 0
/// @returns The probability that two independent events with probabilities @p a and @p b both occur. Mathematically,
///   this is exactly a * b.
double probabilityAnd(double a, double b) noexcept;

/// Calculates the probability of at least one of two independent events occuring.
/// @param a The probability that the first event occurs.
/// @param b The probability that the second event occurs.
/// @pre a >= 0
/// @pre b >= 0
/// @returns The probability that at least one of two independent events with probabilities @p a and @p b occurs.
///   Mathematically, this is exactly a + b.
double probabilityOr(double a, double b) noexcept;


/// @param pointsNeeded The exact number of points Mikaela needs to win the championship.
/// @param castings The number of attempts Mikaela can make to catch a fish and earn points.
/// @param lures The number of different fishing lures available.
/// @param probabilities The probability distribution for each of the fishing lures: probabilities[i][j] is the
///   probability of earning exactly j points on a casting made with fishing lure #i.
/// @pre pointsNeeded >= 1
/// @pre castings >= 1
/// @pre the sum of probabilities for each entry in @p probabilities is 1.0
/// @pre probabilities[x][y] >= 0 for all valid x and all y in [0, 5]
/// @returns The probability that Mikaela earns *exactly* @p pointsNeeded on a limited number of casting attempts with
///   her fishing lures, given @p probabilities.  A return value of 0.0 indicates that it is not possible to accumulate
///   the exact requisite number of points.  Do not round or truncate your answer at all.
double championshipProbability(int pointsNeeded, int castings, const std::vector<std::array<double, 6>> &probabilities) {
    vector<vector<double>> dp(pointsNeeded + 1, vector<double>(castings + 1, 0.0));
    dp[0][0] = 1;
    for (int c = 1; c <= castings; c++) {
        for (int p = 0; p <= pointsNeeded; p++) {
            dp[p][c] = dp[p][c - 1];
            for (int l = 0; l < probabilities.size(); l++) {
                double cur = 0;
                for (int i = 0; i < 6; i++) {
                    if (p - i < 0) break;
                    cur += dp[p - i][c - 1] * probabilities[l][i];
                }
                dp[p][c] = max(dp[p][c], cur);
            }
        }
    }
    return dp[pointsNeeded][castings];
}

#include <fstream>
#include <iomanip>
#include <iostream>

int readInteger(bool wholeLine);

double readDouble(bool wholeLine);

int main()
{
    // read in test case
    const int pointsTarget = readInteger(true);
    const int castings = readInteger(true);
    const int lures = readInteger(true);
    std::vector<std::array<double, 6>> probs{};
    for (int i = 0; i < lures; ++i) {
        probs.push_back({});
        probs.back()[0] = readDouble(false);
        probs.back()[1] = readDouble(false);
        probs.back()[2] = readDouble(false);
        probs.back()[3] = readDouble(false);
        probs.back()[4] = readDouble(false);
        probs.back()[5] = readDouble(true);
    }
    
    // execute function
    const auto result = championshipProbability(pointsTarget, castings, probs);
    
    // write output to file
    constexpr auto PATH_ENV_VAR = "OUTPUT_PATH";
    const auto outputPath = getenv(PATH_ENV_VAR);
    std::ofstream outfile(outputPath);
    outfile << std::setprecision(4) << result << std::endl;
    
    // clean up
    outfile.close();
    
    // return
    return 0;
}


double probabilityAnd(double a, double b) noexcept {
    return a * b;
}

double probabilityOr(double a, double b) noexcept {
    return a + b;
}

int readInteger(bool wholeLine) {
    int value{};
    std::cin >> value;
    if (wholeLine) { std::cin >> std::ws; }
    return value;
}

double readDouble(bool wholeLine) {
    double value{};
    std::cin >> value;
    if (wholeLine) { std::cin >> std::ws; }
    return value;
}