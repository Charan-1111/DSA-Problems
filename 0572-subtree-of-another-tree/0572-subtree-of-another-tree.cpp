class Solution {
public:
    bool isSimilar(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2) return true;

        if (!root1 || !root2) return false;

        return root1->val == root2->val
            && isSimilar(root1->left, root2->left)
            && isSimilar(root1->right, root2->right);
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!subRoot) return true;
        if (!root) return false;

        // Check the current node, and if it doesn't match,
        // continue searching below it.
        return isSimilar(root, subRoot)
            || isSubtree(root->left, subRoot)
            || isSubtree(root->right, subRoot);
    }
};