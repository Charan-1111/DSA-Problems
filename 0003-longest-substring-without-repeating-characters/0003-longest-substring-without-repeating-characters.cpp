class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        int len = 0;
        int lastIdx = 0;

        unordered_map<char, int> mp;

        for(int i=0; i<s.length(); i++) {
            if(mp.find(s[i]) == mp.end()) {
                // this character is not present in the string
                mp[s[i]] = i;
            } else {
                if(lastIdx <= mp[s[i]]) {
                    lastIdx = mp[s[i]] + 1;
                    
                }
            }

            mp[s[i]] = i;

            len = i - lastIdx + 1;

            res = max(res, len);
        }

        return res;
    }
};