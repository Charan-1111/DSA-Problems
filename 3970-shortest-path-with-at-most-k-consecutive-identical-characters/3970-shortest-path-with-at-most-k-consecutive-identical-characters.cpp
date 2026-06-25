class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        const long long INF = 1e18;

        // dist[node][cnt]
        vector<vector<long long>> dist(n, vector<long long>(k + 1, INF));

        using State = tuple<long long, int, int>;
        // {cost, node, consecutive_count}

        priority_queue<State, vector<State>, greater<State>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [cost, node, cnt] = pq.top();
            pq.pop();

            if (cost != dist[node][cnt]) {
                continue;
            }

            for (auto &[next, wt] : adj[node]) {
                int newCnt;

                if (labels[next] == labels[node]) {
                    newCnt = cnt + 1;
                } else {
                    newCnt = 1;
                }

                if (newCnt > k) {
                    continue;
                }

                long long newCost = cost + wt;

                if (newCost < dist[next][newCnt]) {
                    dist[next][newCnt] = newCost;
                    pq.push({newCost, next, newCnt});
                }
            }
        }

        long long ans = INF;

        for (int cnt = 1; cnt <= k; cnt++) {
            ans = min(ans, dist[n - 1][cnt]);
        }

        return ans == INF ? -1 : (int)ans;
    }
};