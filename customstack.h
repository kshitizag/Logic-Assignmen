#ifndef customstack_h
#define customstack_h
#include <stdio.h>
#include <stdlib.h>

// Data structure to represent a stack
struct stack
{
    int maxsize;    // define max capacity of the stack
    int top;
    char *items;
};

// Function to create a new stack
struct stack* newStack(int capacity)
{
    struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
 
    pt->maxsize = capacity + 1;
    pt->top = -1;
    pt->items = (char*)malloc(sizeof(char) * (capacity + 1));
 
    return pt;
}
 
// Function to check if the stack is empty
int isEmpty(struct stack *pt) {
    return pt->top == -1;                   // or return size(pt) == 0;
}
 
//Function to check if the stack is full
int isFull(struct stack *pt) {
    return pt->top == pt->maxsize - 1;
}
 
//Function to add an element `x` to the stack
void push(struct stack *pt, char x)
{
    // check if the stack is already full. Then inserting an element would
    // lead to stack overflow
    if (isFull(pt))
    {
        printf("Error: Stack Overflow\n");
    }
    // add an element and increment the top's index
    pt->items[++pt->top] = x;
}
 
//Function to return the top element of the stack
char peek(struct stack *pt)
{
    // check for an empty stack
    if (!isEmpty(pt)) {
        return pt->items[pt->top];
    }
    else {
        printf("Stack is Empty\n");
        return '\0';
    }
}
 
// Function to pop a top element from the stack
char pop(struct stack *pt)
{
    // check for stack underflow
    if (isEmpty(pt))
    {
        printf("Error: Stack Underflow\n");
    } 
    // decrement stack size by 1 and (optionally) return the popped element
    return pt->items[pt->top--];
}
#endif