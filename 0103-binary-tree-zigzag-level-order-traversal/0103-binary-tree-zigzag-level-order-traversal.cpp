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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(!root) return {};

        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});

        map<int, vector<int>>mp;

        while(!q.empty()) {
            pair<TreeNode*, int> p = q.front();
            q.pop();

            TreeNode* par = p.first;
            int level = p.second;

            mp[level].push_back(par->val);

            if(par->left)
            q.push({par->left, level+1});

            if(par->right)
            q.push({par->right, level+1});
        }

        vector<vector<int>> res;

        for(auto x : mp) {
            if(x.first & 1) {
                reverse(x.second.begin(), x.second.end());
            }

            res.push_back(x.second);
        }

        return res;
    }
};