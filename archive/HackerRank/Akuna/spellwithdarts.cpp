#include <array>
#include <string>
#include <vector>

/// A definition of a two-dimensional Cartesian coordinate.
/// @member x The x-coordinate of the Point.
/// @member y The y-coordinate of the Point.
struct Point { int x; int y; };

/// Calculates the Cartesian distance between two points, using classical geometry.
/// @param a The first point.
/// @param b The second point.
/// @returns The straight-line distance between the two points, guaranteed to be non-negative. The order of the points is
///   irrelevant; that is, distance(i, j) == distance(j, i) for all pairs of points (i, j).  A return value of 0
///   indicates that the two points have the same x- and y-coordinates.
double distance(Point a, Point b) noexcept;


/// @param board The center points of each fo the squares on the dartboard, in letter order (that is: board[0] is the
///   center point of the square labeled 'A' and board[25] is the center point of the square labeled 'Z').
/// @param throws The ordered sequence of impact locations for each of the dart throws.
/// @pre Each point in @p board has a different (x,y)-coordinate combination.
/// @pre @p throws is not empty.
/// @returns The string "score" obtained from the sequence of @throws against @board.  The string should consist only of
///   capital letters A-Z and asterisks.
std::string spellWithDarts(const std::array<Point, 26> &board, const std::vector<Point> &throws) {
    std::string rv = "";
    for (auto &thrw : throws) {
        double min_dist = -1;
        char ch = '.';
        for (int i = 0; i < 26; i++) {
            double cur_dist = distance(thrw, board[i]);
            if (min_dist == -1 || min_dist > cur_dist) {
                min_dist = cur_dist;
                ch = 'A' + i;
            } else if (min_dist == cur_dist) {
                ch = '*';
            }
        }
        rv += ch;
    }
    return rv;
}

#include <cmath>
#include <fstream>
#include <iostream>

int readInteger(bool wholeLine);

int main() {
    // read in test case
    constexpr int NUM_LETTERS = 26;
    std::array<Point, NUM_LETTERS> board{};
    for (int i = 0; i < NUM_LETTERS; ++i) {
        int x = readInteger(false);
        int y = readInteger(true);
        board[i] = Point{ x, y };
    }
    std::vector<Point> throws{};
    int numThrows = readInteger(true);
    for (int i = 0; i < numThrows; ++i) {
        int x = readInteger(false);
        int y = readInteger(true);
        throws.push_back({ x, y });
    }
    
    // execute function
    const std::string result = spellWithDarts(board, throws);
    
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


double distance(Point a, Point b) noexcept {
    double x1 = a.x;
    double y1 = a.y;
    double x2 = b.x;
    double y2 = b.y;
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

int readInteger(bool wholeLine) {
    int value{};
    std::cin >> value;
    if (wholeLine) { std::cin >> std::ws; }
    return value;
}