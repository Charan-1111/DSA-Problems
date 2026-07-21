class Solution {
  public:
    long subarrayXor(vector<int> &arr, int k) {
        long res = 0;
        
        int n = arr.size();
        
        unordered_map<int, int> mp;
        
        int val = 0;
        
        for(int i=0; i<n; i++) {
            val = val ^ arr[i];
            
            if(val == k) {
                res += 1;
            }
            
            if(mp.find(val^k) != mp.end()) {
                res = res + mp[val^k];
            }
            
            mp[val]++;
        }
        
        return res;
    }
};