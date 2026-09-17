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
void solve(TreeNode* root, vector<int> &res) {
    if(!root) return; //Base case if the root is null

    // processing left node
    solve(root->left, res);

    // processing right node
    solve(root->right, res);

    // processing root node
    res.push_back(root->val);
}
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;

        solve(root, res);

        return res;
    }
};