#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

int main() {
    ll n, q; cin >> n >> q;
    vector<ll> d(n), tf(n), ts(n);
    FOR (idx, n) {
        cin >> d[idx] >> tf[idx] >> ts[idx];
    }
    // <ts, tf, d>
    vector<tuple<ll, ll, ll>> laundry;
    FOR (idx, n) {
        laundry.pb({ts[idx], tf[idx], d[idx]});
    }
    ssort(laundry);
    // [length] : min time
    map<ll, ll> ref;
    ll len1 = 0, len2 = accumulate(all(d), 0LL);
    multiset<ll> times1 = {0}, times2 = {0};
    FOR (idx, n) {
        times2.insert(tf[idx]);
    }
    bitset<150001> knap;
    knap[0] = 1;
    ll cur_t = *times2.rbegin();
    ref[len2] = cur_t;
    FOR (i, n) {
        auto [cur_ts, cur_tf, cur_d] = laundry[i];
        len2 -= cur_d;
        len1 += cur_d;
        times2.erase(times2.find(cur_tf));
        times1.insert(cur_ts);
        cur_t = max(*times1.rbegin(), *times2.rbegin());
        knap |= (knap << cur_d);
        ll x = len1 / 2;
        while (!knap[x]) x--;
        ll tot_len = len2 + len1 - x;
        if (!ref.count(tot_len)) ref[tot_len] = cur_t;
    }
    while (q--) {
        ll len; cin >> len;
        auto it = ref.upper_bound(len);
        if (it == ref.begin()) cout << -1 << '\n';
        else {
            it--;
            cout << it->second << '\n';
        }
    }
}