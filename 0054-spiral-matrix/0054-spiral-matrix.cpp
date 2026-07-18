class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> traversal;
        int n = matrix.size();
        int m = matrix[0].size();
        
        int l = 0, r = m-1, t=0, b = n-1;
        
        int div = 0;
        
        while(l<=r && t<=b){
            if(div == 0){
                for(int i=l; i<=r; i++){
                    traversal.push_back(matrix[t][i]);
                }
                t++;
            }
            
            else if(div == 1){
                for(int i=t; i<=b; i++){
                    traversal.push_back(matrix[i][r]);
                }
                r--;
            }
            
            else if(div ==2){
        
                for(int i=r; i>=l; i--)
                    traversal.push_back(matrix[b][i]);
                b--;
            }
            
            else if(div == 3){
                for(int i=b; i>=t; i--)
                    traversal.push_back(matrix[i][l]);
                l++;
            }
            
            div = (div+1)%4;
        }
        
        return traversal;
            
    }
};