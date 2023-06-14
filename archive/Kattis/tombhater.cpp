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

ll dx[3] = {1, 0, 0};
ll dy[3] = {0, 1, -1};

ll trie_cnt = 0;
constexpr ll ALPHA = 26;

struct Trie {
    ch c;
    ll idx = 0;
    bool ending = false;
    vector<Trie*> children = vector<Trie*>(ALPHA, nullptr);

    Trie(ch c_) : c(c_) {
        idx = trie_cnt++;
    }

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m, k;
    cin >> n >> m >> k;
    vector<vector<ch>> grid(n, vector<ch>(m));
    FOR (i, n) {
        FOR (j, m) {
            cin >> grid[i][j];
        }
    }
    Trie root('$');
    vector<str> words(k);
    FOR (i, k) {
        cin >> words[i];
        root.insert(0, words[i]);
    }

    // x, y, trie, dir
    vector<vector<vector<vector<ll>>>> dist(n,
        vector<vector<vector<ll>>>(m,
        vector<vector<ll>>(trie_cnt, 
        vector<ll>(3, 1e18))));
    vector<ll> final_row_dist(m, 1e18);
    // cur pos, cur dist, prev move (to avoid repeat), cur trie
    queue<tuple<ll, ll, ll, ll, Trie*>> bfs;
    FOR (i, m) {
        if (root.children[grid[0][i] - 'A'] != nullptr) {
            dist[0][i][root.children[grid[0][i] - 'A']->idx][0] = 1;
            bfs.push({0, i, 1, 0, root.children[grid[0][i] - 'A']});
        }
    }

    while (!bfs.empty()) {
        ll x, y, d, prev_i;
        Trie* trie;
        tie(x, y, d, prev_i, trie) = bfs.front();
        bfs.pop();
        if (trie->ending && x == n - 1) {
            final_row_dist[y] = min(final_row_dist[y], d);
        }
        d++;
        FOR (i, 3) {
            if (prev_i + i == 3) {
                continue;
            }
            ll nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            if (trie->ending && root.children[grid[nx][ny] - 'A'] != nullptr
                && dist[nx][ny][root.children[grid[nx][ny] - 'A']->idx][i] > d)
            {
                dist[nx][ny][root.children[grid[nx][ny] - 'A']->idx][i] = d;
                bfs.push({nx, ny, d, i, root.children[grid[nx][ny] - 'A']});
            }
            if (trie->children[grid[nx][ny] - 'A'] != nullptr
                && dist[nx][ny][trie->children[grid[nx][ny] - 'A']->idx][i] > d)
            {
                dist[nx][ny][trie->children[grid[nx][ny] - 'A']->idx][i] = d;
                bfs.push({nx, ny, d, i, trie->children[grid[nx][ny] - 'A']});
            }
        }
    }

    ll rv = 1e18;
    FOR (i, m) {
        rv = min(rv, final_row_dist[i]);
    }
    if (rv == 1e18) {
        cout << "impossible\n";
    } else {
        cout << rv << '\n';
    }

    return 0;
}