#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        map<char, int> ref;
        ref['I'] = 1;
        ref['V'] = 5;
        ref['X'] = 10;
        ref['L'] = 50;
        ref['C'] = 100;
        ref['D'] = 500;
        ref['M'] = 1000;
        vector<int> sint;
        for (char c : s) sint.push_back(ref[c]);
        int ans = 0, mx = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (sint[i] < mx) {
                ans -= sint[i];
            } else {
                ans += sint[i];
                mx = max(mx, sint[i]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}