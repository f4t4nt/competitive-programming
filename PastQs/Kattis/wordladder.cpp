#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

str total = "";
vector<str> all_str;

void gen_string(str prev, ll dir, ll depth, ll &idx) {
    if (idx == 0) {
        return;
    }
    if (depth == 3) {
        all_str.push_back(prev);
        idx -= 1;
        return;
    }
    if (dir == 1) {
        ll tmp = 1;
        FOR (i, 26) {
            gen_string(prev + total.substr(i, 1), tmp, depth + 1, idx);
            tmp *= -1;
        }
    } else {
        ll tmp = 1;
        FORR (i, 26) {
            gen_string(prev + total.substr(i, 1), tmp, depth + 1, idx);
            tmp *= -1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;

    FOR(i, 26) {
        total += (ch) ('a' + i);
    }

    all_str = vector<str>();

    ll idx = n;

    gen_string("", 1, 0, idx);

    if (n % 2 == 1) {
        cout << all_str[0] << all_str[0] << '\n';
    }

    FOR (i, n / 2) {
        cout << all_str[i] << all_str[i+1] << '\n';
        cout << all_str[i+1] << all_str[i+1] << '\n';
    }

    return 0;
}