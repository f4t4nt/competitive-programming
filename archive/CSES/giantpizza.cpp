#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt")

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

bool dfs(ll i, vector<pair<vector<ll>, vector<ll>>> &req, vector<ll> &rv, set<ll> &vis) {
    if (vis.count(i)) {
        return false;
    }
    if (i == sz(rv)) {
        bool ok = true;
        FOB (j, 1, sz(rv)) {
            if (rv[j] == 1) {
                FORE (r, req[j].first) {
                    if (r < 0) {
                        if (rv[-r] != -1) {
                            ok = false;
                            break;
                        }
                    } else {
                        if (rv[r] != 1) {
                            ok = false;
                            break;
                        }
                    }
                }
            } elif (rv[j] == -1) {
                FORE (r, req[j].second) {
                    if (r < 0) {
                        if (rv[-r] != -1) {
                            ok = false;
                            break;
                        }
                    } else {
                        if (rv[r] != 1) {
                            ok = false;
                            break;
                        }
                    }
                }
            } else {
                ok = false;
                break;
            }
        }
        return ok;
    }
    if (rv[i] == 0) {
        bool ok = true, mod = false;
        set<ll> undo;
        rv[i] = 1;
        FORE (r, req[i].first) {
            if (r < 0) {
                if (rv[-r] == 1) {
                    mod = true;
                    ok = false;
                    break;
                }
                rv[-r] = -1;
                undo.insert(-r);
            } else {
                if (rv[r] == -1) {
                    mod = true;
                    ok = false;
                    break;
                }
                rv[r] = 1;
                undo.insert(r);
            }
        }
        if (ok && dfs(i + 1, req, rv, vis)) {
            return true;
        }
        rv[i] = 0;
        FORE (r, undo) {
            rv[r] = 0;
        }
        ok = true;
        undo.clear();
        rv[i] = -1;
        FORE (r, req[i].second) {
            if (r < 0) {
                if (rv[-r] == 1) {
                    mod = true;
                    ok = false;
                    break;
                }
                rv[-r] = -1;
                undo.insert(-r);
            } else {
                if (rv[r] == -1) {
                    mod = true;
                    ok = false;
                    break;
                }
                rv[r] = 1;
                undo.insert(r);
            }
        }
        if (ok && dfs(i + 1, req, rv, vis)) {
            return true;
        }
        if (!mod) {
            vis.insert(i);
        }
    } else {
        if (dfs(i + 1, req, rv, vis)) {
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    // {if yes, if no}
    // +i = yes i, -i = no i
    vector<pair<vector<ll>, vector<ll>>> req(m + 1);
    FOR (i, n) {
        ch s1, s2;
        ll x, y;
        cin >> s1 >> x >> s2 >> y;
        x = (s1 == '+' ? x : -x);
        y = (s2 == '+' ? y : -y);
        if (x < 0) {
            req[-x].first.pb(y);
        } else {
            req[x].second.pb(y);
        }
        if (y < 0) {
            req[-y].first.pb(x);
        } else {
            req[y].second.pb(x);
        }
    }
    set<ll> vis;
    vector<ll> rv(m + 1);
    bool res = dfs(1, req, rv, vis);
    if (!res) {
        cout << "IMPOSSIBLE\n";
    } else {
        FOB (i, 1, sz(rv)) {
            if (rv[i] == 1) {
                cout << "+ ";
            } else {
                cout << "- ";
            }
        }
        cout << '\n';
    }

    return 0;
}