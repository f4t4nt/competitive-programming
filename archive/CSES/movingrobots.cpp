#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

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

ll dx[] = {-1, 1, 0, 0};
ll dy[] = {0, 0, -1, 1};

void get_robot_p(ll k, vector<vector<ld>> &state0) {
    while (k--) {
        vector<vector<ld>> state1(8, vector<ld>(8));
        FOR (i, 8) {
            FOR (j, 8) {
                vector<pair<ld, ld>> moves;
                FOR (d, 4) {
                    ll x = i + dx[d];
                    ll y = j + dy[d];
                    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                        moves.pb({x, y});
                    }
                }
                FORE (move, moves) {
                    state1[move.first][move.second] += state0[i][j] / sz(moves);
                }
            }
        }
        state0 = state1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll k;
    cin >> k;
    vector<vector<ld>> state0, ref(8, vector<ld>(8, 1));
    FOR (i, 8) {
        FOR (j, 8) {
            state0 = vector<vector<ld>>(8, vector<ld>(8));
            state0[i][j] = 1;
            get_robot_p(k, state0);
            FOR (i, 8) {
                FOR (j, 8) {
                    ref[i][j] *= 1 - state0[i][j];
                }
            }
        }
    }
    ld rv = 0;
    FOR (i, 8) {
        FOR (j, 8) {
            rv += ref[i][j];
        }
    }
    cout << fixed << setprecision(6) << rv << '\n';

    return 0;
}