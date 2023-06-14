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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

map<ch, vector<str>> shapes = {
    {'F', {
            ".##",
            "##.",
            ".#."
    }}, {'I', {
            "#####",
    }}, {'L', {
            "####",
            "#...",
    }}, {'N', {
            "##..",
            ".###",
    }}, {'P', {
            "###",
            "##.",
    }}, {'T', {
            "###",
            ".#.",
            ".#.",
    }}, {'U', {
            "#.#",
            "###",
    }}, {'V', {
            "#..",
            "#..",
            "###",
    }}, {'W', {
            "#..",
            "##.",
            ".##",
    }}, {'X', {
            ".#.",
            "###",
            ".#.",
    }}, {'Y', {
            "####",
            ".#..",
    }}, {'Z', {
            "##.",
            ".#.",
            ".##",
    }}
};

ll dx[] = {0, 1, 0, -1};
ll dy[] = {1, 0, -1, 0};

void print_board(vector<vector<ch>> board) {
    FOR (i, sz(board)) {
        FOR (j, sz(board[0])) {
            cout << board[i][j];
        }
        cout << '\n';
    }
    cout << endl;
}

set<vector<vector<ch>>> rotated(vector<str> shape0) {
    set<vector<vector<ch>>> rv;
    vector<vector<ch>> shape(sz(shape0), vector<ch>(sz(shape0[0])));
    FOR (i, sz(shape0)) {
        FOR (j, sz(shape0[0])) {
            shape[i][j] = shape0[i][j];
        }
    }
    rv.insert(shape);
    shape = vector<vector<ch>>(sz(shape0), vector<ch>(sz(shape0[0])));
    FORR (i, sz(shape0)) {
        FORR (j, sz(shape0[0])) {
            shape[sz(shape0) - i - 1][sz(shape0[0]) - j - 1] = shape0[i][j];
        }
    }
    rv.insert(shape);
    shape = vector<vector<ch>>(sz(shape0[0]), vector<ch>(sz(shape0)));
    FOR (i, sz(shape0)) {
        FOR (j, sz(shape0[0])) {
            shape[j][sz(shape0) - i - 1] = shape0[i][j];
        }
    }
    rv.insert(shape);
    shape = vector<vector<ch>>(sz(shape0[0]), vector<ch>(sz(shape0)));
    FORR (i, sz(shape0)) {
        FORR (j, sz(shape0[0])) {
            shape[sz(shape0[0]) - j - 1][i] = shape0[i][j];
        }
    }
    rv.insert(shape);
    return rv;
}

set<vector<str>> paste(ll i, ll j, ll val, vector<str> shape0, vector<str> base, bool adj) {
    set<vector<str>> rv;
    FOR (f, 2) {
        auto shapes = rotated(shape0);
        FORE (shape, shapes) {
            vector<str> board = base;
            bool valid = true, is_adj = false;
            FOB (k, i, i + sz(shape)) {
                FOB (l, j, j + sz(shape[0])) {
                    if (k >= sz(base) || l >= sz(base[0])) {
                        valid = false;
                        break;
                    }
                    if (shape[k - i][l - j] == '#') {
                        if (board[k][l] != '.') {
                            valid = false;
                            break;
                        }
                        board[k][l] = val + '0';
                        if (adj && !is_adj) {
                            FOR (m, 4) {
                                ll x = k + dx[m], y = l + dy[m];
                                if (x >= 0 && x < sz(base) && y >= 0 && y < sz(base[0]) && base[x][y] != '.') {
                                    is_adj = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (!valid) {
                    break;
                }
            }
            if (!valid) continue;
            if (adj && !is_adj) continue;
            rv.insert(board);
        }
        flip(shape0);
    }
    return rv;
}

set<vector<str>> get_configs(vector<str> shape, set<vector<str>> &base) {
    set<vector<str>> rv;
    FORE (board, base) {
        FOR (i, sz(board)) {
            FOR (j, sz(board[0])) {
                auto configs = paste(i, j, 0, shape, board, true);
                FORE (config, configs) {
                    ll min_i = sz(config), max_i = -1, min_j = sz(config[0]), max_j = -1;
                    FOR (k, sz(config)) {
                        FOR (l, sz(config[0])) {
                            if (config[k][l] != '.') {
                                min_i = min(min_i, k);
                                max_i = max(max_i, k);
                                min_j = min(min_j, l);
                                max_j = max(max_j, l);
                            }
                        }
                    }
                    vector<str> trimmed;
                    FOB (k, min_i, max_i + 1) {
                        str row;
                        FOB (l, min_j, max_j + 1) {
                            row += config[k][l];
                        }
                        trimmed.push_back(row);
                    }
                    rv.insert(trimmed);
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
    
    str line;
    map<vector<str>, bool> ref;
    while (getline(cin, line)) {
        vector<str> pieces = {line.substr(0, 2), line.substr(3, 2)};
        ssort(pieces[0]), ssort(pieces[1]), ssort(pieces);
        if (ref.find(pieces) == ref.end()) {
            if (pieces[0] == pieces[1]) {
                ref[pieces] = true;
            } else {
                vector<str> base(15, "...............");
                auto base0 = paste(5, 5, 0, shapes[pieces[0][0]], base, false);
                auto final0 = get_configs(shapes[pieces[0][1]], base0);
                auto base1 = paste(5, 5, 0, shapes[pieces[1][0]], base, false);
                auto final1 = get_configs(shapes[pieces[1][1]], base1);
                auto it0 = final0.begin(), it1 = final1.begin();
                bool found = false;
                while (it0 != final0.end() && it1 != final1.end()) {
                    if (*it0 == *it1) {
                        found = true;
                        break;
                    }
                    if (*it0 < *it1) it0++;
                    else it1++;
                }
                ref[pieces] = found;
            }
        }
        cout << (ref[pieces] ? "YES\n" : "NO\n");
    }

    return 0;
}