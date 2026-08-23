class Solution {
public:
    bool isPalindromic(string s) {
       string str = "";

        for(char ch : s) {
            bitset<8> binary(ch);
            string binaryStr = binary.to_string();

            str = str + binaryStr;
        }

        cout << str << endl;


        int i = 0;
        int j = str.length()-1;

        while(i <= j) {
            if(str[i] != str[j])
                return false;

            i++;
            j--;
        }

        return true;
    }
};