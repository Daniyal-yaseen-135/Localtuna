#ifndef BST_H
#define BST_H

#include "node.h"
#include <vector>

struct BSTNode {
    Node* songNode;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Node* n) : songNode(n), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BSTNode* root;

    BST();
    void insert(Node* node);
    void inorder(BSTNode* root, std::vector<Node*>& list);
};

#endif
