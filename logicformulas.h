#ifndef logicformulas_h
#define logicformulas_h
#include "utilities.h"
#include "customtree.h"
#define T 'T'
#define F 'F'

struct atom
{
  char name;
  char value;
};


char evaluate(struct node*, struct atom[]);
char valueOfAtom(char, struct atom[]);
char NOT(char);
char AND(char, char);
char OR(char, char);
char IMPL(char, char);

char valueOfAtom(char nm, struct atom atoms[]){
  int size = sizeof(atoms)/ sizeof(atoms[0]);
  for(int i = 0; i < size; i++){
    if (atoms[i].name == nm){
      return atoms[i].value;
    }
  }
  printf("Error: Atom not defined");
}

char evaluate(struct node* root, struct atom atoms[]){
  if (isAtom(root->item)) return valueOfAtom(root->item, atoms);
  char lval, rval;
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

char NOT(char inp){
  if (inp == T){
    return F;
  } else {
    return T;
  }
}

char AND(char inp1, char inp2){
  if (inp1 == T && inp2 == T){
    return T;
  } else {
    return F;
  }
}

char OR(char inp1, char inp2){
  if (inp1 == T || inp2 == T){
    return T;
  } else {
    return F;
  }
}

char IMPL(char inp1, char inp2){
  if (inp1 == T && inp2 == F){
    return F;
  } else {
    return T;
  }
}
#endif