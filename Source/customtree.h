#ifndef customtree_h
#define customtree_h
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

// Node of the tree
struct node {
  char item;
  struct node* left;
  struct node* right;
};

// Inorder traversal
void inorderTraversal(struct node* root) {
  if (root == NULL) return;
  if (root->left != NULL || root->right != NULL){
    printf("(");
  }
  inorderTraversal(root->left);
  printf("%c", root->item);
  inorderTraversal(root->right);
  if (root->left != NULL || root->right != NULL){
    printf(")");
  }
}

// Create a new Node - root
struct node* createNode(char value) {
  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  newNode->item = value;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

// Tree from prefix expression
int makeTreeFromPrefix(struct node* root, char * exp){
  if (strLen(exp) == 0){
    root = NULL;
    return 0;
  }
  if (exp[0] == ' '){
    return makeTreeFromPrefix(root, exp+1);
  }
  root->item = exp[0];
  if (isAtom(exp[0]))
  {
    return 1;
  } else {
    int left = 0;
    if (exp[0] != '~'){
      root->left = createNode('\0');
      left = makeTreeFromPrefix(root->left, exp + 1);
    }
    root->right = createNode('\0');
    int right = makeTreeFromPrefix(root->right, exp + 1 + left);
    return (left + right + 1);
  }
}

int height(struct node * root){
  if (root == NULL){
    return 0;
  }

  int leftH = height(root->left);
  int rightH = height(root->right);

  if (leftH < rightH){
    return (rightH + 1);
  } else {
    return (leftH + 1);
  }
}

void clearTree(struct node* root){
  if (root->left != NULL){
    clearTree(root->left);
  }
  if (root->right != NULL){
    clearTree(root->right);
  }
  free(root);
}
#endif