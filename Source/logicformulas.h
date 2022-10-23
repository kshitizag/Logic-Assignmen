/**
 * @file logicformulas.h
 * @brief File defining a propsitional logic atom and related functions to fully evaluate a propositional logic formula
 * @version 0.1
 * @date 2022-10-23 
 */

/**
 * @def logicformulas_h
 * @brief PREPROCESSOR GUARDS
 */
#ifndef logicformulas_h
#define logicformulas_h

#include "utilities.h"
#include "customtree.h"

/**
 * @brief T represents the boolean value "true"
 */
#define T 'T'
/**
 * @brief F represents the boolean value "false"
 */
#define F 'F'

/**
 * @brief Implementaion of a propositional logic atom
 */
struct atom
{
  char name;  /**< The character representing the atom*/
  char value;  /**< The truth value of the atom (will be either T or F)*/
};

char evaluate(struct node*, struct atom[]);
char valueOfAtom(char, struct atom[]);
char NOT(char);
char AND(char, char);
char OR(char, char);
char IMPL(char, char);

/**
 * @brief Returns the truth value of the propositional logic atom using the given list of atoms and their truth values
 * 
 * @param [in] nm The @c char name of the atom whose truth value if to be found
 * @param [in] atoms The input list of atom names and their truth values
 * @retval T for boolean True
 * @retval F for boolean False
 * 
 * @warning \0 is returned if the atom is not found in given list
 */
char valueOfAtom(char nm, struct atom atoms[]){
  // find the number of atoms using pointer sizes
  int numberOfAtoms = sizeof((struct atom*)atoms)/sizeof(atoms[0]);
  // iterate through the list, searching for the atom
  for(int i = 0; i < numberOfAtoms; i++){
    if (atoms[i].name == nm){
      return atoms[i].value;
    }
  }
  // the atom is not present in the given list
  printf("Error: Atom not defined");
  return '\0';
}

/**
 * @brief Evaluate the given parse tree expression in a bottom up fashion
 * 
 * @param [in] root The root of the parse tree to be evaluated
 * @param [in] atoms The list of propositional atoms and their truth values
 * @retval T for boolean True
 * @retval F for boolean False
 */
char evaluate(struct node* root, struct atom atoms[]){
  // return the value of an atom if the value of the node is an atom
  if (isAtom(root->item)) return valueOfAtom(root->item, atoms);
  char lval, rval;

  // for an operator, evaluate the children subtrees of the node and perform the corresponding operation
  if (root->item != '~'){
    lval = evaluate(root->left, atoms);
  }
  rval = evaluate(root->right, atoms);
  switch (root->item)
  {
  case '~':
    return NOT(rval);
    break;
  
  case '*':
    return AND(lval, rval);
    break;
  
  case '+':
    return OR(lval, rval);
    break;
  
  case '>':
    return IMPL(lval, rval);
    break;
  }
}

/**
 * @brief Performs (NOT inp)
 * 
 * @param [in] inp The input, either T or F
 * @retval T for boolean True
 * @retval F for boolean False
 */
char NOT(char inp){
  if (inp == T){
    return F;
  } else {
    return T;
  }
}

/**
 * @brief Perfoms (inp1 AND inp2)
 * 
 * @param [in] inp1 Input 1, either T or F
 * @param [in] inp2 Input 2, either T or F
 * @retval T for boolean True
 * @retval F for boolean False
 */
char AND(char inp1, char inp2){
  if (inp1 == T && inp2 == T){
    return T;
  } else {
    return F;
  }
}

/**
 * @brief Perfoms (inp1 OR inp2)
 * 
 * @param [in] inp1 Input 1, either T or F
 * @param [in] inp2 Input 2, either T or F
 * @retval T for boolean True
 * @retval F for boolean False
 */
char OR(char inp1, char inp2){
  if (inp1 == T || inp2 == T){
    return T;
  } else {
    return F;
  }
}

/**
 * @brief Perfoms (inp1 IMPLIES inp2)
 * 
 * @param [in] inp1 Input 1, either T or F
 * @param [in] inp2 Input 2, either T or F
 * @retval T for boolean True
 * @retval F for boolean False
 */
char IMPL(char inp1, char inp2){
  if (inp1 == T && inp2 == F){
    return F;
  } else {
    return T;
  }
}
#endif