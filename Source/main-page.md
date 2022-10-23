
# Assignment 1

## Code Analysis

The complete code has been broken down into 5 header files to contain all internal functions:

  1. utilities.h
  2. customstack.h
  3. customtree.h
  4. infixtoprefix.h
  5. logicformulas.h

and a separate .c file containing separate functions for each assignment Task (1 to 5) 

  Tasks.c

----

### utilities.h

   > This file contains common helper functions, used by many other functions
   > - isAtom() 
   >> Processing time is independent of input
   >
   > - strLen()
   >> Processing time increases linearly with input size


----

### customstack.h

   > This file contains definition for @ref stack data structure and related functions performing push, peek, pop, creation and destruction operations on the stack. <br><br>
   > This structure is also used in getPrefix() function.
   <br><br>
   > The memory space taken up by the stack increases linearly with its maxsize, but is constant throughout its lifetime (till it is cleared from the memory) in our program.
   <br><br>
   > push(), peek(), pop(), isEmpty(), isFull(), newStack() have processing times independent of the size of their inputs


----

### customtree.h

   > This file contains definition for binary tree @ref node data structure and related functions performing traversal, height calculation, creation and destruction operations on the tree.
  <br><br>
   > This structure is also used in evaluate() function
  <br><br>
   > The memory space taken up by the binary tree increases linearly with the number of nodes it has, but is constant throughout its lifetime (till it is cleared from the memory) in our program.
  <br><br>
   > inorderTraversal(), getHeight(), makeTreeFromPrefix() have processing times which increase linearly with the size of their input
  <br><br>
   > createNode() has processing time independent of the size of its input 


----

### infixtoprefix.h

   > This file contains all necessary functions to convert an infix propositional logic formula expression into its prefix form
  <br><br>
   > inorderTraversal(), getHeight(), makeTreeFromPrefix() have processing times which increase linearly with the size of their input
  <br><br>
   > getPrecedence() has processing time independent of the size of the input
  <br><br>
   > outLen() and getPrefix() have processing times which increase linearly with the size of their input


----

### logicformulas.h

   > This file contains definition for the propositional logic @ref atom data structure, defines boolean True @ref T and boolean False @ref F constants, and related functions for finding the truth value of a logical formula
  <br><br>
   > All atom structures take up the same memory space
  <br><br>
   > valueOfAtom() and evaluate() have processing times which increase linearly with the size of their input
  <br><br>
   > NOT(), AND(), OR(), IMPL() have processing times independent of the input size


----

## Task Solutions and Code Examples

**File:** Tasks.c

----

### Task 1

*Code:*

    char* Task1(char* infixExp){
      return getPrefix(infixExp);
    }
    int main(){
      char* infixExpression = " a + b > ~ ( b + c ) "; // Given Input

      char* prefixExpression = Task1(infixExpression);
      printf("The expression in prefix form: \"%s\"\n", prefixExpression);
      free(prefixExpression);
    }

*Examples:*

1. 
  > Input: @code char* infixExpression = " a + b > ~ ( b + c ) " @endcode
  > Output: @code The expression in prefix form: ">+ab~+bc" @endcode

2. 
  > Input: @code char* infixExpression = "(((p)*(q)))>(r))" @endcode
  > Output: @code The expression in prefix form: ">*pqr" @endcode


----

### Task 2

*Code:*

    struct node* Task2(char* prefixExp){
      struct node* root = createNode('\0');
      makeTreeFromPrefix(root, prefixExp);
      return root;
    }
    int main(){
      char* infixExpression = " a + b > ~ ( b + c ) "; // Given Input

      char* prefixExpression = Task1(infixExpression);
      struct node* root = Task2(prefixExpression);  // Use of Task 2
      printf("The prefix expression is converted into a rooted binary parse tree and stored at address \"%p\"\n", root);
      free(prefixExpression);
      clearTree(root);
    }

*Examples:*

1. 
  > Input: @code char* infixExpression = " a + b > ~ ( b + c ) " @endcode
  > Output: @code The prefix expression is converted into a rooted binary parse tree and stored at address "00000276e0871610" @endcode

2. 
  > Input: @code char* infixExpression = "(((p)*(q)))>(r))" @endcode
  > Output: @code The prefix expression is converted into a rooted binary parse tree and stored at address "0000016aa6b21610" @endcode


----

### Task 3

*Code:*

    void Task3(struct node* root){
      inorderTraversal(root);
    }
    int main(){
      char* infixExpression = " a + b > ~ ( b + c ) ";  // Given Input

      char* prefixExpression = Task1(infixExpression);
      struct node* root = Task2(prefixExpression);
      printf("The infix expression back by in-order traversal of the parse tree: \"");
      Task3(root);  // Use of Task 3
      printf("\"\n");
      free(prefixExpression);
      clearTree(root);
    }

*Examples:*

1. 
  > Input: @code char* infixExpression = " a + b > ~ ( b + c ) " @endcode
  > Output: @code The infix expression back by in-order traversal of the parse tree: "((a+b)>(~(b+c)))" @endcode

2. 
  > Input: @code char* infixExpression = "(((p)*(q)))>(r))" @endcode
  > Output: @code The infix expression back by in-order traversal of the parse tree: "((p*q)>r)" @endcode


----

### Task 4

*Code:*

    int Task4(struct node* root){
      return getHeight(root);
    }
    int main(){
      char* infixExpression = " a + b > ~ ( b + c ) "; // Given Input

      char* prefixExpression = Task1(infixExpression);
      struct node* root = Task2(prefixExpression);
      int heightOfTree = Task4(root); // Use of Task4
      printf("The height of a parse tree: \"%d\"\n", heightOfTree);
      free(prefixExpression);
      clearTree(root);
    }

*Examples:*

1. 
  > Input: @code char* infixExpression = " a + b > ~ ( b + c ) " @endcode
  > Output: @code The height of a parse tree: "4" @endcode

2. 
  > Input: @code char* infixExpression = "(((p)*(q)))>(r))" @endcode
  > Output: @code The height of a parse tree: "3" @endcode


----

### Task 5

*Code:*

    char Task5(struct node* root, struct atom atoms[]){
      return evaluate(root, atoms);
    }
    int main(){
      char* infixExpression = " a + b > ~ ( b + c ) "; // Given Input
      struct atom truthValues[] = {{'a', T}, {'b', T}, {'c', F}}; // Given Input

      char* prefixExpression = Task1(infixExpression);
      struct node* root = Task2(prefixExpression);
      printf("The input truth values of propositional atoms (T is True and F is False):\n");
      printf("::atom -> value::\n");
      for (int i = 0; i < numberOfAtoms; i++){
        printf("   %c   ->   %c\n", (truthValues[i]).name, (truthValues[i]).value);
      }
      printf("The truth value of a propositional logic formula by traversing the tree in a bottom up fashion: \"%c\"", Task5(root, truthValues));
      free(prefixExpression);
      clearTree(root);
    }

*Examples:*

1. 
  > Input: @code char* infixExpression = " a + b > ~ ( b + c ) " 
  struct atom truthValues[] = {{'a', T}, {'b', T}, {'c', F}}; @endcode
  > Output: @code The input truth values of propositional atoms (T is True and F is False):
::atom -> value::
   a   ->   T
   b   ->   T
   c   ->   F
The truth value of a propositional logic formula by traversing the tree in a bottom up fashion: "F" @endcode

2. 
  > Input: @code char* infixExpression = "(((p)*(q)))>(r))" 
  struct atom truthValues[] = {{'p', F}, {'q', F}, {'r', F}}; @endcode
  > Output: @code The input truth values of propositional atoms (T is True and F is False):
::atom -> value::
   p   ->   F
   q   ->   F
   r   ->   F
The truth value of a propositional logic formula by traversing the tree in a bottom up fashion: "T" @endcode


----

## Alternate Algorithms and Efficiency




----


## Team Information

Our Team consists of the following 4 people:

1. Aryan Gupta, @c 2021A7PS0162H
2. Kshitiz Agarwal, @c 2021A7PS1818H
3. Mihir Kulkarni, @c 2021A7PS2689H
4. Soumya Choudhury,@c 2021A7PS2674H
