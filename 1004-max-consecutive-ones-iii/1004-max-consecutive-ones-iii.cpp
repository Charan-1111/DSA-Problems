class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();

        int last = 0;
        int len = 0;

        int zero_cnt = 0;

        for(int i=0; i<n; i++) {
            if(nums[i] == 0) {
                zero_cnt++;
            }

            while(zero_cnt > k) {
                if(nums[last] == 0) {
                    zero_cnt--;
                }
                last++;
            }

            
            len = max(len, i-last+1);
        }

        return len;
    }
};