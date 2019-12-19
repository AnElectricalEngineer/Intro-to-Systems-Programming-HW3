#ifndef _HASH_H_
#define _HASH_H_

typedef enum {FAIL = 0, SUCCESS} Result;
typedef enum {SAME = 0, DIFFERENT} CompResult;

typedef struct _Hash *pHash;

typedef void* pElement;
typedef void* pKey;

typedef int (*HashFunc) (pKey key, int size);
typedef Result (*PrintFunc) (pElement element);
typedef CompResult (*CompareFunc) (pKey key1, pKey key2);
typedef pKey (*GetKeyFunc) (pElement element);
typedef void (*DestroyFunc)(pElement element);

/*Interface Function Declarations*/

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
pHash HashCreate(unsigned int, HashFunc, PrintFunc, CompareFunc, GetKeyFunc, DestroyFunc);
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
Result HashAdd(pHash, pElement);
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
pElement HashFind(pHash, pKey);
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
Result HashRemove(pHash, pKey);
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
Result HashPrint(pHash);
//************************************************************************************* 
// Function name : HashDestroy
//
// Description : destroys the entire hash table and frees all dynamically allocated
//				 memory
//
// Parameters:  1) pointer to hash table
//
// Return value : SUCCESS if hash table destroyed successfully, FAIL otherwise
//*************************************************************************************
Result HashDestroy(pHash);
#endif
