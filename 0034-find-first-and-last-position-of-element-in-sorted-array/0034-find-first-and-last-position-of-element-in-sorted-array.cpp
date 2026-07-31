class Solution {
public:
    int findLowerBound(vector<int> &nums, int target) {
        int res = -1;

        int l = 0, r = nums.size()-1;

        while(l <= r) {
            int mid = l + ((r-l) >> 1);

            if(nums[mid] == target) {
                res = mid;
                r = mid - 1;
            } else if(nums[mid] < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return res;
    }

    int findUpperBound(vector<int> &nums, int target) {
        int res = -1;
        int l = 0, r = nums.size()-1;

        while(l <= r) {
            int mid = l + ((r-l) >> 1);

            if(nums[mid] == target) {
                res = mid;
                l = mid + 1;
            } else if(nums[mid] < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return res;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int first = findLowerBound(nums, target);
        int second = findUpperBound(nums, target);

        return {first, second};
    }
};