/**
 * @file bst.c
 * @brief Binary Search Tree Implementation
 */

#include "bst.h"
#include <assert.h>
#include <string.h>

// ==================== INTERNAL HELPER FUNCTIONS ====================

static BSTNode* create_node(int value) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if (!node) return NULL;
    
    node->data = value;
    node->left = node->right = NULL;
    return node;
}

static void destroy_subtree(BSTNode* root) {
    if (!root) return;
    destroy_subtree(root->left);
    destroy_subtree(root->right);
    free(root);
}

static int max_int(int a, int b) {
    return (a > b) ? a : b;
}

// ==================== TREE CREATION & DESTRUCTION ====================

BST* bst_create() {
    BST* tree = (BST*)malloc(sizeof(BST));
    if (!tree) return NULL;
    
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void bst_destroy(BST* tree) {
    if (!tree) return;
    bst_clear(tree);
    free(tree);
}

void bst_clear(BST* tree) {
    if (!tree) return;
    destroy_subtree(tree->root);
    tree->root = NULL;
    tree->size = 0;
}

// ==================== INSERTION OPERATIONS ====================

bool bst_insert(BST* tree, int value) {
    if (!tree) return false;
    
    BSTNode* current = tree->root;
    BSTNode* parent = NULL;
    
    // Find insertion point
    while (current) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            return false; // Duplicate value
        }
    }
    
    // Create new node
    BSTNode* newNode = create_node(value);
    if (!newNode) return false;
    
    // Insert node
    if (!parent) {
        tree->root = newNode; // Empty tree
    } else if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    
    tree->size++;
    return true;
}

bool bst_insert_recursive(BST* tree, int value) {
    if (!tree) return false;
    
    bool success = false;
    tree->root = bst_insert_node(tree->root, value, &success);
    
    if (success) tree->size++;
    return success;
}

BSTNode* bst_insert_node(BSTNode* root, int value, int* success) {
    if (!root) {
        BSTNode* node = create_node(value);
        if (node && success) *success = true;
        return node;
    }
    
    if (value < root->data) {
        root->left = bst_insert_node(root->left, value, success);
    } else if (value > root->data) {
        root->right = bst_insert_node(root->right, value, success);
    } else {
        if (success) *success = false; // Duplicate
    }
    
    return root;
}

// ==================== DELETION OPERATIONS ====================

bool bst_delete(BST* tree, int value) {
    if (!tree || !tree->root) return false;
    
    bool success = false;
    tree->root = bst_delete_node(tree->root, value, &success);
    
    if (success) tree->size--;
    return success;
}

BSTNode* bst_delete_node(BSTNode* root, int value, bool* success) {
    if (!root) {
        if (success) *success = false;
        return NULL;
    }
    
    if (value < root->data) {
        root->left = bst_delete_node(root->left, value, success);
    } else if (value > root->data) {
        root->right = bst_delete_node(root->right, value, success);
    } else {
        // Node found
        if (success) *success = true;
        
        // Case 1: No child or one child
        if (!root->left) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 2: Two children
        // Find inorder successor (minimum in right subtree)
        BSTNode* successor = root->right;
        while (successor && successor->left) {
            successor = successor->left;
        }
        
        // Copy successor data
        root->data = successor->data;
        
        // Delete the successor
        root->right = bst_delete_node(root->right, successor->data, NULL);
    }
    
    return root;
}

// ==================== SEARCH OPERATIONS ====================

bool bst_search(const BST* tree, int value) {
    if (!tree) return false;
    return bst_find_node(tree->root, value) != NULL;
}

BSTNode* bst_find_node(const BSTNode* root, int value) {
    while (root) {
        if (value == root->data) {
            return (BSTNode*)root;
        } else if (value < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return NULL;
}

bool bst_contains(const BST* tree, int value) {
    return bst_search(tree, value);
}

// ==================== TRAVERSAL OPERATIONS ====================

static void inorder_recursive(BSTNode* root, void (*callback)(int)) {
    if (!root) return;
    inorder_recursive(root->left, callback);
    if (callback) callback(root->data);
    inorder_recursive(root->right, callback);
}

void bst_inorder(const BST* tree, void (*callback)(int)) {
    if (!tree || !callback) return;
    inorder_recursive(tree->root, callback);
}

static void preorder_recursive(BSTNode* root, void (*callback)(int)) {
    if (!root) return;
    if (callback) callback(root->data);
    preorder_recursive(root->left, callback);
    preorder_recursive(root->right, callback);
}

void bst_preorder(const BST* tree, void (*callback)(int)) {
    if (!tree || !callback) return;
    preorder_recursive(tree->root, callback);
}

static void postorder_recursive(BSTNode* root, void (*callback)(int)) {
    if (!root) return;
    postorder_recursive(root->left, callback);
    postorder_recursive(root->right, callback);
    if (callback) callback(root->data);
}

void bst_postorder(const BST* tree, void (*callback)(int)) {
    if (!tree || !callback) return;
    postorder_recursive(tree->root, callback);
}

// Level order traversal using queue
typedef struct QueueNode {
    BSTNode* tree_node;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

static Queue* queue_create() {
    return (Queue*)calloc(1, sizeof(Queue));
}

static void queue_enqueue(Queue* q, BSTNode* tree_node) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->tree_node = tree_node;
    newNode->next = NULL;
    
    if (q->rear) {
        q->rear->next = newNode;
    } else {
        q->front = newNode;
    }
    q->rear = newNode;
}

static BSTNode* queue_dequeue(Queue* q) {
    if (!q->front) return NULL;
    
    QueueNode* temp = q->front;
    BSTNode* tree_node = temp->tree_node;
    
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    
    free(temp);
    return tree_node;
}

static void queue_destroy(Queue* q) {
    while (q->front) {
        QueueNode* temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    free(q);
}

void bst_level_order(const BST* tree, void (*callback)(int)) {
    if (!tree || !tree->root || !callback) return;
    
    Queue* q = queue_create();
    if (!q) return;
    
    queue_enqueue(q, tree->root);
    
    while (q->front) {
        BSTNode* current = queue_dequeue(q);
        callback(current->data);
        
        if (current->left) queue_enqueue(q, current->left);
        if (current->right) queue_enqueue(q, current->right);
    }
    
    queue_destroy(q);
}

// ==================== UTILITY OPERATIONS ====================

int bst_min(const BST* tree) {
    if (!tree || !tree->root) {
        fprintf(stderr, "Tree is empty\n");
        return INT_MIN;
    }
    
    BSTNode* current = tree->root;
    while (current->left) {
        current = current->left;
    }
    return current->data;
}

int bst_max(const BST* tree) {
    if (!tree || !tree->root) {
        fprintf(stderr, "Tree is empty\n");
        return INT_MAX;
    }
    
    BSTNode* current = tree->root;
    while (current->right) {
        current = current->right;
    }
    return current->data;
}

static int height_recursive(BSTNode* root) {
    if (!root) return -1;
    return 1 + max_int(height_recursive(root->left), 
                      height_recursive(root->right));
}

int bst_height(const BST* tree) {
    if (!tree) return -1;
    return height_recursive(tree->root);
}

int bst_size(const BST* tree) {
    return tree ? tree->size : 0;
}

bool bst_is_empty(const BST* tree) {
    return !tree || !tree->root;
}

static bool is_valid_recursive(BSTNode* root, int min, int max) {
    if (!root) return true;
    
    if (root->data <= min || root->data >= max) {
        return false;
    }
    
    return is_valid_recursive(root->left, min, root->data) &&
           is_valid_recursive(root->right, root->data, max);
}

bool bst_is_valid(const BST* tree) {
    if (!tree) return true;
    return is_valid_recursive(tree->root, INT_MIN, INT_MAX);
}

// ==================== ADVANCED OPERATIONS ====================

static int kth_smallest_helper(BSTNode* root, int* count, int k) {
    if (!root) return -1;
    
    // Search in left subtree
    int left = kth_smallest_helper(root->left, count, k);
    if (left != -1) return left;
    
    // Current node
    (*count)++;
    if (*count == k) return root->data;
    
    // Search in right subtree
    return kth_smallest_helper(root->right, count, k);
}

int bst_kth_smallest(const BST* tree, int k) {
    if (!tree || k <= 0 || k > tree->size) {
        fprintf(stderr, "Invalid k value\n");
        return -1;
    }
    
    int count = 0;
    return kth_smallest_helper(tree->root, &count, k);
}

static void range_print_helper(BSTNode* root, int low, int high, 
                              void (*callback)(int)) {
    if (!root || !callback) return;
    
    if (root->data > low) {
        range_print_helper(root->left, low, high, callback);
    }
    
    if (root->data >= low && root->data <= high) {
        callback(root->data);
    }
    
    if (root->data < high) {
        range_print_helper(root->right, low, high, callback);
    }
}

void bst_print_range(const BST* tree, int low, int high) {
    if (!tree) return;
    range_print_helper(tree->root, low, high, 
                      ^(int value) { printf("%d ", value); });
    printf("\n");
}
