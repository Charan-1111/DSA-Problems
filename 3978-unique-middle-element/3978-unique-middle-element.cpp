class Solution {
public:
    bool isMiddleElementUnique(vector<int>& nums) {
        unordered_map<int, int> mp;

        int n = nums.size();
        int mid = n >> 1;

        for(int i=0; i < n; i++) {
            mp[nums[i]]++;
            if(mp.find(nums[mid]) != mp.end() && mp[nums[mid]] > 1) {
                return false;
            }   
        }

        return true;
    }
};