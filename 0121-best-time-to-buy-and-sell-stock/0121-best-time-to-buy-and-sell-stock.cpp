class Solution {
public:
    int maxProfit(vector<int>& prices) {
        stack<int> st;

        int maxProfit = INT_MIN;

        int n = prices.size();

        for(int i=n-1; i>=0; i--) {
            while(!st.empty() && st.top() < prices[i])
            st.pop();

            if(!st.empty()) {
                maxProfit = max(maxProfit, abs(st.top()-prices[i]));
            }

            if(st.empty() || prices[i] >= st.top())
            st.push(prices[i]);
        }

        return maxProfit == INT_MIN ? 0 : maxProfit;
    }
};