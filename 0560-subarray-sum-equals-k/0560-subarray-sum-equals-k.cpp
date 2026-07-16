class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;

        int sum = 0;

        int res = 0;

        for(int i = 0; i < nums.size(); i++) {
            sum = sum + nums[i];

            if(sum == k) {
                res = res + 1;
            }
            
            if(mp.find(sum-k) != mp.end()) {
                res = res + mp[sum-k];
            }

            mp[sum]++;
        }

        return res;
    }
};