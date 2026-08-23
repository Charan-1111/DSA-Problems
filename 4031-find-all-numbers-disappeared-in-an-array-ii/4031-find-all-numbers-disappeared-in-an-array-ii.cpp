class Solution {
public:
    vector<vector<int>> findDisappearedNumbers(vector<int>& nums, int lower, int upper) {
        unordered_map<int, int> mp;

        for(int num : nums)
            mp[num]++;

        vector<vector<int>> res;

        int missStart = -1;
        int missEnd = -1;

        for(int i=lower; i<= upper; i++) {
            if(mp.find(i) == mp.end()) {
                if(missStart == -1) {
                    missStart = i;
                }

                missEnd = i;
            } else {
                if(missStart != -1) {
                    res.push_back({missStart, missEnd});

                missStart = -1;
                missEnd = -1;
                }
            }
        }

        if(missStart != -1)
            res.push_back({missStart, missEnd});

        return res;
    }
};