#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
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

// ll n = sz(s), n2 = 2 << (ll) ceil(log2(n));
// vector<cd> a(n2), b(n2);
// fft(a, false);
// fft(b, false);
// FOR (i, n) a[i] *= b[i];
// fft(a, true);
 
void fft(vector<cd> &a, bool inv) {
    ll n = sz(a);
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (ll len = 2; len <= n; len <<= 1) {
        ld ang = 2 * M_PI / len * (inv ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (ll i = 0; i < n; i += len) {
            cd w(1);
            for (ll j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (inv) {
        FORE (x, a) {
            x /= n;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m, k, maxn = 1 << 19;
    cin >> k >> n >> m;
    vector<cd> a(maxn), b(maxn);
    FOR (i, n) {
        ll x;
        cin >> x;
        a[x] += 1;
    }
    FOR (i, m) {
        ll x;
        cin >> x;
        b[x] += 1;
    }
    fft(a, false);
    fft(b, false);
    FOR (i, maxn) {
        a[i] *= b[i];
    }
    fft(a, true);
    vector<ll> rv(maxn);
    FOR (i, maxn) {
        rv[i] = round(a[i].real());
    }
    FOB (i, 2, 2 * k + 1) {
        cout << rv[i] << ' ';
    }
    cout << '\n';
 
    return 0;
}