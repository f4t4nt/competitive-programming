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

constexpr ll MOD = 1e17 + 7;

vector<ll> pow26(25e4 + 1, 1);

void insert_char_back(ch c, ll &hash) {
    hash = (hash * 26 + (c - 'a')) % MOD;
}

void insert_char_front(ch c, ll &hash, ll &len) {
    hash = (hash + (c - 'a') * pow26[len]) % MOD;
    len++;
}

bool find_match(ll idx_x, ll idx_y, ll &lim, str &x, str &y, vector<ll> x_ch, vector<ll> y_ch, ll depth = 0) {
    if (idx_x > lim) {
        return true;
    }
    if (depth > 2) {
        return false;
    }

    ll x_begin = idx_x, y_begin = idx_y;
    ll x_hash = 0, y_hash = 0, len = 0;
    vector<pair<ll, ll>> idxs;

    while (idx_x <= lim) {
        insert_char_back(x[idx_x], x_hash);
        insert_char_front(y[idx_y], y_hash, len);
        x_ch[x[idx_x] - 'a']--;
        y_ch[y[idx_y] - 'a']--;
        if (x_hash == y_hash) {
            bool valid = true;
            FOR (i, 26) {
                if (x_ch[i] != y_ch[i]) {
                    valid = false;
                    break;
                }
            }
            if (valid && memcmp(&x[x_begin], &y[idx_y], idx_x - x_begin + 1) == 0) {
                // if (find_match(idx_x + 1, idx_y - 1, lim, x, y, x_ch, y_ch, depth + 1)) {
                //     return true;
                // }
                idxs.pb(mp(idx_x + 1, idx_y - 1));
            }
        }
        idx_x++;
        idx_y--;
    }

    // random_shuffle(idxs.begin(), idxs.end());

    // ll tmp = 0;
    // FORE (idx, idxs) {
    //     if (find_match(idx.first, idx.second, lim, x, y, x_ch, y_ch, depth + 1)) {
    //         return true;
    //     }
    //     tmp++;
    //     if (tmp > 130) {
    //         break;
    //     }
    // }

    if (sz(idxs) > 0 &&
        find_match(idxs.back().first, idxs.back().second, lim, x, y, x_ch, y_ch, depth + 1)) {
        return true;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    FOR(i, 25e4) {
        pow26[i + 1] = (pow26[i] * 26) % MOD;
    }

    str x, y;
    cin >> x >> y;
    vector<ll> x_ch(26, 0), y_ch(26, 0);
    FOR (i, sz(x)) {
        x_ch[x[i] - 'a']++;
        y_ch[y[i] - 'a']++;
    }

    bool valid = true;
    FOR (i, 26) {
        if (x_ch[i] != y_ch[i]) {
            valid = false;
            break;
        }
    }
    if (!valid) {
        cout << 0 << '\n';
        return 0;
    }

    ll d = sz(x) - 1;
    while (d >= 0 && x[d] == y[d]) {
        x_ch[x[d] - 'a']--;
        y_ch[y[d] - 'a']--;
        d--;
    }

    ll e = 0;
    // while (e < sz(x) && x[e] == y[e]) {
    //     x_ch[x[e] - 'a']--;
    //     y_ch[y[e] - 'a']--;
    //     e++;
    // }

    if (find_match(e, d, d, x, y, x_ch, y_ch)) {
        cout << 1 << '\n';
    } else {
        if (find_match(e, d, d, y, x, y_ch, x_ch)) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }

    return 0;
}