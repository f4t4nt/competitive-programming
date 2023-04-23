#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
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

map<ch, ll> brack_val = {
    {'?', 0},
    {'(', 1},
    {')', -1},
    {'[', 2},
    {']', -2},
    {'{', 3},
    {'}', -3},
    {'<', 4},
    {'>', -4}
};

map<ch, ch> brack_inv = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'},
    {'<', '>'},
    {')', '('},
    {']', '['},
    {'}', '{'},
    {'>', '<'},
    {'?', '?'}
};

ch brack_inv_val(ll k) {
    FORE (x, brack_val) {
        if (x.second == k) {
            return x.first;
        }
    }
    assert(false);
}

void normalize(str &s) {
    flip(s);
    FORE (c, s) {
        c = brack_inv[c];
    }
}

void gen(ll i, str &s, stack<ll> open, map<ll, ll> &ref) {
    if (i == sz(s)) {
        ll val = 0;
        while (!open.empty()) {
            val *= 5;
            val += open.top();
            open.pop();
        }
        ref[val]++;
        return;
    }
    if (s[i] == '?') {
        for (auto c : {'(', '[', '{', '<'}) {
            s[i] = c;
            open.push(brack_val[c]);
            gen(i + 1, s, open, ref);
            open.pop();
        }
        if (!open.empty()) {
            ll tmp = open.top();
            s[i] = brack_inv_val(-tmp);
            open.pop();
            gen(i + 1, s, open, ref);
            open.push(tmp);
        }
        s[i] = '?';
    } else {
        if (brack_val[s[i]] > 0) {
            open.push(brack_val[s[i]]);
        } elif (!open.empty() && open.top() + brack_val[s[i]] == 0) {
            open.pop();
        } else {
            return;
        }
        gen(i + 1, s, open, ref);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str s0;
    cin >> s0;
    str s1 = s0.substr(sz(s0) / 2);
    normalize(s1);
    s0 = s0.substr(0, sz(s0) / 2);

    map<ll, ll> ref0, ref1;
    gen(0, s0, stack<ll>(), ref0);
    gen(0, s1, stack<ll>(), ref1);

    ll rv = 0;
    FORE (x, ref0) {
        rv += x.second * ref1[x.first];
    }
    cout << rv << '\n';

    return 0;
}