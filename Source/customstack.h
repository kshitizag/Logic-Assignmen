/**
 * @file customstack.h
 * @brief File defining the stack data structure and related functions
 * @version 0.1
 * @date 2022-10-23
 */

/**
 * @def customstack_h
 * @brief PREPROCESSOR GUARDS
 */
#ifndef customstack_h
#define customstack_h

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Implementation of the stack data structure
 */
struct stack
{
  int maxsize;  /**< The maximum number of elements that can be stored in the stack*/
  int top;  /**< Index of the top element of the stack*/
  char* items;  /**< A pointer to an array holding the data in the stack*/
};

/**
 * @brief Creates a new stack
 * 
 * @param [in] capacity The maximum number of elements the stack can hold
 * @returns A pointer to the created stack
 */
struct stack* newStack(int capacity)
{
  struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
  
  // initialize all stack members
  pt->maxsize = capacity + 1;
  pt->top = -1;
  pt->items = (char*)malloc(sizeof(char) * (capacity + 1));
  
  return pt;
}
 
/**
 * @brief Checks if the stack is empty
 * 
 * @param [in] pt Pointer to the stack to be checked
 * @retval 0 If the stack is NOT EMPTY
 * @retval 1 If the stack is EMPTY
 */
int isEmpty(struct stack* pt) {
  // Uses the stack's top to find out if its empty
  return pt->top == -1;
}
 
/**
 * @brief Checks if the stack is full
 * 
 * @param [in] pt Pointer to the stack to be checked
 * @retval 0 If the stack is NOT FULL
 * @retval 1 If the stack is FULL
 */
int isFull(struct stack* pt) {
  // Uses the stack's top and maxsize to find out if its empty
  return pt->top == pt->maxsize - 1;
}
 
/**
 * @brief Adds an item to the stack
 * 
 * @param [in] pt Pointer to the stack to be used
 * @param [in] item The @c char to be pushed
 * 
 * @warning Using this function on a full (at maxsize) stack will lead to Stack Overflow Error
 */
void push(struct stack* pt, char item)
{
  // check if the stack is full
  if (isFull(pt))
  {
    // throw stack overflow error
    printf("Error: Stack Overflow\n");
    return;
  }
  
  // add an element and increment the top's index
  pt->items[++pt->top] = item;
}
 
/**
 * @brief Returns the item at the top of the stack
 * 
 * @param [in] pt Pointer to the stack to be used
 * @returns The @c char at the top of the stack
 * 
 * @warning Using this function on an empty stack will return @c \0
 */
char peek(struct stack* pt)
{
  // check if the stack is empty
  if (!isEmpty(pt)) {
    // return the item at top
    return pt->items[pt->top];
  } else {
    printf("Stack is Empty\n");
    return '\0';
  }
}
 
/**
 * @brief Removes the item at the top of the stack
 * 
 * @param [in] pt Pointer to the stack to be used
 * @returns The @c char at the top of the stack
 * 
 * @warning Using this function on an empty stack will lead to Stack Underflow Error and return @c \0
 */
char pop(struct stack* pt)
{
  // check if the stack is empty
  if (isEmpty(pt))
  {
    // throw stack underflow error
    printf("Error: Stack Underflow\n");
    return '\0';
  }

  // decrement stack size by 1 and (optionally) return the popped element
  return pt->items[pt->top--];
}

/**
 * @brief Clears a previously created stack from memory
 * 
 * @param [in] pt Pointer to the stack to be used
 * 
 * @warning A stack or its data should not be referenced after calling this function on it
 */
void clearStack(struct stack* pt){
  // free the data array in the stack
  free(pt->items);
  // free the stack structure
  free(pt);
}
#endif