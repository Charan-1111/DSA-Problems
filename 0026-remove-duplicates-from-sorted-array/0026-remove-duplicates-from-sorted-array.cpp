class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int idx = 0;

        int lastVal = -10000000000000000;

        for(int i=0; i<nums.size(); i++) {
            if(nums[i] != lastVal) {
                lastVal = nums[i];
                nums[idx] = lastVal;
                idx++;
            }
        }

        return idx;
    }
};