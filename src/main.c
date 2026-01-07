/**
 * @file main.c
 * @brief Demonstration of BST Operations
 */

#include "bst.h"
#include <time.h>

// Callback function for traversals
void print_value(int value) {
    printf("%d ", value);
}

// Example 1: Basic Operations
void example_basic_operations() {
    printf("\n=== Example 1: Basic BST Operations ===\n");
    
    BST* tree = bst_create();
    
    // Insert values
    int values[] = {50, 30, 70, 20, 40, 60, 80, 15, 25, 35, 45};
    int n = sizeof(values) / sizeof(values[0]);
    
    printf("Inserting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        bst_insert(tree, values[i]);
    }
    printf("\n");
    
    printf("Tree size: %d\n", bst_size(tree));
    printf("Tree height: %d\n", bst_height(tree));
    printf("Min value: %d\n", bst_min(tree));
    printf("Max value: %d\n", bst_max(tree));
    
    printf("\nTraversals:\n");
    printf("Inorder   : "); bst_inorder(tree, print_value); printf("\n");
    printf("Preorder  : "); bst_preorder(tree, print_value); printf("\n");
    printf("Postorder : "); bst_postorder(tree, print_value); printf("\n");
    printf("Level Order: "); bst_level_order(tree, print_value); printf("\n");
    
    // Search operations
    printf("\nSearch Operations:\n");
    int search_values[] = {30, 35, 100};
    for (int i = 0; i < 3; i++) {
        bool found = bst_search(tree, search_values[i]);
        printf("Value %d: %s\n", search_values[i], 
               found ? "Found" : "Not Found");
    }
    
    // Delete operations
    printf("\nDelete Operations:\n");
    int delete_values[] = {20, 30, 50};
    for (int i = 0; i < 3; i++) {
        printf("After deleting %d: ", delete_values[i]);
        bst_delete(tree, delete_values[i]);
        bst_inorder(tree, print_value);
        printf(" (Size: %d)\n", bst_size(tree));
    }
    
    bst_destroy(tree);
}

// Example 2: Advanced Operations
void example_advanced_operations() {
    printf("\n=== Example 2: Advanced BST Operations ===\n");
    
    BST* tree = bst_create();
    
    // Insert random values
    srand(time(NULL));
    for (int i = 0; i < 15; i++) {
        bst_insert(tree, rand() % 100);
    }
    
    printf("Tree (inorder): ");
    bst_inorder(tree, print_value);
    printf("\n");
    
    // Kth smallest
    printf("\nKth Smallest Elements:\n");
    for (int k = 1; k <= 5; k++) {
        int value = bst_kth_smallest(tree, k);
        printf("%dth smallest: %d\n", k, value);
    }
    
    // Range query
    printf("\nValues in range [25, 75]: ");
    bst_print_range(tree, 25, 75);
    
    printf("Is valid BST? %s\n", bst_is_valid(tree) ? "Yes" : "No");
    
    bst_destroy(tree);
}

// Example 3: Performance Comparison
void example_performance() {
    printf("\n=== Example 3: Performance Analysis ===\n");
    
    BST* tree = bst_create();
    clock_t start, end;
    
    // Insert performance
    printf("Testing insert performance...\n");
    start = clock();
    for (int i = 0; i < 10000; i++) {
        bst_insert(tree, rand() % 100000);
    }
    end = clock();
    printf("Inserted 10000 elements in %.2f ms\n", 
           (double)(end - start) * 1000 / CLOCKS_PER_SEC);
    
    // Search performance
    printf("\nTesting search performance...\n");
    start = clock();
    for (int i = 0; i < 1000; i++) {
        bst_search(tree, rand() % 100000);
    }
    end = clock();
    printf("1000 searches in %.2f ms\n", 
           (double)(end - start) * 1000 / CLOCKS_PER_SEC);
    
    printf("\nFinal tree size: %d\n", bst_size(tree));
    printf("Final tree height: %d\n", bst_height(tree));
    
    bst_destroy(tree);
}

int main() {
    printf("=== Binary Search Tree Implementation ===\n");
    printf("Author: [Your Name]\n");
    printf("Date: %s\n", __DATE__);
    printf("=========================================\n");
    
    example_basic_operations();
    example_advanced_operations();
    example_performance();
    
    printf("\n=== Program Completed Successfully ===\n");
    return 0;
}
