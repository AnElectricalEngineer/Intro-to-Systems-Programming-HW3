#ifndef DICT_H
#define DICT_H

#include "hash.h"

#define MAX_WORD_LEN 25

typedef struct _WORD_NODE
{
	char word[MAX_WORD_LEN];
	char translation[MAX_WORD_LEN];
} WordNode, *pWordNode;

//************************************************************************************* 
// Function name : HashWord
//
// Description : Receives a word and size of hash table (dictionary) and
//				 performs the hash operation
//
// Parameters:  1) pointer to key (word) to hash
//				2) size of hash table (for hashing function)
//
// Return value : the result of the hash function (int)
//*************************************************************************************
int HashWord(pKey, int);
//************************************************************************************* 
// Function name : PrintEntry
//
// Description : Receives an word and translation, and prints the word and
//				 translation
//
// Parameters:  1) a pointer to an element in the dictionary
//
// Return value : SUCCESS if successful, FAIL otherwise
//*************************************************************************************
Result PrintEntry(pElement);
//************************************************************************************* 
// Function name : CompareWords
//
// Description : Checks if two words are identical
//
// Parameters:  1) pointer to first word
//				2) pointer to second word
//
// Return value : SAME if the words are identical, DIFFERENT if they are different
//*************************************************************************************
CompResult CompareWords(pKey, pKey);
//************************************************************************************* 
// Function name : GetEntryKey
//
// Description : Receives an element (word and translation) in the dictionary and
//				 returns its key as a pointer
//
// Parameters:  1) a pointer to an element in the dictionary
//
// Return value : a pointer to the key of the element
//*************************************************************************************
pKey GetEntryKey(pElement);
//************************************************************************************* 
// Function name : DestroyEntry
//
// Description : Destroys an element of the dictionary
//
// Parameters:  1) a pointer to an element of the dictionary
//
// Return value : none
//*************************************************************************************
void DestroyEntry(pElement);

//************************************************************************************* 
// Function name : CreateDictionary
//
// Description : Creates a hash table for the dictionary of size 25*26
//
// Parameters:  1) none
//
// Return value : a pointer to the hash table for the dictionary
//*************************************************************************************
pHash CreateDictionary();
//************************************************************************************* 
// Function name : AddTranslation
//
// Description : Adds a word along with the matching translation to the dictionary
//
// Parameters:  1) a pointer to the dictionary
//				2) the word to add
//				3) the translation of the word
//
// Return value : SUCCESS if the addition was successful, FAIL if not
//*************************************************************************************
Result AddTranslation(pHash, char*, char*);
//************************************************************************************* 
// Function name : Translate
//
// Description : Finds a word in the dictionary and prints out the word and the
//				 translation
//
// Parameters:  1) a pointer to the hash table
//				2) a word whose translation must be found
//
// Return value : SUCCESS if the translation was successful, FAIL if not
//*************************************************************************************
Result Translate(pHash, char*);
//************************************************************************************* 
// Function name : DeleteTranslation
//
// Description : Removes a word and its translation from the dictionary
//
// Parameters:  1) a pointer to the hash table of the dictionary
//				2) the word to be deleted from the dictionary
//
// Return value : SUCCESS if the deletion was successful, FAIL if not
//*************************************************************************************
Result DeleteTranslation(pHash, char*);
//************************************************************************************* 
// Function name : PrintDictionary
//
// Description : Prints out the entire contents of the dictionary
//
// Parameters:  1) a pointer to the dictionary
//
// Return value : SUCCESS if the printing was successful, FAIL if not
//*************************************************************************************
Result PrintDictionary(pHash);

//************************************************************************************* 
// Function name : DestroyDictionary
//
// Description : Destroys the dictionary, and frees all allocated memory
//
// Parameters:  1) a pointer to the dictionary
//
// Return value : none
//*************************************************************************************
void DestroyDictionary(pHash);
#endif