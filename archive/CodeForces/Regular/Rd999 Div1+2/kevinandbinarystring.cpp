#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define x first
// #define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct Block {
    ch c;
    ll len;
};

void merge(list<Block> &blocks, list<Block>::iterator it) {
    bool changed = true;
    while (changed) {
        changed = false;
        // for (auto it = blocks.begin(); it != blocks.end() && next(it) != blocks.end();) {
        //     auto nxt = next(it);
        //     if (it->c == nxt->c) {
        //         it->len += nxt->len;
        //         blocks.erase(nxt);
        //         changed = true;
        //     } else {
        //         it++;
        //     }
        // }
        if (it != blocks.begin()) {
            auto prv = prev(it);
            if (prv->c == it->c) {
                prv->len += it->len;
                auto tmp = it;
                it = prv;
                blocks.erase(tmp);
                changed = true;
            }
        }
        if (next(it) != blocks.end()) {
            auto nxt = next(it);
            if (nxt->c == it->c) {
                it->len += nxt->len;
                blocks.erase(nxt);
                changed = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll tt; cin >> tt;
    while (tt--) {
        str s, t; cin >> s >> t;
        ll n = sz(s), cost = 0;
        ll c0s = 0, c1s = 0, c0t = 0, c1t = 0;
        for (ch c : s) {
            if (c == '0') c0s++;
            else c1s++;
        }
        for (ch c : t) {
            if (c == '0') c0t++;
            else c1t++;
        }
        if (c0s != c0t || c1s != c1t) {
            cout << -1 << '\n';
            continue;
        }

        auto buildBlocks = [&](const str &s) {
            vector<Block> vec;
            for (ch c : s) {
                if (vec.empty() || vec.back().c != c) {
                    vec.pb({c, 1});
                } else {
                    vec.back().len++;
                }
            }
            return vec;
        };
        vector<Block> tb = buildBlocks(t);

        auto maxBlockChar = [&](const vector<Block> &vec, char c) {
            ll mx = 0;
            for (auto [cc, len] : vec) if (cc == c && len > mx) mx = len;
            return mx;
        };

        vector<Block> sb = buildBlocks(s);
        ll s0max = maxBlockChar(sb, '0'),
            t0max = maxBlockChar(tb, '0'),
            s1max = maxBlockChar(sb, '1'),
            t1max = maxBlockChar(tb, '1');
        
        if (s0max > t0max || s1max > t1max) {
            cout << -1 << ' ';
            continue;
        }

        list<Block> sl(all(sb));
        bool ok = true;
        ll j = 0;

        while (j < sz(tb) && ok) {
            auto [tc, tlen] = tb[j];
            while (tlen > 0 && ok) {
                if (sl.empty()) {
                    ok = false;
                    break;
                }

                auto it0 = sl.begin();
                if (it0->c == tc) {
                    if(it0->len == tlen) {
                        sl.erase(it0);
                        tlen = 0;
                    } elif (it0->len < tlen) {
                        tlen -= it0->len;
                        sl.erase(it0);
                    } else {
                        ok = false;
                        break;
                    }
                } else {
                    auto it1 = sl.begin(); it1++;
                    ll pos = 1;
                    bool found = false;
                    while (it1 != sl.end()) {
                        if (it1->c == tc) {
                            found = true;
                            break;
                        }
                        it1++, pos++;
                    }
                    if (!found) {
                        ok = false;
                        break;
                    }

                    FOR (j, pos) {
                        auto prv = prev(it1);
                        cost++;
                        sl.splice(prv, sl, it1);
                        it1 = prv;
                        merge(sl, it1);
                    }
                }
            }

            if(!ok) break;
            j++;
        }

        if (ok && j == sz(tb)) {
            if (!sl.empty()) {
                for (auto &b : sl) if (b.len > 0) {
                    ok = false;
                    break;
                }
            }
        } else {
            ok = false;
        }

        cout << (ok ? cost : -1) << '\n';
    }

    return 0;
}