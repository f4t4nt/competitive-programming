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

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

vector<ll> gen_test(ll n, vector<ll> s, bool print = false) {
    ll x = n, t = 0;
    set<ll> tmp;
    vector<ll> rv(n);
    FOR (i, n) {
        if (print) {
            cout << x << ' ';
        }
        rv[i] = x;
        tmp.insert(x);
        x = s[t] - x;
        t = 1 - t;
    }
    assert(sz(tmp) == n);
    if (print) {
        cout << endl;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t, tmp;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        if (n == 2) {
            cout << "! 1 2 2 1" << endl;
            cout.flush();
            cin >> tmp;
            if (tmp == -2) { // WA
                return 0;
            }
            continue;
        }
        vector<ll> ref;
        cout << "+ " << n + 1 << endl;
        cout.flush();
        cin >> tmp;
        if (tmp == -2) { // WA
            return 0;
        }
        if (n % 2 == 0) {
            cout << "+ " << n - 1 << endl;
            cout.flush();
            cin >> tmp;
            if (tmp == -2) { // WA
                return 0;
            }
            ref = gen_test(n, {n + 1, n - 1});
        } else {
            cout << "+ " << n << endl;
            cout.flush();
            cin >> tmp;
            if (tmp == -2) { // WA
                return 0;
            }
            ref = gen_test(n, {n + 1, n});
        }
        ll max_d = 0, max_d_i = 0;
        vector<ll> d0(n), di(n);
        FOB (i, 1, n) {
            cout << "? " << 1 << ' ' << i + 1 << endl;
            cout.flush();
            cin >> d0[i];
            if (d0[i] == -2) { // WA
                return 0;
            }
            while (d0[i] == -1) { // TLE
                continue;
            }
            if (d0[i] > max_d) {
                max_d = d0[i];
                max_d_i = i;
            }
        }
        while (max_d < (n + 1) / 2) { // TLE
            continue;
        }
        di[0] = d0[max_d_i];
        FOR (i, n) {
            if (i == 0 || i == max_d_i) {
                continue;
            }
            cout << "? " << max_d_i + 1 << ' ' << i + 1 << endl;
            cout.flush();
            cin >> di[i];
            if (di[i] == -2) { // WA
                return 0;
            }
            while (di[i] == -1) { // TLE
                continue;
            }
        }
        vector<ll> rv_1(n), rv_2(n);
        FOR (i, n) {
            while (di[i] < 0 || di[i] > n - 1) { // TLE
                continue;
            }
            rv_1[i] = ref[di[i]];
            rv_2[i] = ref[n - 1 - di[i]];
        }
        cout << "! ";
        FORE (x, rv_1) {
            cout << x << ' ';
        }
        FORE (x, rv_2) {
            cout << x << ' ';
        }
        cout << endl;
        cout.flush();
        cin >> tmp;
        if (tmp == -2) { // WA
            return 0;
        }
    }

    return 0;
}