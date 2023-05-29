#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (int) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(int x = 0; x < (int) e; x++)
#define FORR(x, e) for(int x = (int) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(int x = 0; x < (int) e; x += (int) i)
#define FOBI(x, b, e, i) for(int x = (int) b; x < (int) e; x += (int) i)
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, l, h;
    cin >> n >> l >> h;
    vector<ll> a(n);
    FOR (i, n) {
        cin >> a[i];
    }
    ll lo = n, hi = -n;
    FOB (k, l, h + 1) {
        vector<ll> seg(n / k + 2);
        FOR (i, n) {
            seg[i / k] += a[i];
        }
        ll cur = 0;
        FOR (j, sz(seg)) {
            if (seg[j] > 0) {
                cur++;
            }
        }
        lo = min(lo, cur);
        hi = max(hi, cur);
        FOR (i, k - 1) {
            ll pos = k - i - 1;
            while (pos < n) {
                seg[pos / k] -= a[pos];
                seg[pos / k + 1] += a[pos];
                pos += k;
            }
            cur = 0;
            FOR (j, sz(seg)) {
                if (seg[j] > 0) {
                    cur++;
                }
            }
            lo = min(lo, cur);
            hi = max(hi, cur);
        }
    }
    cout << lo << ' ' << hi << '\n';

    return 0;
}