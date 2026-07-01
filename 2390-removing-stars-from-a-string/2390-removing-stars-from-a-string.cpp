class Solution {
public:
    string removeStars(string s) {
        string res;

        for(char ch : s) {
            if(ch != '*') {
                res.push_back(ch);
            } else {
                res.pop_back();
            }
        }

        return res;
    }
};