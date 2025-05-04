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

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
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
#define f first
#define s second

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

    vector<vector<ll>> divs(1e6 + 1);
    for (ll i = 1; i <= 1e6; i++)
        for (ll j = 2 * i; j <= 1e6; j += i)
            divs[j].pb(i);

    ll t; cin >> t;
    while (t--) {
        ll n, mx = 0; cin >> n;
        vector<ll> a(n);
        for (ll &x : a) {
            cin >> x;
            mx = max(mx, x);
        }
        vector<ll> nxt_gt(n, n), prv_gt(n, -1),
            nxt_lt(n, n), prv_lt(n, -1),
            nxt_eq(n, n), prv_eq(n, -1);
        vector<ll> tmp(mx + 1, -1);
        for (ll i = 0; i < n; i++) {
            prv_eq[i] = tmp[a[i]];
            tmp[a[i]] = i;
        }
        tmp = vector<ll>(mx + 1, n);
        for (ll i = n - 1; i >= 0; i--) {
            nxt_eq[i] = tmp[a[i]];
            tmp[a[i]] = i;
        }
        stack<pll> stk;
        for (ll i = 0; i < n; i++) {
            while (!stk.empty() && stk.top().f < a[i]) {
                nxt_gt[stk.top().s] = i;
                stk.pop();
            }
            stk.push({a[i], i});
        }
        stk = stack<pll>();
        for (ll i = n - 1; i >= 0; i--) {
            while (!stk.empty() && stk.top().f < a[i]) {
                prv_gt[stk.top().s] = i;
                stk.pop();
            }
            stk.push({a[i], i});
        }
        stk = stack<pll>();
        for (ll i = 0; i < n; i++) {
            while (!stk.empty() && stk.top().f > a[i]) {
                nxt_lt[stk.top().s] = i;
                stk.pop();
            }
            stk.push({a[i], i});
        }
        stk = stack<pll>();
        for (ll i = n - 1; i >= 0; i--) {
            while (!stk.empty() && stk.top().f > a[i]) {
                prv_lt[stk.top().s] = i;
                stk.pop();
            }
            stk.push({a[i], i});
        }
        vector<vector<ll>> pos(mx + 1);
        for (ll i = 0; i < n; i++) pos[a[i]].pb(i);
        ll ans = 0;
        for (ll i = 0; i < n; i++) {
            ll x = a[i];
            for (ll d : divs[x]) {
                if (pos[d].empty()) continue;
                auto it = lower_bound(all(pos[d]), i);
                ll prv_d = -1, nxt_d = n;
                if (it != pos[d].begin()) prv_d = *prev(it);
                if (it != pos[d].end()) nxt_d = *it;
                bool ok_li = max(prv_gt[i], prv_eq[i]) < prv_d,
                    ok_ri = nxt_gt[i] > nxt_d;
                if (!ok_li && !ok_ri) continue;
                elif (ok_li && !ok_ri) {
                    assert(prv_d != -1);
                    if (nxt_lt[prv_d] > i) {
                        ll l = max({prv_gt[i], prv_eq[i], prv_lt[prv_d]}),
                            r = min(nxt_gt[i], nxt_lt[prv_d]);
                        ans += (prv_d - l) * (r - i);
                    }
                } elif (!ok_li && ok_ri) {
                    assert(nxt_d != n);
                    if (prv_lt[nxt_d] < i) {
                        ll l = max({prv_gt[i], prv_eq[i], prv_lt[nxt_d]}),
                            r = min(nxt_gt[i], nxt_lt[nxt_d]);
                        ans += (i - l) * (r - nxt_d);
                    }
                } else {
                    assert(prv_d != -1 && nxt_d != n);
                    if (nxt_lt[prv_d] > nxt_d) {
                        assert(nxt_eq[prv_d] == nxt_d);
                        ll l = max({prv_gt[i], prv_eq[i], prv_lt[prv_d]}),
                            r = min(nxt_gt[i], nxt_lt[nxt_d]);
                        ans += (i - l) * (r - i) - (i - prv_d) * (nxt_d - i);
                    } elif (nxt_lt[prv_d] > i) {
                        ll l = max({prv_gt[i], prv_eq[i], prv_lt[prv_d]}),
                            r = min(nxt_gt[i], nxt_lt[prv_d]);
                        ans += (prv_d - l) * (r - i);
                    } elif (prv_lt[nxt_d] < i) {
                        ll l = max({prv_gt[i], prv_eq[i], prv_lt[nxt_d]}),
                            r = min(nxt_gt[i], nxt_lt[nxt_d]);
                        ans += (i - l) * (r - nxt_d);
                    }
                }
            }
        }
        for (ll i = 0; i < n;) {
            ll j = i;
            while (j < n && a[j] == a[i]) j++;
            ans += (j - i) * (j - i + 1) / 2;
            i = j;
        }
        cout << ans << '\n';
    }

    return 0;
}