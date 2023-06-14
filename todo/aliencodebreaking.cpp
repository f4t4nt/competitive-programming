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

// https://open.kattis.com/problems/aliencodebreaking

constexpr ll MOD = 1 << 20;
constexpr ll BASE = 27;

map<ll, vector<ll>> pow_10;

vector<ll> str_to_vec(str &s) {
    vector<ll> rv(sz(s));
    FOR (i, sz(s)) {
        if (s[i] == ' ') {
            rv[i] = BASE - 1;
        } else {
            rv[i] = s[i] - 'A';
        }
    }
    return rv;
}

str vec_to_str(vector<ll> &v) {
    str rv;
    FOR (i, sz(v)) {
        if (v[i] == BASE - 1) {
            rv += ' ';
        } else {
            rv += 'A' + v[i];
        }
    }
    return rv;
}

vector<ll> pad_vec(vector<ll> &v1, vector<ll> &v2) {
    vector<ll> rv(sz(v1));
    FOR (i, sz(v1)) {
        rv[i] = (v1[i] + v2[i]) % BASE;
    }
    return rv;
}

vector<ll> unwrap_digits(ll x) {
    vector<ll> rv;
    while (x) {
        rv.pb(x % 10);
        x /= 10;
    }
    return rv;
}

vector<ll> get_pow_10(ll x) {
    if (pow_10.count(x)) {
        return pow_10[x];
    }
    if (x == 0) {
        return {1};
    }
    if (x == 1) {
        return {10};
    }
    if (x % 2 == 0) {
        vector<ll> tmp = get_pow_10(x / 2);
        return pow_10[x] = mul_vec(tmp, tmp);
    } else {
        vector<ll> tmp = get_pow_10(x - 1);
        return pow_10[x] = mul_vec(tmp, {10});
    }
}

vector<ll> base10_to_27(vector<ll> &b10, ll lo, ll hi) {
    if (lo == hi) {
        return {b10[lo]};
    }
    ll mid = lo + (hi - lo + 1) / 2;
    vector<ll> left = base10_to_27(b10, lo, mid - 1),
        right = base10_to_27(b10, mid, hi);
    vector<ll> pad = get_pow_10(hi - mid + 1);
    return add_vec(mul_vec(left, pad), right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<ll> ref(1);
    do {
        ref.pb((33 * ref.back() + 1) % MOD);
    } while (ref.back() != 0);
    ref.pop_back();

    str s;
    getline(cin, s);
    ll n, x;
    istringstream iss(s);
    iss >> n >> x;
    getline(cin, s);
    vector<ll> v1 = str_to_vec(s);
    vector<ll> col_sum(x);
    FOR (i, x) {
        col_sum[0] = (col_sum[0] + ref[(i * x + 1) % sz(ref)]) % MOD;
    }
    FOB (i, 1, x) {
        col_sum[i] = (33 * col_sum[i - 1] + x) % MOD;
    }
    vector<ll> b10;
    FOR (i, sz(col_sum)) {
        vector<ll> tmp = unwrap_digits(col_sum[i]);
        while (!tmp.empty()) {
            b10.pb(tmp.back());
            tmp.pop_back();
        }
    }
    flip(b10);

    vector<ll> v2 = base10_to_27(b10, 0, sz(b10) - 1);
    vector<ll> rv_v = pad_vec(v1, v2);
    str rv = vec_to_str(rv_v);
    cout << rv << '\n';

    return 0;
}