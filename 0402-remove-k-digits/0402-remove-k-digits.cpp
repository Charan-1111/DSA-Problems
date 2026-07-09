class Solution {
public:
    string removeKdigits(string num, int k) {
        string st = "";

        int n = num.size();

        for(int i=0; i<n; i++) {
            while(st != "" && st.back() > num[i] && k > 0) {
                st.pop_back();
                k--;
            }

            st.push_back(num[i]);
        }

        while(k--) {
            st.pop_back();
        }

        int i=0;

        while(st[i] == '0') {
            i++;
        }

        st = st.substr(i, st.length()-i);

        return st.length() == 0 ? "0" : st;
    }
};