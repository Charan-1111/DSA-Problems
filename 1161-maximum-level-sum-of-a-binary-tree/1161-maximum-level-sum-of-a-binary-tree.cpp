/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        if(!root) return 0;

        queue<pair<TreeNode*, int>> q;
        q.push({root, 1});

        map<int, int> mp;

        while(!q.empty()) {
            pair<TreeNode*, int> p = q.front();
            q.pop();

            TreeNode* par = p.first;
            int level = p.second;

            mp[level] += par->val;

            if(par->left)
            q.push({par->left, level+1});

            if(par->right)
            q.push({par->right, level+1});
        }

        int max_val = INT_MIN;
        int max_level = -1;

        for(auto x : mp) {
            if(x.second > max_val) {
                max_val = x.second;
                max_level = x.first;
            }
        }

         return max_level;
    }
};