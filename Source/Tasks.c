/**
 * @file Tasks.c
 * @brief Contains wrapper functions for individual Tasks and code to test them
 * @version 0.1
 * @date 2022-10-23
 */

#include <stdio.h>
#include <stdlib.h>
#include "infixtoprefix.h"
#include "customtree.h"
#include "logicformulas.h"

/**
 * @brief Task 1 solution
 * 
 * @param [in] infixExp Infix propositional logic expression
 * @returns Prefix propositional logic
expression form of the input
 */
char* Task1(char* infixExp){
  return getPrefix(infixExp);
}

/**
 * @brief Task 2 solution
 * 
 * @param [in] prefixExp Prefix propositional logic expression
 * @returns Pointer to the root of the  rooted binary parse tree of the input
 */
struct node* Task2(char* prefixExp){
  struct node* root = createNode('\0');
  makeTreeFromPrefix(root, prefixExp);
  return root;
}

/**
 * @brief Task 3 solution
 * 
 * In-order traversal of the binary tree to get the infix expression
 * 
 * @param [in] root Infix propositional logic expression form of the input
 */
void Task3(struct node* root){
  inorderTraversal(root);
}

/**
 * @brief Computes the height of the parse tree with the given root
 * 
 * @param [in] root Pointer to the root of the parse tree
 * @returns @c int height of the parse tree
 */
int Task4(struct node* root){
  return height(root);
}

/**
 * @brief Evaluates the truth value of a propositional logic formula in parse tree form
 * 
 * @param [in] root Pointer to the root of the parse tree
 * @param [in] atoms Array of propostional logic atoms and their truth values
 * @retval T for boolean True
 * @retval F for boolean False
 */
char Task5(struct node* root, struct atom atoms[]){
  return evaluate(root, atoms);
}

/**
 * @brief main function to test the task functions
 * 
 * @returns 0 for successful execution
 */
int main(){
  // Given Input
  char* infixExpression = " a + b > ~ ( b + c ) ";
  struct atom truthValues[] = {{'a', T}, {'b', T}, {'c', F}};

  // Processing and Output
  int numberOfAtoms = sizeof(truthValues)/sizeof(truthValues[0]);
  printf("The input infix expression: \"%s\"\n", infixExpression);
  char* prefixExpression = Task1(infixExpression);
  printf("The expression in prefix form: \"%s\"\n", prefixExpression);
  struct node* root = Task2(prefixExpression);
  printf("The prefix expression is converted into a rooted binary parse tree and stored at address \"%p\"\n", root);
  printf("The infix expression back by in-order traversal of the parse tree: \""); Task3(root);
  printf("\"\n");
  int heightOfTree = Task4(root);
  printf("The height of a parse tree: \"%d\"\n", heightOfTree);
  printf("The input truth values of propositional atoms (T is True and F is False):\n");
  printf("::atom -> value::\n");
  for (int i = 0; i < numberOfAtoms; i++){
    printf("   %c   ->   %c\n", (truthValues[i]).name, (truthValues[i]).value);
  }
  printf("The truth value of a propositional logic formula by traversing the tree in a bottom up fashion: \"%c\"", Task5(root, truthValues));
  free(prefixExpression);
  clearTree(root);
  return 0;
}
