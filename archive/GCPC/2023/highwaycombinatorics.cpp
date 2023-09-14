#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <set>
#include <queue>
#include <map>

using namespace std;

#define int long long

typedef vector<int> vi;
typedef pair<int, int> ii;

#define rep(i, n) for (int i = 0 ; i < n ; i++)
#define rrep(i, a, b) for (int i = a ; i < b ; i++)
#define pb push_back

int INF = 2000000000LL;
int MOD = 1000000007;

int modpow(int n, int k) {
    int s = n;
    int ans = 1LL;
    
    rep(i, 60) {
        if ((1LL << i) & k) {
            ans = (ans * s) % MOD;
        }
        
        s = (s * s) % MOD;
    }
    
    return ans;
}

int inv(int n) {
    return modpow(n, MOD - 2);
}

int32_t main() {
    
    int n;
    cin >> n;
    
    int ITERS = 700000;
    
    if (n == 0) {
        cout << ".##" << endl;
        cout << "##." << endl;
        return 0;
    }
    
    bool blocked[ITERS][99];
    
    vi fib;
    fib.pb(1LL);
    fib.pb(1LL);
    
    rep(i, 205) {
        fib.pb((fib[fib.size() - 1] + fib[fib.size() - 2]) % MOD);
    }
    
    vi vals;
    
    map<int, int> seen;
    
    rep(x, ITERS) {
        
        rep(i, 99) {
            if (rand() % 18 < 1) {
                blocked[x][i] = true;
            }
            else {
                blocked[x][i] = false;
            }
        }
        
        int ans = 1LL;
        int ct = 0;
        
        rep(i, 99) {
            if (blocked[x][i]) {
                ans = (ans * fib[ct]) % MOD;
                ct = 0;
            }
            else {
                ct++;
            }
        }
        
        ans = (ans * fib[ct]) % MOD;
        
    //    cout << ans << endl;
    //    cout << (n * inv(ans)) % MOD << endl;
        
        if (seen[(n * inv(ans)) % MOD] > 0) {
            int prev = seen[(n * inv(ans)) % MOD] - 1;
            
            string s = "";
            string t = "";
            
            int cct = 0;
            int aa = 1LL;
            
            rep(i, 99) {
                if (blocked[prev][i]) {
                    s += '#';
                    t += '#';
                //    cout << cct << " " << fib[cct] << endl;
                    aa = (aa * fib[cct]) % MOD;
                    cct = 0;
                }
                else {
                    s += '.';
                    t += '.';
                    cct++;
                }
            }
            
            //0 1 2 3 4 5 6
            //1 1 2 3 5 8 13
            s += '#';
            t += '#';
            
            cct = 0;
            
            rep(i, 99) {
                if (blocked[x][i]) {
                    s += '#';
                    t += '#';
                    aa = (aa * fib[cct]) % MOD;
                    cct = 0;
                }
                else {
                    s += '.';
                    t += '.';
                    cct++;
                }
            }
            
         //   cout << aa << endl;
            cout << s << '\n';
            cout << t << '\n';
            
            return 0;
            
        }
        
        seen[ans] = x + 1;
        
    }
    
    cout << ":(" << endl;
    
}