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

const ll INF = 1e18;

bool ok(str &seq) {
    if (seq.back() != 'O') {
        return false;
    }
    FOR (i, sz(seq)) {
        if (seq[i] != 'O' && seq[i] != 'E') {
            return false;
        }
        if (i > 0 && seq[i] == 'O' && seq[i - 1] == 'O') {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    set<ll> pow2;
    FOR (p, 62) {
        pow2.insert(1LL << p);
    }

    str seq;
    cin >> seq;
    if (!ok(seq)) {
        cout << "INVALID\n";
        return 0;
    }
    for (ll x : pow2) {
        bool ok = true;
        FORR (i, sz(seq)) {
            if (seq[i] == 'O') {
                x--;
                if (x <= 0 || x % 3 != 0) {
                    goto skip;
                }
                x /= 3;
                if (x % 2 == 0) {
                    goto skip;
                }
            } else {
                x *= 2;
                if (x > INF) {
                    goto skip;
                }
            }
            if (pow2.count(x)) {
                goto skip;
            }
        }
        cout << x << '\n';
        return 0;
        skip:;
    }
    cout << "INVALID\n";

    return 0;
}