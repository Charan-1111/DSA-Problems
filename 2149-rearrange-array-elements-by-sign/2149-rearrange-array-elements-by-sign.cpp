class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> neg;
        vector<int> pos;

        for(int num : nums) {
            if(num < 0) {
                neg.push_back(num);
            } else {
                pos.push_back(num);
            }
        }

        vector<int> res;

        int j=0, k=0;

        int check = 1;

        for(int i=0; i<nums.size(); i++) {
            if(check == 1) {
                res.push_back(pos[j]);
                j++;
            } else {
                res.push_back(neg[k]);
                k++;
            }

            check = 1-check;
        }

        while(j < pos.size()) {
            res.push_back(pos[j]);
            j++;
        }

        while(k < neg.size()) {
            res.push_back(neg[k]);
            k++;
        }

        return res;
    }
};