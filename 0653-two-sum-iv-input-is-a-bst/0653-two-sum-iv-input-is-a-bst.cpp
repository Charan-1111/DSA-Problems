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
    
    vector<int> v;
    
    void inorder(TreeNode* root){
        if(root->left)
            inorder(root->left);
        
        v.push_back(root->val);
        
        if(root->right)
            inorder(root->right);
        
    }
    
    bool findTarget(TreeNode* root, int k) {
        if(root == NULL)
            return 0;
        
        
        inorder(root);
        
        
        int i=0, j=v.size()-1;
        
        bool res = false;
        
        while(i<j){
            int sum = v[i]+v[j];
            
            if(sum == k){
                res = true;
                break;
            }
            
            else if(sum > k)
                j--;
            
            else
                i++;
            
        }
        
        
        return res;
        
    }
};