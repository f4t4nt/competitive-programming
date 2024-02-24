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
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll  m, n;
    cin >> m >> n;
    ll alice, bob;
    ll a, b;
    alice=0; bob=0;
    FOR (i, m)
    {
        cin >> a;
        alice+=a;
        alice+=1;
    }
    FOR (i, n)
    {
        cin >> b;
        bob+=b;
        bob+=1;
    }
    if (alice>bob)
    {
        cout << "ALICE" << endl;
    }
    else if (alice<bob)
    {
        cout << "BOB" << endl;
    }
    else
        cout << "TIED" << endl;

}