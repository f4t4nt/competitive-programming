#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
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

int findMinimumEqualSum(vector<int> rowA, vector<int> rowB) {
    bool hasZeroA = false, hasZeroB = false;
    for (auto &x : rowA) {
        if (x == 0) {
            x = 1;
            hasZeroA = true;
        }
    }
    for (auto &x : rowB) {
        if (x == 0) {
            x = 1;
            hasZeroB = true;
        }
    }
    int sumA = accumulate(rowA.begin(), rowA.end(), 0),
        sumB = accumulate(rowB.begin(), rowB.end(), 0);
    if (sumA == sumB) {
        return sumA;
    }
    if (sumA < sumB) {
        if (hasZeroA) {
            return sumB;
        }
    }
    if (sumA > sumB) {
        if (hasZeroB) {
            return sumA;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n;
    vector<int> rowA(n);
    FOR (i, n) {
        cin >> rowA[i];
    }
    cin >> m;
    vector<int> rowB(m);
    FOR (i, m) {
        cin >> rowB[i];
    }
    cout << findMinimumEqualSum(rowA, rowB) << '\n';

    return 0;
}