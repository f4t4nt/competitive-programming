#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto &x : C)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

str all_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll len = 1, best_len = -1, best_runtime = 0;
    str response;
    while (len <= 20) {
        FOR (i, len) {
            cout << 'a';
        }
        cout << endl;

        getline(cin, response);
        if (response == "ACCESS GRANTED") {
            return 0;
        }
        ll i = 15, runtime = 0;
        while (response[i] != ' ') {
            runtime *= 10;
            runtime += response[i] - '0';
            i++;
        }
        if (runtime > best_runtime) {
            best_len = len;
            best_runtime = runtime;
        }
        len++;
    }

    str best_pw = "";
    FOR (i, best_len) {
        best_pw += "a";
    }

    FOR (i, best_len) {
        str pw = best_pw;
        best_runtime = 0;
        FORE (c, all_chars) {
            pw[i] = c;
            cout << pw << endl;
            getline(cin, response);
            if (response == "ACCESS GRANTED") {
                return 0;
            }
            ll j = 15, runtime = 0;
            while (response[j] != ' ') {
                runtime *= 10;
                runtime += response[j] - '0';
                j++;
            }
            if (runtime > best_runtime) {
                best_pw = pw;
                best_runtime = runtime;
            }
        }
    }

    return 0;
}