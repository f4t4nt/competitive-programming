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

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, q; cin >> n >> q;
    ll cnt_rows = n, cnt_cols = n;
    vector<ll> cols(n), rows(n);
    FOR (i, n) cols[i] = i & 1;
    FOR (i, n) rows[i] = i & 1;
    while (q--) {
        str s; ll idx; cin >> s >> idx; idx--;
        if (s == "ROW") {
            if (idx > 0) {
                if (rows[idx] != rows[idx - 1]) cnt_rows--;
                else cnt_rows++;
            }
            if (idx < n - 1) {
                if (rows[idx] != rows[idx + 1]) cnt_rows--;
                else cnt_rows++;
            }
            rows[idx] = !rows[idx];
        } else {
            if (idx > 0) {
                if (cols[idx] != cols[idx - 1]) cnt_cols--;
                else cnt_cols++;
            }
            if (idx < n - 1) {
                if (cols[idx] != cols[idx + 1]) cnt_cols--;
                else cnt_cols++;
            }
            cols[idx] = !cols[idx];
        }
        cout << cnt_rows * cnt_cols << '\n';
    }

    return 0;
}