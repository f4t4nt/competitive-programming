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
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)

struct Expr {
    vector<str> s;

    ll eval() {
        if (sz(s) == 3) {
            ll i = 0;
            while (true) {
                while (i < sz(s[0]) && s[1][i] != '=') {
                    i++;
                }
                ll lo = i;
                while (i < sz(s[0]) && s[1][i] == '=') {
                    i++;
                }
                ll hi = i;
                if (lo == hi) {
                    break;
                }
                Expr en = {{s[0].substr(lo, hi - lo)}},
                    ed = {{s[2].substr(lo, hi - lo)}};
                ll nn = en.eval(), nd = ed.eval();
                str post0 = s[0].substr(hi),
                    post1 = s[1].substr(hi),
                    post2 = s[2].substr(hi);
                str pre0 = s[0].substr(0, lo),
                    pre1 = s[1].substr(0, lo),
                    pre2 = s[2].substr(0, lo);
                assert(nn % nd == 0);
                str tmp = to_string(nn / nd);
                str filler = "";
                while (sz(filler) < sz(tmp)) {
                    filler += " ";
                }
                s[0] = pre0 + filler + post0;
                s[1] = pre1 + tmp + post1;
                s[2] = pre2 + filler + post2;
                i = lo;
            }
            s.pop_back();
        }
        if (sz(s) == 2) {
            ll i = 0;
            while (true) {
                while (i < sz(s[0]) && s[1][i] != '\\') {
                    i++;
                }
                ll lo = i;
                i += 2;
                while (i < sz(s[1]) && s[0][i] == '_') {
                    i++;
                }
                ll hi = i;
                if (lo + 2 == hi) {
                    break;
                }
                Expr es = {{s[1].substr(lo + 2, hi - lo - 2)}};
                ll ns = es.eval();
                str post0 = s[0].substr(hi),
                    post1 = s[1].substr(hi);
                str pre0 = s[0].substr(0, lo),
                    pre1 = s[1].substr(0, lo);
                str tmp = to_string((ll) sqrt(ns));
                str filler = "";
                while (sz(filler) < sz(tmp)) {
                    filler += " ";
                }
                s[0] = pre0 + filler + post0;
                s[1] = pre1 + tmp + post1;
                i = lo;
            }
            s.erase(s.begin());
        }
        istringstream iss(s[0]);
        vector<str> ref;
        str x;
        while (iss >> x) {
            ref.pb(x);
        }
        FOR (i, sz(ref)) {
            if (ref[i] == "*") {
                ref[i - 1] = to_string(stoll(ref[i - 1]) * stoll(ref[i + 1]));
                ref.erase(ref.begin() + i);
                ref.erase(ref.begin() + i);
                i--;
            }
        }
        FOR (i, sz(ref)) {
            if (ref[i] == "-") {
                ref[i - 1] = to_string(stoll(ref[i - 1]) - stoll(ref[i + 1]));
                ref.erase(ref.begin() + i);
                ref.erase(ref.begin() + i);
                i--;
            } elif (ref[i] == "+") {
                ref[i - 1] = to_string(stoll(ref[i - 1]) + stoll(ref[i + 1]));
                ref.erase(ref.begin() + i);
                ref.erase(ref.begin() + i);
                i--;
            }
        }
        assert(sz(ref) == 1);
        return stoll(ref[0]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str line;
    getline(cin, line);
    istringstream iss(line);
    ll r, c;
    iss >> r >> c;
    vector<str> lines(r);
    FOR (i, r) {
        getline(cin, lines[i]);
    }
    Expr e = {lines};
    cout << e.eval() << '\n';

    return 0;
}