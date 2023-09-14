#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;

#define rep(i, n) for (int i = 0 ; i < n ; i++)
#define pb push_back
#define int long long

int32_t main() {
    string s;
    cin >> s;
    
    int n = s.length();
    
    rep(i, n) {
        s[i] = (char) (((int)s[i]) + 32);
    }
    
    for (int i = 0 ; i < n - 1 ; i++) {
        if (s[i] == 's' && s[i + 1] == 's') {
            if (i < n - 2 && s[i + 2] == 's') {
                string t = "";
                string u = "";
                string v = "";
                
                for (int j = 0 ; j < i ; j++) {
                    t += s[j];
                    u += s[j];
                    v += s[j];
                }
                
                t += 's';
                t += 'B';
                u += 'B';
                u += 's';
                v += 's';
                v += 's';
                v += 's';
                
                for (int j = i + 3 ; j < n ; j++) {
                    t += s[j];
                    u += s[j];
                    v += s[j];
                }
                
                cout << t << '\n';
                cout << u << '\n';
                cout << v << '\n';
                
                return 0;
            }
            else {
                string t = "";
                string u = "";
                
                for (int j = 0 ; j < i ; j++) {
                    t += s[j];
                    u += s[j];
                }
                
                t += 'B';
                u += 's';
                u += 's';
                
                for (int j = i + 2 ; j < n ; j++) {
                    t += s[j];
                    u += s[j];
                }
                
                cout << t << '\n';
                cout << u << '\n';
                
                return 0;
            }
        }
    }
    
    cout << s << '\n';
}