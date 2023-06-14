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

void print_board(vector<str> &board) {
    FORE (s, board) {
        cout << s << '\n';
    }
    cout << '\n';
    return;
}

ll dfs(ll idx, vector<ll> szs, vector<str> board, vector<str> &board0) {
    if (idx == sz(szs)) {
        bool ok = true;
        FOR (i, sz(board)) {
            FOR (j, sz(board)) {
                ok &= (board[i][j] != 'O');
                if (!ok) break;
            }
            if (!ok) break;
        }
        // if (ok) {
        //     print_board(board);
        // }
        return ok;
    }
    ll rv =  0, &len = szs[idx];
    FOR (i, sz(board)) {
        FOR (j, sz(board)) {
            // vertical
            if (i + len <= sz(board)) {
                bool ok = true;
                FOB (l, i, i + len) {
                    if (board[l][j] != '.' && board[l][j] != 'O') {
                        ok = false;
                        break;
                    } else {
                        board[l][j] = '0' + idx;
                    }
                }
                if (ok) {
                    rv += dfs(idx + 1, szs, board, board);
                }
                FOB (l, i, i + len) {
                    board[l][j] = board0[l][j];
                }
            }
            // horizontal
            if (j + len <= sz(board) && len != 1) {
                bool ok = true;
                FOB (l, j, j + len) {
                    if (board[i][l] != '.' && board[i][l] != 'O') {
                        ok = false;
                        break;
                    } else {
                        board[i][l] = '0' + idx;
                    }
                }
                if (ok) {
                    rv += dfs(idx + 1, szs, board, board);
                }
                FOB (l, j, j + len) {
                    board[i][l] = board0[i][l];
                }
            }
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    vector<str> board0(n);
    FOR (i, n) {
        cin >> board0[i];
    }
    vector<ll> szs(k);
    FOR (i, k) {
        cin >> szs[i];
    }
    rsort(szs);
    cout << dfs(0, szs, board0, board0) << '\n';

    return 0;
}