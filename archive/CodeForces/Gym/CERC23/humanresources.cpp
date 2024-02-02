#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

map<string, int> nums;
string names[700];
ll cnt=1;

vector<int> adja[700];

//bool vis[700];

string ans;
vector<int> namelist;
vector<string> namesinorder;

/*void dfs(int pos)
{
    //vis[pos]=true;
    for (int i=0; i<adja[pos].size(); i++)
        ans+="1";
    ans+="0";
    //namelist.pb(pos);
    for (int i=0; i<adja[pos].size(); i++)
    {
        namelist.pb(adja[pos][i]);
    }
    for (int i=0; i<adja[pos].size(); i++)
    {
        dfs(adja[pos][i]);
    }

}*/

int main()
{
    string s;
    cin >> s;
    if (s=="ENCODE")
    {
        string t;
        int curcnt;
        while (cin >> t)
        {
            //if (t == "quit") break;
            if (t[t.length()-1]==':')
            {
                t=t.substr(0, t.length()-1);
                if (!nums[t])
                {
                    nums[t]=cnt;
                    names[cnt]=t;
                    cnt++;
                }
                curcnt=nums[t];
            }
            else
            {
                if (!nums[t])
                {
                    nums[t]=cnt;
                    names[cnt]=t;
                    cnt++;
                }
                adja[curcnt].pb(nums[t]);
            }
        }
        //cout << "hi" << endl;
        //cout << adja[1][0] << " " << adja[1][1] << endl;
        //cout << adja[2][0] << " " << adja[2][1] << endl;
        //cout << adja[3][0] << " " << adja[3][1] << endl;

        //cout << "made it" << endl;
        namelist.pb(1);
        queue<int> q;
        q.push(1);
        while (!q.empty())
        {
            int pos=q.front();
            q.pop();
            for (int i=0; i<adja[pos].size(); i++)
                ans+="1";
            ans+="0";
            //namelist.pb(pos);
            for (int i=0; i<adja[pos].size(); i++)
            {
                namelist.pb(adja[pos][i]);
                q.push(adja[pos][i]);
            }   
        }

        /*for (int i=1; i<cnt; i++)
        {
            if (!vis[i])
            {
                dfs(i);
            }
        }*/
        for (int i=0; i<namelist.size(); i++)
            cout << names[namelist[i]] << endl;
        cout << ans << endl;
    }
    else
    {
        string t;
        while (cin >> t)
        {
            //if (t=="quit") break;
            if (t[0]=='0' || t[0]=='1')
            {
                int curpos=0;
                int curstrpos=0;
                for (int i=0; i<namesinorder.size(); i++)
                {
                    int anssum=0;
                    while (t[curstrpos]=='1')
                    {
                        anssum++;
                        curstrpos++;
                    }
                    curstrpos++;
                    if (curpos==i)
                        curpos++;
                    if (anssum>0)
                    {
                        cout << namesinorder[i] << ":";
                        for (int j=0; j<anssum; j++)
                        {
                            cout << " " << namesinorder[curpos+j];
                        }
                        cout << endl;
                        curpos+=anssum;
                    }
                }
            }
            else
            {
                namesinorder.pb(t);
            }
        }
    }
}