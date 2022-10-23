/**
 * @file utilities.h
 * @brief File containing common helper functions for all other functions
 * @version 0.1
 * @date 2022-10-23
 */

/**
 * @def utilities_h
 * @brief PREPROCESSOR GUARDS
 */
#ifndef utilities_h
#define utilities_h

int isAtom(char);
int strLen(char*);

/**
 * @brief Checks if the given character is a valid propositional logic atom
 * 
 * @param [in] chr The @c char to be checked
 * @retval 0 If @c chr is *NOT* a valid atom
 * @retval 1 If @c chr is a valid atom
 */
int isAtom(char chr){
  // checks if chr is a lowercase or uppercase alphabet
  return ((65<=chr && chr<=90) || (97<=chr && chr<=122));
}

/**
 * @brief Returns the length of the input string
 * 
 * @param [in] str The pointer to the beginning of the string ( @c char array)
 * @returns Length of the string
 */
int strLen(char* str){
  int len = 0;
  while(str[len] != '\0'){
    len++;
  }
  return len;
}
#endif