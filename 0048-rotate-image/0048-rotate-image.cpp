class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
       int n = matrix.size();
       int m = matrix[0].size();
        
        vector<int> v;
        for(int i=n-1; i>=0; i--){
            for(int j=0; j<m; j++)
                v.push_back(matrix[i][j]);
        }
        
        
        int k=0;
        for(int j=0; j<m; j++){
            for(int i=0; i<n; i++){
                matrix[i][j] = v[k];
                k++;
            }
        }
        
        
    }
};