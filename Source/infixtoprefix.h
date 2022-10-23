/**
 * @file infixtoprefix.h
 * @brief File containing all necessary functions to convert an infix propositional logic formula expression into its prefix form
 * @version 0.1
 * @date 2022-10-23 
 */

/**
 * @def infixtoprefix_c
 * @brief PREPROCESSOR GUARDS
 */
#ifndef infixtoprefix_c
#define infixtoprefix_c

#include <stdio.h>
#include <stdlib.h>
#include "customstack.h"
#include "utilities.h"

int getPrecedence(char);
int outLen(char *);
char* getPrefix(char*);

/**
 * @brief Returns the prefix form of the given infix expression
 * 
 * Some notes about the input and the function:
 *   -# The input must be a well formed propositional logic formula expression in infix form
 *   -# All whitespace between characters will be ignored
 *   -# The formula need not be well bracketed, in case of missing brackets, precedence is calculated by getPrecedence()
 *   -# The expression is considered to be case sensitive (a and A are different atoms)
 *   .
 * The memory for the output is dynamically allocated. \ref stack data structure is used to store the operators untl they are needed
 * 
 * @param [in] infixExp The proposition logic formula expression in infix form ( @c char array)
 * @returns The proposition logic formula expression in prefix form ( @c char array)
 */
char* getPrefix(char* infixExp){
  // find the length of input and output, and allocate memory
  int outPos = outLen(infixExp) - 1;
  int inPos = strLen(infixExp) - 1;
  char nextChar;
  char* out = (char*)calloc(outPos + 1, sizeof(char));
  struct stack* oprtr = newStack(inPos + 1);

  // the input is iterated from back to front
  while(inPos>=0){
    nextChar = infixExp[inPos];
    switch (nextChar)
    {
      // ignore whitespace
      case ' ':
      case '\t':
      case '\n':
        break;
      
      // brackets are followed whenever present
      case ')':
        push(oprtr, nextChar);
        break;
      
      case '(':
        while (peek(oprtr) !=')') {
					out[--outPos]=pop(oprtr);
				}
				pop(oprtr);
        break;

      // check if nextChar is a defined operator
      case '+':
      case '~':
      case '*':
      case '>':
        // precedence is followed in absence of brackets
        if (isEmpty(oprtr) || (getPrecedence(nextChar) >= getPrecedence(peek(oprtr)))){
          push(oprtr, nextChar);
        } else {
          while(!isEmpty(oprtr) && getPrecedence(nextChar) <= getPrecedence(peek(oprtr))) {
						out[--outPos]=pop(oprtr);
					}
          push(oprtr, nextChar);
        }
        break;
      
      // nextChar is not a operator nor a bracket nor a whitespace
      default:
        if (isAtom(nextChar)){
          out[--outPos] = nextChar;
        } else {
          printf("Invalid Logical Operator %c", nextChar);
          return out;
        }
        break;
    }
    inPos--;
  }

  // add any remaining operators in the stack
  while (!isEmpty(oprtr)) {
    out[--outPos]=pop(oprtr);
	}

  // clear stack from memory
  clearStack(oprtr);
  return out;
}

/**
 * @brief Returns an integer representing the precedence of the input operator
 * 
 * Precedence used:
 *   -# ~
 *   -# *
 *   -# +
 *   -# >
 *   .
 * @c -1 is returned if the @c oprtr is not one of the above
 * 
 * @param [in] oprtr The operator whose precedence is to be checked
 * @returns An @c int representing the @c oprtr 's precedence
 */
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

/**
 * @brief A helper function to find the length of the outputprefix expression ( @c char array) for a given input infix expression
 * 
 * @note @c \0 at the end of the string is counted too
 * 
 * @param [in] infixExp The input infix expression
 * @returns The length of the output prefix expression
 */
int outLen(char * infixExp){
  int len = 1;  // for \0 at the end
  while(infixExp[0] != '\0'){
    // ignore brackets and whitespaces
    if (infixExp[0] != '(' && infixExp[0] != ')' && infixExp[0] != ' ' && infixExp[0] != '\t' && infixExp[0] != '\n'){
      len++;
    }
    infixExp++;
  }
  return len;
}
#endif