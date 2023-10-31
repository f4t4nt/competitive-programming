#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

bool is_distinct(int n) {
    vector<bool> digits(10);
    while (n) {
        if (digits[n % 10]) {
            return false;
        }
        digits[n % 10] = true;
        n /= 10;
    }
    return true;
}

void countNumbers(vector<vector<int>> arr) {
    vector<int> ref(1e6 + 1);
    for (int i = 1; i <= 1e6; i++) {
        ref[i] = ref[i - 1] + is_distinct(i);
    }
    for (auto &v : arr) {
        cout << ref[v[1]] - ref[v[0] - 1] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll q, n;
    cin >> q >> n;
    vector<vector<int>> arr(q, vector<int>(n));
    for (auto &v : arr) {
        for (auto &x : v) {
            cin >> x;
        }
    }
    countNumbers(arr);

    return 0;
}