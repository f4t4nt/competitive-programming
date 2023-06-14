#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ch = char;
using str = string;

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

ll pows10[] = {1, 10, 100, 1000, 10000, 100000};

ll eval(vector<str> ref) {
    ll rv = 0;
    FORE (x, ref) {
        rv += pows10[x[0] - 'A'];
        FOB (i, 1, sz(x)) {
            rv -= pows10[x[i] - 'A'];
        }
    }
    return rv;
}

vector<str> vec(str &s) {
    vector<str> ref(1);
    ref[0] += s[0];
    FOB (i, 1, sz(s)) {
        if (s[i] >= ref.back()[0]) {
            ref.pb("");
        }
        ref.back() += s[i];
    }
    return ref;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        str s;
        cin >> s;
        ll n = sz(s);
        flip(s);
        vector<ll> lo(5, n), hi(5, -1);
        FOR (i, n) {
            lo[s[i] - 'A'] = min(lo[s[i] - 'A'], i);
            hi[s[i] - 'A'] = max(hi[s[i] - 'A'], i);
        }
        ll rv = eval(vec(s));
        FOR (i, 5) {
            if (lo[i] == n) {
                continue;
            }
            for (ch c = 'A'; c <= 'E'; c++) {
                str tmp = s;
                tmp[lo[i]] = c;
                rv = max(rv, eval(vec(tmp)));
                tmp = s;
                tmp[hi[i]] = c;
                rv = max(rv, eval(vec(tmp)));
            }
        }
        cout << rv << '\n';
    }

    return 0;
}