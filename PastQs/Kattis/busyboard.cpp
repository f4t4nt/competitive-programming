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

void read_board(ll &n, ll &m, bool &not_empty, vector<vector<bool>> &board) {
    FOR (i, n) {
        FOR (j, m) {
            ch c;
            cin >> c;
            board[i][j] = c == 'O';
            not_empty |= board[i][j];
        }
    }
}

void parse_board(ll &n, ll &m,
    map<ll, ll> &row_counts,
    map<ll, ll> &col_counts,
    vector<vector<ll>> &types,
    vector<vector<bool>> &board)
{
    FOR (i, n) {
        FOR (j, m) {
            if (!board[i][j]) {
                row_counts[i]++;
                col_counts[j]++;
                types[i][j] = 1;
            }
        }
    }

    FORE (el_i, row_counts) {
        ll i, i_cnt;
        tie(i, i_cnt) = el_i;
        FORE (el_j, col_counts) {
            ll j, j_cnt;
            tie(j, j_cnt) = el_j;
            if (board[i][j]) {
                continue;
            }
            if (i_cnt > 1 || j_cnt > 1) {
                types[i][j] = 2;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<vector<bool>> initial(n, vector<bool>(m)), target = initial;
    bool not_empty_0 = false, not_empty_1 = false;
    read_board(n, m, not_empty_0, initial);
    read_board(n, m, not_empty_1, target);

    if (not_empty_0 != not_empty_1) {
        cout << 0 << '\n';
        return 0;
    }

    map<ll, ll> row_counts_0, col_counts_0, row_counts_1, col_counts_1;
    vector<vector<ll>> types_0(n, vector<ll>(m)), types_1 = types_0;
    parse_board(n, m, row_counts_0, col_counts_0, types_0, initial);
    parse_board(n, m, row_counts_1, col_counts_1, types_1, target);

    vector<bool> banned_rows(n), banned_cols(m);

    bool has_free = false, has_extra = false;
    FOR (i, n) {
        FOR (j, m) {
            if (types_1[i][j] == 1) {
                has_free = true;
            }
        }
    }

    FOR (i, n) {
        if (row_counts_1[i] > 1) {
            banned_rows[i] = true;
            continue;
        }
        FOR (j, m) {
            if (col_counts_1[j] > 1) {
                banned_cols[j] = true;
                continue;
            }
            if (types_0[i][j] == 0) {
                has_extra = true;
            }
        }
    }

    FOR (i, n) {
        FOR (j, m) {
            if (types_0[i][j] != 2 && types_1[i][j] == 2) {
                cout << 0 << '\n';
                return 0;
            }
            if (types_0[i][j] != 0 && types_1[i][j] == 0) {
                if (!has_free || !has_extra || (banned_rows[i] && banned_cols[j])) {
                    cout << 0 << '\n';
                    return 0;
                }
            }
        }
    }

    cout << 1 << '\n';

    return 0;
}