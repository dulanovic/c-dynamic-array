
#include <assert.h>
#include "dynamic_array.h"
#include "quicksort_p.c"
// #include "test_struct.c"

static const size_t MIN_ARRAY_LENGTH = 2;

struct DynamicArray {
    size_t lastIndex;
    size_t length;
    const void **array;
};

#ifndef NDEBUG

static int dnar_isValid(DynArray array) {
    if (array->lastIndex > array->length) {
        return 0;
    }
    if (array->length < MIN_ARRAY_LENGTH) {
        return 0;
    }
    if (array->array == NULL) {
        return 0;
    }
    return 1;
}

#endif

static int dnar_increase(DynArray array) {
    assert(array != NULL);
    const size_t GROWTH_FACTOR = 2;
    size_t newLength;
    const void **newArray;
    newLength = GROWTH_FACTOR * array->length;
    // dnar_print(array);
    newArray = (const void **) realloc(array->array, newLength * sizeof(void *));
    if (newArray == NULL) {
        return 0;
    }
    array->array = newArray;
    array->length = newLength;
    // printf("\n\n--- SUCCESSFULL MEMORY REALLOCATION(INCREASE)!!! ---\n\n");
    return 1;
}

DynArray dnar_new(size_t length) {
    assert(length >= 0);
    DynArray array = (struct DynamicArray *) malloc(sizeof(struct DynamicArray));
    if (array == NULL) {
        return NULL;
    }
    array->lastIndex = 0;
    if (length > MIN_ARRAY_LENGTH) {
        array->length = length;
    } else {
        array->length = MIN_ARRAY_LENGTH;
    }
    array->array = (const void **) calloc(array->length, sizeof(void *));
    if (array->array == NULL) {
        free(array);
        return NULL;
    }
    return array;
}

void dnar_free(DynArray array) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    free(array->array);
    free(array);
}

size_t dnar_getLength(DynArray array) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    return array->lastIndex;
}

void *dnar_get(DynArray array, size_t index) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(index >= 0);
    assert(index < array->lastIndex);
    return (void *) (array->array[index]);
}

void *dnar_set(DynArray array, size_t index, const void *newItem) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(index >= 0);
    assert(index < array->lastIndex);
    assert(newItem != NULL);
    void *oldElement = (void *) (array->array[index]);
    array->array[index] = newItem;
    assert(dnar_isValid(array));
    return oldElement;
}

int dnar_add(DynArray array, const void *item) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(item != NULL);
    int errorCheck;
    if (array->lastIndex == array->length) {
        errorCheck = dnar_increase(array);
        if (!errorCheck) {
            return 0;
        }
    }
    array->array[array->lastIndex] = item;
    array->lastIndex++;
    assert(dnar_isValid(array));
    return 1;
}

int dnar_addAt(DynArray array, size_t index, const void *item) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(index >= 0);
    assert(index < array->lastIndex);
    assert(item != NULL);
    int errorCheck;
    if (array->lastIndex == array->length) {
        errorCheck = dnar_increase(array);
        if (!errorCheck) {
            return 0;
        }
    }
    size_t i;
    for (i = array->lastIndex; i > index; i--) {
        array->array[i] = array->array[i - 1];
    }
    array->array[index] = item;
    array->lastIndex++;
    assert(dnar_isValid(array));
    return 1;
}

void *dnar_removeAt(DynArray array, size_t index) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(index >= 0);
    assert(index < array->lastIndex);
    void *removed = (void *) array->array[index];
    size_t i;
    for (i = index + 1; i < (array->lastIndex); i++) {
        array->array[i - 1] = array->array[i];
    }
    array->lastIndex--;
    assert(dnar_isValid(array));
    return removed;
}

void dnar_toArray(DynArray array, void **arrayCopy) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(arrayCopy != NULL);
    for (size_t i = 0; i < array->lastIndex; i++) {
        arrayCopy[i] = (void *) (array->array[i]);
    }
}

void dnar_map(DynArray array, void (*func)(void *item, void *extra), const void *extra) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(func != NULL);
    for (size_t i = 0; i < array->lastIndex; i++) {
        (*func)((void *) (array->array[i]), (void *) extra);
    }
}

void dnar_sort(DynArray array, int (*compareFunc)(const void *item1, const void *item2)) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(compareFunc != NULL);
    quicksort(&array->array[0], &array->array[array->lastIndex], compareFunc);
    verifySort(&array->array[0], &array->array[array->lastIndex], compareFunc);
    // dnar_print(array);
}

int dnar_search(DynArray array, void *searchCriteria, size_t *foundIndex, int (*cmpFunc)(const void *item1, const void *item2)) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(searchCriteria != NULL);
    assert(foundIndex != NULL);
    assert(cmpFunc != NULL);
    size_t i;
    int found;
    for (i = 0; i < array->lastIndex; i++) {
        found = (*cmpFunc)(array->array[i], searchCriteria);
        if (!found) {
            *foundIndex = i;
            return 1;
        }
    }
    return 0;
}

int dnar_bsearch(DynArray array, void *searchCriteria, size_t *foundIndex, int (*compareFunc)(const void *item1, const void *item2)) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(searchCriteria != NULL);
    assert(foundIndex != NULL);
    assert(compareFunc != NULL);
    dnar_sort(array, compareFunc);
    int lo = 0;
    int hi = (int) array->lastIndex;
    int mid = (lo + hi) / 2;
    int cmp;
    while (lo <= hi) {
        cmp = (*compareFunc)(array->array[mid], searchCriteria);
        switch (cmp) {
            case 0: {
                *foundIndex = (size_t) mid;
                return 1;
            }
            case -1: {
                lo = mid + 1;
                break;
            }
            case 1: {
                hi = mid - 1;
            }
        }
        mid = (lo + hi) / 2;
    }
    return 0;
}

void dnar_print(DynArray array) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    size_t i;
    struct TestStruct *das;
    printf("\n\n--------- DYNAMIC ARRAY ---------\nArray size ---> %i\nNo. of items ---> %i\n\n", array->length, array->lastIndex);
    for (i = 0; i < array->lastIndex; i++) {
        printf("Item %i\nHeap address ---> %u\n", i, (unsigned int) (array->array + i));
        printf("\tStack address ---> %u\n", (unsigned int)(array->array[i]));
        das = (struct TestStruct *) array->array[i];
        printf("\t\tDoubleVal ---> %.8f\n\t\tStringVal ---> %s\n", das->doubleAtt, das->stringAtt);
    }
    for (; i < array->length; i++) {
        printf("Item %i\nHeap address ---> %u\n", i, (unsigned int) (array->array[i]));
        printf("\tStack address ---> %i\n", 0);
        printf("\t\tValue ---> %s (NO VALUE ASSIGNED!)\n", "NULL");
    }
    printf("\n\n");
}
