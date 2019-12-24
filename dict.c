#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"

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
int HashWord (pKey key, int size)
{
	char* word = (char*)key;
	return ((int)(word[0] - 'a') * 26 + strlen(word)) % size;
}

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
Result PrintEntry(pElement element)
{
	pWordNode node = (pWordNode)element;
	if (node == NULL)
		return FAIL;
	printf("%s : %s\n", node->word, node->translation);
	return SUCCESS;
}

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
CompResult CompareWords(pKey key1, pKey key2)
{
	char* word1 = (char*)key1;
	char* word2 = (char*)key2;
	return (strcmp(word1, word2) == 0);
}

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
pKey GetEntryKey(pElement element)
{
	pWordNode node = (pWordNode)element;
	return node->word;
}

//************************************************************************************* 
// Function name : DestroyEntry
//
// Description : Destroys an element of the dictionary
//
// Parameters:  1) a pointer to an element of the dictionary
//
// Return value : none
//*************************************************************************************
void DestroyEntry(pElement element)
{
	pWordNode node = (pWordNode)element;
	free(node);
}

//************************************************************************************* 
// Function name : CreateDictionary
//
// Description : Creates a hash table for the dictionary of size 25*26
//
// Parameters:  1) none
//
// Return value : a pointer to the hash table for the dictionary
//*************************************************************************************
pHash CreateDictionary()
{
	
	int size = 26*25;
	return HashCreate(size , HashWord, PrintEntry, CompareWords, GetEntryKey, DestroyEntry);
}

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
Result AddTranslation(pHash dictionary, char* word, char* translation)
{
	if (dictionary == NULL)
		return FAIL;

	pWordNode element =  HashFind(dictionary, (pKey)word);
	if (element != NULL)
		return FAIL;

	// create element
	pWordNode node = (pWordNode)malloc(sizeof(WordNode));
	if (node == NULL)
		return FAIL;
	strcpy(node->word, word);
	strcpy(node->translation, translation);

	// add element
	if (HashAdd(dictionary, (pElement)node) == FAIL)
	{
		free(node);
		return FAIL;
	}
	return SUCCESS;
}

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
Result Translate(pHash dictionary, char* word)
{
	//edge case
	if (dictionary == NULL)
		return FAIL;

	//get node
	pWordNode element = HashFind(dictionary, (pKey)word);
	if (element == NULL)
		return FAIL;

	//print
	printf("Translation: ");
	PrintEntry((pElement)element);
	return SUCCESS;
}

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
Result DeleteTranslation(pHash dictionary, char* word)
{
	//edge case
	if (dictionary == NULL)
		return FAIL;

	return HashRemove(dictionary, (pKey)word);
}

//************************************************************************************* 
// Function name : PrintDictionary
//
// Description : Prints out the entire contents of the dictionary
//
// Parameters:  1) a pointer to the dictionary
//
// Return value : SUCCESS if the printing was successful, FAIL if not
//*************************************************************************************
Result PrintDictionary(pHash dictionary)
{
	if (dictionary == NULL)
		return FAIL;
	printf("Dictionary Contents\n");
	return HashPrint(dictionary);
}

//************************************************************************************* 
// Function name : DestroyDictionary
//
// Description : Destroys the dictionary, and frees all allocated memory
//
// Parameters:  1) a pointer to the dictionary
//
// Return value : none
//*************************************************************************************
void DestroyDictionary(pHash dictionary)
{
	HashDestroy(dictionary);
}