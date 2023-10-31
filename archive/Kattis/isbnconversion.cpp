#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
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

// imma show YOU how great i am.

bool ok_hyphen(str &isbn10) {
    ll cnt = 0;
    FORE (c, isbn10) {
        if (c == '-') {
            cnt++;
        }
    }
    if (sz(isbn10) - cnt != 10) {
        return false;
    }
    if (isbn10[0] == '-' or isbn10.back() == '-') {
        return false;
    }
    if (cnt > 3) {
        return false;
    }
    if (cnt == 3) {
        if (isbn10[sz(isbn10) - 2] != '-') {
            return false;
        }
    }
    FOR (i, sz(isbn10) - 1) {
        if (isbn10[i] == '-' and isbn10[i + 1] == '-') {
            return false;
        }
    }
    return true;
}

bool ok_last(str &isbn10) {
    vector<ll> d;
    FOR (i, sz(isbn10)) {
        if (isbn10[i] == '-') {
            continue;
        }
        if (isbn10[i] == 'X') {
            if (i != sz(isbn10) - 1) {
                return false;
            }
            d.pb(10);
        } else {
            d.pb(isbn10[i] - '0');
        }
    }
    ll sum = 0;
    FOR (i, sz(d)) {
        sum += d[i] * (10 - i);
    }
    return sum % 11 == 0;
}

void get_last(str &isbn13) {
    vector<ll> d;
    FOR (i, sz(isbn13)) {
        if (isbn13[i] == '-') {
            continue;
        }
        d.pb(isbn13[i] - '0');
    }
    ll sum = 0;
    FOR (i, sz(d)) {
        if (i % 2 == 0) {
            sum += d[i];
        } else {
            sum += d[i] * 3;
        }
    }
    ll last = (10 - sum % 10) % 10;
    isbn13 += to_string(last);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        str isbn;
        cin >> isbn;
        if (!ok_hyphen(isbn)) {
            cout << "invalid\n";
            continue;
        }
        if (!ok_last(isbn)) {
            cout << "invalid\n";
            continue;
        }
        isbn.pop_back();
        isbn = "978-" + isbn;
        get_last(isbn);
        cout << isbn << '\n';
    }

    return 0;
}