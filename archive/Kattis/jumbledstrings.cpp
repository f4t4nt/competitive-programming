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
#define sz(C) (int) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(int x = 0; x < (int) e; x++)
#define FORR(x, e) for(int x = (int) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(int x = 0; x < (int) e; x += (int) i)
#define FOBI(x, b, e, i) for(int x = (int) b; x < (int) e; x += (int) i)
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

    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    ll cnt0 = (ll) sqrt(2 * a), cnt1 = (ll) sqrt(2 * d);
    while (cnt0 * (cnt0 - 1) / 2 < a) {
        cnt0++;
    }
    while (cnt1 * (cnt1 - 1) / 2 < d) {
        cnt1++;
    }
    if (cnt0 * (cnt0 - 1) / 2 != a || cnt1 * (cnt1 - 1) / 2 != d) {
        cout << "impossible\n";
        return 0;
    }
    vector<ll> poss0 = {cnt0}, poss1 = {cnt1};
    if (cnt0 == 0) {
        poss0.pb(1);
    }
    if (cnt1 == 0) {
        poss1.pb(1);
    }
    str rv = "";
    ll b_tmp = 0, c_tmp = 0;
    bool ok = false;
    b_tmp = 0, c_tmp = 0;
    FORE (cnt_0, poss0) {
        FORE (cnt_1, poss1) {
            rv = "";
            cnt0 = cnt_0, cnt1 = cnt_1;
            while (cnt0 > 0 || cnt1 > 0) {
                if (cnt0 > 0 && b_tmp + cnt1 <= b) {
                    rv += '0';
                    b_tmp += cnt1;
                    cnt0--;
                } elif (cnt1 > 0 && c_tmp + cnt0 <= c) {
                    rv += '1';
                    c_tmp += cnt0;
                    cnt1--;
                } else {
                    break;
                }
            }
            if (b_tmp == b && c_tmp == c && cnt0 == 0 && cnt1 == 0 && sz(rv) > 0) {
                cout << rv << '\n';
                ok = true;
                break;
            }
        }
        if (ok) {
            break;
        }
    }
    if (!ok) {
        cout << "impossible\n";
    }

    return 0;
}