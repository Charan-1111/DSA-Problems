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

    bool solve(TreeNode* root, int sum, int targetSum) {
        if(!root) return false;
        
        if(isLeaf(root)) {
            if(sum + root->val == targetSum) return true; 
        }

        return solve(root->left, sum + root->val, targetSum) || solve(root->right, sum + root->val, targetSum);
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        return solve(root, 0, targetSum);    
    }
};