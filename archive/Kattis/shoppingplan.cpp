#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
 
#define ll long long
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vi>
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define sl set<ll>
#define spll set<pll>
#define vsl vector<sl>
#define ssl set<sl>
#define plsl pair<ll, sl>
#define vplsl vector<plsl>
#define msl multiset<ll>
#define mspll multiset<pll>
#define vb vector<bool>
#define vvb vector<vb>
#define mll map<ll, ll>
#define mlll map<ll, mll>
#define mlvl map<ll, vl>
#define mlpll map<ll, pll>
#define mlvpll map<ll, vpll>
#define mlsl map<ll, sl>
#define mpllb map<pll, bool>
#define vmll vector<mll>
#define ql queue<ll>
#define qpll queue<pll>
#define fl float
#define vf vector<fl>
#define vvf vector<vf>
#define str string
#define vstr vector<str>
#define mstrl map<str, ll>
 
#define pb push_back
#define mp make_pair
#define elif else if
#define sz(x) (ll) x.size()
#define vsort(x) sort(x.begin(), x.end())
#define last_elem(C) (*(C.rbegin()))
#define max_elem(C) (*max_element(C.begin(), C.end()))
#define min_elem(C) (*min_element(C.begin(), C.end()))
 
#define FIND(x, v) find(x.begin(), x.end(), v)
#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= (ll) 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x >= (ll) b; x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://open.kattis.com/problems/shoppingplan

fl dist(pll &coord1, pll &coord2)
{
    ll dx = coord1.first - coord2.first, dy = coord1.second - coord2.second;
    return sqrt((fl) (dx * dx + dy * dy));
}

fl eval(vl &perm, vector<pair<pll, vl>> &stores, vvf &interstore_price, vb &perishable, ll &num_stores, ll &num_items)
{
    vvf dp(num_items, vf(num_stores, 1e18));
    dp[0][0] = 0;
    FOB(i, 1, num_items)
    {
        if(perishable[perm[i - 1]])
        {
            FOB(j, 1, num_stores)
            {
                FOR(k, num_stores)
                {
                    fl tmp = dp[i - 1][k] + interstore_price[j][k] + stores[j].second[perm[i - 1]] + interstore_price[j][0];
                    dp[i][0] = min(dp[i][0], tmp);
                    FOB(l, i + 1, num_items)
                    {
                        tmp += stores[j].second[perm[l - 1]];
                        dp[l][0] = min(dp[l][0], tmp);
                    }
                }
            }
        }
        else
        {
            FOB(j, 1, num_stores)
            {
                FOR(k, num_stores)
                {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + interstore_price[j][k] + stores[j].second[perm[i - 1]]);
                }
            }
        }
    }
    fl res = dp[num_items - 1][0];
    FOB(i, 1, num_stores) { res = min(res, dp[num_items - 1][i] + interstore_price[i][0]); }
    return res;
}

int main()
{
    ll T;
    cin >> T;
    FOR(t, T)
    {
        ll num_items, num_stores, price_of_gas;
        cin >> num_items >> num_stores >> price_of_gas;
        mstrl item_idx;
        vb perishable(num_items);
        FOR(i, num_items)
        {
            str item;
            cin >> item;
            if(last_elem(item) == '!')
            { perishable[i] = true; item = item.substr(0, sz(item) - 1); }
            item_idx[item] = i;
        }
        num_stores++;
        vector<pair<pll, vl>> stores(num_stores, { { 0, 0 }, vl(num_items, 1e18) });
        str line;
        getline(cin, line);
        FOB(i, 1, num_stores)
        {
            getline(cin, line);
            istringstream sin(line);
            ll x_pos, y_pos;
            sin >> x_pos >> y_pos;
            stores[i].first = { x_pos, y_pos };
            str item;
            while(sin >> item)
            {
                ll pos = item.find(':');
                stores[i].second[item_idx[item.substr(0, pos)]] = stol(item.substr(pos + 1, sz(item)));
            }
        }
        vvf interstore_price(num_stores, vf(num_stores));
        FOR(i, num_stores)
        {
            FOB(j, i + 1, num_stores)
            {
                interstore_price[i][j] = price_of_gas * dist(stores[i].first, stores[j].first);
                interstore_price[j][i] = interstore_price[i][j];
            }
        }
        vvl perms(1);
        FOR(i, num_items) { perms[0].pb(i); }
        perms.pb(perms[0]);
        while(next_permutation(perms[sz(perms) - 1].begin(), perms[sz(perms) - 1].end()))
        { perms.pb(perms[sz(perms) - 1]); }
        fl res = 1e18;
        num_items++;
        FOR(i, sz(perms) - 1)
        { res = min(res, eval(perms[i], stores, interstore_price, perishable, num_stores, num_items)); }
        cout << "Case #" << t + 1 << ": " << setprecision(9) << res << endl;
    }
}