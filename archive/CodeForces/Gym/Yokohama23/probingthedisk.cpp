#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

ld query(ll qx0, ll qy0, ll qx1, ll qy1) {
    cout << "query " << qx0 << " " << qy0 << " " <<
        qx1 << " " << qy1 << endl;
    ld ret; cin >> ret;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll qy = -99;
    ld ret = 0;
    do {
        // cout << "query " << 0 << " " << qy << " " << 100000 << " " << qy << endl;
        // cin >> ret;
        qy += 199;
        ret = query(0, qy, 1e5, qy);
    } while (ret == 0);
    ld span = ret;
    ll loy = 0, hiy = qy;
    while (loy < hiy) {
        ll midy = (loy + hiy + 1) / 2;
        // cout << "query " << 0 << " " << midy << " " << 100000 << " " << midy << endl;
        // cin >> ret;
        ret = query(0, midy, 1e5, midy);
        if (ret == 0) loy = midy;
        else hiy = midy - 1;
    }
    ld dy = qy - loy;
    ld diameter = (span * span) / (4 * dy) + dy;
    diameter = round(diameter);
    assert((ll) diameter % 2 == 0);
    ll radius = diameter / 2;
    ll cy = loy + radius;
    ll lox = 0, hix = 1e5;
    while (lox < hix) {
        ll midx = (lox + hix + 1) / 2;
        // cout << "query " << 0 << " " << cy << " " << midx << " " << cy << endl;
        // cin >> ret;
        ret = query(0, cy, midx, cy);
        if (ret == 0) lox = midx;
        else hix = midx - 1;
    }
    ll cx = lox + radius;
    cout << "answer " << cx << " " << cy << " " << radius << endl;

    return 0;
}