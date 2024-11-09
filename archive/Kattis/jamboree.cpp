#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool good(vector<int>& nums, ll mx, int M){
    int N = int(nums.size());
    sort(nums.begin(), nums.end());
    vector<int> taken(N);
    for(int i = 0; i<N; i++) {
        if(taken[i]) continue;
        if(nums[i] > mx) return false;
        M--;
        for(int j = N-1; j>=0; j--){
            if(!taken[j] && nums[j] <= mx - nums[i]){
                taken[j] = 1; break;
            }
        }
        taken[i] = true;
    }   
    return M >= 0;
}


int main() {
    int N, M; cin >> N >> M;
    vector<int> nums(N);
    for(int i = 0; i<N; i++) cin >> nums[i];

    ll l = 1, r = 1e9 + 100;

    while(l < r){
        ll mid = (l + r) / 2;
        if(good(nums, mid, M)){
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    cout << r << endl;
    return 0;
}