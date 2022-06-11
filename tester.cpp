#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int test_main();
istringstream fin;
ostringstream fout;
extern string test_file_name;

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

void print_result(ostream& cout, string& test_in, string& test_out, string& test_result, size_t& test_idx)
{
    if(test_result == test_out)
    { cout << "test " << test_idx + 1 << " passed\n"; }
    else
    { cout << "TEST " << test_idx + 1 << " FAILED\n" << "input:\n" << test_in << '\n' << "expected:\n" << test_out << endl << "received:\n" << test_result << '\n'; }
}

void run_test(ofstream& test_results, string& test_in, string& test_out, size_t test_idx)
{
    fin.clear();
    fout.clear();
    fin.str(test_in);
    fout.str("");
    test_main();

    auto test_result = fout.str();

    fin.clear();
    fin.str(test_result);
    test_result = read_block(fin);
    
    print_result(cout, test_in, test_out, test_result, test_idx);
    print_result(test_results, test_in, test_out, test_result, test_idx);
}

int main()
{
    ofstream test_results(test_file_name + ".out");
    
    auto tests = read_inputs();
    for(size_t test_idx = 0; test_idx < tests.size(); test_idx++)
    { run_test(test_results, tests[test_idx].first, tests[test_idx].second, test_idx); }
    
    return 0;
}