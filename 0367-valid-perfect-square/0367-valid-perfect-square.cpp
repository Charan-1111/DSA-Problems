class Solution {
public:
    bool isPerfectSquare(int num) {
        int l = 0, r = num;

        while(l <= r) {
            long long mid = l + ((r-l) >> 1);

            if((mid * mid) == num) {
                return true;
            } else if((mid * mid) < num) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return false;
    }
};