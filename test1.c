#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"

pHash ReadDictionary () {	
	/* This function reads a dictionary line by line from the standard input. */
	pHash dictionary;
	char entryLine [100] = "";
	char *word, *translation;

	dictionary = CreateDictionary();

	while (scanf ("%s", entryLine) == 1) { // Not EOF
		word = strtok(entryLine, "=");
		translation = strtok(NULL, "=");
		AddTranslation(dictionary, word, translation);
	}

	return dictionary;
}

int main ()
{
	pHash dictionary;
	dictionary = CreateDictionary();

	char* word, * translation;
	word = "dan";
	translation = "ilan";

	AddTranslation(dictionary, word, translation);
	AddTranslation(dictionary, word, "boga");

	word = "sahara";
	translation = "smart";
	AddTranslation(dictionary, word, translation);

	Translate(dictionary, "dan");
	Translate(dictionary, word);
	Translate(dictionary, "moshe"); // not in the dictionary
	DeleteTranslation(dictionary, "sahara");
	DeleteTranslation(dictionary, "dan");
	PrintDictionary(dictionary);

	DestroyDictionary(dictionary);
	return 0;
}
