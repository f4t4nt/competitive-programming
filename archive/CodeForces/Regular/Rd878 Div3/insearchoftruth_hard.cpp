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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll wtf = 837183;
    vector<ll> idfk(wtf);
    iota(all(idfk), 1);
    random_shuffle(all(idfk));

    ll total = 0;
    ll x, max_x = 0;
    ll BASE = 250;
    FOR (i, 500) {
        x = idfk[total % wtf];
        cin >> x;
        ll del = rand() + 1;
        cout << "+ " << del << endl;
        total += del;
        max_x = max(max_x, x);
    }

    x = idfk[total % wtf];
    cin >> x;
    total = 0;
    map<ll, ll> pos;
    pos[x] = 0;
    FOR (i, BASE) {
        cout << "+ 1" << endl;
        total++;
        x = idfk[total % wtf];
        cin >> x;
        if (pos.count(x)) {
            cout << "! " << total << endl;
            return 0;
        }
        pos[x] = total;
    }
    FOR (i, BASE) {
        if (i == 0) {
            cout << "+ " << max_x << endl;
            total += max_x;
        } else {
            cout << "+ " << BASE << endl;
            total += BASE;
        }
        x = idfk[total % wtf];
        cin >> x;
        if (pos.count(x)) {
            ll rv = total - pos[x];
            // assert(rv == wtf);
            cout << "! " << rv << endl;
            return 0;
        }
        pos[x] = total;
    }

    assert(false);
    return 0;
}