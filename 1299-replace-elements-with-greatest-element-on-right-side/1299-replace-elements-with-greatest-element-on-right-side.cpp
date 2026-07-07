class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n = arr.size();

        vector<int> res(n);

        stack<int> st;

        for(int i=n-1; i>=0; i--) {
            int val = -1;

            while(!st.empty() && st.top() <= arr[i]) {
                val = st.top();
                st.pop();
            }

            if(st.empty()) {
                res[i] = val;
                st.push(arr[i]);
            } else {
                res[i] = st.top();
                if(st.top() <= arr[i]) {
                    st.push(arr[i]);
                }
            }
        }

        return res;
    }
};