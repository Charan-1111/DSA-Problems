class Solution {
public:
    vector<int> findNsi(vector<int> &arr, int n) {
        stack<int> st;
        st.push(n-1);

        vector<int> res(n);
        res[n-1] = n;

        for(int i=n-2; i>=0; i--) {
            while(!st.empty() && arr[st.top()] >= arr[i])
            st.pop();

            if(st.empty()) {
                res[i] = n;
            } else {
                res[i] = st.top();
            }

            st.push(i);
        }

        return res;
    }

    vector<int> findPsi(vector<int> &arr, int n) {
        stack<int> st;
        st.push(0);

        vector<int> res(n);
        res[0] = -1;

        for(int i=1; i<n; i++) {
            while(!st.empty() && arr[st.top()] > arr[i])
            st.pop();

            if(st.empty()) {
                res[i] = -1;
            } else {
                res[i] = st.top();
            }

            st.push(i);
        }

        return res;
    }

    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();

        int mod = 1e9+7;

        vector<int> nsi = findNsi(arr, n);
        vector<int> psi = findPsi(arr, n);

        int res = 0;

        for(int i=0; i<n; i++) {
            long long val = (1LL * (nsi[i]-i) * (i-psi[i])) % mod;

            val = (arr[i] * val) % mod;

            res = (res + val) % mod;
        }

        return res;
    }
};