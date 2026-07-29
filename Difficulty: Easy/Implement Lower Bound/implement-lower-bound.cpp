class Solution {
  public:
    int lowerBound(vector<int>& arr, int target) {
        int l = 0;
        int r = arr.size()-1;
        
        int res = arr.size();
        
        while(l <= r) {
            int mid = l + ((r-l)>>1);
            
            if(arr[mid] >= target) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        
        return res;
    }
};
