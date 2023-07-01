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

constexpr ll ALPHA = 26;
ll dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
ll dy[] = {1, 0, -1, 1, -1, 1, 0, -1};

struct Trie {
    ch c;
    bool ending = false;
    vector<Trie*> children = vector<Trie*>(ALPHA, nullptr);

    Trie(ch c_) : c(c_) {}

    void insert(ll i, str &s) {
        if (i == sz(s)) {
            ending = true;
            return;
        }
        ll si = s[i] - 'A';
        if (children[si] == nullptr) {
            children[si] = new Trie(s[i]);
        }
        children[si]->insert(i + 1, s);
    }
};

void dfs(ll x, ll y, str w, Trie &t, vector<set<str>> &found, vector<str> &board, vector<vector<bool>> &vis) {
    vis[x][y] = true;
    FOR (i, 8) {
        ll nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) {
            continue;
        }
        if (t.ending) {
            found[sz(w)].insert(w);
        }
        if (t.children[board[nx][ny] - 'A'] != nullptr && !vis[nx][ny]) {
            dfs(nx, ny, w + board[nx][ny], *t.children[board[nx][ny] - 'A'], found, board, vis);
        }
    }
    vis[x][y] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll w;
    cin >> w;
    Trie *root = new Trie(' ');
    vector<str> words(w);
    FOR (i, w) {
        cin >> words[i];
        root->insert(0, words[i]);
    }
    ssort(words);
    ll q;
    cin >> q;
    while (q--) {
        vector<str> board(4);
        FOR (i, 4) {
            cin >> board[i];
        }
        vector<set<str>> found(9);
        FOR (i, 4) {
            FOR (j, 4) {
                str w = "";
                w += board[i][j];
                auto ptr = root->children[board[i][j] - 'A'];
                if (ptr == nullptr) {
                    continue;
                }
                vector<vector<bool>> vis(4, vector<bool>(4, false));
                Trie &t = *ptr;
                dfs(i, j, w, t, found, board, vis);
            }
        }
        ll score = (sz(found[3]) + sz(found[4])) * 1 +
            sz(found[5]) * 2 +
            sz(found[6]) * 3 +
            sz(found[7]) * 5 +
            sz(found[8]) * 11;
        ll total = sz(found[1]) +
            sz(found[2]) +
            sz(found[3]) +
            sz(found[4]) +
            sz(found[5]) +
            sz(found[6]) +
            sz(found[7]) +
            sz(found[8]);
        str best_word = "";
        FORR (i, 9) {
            if (sz(found[i]) > 0) {
                best_word = *found[i].begin();
                break;
            }
        }
        cout << score << ' ' << best_word << ' ' << total << '\n';
    }

    return 0;
}