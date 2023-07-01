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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

vector<ll> manacher(str &s, str &t) {
    t = "$#";
    FORE (c, s) {
        t += c;
        t += '#';
    }

    ll n = sz(t);
    ll center = 0, max_rad = -1, rad;
    vector<ll> p(n);
    FOR (i, n) {
        if (i <= max_rad) {
            rad = min(p[2 * center - i], max_rad - i);
        } else {
            rad = 0;
        }
        while (i - rad - 1 >= 0 && i + rad + 1 < n && t[i - rad - 1] == t[i + rad + 1]) {
            rad++;
        }
        p[i] = rad;
        if (i + rad > max_rad) {
            center = i;
            max_rad = i + rad;
        }
    }

    ll len = 0, idx = 0;
    FOR (i, n) {
        if (p[i] > len) {
            len = p[i];
            idx = i;
        }
    }

    // return {len, (idx - len) / 2};
    return p;
}

ll full_brute(ll l, ll r, str &s) {
    ll rv = 0;
    l--;
    FOB (i, l, r + 1) {
        FOB (j, i + 1, r + 1) {
            str t = s.substr(i, j - i);
            str t2 = t;
            flip(t2);
            if (t == t2) {
                rv++;
            }
        }
    }
    return rv;
}

ll mini_brute(ll l, ll r, str &s) {
    ll rv = 0;
    l--;
    str s0 = s.substr(l, r - l), t;
    vector<ll> p = manacher(s0, t);
    FOR (i, sz(p)) {
        rv += (p[i] + 1) / 2;
    }
    return rv;
}

struct SegTree {
    ll n;
    vector<map<ll, ll>> cnts, sums;
    SegTree (ll n) : n(n), cnts(4 * n), sums(4 * n) {}
    void update(ll idx, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (idx <= l && r <= idx + 1) {
            cnts[i][val]++;
            return;
        }
        if (r <= idx || idx + 1 <= l) return;
        ll m = (l + r) / 2;
        update(idx, val, 2 * i, l, m);
        update(idx, val, 2 * i + 1, m, r);
        ll vall = (cnts[2 * i].count(val) ? cnts[2 * i][val] : 0),
            valr = (cnts[2 * i + 1].count(val) ? cnts[2 * i + 1][val] : 0);
        cnts[i][val] = vall + valr;
    }
    void eval(ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (l + 1 != r) {
            ll m = (l + r) / 2;
            eval(2 * i, l, m), eval(2 * i + 1, m, r);
        }
        ll cur_cnt = 0, cur_sum = 0;
        map<ll, ll> tmp;
        FORE (e, cnts[i]) {
            cur_cnt += e.second;
            cur_sum += e.first / 2 * e.second;
            tmp[e.first] = cur_cnt;
            sums[i][e.first] = cur_sum;
        }
        cnts[i] = tmp;
    }
    // return cnt of < thresh, sum of < thresh
    pair<ll, ll> query(ll lo, ll hi, ll thresh, ll i = 1, ll l = 0, ll r = -1) { // [lo, hi)
        if (r == -1) r = n;
        if (lo <= l && r <= hi) {
            // return {cnts[i][thresh], sums[i][thresh]};
            auto it0 = cnts[i].lower_bound(thresh),
                it1 = sums[i].lower_bound(thresh);
            if (it0 == cnts[i].begin()) {
                assert(it1 == sums[i].begin());
                return {0, 0};
            }
            it0--, it1--;
            return {it0->second, it1->second};
        }
        if (r <= lo || hi <= l) return {0, 0};
        ll m = (l + r) / 2;
        auto [cntl, suml] = query(lo, hi, thresh, 2 * i, l, m);
        auto [cntr, sumr] = query(lo, hi, thresh, 2 * i + 1, m, r);
        pair<ll, ll> rv = {cntl + cntr, suml + sumr};
        return rv;
    }
};

ll sum_brute(ll l, ll r, vector<ll> &p) {
    ll m = l + r;
    l *= 2, r *= 2;
    ll ref = 0, rv = 0, lis = 0, ris = 0, lcnt = 0, rcnt = 0, lsum = 0, rsum = 0;
    vector<ll> tmp;
    FOB (i, l, m + 1) {
        tmp.pb(i / 2 + min(2 - l, p[i] - i + 1) / 2);
        ref += tmp.back();
        lis += i / 2;
        if (p[i] - i + 1 < 2 - l) {
            lcnt++;
            lsum += (p[i] - i + 1) / 2;
        }
    }
    FOB (i, m + 1, r + 1) {
        tmp.pb((-i + 1) / 2 + min(r + 1, p[i] + i) / 2);
        ref += tmp.back();
        ris += (-i + 1) / 2;
        if (p[i] + i < r + 1) {
            rcnt++;
            rsum += (p[i] + i) / 2;
        }
    }
    ll lcnt0 = m + 1 - l - lcnt, rcnt0 = r - m - rcnt;
    rv = lis + ris + (2 - l) / 2 * lcnt0 + (r + 1) / 2 * rcnt0 + lsum + rsum;
    assert(rv == ref);
    return rv;
}

ll sad_brute(ll l, ll r, vector<ll> &p, vector<ll> &lisum, vector<ll> &risum, SegTree &lt, SegTree &rt) {
    ll m = l + r;
    l *= 2, r *= 2;
    ll lis = lisum[m] - lisum[l - 1], ris = risum[r] - risum[m];
    auto [lcnt, lsum] = lt.query(l, m + 1, 2 - l);
    auto [rcnt, rsum] = rt.query(m + 1, r + 1, r + 1);
    ll lcnt0 = m + 1 - l - lcnt, rcnt0 = r - m - rcnt;
    ll rv = lis + ris + (2 - l) / 2 * lcnt0 + (r + 1) / 2 * rcnt0 + lsum + rsum;
    return rv;
}

struct Vertex {
    Vertex *l, *r;
    ll sum, cnt;

    Vertex(ll val) : l(nullptr), r(nullptr), sum(val), cnt(1) {}
    Vertex(ll val, ll c) : l(nullptr), r(nullptr), sum(val), cnt(c) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0), cnt(0) {
        if (l) {
            sum += l->sum;
            cnt += l->cnt;
        }
        if (r) {
            sum += r->sum;
            cnt += r->cnt;
        }
    }
};

Vertex* build(vector<ll> &a, ll tl, ll tr) {
    if (tl == tr) return new Vertex(a[tl], 0);
    ll tm = (tl + tr) / 2;
    return new Vertex(build(a, tl, tm), build(a, tm + 1, tr));
}

pair<ll, ll> get_sum(Vertex* v, ll tl, ll tr, ll l, ll r) {
    if (l > r) return {0, 0};
    if (l == tl && tr == r) return {v->sum, v->cnt};
    ll tm = (tl + tr) / 2;
    auto [sl, cl] = get_sum(v->l, tl, tm, l, min(r, tm));
    auto [sr, cr] = get_sum(v->r, tm + 1, tr, max(l, tm + 1), r);
    return {sl + sr, cl + cr};
}

Vertex* update(Vertex* v, ll tl, ll tr, ll pos, ll new_val) {
    if (tl == tr) return new Vertex(new_val);
    ll tm = (tl + tr) / 2;
    if (pos <= tm) return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else return new Vertex(v->l, update(v->r, tm + 1, tr, pos, new_val));
}

vector<ll> concat(Vertex* v, ll tl, ll tr) {
    if (tl == tr) return {v->sum};
    ll tm = (tl + tr) / 2;
    auto l = concat(v->l, tl, tm);
    auto r = concat(v->r, tm + 1, tr);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // ll len = 400;
    // FOR (i, len) {
    //     cout << (ch)('a' + rand() % 6);
    // }
    // FOR (i, len) {
    //     FOB (j, i + 1, len) {
    //         cout << i + 1 << ' ' << j + 1 << '\n';
    //     }
    // }
    // return 0;

    str s, t;
    ll q;
    cin >> s >> q;
    vector<ll> p = manacher(s, t);
    vector<ll> lisum(sz(p)), risum(sz(p));
    FOB (i, 1, sz(p)) {
        lisum[i] = lisum[i - 1] + i / 2;
        risum[i] = risum[i - 1] + (-i + 1) / 2;
    }
    // SegTree lt(sz(p)), rt(sz(p));
    // FOR (i, sz(p)) {
    //     lt.update(i, p[i] - i + 1);
    //     rt.update(i, p[i] + i);
    // }
    // lt.eval(), rt.eval();
    vector<pair<ll, ll>> vals_l, vals_r;
    FOR (i, sz(p)) {
        vals_l.pb({(p[i] - i + 1) / 2, i});
        vals_r.pb({(p[i] + i) / 2, i});
    }
    ssort(vals_l), ssort(vals_r);
    vector<Vertex*> roots_l(sz(p) + 1), roots_r(sz(p) + 1);
    vector<ll> tmp(sz(p));
    roots_l[0] = build(tmp, 0, sz(p) - 1);
    roots_r[0] = build(tmp, 0, sz(p) - 1);
    FOR (i, sz(p)) {
        roots_l[i + 1] = update(roots_l[i], 0, sz(p) - 1, vals_l[i].second, vals_l[i].first);
        roots_r[i + 1] = update(roots_r[i], 0, sz(p) - 1, vals_r[i].second, vals_r[i].first);
    }
    while (q--) {
        ll l, r;
        cin >> l >> r;
        // ll ref = sad_brute(l, r, p, lisum, risum, lt, rt);
        // cout << ref << '\n';
        ll m = l + r, lo = 0, hi = sz(p);
        l *= 2, r *= 2;
        ll target_l = (2 - l) / 2, target_r = (r + 1) / 2;
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            if (vals_l[mid].first >= target_l) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        ll lpos = lo;
        lo = 0, hi = sz(p);
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            if (vals_r[mid].first >= target_r) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        ll rpos = lo;
        ll lis = lisum[m] - lisum[l - 1], ris = risum[r] - risum[m];
        auto [lsum, lcnt] = get_sum(roots_l[lpos], 0, sz(p) - 1, l, m);
        auto [rsum, rcnt] = get_sum(roots_r[rpos], 0, sz(p) - 1, m + 1, r);
        ll lcnt0 = m + 1 - l - lcnt, rcnt0 = r - m - rcnt;
        ll rv = lis + ris + (2 - l) / 2 * lcnt0 + (r + 1) / 2 * rcnt0 + lsum + rsum;
        // assert(rv == ref);
        cout << rv << '\n';
    }

    return 0;
}