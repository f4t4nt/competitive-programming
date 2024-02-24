#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) sort(all(C))

#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll refx[] = {1, 0, 1, 1};
ll refy[] = {0, 1, 1, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<vector<ll>> queens(n);
        FOR (i, n) {
            ll x, y; cin >> x >> y;
            queens[i] = {x, y, x + y, x - y};
        }
        // FOR (_, 850) {
        //     ll dir = rng() % 4, djr = rng() % 4;
        //     do {
        //         djr = rng() % 4;
        //     } while (dir == djr);
        //     ll i = rng() % sz(condensed[dir]),
        //         j = rng() % sz(condensed[djr]);
        //     ll a = refx[dir], b = refy[dir],
        //         c = refx[djr], d = refy[djr];
        //     ll det = a * d - b * c;
        //     ll &val1 = condensed[dir][i], &val2 = condensed[djr][j];
        //     ll numx = d * val1 - b * val2, numy = -c * val1 + a * val2;
        //     if (numx % det != 0 || numy % det != 0) {
        //         _--;
        //         continue;
        //     }
        //     numx /= det;
        //     numy /= det;
        //     vector<ll> vals = {numx, numy, numx + numy, numx - numy};
        //     bool cur_pt = true;
        //     FOR (ai, n) {
        //         bool cur_q = false;
        //         FOR (aj, 4) {
        //             if (queens[ai][aj] == vals[aj]) {
        //                 cur_q = true;
        //                 break;
        //             }
        //         }
        //         if (!cur_q) {
        //             cur_pt = false;
        //             break;
        //         }
        //     }
        //     if (cur_pt) {
        //         ok = true;
        //         ans = {numx, numy};
        //         break;
        //     }
        // }
        bool ok = false;
        pll ans = {queens[0][0], queens[0][1]};
        ll j = 1;
        while (j < n) {
            if (queens[j][0] != queens[0][0] &&
                queens[j][1] != queens[0][1] &&
                queens[j][2] != queens[0][2] &&
                queens[j][3] != queens[0][3])
            {
                break;
            }
            j++;
        }
        ok = j == n;
        if (!ok) {
            vector<vector<ll>> pts;
            FOR (dir, 4) {
                FOR (djr, 4) {
                    ll i = 0;
                    if (dir == djr) continue;
                    ll a = refx[dir], b = refy[dir],
                        c = refx[djr], d = refy[djr];
                    ll det = a * d - b * c;
                    ll &val1 = queens[i][dir], &val2 = queens[j][djr];
                    ll numx = d * val1 - b * val2, numy = -c * val1 + a * val2;
                    if (numx % det != 0 || numy % det != 0) {
                        continue;
                    }
                    numx /= det;
                    numy /= det;
                    pts.pb({numx, numy, numx + numy, numx - numy});
                }
            }
            for (auto vals : pts) {
                bool cur_pt = true;
                FOR (ai, n) {
                    bool cur_q = false;
                    FOR (aj, 4) {
                        if (queens[ai][aj] == vals[aj]) {
                            cur_q = true;
                            break;
                        }
                    }
                    if (!cur_q) {
                        cur_pt = false;
                        break;
                    }
                }
                if (cur_pt) {
                    ok = true;
                    ans = {vals[0], vals[1]};
                    break;
                }
            }
        }
        if (ok) cout << "YES\n" << ans.x << ' ' << ans.y << '\n';
        else cout << "NO\n";
    }
}
