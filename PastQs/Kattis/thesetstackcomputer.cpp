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

    ll t;
    cin >> t;
    map<set<ll>, ll> ref;
    vector<set<ll>> r_inv;
    ref[{}] = 0;
    r_inv.pb({});
    while (t--) {
        ll n;
        cin >> n;
        stack<ll> stk;
        while (n--) {
            str move;
            cin >> move;
            if (move == "PUSH") {
                stk.push(0);
            } elif (move == "DUP") {
                stk.push(stk.top());
            } elif (move == "UNION") {
                ll al = stk.top();
                stk.pop();
                ll bl = stk.top();
                stk.pop();
                set<ll> &a = r_inv[al], &b = r_inv[bl];
                set<ll> c = a;
                c.insert(all(b));
                if (ref.find(c) == ref.end()) {
                    r_inv.pb(c);
                    ref[c] = sz(ref);
                }
                stk.push(ref[c]);
            } elif (move == "INTERSECT") {
                ll al = stk.top();
                stk.pop();
                ll bl = stk.top();
                stk.pop();
                set<ll> &a = r_inv[al], &b = r_inv[bl];
                set<ll> c;
                auto it = set_intersection(all(a), all(b), inserter(c, c.begin()));
                if (ref.find(c) == ref.end()) {
                    r_inv.pb(c);
                    ref[c] = sz(ref);
                }
                stk.push(ref[c]);
            } else {
                ll al = stk.top();
                stk.pop();
                ll bl = stk.top();
                stk.pop();
                set<ll> &b = r_inv[bl];
                set<ll> c = b;
                c.insert(al);
                if (ref.find(c) == ref.end()) {
                    r_inv.pb(c);
                    ref[c] = sz(ref);
                }
                stk.push(ref[c]);
            }
            ll rv = sz(r_inv[stk.top()]);
            cout << rv << '\n';
        }
        cout << "***\n";
    }

    return 0;
}