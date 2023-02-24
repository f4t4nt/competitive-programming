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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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

vector<ll> pow10_(19, 1);

ll score(vector<ll> r) {
    ll rv = 0;
    while (rv < sz(r) && r[rv] == rv) {
        rv++;
    }
    return rv;
}

vector<ll> multiply(vector<ll> &p, vector<ll> &q) {
    vector<ll> r(sz(p));
    FOR (i, sz(p)) {
        r[i] = q[p[i]];
    }
    return r;
}

bool has_key(vector<ll> &a, ll lo, ll hi) {
    ll l = 0, r = sz(a);
    while (l < r) {
        ll m = (l + r) / 2;
        if (a[m] < lo) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l < sz(a) && a[l] < hi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    FOR (i, 18) {
        pow10_[i + 1] = pow10_[i] * 10;
    }

    ll t;
    cin >> t;

    while (t--) {
        ll n, m;
        cin >> n >> m;
        vector<vector<ll>> a(n, vector<ll>(m));
        FOR (i, n) {
            FOR (j, m) {
                cin >> a[i][j];
                a[i][j]--;
            }
        }
        vector<ll> ref;
        FOR (i, n) {
            ll key = 0;
            FOR (j, m) {
                key += j * pow10_[m - a[i][j] - 1];
            }
            ref.pb(key);
        }
        ssort(ref);
        FOR (i, n) {
            // ll rv = 0;
            // FOR (j, n) {
            //     rv = max(rv, score(multiply(a[i], a[j])));
            // }
            // cout << rv << ' ';
            ll rv = 0, key = 0, curr10 = pow10_[m - 1];
            // FOR (j, m) {
            //     key += a[i][j] * pow10[m - j - 1];
            // }
            do {
                key += a[i][rv] * curr10;
                rv++;
            } while (rv < m && has_key(ref, key, (key / curr10 + 1) * curr10) && (curr10 /= 10));
            if (!has_key(ref, key, (key / curr10 + 1) * curr10)) {
                rv--;
            }
            cout << rv << ' ';
        }
        cout << '\n';
    }


    return 0;
}