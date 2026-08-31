class Solution {
public:
    bool isValidString(int len, int maxFreq, int k) {
        return len-maxFreq <= k;
    }
    int obtainMaxFreq(unordered_map<char, int> &mp) {
        int maxVal = 0;
        for(auto x : mp) {
            maxVal = max(maxVal, x.second);
        }

        return maxVal;
    }
    int characterReplacement(string s, int k) {
        int n = s.length();

        int maxLen = 0;
        int maxFreq = 0;

        unordered_map<char, int> mp;

        int left = 0, right = 0;


        while(right < n) {
            mp[s[right]]++;
            maxFreq = max(maxFreq, mp[s[right]]);

            if(isValidString(right-left+1, maxFreq, k)) {
                maxLen = max(maxLen, right-left+1);
            } else {
                while(!isValidString(right-left+1, maxFreq, k)) {
                    mp[s[left]]--;
                    left++;

                    maxFreq = obtainMaxFreq(mp);
                }
                maxLen = max(maxLen, right-left+1);
            }
            right++;
        }

        return maxLen;
    }
};