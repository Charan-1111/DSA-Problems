class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> dq; // stores the indexes instead of the numbers

        for(int i=0; i<nums.size(); i++) {
            int windowStart = i-k+1;

            // poping all the indexes that are out of the current window from the front of the deque
            while(!dq.empty() && dq.front() < windowStart) {
                dq.pop_front();
            }

            while(!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }

            dq.push_back(i);

            if(windowStart >= 0) {
                res.push_back(nums[dq.front()]);
            }
        }

        return res;
    }
};