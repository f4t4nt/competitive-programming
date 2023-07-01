#include <bits/stdc++.h>

using namespace std;

using ll = long long;
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

ll dist2(ll x1, ll y1, ll x2, ll y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1- y2);
}

bool ok(vector<vector<bool>> p) {
    vector<bool> rv(4);
    FOR (i, sz(p)) {
        FOR (j, 4) {
            rv[j] = rv[j] || p[i][j];
        }
    }
    return rv[0] && rv[1] && rv[2] && rv[3];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll l, w, n, r;
    cin >> l >> w >> n >> r;
    l *= 2, w *= 2, r *= 2;
    vector<vector<bool>> p(n);
    FOR (i, n) {
        ll x, y;
        cin >> x >> y;
        x *= 2, y *= 2;
        p[i] = {dist2(x, y, -l / 2, 0) <= r * r,
            dist2(x, y, l / 2, 0) <= r * r,
            dist2(x, y, 0, -w / 2) <= r * r,
            dist2(x, y, 0, w / 2) <= r * r,
        };
    }
    rsort(p);
    int rv = 5;
    FOR (i, sz(p)) {
        if (ok({p[i]})) {
            rv = min(rv, 1);
        }
        FOB (j, i + 1, sz(p)) {
            if (ok({p[i], p[j]})) {
                rv = min(rv, 2);
            }
            FOB (k, j + 1, sz(p)) {
                if (ok({p[i], p[j], p[k]})) {
                    rv = min(rv, 3);
                }
                FOB (l, k + 1, sz(p)) {
                    if (ok({p[i], p[j], p[k], p[l]})) {
                        rv = min(rv, 4);
                    }
                }
            }
        } 
    }
    if (rv == 5) {
        cout << "Impossible\n";
    } else {
        cout << rv << '\n';
    }

    return 0;
}