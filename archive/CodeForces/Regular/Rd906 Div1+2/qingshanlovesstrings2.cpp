#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
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

// imma show YOU how great i am.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        str s;
        cin >> s;
        if (sz(s) % 2 == 1) {
            cout << -1 << '\n';
            continue;
        } else {
            ll cnt[2] = {0, 0};
            FOR (i, n) {
                cnt[s[i] - '0']++;
            }
            if (cnt[0] != cnt[1]) {
                cout << -1 << '\n';
                continue;
            } else {
                vector<ll> rv;
                ll i = 0;
                while (i < sz(s)) {
                    ll j = sz(s) - i - 1;
                    if (s[i] == '0') {
                        if (s[j] == '0') {
                            s.insert(j + 1, "01");
                            rv.pb(j + 1);
                        }
                    } else {
                        if (s[j] == '1') {
                            s.insert(i, "01");
                            rv.pb(i);
                        }
                    }
                    if (sz(rv) > 300) {
                        break;
                    }
                    i++;
                }
                if (sz(rv) > 300) {
                    cout << -1 << '\n';
                } else {
                    // cout << s << '\n';
                    cout << sz(rv) << '\n';
                    FORE (x, rv) {
                        cout << x << ' ';
                    }
                    cout << '\n';
                }
            }
        }
    }

    return 0;
}