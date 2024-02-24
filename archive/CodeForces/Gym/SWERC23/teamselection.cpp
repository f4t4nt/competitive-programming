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

struct BIT {
    vector<ll> tree; ll n;
    BIT(ll n) : n(n), tree(n + 1) {}
    void upd(ll idx, ll val) {
        idx++;
        while(idx <= n) {
            tree[idx] += val;
            idx += idx & (-idx);
        }
    }
    ll qry(ll idx) {
        idx++; ll sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll n; cin >> n;
    vector<ll> ain(n / 2), bin(n / 2), a, b;
    FOR(i, n/2) cin >> ain[i];
    FOR(i, n/2) cin >> bin[i];
    BIT bit(n);
    FOR (i, n) bit.upd(i, 1);

    int x;
    int cnt=0;
    FOR(i, n/2) {
        x=ain[i];
        {
            ll lo = 0, hi = n;
            while (lo < hi) {
                ll mid = (lo + hi) / 2;
                if (bit.qry(mid) >= x) hi = mid;
                else lo = mid + 1;
            }
            bit.upd(lo, -1);
            a.pb(lo + 1);
        }
        x=bin[i];
        {
            ll lo = 0, hi = n;
            while (lo < hi) {
                ll mid = (lo + hi) / 2;
                if (bit.qry(mid) >= x) hi = mid;
                else lo = mid + 1;
            }
            bit.upd(lo, -1);
            b.pb(lo + 1);
        }
    }
    FOR(i, n/2) cout << a[i] << " ";
    cout << '\n';
    FOR(i, n/2) cout << b[i] << " ";
    cout << '\n';

    return 0;
}