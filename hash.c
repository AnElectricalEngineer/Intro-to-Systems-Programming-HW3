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

	// *************************************************
	int size;
	//int numElement; // need to add this to check that we dont overflow
	//**************************************************
} Hash, *pHash;

pHash HashCreate(int size, HashFunc func, PrintFunc print, CompareFunc comp, GetKeyFunc getKey, DestroyFunc destroy)
{
	// create hash table
	pHash hashTable = (pHash)malloc(sizeof(Hash));
	if (hashTable == NULL)
	{
		fprintf(stderr, "Error Allocating Memory");
		exit(-1);
		// need to add "Exit" from the program
	}

	// create the hash and set all the address to NULL
	hashTable->pFirstNode = (pElementNode*)malloc(size*sizeof(pElementNode));
	if (hashTable->pFirstNode == NULL)
	{
		fprintf(stderr, "Error Allocating Memory");
		free(hashTable);
		exit(-1);
		// need to add "Exit" from the program
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

	// ints for overflow
	hashTable->size = size;
	//hashTable->numElement = 0;
	
	return hashTable;
}

Result HashAdd(pHash hashTable, pElement element)
{
	// edge case
	if (hashTable == NULL || element == NULL || HashFind(hashTable, hashTable->getKey(element)) != NULL)
		return FAIL;

	// create node
	pElementNode pNode = (pElementNode)malloc(sizeof(ElementNode));
	if (pNode == NULL)
	{
		fprintf(stderr, "Error Allocating Memory");
		exit(-1);
		// need to add "Exit" from the program
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

	// the node is not the first one, so there is at lest 2 element
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
		//**********************************************************************
		// make sure not to print "\n" when there is no element in the hash
		//**********************************************************************
		/*if(*indxPtr != NULL)
			printf("\n");*/
	}
	return SUCCESS;
}

//Result HashPrint(pHash hashTable) //josh
//{
//	//edge case
//	if (hashTable == NULL)
//		return FAIL;
//
//	 //print
//	pElementNode* indxPtr = hashTable->pFirstNode;
//	for (int i = 0; i < hashTable->size; i++)
//	{
//		if (*(indxPtr+i) == NULL)
//			continue;
//		pElementNode j = *(indxPtr + i);
//		while(j != NULL)
//		{
//			hashTable->print(j);
//			j = j->next;
//		}
//	}
//	return SUCCESS;
//}

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