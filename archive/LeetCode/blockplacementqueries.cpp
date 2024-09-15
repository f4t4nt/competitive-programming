#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int n; vector<int> data;
    SegTree (int n) : n(n), data(4 * n) {}
    void upd(int ul, int val, int i = 1, int l = 0, int r = -1) {
        int ur = ul + 1;
        if (r == -1) r = n;
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            data[i] = val;
            return;
        }
        int m = (l + r) / 2;
        upd(ul, val, 2 * i, l, m);
        upd(ul, val, 2 * i + 1, m, r);
        data[i] = max(data[2 * i], data[2 * i + 1]);
    }
    int qry(int qr, int i = 1, int l = 0, int r = -1) {
        int ql = 0;
        if (r == -1) r = n;
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[i];
        int m = (l + r) / 2;
        return max(qry(qr, 2 * i, l, m), qry(qr, 2 * i + 1, m, r));
    }
    void dbg() {
        for (int x : data) cout << x << ' ';
        cout << '\n';
    }
};

class Solution {
public:
    const int MX = 50000;

    vector<bool> getResults(vector<vector<int>>& queries) {
        vector<bool> res;
        set<int> obstacles = {0, MX};
        SegTree st(MX);
        st.upd(0, MX);
        for (auto q : queries) {
            if (q[0] == 1) {
                int x = q[1],
                    prv = *prev(obstacles.lower_bound(x)),
                    nxt = *obstacles.upper_bound(x);
                st.upd(prv, x - prv);
                st.upd(x, nxt - x);
                obstacles.insert(x);
                // st.dbg();
            } else {
                int x = q[1],
                    sz = q[2],
                    prv = *prev(obstacles.lower_bound(x));
                // cout << x << ' ' << sz << ' ' << prv << '\n';
                res.push_back(max(x - prv, st.qry(prv)) >= sz);
            }
        }
        return res;
    }
};
