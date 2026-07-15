class Solution {
public:
    int secondHighest(string s) {
        int large = INT_MIN;
        int secondLarge = INT_MIN;


        for(char ch : s) {
            if(ch >= '0' and ch <= '9') {
                if(ch-'0' > large) {
                    secondLarge = max(large, secondLarge);

                    large = ch-'0';
                } else {
                    if(ch-'0' < large) {
                        secondLarge = max(secondLarge, ch-'0');
                    }
                }
            }
        }  

        return secondLarge == INT_MIN ? -1 : secondLarge;
    }
};