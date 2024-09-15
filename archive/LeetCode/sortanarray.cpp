#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        // sort(nums.begin(), nums.end());
        // return nums;
        vector<int> ref(1e5 + 1);
        for (int x : nums) ref[x + 5e4]++;
        int idx = 0;
        for (int i = 0; i < ref.size(); i++) while(ref[i]--) nums[idx++] = i - 5e4;
        return nums;
    }
};