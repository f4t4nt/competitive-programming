#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;
 
#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
 
#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto &x : C)
 
#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll MOD = 1e9 + 7;

struct SegTree {
    ll n;
    vector<ll> data, lazy;
    SegTree (ll n) : n(n), data(4 * n), lazy(4 * n) {}
    void push(ll i, ll l, ll r) {
        if (lazy[i] == 0) return;
        data[i] += (r - l) * lazy[i];
        if (r - l > 1) {
            lazy[2 * i] = (lazy[2 * i] + lazy[i]) % MOD;
            lazy[2 * i + 1] = (lazy[2 * i + 1] + lazy[i]) % MOD;
        }
        lazy[i] = 0;
    }
    void update(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            lazy[i] = (lazy[i] + val) % MOD;
            push(i, l, r);
            return;
        }
        ll m = (l + r) / 2;
        update(ul, ur, val, 2 * i, l, m);
        update(ul, ur, val, 2 * i + 1, m, r);
        data[i] = (data[2 * i] + data[2 * i + 1]) % MOD;
    }
    ll query(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        push(i, l, r);
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return (query(ql, qr, 2 * i, l, m) + query(ql, qr, 2 * i + 1, m, r)) % MOD;
    }
    void print(ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        cout << "[" << l << ", " << r << "): " << data[i] << " " << lazy[i] << '\n';
        if (r - l > 1) {
            ll m = (l + r) / 2;
            print(2 * i, l, m);
            print(2 * i + 1, m, r);
        }
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> a(n);
    map<ll, ll> m;
    FORE (x, a) {
        cin >> x;
        m[x] = 0;
    }
    ll cnt = 0;
    FORE (x, m) {
        x.second = cnt++;
    }
    FORE (x, a) {
        x = m[x];
    }
    SegTree st(cnt);
    FORE (x, a) {
        ll pre = st.query(0, x);
        st.update(x, x + 1, pre + 1);
    }
    cout << st.query(0, cnt) << '\n';

    return 0;
}