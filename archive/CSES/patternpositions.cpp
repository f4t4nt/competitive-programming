#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct SuffixTree {
    str s; // input string for which the suffix tree is being built
    vector<vector<int>> tree; // array of transitions (state, letter)
    // left... and right boundaries of the substring of s which correspond to incoming edge
    // parent of the node
    // suffix link
    vector<int> lo, hi, par, link;
    // maximum possible number of nodes in suffix tree
    // number of letters in the alphabet
    int n, alpha;
    // the node of the current suffix (if we're mid-edge, the lower node of the edge)
    // position in the string which corresponds to the position on the edge (between lo[cur_node] and hi[cur_node], inclusive)
    // the number of nodes
    // the current character in the string
    int cur_node, cur_pos, cur_size, cur_char;
 
    SuffixTree(str &s_in, int alpha = 27) : s(s_in), alpha(alpha) {
        s += '$';
        n = sz(s) * 2 + 2;
        tree = vector<vector<int>>(n, vector<int>(alpha, -1));
        lo = vector<int>(n);
        hi = vector<int>(n, sz(s) - 1);
        par = vector<int>(n);
        link = vector<int>(n);
        cur_size = 2;
        cur_node = 0;
        cur_pos = 0;
        // initialize data for the root of the tree
        link[0] = 1;
        lo[0] = -1;
        hi[0] = -1;
        lo[1] = -1;
        hi[1] = -1;
        tree[1] = vector<int>(alpha, 0);
        // add the text to the tree, letter by letter
        for (cur_char = 0; cur_char < sz(s); ++cur_char) {
            add_char(char_to_index(s[cur_char]));
        }
    }
 
    int char_to_index(ch c) {
        if (c == '$') {
            return 0;
        } else {
            return c - 'a' + 1;
        }
    }
 
    // add character c to the tree
    void add_char(int c) {
        // we'll return here after each transition to the suffix (and will add character again)
        suff:;
        // check whether we're still within the boundaries of the current edge
        if (hi[cur_node] < cur_pos) {
            // if we're not, find the next edge. If it doesn't exist, create a leaf and add it to the tree
            if (tree[cur_node][c] == -1) {
                tree[cur_node][c] = cur_size;
                lo[cur_size] = cur_char;
                par[cur_size++] = cur_node;
                cur_node = link[cur_node];
                cur_pos = hi[cur_node] + 1;
                goto suff;
            }
            cur_node = tree[cur_node][c];
            cur_pos = lo[cur_node];
        } // otherwise just proceed to the next edge
        if (cur_pos == -1 || c == char_to_index(s[cur_pos])) {
            cur_pos++; // if the letter on the edge equal c, go down that edge
        } else { 
            // otherwise split the edge in two with middle in node cur_size
            lo[cur_size] = lo[cur_node];
            hi[cur_size] = cur_pos - 1;
            par[cur_size] = par[cur_node];
            tree[cur_size][char_to_index(s[cur_pos])] = cur_node;
            // add leaf cur_size+1. It corresponds to transition through c.
            tree[cur_size][c] = cur_size + 1;
            lo[cur_size + 1] = cur_char;
            par[cur_size + 1] = cur_size;
            // update info for the current node - remember to mark cur_size as parent of cur_node
            lo[cur_node] = cur_pos;
            par[cur_node] = cur_size;
            tree[par[cur_size]][char_to_index(s[lo[cur_size]])] = cur_size;
            cur_size += 2;
            // prepare for descent
            // cur_pos will mark where are we in the current suffix
            cur_node = link[par[cur_size - 2]];
            cur_pos = lo[cur_size - 2];
            // while the current suffix is not over, descend
            while (cur_pos <= hi[cur_size - 2]) {
                cur_node = tree[cur_node][char_to_index(s[cur_pos])];
                cur_pos += hi[cur_node] - lo[cur_node] + 1;
            }
            // if we're in a node, add a suffix link to it, otherwise add the link to cur_size
            // (we'll create cur_size on next iteration).
            if (cur_pos == hi[cur_size - 2] + 1) {
                link[cur_size - 2] = cur_node;
            } else {
                link[cur_size - 2] = cur_size;
            } 
            // add cur_pos to the new edge and return to add letter to suffix
            cur_pos = hi[cur_node] - (cur_pos - hi[cur_size - 2]) + 2;
            goto suff;
        }
    }
 
    void print() {
        FOR (i, cur_size) {
            cout << i << ':' << lo[i] << ' ' << hi[i] << ' ' << par[i] << ' ' << link[i] << " " << '\n';
            FOR (j, alpha) {
                if (tree[i][j] != -1) {
                    if (j == 0) {
                        cout << "$ ";
                    } else {
                        cout << (char)('a' + j - 1) << ' ';
                    }
                    cout << tree[i][j] << '\n';
                }
            }
        }
    }
};
 
int gen_tree(SuffixTree &st, vector<int> &leafs, vector<int> &depth, int v = 0, int d = 0) {
    depth[v] = d;
    int rv = 0;
    FOR (i, st.alpha) {
        if (st.tree[v][i] != -1) {
            rv += gen_tree(st, leafs, depth, st.tree[v][i], d + st.hi[st.tree[v][i]] - st.lo[st.tree[v][i]] + 1);
        }
    }
    if (rv == 0) {
        rv = 1;
    }
    leafs[v] = rv;
    return rv;
}
 
// void gen_tree(SuffixTree &st, vector<int> &leafs, vector<int> &depth) {
//     vector<int> in(st.cur_size);
//     queue<int> depth_q, leaf_q;
//     depth_q.push(0);
//     while (!depth_q.empty()) {
//         int v = depth_q.front();
//         depth_q.pop();
//         bool is_leaf = true;
//         FOR (i, st.alpha) {
//             if (st.tree[v][i] != -1) {
//                 depth[st.tree[v][i]] = depth[v] + st.hi[st.tree[v][i]] - st.lo[st.tree[v][i]] + 1;
//                 depth_q.push(st.tree[v][i]);
//                 in[v]++;
//                 is_leaf = false;
//             }
//         }
//         if (is_leaf) {
//             leafs[v] = 1;
//             leaf_q.push(v);
//         }
//     }
//     while (!leaf_q.empty()) {
//         int v = leaf_q.front();
//         leaf_q.pop();
//         if (v != 0) {
//             leafs[st.par[v]] += leafs[v];
//             in[st.par[v]]--;
//             if (in[st.par[v]] == 0) {
//                 leaf_q.push(st.par[v]);
//             }
//         }
//     }
// }
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    str s;
    cin >> s;
    SuffixTree st(s);
    vector<int> leafs(st.cur_size), depth(st.cur_size);
    gen_tree(st, leafs, depth);
    int k;
    cin >> k;
 
    while (k--) {
        str t;
        cin >> t;
 
        int i = 0, v = 0;
        if (st.tree[0][st.char_to_index(t[0])] == -1) {
            cout << -1 << '\n';
            continue;
        } else {
            v = st.tree[0][st.char_to_index(t[0])];
        }
 
        int idx = -1;
        while (i < sz(t)) {
            int j = st.lo[v];
            while (j <= st.hi[v] && i < sz(t) && t[i] == s[j]) {
                i++;
                j++;
            }
            if (i == sz(t)) {
                idx = j - sz(t) + 1;
                break;
            }
            if (j > st.hi[v]) {
                if (st.tree[v][st.char_to_index(t[i])] == -1) {
                    idx = -1;
                    break;
                } else {
                    v = st.tree[v][st.char_to_index(t[i])];
                }
            } else {
                idx = -1;
                break;
            }
        }

        cout << idx << '\n';
    }
 
    return 0;
}