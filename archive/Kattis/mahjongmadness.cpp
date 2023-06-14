#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll x;
    cin >> x;
    x--;
    vector<ll> a(14), cnt_a(9);
    multiset<ll> s;
    FOR (i, 4) {
        FOR (j, 9) {
            s.insert(j);
        }
    }
    FOR (i, 14) {
        cin >> a[i];
        a[i]--;
        cnt_a[a[i]]++;
        s.erase(s.find(a[i]));
    }
    vector<ll> s_v = vector<ll>(all(s));
    assert(sz(s_v) == 22);

    vector<ld> rv(14);
    FOR (i, 14) {
        ld total = 0;
        vector<ll> ijkl;
        FOR (wtf, 22) {
            ll j = s_v[wtf];
            vector<ll> b = a, cnt_b = cnt_a;
            cnt_b[b[i]]--;
            b[i] = j;
            cnt_b[b[i]]++;
            ld score = 0;
            bool bonus = false;
            FOR (k, 9) {
                if (cnt_b[k] < 2) {
                    continue;
                }
                ll set_cnt = 0;
                vector<ll> tmp = cnt_b;
                tmp[k] -= 2;
                FOR (l, 9) {
                    if (tmp[l] < 3) {
                        continue;
                    }
                    tmp[l] -= 3;
                    set_cnt++;
                }
                FOB (l, 1, 8) {
                    while (tmp[l - 1] && tmp[l] && tmp[l + 1]) {
                        tmp[l - 1]--;
                        tmp[l]--;
                        tmp[l + 1]--;
                        set_cnt++;
                    }
                }
                if (set_cnt == 4) {
                    bonus = true;
                    break;
                }
                set_cnt = 0;
                tmp = cnt_b;
                tmp[k] -= 2;
                FOB (l, 1, 8) {
                    while (tmp[l - 1] && tmp[l] && tmp[l + 1]) {
                        tmp[l - 1]--;
                        tmp[l]--;
                        tmp[l + 1]--;
                        set_cnt++;
                    }
                }
                FOR (l, 9) {
                    if (tmp[l] < 3) {
                        continue;
                    }
                    tmp[l] -= 3;
                    set_cnt++;
                }
                if (set_cnt == 4) {
                    bonus = true;
                    break;
                }
            }
            if (bonus) {
                score = 1 + cnt_b[x];
            }
            total += score;
        }
        rv[i] = total / (ld) 22;
    }
    ld max_rv = 0;
    FOR (i, 14) {
        max_rv = max(max_rv, rv[i]);
    }
    cout << fixed << setprecision(10) << max_rv << '\n';

    return 0;
}