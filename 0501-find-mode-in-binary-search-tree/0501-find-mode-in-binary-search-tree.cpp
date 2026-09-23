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
    void inorder(TreeNode* root, unordered_map<int, int> &mp, int &max_val) {
        if(!root) return;

        inorder(root->left, mp, max_val);

        mp[root->val]++;

        max_val = max(max_val, mp[root->val]);

        inorder(root->right, mp, max_val);
    }
    vector<int> findMode(TreeNode* root) {
        unordered_map<int, int> mp;
        int max_val = INT_MIN;

        inorder(root, mp, max_val);

        vector<int> res;
        for(auto x : mp) {
            if(x.second == max_val)
            res.push_back(x.first);
        }

        return res;
    }
};