#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"


int HashWord (char* word, int size)
{
	return ((int)(word - 'a') * 26 + strlen(word)) % size;
}

Result PrintEntry(pWordNode node)
{
	if (node == NULL)
		return FAIL;
	printf("%s : %s", (node)->word, (node)->translation);
	return SUCCESS;
}

CompResult CompareWords(char* word1, char* word2)
{
	return (strcmp(word1, word2) == 0);
}

pKey GetEntryKey(pWordNode node)
{
	return node->word;
}

void DestroyEntry(pWordNode node)
{
	free(node);
	return;
}

pHash CreateDictionary()
{
	unsigned int size = 26;
	return HashCreate(size , HashWord, PrintEntry, CompareWords, GetEntryKey, DestroyEntry);
}

Result AddTranslation(pHash dictionary, char* word, char* translation)
{
	if (dictionary == NULL)
		return FAIL;

	pWordNode element =  HashFind(dictionary, word);
	if (element != NULL)
		return FAIL;

	// creat element
	pWordNode node = (pWordNode)malloc(sizeof(WordNode));
	if (node == NULL)
		return FAIL;
	strcpy(node->word, word);
	strcpy(node->translation, translation);

	// add element
	return HashAdd(dictionary, (node));


	//strcpy( ((pWordNode)element)->translation, translation );
}

Result Translate(pHash dictionary, char* word)
{
	//edge case
	if (dictionary == NULL)
		return FAIL;

	//get node
	pWordNode element = HashFind(dictionary, word);
	if (element == NULL)
		return FAIL;

	//print
	printf("Translation: ");
	PrintEntry(element);
	printf("\n");
	return SUCCESS;
}

Result DeleteTranslation(pHash dictionary, char* word)
{
	//edge case
	if (dictionary == NULL)
		return FAIL;

	return HashRemove(dictionary, word);
}

Result PrintDictionary(pHash dictionary)
{
	if (dictionary == NULL)
		return FAIL;
	printf("Dictionary Contents\n");
	return HashPrint(dictionary);
}

void DestroyDictionary(pHash dictionary)
{
	HashDestroy(dictionary);
	return;
}
