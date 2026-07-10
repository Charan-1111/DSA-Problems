class StockSpanner {
public:
    StockSpanner() {
        
    }

    stack<pair<int, int>> st;

    int i = 0;
    
    int next(int price) {
        while(!st.empty() && st.top().first <= price)
        st.pop();

        int res;

        if(st.empty()) {
            res = i+1;
        } else {
            res = i-st.top().second;
        }

        st.push({price, i});
        i++;

        return res;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */