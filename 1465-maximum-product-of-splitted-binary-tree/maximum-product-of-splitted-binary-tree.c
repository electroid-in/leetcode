#define MOD 1000000007

long long totalSum;
long long maxProd;

long long getTotalSum(struct TreeNode* root) {
    if (!root) return 0;
    return root->val + getTotalSum(root->left) + getTotalSum(root->right);
}

long long dfs(struct TreeNode* root) {
    if (!root) return 0;

    long long left = dfs(root->left);
    long long right = dfs(root->right);

    long long currSum = left + right + root->val;

    long long product = currSum * (totalSum - currSum);
    if (product > maxProd) {
        maxProd = product;
    }

    return currSum;
}

int maxProduct(struct TreeNode* root) {
    totalSum = 0;
    maxProd = 0;          // 🔴 CRITICAL FIX

    totalSum = getTotalSum(root);
    dfs(root);

    return (int)(maxProd % MOD);
}
