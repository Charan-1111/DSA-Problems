class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> st;
        
    for(char ch : num) {
            while(!st.empty() && k > 0 && st.top() > ch) {
                st.pop();
                k--;
            }
            st.push(ch);
    }

    while(k > 0) {
        st.pop();
        k--;
    }

    string res;

    while(!st.empty()) {
        res.push_back(st.top());
        st.pop();
    }

    while(res != "" && res.back() == '0') {
        res.pop_back();
    }

    reverse(res.begin(), res.end());

        return res == "" ? "0" : res;
    }
};