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
    bool isLeaf(TreeNode* root) {
        return !root->left && !root->right;
    }

    int minDepth(TreeNode* root) {
        if(!root) return 0;

        queue<pair<TreeNode*, int>> q;
        q.push({root, 1});

        unordered_map<int, int> mp;

        while(!q.empty()) {
            pair<TreeNode*, int> p = q.front();
            q.pop();

            TreeNode* par = p.first;
            int level = p.second;

            if(isLeaf(par)) {
                return level;
            }

            mp[level] = par->val;

            if(par->left)
            q.push({par->left, level+1});

            if(par->right)
            q.push({par->right, level+1});
        }

        return mp.size();
    }
};