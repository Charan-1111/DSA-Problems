class Solution {
  public:
    vector<int> findTwoElement(vector<int>& arr) {
        unordered_map<int, int> mp;
        int repeat;
        
        for(int num : arr) {
            mp[num]++;
            
            if(mp[num] == 2) {
                repeat = num;
            }
        }
        
        int miss;
        
        for(int i=1; i<=arr.size(); i++) {
            if(mp.find(i) == mp.end()) {
                miss = i;
                break;
            }
        }
        
        return {repeat, miss};
    }
};