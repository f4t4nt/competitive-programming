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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

// https://open.kattis.com/problems/evensubstrings

str s;
constexpr ll ALPHA = 1 << 6;

struct SegTree {
    ll n;
    // prefix, net xor
    vector<pair<vector<ll>, ll>> data;
    SegTree (ll n) :
        n(n),
        data(4 * n, {vector<ll>(ALPHA), 0})
    {
        init();
    }
    pair<vector<ll>, ll> init(bool check = false, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        pair<vector<ll>, ll> rv = {vector<ll>(ALPHA), 0};
        if (r - l == 1) {
            rv.second = 1 << (s[l] - 'a');
            rv.first[rv.second] = 1;
        } else {
            ll m = (l + r) / 2;
            rv = init(check, 2 * i, l, m);
            auto right = init(check, 2 * i + 1, m, r);
            FOR (j, ALPHA) {
                rv.first[j ^ rv.second] += right.first[j];
            }
            rv.second ^= right.second;
        }
        assert(!check || rv == data[i]);
        data[i] = rv;
        return rv;
    }
    bool update(ll idx, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        if (idx == l && r == idx + 1) {
            vector<ll> tmp = data[i].first;
            FOR (j, ALPHA) {
                data[i].first[j ^ val] = tmp[j];
            }
            data[i].second ^= val;
            return true;
        }
        if (r <= idx || idx < l) {
            return false;
        }
        ll m = (l + r) / 2;
        bool rv = false;
        if (update(idx, val, 2 * i, l, m)) {
            rv = true;
        } elif (update(idx, val, 2 * i + 1, m, r)) {
            rv = true;
        }
        if (rv) {
            data[i].first = data[2 * i].first;
            FOR (j, ALPHA) {
                data[i].first[j ^ data[2 * i].second] += data[2 * i + 1].first[j];
            }
            data[i].second = data[2 * i].second ^ data[2 * i + 1].second;
        }
        return rv;
    }
    // [lo, hi)
    pair<vector<ll>, ll> query(ll lo, ll hi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        if (lo <= l && r <= hi) {
            return data[i];
        }
        if (r <= lo || hi <= l) {
            return {vector<ll>(ALPHA), 0};
        }
        ll m = (l + r) / 2;
        auto rv = query(lo, hi, 2 * i, l, m),
            right = query(lo, hi, 2 * i + 1, m, r);
        FOR (j, ALPHA) {
            rv.first[j ^ rv.second] += right.first[j];
        }
        rv.second ^= right.second;
        return rv;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> s;
    SegTree st(sz(s));
    ll q;
    cin >> q;
    while (q--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll l, r;
            cin >> l >> r;
            l--;
            vector<ll> tmp = st.query(l, r).first;
            tmp[0]++;
            ll rv = 0;
            FORE (x, tmp) {
                rv += x * (x - 1) / 2;
            }
            cout << rv << '\n';
        } else {
            ll i;
            ch x;
            cin >> i >> x;
            i--;
            st.update(i, (1 << (x - 'a')) ^ (1 << (s[i] - 'a')));
            s[i] = x;
            // st.init(true);
        }
    }

    return 0;
}