class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int l = 0, r = letters.size()-1;

        int res = -1;

        while(l <= r) {
            int mid = l + ((r-l) >> 1);

            if(letters[mid] > target) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        return res == -1 ? letters[0] : letters[res];
    } 
};
