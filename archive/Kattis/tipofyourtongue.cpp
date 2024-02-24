#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

const ll ALPHA = 26;
const ll MOD = 1e15 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n, q; cin >> n >> q;
    vector<str> words(n);
    for (str &w : words) cin >> w;
    // <len, hash> : count
    map<pll, ll> pres, sufs;
    map<tuple<ll, ll, ll>, ll> combos;
    for (str &w : words) {
        ll len = 0, pre = 0, suf = 0, lo = 0, hi = w.size() - 1;
        while (len != w.size()) {
            len++;
            pre = (pre * ALPHA + w[lo] - 'a' + 1) % MOD;
            suf = (suf * ALPHA + w[hi] - 'a' + 1) % MOD;
            pres[{len, pre}]++;
            sufs[{len, suf}]++;
            combos[{len, pre, suf}]++;
            lo++, hi--;
        }
    }
    while (q--) {
        str op, pre_s, suf_s;
        cin >> op >> pre_s >> suf_s;
        ll len = pre_s.size(), pre = 0, suf = 0, lo = 0, hi = len - 1;
        while (hi >= 0) {
            pre = (pre * ALPHA + pre_s[lo] - 'a' + 1) % MOD;
            suf = (suf * ALPHA + suf_s[hi] - 'a' + 1) % MOD;
            lo++, hi--;
        }
        if (op == "AND") {
            cout << combos[{len, pre, suf}] << '\n';
        } else if (op == "OR") {
            cout << pres[{len, pre}] + sufs[{len, suf}] - combos[{len, pre, suf}] << '\n';
        } else if (op == "XOR") {
            cout << pres[{len, pre}] + sufs[{len, suf}] - 2 * combos[{len, pre, suf}] << '\n';
        } else assert(false);
    }
}
/*
4 4
cat
catcat
octal
occidental
AND cat cat
OR oc at
AND ca at
XOR oc al

2
4
2
0
*/