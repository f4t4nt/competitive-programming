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
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, p, k;
    cin >> n >> p >> k;
    vector<ll> duration(n);
    FOR (i, n) {
        cin >> duration[i];
    }
    vector<ll> prefix(2 * n + 1);
    FOR (i, 2 * n) {
        prefix[i + 1] = prefix[i] + duration[i % n];
    }
    vector<pair<ll, ll>> last_start(n, {-1, 0}), next_player(n, {-1, 0});
    ll day = 0, cur = 0, pass = 0;
    while (last_start[cur].first == -1) {
        ll orig = cur, cur_pass = pass;
        last_start[cur] = {day, pass};
        // ll today = 0;
        // while (today + duration[cur] <= p) {
        //     today += duration[cur];
        //     cur++;
        //     if (cur == n) {
        //         cur = 0;
        //         pass++;
        //     }
        // }
        pass += p / prefix[n];
        ll rem = p % prefix[n];
        auto it = upper_bound(all(prefix), rem + prefix[cur]);
        ll next = (it - prefix.begin() - 1 + 2 * n) % n;
        if (next < cur) {
            pass++;
        }
        cur = next;
        next_player[orig] = {cur, pass - cur_pass};
        day++;
    }
    ll period = day - last_start[cur].first;
    ll total_pass = pass - last_start[cur].second;
    ll rv = last_start[cur].second + (k - last_start[cur].first) / period * total_pass;
    ll remaing_days = (k - last_start[cur].first) % period;
    while (remaing_days--) {
        ll today = 0;
        rv += next_player[cur].second;
        cur = next_player[cur].first;
    }
    cout << rv << '\n';

    return 0;
}