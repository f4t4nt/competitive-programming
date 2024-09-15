#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) swap(nums1, nums2);
        int n1 = nums1.size(), n2 = nums2.size();
        int left = (n1 + n2 + 1) / 2;
        int lo = 0, hi = n1;

        while (lo <= hi) {
            int mid1 = (lo + hi) / 2;
            int mid2 = left - mid1;

            int l1 = (mid1 == 0) ? INT_MIN : nums1[mid1 - 1];
            int r1 = (mid1 == n1) ? INT_MAX : nums1[mid1];
            int l2 = (mid2 == 0) ? INT_MIN : nums2[mid2 - 1];
            int r2 = (mid2 == n2) ? INT_MAX : nums2[mid2];

            if (l1 <= r2 && l2 <= r1) {
                if ((n1 + n2) % 2 == 0) return (max(l1, l2) + min(r1, r2)) / 2.0;
                else return max(l1, l2);
            } else if (l1 > r2) hi = mid1 - 1;
            else lo = mid1 + 1;
        }
        return 0.0;
    }
};