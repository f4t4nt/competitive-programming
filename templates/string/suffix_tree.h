#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef string str;
typedef char ch;

#define sz(C) (ll) C.size()

// -----------------------------------------------------------------------------
//  Suffix Tree (Ukkonen, online)
// -----------------------------------------------------------------------------
//  Supports:   - built one letter at a time over s + '$'
//              - tree[v][c]: child of v through letter c (-1 if none);
//                the edge into v spells s[lo[v]..hi[v]]; par / link per node
//              - stats(leafs, depth): suffixes through each node + string depth
//  Restrictions: letters 'a'..'z' plus the '$' terminator (alpha = 27)
//  Complexity: O(n * alpha) time and memory
//  Notes:      - node 0 is the root; node 1 is an auxiliary node with an edge
//                to the root for every letter (the root's suffix link)
//              - occurrences of t in s = leafs[] at the node t's walk ends in
//                (the lower node of the edge, if it ends mid-edge)
// -----------------------------------------------------------------------------
struct SuffixTree {
    str s;                     // input + trailing '$'
    ll n, alpha;               // max node count, alphabet size (incl. '$')
    vector<vector<ll>> tree;   // tree[v][c] = child of v through letter c, -1 if none
    vector<ll> lo, hi;         // edge into v spells s[lo[v]..hi[v]]
    vector<ll> par, link;      // parent, suffix link
    ll cur_node, cur_pos;      // active point: its node (lower one if mid-edge) + position in s
    ll cur_sz, cur_ch;         // number of nodes, index of the letter being added

    SuffixTree(str &s_in, ll alpha = 27) : s(s_in), alpha(alpha) {
        s += '$';
        n = sz(s) * 2 + 2;
        tree.resize(n, vector<ll>(alpha, -1));
        lo.resize(n), hi.resize(n, sz(s) - 1), par.resize(n), link.resize(n);
        cur_sz = 2, cur_node = 0, cur_pos = 0;
        link[0] = 1, lo[0] = hi[0] = lo[1] = hi[1] = -1;
        tree[1] = vector<ll>(alpha, 0);
        for (cur_ch = 0; cur_ch < sz(s); cur_ch++) add_char(ch_to_idx(s[cur_ch]));
    }

    // letter -> transition index
    ll ch_to_idx(ch c) { return (c == '$' ? 26 : c - 'a'); }

    // add letter c, extending every suffix by it
    void add_char(ll c) {
        // return here after each jump to the next suffix (and add c again)
        suff:;
        // past the end of the current edge: find the next one, or make a leaf
        if (hi[cur_node] < cur_pos) {
            if (tree[cur_node][c] == -1) {
                tree[cur_node][c] = cur_sz;
                lo[cur_sz] = cur_ch;
                par[cur_sz++] = cur_node;
                cur_node = link[cur_node];
                cur_pos = hi[cur_node] + 1;
                goto suff;
            }
            cur_node = tree[cur_node][c];
            cur_pos = lo[cur_node];
        }
        // letter on the edge matches c: just walk down
        if (cur_pos == -1 || c == ch_to_idx(s[cur_pos])) cur_pos++;
        else {
            // split the edge in two, middle node cur_sz
            lo[cur_sz] = lo[cur_node];
            hi[cur_sz] = cur_pos - 1;
            par[cur_sz] = par[cur_node];
            tree[cur_sz][ch_to_idx(s[cur_pos])] = cur_node;
            // leaf cur_sz + 1 hangs off it through c
            tree[cur_sz][c] = cur_sz + 1;
            lo[cur_sz + 1] = cur_ch;
            par[cur_sz + 1] = cur_sz;
            lo[cur_node] = cur_pos;
            par[cur_node] = cur_sz;
            tree[par[cur_sz]][ch_to_idx(s[lo[cur_sz]])] = cur_sz;
            cur_sz += 2;
            // descend to the same position in the next (shorter) suffix
            cur_node = link[par[cur_sz - 2]];
            cur_pos = lo[cur_sz - 2];
            while (cur_pos <= hi[cur_sz - 2]) {
                cur_node = tree[cur_node][ch_to_idx(s[cur_pos])];
                cur_pos += hi[cur_node] - lo[cur_node] + 1;
            }
            // landed on a node: link to it; mid-edge: link to cur_sz
            // (the split node the next iteration will create)
            if (cur_pos == hi[cur_sz - 2] + 1) link[cur_sz - 2] = cur_node;
            else link[cur_sz - 2] = cur_sz;
            cur_pos = hi[cur_node] - (cur_pos - hi[cur_sz - 2]) + 2;
            goto suff;
        }
    }

    // leafs[v] = suffixes ending under v (= occurrences of v's substring),
    // depth[v] = letters from root to v; pass vectors of size cur_sz
    ll stats(vector<ll> &leafs, vector<ll> &depth, ll v = 0, ll d = 0) {
        depth[v] = d;
        ll rv = 0;
        for (ll i = 0; i < alpha; i++)
            if (tree[v][i] != -1)
                rv += stats(leafs, depth, tree[v][i], d + hi[tree[v][i]] - lo[tree[v][i]] + 1);
        if (rv == 0) rv = 1;
        leafs[v] = rv;
        return rv;
    }

    // debug dump: per node its edge range, parent, link, transitions
    void print() {
        for (ll i = 0; i < cur_sz; i++) {
            cout << i << ": [" << lo[i] << ", " << hi[i] << "] par: " << par[i] << " link: " << link[i] << '\n';
            for (ll j = 0; j < alpha; j++)
                if (tree[i][j] != -1)
                    cout << (j == 26 ? '$' : (ch) ('a' + j)) << ' ' << tree[i][j] << '\n';
        }
    }
};
