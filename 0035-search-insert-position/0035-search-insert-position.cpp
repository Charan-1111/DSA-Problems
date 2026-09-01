class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;

        int res = 0;

        while(l <= r ) {
            int mid = l + ((r-l) >> 1);

            if(nums[mid] == target) {
                return mid;
            } else if(nums[mid] < target) {
                res = mid+1;
                l = mid + 1;
            } else {
                res = mid;
                r = mid-1;
            }
        }

        return res;
    }
};