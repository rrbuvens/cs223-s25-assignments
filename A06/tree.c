/**
 * Name: Reagan Buvens
 * Date: 02/28/2025
 * Description: Implements a binary search tree.
 */

#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct tree_node* find(const char* name, struct tree_node* root) {
  if (root == NULL || strcmp(root->data.name, name) == 0) {
    return root;
  }
  else if (strcmp(root->data.name, name) > 0) {
    return find(name, root->left);
  }
  return find(name, root->right);
}

struct tree_node* insert(const char* name, struct tree_node* root) {
  if (root == NULL) {
    struct tree_node* newNode = (struct tree_node*) malloc(sizeof(struct tree_node));
    if (!newNode) {
      printf("Memory allocation error. Exiting...");
      exit(1);
    }
    strcpy(newNode->data.name, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  }
  else if (strcmp(root->data.name, name) > 0) {
    root->left = insert(name, root->left);
  }
  else {
    root->right = insert(name, root->right);
  }
  return root;
}

void clear(struct tree_node* root) {
  if (root) {
    clear(root->left);
    clear(root->right);
    free(root);
  }
}

void printI(struct tree_node* root, int level, char* child) {
  if (root) {
    for (int i = 0; i < level; i++) {
      printf("  ");
    }

    printf("%s%s\n", child, root->data.name);

    printI(root->left, level + 1, "l: ");
    printI(root->right, level + 1, "r: ");
  }
}

void print(struct tree_node* root) {
  printI(root, 0, "");
}

void printSorted(struct tree_node* root) {
  if (root) {
    printSorted(root->left);
    printf("%s\n", root->data.name);
    printSorted(root->right);
  }
}

