
// User function template for C++

class Solution {
  public:
    int celebrity(vector<vector<int> >& mat) {
        // code here
        int n = mat.size();
        
        
        stack<int> s;
        
        for(int j=0; j<n; j++){
            int known_cnt = 0;
            for(int i=0; i<n; i++){
                known_cnt += (mat[i][j] == 1);
            }
            
            if(known_cnt == n)
            s.push(j);
        }
        
        
        
        while(!s.empty()) {
            int celeb = s.top();
            s.pop();
            
            bool isOk = true;
            for(int j=0; j<n; j++){
                if(j != celeb && mat[celeb][j] == 1) {
                    isOk = isOk && false;
                }
            }
            
            if(isOk)
            return celeb;
        }
        
        return -1;
    }
};

