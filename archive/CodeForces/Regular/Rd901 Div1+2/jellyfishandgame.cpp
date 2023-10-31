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

ll bash(ll &n, ll &m, ll &k, multiset<ll> &a, multiset<ll> &b) {
    FOR (i, k) {
        if (i % 2 == 0) {  // jelly (a) move
            // pick smallest a, pick largest b, swap
            ll min_a = *a.begin(), max_b = *b.rbegin();
            if (min_a < max_b) {
                a.erase(a.begin());
                b.erase(--b.end());
                a.insert(max_b);
                b.insert(min_a);
            }
        } else { // gelly (b) move
            // pick largest a, pick smallest b, swap
            ll max_a = *a.rbegin(), min_b = *b.begin();
            if (max_a > min_b) {
                a.erase(--a.end());
                b.erase(b.begin());
                a.insert(min_b);
                b.insert(max_a);
            }
        }
    }
    // find sum of jelly
    ll rv = 0;
    FORE (i, a) {
        rv += i;
    }
    return rv;
}

const ll SZ = 1000;

ll fast(ll &n, ll &m, ll &k, multiset<ll> &a, multiset<ll> &b) {
    vector<ll> pre(SZ), nxt;
    ll i = 0, a_sum = 0, b_sum = 0;
    FORE (x, a) {
        a_sum += x;
    }
    while (i < k) {
        if (i % 2 == 0) {  // jelly (a) move
            // pick smallest a, pick largest b, swap
            ll min_a = *a.begin(), max_b = *b.rbegin();
            if (min_a < max_b) {
                a.erase(a.begin());
                b.erase(--b.end());
                a.insert(max_b);
                b.insert(min_a);
                a_sum += max_b - min_a;
            }
        } else { // gelly (b) move
            // pick largest a, pick smallest b, swap
            ll max_a = *a.rbegin(), min_b = *b.begin();
            if (max_a > min_b) {
                a.erase(--a.end());
                b.erase(b.begin());
                a.insert(min_b);
                b.insert(max_a);
                a_sum += min_b - max_a;
            }
        }
        nxt.pb(a_sum);
        if (sz(nxt) == SZ) {
            if (nxt == pre) {
                return nxt[(k + 1) % SZ];
            } else {
                pre = nxt;
                nxt.clear();
            }
        }
        i++;
    }
    return a_sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, m, k;
        cin >> n >> m >> k;
        multiset<ll> a, b;
        FOR (i, n) {
            ll x;
            cin >> x;
            a.insert(x);
        }
        FOR (i, m) {
            ll x;
            cin >> x;
            b.insert(x);
        }
        cout << fast(n, m, k, a, b) << '\n';
    }

    return 0;
}