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

vector<vector<ll>> pow10s(3, vector<ll>(5e3 + 5, 1));
vector<ll> ref4(3);
ll MODS[] = {(ll) 1e9 + 7, (ll) 1e12 + 7, (ll) 1e15 + 7};
map<ch, ll> ch_map;

vector<vector<ll>> get_hash(str &s) {
    vector<vector<ll>> rv(sz(pow10s), vector<ll>(sz(s)));
    FOR (j, sz(pow10s)) {
        FOR (i, sz(s)) {
            rv[j][0] = (10 * rv[j][0] + ch_map[s[i]]) % MODS[j];
        }
        FOB (i, 1, sz(s)) {
            rv[j][i] = ((10 * rv[j][i - 1] - ch_map[s[i - 1]] * pow10s[j][sz(s)] +
                ch_map[s[i - 1]]) % MODS[j] + MODS[j]) % MODS[j];
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ch_map['A'] = 0;
    ch_map['B'] = 1;
    ch_map['C'] = 3;
    FOR (j, sz(pow10s)) {
        auto &pow10 = pow10s[j];
        FOB (i, 1, sz(pow10)) {
            pow10[i] = (pow10[i - 1] * 10) % MODS[j];
        }
    }

    vector<str> s(3);
    FOR (i, 3) {
        cin >> s[i];
    }
    FOR (j, sz(pow10s)) {
        FOR (i, sz(s[0])) {
            ref4[j] = (ref4[j] * 10 + 4) % MODS[j];
        }
    }
    // [layer][mod][rotation]
    vector<vector<vector<ll>>> h(3);
    FOR (i, 3) {
        h[i] = get_hash(s[i]);
    }
    ll rv = 1e18;
    FOR (i, sz(s[0])) {
        FOR (j, sz(s[0])) {
            bool ok = true;
            FOR (k, sz(pow10s)) {
                ll tmp = ((h[0][k][i] + h[1][k][j]) % MODS[k] + h[2][k][0]) % MODS[k];
                if (tmp != ref4[k]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                vector<ll> tmp = {
                    min(i, sz(s[0]) - i) + min(j, sz(s[0]) - j),
                    min(i, sz(s[0]) - i) + min(abs(j - i), sz(s[0]) - abs(j - i)),
                    min(abs(j - i), sz(s[0]) - abs(j - i)) + min(j, sz(s[0]) - j) 
                };
                FORE (x, tmp) {
                    rv = min(rv, x);
                }
            }
        }
    }
    if (rv == 1e18) {
        cout << -1 << '\n';
    } else {
        cout << rv << '\n';
    }

    return 0;
}