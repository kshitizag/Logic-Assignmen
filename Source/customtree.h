/**
 * @file customtree.h
 * @brief File defining the binary data structure for the parse tree and related functions
 * @version 0.1
 * @date 2022-10-23 
 */

/**
 * @def customtree_h
 * @brief PREPROCESSOR GUARDS
 */
#ifndef customtree_h
#define customtree_h

#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

/**
 * @brief Implementation of one node of the binary parse tree data structure
 * 
 */
struct node {
  char item;  /**< The value stored at the node*/
  struct node* left;  /**< Pointer to the left subtree*/
  struct node* right;  /**< Pointer to the right subtree*/
};

/**
 * @brief Performs inorder traversal of the parse tree and prints it to stdout
 * 
 * @param [in] root Pointer to the root of the parse tree
 */
void inorderTraversal(struct node* root) {
  // do nothing for a null input
  if (root == NULL) return;

  // add brackets iff the node is not a leaf (has children, right or left subtree)
  // a leaf node corresponds to an atom
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

/**
 * @brief Creates a new binary tree node with the given value
 * 
 * @note
 * The memory for the node is dynamically allocated
 * 
 * @param [in] value The @c char to be used as the node's value
 * @returns A pointer to the created node
 */
struct node* createNode(char value) {
  // allocate memory
  struct node* newNode = (struct node*)malloc(sizeof(struct node));

  // initialize all members
  newNode->item = value;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

/**
 * @brief Makes a rooted binary parse tree from the given prefix expression
 * 
 * Some notes about the input and the function:
 *   -# The input must be a well formed propositional logic formula expression in prefix form
 *   -# All whitespace between characters will be ignored
 *   -# The expression is considered to be case sensitive (a and A are different atoms)
 *   .
 * 
 * @note
 * The memory for the tree is dynamically allocated
 * 
 * @param [out] root The pointer to the root of the binary parse tree
 * @param [in] prefixExp The proposition logic formula expression in prefix form ( @c char array)
 * 
 * @returns The length of the expression string used to make the tree (will be the length of the input prefix expression if it is well formed)
 */
int makeTreeFromPrefix(struct node* root, char* prefixExp){
  // if the expression is empty, the node is set to null
  if (strLen(prefixExp) == 0){
    root = NULL;
    return 0;
  }
  // ignore whitespaces, start from next character
  if (prefixExp[0] == ' ' || prefixExp[0] == '\t' || prefixExp[0] == '\n'){
    return makeTreeFromPrefix(root, prefixExp+1);
  }
  root->item = prefixExp[0];
  if (isAtom(prefixExp[0]))
  {
    return 1;
  } else {
    int left = 0;
    if (prefixExp[0] != '~'){
      root->left = createNode('\0');
      left = makeTreeFromPrefix(root->left, prefixExp + 1);
    }
    root->right = createNode('\0');
    int right = makeTreeFromPrefix(root->right, prefixExp + 1 + left);
    return (left + right + 1);
  }
}

/**
 * @brief Returns the height of the binary tree with the given root
 * 
 * @param [in] root Pointer to the root of the binary tree to be used
 * @returns The height of the given binary tree from the given root
 * 
 * @note
 * Height of a binary tree with only one node is considered to be @c 1 and
 * @c 0 is returned for @c NULL input
 */
int height(struct node * root){
  // NULL input means 0 height
  if (root == NULL){
    return 0;
  }

  // find the height of the left subtree
  int leftH = height(root->left);
  // find the height of the right subtree
  int rightH = height(root->right);
  
  // return the greater of the two, plus one for the current node
  if (leftH < rightH){
    return (rightH + 1);
  } else {
    return (leftH + 1);
  }
}

/**
 * @brief Clears a previously created binary tree from the memory
 * 
 * @param [in] root Pointer to the root of the binary tree to be cleared
 * 
 * @warning Any node of the binary tree should not be referenced after calling this function on it
 */
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