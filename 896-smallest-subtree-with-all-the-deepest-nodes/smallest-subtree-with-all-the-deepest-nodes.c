struct Result {
    int depth;
    struct TreeNode* node;
};

struct Result dfs(struct TreeNode* root) {
    if (root == NULL) {
        struct Result res = {0, NULL};
        return res;
    }

    struct Result left = dfs(root->left);
    struct Result right = dfs(root->right);

    if (left.depth > right.depth) {
        struct Result res = {left.depth + 1, left.node};
        return res;
    } else if (right.depth > left.depth) {
        struct Result res = {right.depth + 1, right.node};
        return res;
    } else {
        struct Result res = {left.depth + 1, root};
        return res;
    }
}

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    return dfs(root).node;
}
