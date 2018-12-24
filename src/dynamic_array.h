
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

typedef struct DynamicArray *DynArray;

DynArray dnar_new(size_t length);
void dnar_free(DynArray array);
size_t dnar_getLength(DynArray array);
void *dnar_get(DynArray array, size_t index);
void *dnar_set(DynArray array, size_t index, const void *newItem);
int dnar_add(DynArray array, const void *item);
int dnar_addAt(DynArray array, size_t index, const void *item);
void *dnar_removeAt(DynArray array, size_t index);
void dnar_toArray(DynArray array, void **arrayCopy);
void dnar_map(DynArray array, void (*func)(void *item, void *extra), const void *extra);
void dnar_sort(DynArray array, int (*compareFunc)(const void *item1, const void *item2));
int dnar_search(DynArray array, void *searchCriteria, size_t *foundIndex, int (*compareFunc)(const void *item1, const void *item2));
int dnar_bsearch(DynArray array, void *searchCriteria, size_t *foundIndex, int (*compareFunc)(const void *item1, const void *item2));
void dnar_print(DynArray array);

#endif
