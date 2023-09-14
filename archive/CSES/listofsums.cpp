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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

bool ok(vector<ll> &a, multiset<ll> b) {
    FOB (i, 1, sz(a)) {
        FOR (j, i - 1) {
            ll sum = a[i - 1] + a[j];
            auto it = b.find(sum);
            if (it == b.end()) {
                return false;
            }
            b.erase(it);
        }
        a[i] = *b.begin() - a[0];
    }
    FOR (i, sz(a) - 1) {
        auto it = b.find(a[i] + a.back());
        if (it == b.end()) {
            return false;
        }
        b.erase(it);
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    ll m = n * (n - 1) / 2;
    vector<ll> b(m);
    multiset<ll> bs;
    FOR (i, m) {
        cin >> b[i];
        bs.insert(b[i]);
    }
    ssort(b);
    vector<ll> a(n);
    FOB (i, 1, m) {
        a[0] = (b[0] + b[1] - b[i]) / 2;
        if (0 < a[0] && a[0] <= b[0] / 2 && ok(a, bs)) {
            break;
        }
    }
    FORE (ai, a) {
        cout << ai << ' ';
    }
    cout << '\n';

    return 0;
}