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
    if(!root) return; // base case when the root not is empty

    // processing the root node
    res.push_back(root->val);

    // processing left node
    solve(root->left, res);

    // processing right node
    solve(root->right, res);
}
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;

        solve(root, res);

        return res;
    }
};