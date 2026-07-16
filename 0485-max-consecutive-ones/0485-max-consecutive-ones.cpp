class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();

        int maxVal = 0;

        int val = 0;

        for(int i=0; i<n; i++) {
            if(nums[i] == 1) {
                val++;
            } else {
                maxVal = max(maxVal, val);
                val = 0;
            }
        }

        maxVal = max(maxVal, val);

        return maxVal;
    }
};