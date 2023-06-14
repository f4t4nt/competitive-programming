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

constexpr ll MOD = 998244353;
map<ch, ll> ch_to_i = {{'C', 0}, {'I', 1}, {'P', 2}};
ch i_to_ch[3] = {'C', 'I', 'P'};

ll pow_(ll x, ll p) {
    ll rv = 1;
    while (p) {
        if(p & 1) rv = (rv * x) % MOD;
        x = (x * x) % MOD;
        p >>= 1;
    }
    return rv;
}

bool is_valid(vector<ch> &row, ll hash) {
    FORR (i, sz(row)) {
        if (row[i] != '?' &&
            ch_to_i[row[i]] != (hash % 3)) {
            return false;
        }
        hash /= 3;
    }
    return true;
}

str i_to_hash(ll &m, ll hash) {
    str rv;
    FORR (i, m) {
        rv += i_to_ch[hash % 3];
        hash /= 3;
    }
    flip(rv);
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m, total_empty = 0;
    cin >> n >> m;
    vector<vector<ch>> grid(n, vector<ch>(m));
    FOR (i, n) {
        FOR (j, m) {
            cin >> grid[i][j];
            if (grid[i][j] == '?') {
                total_empty++;
            }
        }
    }

    ll rv = pow_(3, total_empty);

    ll row_pow = pow_(3, m);
    vector<vector<ll>> edges(row_pow);
    FOR (i, row_pow) {
        set<ll> divs;
        ll tmp = i, div = 1;
        while (tmp > 0) {
            if (tmp % 9 == 6) {
                divs.insert(div);
            }
            tmp /= 3;
            div *= 3;
        }
        if (divs.empty()) {
            continue;
        }
        FOR (j, row_pow) {
            FORE (div, divs) {
                if ((j / div) % 9 == 3) {
                    edges[i].pb(j);
                    break;
                }
            }
        }
    }
    
    ll sum = 0;
    vector<ll> dp0(row_pow);
    FOR (i, row_pow) {
        if (is_valid(grid[0], i)) {
            dp0[i] = 1;
            sum++;
        }
    }

    FOB (i, 1, n) {
        vector<ll> dp1(row_pow);
        FOR (j, row_pow) {
            if (is_valid(grid[i], j)) {
                dp1[j] = sum;
                FORE (k, edges[j]) {
                    is_valid(grid[i], j);
                    dp1[j] = (dp1[j] - dp0[k] + MOD) % MOD;
                }
            }
        }
        dp0 = dp1;
        sum = 0;
        FORE (x, dp0) {
            sum = (sum + x) % MOD;
        }
    }

    ll tv = 0;
    FORE (x, dp0) {
        tv = (tv + x) % MOD;
    }
    rv = (rv - tv + MOD) % MOD;
    cout << rv << '\n';

    return 0;
}