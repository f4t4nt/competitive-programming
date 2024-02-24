#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<int, int> pii;

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

ll lo;
set<ll> missing;

void eval(str &s, ll len) {
    lo = stoll(s.substr(0, len));
    ll err = 0, idx = 0, cur = lo;
    missing.clear();
    do {
        str tmp = to_string(cur);
        while (idx + tmp.size() <= s.size() && tmp != s.substr(idx, tmp.size())) {
            missing.insert(cur);
            cur++;
            err++;
            if (err > 1) {
                missing.clear();
                return;
            }
            tmp = to_string(cur);
        }
        if (idx + tmp.size() > s.size()) {
            missing.clear();
            return;
        }
        cur++;
        idx += tmp.size();
    } while (idx != s.size());
    if (err == 0) {
        missing.insert(lo - 1);
        missing.insert(cur);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        str s; cin >> s;
        set<ll> ans;
        for (ll len = 1; len <= 5; len++) {
            eval(s, len);
            for (ll x : missing) ans.insert(x);
        }
        ans.erase(0);
        while (ans.size() > 0 && *ans.rbegin() > 99999) ans.erase(*ans.rbegin());
        cout << ans.size() << '\n';
        for (ll x : ans) cout << x << ' ';
        cout << '\n';
        cout << endl;
    }
}