#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<tuple<ll, ll, str>> res;
    FOR (i, n) {
        str name; cin >> name;
        ll p; cin >> p;
        vector<ll> e(6);
        FOR (i, 6) cin >> e[i];
        sort(all(e));
        e.erase(e.begin());
        e.pop_back();
        ll t_score = accumulate(all(e), 0LL);
        ll net = p * 10 + t_score;
        res.pb({-net, i, name});
    }
    ssort(res);
    ll cut = 2;
    while (cut < n && get<0>(res[cut]) == get<0>(res[2])) cut++;
    while (sz(res) > cut) res.pop_back();
    FOR (i, cut) cout << get<2>(res[i]) << ' ' << -get<0>(res[i]) << '\n';
    
    return 0;
}