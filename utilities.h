#ifndef utilities_h
#define utilities_h
int isAtom(char);
int strLen(char*);

int isAtom(char chr){
  return ((65<=chr && chr<=90) || (97<=chr && chr<=122));
}

int strLen(char* exp){
  int len = 0;
  while(exp[len] != '\0'){
    len++;
  }
  return len;
}
#endif