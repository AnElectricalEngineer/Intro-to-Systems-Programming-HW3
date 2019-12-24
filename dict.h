#ifndef DICT_H
#define DICT_H

#include "hash.h"

#define MAX_WORD_LEN 25

typedef struct _WORD_NODE
{
	char word[MAX_WORD_LEN];
	char translation[MAX_WORD_LEN];
} WordNode, *pWordNode;

int HashWord(pKey, int);
Result PrintEntry(pElement);
CompResult CompareWords(pKey, pKey);
pKey GetEntryKey(pElement);
void DestroyEntry(pElement);

pHash CreateDictionary();
Result AddTranslation(pHash, char*, char*);
Result Translate(pHash, char*);
Result DeleteTranslation(pHash, char*);
Result PrintDictionary(pHash);

void DestroyDictionary(pHash);
#endif