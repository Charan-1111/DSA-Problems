class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums2.size();

        vector<int> res(n);

        unordered_map<int, int> mp;

        stack<int> st;

        for(int i=n-1; i>=0; i--) {
            while(!st.empty() && st.top() <= nums2[i]) {
                st.pop();
            }

            if(st.empty()) {
                res[i] = -1;
            } else {
                res[i] = st.top();
            }

            mp[nums2[i]] = res[i];

            st.push(nums2[i]);
        }

        vector<int> v;

        for(int num : nums1) {
            v.push_back(mp[num]);
        }

        return v;
    }
};