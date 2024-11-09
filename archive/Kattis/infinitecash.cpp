#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define f first
// #define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

const ll MAX_DAYS = 2e6;
const ll INF = 1e12;

str add(str &a, str &b) {
    ll la = sz(a), lb = sz(b);
    ll max_len = max(la, lb);
    str result(max_len + 1, '0');
    bool carry = false;

    FOR (i, max_len) {
        ll bit_a = (i < la) ? a[la - 1 - i] - '0' : 0;
        ll bit_b = (i < lb) ? b[lb - 1 - i] - '0' : 0;
        ll sum = bit_a + bit_b + carry;
        result[max_len - i] = '0' + (sum % 2);
        carry = (sum > 1);
    }
    
    result[0] = carry ? '1' : '0';
    return result[0] == '0' ? result.substr(1) : result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    str s_str, d_str, m_str; cin >> s_str >> d_str >> m_str;
    ll day = 0, d = INF;
    if (sz(d_str) < 30) {
        d = 0;
        ll tmp = 1;
        FORR (i, sz(d_str)) {
            if (d_str[i] == '1') d |= tmp;
            tmp <<= 1;
        }
    }
    while (sz(m_str) && day < MAX_DAYS) {
        m_str.pop_back();
        day++;
        if (day > 0 && day % d == 0) {
            m_str = add(m_str, s_str);
        }
    }
    if (day == MAX_DAYS) cout << "Infinite money!" << endl;
    else {
        string res = "";
        while (day) {
            res += '0' + (day & 1);
            day >>= 1;
        }
        flip(res);
        cout << res << endl;
    }

    return 0;
}