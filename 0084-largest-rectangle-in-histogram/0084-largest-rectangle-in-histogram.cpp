class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();

        vector<int> nse(n);
        vector<int> pse(n);

        stack<int> st;

        for(int i=n-1; i>=0; i--) {
            while(!st.empty() && heights[st.top()] >= heights[i]) {
                st.pop();
            }

            if(st.empty()) {
                nse[i] = n;
            } else {
                nse[i] = st.top();
            }

            st.push(i);
        }

        while(!st.empty())
        st.pop();

        for(int i=0; i<n; i++) {
            while(!st.empty() && heights[st.top()] >= heights[i]) {
                st.pop();
            }

            if(st.empty()) {
                pse[i] = -1;
            } else {
                pse[i] = st.top();
            }

            st.push(i);
        }

        int maxVal = INT_MIN;

        for(int i=0; i<n; i++) {
            int val = (nse[i] - pse[i] - 1) * heights[i];

            maxVal = max(maxVal, val);
        }

        return maxVal;
    }
};