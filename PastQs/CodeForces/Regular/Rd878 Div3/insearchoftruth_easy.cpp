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

    ll x, total = 0;
    cin >> x;
    map<ll, ll> pos;
    pos[x] = 0;
    FOR (i, 1000) {
        cout << "+ 1" << endl;
        total++;
        cin >> x;
        if (pos.count(x)) {
            cout << "! " << total << endl;
            return 0;
        }
        pos[x] = total;
    }
    FOR (i, 1000) {
        cout << "+ 1000" << endl;
        total += 1000;
        cin >> x;
        if (pos.count(x)) {
            cout << "! " << total - pos[x] << endl;
            return 0;
        }
        pos[x] = total;
    }

    assert(false);
    return 0;
}