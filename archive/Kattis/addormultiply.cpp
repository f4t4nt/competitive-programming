#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <set>

using namespace std;

#define int long long

typedef vector<int> vi;

#define rep(i, n) for (int i = 0 ; i < n ; i++)
#define pb push_back

int INF = 2e9;
int MOD = 1000000007;

int modpow(int n, int k) {
    int ans = 1LL;
    int s = n;
    
    rep(i, 64) {
        if ((1LL << i) & k) {
            ans = (ans * s) % MOD;
        }
        s = (s * s) % MOD;
    }
    
    return ans;
}

int inv(int n) {
    return modpow(n, MOD - 2);
}

struct SegTree {
    int n;
    vi data, lazy;
    
    SegTree(int n) : n(n), data(4 * n), lazy(4 * n) {}
    void push(int i, int l, int r) {
        if (lazy[i] == 0) return;
        data[i] = (data[i] + (r - l) * lazy[i]) % MOD;
        if (r - l > 1) {
            lazy[2 * i] = (lazy[2 * i] * lazy[i]) % MOD;
            lazy[2 * i + 1] = (lazy[2 * i + i] * lazy[i]) % MOD;
        }
        lazy[i] = 0;
    }
    
    void update(int ul, int ur, int val, int i = 1, int l = 0, int r = -1) {
        if (r == -1) r = n;
        push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            lazy[i] = (lazy[i] + val) % MOD;
            push(i, l, r);
            return;
        }
        int m = (l + r) / 2;
        update(ul, ur, val, 2 * i, l, m);
        update(ul, ur, val, 2 * i + 1, m, r);
        data[i] = (data[2 * i] * data[2 * i + 1]) % MOD;
    }
    
    int query(int ql, int qr, int i = 1, int l = 0, int r = -1) {
        if (r == -1) r = n;
        push(i, l, r);
        if (qr <= l || r <= ql) return 1LL;
        if (ql <= l && r <= qr) return data[i];
        int m = (l + r) / 2;
        return (query(ql, qr, 2 * i, l, m) * query(ql, qr, 2 * i + 1, m, r)) % MOD;
    }
};

int32_t main() {
    
    int n, m;
    cin >> n >> m;
    
    string s;
    cin >> s;
    
    set<int> adds1;
    set<int> adds2;
    
    adds1.insert(0);
    adds2.insert(0);
    
    adds1.insert(n);
    adds2.insert(n);
    
    vector<int> a;
    
    rep(i, s.length()) {
        if (i % 2 == 0) {
            a.pb(s[i] - '0');
        }
        else {
            if (s[i] == '+') {
                adds1.insert(i / 2 + 1);
            }
            else {
                adds2.insert(i / 2 + 1);
            }
        }
    }
    
    SegTree st(n);
    
    rep(i, n) {
        st.update(i, i + 1, a[i]);
    }
    
    int cur1 = 0;
    int cur2 = 0;
    
    for (auto it = adds1.begin() ; next(it) != adds1.end() ; it++) {
        int ind1 = *it;
        int ind2 = *next(it);
        
        int rng = st.query(ind1, ind2);
        
        cur1 = (cur1 + rng) % MOD;
    }
    
    for (auto it = adds2.begin() ; next(it) != adds2.end() ; it++) {
        int ind1 = *it;
        int ind2 = *next(it);
        
        int rng = st.query(ind1, ind2);
        
        cur2 = (cur2 + rng) % MOD;
    }
    
    bool flipped = false;
    
    rep(i, m + 1) {
        if (flipped) {
            cout << cur2 << '\n';
        }
        else {
            cout << cur1 << '\n';
        }
        
        if (i == m) break;
        
        char c;
        cin >> c;
        
        if (c == 'a') {
            flipped = !flipped;
        }
        else if (c == 's') {
            int x, y;
            cin >> x >> y;
            
            int old_ax = a[x - 1];
            int old_ay = a[y - 1];
            
            int l1 = *prev(adds1.lower_bound(x));
            int r1 = *adds1.lower_bound(x);
            int l1_flip = *prev(adds2.lower_bound(x));
            int r1_flip = *adds2.lower_bound(x);
            
            int old_rng1 = st.query(l1, r1);
            int old_rng1_flip = st.query(l1_flip, r1_flip);
            
            a[x - 1] = old_ay;
            st.update(x - 1, x, (a[x - 1] - old_ax + MOD) % MOD);
                        
            cur1 = (cur1 - old_rng1 + st.query(l1, r1) + MOD) % MOD;
            cur2 = (cur2 - old_rng1_flip + st.query(l1_flip, r1_flip) + MOD) % MOD;
            
            int l2 = *prev(adds1.lower_bound(y));
            int r2 = *adds1.lower_bound(y);
            int l2_flip = *prev(adds2.lower_bound(y));
            int r2_flip = *adds2.lower_bound(y);
            
            int old_rng2 = st.query(l2, r2);
            int old_rng2_flip = st.query(l2_flip, r2_flip);
            
            a[y - 1] = old_ax;
            st.update(y - 1, y, (a[y - 1] - old_ay + MOD) % MOD);
                        
            cur1 = (cur1 - old_rng2 + st.query(l2, r2) + MOD) % MOD;
            cur2 = (cur2 - old_rng2_flip + st.query(l2_flip, r2_flip) + MOD) % MOD;
            
            
        }
        else {
            int ind;
            cin >> ind;
            
            if (s[ind * 2 - 1] == '+') {
                s[ind * 2 - 1] = '*';
                
                int pre = *prev(adds1.find(ind));
                int cur = *adds1.find(ind);
                int nxt = *next(adds1.find(ind));
                
                int old_rng1 = st.query(pre, cur);
                int old_rng2 = st.query(cur, nxt);
                
                adds1.erase(adds1.find(ind));
                
                int new_rng = st.query(pre, nxt);
                
                cur1 = (cur1 - old_rng1 - old_rng2 + new_rng + MOD * 2) % MOD;
                
                cur = *adds2.lower_bound(ind);
                pre = *prev(adds2.lower_bound(ind));
                
                int old_rng = st.query(pre, cur);
                
                adds2.insert(ind);
                
                int new_rng1 = st.query(pre, ind);
                int new_rng2 = st.query(ind, cur);
                
                cur2 = (cur2 - old_rng + new_rng1 + new_rng2 + MOD) % MOD;
            }
            else {
                s[ind * 2 - 1] = '+';

                int pre = *prev(adds2.lower_bound(ind));
                int cur = *adds2.lower_bound(ind);
                int nxt = *next(adds2.lower_bound(ind));
                
                int old_rng1 = st.query(pre, cur);
                int old_rng2 = st.query(cur, nxt);
                
                adds2.erase(adds2.find(ind));
                
                int new_rng = st.query(pre, nxt);
                
                cur2 = (cur2 - old_rng1 - old_rng2 + new_rng + MOD * 2) % MOD;
                
                cur = *adds1.lower_bound(ind);
                pre = *prev(adds1.lower_bound(ind));
                
                int old_rng = st.query(pre, cur);
                
                adds1.insert(ind);
                
                int new_rng1 = st.query(pre, ind);
                int new_rng2 = st.query(ind, cur);
                
                cur1 = (cur1 - old_rng + new_rng1 + new_rng2 + MOD) % MOD;
            }
        }
    }
}