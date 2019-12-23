#ifndef _DICT_H_
#define _DICT_H_

#include "hash.h"

#define MAX_WORD_LEN 25

typedef struct _WORD_NODE
{
	char word[MAX_WORD_LEN+1];
	char translation[MAX_WORD_LEN+1];
} wordNode, *pWordNode;

int HashWord(pKey, int);
Result PrintEntry(pElement);
CompResult CompareWords(pKey, pKey);
pKey GetEntryKey(pElement);
void DestroyEntry(pElement);
pHash CreateDictionary();
Result AddTranslation(pHash, pKey, char*);
Result Translate(pHash, pKey);
Result DeleteTranslation(pHash, pKey);
Result PrintDictionary(pHash);
#endif