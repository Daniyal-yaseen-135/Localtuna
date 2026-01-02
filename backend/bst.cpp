#include "bst.h"

BST::BST() { root = nullptr; }

void BST::insert(Node* node) {
    BSTNode** curr = &root;
    while (*curr) {
        if (node->song.title < (*curr)->songNode->song.title)
            curr = &((*curr)->left);
        else
            curr = &((*curr)->right);
    }
    *curr = new BSTNode(node);
}

void BST::inorder(BSTNode* r, std::vector<Node*>& list) {
    if (!r) return;
    inorder(r->left, list);
    list.push_back(r->songNode);
    inorder(r->right, list);
}
