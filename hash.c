#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

// the [0 to (size-1)] are pointers in the array.
// the (size) location is the address to the hash func 
pHash HashCreate(unsigned int size, HashFunc func)
{
	pHash hashTable = (pHash)calloc(NULL, sizeof(int)*(size + 1));
	if (hashTable == NULL)
	{
		printf("Error Allocating Memory");
		exit(-1);
		// need to add "Exit" from the program
	}

	hashTable + sizeof(int) * (size) = func; // still need to finish it, add the func to the last address of the array.

	return hashTable;
}
//This is just a test