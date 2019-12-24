#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _ELEMENT_NODE
{
	pElement element;
	struct _ELEMENT_NODE* next;
}ElementNode, *pElementNode;

typedef struct _Hash
{
	pElementNode *pFirstNode;
	HashFunc func;
	PrintFunc print;
	CompareFunc comp;
	GetKeyFunc getKey;
	DestroyFunc destroy;
	int size;

} Hash, *pHash;

//************************************************************************************* 
// Function name : HashCreate
//
// Description : creates an empty hash table w/undefined (NULL) elements
//
// Parameters:  1) size of array
//				2) pointer to user-supplied hashing function
//				3) pointer to user-supplied element printing function
//				4) pointer to user-supplied function that compares keys of two elements
//				5) pointer to user-supplied function that returns key of element
//				6) pointer to user-supplied function that destroys the hash table
//
// Return value : pointer to hash table, or NULL on failure
//*************************************************************************************
pHash HashCreate(int size, HashFunc func, PrintFunc print, CompareFunc comp, GetKeyFunc getKey, DestroyFunc destroy)
{
	// create hash table
	pHash hashTable = (pHash)malloc(sizeof(Hash));
	if (hashTable == NULL)
	{
		printf("Error Allocating Memory");
		exit(-1);
	}

	// create the hash and set all the address to NULL
	hashTable->pFirstNode = (pElementNode*)malloc(size*sizeof(pElementNode));
	if (hashTable->pFirstNode == NULL)
	{
		printf("Error Allocating Memory");
		free(hashTable);
		exit(-1);
	}
	pElementNode* indxPtr = hashTable->pFirstNode;
	for (int i = 0; i < size; i++)
	{
		*(indxPtr + i) = NULL;
	}
	//create pointer to the funcs
	hashTable->func = func;
	hashTable->print = print;
	hashTable->comp = comp;
	hashTable->getKey = getKey;
	hashTable->destroy = destroy;
	hashTable->size = size;
	
	return hashTable;
}

//************************************************************************************* 
// Function name : HashAdd
//
// Description : inserts a new element into the hash table
//				 new elements are inserted at the HEAD of the linked list 
//
// Parameters:  1) pointer to hash table
//				2) pointer to new element to be added
//
// Return value : FAIL if unsuccessful, SUCCESS if successful
//*************************************************************************************
Result HashAdd(pHash hashTable, pElement element)
{
	// edge case
	if (hashTable == NULL || element == NULL || HashFind(hashTable, hashTable->getKey(element)) != NULL)
		return FAIL;

	// create node
	pElementNode pNode = (pElementNode)malloc(sizeof(ElementNode));
	if (pNode == NULL)
	{
		printf("Error Allocating Memory");
		exit(-1);
	}
	pNode->element = element;

	// get keyHash
	pKey key = hashTable->getKey(element);
	int size = hashTable->size;
	int keyHash = hashTable->func(key, size);
	// link the element
	pElementNode* indxPtr = hashTable->pFirstNode + keyHash;
	pNode->next = *indxPtr;
	*indxPtr = pNode;

	return SUCCESS;
}

//************************************************************************************* 
// Function name : HashFind
//
// Description : searches for element in hash table with a given key
//
// Parameters:  1) pointer to hash table
//				2) pointer to key of element to search for
//
// Return value : pointer to element with requested key, or NULL if doesn't exist
//*************************************************************************************
pElement HashFind(pHash hashTable, pKey key)
{
	// edge case
	if (hashTable == NULL || key == NULL)
		return NULL;

	// get keyHash
	int size = hashTable->size;
	int keyHash = hashTable->func(key, size);

	// search the key in the node
	pElementNode* indxPtr = hashTable->pFirstNode + keyHash;
	pElementNode searchElement = *indxPtr;
	// search in the hashKeyNode until node==NULL
	for (; searchElement; searchElement = searchElement->next)
	{
		if (hashTable->comp(hashTable->getKey(searchElement->element), key))
			return searchElement->element;
	}

	//fail, key not found
	return NULL;
}

//************************************************************************************* 
// Function name : HashRemove
//
// Description : finds element with given key, and deletes the element from the hash
//			     table - frees memory allocated
//
// Parameters:  1) pointer to hash table
//				2) pointer to key of element to remove
//
// Return value : SUCCESS if successfully removed element, FAIL if not
//*************************************************************************************
Result HashRemove(pHash hashTable, pKey key)
{
	// edge case. and make sure there is at least one element in the node
	if (hashTable == NULL || key == NULL || HashFind(hashTable, key) == NULL)
		return FAIL;

	// get keyHash
	int size = hashTable->size;
	int keyHash = hashTable->func(key, size);

	// search the key in the node
	pElementNode* indxPtr = hashTable->pFirstNode + keyHash;
	pElementNode searchElement = *(indxPtr);
	// if the node is the first node
	if (hashTable->comp(hashTable->getKey(searchElement->element), key))
	{
		// destroy the first elementNode
		*(indxPtr) = searchElement->next;
		hashTable->destroy(searchElement->element);
		free(searchElement);
		return SUCCESS;
	}

	// the node is not the first one, so there are at least 2 elements
	// search in the hashKeyNode until node==NULL
	pElementNode preElement = searchElement;
	searchElement = searchElement->next;
	while (searchElement)
	{
		if (hashTable->comp(hashTable->getKey(searchElement->element), key))
		{
			preElement->next = searchElement->next;
			hashTable->destroy(searchElement->element);
			free(searchElement);
			return SUCCESS;
		}
		preElement = preElement->next;
		searchElement = searchElement->next;
	}

	//fail, key not found
	return FAIL;
}

//************************************************************************************* 
// Function name : HashPrint
//
// Description : prints the elements in the hash table
//				 prints the elements from the array in order from index 0 to size-1,
//				 where each linked list is printed from the head to the tail
//
// Parameters:  1) pointer to hash table
//
// Return value : SUCCESS if succeeded printing, FAIL if not
//*************************************************************************************
Result HashPrint(pHash hashTable)
{
	//edge case
	if (hashTable == NULL)
		return FAIL;

	// print
	pElementNode* indxPtr;
	for (int i = 0; i < hashTable->size; i++)
	{
		indxPtr = hashTable->pFirstNode + i;
		for (pElementNode searchElement = *indxPtr; searchElement != NULL; searchElement = searchElement->next)
		{
			hashTable->print(searchElement->element);
		}
	}
	return SUCCESS;
}

// Function name : HashDestroy
//
// Description : destroys the entire hash table and frees all dynamically allocated
//				 memory
//
// Parameters:  1) pointer to hash table
//
// Return value : SUCCESS if hash table destroyed successfully, FAIL otherwise
//*************************************************************************************
Result HashDestroy(pHash hashTable)
{
	//edge case
	if (hashTable == NULL)
		return FAIL;

	// destroy all
	pElementNode* indxPtr;
	for (int i = 0; i < hashTable->size; i++)
	{
		// destroy node
		indxPtr = hashTable->pFirstNode + i;
		while(*indxPtr != NULL)
		{
			// remove the first element in the node
			pElementNode searchElement = *indxPtr;
			HashRemove(hashTable, hashTable->getKey(searchElement->element));
		}
	}
	free(hashTable->pFirstNode);
	free(hashTable);
	return SUCCESS;
}