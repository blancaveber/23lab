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
void set_parentness(Node* parent, Node* child, int is_left) {
    if (is_left) {
        parent->left = child;
    } else {
        parent->right = child;
    }
    if (child != NULL) {
        child->parent = parent;
    }
}


Node* rotate_small_right(Node* node) {
    Node* a = node;
    Node* b = a->left;
    set_parentness(a, b->right, 1);
    Node* a_parent = a->parent;
    set_parentness(b, a, 0);
    b->parent = a_parent;
    return b;
}


Node* rotate_big_right(Node* node) {
    Node* a = node;
    Node* b = a->left;
    Node* c = b->right;
    set_parentness(a, c->right, 1);
    set_parentness(b, c->left, 0);
    set_parentness(c, b, 1);
    Node* a_parent = a->parent;
    set_parentness(c, a, 0);
    c->parent = a_parent;
    return c;
}


Node* rotate_big_left(Node* node) {
    Node* a = node;
    Node* b = a->right;
    Node* c = b->left;
    set_parentness(a, c->left, 0);
    set_parentness(b, c->right, 1);
    set_parentness(c, b, 0);
    Node* a_parent = a->parent;
    set_parentness(c, a, 1);
    c->parent = a_parent;
    return c;
}


Node* rotate_small_left(Node* node) {
    Node* a = node;
    Node* b = a->right;
    set_parentness(a, b->left, 0);
    Node* a_parent = a->parent;
    set_parentness(b, a, 1);
    b->parent = a_parent;
    return b;
}