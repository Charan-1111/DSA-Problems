class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        set<vector<int>>s;
        for(int i=0; i<=n-3; i++){
            int sum = -nums[i];
            int j=i+1, k=n-1;
            
            while(j<k){
                int a = nums[j]+nums[k];
                if(a == sum){
                    s.insert({nums[i], nums[j], nums[k]});
                    j++, k--;
                }
                
                else if(a > sum)
                    k--;
                else
                    j++;
            }
        }
        
        vector<vector<int>> res;
        for(auto x : s)
            res.push_back(x);
        
        return res;
    }
};