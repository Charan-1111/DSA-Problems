class Solution {
public:
    static bool comp(vector<int> a, vector<int> b) {
        if(a[0] < b[0]) return true;

        return a[1] < b[1];
    }


    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;

        sort(intervals.begin(), intervals.end());
        
        int n = intervals.size();

        int start = intervals[0][0];
        int end = intervals[0][1];

        for(int i=1; i<n; i++) {
            if(intervals[i][0] <= end) {
                end = max(end, intervals[i][1]);
            } else {
                res.push_back({start, end});
                start = intervals[i][0];
                end = intervals[i][1];
            }
        }

        res.push_back({start, end});

        return res;
    }
};