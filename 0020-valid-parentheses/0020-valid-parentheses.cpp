class Solution {
public:
    bool isValid(string s) {
        unordered_map<char, char> mp;

        mp[')'] = '(';
        mp['}'] = '{';
        mp[']'] = '[';

        stack<char> st;

        for(char ch : s) {
            if(ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            } else {
                if(st.empty() || st.top() != mp[ch]) {
                    return false;
                }  else {
                    st.pop();
                }
            }
        }

        return st.empty();        
    }
};