#include <bits/stdc++.h>

using namespace std;

int test_main();
istringstream fin;
ostringstream fout;
extern string test_file_name;

bool RESULT_ONLY = false;
bool SHOW_DIFF = false;
const int DIFF_WIDTH = 30;

void trim(string& str)
{
    string whitespaces = " \t\n\r\f\v";
    str.erase(str.find_last_not_of(whitespaces) + 1);
    str.erase(0, str.find_first_not_of(whitespaces));
}

string read_block(basic_istream<char, char_traits<char>>& test_in)
{
    char ch;
    string block;
    while((ch = test_in.peek()) >= 0 && ch != '=')
    {
        string line;
        getline(test_in, line);
        trim(line);
        if (line.length() != 0)
        {
            if (block.length() != 0)
            { block += "\n"; }
            block += line;
        }
    }
    return block;
}

vector<pair<string, string>> read_inputs()
{
    ifstream test_in(test_file_name + ".in");
    auto str = read_block(test_in);
    string tmp;
    
    vector<pair<string, string>> tests;
    while(!test_in.eof())
    {
        getline(test_in, tmp);
        auto in = read_block(test_in);
        
        getline(test_in, tmp);
        auto out = read_block(test_in);
        tests.push_back({in, out});
    }
    
    return tests;
}

void line_diff(ostream& cout, const string& test_out, const string& test_result) {
    istringstream expected_stream(test_out);
    istringstream result_stream(test_result);

    string expected_line, result_line;
    int line_num = 1;
    
    cout << setw(8) << "Line #" << setw(DIFF_WIDTH) << "Expected" << setw(DIFF_WIDTH) << "Received" << endl;
    cout << string(DIFF_WIDTH * 2 + 8, '-') << endl;

    while (getline(expected_stream, expected_line) && getline(result_stream, result_line)) {
        if (expected_line != result_line) {
            cout << setw(8) << line_num 
                 << setw(DIFF_WIDTH) << expected_line 
                 << setw(DIFF_WIDTH) << result_line << endl;
        }
        line_num++;
    }

    while (getline(expected_stream, expected_line)) {
        cout << setw(8) << line_num 
             << setw(DIFF_WIDTH) << expected_line 
             << setw(DIFF_WIDTH) << "(missing)" << endl;
        line_num++;
    }
    while (getline(result_stream, result_line)) {
        cout << setw(8) << line_num 
             << setw(DIFF_WIDTH) << "(missing)" 
             << setw(DIFF_WIDTH) << result_line << endl;
        line_num++;
    }
}

void print_result(ostream& cout, string& test_in, string& test_out, string& test_result, size_t& test_idx, double diff)
{
    if (RESULT_ONLY) {
        cout << test_result << endl;
    } else {
        if(test_result == test_out)
        { cout << fixed << setprecision(6) <<
            "test " << test_idx + 1 << " passed; " << diff << "ms" << endl; }
        else if(SHOW_DIFF)
        { cout << fixed << setprecision(6) << 
            "TEST " << test_idx + 1 << " FAILED; " << diff << "ms" << endl;
            line_diff(cout, test_out, test_result); }
        else
        { cout << fixed << setprecision(6) <<
            "TEST " << test_idx + 1 << " FAILED; " << diff << "ms" << endl <<
            "input:\n" << test_in << endl <<
            "expected:\n" << test_out << endl <<
            "received:\n" << test_result << endl; }
    }
}

void run_test(ofstream& test_results, string& test_in, string& test_out, size_t test_idx)
{
    fin.clear();
    fout.clear();
    fin.str(test_in);
    fout.str("");
    auto start = chrono::steady_clock::now();
    test_main();
    auto end = chrono::steady_clock::now();
    double diff = chrono::duration<double, milli>(end - start).count();

    auto test_result = fout.str();

    fin.clear();
    fin.str(test_result);
    test_result = read_block(fin);
    
    print_result(cout, test_in, test_out, test_result, test_idx, diff);
    print_result(test_results, test_in, test_out, test_result, test_idx, diff);
}

int main()
{
    ofstream test_results(test_file_name + ".out");
    
    auto tests = read_inputs();
    for(size_t test_idx = 0; test_idx < tests.size(); test_idx++)
    { run_test(test_results, tests[test_idx].first, tests[test_idx].second, test_idx); }
    
    return 0;
}