class Solution {
public:
   int first_occurance(vector<int>&nums, int t){
        int l=0;
        int r = nums.size()-1;
        int ans = -1;
        
        while(l<=r){
            int mid = l+(r-l)/2;
            
            if(nums[mid] == t){
                ans = mid;
                r = mid-1;
            }
            
            else if(nums[mid] < t)
                l = mid+1;
            
            else
                r = mid-1;
        
        }
        
        return ans;
    }
    
    int last_occurance(vector<int>&nums, int t){
        int l=0;
        int r = nums.size()-1;
        int ans = -1;
        
        while(l<=r){
            int mid = l+(r-l)/2;
            
            if(nums[mid] == t){
                ans = mid;
                l = mid+1;
            }
            
            else if(nums[mid] < t)
                l = mid+1;
            
            else
                r = mid-1;
        
        }
        
        return ans;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans;
        
        int fst = first_occurance(nums, target);
        int lst = last_occurance(nums, target);
        
        ans.push_back(fst);
        ans.push_back(lst);
        
        return ans;
    }
};