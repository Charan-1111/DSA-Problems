class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;

        int n = asteroids.size();

        for(int i=0; i<n; i++) {
            if(asteroids[i] < 0) {
                bool isBlast = false;
                while(!st.empty()) {
                    if(st.top() < 0) {
                        // both are moving in same direction
                        st.push(asteroids[i]);
                        isBlast = true;
                        break;
                    } else {
                        if(abs(st.top()) < abs(asteroids[i])) {
                            st.pop();
                        } else if(abs(st.top()) > abs(asteroids[i])) {
                            isBlast = true;
                            break;
                        } else {
                            st.pop();
                            isBlast = true;
                            break;
                        }
                    }
                }

                if(!isBlast) {
                    st.push(asteroids[i]);
                }
            } else {
                st.push(asteroids[i]);
            }
        }

        vector<int> res;
        while(!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }

        reverse(res.begin(), res.end());
        return res;
    }
};