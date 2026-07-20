class Solution {
  public:
    int maxLength(vector<int>& arr) {
        int n = arr.size();
        
        unordered_map<int, int> mp;
        
        int maxLen = INT_MIN;
        
        int sum = 0;
        
        for(int i=0; i<n; i++) {
            sum = sum + arr[i];
            
            if(sum == 0) {
                maxLen = max(maxLen, i+1);
            } else {
                if(mp.find(sum) != mp.end()) {
                    maxLen = max(maxLen, i-mp[sum]);
                }
            }
            
            if(mp.find(sum) == mp.end()) {
                mp[sum] = i;
            }
        }
        
        return maxLen == INT_MIN ? 0 : maxLen;
    }
};