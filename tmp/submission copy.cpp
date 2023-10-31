#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

// imma show YOU how great i am.

// king
ll kdx[] = {1, 1, 1, 0, 0, -1, -1, -1},
    kdy[] = {1, 0, -1, 1, -1, 1, 0, -1};
// knight
ll ndx[] = {2, 2, -2, -2, 1, 1, -1, -1},
    ndy[] = {1, -1, 1, -1, 2, -2, 2, -2};

void apply_K(vector<vector<bool>> &open, vector<vector<bool>> &ok, ll x, ll y) {
    FOR (i, 8) {
        ll nx = x + kdx[i], ny = y + kdy[i];
        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
            ok[nx][ny] = false;
        }
    }
}

// move pc by dx, dy until hits edge of board or unopen slot
void streak(vector<vector<bool>> &open, vector<vector<bool>> &ok, ll x, ll y, ll dx, ll dy) {
    assert(dx != 0 || dy != 0);
    x += dx, y += dy;
    while (x >= 0 && x < 8 && y >= 0 && y < 8 && open[x][y]) {
        ok[x][y] = false;
        x += dx, y += dy;
    }
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        ok[x][y] = false;
    }
}

void apply_R(vector<vector<bool>> &open, vector<vector<bool>> &ok, ll x, ll y) {
    streak(open, ok, x, y, 1, 0); // right
    streak(open, ok, x, y, -1, 0); // left
    streak(open, ok, x, y, 0, 1); // up
    streak(open, ok, x, y, 0, -1); // down
}

void apply_B(vector<vector<bool>> &open, vector<vector<bool>> &ok, ll x, ll y) {
    streak(open, ok, x, y, 1, 1); // up-right
    streak(open, ok, x, y, -1, 1); // up-left
    streak(open, ok, x, y, 1, -1); // down-right
    streak(open, ok, x, y, -1, -1); // down-left
}

void apply_Q(vector<vector<bool>> &open, vector<vector<bool>> &ok, ll x, ll y) {
    apply_R(open, ok, x, y);
    apply_B(open, ok, x, y);      
}

void apply_N(vector<vector<bool>> &open, vector<vector<bool>> &ok, ll x, ll y) {
    FOR (i, 8) {
        ll nx = x + ndx[i], ny = y + ndy[i];
        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
            ok[nx][ny] = false;
        }
    }
}

bool is_won(ll i, vector<pair<ch, ll>> &pcs) {
    // i = [pcs2pos][pc1pos][kpos][my move?]
    ll my_move = i & 1,
        kpos = (i >> 1) & ((1 << 6) - 1),
        pc1pos = (i >> 7) & ((1 << 6) - 1),
        pc2pos = (i >> 13) & ((1 << 6) - 1);
    if (my_move) {
        return false;
    }
    if (kpos == pc1pos || kpos == pc2pos || pc1pos == pc2pos) {
        return false;
    }
    assert(pcs[0].first == 'k');
    ch pc1 = pcs[1].first, pc2 = pcs[2].first;
    ll kx = kpos / 8, ky = kpos % 8,
        pc1x = pc1pos / 8, pc1y = pc1pos % 8,
        pc2x = pc2pos / 8, pc2y = pc2pos % 8;
    if (pc1 == 'K' && abs(kx - pc1x) <= 1 && abs(ky - pc1y) <= 1) {
        return false;
    }
    if (pc2 == 'K' && abs(kx - pc2x) <= 1 && abs(ky - pc2y) <= 1) {
        return false;
    }
    vector<vector<bool>> open(8, vector<bool>(8, true)), ok = open;
    open[kx][ky] = false, open[pc1x][pc1y] = false, open[pc2x][pc2y] = false;

    if (pc1 == 'K') apply_K(open, ok, pc1x, pc1y);
    elif (pc1 == 'R') apply_R(open, ok, pc1x, pc1y);
    elif (pc1 == 'B') apply_B(open, ok, pc1x, pc1y);
    elif (pc1 == 'Q') apply_Q(open, ok, pc1x, pc1y);
    elif (pc1 == 'N') apply_N(open, ok, pc1x, pc1y);

    if (pc2 == 'K') apply_K(open, ok, pc2x, pc2y);
    elif (pc2 == 'R') apply_R(open, ok, pc2x, pc2y);
    elif (pc2 == 'B') apply_B(open, ok, pc2x, pc2y);
    elif (pc2 == 'Q') apply_Q(open, ok, pc2x, pc2y);
    elif (pc2 == 'N') apply_N(open, ok, pc2x, pc2y);

    if (ok[kx][ky]) {
        return false;
    }
    FOR (i, 8) {
        ll nx = kx + kdx[i], ny = ky + kdy[i];
        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && ok[nx][ny]) {
            return false;
        }
    }
    return true;
}

vector<str> show_board(ll i, vector<pair<ch, ll>> &pcs) {
    vector<str> rv, board(8, "........");
    ll my_move = i & 1,
        kpos = (i >> 1) & ((1 << 6) - 1),
        pc1pos = (i >> 7) & ((1 << 6) - 1),
        pc2pos = (i >> 13) & ((1 << 6) - 1);
    if (my_move) {
        rv.pb("my move");
    } else {
        rv.pb("his move");
    }
    if (kpos == pc1pos || kpos == pc2pos || pc1pos == pc2pos) {
        rv.pb("OVERLAPPING PIECES");
    }
    assert(pcs[0].first == 'k');
    ch pc1 = pcs[1].first, pc2 = pcs[2].first;
    ll kx = kpos / 8, ky = kpos % 8,
        pc1x = pc1pos / 8, pc1y = pc1pos % 8,
        pc2x = pc2pos / 8, pc2y = pc2pos % 8;
    if (pc1 == 'K' && abs(kx - pc1x) <= 1 && abs(ky - pc1y) <= 1) {
        rv.pb("k CONFLICT WITH pc1 K");
    }
    if (pc2 == 'K' && abs(kx - pc2x) <= 1 && abs(ky - pc2y) <= 1) {
        rv.pb("k CONFLICT WITH pc2 K");
    }
    board[kx][ky] = 'k', board[pc1x][pc1y] = pc1, board[pc2x][pc2y] = pc2;
    FOR (i, 8) {
        rv.pb(board[i]);
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<str> board(8);
    FOR (i, 8) {
        cin >> board[i];
    }
    vector<pair<ch, ll>> pcs;
    FOR (i, 8) {
        FOR (j, 8) {
            if (board[i][j] != '.') {
                pcs.pb({board[i][j], i * 8 + j});
            }
        }
    }
    rsort(pcs); // k first
    assert(sz(pcs) == 3);
    // {0 = no win, 1 = win}
    bitset<1 << 19> results;
    FOR (i, 1 << 19) {
        results[i] = is_won(i, pcs);
        if (results[i]) {
            auto board = show_board(i, pcs);
            FORE (line, board) {
                cout << line << '\n';
            }
            cout << '\n';
        }
    }
    // what states lead to this state?
    vector<vector<ll>> adj(1 << 19);
    

    return 0;
}