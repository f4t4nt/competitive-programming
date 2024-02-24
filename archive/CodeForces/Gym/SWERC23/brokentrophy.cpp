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
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)
#define FORE(x, C) for (auto &x : C)

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t = 1;// cin >> t;
    while (t--) {
        ll k, n; cin >> k >> n;
        vector<ll> xs(k), ys(k);
        FOR (i, k) cin >> xs[i];
        FOR (i, k) cin >> ys[i];
        vector<vector<vector<ll>>> idxs(4, vector<vector<ll>>(4));
        FOR (i, k) {
            ll x = xs[i], y = ys[i];
            if (x < y) swap(x, y);
            idxs[x][y].pb(i + 1);
        }

        vector<vector<ll>> ans(n, vector<ll>(3));
        ll cur = 0; // last completely filled col

        // 3x3
        FORE (i, idxs[3][3]) {
            for (ll j = cur; j < cur + 3; j++) {
                FOR (k, 3) {
                    ans[j][k] = i;
                }
            }
            cur += 3;
        }

        // 3x2
        FORE (i, idxs[3][2]) {
            for (ll j = cur; j < cur + 2; j++) {
                FOR (k, 3) {
                    ans[j][k] = i;
                }
            }
            cur += 2;
        }

        // 2x2
        ll tmp22 = cur;
        FORE (i, idxs[2][2]) {
            for (ll j = tmp22; j < tmp22 + 2; j++) {
                FOR (k, 2) {
                    ans[j][k] = i;
                }
            }
            tmp22 += 2;
        }

        // 3x1
        ll tmp1 = cur, idx31 = 0;
        // FORE (i, idxs[3][1]) {
        while (idx31 < sz(idxs[3][1])) {
            if (tmp1 + 3 > tmp22) break;
            ll i = idxs[3][1][idx31++];
            for (ll j = tmp1; j < tmp1 + 3; j++) {
                ans[j][2] = i;
            }
            tmp1 += 3;
        }

        ll tmp31 = n - 1;
        while (idx31 < sz(idxs[3][1])) {
            ll i = idxs[3][1][idx31++];
            FOR (k, 3) {
                ans[tmp31][k] = i;
            }
            tmp31--;
        }

        // 2x1, filled with 2x2s
        ll idx21 = 0;
        // FORE (i, idxs[2][1]) {
        while (idx21 < sz(idxs[2][1])) {
            if (tmp1 >= tmp22) break;
            ll i = idxs[2][1][idx21++];
            for (ll j = tmp1; j < tmp1 + 2; j++) {
                ans[j][2] = i;
            }
            tmp1 += 2;
        }

        // 2x1, fill remaining
        ll y21 = 0;
        while (idx21 < sz(idxs[2][1])) {
            if (tmp1 + 1 >= n || ans[tmp1][y21] != 0 || ans[tmp1 + 1][y21] != 0) break;
            ll i = idxs[2][1][idx21++];
            ans[tmp1][y21] = ans[tmp1 + 1][y21] = i;
            y21++;
            if (y21 == 3) {
                tmp1 += 2;
                y21 = 0;
            }
        }

        if (idx21 < sz(idxs[2][1])) {
            ll i = idxs[2][1][idx21++];
            ll idek = 0;
            while (ans[idek][0] != 0) idek++;
            ans[idek][0] = ans[idek][1] = i;
        }

        // 1x1
        ll idx11 = 0;
        FOR (i, 3) FOR (j, n) if (ans[j][i] == 0) ans[j][i] = idxs[1][1][idx11++];
        while(idx11 != sz(idxs[1][1])) continue;

        cout << '\n';
        FOR (i, 3) {
            FOR (j, n) cout << ans[j][i] << ' ';
            cout << '\n';
        }
        cout << endl;
    }

    return 0;
}
/*
100

16 17
1 2 1 1 2 1 2 1 1 1 1 1 2 2 1 1
3 3 1 3 2 3 3 1 1 2 2 3 3 3 1 3

18 23
1 2 1 1 2 1 2 1 1 1 1 1 2 2 1 1 3 3
3 3 1 3 2 3 3 1 1 2 2 3 3 3 1 3 3 3

8 5
1 1 1 1 1 1 1 1
2 2 2 2 2 2 2 1

3 2
2 1 1
2 1 1

12 11
2 2 2 2 3 3 3 2 2 2 1 1
2 2 2 2 1 1 1 1 1 1 1 1

5 5
2 2 3 2 2
2 2 1 1 1

6 6
2 2 2 2 3 3
2 2 1 1 1 1

10 10
2 2 2 2 2 2 2 2 3 3
2 2 2 2 1 1 1 1 1 1

6 5
2 2 2 2 2 3
2 1 1 1 1 1

8 7
2 2 3 2 2 2 2 2
2 2 1 1 1 1 1 1

4 4
3 3 2 1
2 1 1 1
*/