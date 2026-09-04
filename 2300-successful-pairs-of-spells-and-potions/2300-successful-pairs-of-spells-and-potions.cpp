class Solution {
public:
    int bin_search(vector<int> &v, int m, long long t){
        int l = 0;
        int r = v.size()-1;
        
        int ans = -1;
        
        while(l<=r){
            int mid = l + (r-l)/2;
            
            if((long long)v[mid] * m >= t){
                ans = mid;
                r = mid-1;
            }
            
            else
                l = mid+1;
        }
        
        return ans;
    }
    
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int n = spells.size();
        int m = potions.size();
        
        sort(potions.begin(), potions.end());
        
        vector<int> pairs(n,0);
        
        for(int i=0; i<n; i++){
            int idx = bin_search(potions, spells[i], success);
            
            if(idx != -1){
                pairs[i] = m - idx;
            }
        }
        
        return pairs;
    }
};