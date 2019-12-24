#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"

int HashWord (pKey key, int size)
{
	char* word = (char*)key;
	return ((int)(word[0] - 'a') * 26 + strlen(word)) % size;
}

Result PrintEntry(pElement element)
{
	pWordNode node = (pWordNode)element;
	if (node == NULL)
		return FAIL;
	printf("%s : %s\n", node->word, node->translation);
	return SUCCESS;
}

CompResult CompareWords(pKey key1, pKey key2)
{
	char* word1 = (char*)key1;
	char* word2 = (char*)key2;
	return (strcmp(word1, word2) == 0);
}

pKey GetEntryKey(pElement element)
{
	pWordNode node = (pWordNode)element;
	return node->word;
}

void DestroyEntry(pElement element)
{
	pWordNode node = (pWordNode)element;
	free(node);
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
	printf("\n");
	return SUCCESS;
}

Result DeleteTranslation(pHash dictionary, char* word)
{
	//edge case
	if (dictionary == NULL)
		return FAIL;

	return HashRemove(dictionary, (pKey)word);
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
}