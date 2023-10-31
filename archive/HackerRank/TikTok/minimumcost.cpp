#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'minimumCost' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY data
 *  2. LONG_INTEGER k
 */

int minimumCost(vector<int> data, long k) {
    // cerr << data.size() << '\n';
    // for (int d : data) {
    //     cerr << d << '\n';
    // }
    // cerr << k << '\n';
    
    int n = data.size() / 2;
    sort(data.begin(), data.end());
    long cur = 0;
    for (int i = n; i < 2 * n; i++) {
        cur += data[i];
    }
    if (cur < k) {
        return -1;
    }
    int rv = n, tmp = n - 1, i = n - 1, j = n;
    vector<long> sum(2);
    while (i >= 0) {
        sum[i % 2] += data[i];
        sum[j % 2] += data[j];
        cur -= data[j];
        cerr << cur << '+' << sum[i % 2] << '=' << cur + sum[i % 2] << '\n';
        if (cur + sum[i % 2] >= k) {
            rv = tmp;
        }
        i--, j++, tmp--;
    }
    return rv;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string data_count_temp;
    getline(cin, data_count_temp);

    int data_count = stoi(ltrim(rtrim(data_count_temp)));

    vector<int> data(data_count);

    for (int i = 0; i < data_count; i++) {
        string data_item_temp;
        getline(cin, data_item_temp);

        int data_item = stoi(ltrim(rtrim(data_item_temp)));

        data[i] = data_item;
    }

    string k_temp;
    getline(cin, k_temp);

    long k = stol(ltrim(rtrim(k_temp)));

    int result = minimumCost(data, k);

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
