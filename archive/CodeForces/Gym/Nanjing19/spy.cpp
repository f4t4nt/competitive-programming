#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef string str;
typedef char ch;
typedef long double ld;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define fliip(C) reverse(all(C))
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

const ll INF = 1e18;

ll arra[400];
ll arrp[400];
ll arrb[400];
ll arrc[400];

// costs[i][j] = j-th worker's cost to do i-th job
vector<ll> hungarian(vector<vector<ll>> &costs) {
    ll J = sz(costs), W = sz(costs[0]);
    vector<ll> job(W + 1, -1), ys(J), yt(W + 1), rv;
    FOR (j_cur, J) {
        ll w_cur = W;
        job[w_cur] = j_cur;
        vector<ll> min_to(W + 1, INF), prv(W + 1, -1);
        vector<bool> in_Z(W + 1);
        while (job[w_cur] != -1) {
            in_Z[w_cur] = true;
            ll j = job[w_cur], del = INF, w_nxt;
            FOR (w, W) {
                if (!in_Z[w]) {
                    if (min_to[w] > costs[j][w] - ys[j] - yt[w]) {
                        min_to[w] = costs[j][w] - ys[j] - yt[w];
                        prv[w] = w_cur;
                    }
                    if (del > min_to[w]) {
                        del = min_to[w];
                        w_nxt = w;
                    }
                }
            }
            FOR (w, W + 1) {
                if (in_Z[w]) ys[job[w]] += del, yt[w] -= del;
                else min_to[w] -= del;
            }
            w_cur = w_nxt;
        }
        for (ll w; w_cur != W; w_cur = w) job[w_cur] = job[w = prv[w_cur]];
        rv.pb(-yt[W]);
    }
    return rv;
}

int main() {
    int n;
    cin >> n;
    FOR(i, n)
    cin >> arra[i];
    FOR(i, n)
    cin >> arrp[i];
    FOR(i, n)
    cin >> arrb[i];
    FOR(i, n)
    cin >> arrc[i];
    vector<vector<ll>> costs(n, vector<ll>(n));
    FOR(i, n)
        FOR(j, n)
        {
            ll power=arrb[i]+arrc[j];
            FOR(k, n)
            {
                if (arra[k]<power)
                    costs[i][j]-=arrp[k];
            }
        }

    cout << -hungarian(costs).back() << endl;
}