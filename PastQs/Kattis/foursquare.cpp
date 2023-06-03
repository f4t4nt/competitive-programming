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

struct Rect {
    ll w, h;
};

bool ok(vector<Rect> &r) {
    if (r[0].h + r[2].h == r[1].h + r[3].h &&
        r[0].h + r[2].h == r[0].w + r[1].w &&
        r[0].w == r[2].w &&
        r[1].w == r[3].w)
    { return true; }
    if (r[0].h == r[1].h &&
        r[0].h == r[2].h &&
        r[0].h == r[3].h &&
        r[0].h == r[0].w + r[1].w + r[2].w + r[3].w)
    { return true; }
    if (r[0].h == r[1].h &&
        r[0].w + r[1].w == r[3].w &&
        r[0].h + r[3].h == r[2].h &&
        r[2].h == r[2].w + r[3].w)
    { return true; }
    if (r[0].h == r[1].h &&
        r[2].w == r[3].w &&
        r[0].w + r[1].w == r[2].w &&
        r[0].h + r[2].h + r[3].h == r[3].w)
    { return true; }
    if (r[0].h == r[1].h &&
        r[0].h == r[2].h &&
        r[0].w + r[1].w + r[2].w == r[3].w &&
        r[0].h + r[3].h == r[3].w)
    { return true; }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<Rect> r0(4);
    FOR (i, 4) {
        cin >> r0[i].w >> r0[i].h;
    }

    vector<ll> p = {0,1,2,3};
    do {
        FOR (x, 16) {
            vector<Rect> r(4);
            FOR (i, 4) {
                r[i] = r0[p[i]];
            }
            FOR (i, 4) {
                if (x & (1 << i)) {
                    swap(r[i].w, r[i].h);
                }
            }
            if (ok(r)) {
                cout << 1 << '\n';
                return 0;
            }
        }
    } while (next_permutation(all(p)));

    cout << 0 << '\n';
    return 0;
}