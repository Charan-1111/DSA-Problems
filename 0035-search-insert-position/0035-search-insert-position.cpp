class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size()-1;

        int res = -1;

        while(l <= r) {
            int mid = l + ((r-l) >> 1);

            if(nums[mid] <= target) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if(res == -1) return 0;

        return nums[res] == target ? res : res + 1;
    }
};