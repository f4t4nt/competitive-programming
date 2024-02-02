#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

// vector<cd> a(n2), b(n2);
// ...init a, b...
// fft(a, false);
// fft(b, false);
// FOR (i, n) a[i] *= b[i];
// fft(a, true);

void fft(vector<cd> &a, bool inv) {
    int n = sz(a);
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ld ang = 2 * M_PI / len * (inv ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (inv) FORE (x, a) x /= n;
}

const ll MAXN = 1 << 18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // FOR (_, 1e2) {
    //     ll n = rng() % 20 + 1;
    //     vector<ll> as(n);
    //     FOR (i, n) as[i] = rng() % 21 - 10;
    //     ll rv = 0;
    //     FOR (i, n) FOR (j, n) FOR (k, n) {
    //         if (i != j && j != k && i != k &&
    //             as[i] + as[j] == as[k]) rv++;
    //     }
    //     cout << "--\n";
    //     cout << n << '\n';
    //     FOR (i, n) cout << as[i] << ' ';
    //     cout << '\n';
    //     cout << "--\n";
    //     cout << rv << '\n';
    // }

    ll n; cin >> n;
    vector<ll> as(n);
    map<ll, ll> cnts;
    vector<cd> x(MAXN), y(MAXN), z(MAXN);
    FOR (i, n) {
        ll a; cin >> a;
        as[i] = a;
        cnts[a]++;
        if (a) {
            x[a + 5e4] += 1; // x = y
            z[5e4 - a] += 1;
        }
    }
    fft(x, false);
    fft(z, false);
    FOR (i, MAXN) x[i] *= x[i];
    FOR (i, MAXN) x[i] *= z[i];
    fft(x, true);
    ll rv = round(x[15e4].real()), neg = 0;
    for (auto [a, cnt] : cnts) {
        if (a == 0) rv += cnt * (cnt - 1) * (cnt - 2);
        else {
            rv += 2 * cnt * (cnt - 1) * cnts[0];
            rv -= cnt * cnts[2 * a];
            neg += cnt * cnts[-a];
        }
    }
    rv += neg * cnts[0];
    cout << rv << '\n';

    return 0;
}