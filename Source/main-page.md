
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
   > - push()
   > - peek()
   > - pop()
   > - isEmpty()
   > - isFull()
       >> Processing times independent of the size of their inputs
   > <br>
   > - newStack() 
   > - clearStack()
       >> Processing time dependent on the system (here: independent of input size)


----

### customtree.h

   > This file contains definition for binary tree @ref node data structure and related functions performing traversal, height calculation, creation and destruction operations on the tree.
  <br><br>
   > This structure is also used in evaluate() function
  <br><br>
   > The memory space taken up by the binary tree increases linearly with the number of nodes it has, but is constant throughout its lifetime (till it is cleared from the memory) in our program.
  <br><br>
   > - inorderTraversal()
   > - getHeight()
   > - makeTreeFromPrefix() 
       >> Processing times which increase linearly with the size of their input
   > <br>
   > - createNode() 
   > - clearTree()
       >> Processing time dependent on the system (here: independent of input size)


----

### infixtoprefix.h

   > This file contains all necessary functions to convert an infix propositional logic formula expression into its prefix form
  <br><br>
   > - outLen()
   > - getPrefix()
       >> Processing times which increase linearly with the size of their input
   > <br>
   > - getPrecedence()
       >> Processing time independent of the size of the input


----

### logicformulas.h

   > This file contains definition for the propositional logic @ref atom data structure, defines boolean True @ref T and boolean False @ref F constants, and related functions for finding the truth value of a logical formula
  <br><br>
   > All atom structures take up the same memory space
   >
   > - valueOfAtom()
   > - evaluate() 
       >> Processing times which increase linearly with the size of their input
   > <br>
   > - NOT()
   > - AND()
   > - OR()
   > - IMPL() 
       >> Processing times independent of the input size


----

## Task Solutions and Code Tests with Some Examples

**File:** Tasks.c

@note All codes are tested on the same machine with similar conditions.
Mean execution time is calculated across 5 different executions with the same input.

 > *Test Machine Specifications*
 > 1. Processor: Intel(R) Core(TM) i5-1035G1 CPU @ 1.00GHz   1.19 GHz
 > 2. Operating System: Windows 11 Home Single Language; Version: 22H2
 > 3. System Type: 64-bit operating system, x64-based processor
 > 4. Installed RAM: 8.00 GB (7.70 GB usable)


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
  > Mean Execution Time: 0.31 seconds

2. 
  > Input: @code char* infixExpression = "(((p)*(q)))>(r))" @endcode
  > Output: @code The expression in prefix form: ">*pqr" @endcode
  > Mean Execution Time: 0.3 seconds


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
  > Mean Execution Time: 0.302 seconds

2. 
  > Input: @code char* infixExpression = "(((p)*(q)))>(r))" @endcode
  > Output: @code The prefix expression is converted into a rooted binary parse tree and stored at address "0000016aa6b21610" @endcode
  > Mean Execution Time: 0.290 seconds


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
  Mean Execution Time: 0.288 seconds

2. 
  > Input: @code char* infixExpression = "(((p)*(q)))>(r))" @endcode
  > Output: @code The infix expression back by in-order traversal of the parse tree: "((p*q)>r)" @endcode
  Mean Execution Time: 0.322 seconds


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
  > Mean Execution Time: 0.295 seconds

2. 
  > Input: @code char* infixExpression = "(((p)*(q)))>(r))" @endcode
  > Output: @code The height of a parse tree: "3" @endcode
  > Mean Execution Time: 0.290 seconds


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
  > Mean Execution Time: 0.283 seconds

2. 
  > Input: @code char* infixExpression = "(((p)*(q)))>(r))" 
  struct atom truthValues[] = {{'p', F}, {'q', F}, {'r', F}}; @endcode
  > Output: @code The input truth values of propositional atoms (T is True and F is False):
::atom -> value::
   p   ->   F
   q   ->   F
   r   ->   F
The truth value of a propositional logic formula by traversing the tree in a bottom up fashion: "T" @endcode
  > Mean Execution Time: 0.290 seconds


----

## Alternate Algorithms and Efficiency

General steps taken to improve the code:

 - Include guards (also called Preprocessor guards) are added in all header files to safe-guard from double-inclusion

### Task 1

Steps taken to improve the code:

 - Iterating from end to start of the input string instead of reversing it

    > Reversing a string decreases time efficiency

 - Creating a stack structure instead of using stack functions (push, pop, ...) on an array

    > Increases memory usage a little, but improves readability and understanding of the code

 - Ignoring any white spaces in the expression

    > Increases code robustness


Few Steps that can be taken to improve the code:

 - Allow multiple characters and various symbols as logical atoms

    > Not taken as it will lead to more rules regarding atom naming, much more cases, and greater complexity


----


### Task 2

Steps taken to improve the code:

 - Making the function return the length of the substring used in creating the subtree (instead of finding the location of next node iteratively)

    > Improves code readability

 - Ignore any whitespaces in the expression

    > Increases code robustness


----

### Task 3

Steps taken to improve the code:

 - Adding brackets if the node doesn,t represent a propositional atom

    > Makes the output more presentable as an infix notation formula


----

### Task 5

Steps taken to improve the code:

 - Creating an array of atom structures to represent the propositional logic atom truth values instead of creating two arrays and using a common reference

    > Makes the code more readable and easy to work with


 - Defining T (representing True) and F (representing False) as macro constants

    > makes the code uniform and reduces data misuse


----

## Team Information

Our Team consists of the following 4 students:

1. Aryan Gupta, @c 2021A7PS0162H
2. Kshitiz Agarwal, @c 2021A7PS1818H
3. Mihir Kulkarni, @c 2021A7PS2689H
4. Soumya Choudhury, @c 2021A7PS2674H
