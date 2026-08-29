class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();

        int left = 0, right = 0;

        unordered_map<int, int> mp;

        int fruitCnt = 0, maxFruitCnt = 0;

        while(right < n) {
            if(mp.find(fruits[right]) == mp.end() && mp.size() == 2) {
                // means this is the new fruit we need to handle according
                // start removing fruits from the left
                while(left < right && mp.size() == 2) {
                    mp[fruits[left]]--;
                    fruitCnt--;
                    if(mp[fruits[left]] == 0) {
                        mp.erase(fruits[left]);
                    }
                    left++;
                }
            }

            fruitCnt++;
            maxFruitCnt = max(maxFruitCnt, fruitCnt);
            mp[fruits[right]]++;
            right++;
        }

        return maxFruitCnt;
    }
};