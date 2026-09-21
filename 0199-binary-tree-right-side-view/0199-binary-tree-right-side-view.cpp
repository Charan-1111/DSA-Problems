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
    vector<int> rightSideView(TreeNode* root) {
        if(!root) return {};

        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});

        map<int, int> mp;

        while(!q.empty()) {
            pair<TreeNode*, int> p = q.front();
            q.pop();

            TreeNode* par = p.first;
            int par_level = p.second;

            mp[par_level] = par->val;

            if(par->left)
            q.push({par->left, par_level+1});

            if(par->right)
            q.push({par->right, par_level+1});
        }

        vector<int> res;
        for(auto x : mp) {
            res.push_back(x.second);
        }

        return res;
    }
};