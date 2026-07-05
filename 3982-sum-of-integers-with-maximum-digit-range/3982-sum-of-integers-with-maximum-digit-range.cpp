class Solution {
public:
    int maxDigitRange(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;

        int maxDiff = INT_MIN;

        for(int num : nums) {
            int large = INT_MIN;
            int small = INT_MAX;

            int temp = num;

            while(temp) {
                int rem = temp % 10;
                temp /= 10;

                large = max(large, rem);
                small = min(small, rem);
            }

            int diff = large-small;

            maxDiff = max(maxDiff, diff);

            mp[diff].push_back(num);
        }

        int sum = 0;

        for(int num : mp[maxDiff]) {
            sum = sum + num;
        }

        return sum;
    }
};