#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"


int HashWord (pKey word, int size)
{
	return ((int)((char*)word - 'a') * 26 + strlen((char*)word)) % size;
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
	/*for (int i = 0; i < 25; i++)
	{
		if (word1[i] != word2[i])
			return DIFFERENT;
		if (word1[i] == 0x00)
			return SAME;
	}
	return SAME;*/
	return strcmp((char*)word1, (char*)word2);
}

pKey GetEntryKey(pElement node)
{
	return (pKey) ( ((pWordNode)node)->word );
}

void DestroyEntry(pElement node)
{
	free((pWordNode)node);
	return;
}

pHash CreateDictionary()
{
	unsigned int size = 26;
	return HashCreate(size , HashWord, PrintEntry, CompareWords, GetEntryKey, DestroyEntry);
}

Result AddTranslation(pHash dictionary, pKey word, char* translation)
{
	if (dictionary == NULL)
		return FAIL;

	pElement element =  HashFind(dictionary, word);
	if (element != NULL)
		return FAIL;

	// creat element
	pWordNode node = (pWordNode)malloc(sizeof(WordNode));
	if (node == NULL)
		return FAIL;
	strcpy(node->word, (char*)word);
	strcpy(node->translation, translation);

	// add element
	return HashAdd(dictionary, ((pElement)node));


	//strcpy( ((pWordNode)element)->translation, translation );
}

Result Translate(pHash dictionary, pKey word)
{
	//edge case
	if (dictionary == NULL)
		return FAIL;

	//get node
	pElement element = HashFind(dictionary, word);
	if (element == NULL)
		return FAIL;

	//print
	printf("Translation ");
	PrintEntry(element);
	return SUCCESS;
}

Result DeleteTranslation(pHash dictionary, pKey word)
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
