class Solution {
public:
    int maxDistance(string moves) {
        int n = moves.length();
    
        int x = 0, y = 0;
        
        unordered_map<char, vector<int>> dir;
        dir['L'] = {-1, 0};
        dir['R'] = {1, 0};
        dir['U'] = {0, 1};
        dir['D'] = {0, -1};
    
        int cnt = 0;

        for(int i=0; i<n; i++) {
            if(moves[i] == '_') {
                cnt++;
            } else {
                x = x + dir[moves[i]][0];
                y = y + dir[moves[i]][1];
            }
        }
        
        return abs(x) + abs(y) + cnt;
    }
};