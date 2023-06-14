#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ld = long double;
using ch = char;
using str = string;
using ost = tree<str, null_type, less<str>, rb_tree_tag, tree_order_statistics_node_update>;

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

    vector<ost> trees(2);

    while (true) {
        ll q;
        cin >> q;
        if (q == 0) {
            break;
        } elif (q == 1) {
            str name;
            ll gender;
            cin >> name >> gender;
            gender--;
            trees[gender].insert(name);
        } elif (q == 2) {
            str name;
            cin >> name;
            trees[0].erase(name);
            trees[1].erase(name);
        } else {
            str lo, hi;
            ll gender;
            cin >> lo >> hi >> gender;
            gender--;
            ll rv;
            if (gender == -1) {
                rv = trees[0].order_of_key(hi) - trees[0].order_of_key(lo) + trees[1].order_of_key(hi) - trees[1].order_of_key(lo);
            } else {
                rv = trees[gender].order_of_key(hi) - trees[gender].order_of_key(lo);
            }
            cout << rv << '\n';
        }
    }

    return 0;
}