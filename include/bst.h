/**
 * @file bst.h
 * @brief Binary Search Tree Implementation with Complete Operations
 * @author [Your Name]
 * @date 2024
 * @license MIT
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @struct BSTNode
 * @brief Structure representing a node in Binary Search Tree
 */
typedef struct BSTNode {
    int data;                   ///< Data stored in node
    struct BSTNode* left;       ///< Pointer to left child
    struct BSTNode* right;      ///< Pointer to right child
} BSTNode;

/**
 * @struct BST
 * @brief Structure representing Binary Search Tree
 */
typedef struct {
    BSTNode* root;              ///< Root of the BST
    int size;                   ///< Number of nodes in BST
} BST;

// ==================== TREE CREATION & DESTRUCTION ====================

BST* bst_create();
void bst_destroy(BST* tree);
void bst_clear(BST* tree);

// ==================== INSERTION OPERATIONS ====================

bool bst_insert(BST* tree, int value);
bool bst_insert_recursive(BST* tree, int value);
BSTNode* bst_insert_node(BSTNode* root, int value, int* success);

// ==================== DELETION OPERATIONS ====================

bool bst_delete(BST* tree, int value);
BSTNode* bst_delete_node(BSTNode* root, int value, bool* success);
bool bst_remove_min(BST* tree, int* min_value);
bool bst_remove_max(BST* tree, int* max_value);

// ==================== SEARCH OPERATIONS ====================

bool bst_search(const BST* tree, int value);
BSTNode* bst_find_node(const BSTNode* root, int value);
bool bst_contains(const BST* tree, int value);

// ==================== TRAVERSAL OPERATIONS ====================

void bst_inorder(const BST* tree, void (*callback)(int));
void bst_preorder(const BST* tree, void (*callback)(int));
void bst_postorder(const BST* tree, void (*callback)(int));
void bst_level_order(const BST* tree, void (*callback)(int));

// ==================== UTILITY OPERATIONS ====================

int bst_min(const BST* tree);
int bst_max(const BST* tree);
int bst_height(const BST* tree);
int bst_size(const BST* tree);
bool bst_is_empty(const BST* tree);
bool bst_is_valid(const BST* tree);

// ==================== ADVANCED OPERATIONS ====================

int bst_kth_smallest(const BST* tree, int k);
int bst_kth_largest(const BST* tree, int k);
void bst_print_range(const BST* tree, int low, int high);
bool bst_is_balanced(const BST* tree);
BST* bst_clone(const BST* tree);
bool bst_equals(const BST* tree1, const BST* tree2);

// ==================== SERIALIZATION ====================

void bst_serialize(const BST* tree, FILE* stream);
BST* bst_deserialize(FILE* stream);

// ==================== VISUALIZATION ====================

void bst_print_pretty(const BST* tree);
void bst_print_horizontal(const BSTNode* root, int space);
void bst_export_dot(const BST* tree, const char* filename);

#endif // BINARY_SEARCH_TREE_H
