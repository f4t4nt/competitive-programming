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

struct Operation {
    bool insert;
    ll idx;
    ch c;

    bool operator==(const Operation &o) const {
        return insert == o.insert && idx == o.idx && c == o.c;
    }

    bool operator!=(const Operation &o) const {
        return !(*this == o);
    }
};

void read_program(vector<Operation> &p) {
    while (true) {
        ch type;
        cin >> type;
        if (type == 'E') {
            break;
        } elif (type == 'D') {
            ll idx;
            cin >> idx;
            p.pb({false, idx, 0});
        } elif (type == 'I') {
            ll idx;
            ch c;
            cin >> idx >> c;
            p.pb({true, idx, c});
        }
    }
}

void bubble_sort(vector<Operation> &p) {
    FOB (i, 1, sz(p)) {
        for (ll j = i; j > 0; j--) {
            if (!p[j - 1].insert && !p[j].insert && p[j - 1].idx <= p[j].idx) {
                swap(p[j - 1], p[j]);
                p[j - 1].idx++;
            } elif (p[j - 1].insert && p[j].insert && p[j - 1].idx >= p[j].idx) {
                swap(p[j - 1], p[j]);
                p[j].idx++;
            } elif (p[j - 1].insert && !p[j].insert) {
                if (p[j - 1].idx > p[j].idx) {
                    swap(p[j - 1], p[j]);
                    p[j].idx--;
                } elif (p[j - 1].idx == p[j].idx) {
                    p.erase(p.begin() + j - 1, p.begin() + j + 1);
                    i -= 2;
                    break;
                } else {
                    swap(p[j - 1], p[j]);
                    p[j - 1].idx--;
                }
            } else {
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    vector<Operation> p1, p2;
    read_program(p1);
    read_program(p2);

    bubble_sort(p1);
    bubble_sort(p2);

    cout << (p1 == p2 ? 0 : 1) << '\n';

    return 0;
}