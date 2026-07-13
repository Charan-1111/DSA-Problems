class Solution {
public:
    int hammingWeight(int n) {
        int tot = 0;

        while(n) {
            tot += (n&1);
            n = n >> 1;
        }

        return tot;
     }
};