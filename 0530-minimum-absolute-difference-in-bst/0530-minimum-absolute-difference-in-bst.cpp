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
    void inorder(TreeNode* root, vector<int> &v) {
        if(!root) return;

        if(root->left)
        inorder(root->left, v);

        v.push_back(root->val);

        if(root->right)
        inorder(root->right, v);
    }
    int getMinimumDifference(TreeNode* root) {
        vector<int> v;

        inorder(root, v);

        if(v.size() == 0) return 0;
        if(v.size() == 1) return v[0];

        int minVal = INT_MAX;

        for(int i=1; i<v.size(); i++) {
            minVal = min(minVal, abs(v[i]-v[i-1]));
        }

        return minVal;
    }
};