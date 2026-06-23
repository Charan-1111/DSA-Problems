class Solution {
public:
    bool isValid(long long num, int x) {
        if(num < 10) return num == x;
        
        bool valid = (num%10) == x;
        num = num / 10;
    
        while(num >= 10) {
            num = num / 10;
        }
    
        valid = valid && (num == x);
        
        return valid;
    }
    
    int countValidSubarrays(vector<int>& nums, int x) {
        int cnt = 0;
    
        int n = nums.size();

        for(int i=0; i<n; i++) {
            long long sum = 0;
            for(int j=i; j<n; j++) {
                sum = sum + nums[j];
                cnt = cnt + isValid(sum, x);
            }
        }
    
        return cnt;
    }
};