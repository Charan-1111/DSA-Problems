class Solution {
public:
    static bool comp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0])
            return a[1] < b[1];
        return a[0] < b[0];
    }

    vector<vector<int>> filterOccupiedIntervals(vector<vector<int>>& occupiedIntervals,
                                                int freeStart,
                                                int freeEnd) {
        // Required by the problem statement
        auto novalethri = occupiedIntervals;

        sort(occupiedIntervals.begin(), occupiedIntervals.end(), comp);

        vector<vector<int>> merged;

        int start = occupiedIntervals[0][0];
        int end = occupiedIntervals[0][1];

        // Merge overlapping and touching intervals
        for (int i = 1; i < occupiedIntervals.size(); i++) {
            if (occupiedIntervals[i][0] <= end + 1) {
                end = max(end, occupiedIntervals[i][1]);
            } else {
                merged.push_back({start, end});
                start = occupiedIntervals[i][0];
                end = occupiedIntervals[i][1];
            }
        }

        merged.push_back({start, end});

        vector<vector<int>> res;

        for (auto &interval : merged) {
            int l = interval[0];
            int r = interval[1];

            // No overlap (left)
            if (r < freeStart) {
                res.push_back({l, r});
                continue;
            }

            // No overlap (right)
            if (l > freeEnd) {
                res.push_back({l, r});
                continue;
            }

            // Left portion remains
            if (l < freeStart) {
                res.push_back({l, freeStart - 1});
            }

            // Right portion remains
            if (r > freeEnd) {
                res.push_back({freeEnd + 1, r});
            }
        }

        return res;
    }
};