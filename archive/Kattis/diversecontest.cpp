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
// #define f first
// #define s second

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, k; cin >> n >> k;
    map<str, ll> topic_id;
    vector<vector<ll>> problems(n);
    FOR (i, n) {
        ll m; cin >> m;
        FOR (j, m) {
            str topic; cin >> topic;
            if (!topic_id.count(topic)) {
                ll id = sz(topic_id);
                topic_id[topic] = id;
            }
            problems[i].pb(topic_id[topic]);
        }
    }
    ll ans = 0;
    FOR (mask, 1 << n) {
        if (__builtin_popcount(mask) != k) continue;
        vector<ll> topics(sz(topic_id));
        bool ok = true;
        FOR (i, n) {
            if (mask & (1 << i)) {
                for (ll topic : problems[i]) {
                    topics[topic]++;
                    if (topics[topic] > k / 2) {
                        ok = false;
                        break;
                    }
                }
            }
            if (!ok) break;
        }
        if (ok) ans++;
    }
    cout << ans << '\n';

    return 0;
}