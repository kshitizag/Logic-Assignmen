#ifndef infixtoprefix_c
#define infixtoprefix_c
#include <stdio.h>
#include <stdlib.h>
#include "customstack.h" // Custom file for stack
#include "utilities.h"

int getPrecedence(char);
int outLen(char *);
char* getPrefix(char*);

char* getPrefix(char* exp){
  int outPos = outLen(exp) - 1;
  int inPos = strLen(exp) - 1;
  char nextChar;
  char* out = (char*)calloc(outPos + 1, sizeof(char));
  struct stack *oprtr = newStack(inPos + 1);
  while(inPos>=0){
    nextChar = exp[inPos];
    switch (nextChar)
    {
      case ' ':
        break;
      case ')':
        push(oprtr, nextChar);
        break;
      case '(':
        while (peek(oprtr) !=')') {
					out[outPos--]=pop(oprtr);
				}
				pop(oprtr);
        break;

      case '+':
      case '~':
      case '*':
      case '>':
        if (isEmpty(oprtr) || (getPrecedence(nextChar) >= getPrecedence(peek(oprtr)))){
          push(oprtr, nextChar);
        } else {
          while(!isEmpty(oprtr) && getPrecedence(nextChar) <= getPrecedence(peek(oprtr))) {
						out[outPos--]=pop(oprtr);
					}
          push(oprtr, nextChar);
        }
        break;

      default:
        if (isAtom(nextChar)){
          out[outPos--] = nextChar;
        } else {
          printf("Invalid Logical Operator %c", nextChar);
        return out;
      }
        break;
    }
    inPos--;
  }
  while (!isEmpty(oprtr)) {
    out[outPos--]=pop(oprtr);
	}
  free(oprtr);
  return out;
}

int getPrecedence(char oprtr){
  switch (oprtr)
  {
  case '~':
    return 4;
  case '*':
    return 3;
  case '+':
    return 2;
  case '>':
    return 1;
  default:
    return -1;
  }
}

int outLen(char * exp){
  int len = 0;
  while(exp[0] != '\0'){
    if (exp[0] != '(' && exp[0] != ')' && exp[0] != ' '){
      len++;
    }
    exp++;
  }
  return len;
}
#endif