#include <vector>
using namespace std;

/// @param budget The maximum amount of money that Shira is willing to spend on the tour.
/// @param landmarks The price point of each landmark on the tour, in the order that the tour will visit them.
/// @pre @p budget > 0
/// @pre @p landmarks is not empty, and each element is > 0
/// @returns The largest amount of @p budget that Shira can spend by getting on the tour at some stop j >= 0 and exiting
///   the tour at some subsequent stop k >= j.  A return value of 0 indicates that the budget is too low for any of the
///   planned stops.
int planSightseeingTour(int budget, const std::vector<int> &landmarks) {
    int idx = 0, jdx = 0, cur = 0, rv = 0;
    while (idx < landmarks.size()) {
        while (jdx < landmarks.size() && cur + landmarks[jdx] <= budget) {
            cur += landmarks[jdx];
            jdx++;
        }
        rv = max(rv, cur);
        cur -= landmarks[idx];
        idx++;
    }
    return rv;
}

#include <fstream>
#include <iostream>

int readInteger(bool wholeLine);


int main()
{
    // read in test case
    const int budget = readInteger(true);
    std::vector<int> landmarks{};
    const int numStops = readInteger(true);
    for (int i = 0; i < numStops; ++i) {
        landmarks.push_back(readInteger(true));
    }
    
    // execute function
    const auto result = planSightseeingTour(budget, landmarks);
    
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