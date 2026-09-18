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
    bool isLeaf(TreeNode* root){
        return !root->left && !root->right;
    }
    void preorder(TreeNode* root, int num, int &sum){
        if(isLeaf(root)){
            sum = sum + num*10 + root->val;
            return;
        }
        
        if(root->left)
            preorder(root->left, num*10+root->val, sum);
        
        if(root->right)
            preorder(root->right, num*10+root->val, sum);
    }
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        
        int sum =0;
        int num = 0;
        
        preorder(root, num, sum);
        
        
        return sum;
    }
};