class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        // the array is sorted

        int left = 0, right = numbers.size()-1;

        while(left <= right) {
            int sum = numbers[left] + numbers[right];

            if(sum == target) {
                return {left+1, right+1};
            } else if(sum > target) {
                // right is pointing to much higher value
                right--;
            } else {
                // left is pointing to much smaller value
                left++;
            }
        }

        return {};
    }
};