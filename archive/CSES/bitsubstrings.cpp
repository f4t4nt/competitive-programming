#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
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

void solve(int l, int r, str &s, vector<ll> &rv) {
    if (l + 1 == r) {
        rv[s[l] - '0']++;
        return;
    }
    int m = (l + r) / 2,
        d = 1 << (32 - __builtin_clz(r - l)),
        cnt = 0;
    vector<cd> a(d), b(d);
    for (int i = m - 1; i >= l; i--) {
        cnt += (s[i] == '1');
        a[cnt] += 1;
    }
    cnt = 0;
    for (int i = m; i < r; i++) {
        cnt += (s[i] == '1');
        b[cnt] += 1;
    }
    fft(a, false);
    fft(b, false);
    FOR (i, d) a[i] *= b[i];
    fft(a, true);
    FOR (i, min(d, (int) s.size() + 1)) rv[i] += (ll) round(a[i].real());
    solve(l, m, s, rv);
    solve(m, r, s, rv);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str s;
    cin >> s;
    int n = sz(s);
    vector<ll> rv(n + 1);
    solve(0, n, s, rv);
    FORE (x, rv) cout << x << ' ';
    cout << '\n';

    return 0;
}