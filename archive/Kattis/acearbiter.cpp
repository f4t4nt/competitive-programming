#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

#define a first
#define b second

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n; cin >> n;
    vector<pair<ll, ll>> scores(n);
    FOR (i, n) {
        str s; cin >> s;
        scores[i].a = stoll(s.substr(0, s.find('-')));
        scores[i].b = stoll(s.substr(s.find('-') + 1));
    }
    FOR (i, n) {
        ll sum = scores[i].a + scores[i].b + 1;
        sum /= 2;
        if (sum & 1) {
            swap(scores[i].a, scores[i].b);
        }
    }
    bool fixed = false;
    FOR (i, n - 1) {
        if (scores[i].a > scores[i + 1].a || scores[i].b > scores[i + 1].b) {
            cout << "error " << i + 2 << '\n';
            return 0;
        }
        if (scores[i].a == 11 || scores[i].b == 11) {
            fixed = true;
        }
        if (fixed && scores[i] != scores[i + 1]) {
            cout << "error " << i + 2 << '\n';
            return 0;
        }
        if (scores[i].a == 11 && scores[i].b == 11) {
            cout << "error " << i + 1 << '\n';
            return 0;
        }
    }
    if (scores[n - 1].a == 11 && scores[n - 1].b == 11) {
        cout << "error " << n << '\n';
        return 0;
    }
    cout << "ok\n";

    return 0;
}