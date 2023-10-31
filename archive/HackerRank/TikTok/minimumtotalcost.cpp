#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'minimumTotalCost' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY price as parameter.
 */

int minimumTotalCost(vector<int> price) {
    // cerr << price.size() << '\n';
    // for (int p : price) {
    //     cerr << p << '\n';
    // }
    int n = price.size(), rv = 0;
    for (int i = 1; i < n; i++) {
        rv += abs(price[i] - price[i - 1]);
    }
    vector<int> tmp(n);
    tmp[0] = rv - abs(price[0] - price[1]) + abs(price[0] / 2 - price[1]);
    tmp[n - 1] = rv - abs(price[n - 1] - price[n - 2]) + abs(price[n - 1] / 2 - price[n - 2]);
    for (int i = 1; i < n - 1; i++) {
        tmp[i] = rv - abs(price[i] - price[i - 1]) + abs(price[i] / 2 - price[i - 1]) - abs(price[i] - price[i + 1]) + abs(price[i] / 2 - price[i + 1]);
    }
    cerr << rv << '\n';
    for (int t : tmp) {
        cerr << t << '\n';
        rv = min(rv, t);
    }
    return rv;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string price_count_temp;
    getline(cin, price_count_temp);

    int price_count = stoi(ltrim(rtrim(price_count_temp)));

    vector<int> price(price_count);

    for (int i = 0; i < price_count; i++) {
        string price_item_temp;
        getline(cin, price_item_temp);

        int price_item = stoi(ltrim(rtrim(price_item_temp)));

        price[i] = price_item;
    }

    int result = minimumTotalCost(price);

    fout << result << "\n";

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
