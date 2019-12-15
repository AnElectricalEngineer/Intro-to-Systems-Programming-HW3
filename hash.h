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

// Add your declarations here...

#endif
