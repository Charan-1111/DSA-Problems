class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> dq; // this queue will store the indices instead of the original values

        for(int i=0; i<nums.size(); i++) {
            int windowStart = i+1-k;

            while(!dq.empty() && dq.front() < windowStart) {
                dq.pop_front();
            }

            while(!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }

            dq.push_back(i);


            if(windowStart >= 0)
            res.push_back(nums[dq.front()]);
        }

        return res;
    }
};