class Solution {
public:
    long long maxSum(vector<int>& nums, int k, int mul) {
        sort(nums.begin(), nums.end());
        
        int n = nums.size();
        
        long long total = 0;
        
        for(int i=n-1; i>=0; i--) {
            if(k == 0) break;
            k--;
            
            if(nums[i] > 0) {
                if(mul > 0) {
                    // total = total + static_cast<long long>(mul * nums[i]);
                    total += 1LL * mul * nums[i];
                    mul--;
                } else {
                    total = total + nums[i];
                }
            } else {
                if(mul < 0) {
                    total += 1LL * mul * nums[i];
                    mul--;
                } else {
                    total = total + nums[i];
                }
            }
        }
        
        return total;
    }
};