#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"

int HashWord(pKey word, int size)
{
	return ((int)(*((char*)word) - 'a') * 26 + strlen(word)) % size;
}

Result PrintEntry(pElement node)
{
	if (node == NULL)
		return FAIL;
	printf("%s:%s", ((pWordNode)node)->word, ((pWordNode)node)->translation);
	return SUCCESS;
}

CompResult CompareWords(pKey word1, pKey word2)
{
	return strcmp((char*)word1, (char*)word2);
}

pKey GetEntryKey(pElement node)
{
	if ((pWordNode)node == NULL)
		return NULL;
	return (pKey) (((pWordNode)node)->word);
}

void DestroyEntry(pElement node)
{
	free ((pWordNode)node);
}

pHash CreateDictionary()
{
	pHash dictionary = HashCreate(26, HashWord, PrintEntry, CompareWords, GetEntryKey, DestroyEntry);
	return dictionary;
}

Result AddTranslation(pHash dictionary, pKey word, char* translation)
{
	if (dictionary == NULL || word == NULL || translation == NULL)
		return FAIL;
	pElement element = HashFind(dictionary, word);
	if (element != NULL)
		return FAIL;
	pWordNode node = (pWordNode)malloc(sizeof(wordNode));
	if (node == NULL)
		return FAIL;
	strcpy(node->word, (char*)word);
	strcpy(node->translation, translation);
	return HashAdd(dictionary, (pElement)node);
}

Result Translate(pHash dictionary, pKey word)
{
	if (dictionary == NULL || word == NULL)
		return FAIL;
	pElement element = HashFind(dictionary, word);
	if (element == NULL)
		return FAIL;
	printf("Translation: ");
	PrintEntry(element);
	return SUCCESS;
}

Result DeleteTranslation(pHash dictionary, pKey word)
{
	if (dictionary == NULL || word == NULL)
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