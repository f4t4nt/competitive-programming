#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'matchStrings' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY text
 *  2. STRING_ARRAY pat
 */

bool is_match(string &text, string &pat) {
    if (text.size() < pat.size() - 1) return false;
    bool ok = true;
    int lo = 0, hi = 1;
    while (pat[lo] != '*') {
        ok &= text[lo] == pat[lo];
        lo++;
    }
    while (pat[(int) pat.size() - hi] != '*') {
        ok &= text[(int) text.size() - hi] == pat[(int) pat.size() - hi];
        hi++;
    }
    return ok;
}

vector<string> matchStrings(vector<string> text, vector<string> pat) {
    vector<string> rv;
    for (int i = 0; i < (int) text.size(); i++) {
        if (is_match(text[i], pat[i])) {
            rv.push_back("YES");
        } else {
            rv.push_back("NO");
        }
    }
    return rv;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string text_count_temp;
    getline(cin, text_count_temp);

    int text_count = stoi(ltrim(rtrim(text_count_temp)));

    vector<string> text(text_count);

    for (int i = 0; i < text_count; i++) {
        string text_item;
        getline(cin, text_item);

        text[i] = text_item;
    }

    string pat_count_temp;
    getline(cin, pat_count_temp);

    int pat_count = stoi(ltrim(rtrim(pat_count_temp)));

    vector<string> pat(pat_count);

    for (int i = 0; i < pat_count; i++) {
        string pat_item;
        getline(cin, pat_item);

        pat[i] = pat_item;
    }

    vector<string> result = matchStrings(text, pat);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}