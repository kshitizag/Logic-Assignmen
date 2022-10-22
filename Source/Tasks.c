#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "infixtoprefix.h"
#include "customtree.h"
#include "logicformulas.h"

char* Task1(char* inorderExp){
  return getPrefix(inorderExp);
}

struct node* Task2(char* prefixExp){
  struct node* root = createNode('\0');
  makeTreeFromPrefix(root, prefixExp);
  return root;
}

void Task3(struct node* root){
  inorderTraversal(root);
}

int Task4(struct node* root){
  return height(root);
}

char Task5(struct node* root, struct atom atoms[]){
  return evaluate(root, atoms);
}

int main(){
  // Given Input
  char* infixExpression = "a+b>~c";
  struct atom truthValues[] = {{'a', T}, {'b', T}, {'c', F}};

  // Processing and Output
  int length = sizeof(truthValues)/sizeof(truthValues[0]);
  printf("The input infix expression: \"%s\"\n", infixExpression);
  char* prefixExpression = Task1(infixExpression);
  printf("The expression in prefix form: \"%s\"\n", prefixExpression);
  struct node* root = Task2(prefixExpression);
  printf("The prefix expression is converted into a rooted binary parse tree and stored at address \"%p\"\n", root);
  printf("The infix expression back by in-order traversal of the parse tree:"); Task3(root);
  printf("\n");
  int heightOfTree = Task4(root);
  printf("The height of a parse tree: \"%d\"\n", heightOfTree);
  printf("The input truth values of propositional atoms (T is True and F is False):\n");
  printf("::atom -> value::\n");
  for (int i = 0; i < length; i++){
    printf("   %c   ->   %c\n", (truthValues[i]).name, (truthValues[i]).value);
  }
  printf("The truth value of a propositional logic formula by traversing the tree in a bottom up fashion: \"%c\"", Task5(root, truthValues));
  clearTree(root);
  return 0;
}
