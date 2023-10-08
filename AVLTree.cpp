#include <iostream>
#include <algorithm>

class AVLNode {
public:
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLNode* root;

    AVLTree() : root(nullptr) {}

    // Get the height of a node
    int getHeight(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Update the height of a node
    void updateHeight(AVLNode* node) {
        if (node != nullptr) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    // Get the balance factor of a node
    int getBalanceFactor(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Right rotation
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left rotation
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Insert a node into the AVL tree
    AVLNode* insert(AVLNode* node, int value) {
        if (node == nullptr)
            return new AVLNode(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else
            return node; // Duplicate values are not allowed

        updateHeight(node);

        int balance = getBalanceFactor(node);

        // Left Heavy
        if (balance > 1) {
            if (value < node->left->data) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        // Right Heavy
        if (balance < -1) {
            if (value > node->right->data) {
                return leftRotate(node);
            } else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    // Insert a value into the AVL tree
    void insert(int value) {
        root = insert(root, value);
    }

    // In-order traversal of the AVL tree
    void inOrderTraversal(AVLNode* node) {
        if (node == nullptr)
            return;
        inOrderTraversal(node->left);
        std::cout << node->data << " ";
        inOrderTraversal(node->right);
    }

    // Display the AVL tree
    void display() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }
};

int main() {
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    std::cout << "In-order traversal of AVL tree: ";
    avl.display();

    return 0;
}
