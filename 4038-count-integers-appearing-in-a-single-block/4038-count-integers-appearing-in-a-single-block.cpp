class Solution {
public:
    int countSpecialIntegers(vector<int>& nums) {
        int cnt = 0;

        unordered_map<int, int> mp;
        unordered_map<int, bool> used;

        for(int i=0; i<nums.size(); i++) {
            if(mp.find(nums[i]) != mp.end()) {
                if(i != mp[nums[i]]+1) {
                    if(used.find(nums[i]) == used.end()) {
                     cnt--;
                        used[nums[i]] = true;
                    }
                } else {
                    mp[nums[i]] = i;
                }
            } else {
                cnt++;
                mp[nums[i]] = i;
            }
        }

        return cnt;
    }
};