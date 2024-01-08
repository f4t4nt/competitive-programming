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

bool valid(vector<ll> &t) {
    ll h = t[0] * 10 + t[1], m = t[2] * 10 + t[3];
    return 0 <= h && h < 24 && 0 <= m && m < 60;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str t0_s, t1_s;
    cin >> t0_s >> t1_s;
    vector<ll> t0 = {t0_s[0] - '0', t0_s[1] - '0', t0_s[3] - '0', t0_s[4] - '0'},
        t1 = {t1_s[0] - '0', t1_s[1] - '0', t1_s[3] - '0', t1_s[4] - '0'};
    map<vector<ll>, pair<ll, vector<ll>>> dist;
    queue<vector<ll>> q;
    q.push(t0);
    dist[t0] = {0, {}};
    while(!q.empty()) {
        auto t = q.front();
        q.pop();
        if (t == t1) {
            break;
        }
        FOR (i, 4) {
            vector<ll> t2 = t;
            t2[i] = (t2[i] + 1) % 10;
            if (!dist.count(t2) && valid(t2)) {
                dist[t2] = {dist[t].first + 1, t};
                q.push(t2);
            }
            t2 = t;
            t2[i] = (t2[i] + 9) % 10;
            if (!dist.count(t2) && valid(t2)) {
                dist[t2] = {dist[t].first + 1, t};
                q.push(t2);
            }
        }
    }
    vector<str> rv;
    auto t = t1;
    while (t != t0) {
        rv.pb(to_string(t[0]) + to_string(t[1]) + ":" + to_string(t[2]) + to_string(t[3]));
        t = dist[t].second;
    }
    rv.pb(to_string(t0[0]) + to_string(t0[1]) + ":" + to_string(t0[2]) + to_string(t0[3]));
    flip(rv);
    cout << sz(rv) << '\n';
    FORE (x, rv) {
        cout << x << '\n';
    }

    return 0;
}