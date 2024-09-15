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

long getMaximumPower(vector<int> power) {
    map<long, long> m;
    for (auto p : power) {
        m[p] += p;
    }
    int n = m.size();
    vector<long> dp(n);
    dp[0] = m.begin()->second;
    auto prev2 = m.begin();
    auto prev = m.begin();
    auto curr = ++m.begin();
    for (int i = 1; i < n; i++) {
        if (curr->first - prev->first == 1) {
            if (i - 2 >= 0) {
                dp[i] = max(dp[i - 2] + curr->second, dp[i - 1]);
            } else {
                dp[i] = max(curr->second, dp[i - 1]);
            }
        } else {
            dp[i] = dp[i - 1] + curr->second;
        }
        prev2 = prev;
        prev = curr;
        curr++;
    }
    return dp[n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> power(n);
    FOR (i, n) {
        cin >> power[i];
    }
    cout << getMaximumPower(power) << '\n';

    return 0;
}