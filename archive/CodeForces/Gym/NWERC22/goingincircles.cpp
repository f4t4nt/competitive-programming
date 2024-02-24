#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define x first
#define y second
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

ll tracker = 0;

ll move_right() {
    tracker++;
    cout << "? right" << endl;
    ll res; cin >> res;
    return res;
}

ll move_left() {
    tracker--;
    cout << "? left" << endl;
    ll res; cin >> res;
    return res;
}

ll flip() {
    cout << "? flip" << endl;
    ll res; cin >> res;
    return res;
}

const ll NUM1 = 200;
const ll NUM2 = 200;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    vector<ll> part1(NUM1);
    cin >> part1[0];
    FOR (i, NUM1 - 1) {
        part1[i + 1] = move_right();
    }
    flip();
    for (ll i = NUM1 - 2; i >= 0; i--) {
        if (move_left() != part1[i]) {
            cout << "! " << NUM1 - i - 1 << endl;
            return 0;
        }
    }

    bitset<NUM2> marker, cur;
    FOR (i, NUM2) {
        marker[i] = move_right();
        if (rand() & 1) marker[i] = flip();
    }
    ll pin = tracker;
    cur = marker;
    do {
        cur >>= 1;
        cur[NUM2 - 1] = move_right();
    } while (cur != marker);
    cout << "! " << tracker - pin << endl;

    return 0;
}