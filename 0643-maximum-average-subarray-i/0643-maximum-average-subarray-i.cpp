class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int sum = 0;
        double maxAvg = -100000000000000;

        for(int i=0; i<k; i++) {
            sum += nums[i];
        }

        double avg = (1.0*sum)/k;

        maxAvg = max(maxAvg, avg);

        for(int i=k; i<nums.size(); i++) {
            sum -= nums[i-k];
            sum += nums[i];

            avg = (1.0 * sum)/k;

            maxAvg = max(maxAvg, avg);
        }
        
        return maxAvg;
    }
};