#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;

typedef vector<int> vi;

#define int long long
#define rep(i, n) for (int i = 0 ; i < n ; i++)
#define pb push_back

int INF = 2e9;

int32_t main() {
    
    int p, n;
    cin >> p >> n;
    
    priority_queue<pair<pair<int, int>, pair<int, pair<char, int>>>> q;
    
    rep(i, n) {
        int t, f;
        char s;
        cin >> t >> f >> s;
        
        q.push({{-t, -1}, {f, {s, i}}});
    }
    
    queue<pair<int, int>> pm[p * 2];
    bool oc[p * 4];
    
    memset(oc, false, sizeof oc);
    
    int fin[n];
    
    while (q.size()) {
        pair<pair<int, int>, pair<int, pair<char, int>>> cur = q.top();
        q.pop();
        
        int t = -cur.first.first;
        int stat = cur.first.second;
        int dur = cur.second.first;
        char side = cur.second.second.first;
        int ind = cur.second.second.second;
        
     //   cout << t << " " << stat << " " << dur << " " << side << " " << ind << endl;
        
        /*cout << t << endl;
        rep(i, p * 2) cout << pm[i].size() << " ";
        cout << endl;*/
        
     /*   cout << t << " " << ind << " " << stat << endl;
        rep(i, p*2) cout << pm[i].size() << " ";
        cout << endl;*/
        
        if (stat == -1) {
            int addon = 0;
            if (side == 'R') {
                addon += 2;
            }
                        
            int new_ind = -1;
            
            rep(i, p) {
                if (!oc[i * 4 + addon]) {
                    if (!oc[i * 4 + addon + 1]) {
                        new_ind = i * 4 + addon + 1;
                    }
                    else {
                        new_ind = i * 4 + addon;
                    }
                    break;
                }
            }
            
            if (new_ind != -1) {
                oc[new_ind] = true;
                q.push({{-(t + dur), new_ind}, {dur, {side, ind}}});
            }
            else {
                int mn = INF;
                int mni = -1;
                
                rep(i, p) {
                    if (pm[i * 2 + addon/2].size() < mn) {
                        mn = pm[i * 2 + addon/2].size();
                        mni = i * 2 + addon/2;
                    }
                }
                
                pm[mni].push({dur, ind});
            }
        }
        else {
            int addon = 0;
            if (side == 'R') {
                addon += 2;
            }
            
            fin[ind] = t;
            
            oc[stat] = false;
            
            //cout << "stat: " << stat << endl;
            
            if (stat % 2 == 0) {
                if (pm[stat / 2].size()) {
                    pair<int, int> front = pm[stat / 2].front();
                    int fd = front.first;
                    int fi = front.second;
                    pm[stat / 2].pop();
                    
                    int new_stat = stat;
                    if (!oc[stat + 1]) {
                        new_stat++;
                    }
                    
                    oc[new_stat] = true;
                    
                    q.push({{-(t + fd), new_stat}, {fd, {side, fi}}});
                }
                
                if (!oc[stat] && pm[stat / 2].size()) {
                    pair<int, int> front = pm[stat / 2].front();
                    int fd = front.first;
                    int fi = front.second;
                    pm[stat / 2].pop();
                    
                    oc[stat] = true;
                    
                    q.push({{-(t + fd), stat}, {fd, {side, fi}}});
                }
            }
        }
    }
    
    rep(i, n) cout << fin[i] << '\n';
}