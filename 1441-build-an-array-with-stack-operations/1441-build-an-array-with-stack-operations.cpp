class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> res;

        int i = 0;

        unordered_map<int, int> mp;
        for(int num : target) {
            mp[num]++;
        }

        stack<int> st;

        int k = 1;
        while(k <= n && i < target.size()) {
            if(mp.find(k) == mp.end()) {
                res.push_back("Push");
                res.push_back("Pop");
            } else {
                res.push_back("Push");
                i++;
            }
            k++;
        }

        return res;
    }
};