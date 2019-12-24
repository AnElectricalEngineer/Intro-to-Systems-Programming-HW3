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
	//pHash dictionary;
	//dictionary = CreateDictionary();

	//char* word, * translation;
	//word = "dan";
	//translation = "ilan";

	//AddTranslation(dictionary, word, translation);
	//AddTranslation(dictionary, word, "boga");

	//word = "sahara";
	//translation = "smart";
	//AddTranslation(dictionary, word, translation);

	//Translate(dictionary, "dan");
	//Translate(dictionary, word);
	//Translate(dictionary, "moshe"); // cant be added to the dictionary
	////DeleteTranslation(dictionary, "sahara");
	//DeleteTranslation(dictionary, "dan");
	//PrintDictionary(dictionary);

	//DestroyDictionary(dictionary);

	pHash dictionary = ReadDictionary();
	PrintDictionary(dictionary);
	DeleteTranslation(dictionary, "dog");
	DeleteTranslation(dictionary, "cat");
	DeleteTranslation(dictionary, "astronaut");
	PrintDictionary(dictionary);
	AddTranslation(dictionary, "goat", "ez");
	AddTranslation(dictionary, "cow", "para");
	AddTranslation(dictionary, "school", "beitsefer");
	AddTranslation(dictionary, "boy", "yeled");
	PrintDictionary(dictionary);
	Translate(dictionary, "flag");
	Translate(dictionary, "goat");
	Translate(dictionary, "school");
	Translate(dictionary, "apple");
	DestroyDictionary(dictionary);


	//pHash dictionary = CreateDictionary();

	//char* word, * translation;
	//word = "dog";
	//translation = "kelev";
	//AddTranslation(dictionary, word, translation);

	//word = "cat";
	//translation = "hatul";
	//AddTranslation(dictionary, word, translation);

	//word = "flag";
	//translation = "degel";
	//AddTranslation(dictionary, word, translation);

	//word = "man";
	//translation = "ish";
	//AddTranslation(dictionary, word, translation);

	//word = "school";
	//translation = "beitsefer";
	//AddTranslation(dictionary, word, translation);

	//word = "woman";
	//translation = "isha";
	//AddTranslation(dictionary, word, translation);

	//word = "student";
	//translation = "talmid";
	//AddTranslation(dictionary, word, translation);

	//word = "home";
	//translation = "bayt";
	//AddTranslation(dictionary, word, translation);

	//word = "teacher";
	//translation = "more";
	//AddTranslation(dictionary, word, translation);

	//word = "exercise";
	//translation = "targil";
	//AddTranslation(dictionary, word, translation);
	//PrintDictionary(dictionary);
	return 0;
}