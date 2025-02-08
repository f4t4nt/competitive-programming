#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
#include <array>
#include <fstream>

using namespace std;

// The initial grid
vector<vector<int>> sudoku = {
    {-1, -1, -1, -1, -1, -1, -1,  2, -1},
    {-1, -1, -1, -1,  2, -1, -1, -1,  5},
    {-1,  2, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1,  0, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1,  2, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1,  0, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1,  2, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1,  5, -1, -1},
};

// Function to get the box index from row and column
inline int get_box_index(int row, int col) {
    return (row / 3) * 3 + (col / 3);
}

// This function generates all 9-digit multiples of the GCD with unique digits, containing digits 0,2,5
vector<string> generate_candidate_numbers(int gcd) {
    vector<string> candidates;
    int start = 12345678 / gcd; // Ensure the product is at least 8 digits
    int end = 987654321 / gcd; // Ensure the product is at most 9 digits
    for (int mult = start; mult <= end; ++mult) {
        long long product = static_cast<long long>(gcd) * mult;
        string num_str = to_string(product);
        if (num_str.length() > 9) {
            break; // Exceeded 9 digits
        }
        // Pad with leading zeros if necessary
        num_str = string(9 - num_str.length(), '0') + num_str;
        // Check if the number has unique digits
        bitset<10> digits_in_num;
        bool unique_digits = true;
        for (char c : num_str) {
            int digit = c - '0';
            if (digits_in_num.test(digit)) {
                unique_digits = false;
                break;
            }
            digits_in_num.set(digit);
        }
        if (!unique_digits || digits_in_num.count() != 9) {
            continue;
        }
        // Check if number contains digits '0', '2', '5'
        if (!digits_in_num.test(0) || !digits_in_num.test(2) || !digits_in_num.test(5)) {
            continue;
        }
        candidates.push_back(num_str);
    }
    return candidates;
}

// Function to print the Sudoku grid and used numbers to an output stream
void print_sudoku(const vector<vector<int>>& grid, const vector<string>& used_numbers, ostream& os) {
    os << "Sudoku grid found:" << endl;
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            os << grid[r][c] << " ";
            if (c % 3 == 2 && c != 8) os << "| ";
        }
        os << endl;
        if (r % 3 == 2 && r != 8) {
            os << "------+-------+------" << endl;
        }
    }

    // Print a comma-separated list of the used numbers
    os << "Used numbers:" << endl;
    for (const string& num_str : used_numbers) {
        os << num_str << ", ";
    }
    os << endl;
}

// Check if the candidate numbers can be used to fill the Sudoku grid
bool fill_sudoku(vector<vector<int>>& grid, const vector<string>& candidate_numbers, int row_index,
                 array<bitset<10>, 9>& col_used, array<bitset<10>, 9>& box_used, int omitted_digit,
                 vector<string>& used_numbers, ostream& outfile) {
    if (row_index == 9) {
        // Successfully filled all rows
        // Print to console
        print_sudoku(grid, used_numbers, cout);
        // Also print to file
        print_sudoku(grid, used_numbers, outfile);
        return true;
    }
    // Try each candidate number as the current row
    for (const string& num_str : candidate_numbers) {
        // Skip if this number has been used already
        if (find(used_numbers.begin(), used_numbers.end(), num_str) != used_numbers.end()) {
            continue;
        }
        // Extract digits
        vector<int> digits_in_num(9);
        bool uses_omitted_digit = false;
        for (int i = 0; i < 9; ++i) {
            int val = num_str[i] - '0';
            digits_in_num[i] = val;
            if (val == omitted_digit) {
                uses_omitted_digit = true;
                break;
            }
        }
        if (uses_omitted_digit) {
            continue;
        }
        // Check for conflicts in the row with the initial grid
        bool conflict = false;
        for (int col = 0; col < 9; ++col) {
            if (sudoku[row_index][col] != -1 && sudoku[row_index][col] != digits_in_num[col]) {
                conflict = true;
                break;
            }
        }
        if (conflict) {
            continue;
        }
        // Check for conflicts in columns and boxes
        bool can_place = true;
        for (int col = 0; col < 9; ++col) {
            int val = digits_in_num[col];
            // Skip if the cell is already filled correctly
            if (sudoku[row_index][col] == val) {
                continue;
            }
            // Check columns and boxes
            if (col_used[col].test(val) || box_used[get_box_index(row_index, col)].test(val)) {
                can_place = false;
                break;
            }
        }
        if (!can_place) {
            continue;
        }
        // Place the number in the grid
        for (int col = 0; col < 9; ++col) {
            int val = digits_in_num[col];
            grid[row_index][col] = val;
            col_used[col].set(val);
            box_used[get_box_index(row_index, col)].set(val);
        }
        used_numbers.push_back(num_str);
        // Recurse to next row
        if (fill_sudoku(grid, candidate_numbers, row_index + 1, col_used, box_used, omitted_digit, used_numbers, outfile)) {
            return true; // Solution found
        }
        // Backtrack
        for (int col = 0; col < 9; ++col) {
            int val = digits_in_num[col];
            grid[row_index][col] = sudoku[row_index][col]; // Reset to initial grid value
            col_used[col].reset(val);
            box_used[get_box_index(row_index, col)].reset(val);
        }
        used_numbers.pop_back();
    }
    return false; // No solution found at this level
}

int main() {
    // Open file for output
    ofstream outfile("sudoku_solutions.txt");
    if (!outfile) {
        cerr << "Could not open file for writing." << endl;
        return 1;
    }

    for (int gcd = 12345679; gcd < 1000000000; ++gcd) {
        if (gcd % 2 == 0 || gcd % 5 == 0) {
            continue; // Skip GCDs divisible by 2 or 5
        }
        bool found_solution = false;
        // Generate candidate numbers
        vector<string> candidate_numbers = generate_candidate_numbers(gcd);
        if (candidate_numbers.empty()) {
            continue;
        }
        // Initialize the grid and used structures
        vector<vector<int>> grid = sudoku;
        array<bitset<10>, 9> col_used{}, box_used{};
        // Insert initial grid values into col_used and box_used
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (sudoku[i][j] != -1) {
                    int val = sudoku[i][j];
                    col_used[j].set(val);
                    box_used[get_box_index(i, j)].set(val);
                }
            }
        }
        // Try each candidate number as the first row number
        for (const string& first_row_num : candidate_numbers) {
            // Early conflict check for the first row number
            vector<int> digits_in_num(9);
            bool conflict = false;
            for (int i = 0; i < 9; ++i) {
                int val = first_row_num[i] - '0';
                digits_in_num[i] = val;
                // Check with initial grid
                if (sudoku[0][i] != -1 && sudoku[0][i] != val) {
                    conflict = true;
                    break;
                }
                // If the cell is already filled correctly, skip
                if (sudoku[0][i] == val) {
                    continue;
                }
                // Check columns and boxes
                if (col_used[i].test(val) || box_used[get_box_index(0, i)].test(val)) {
                    conflict = true;
                    break;
                }
            }
            if (conflict) {
                continue; // Can't use this number as the first row
            }
            // Get the digits used in the first row number
            bitset<10> digits_used;
            for (int val : digits_in_num) {
                digits_used.set(val);
            }
            // Ensure digits '0', '2', and '5' are included
            if (!digits_used.test(0) || !digits_used.test(2) || !digits_used.test(5)) {
                continue;
            }
            // Determine the omitted digit
            bitset<10> all_digits;
            all_digits.set(); // All bits set (digits 0-9)
            bitset<10> omitted_digits = all_digits ^ digits_used;
            if (omitted_digits.count() != 1) {
                continue; // Must omit exactly one digit
            }
            int omitted_digit = omitted_digits._Find_first();
            // Now filter candidate_numbers to only include numbers using the same digits
            vector<string> filtered_candidates;
            for (const string& num_str : candidate_numbers) {
                bitset<10> num_digits;
                bool uses_omitted_digit = false;
                for (char c : num_str) {
                    int d = c - '0';
                    if (d == omitted_digit) {
                        uses_omitted_digit = true;
                        break;
                    }
                    num_digits.set(d);
                }
                if (uses_omitted_digit || num_digits.count() != 9) {
                    continue; // Can't use numbers with the omitted digit
                }
                filtered_candidates.push_back(num_str);
            }
            if (filtered_candidates.size() < 9) {
                continue; // Not enough candidates
            }
            // Place the first row number
            for (int i = 0; i < 9; ++i) {
                int val = digits_in_num[i];
                grid[0][i] = val;
                col_used[i].set(val);
                box_used[get_box_index(0, i)].set(val);
            }
            vector<string> used_numbers = {first_row_num};
            // Try to fill the rest of the grid
            if (fill_sudoku(grid, filtered_candidates, 1, col_used, box_used, omitted_digit, used_numbers, outfile)) {
                // Solution found and printed inside fill_sudoku
                cout << "Omitted Digit: " << omitted_digit << endl;
                cout << "GCD: " << gcd << endl;
                outfile << "Omitted Digit: " << omitted_digit << endl;
                outfile << "GCD: " << gcd << endl;
                found_solution = true;
                
                break; // Move to the next GCD
            }
            // Backtrack: remove the first row values from col_used and box_used
            for (int i = 0; i < 9; ++i) {
                int val = digits_in_num[i];
                col_used[i].reset(val);
                box_used[get_box_index(0, i)].reset(val);
                // Reset grid to initial state
                grid[0][i] = sudoku[0][i];
            }
        }
        if (!found_solution) {
            cout << "No solution found for GCD: " << gcd << endl;
        }
    }
    return 0;
}

/*
Sudoku grid found:
0 1 3 | 4 5 7 | 8 2 6 
4 6 8 | 1 2 3 | 7 0 5 
5 2 7 | 0 6 8 | 1 3 4 
------+-------+------
1 7 0 | 5 8 6 | 2 4 3 
2 4 6 | 3 7 1 | 0 5 8 
3 8 5 | 2 4 0 | 6 1 7 
------+-------+------
7 3 2 | 8 0 5 | 4 6 1 
8 5 4 | 6 1 2 | 3 7 0 
6 0 1 | 7 3 4 | 5 8 2 
Used numbers:
013457826, 468123705, 527068134, 170586243, 246371058, 385240617, 732805461, 854612370, 601734582, 
Omitted Digit: 9
GCD: 81

Sudoku grid found:
3 9 5 | 0 6 1 | 7 2 8 
0 6 1 | 7 2 8 | 3 9 5 
7 2 8 | 3 9 5 | 0 6 1 
------+-------+------
9 5 0 | 6 1 7 | 2 8 3 
2 8 3 | 9 5 0 | 6 1 7 
6 1 7 | 2 8 3 | 9 5 0 
------+-------+------
8 3 9 | 5 0 6 | 1 7 2 
5 0 6 | 1 7 2 | 8 3 9 
1 7 2 | 8 3 9 | 5 0 6 
Used numbers:
395061728, 061728395, 728395061, 950617283, 283950617, 617283950, 839506172, 506172839, 172839506, 
Omitted Digit: 4
GCD: 12345679
*/