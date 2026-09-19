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
    int solve(TreeNode* root, int parVal) {
        if(!root) return 0;

        if(root->val >= parVal) {
            return 1 + solve(root->left, root->val) + solve(root->right, root->val);
        }

        return solve(root->left, parVal) + solve(root->right, parVal);
    }

    int goodNodes(TreeNode* root) {
        if(!root) return 0;

        int parVal = INT_MIN;

        return solve(root, parVal); 
    }
};