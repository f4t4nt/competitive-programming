#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<int, int> pii;

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)
#define MOD 9302023
#define pb push_back

int n;
string s;


ll dp[1000001];
ll dpnum[1000001];

int main() {
    vector<string> dig;
dig.pb("zero"); dig.pb("one"); dig.pb("two"); dig.pb("three");
dig.pb("four"); dig.pb("five"); dig.pb("six"); dig.pb("seven");
dig.pb("eight"); dig.pb("nine");
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> s;
    n=s.size();
    dpnum[0]=1;
    for (int i=1; i<=n; i++)
    {
        dp[i]=dp[i-1]+1;
        for (int j=0; j<10; j++)
        {
            if (dig[j].size()<=i && s.substr(i-dig[j].size(), dig[j].size())==dig[j])
            {
                dp[i]=min(dp[i], dp[i-dig[j].size()]+1);
            }
        }
        if (dp[i]==dp[i-1]+1)
        {
            dpnum[i]+=dpnum[i-1];
            dpnum[i]%=MOD;
        }
        for (int j=0; j<10; j++)
        {
            if (dig[j].size()<=i && s.substr(i-dig[j].size(), dig[j].size())==dig[j])
            {
                if (dp[i]==dp[i-dig[j].size()]+1)
                {
                    dpnum[i]+=dpnum[i-dig[j].size()];
                    dpnum[i]%=MOD;
                }
            }
        }
    }
    cout << dp[n] << endl << dpnum[n] << endl;


}