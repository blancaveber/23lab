#include "stdio.h"
#include "stdlib.h"

typedef struct Node_ {
    int value;
    struct Node_* left;
    struct Node_* right;
    struct Node_* parent;
} Node;

typedef struct Tree_ {
    Node* root;
} Tree;


Node* create_new_node(int value) {
    Node* new_node;
    new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    return new_node;
}

Tree* create_tree() {
    Tree* tree;
    tree = malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

int has_right_child(Node* node) {
    return node->right != NULL;
}

int has_left_child(Node* node) {
    return node->left != NULL;
}

int get_node_height(Node* node) {
    int height_left = 0, height_right = 0;
    if (has_left_child(node)) {
        height_left = get_node_height(node->left);
    }
    if (has_right_child(node)) {
        height_right = get_node_height(node->right);
    }
    return height_right > height_left ? ++height_right : ++height_left;
}

int get_balance_factor(Node* node) {
    int bf = 0;
    if (has_left_child(node)) {
        bf += get_node_height(node->left);
    }
    if (has_right_child(node)) {
        bf -= get_node_height(node->right);
    }
    return bf;
}