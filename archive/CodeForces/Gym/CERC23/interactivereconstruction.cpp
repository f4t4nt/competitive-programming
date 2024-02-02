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
    ll n;
    cin >> n;
    vector<vector<ll>> vals(16, vector<ll>(n, 0));

    cout << "QUERY ";
    FOR (i, n) cout << 1;
    cout << endl;
    FOR (i, n) cin >> vals[0][i];

    FOR (b, 15) {
        cout << "QUERY ";
        FOR (i, n) cout << ((i >> b) & 1);
        cout << endl;
        FOR (i, n) cin >> vals[b + 1][i];
    }

    deque<ll> q;
    FOR (i, n) {
        if (vals[0][i] == 1) q.pb(i);
    }

    cout << "ANSWER\n";

    FOR (ct, n - 1) {
        ll cur = q.front();
        q.pop_front();

        ll par = 0;
        FOR (i, 15) {
            if (vals[i + 1][cur]) par |= (1 << i);
        }

        FOR (i, 16) vals[i][cur] = 0;
        vals[0][par]--;
        FOR (i, 15) {
            if (cur & (1 << i)) {
                vals[i + 1][par]--;
            }
        }

        if (vals[0][par] == 1) q.pb(par);
        cout << cur+1 << " " << par+1 << endl;
    }
    
}