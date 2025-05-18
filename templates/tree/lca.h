#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define pb push_back

template<class T>
struct SparseTable {
    ll n, K;
    vector<vector<T>> st;
    vector<ll> log2s;
    static T combine(const T &a, const T &b) {
        return (a.second < b.second) ? a : b; // min depth
    }
    SparseTable(const vector<T> &a) {
        n = a.size(); K = 64 - __builtin_clzll(n);
        st.assign(K, vector<T>(n)); log2s.assign(n + 1, 0);
        for (ll i = 2; i <= n; i++) log2s[i] = log2s[i >> 1] + 1;
        st[0] = a;
        for (ll k = 1; k < K; k++)
            for (ll i = 0; i + (1LL << k) <= n; i++)
                st[k][i] = combine(st[k - 1][i], st[k - 1][i + (1LL << (k - 1))]);
    }
    // query [l, r)
    T qry(ll l, ll r) const {
        if (l == r) return T{ -1, LLONG_MAX };
        ll k = log2s[r - l];
        return combine(st[k][l], st[k][r - (1LL << k)]);
    }
};

struct LCA {
    ll n, timer = 0;
    vector<vector<ll>> adj;
    vector<ll> first, depth;
    vector<pair<ll, ll>> euler; // {node, depth}
    SparseTable<pair<ll, ll>> *st;

    LCA(ll _n, const vector<vector<ll>> &_adj) : n(_n), adj(_adj) {
        first.assign(n, -1);
        depth.resize(n);
        dfs(0, -1, 0);
        st = new SparseTable<pair<ll, ll>>(euler);
    }

    void dfs(ll v, ll p, ll d) {
        first[v] = euler.size();
        depth[v] = d;
        euler.pb({v, d});
        for (ll u : adj[v]) if (u != p) {
            dfs(u, v, d + 1);
            euler.pb({v, d}); // re-visit for RMQ
        }
    }

    ll lca(ll u, ll v) {
        ll L = first[u], R = first[v];
        if (L > R) swap(L, R);
        return st->qry(L, R + 1).first;
    }

    ll dist(ll u, ll v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    bool is_anc(ll u, ll v) {
        return lca(u, v) == u;
    }

    bool disjoint(vector<pair<ll, ll>> paths) {
        vector<pair<ll, ll>> p;
        for (auto &[u, v] : paths) {
            ll w = lca(u, v);
            p.pb({w, u});
            p.pb({w, v});
        }
        for (ll i = 0; i < p.size(); i++)
            for (ll j = 0; j < i; j++) {
                ll a = p[i].second, b = p[j].first;
                ll c = p[j].second, d = p[i].first;
                if (lca(a, b) == b && lca(c, d) == d) return false;
            }
        return true;
    }
};
