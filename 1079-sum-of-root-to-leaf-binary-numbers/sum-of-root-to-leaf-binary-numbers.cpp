class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        return dfs(root, 0);
    }
    
private:
    int dfs(TreeNode* node, int current) {
        if (!node) return 0;
        
        // Update current binary number
        current = (current << 1) | node->val;
        
        // If leaf node, return the number
        if (!node->left && !node->right) {
            return current;
        }
        
        // Recur left and right
        return dfs(node->left, current) + 
               dfs(node->right, current);
    }
};