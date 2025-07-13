#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<str> g(n);
    for (str &row : g) cin >> row;

    vector<str> ans(n, str(m, '?'));

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            bool forbidden[256] = {};
            forbidden[g[i][j]] = true;
            if (i) forbidden[ans[i - 1][j]] = true;
            if (j) forbidden[ans[i][j - 1]] = true;

            for (ch c : {'A', 'B', 'C', 'D'})
                if (!forbidden[c]) {
                    ans[i][j] = c;
                    break;
                }
        }
    }

    for (str &row : ans) cout << row << '\n';

    return 0;
}
