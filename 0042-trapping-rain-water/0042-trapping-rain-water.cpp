class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();

        vector<int> nge(n);
        vector<int> pge(n);

        stack<int> st;

        for(int i=n-1; i>=0; i--) {
            while(!st.empty() && height[st.top()] <= height[i]){
                st.pop();
            }

            if(st.empty()) {
                nge[i] = -1;
            } else {
                nge[i] = max(height[st.top()], nge[st.top()]);
            }

            st.push(i);
        }

        while(!st.empty())
        st.pop();

        for(int i=0; i<n; i++) {
            while(!st.empty() && height[st.top()] <= height[i]) {
                st.pop();
            }

            if(st.empty()) {
                pge[i] = -1;
            } else {
                pge[i] = max(height[st.top()], pge[st.top()]);
            }

            st.push(i);
        }

        int totalWater = 0;

        for(int i=0; i<n; i++) {
            if(nge[i] != -1 && pge[i] != -1) {
                totalWater += abs(min(nge[i], pge[i]) - height[i]);
            }
        }

        return totalWater;
    }
};