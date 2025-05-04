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
    pld,
    null_type,
    less<pld>,
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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n; cin >> n;
    vector<tuple<ll, ll, ll>> jobs(n);
    FOR (i, n) {
        ll p, d; cin >> p >> d;
        jobs[i] = {d, p, i + 1};
    }
    ssort(jobs);
    set<pll> s;
    vector<ll> schedule;
    FORR (i, n) {
        ll t = get<0>(jobs[i]) - (i ? get<0>(jobs[i - 1]) : 0);
        s.insert({get<1>(jobs[i]), get<2>(jobs[i])});
        while (t && !s.empty()) {
            auto it = s.begin();
            if (it->first <= t) {
                t -= it->first;
                schedule.pb(it->second);
            } else {
                s.insert({it->first - t, it->second});
                t = 0;
            }
            s.erase(it);
        }
    }
    FORR (i, sz(schedule)) cout << schedule[i] << " \n"[i == 0];

    return 0;
}