#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<long, long> pll;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)
#define FORE(x, C) for (auto &x : C)

ll lis(vector<pll> conv) {
    vector<pll> cur;
    FORE (card, conv) {
        if (sz(cur) == 0) cur.pb(card);
        else {
            auto it = upper_bound(all(cur), card);
            if (it == cur.end()) cur.pb(card);
            else *it = min(*it, card);
        }
    }
    return sz(cur);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, ans = 1e18; cin >> n;
    vector<pair<ch, ll>> cards(n);
    FOR (i, n) {
        str card; cin >> card;
        cards[i] = {*card.begin(), stoll(card.substr(1))};
    }
    str ref = "SWER";
    ssort(ref);
    do {
        map<ch, ll> mapping;
        FOR (i, 5) mapping[ref[i]] = i;
        mapping['C'] = 10;
        vector<pll> conv;
        FOR (i, n) conv.pb({mapping[cards[i].first], cards[i].second});
        ans = min(ans, n - lis(conv));
    } while (next_permutation(all(ref)));
    cout << ans << '\n';

    return 0;
}