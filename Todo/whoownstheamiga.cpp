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

// https://open.kattis.com/problems/amiga

str obj[] = {
    "1", "2", "3", "4", "5",
    "blue", "green", "red", "white", "yellow",
    "anna", "bernhard", "chris", "david", "ellen",
    "danish", "finish", "icelandic", "norwegian", "swedish",
    "amiga", "atari", "linux", "mac", "windows",
    "c", "c++", "java", "pascal", "perl"
};
str rel[] = {"same-as", "left-of", "right-of", "next-to"};

bool validate(vector<ll> &pos, vector<tuple<ll, ll, ll>> &rels) {
    FORE (rel, rels) {
        ll o1, r, o2;
        tie(o1, r, o2) = rel;
        if (pos[o1] == -1 || pos[o2] == -1) {
            continue;
        } elif (r == 0) {
            if (pos[o1] != pos[o2]) {
                return false;
            }
        } elif (r == 1) {
            if (pos[o1] != pos[o2] - 1) {
                return false;
            }
        } elif (r == 2) {
            if (pos[o1] != pos[o2] + 1) {
                return false;
            }
        } elif (r == 3) {
            if (abs(pos[o1] - pos[o2]) != 1) {
                return false;
            }
        }
    }
    return true;
}

void dfs(
    ll obj_t,
    ll obj_i,
    vector<ll> &pos,
    vector<ll> &ord,
    vector<tuple<ll, ll, ll>> &rels,
    set<ll> &rv
) {
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    map<str, ll> obj_m, rel_m;
    FOR (i, 30) obj_m[obj[i]] = i;
    FOR (i, 4) rel_m[rel[i]] = i;

    ll T;
    cin >> T;
    for (ll t = 1; t <= T; t++) {
        ll n;
        cin >> n;
        vector<pair<ll, ll>> cnts(6);
        FOR (i, 6) cnts[i] = mp(0, i);
        vector<tuple<ll, ll, ll>> rels(n);
        FOR (i, n) {
            str o1, r, o2;
            cin >> o1 >> r >> o2;
            rels[i] = mt(obj_m[o1], rel_m[r], obj_m[o2]);
            cnts[obj_m[o1] / 5].first++;
            cnts[obj_m[o2] / 5].first++;
        }
        rsort(cnts);
        vector<ll> ord(6);
        FOR (i, 6) ord[i] = cnts[i].second;
        set<ll> rv;
        vector<ll> pos(30, -1);
        dfs(0, 0, pos, ord, rels, rv);
        cout << "scenario #" << t << ": ";
        if (sz(rv) == 0) {
            cout << "impossible.\n";
        } elif (sz(rv) == 1) {
            cout << *rv.begin() << " owns the amiga.\n";
        } else {
            cout << "cannot identify the amiga owner.\n";
        }
    }

    return 0;
}