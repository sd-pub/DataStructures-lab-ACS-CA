/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - length of the tree
 */

#include "binary_tree.h"

void read_tree(b_tree_t *b_tree)
{
    int i, N, data;

    scanf("%d\n", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d ", &data);
        b_tree_insert(b_tree, &data);
    }
}

void dfs_binary_tree(b_node_t *b_node, int length, int *full_length)
{
    if (!b_node)
        return;
    
    length++;

    dfs_binary_tree(b_node->left, length, full_length);
    dfs_binary_tree(b_node->right, length, full_length);

    if (*full_length < length)
        *full_length = length;
}

int main(void)
{
    int length = 0, full_length = 0;

    b_tree_t *b_tree = b_tree_create(sizeof(int));

    read_tree(b_tree);

    dfs_binary_tree(b_tree->root, length, &full_length);

    fprintf(stdout, "There length of the binary tree is of %d levels\n",
            full_length);

    b_tree_free(b_tree, free);

    return 0;
}
