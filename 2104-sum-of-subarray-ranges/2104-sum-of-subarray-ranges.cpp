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

    vector<int> findPge(vector<int> &arr, int n) {
        stack<int> st;
        vector<int> res(n);

        for(int i=0; i<n; i++) {
            while(!st.empty() && arr[st.top()] < arr[i]){
                st.pop();
            }

            if(st.empty()) {
                res[i] = -1;
            } else {
                res[i] = st.top();
            }

            st.push(i);
        }

        return res;
    }


    vector<int> findNge(vector<int> &arr, int n) {
        stack<int> st;
        vector<int> res(n);

        for(int i=n-1; i>=0; i--) {
            while(!st.empty() && arr[st.top()] <= arr[i]) {
                st.pop();
            }

            if(st.empty()) {
                res[i] = n;
            } else {
                res[i] = st.top();
            }

            st.push(i);
        }

        return res;
    }

    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();

        vector<int> nse = findNsi(nums, n);
        vector<int> pse = findPsi(nums, n);
        vector<int> nge = findNge(nums, n);
        vector<int> pge = findPge(nums, n);

        long long res = 0;

        for(int i=0; i<n; i++) {
            long long maxi = (1LL * (nge[i]-i) * (i-pge[i])) * nums[i];
            long long mini = (1LL * (nse[i]-i) * (i-pse[i])) * nums[i];

            res = res + (maxi - mini);
        }

        return res;
    }
};