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

struct SegTreeLazy {
    ll n;
    vector<ll> data, lazy;
    SegTreeLazy (ll n) :
        n(n),
        data(4 * n, 0),
        lazy(4 * n, 0) {}
    // [lo, hi)
    void update(ll lo, ll hi, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        if (lazy[i] != 0) {
            data[i] += (r - l) * lazy[i];
            if (r - l > 1) {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if (lo <= l && r <= hi) {
            data[i] += (r - l) * val;
            if (r - l > 1) {
                lazy[2 * i] += val;
                lazy[2 * i + 1] += val;
            }
            return;
        }
        if (r <= lo || hi <= l) {
            return;
        }
        ll m = (l + r) / 2;
        update(lo, hi, val, 2 * i, l, m);
        update(lo, hi, val, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    ll query(ll lo, ll hi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        if (lazy[i] != 0) {
            data[i] += (r - l) * lazy[i];
            if (r - l > 1) {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if (lo <= l && r <= hi) {
            return data[i];
        }
        if (r <= lo || hi <= l) {
            return 0;
        }
        ll m = (l + r) / 2;
        return query(lo, hi, 2 * i, l, m) + query(lo, hi, 2 * i + 1, m, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    str s;
    cin >> s;
    // +1 for ( and -1 for )
    SegTreeLazy st(n);
    FOR (i, n) {
        if (s[i] == '(') {
            st.update(i, i + 1, 1);
        } else {
            st.update(i, i + 1, -1);
        }
    }
    // locations of (( and ))
    // store idx of second
    set<ll> lo, hi;
    FOB (i, 1, n) {
        if (s[i - 1] == '(' && s[i] == '(') {
            lo.insert(i);
        } elif (s[i - 1] == ')' && s[i] == ')') {
            hi.insert(i);
        }
    }
    while (q--) {
        ll x;
        cin >> x;
        x--;
        if (s[x] == '(') {
            s[x] = ')';
            st.update(x, x + 1, -2);
            if (x > 0 && s[x - 1] == '(') {
                lo.erase(x);
            }
            if (x < n - 1 && s[x + 1] == '(') {
                lo.erase(x + 1);
            }
            if (x > 0 && s[x - 1] == ')') {
                hi.insert(x);
            }
            if (x < n - 1 && s[x + 1] == ')') {
                hi.insert(x + 1);
            }
        } else {
            s[x] = '(';
            st.update(x, x + 1, 2);
            if (x > 0 && s[x - 1] == ')') {
                hi.erase(x);
            }
            if (x < n - 1 && s[x + 1] == ')') {
                hi.erase(x + 1);
            }
            if (x > 0 && s[x - 1] == '(') {
                lo.insert(x);
            }
            if (x < n - 1 && s[x + 1] == '(') {
                lo.insert(x + 1);
            }
        }
        bool ok = s[0] == '(' && s[n - 1] == ')';
        // find the last ))
        if (!hi.empty()) {
            ll idx = *hi.rbegin();
            if (st.query(idx + 1, n) != 0) {
                ok = false;
            }
            // check everything preceding has even sum
            if (st.query(0, idx - 1) % 2 != 0) {
                ok = false;
            }
        } elif (st.query(0, n) != 0) {
            ok = false;
        }
        // find the first ((
        if (!lo.empty()) {
            ll idx = *lo.begin();
            if (st.query(0, idx - 1) != 0) {
                ok = false;
            }
            // check everything following has even sum
            if (st.query(idx + 1, n) % 2 != 0) {
                ok = false;
            }
        } elif (st.query(0, n) != 0) {
            ok = false;
        }
        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        // cout << s << ' ' << st.query(0, n) << '\n';
    }

    return 0;
}