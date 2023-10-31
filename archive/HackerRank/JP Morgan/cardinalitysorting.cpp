#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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

int bitcount(int x) {
    int cnt = 0;
    while (x) {
        x &= (x - 1);
        cnt++;
    }
    return cnt;
}

vector<int> cardinalitySort(vector<int> nums) {
    sort(nums.begin(), nums.end(), [](int a, int b) {
        int ac = bitcount(a);
        int bc = bitcount(b);
        if (ac == bc) {
            return a < b;
        }
        return ac < bc;
    });
    return nums;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> nums(n);
    FORE (x, nums) {
        cin >> x;
    }
    vector<int> rv = cardinalitySort(nums);
    FORE (x, rv) {
        cout << x << '\n';
    }

    return 0;
}