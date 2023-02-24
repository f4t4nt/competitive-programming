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

vector<ll> fraction(ll p, ll q) {
    vector<ll> a;
    while (q) {
        a.push_back(p / q);
        p %= q;
        swap(p, q);
    }
    return a;
}

pair<vector<ll>, vector<ll>> convergents(vector<ll> a) {
    vector<ll> p = {0, 1};
    vector<ll> q = {1, 0};
    FORE (it, a) {
        p.pb(p[sz(p) - 1] * it + p[sz(p) - 2]);
        q.pb(q[sz(q) - 1] * it + q[sz(q) - 2]);
    }
    return {p, q};
}

tuple<vector<ll>, vector<ll>, vector<ll>> hull(vector<ll> a, ll N) {
    vector<ll> p, q;
    tie(p, q) = convergents(a);
    ll t = N / q[sz(q) - 1];
    vector<ll> ah = {t};
    vector<ll> ph = {0, t * p[sz(p) - 1]};
    vector<ll> qh = {0, t * q[sz(q) - 1]};
    FORR (i, sz(q)) {
        if (i % 2 == 1) {
            while (qh[sz(qh) - 1] + q[i - 1] <= N) {
                ll t = (N - qh[sz(qh) - 1] - q[i - 1]) / q[i];
                ll dp = p[i - 1] + t * p[i];
                ll dq = q[i - 1] + t * q[i];
                ll k = (N - qh[sz(qh) - 1]) / dq;
                ah.pb(k);
                ph.pb(ph[sz(ph) - 1] + k * dp);
                qh.pb(qh[sz(qh) - 1] + k * dq);
            }
        }
    }
    return {ah, ph, qh};
}

ll sum(ll p, ll q, ll N) {
    N++;
    vector<ll> ah, ph, qh;
    tie(ah, ph, qh) = hull(fraction(p, q), N);

    auto picks = [&](ll y1, ll y2, ll dx, ll a) {
        ll b = y1 + y2 + a + dx;
        ll A = (y1 + y2) * dx;
        return (A - b + 2) / 2 + b - (y2 + 1);
    };

    ll ans = 0;
    FOB (i, 1, sz(qh)) {
        ans += picks(ph[i - 1], ph[i], qh[i] - qh[i - 1], ah[i - 1]);
    }
    return ans - N;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll t;
    cin >> t;

    while (t--) {
        ll p, q, n;
        cin >> p >> q >> n;
        // t1 = p * sum_i=1^n i
        ll t1 = p * n * (n + 1) / 2;
        // t2 = q * sum_i=1^n floor(p * i / q)
        ll t2 = sum(p, q, n);
        t2 *= q;
        // rv = t1 - t2
        ll rv = t1 - t2;
        cout << rv << '\n';
    }

    return 0;
}