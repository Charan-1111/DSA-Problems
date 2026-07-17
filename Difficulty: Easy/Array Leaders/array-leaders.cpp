class Solution {
  public:
    vector<int> leaders(vector<int>& arr) {
        vector<int> res;
        
        for(int i = arr.size()-1; i >= 0; i--) {
            if(res.size() == 0 || arr[i] >= res.back()) {
                res.push_back(arr[i]);
            }
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};