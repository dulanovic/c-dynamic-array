
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dynamic_array.h"

static const size_t MIN_ARRAY_LENGTH = 2;

struct DynamicArray {
    size_t lastIndex;
    size_t length;
    const void **array;
};

#ifndef NDEBUG

static int dnar_isValid(DynArray array) {
    if (array->lastIndex > array->length) {
        printf("array->lastIndex > array->length");
        return 0;
    }
    if (array->length < MIN_ARRAY_LENGTH) {
        printf("array->length < MIN_ARRAY_LENGTH");
        return 0;
    }
    if (array->array == NULL) {
        printf("array->array == NULL");
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
    dnar_print(array);
    newArray = (const void **) realloc(array->array, newLength * sizeof(void *));
    if (newArray == NULL) {
        printf("\nnewArray == NULL\n");
        return 0;
    }
    array->array = newArray;
    array->length = newLength;
    printf("\n\n--- SUCCESSFULL MEMORY REALLOCATION(INCREASE)!!! ---\n\n");
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
    return (void *) (array->array + index);
}

void *dnar_set(DynArray array, size_t index, const void *newItem) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(index >= 0);
    assert(index < array->lastIndex);
    assert(newItem != NULL);
    void *oldElement = (void *) (array->array + index);
    printf("\noldElement ---> %u\n", oldElement);
    *(array->array + index) = newItem;
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
    *(array->array + array->lastIndex) = item;
    array->lastIndex++;
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
    int i;
    for (i = (int) array->lastIndex; i >= (int) index; i--) {
        *(array->array + i) = *(array->array + i - 1);
    }
    *(array->array + index) = item;
    array->lastIndex++;
    return 1;
}

void *dnar_removeAt(DynArray array, size_t index) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(index >= 0);
    assert(index < array->lastIndex);
    void *removed = array->array + index;
    int i;
    for (i = (int) index + 1; i < (int) array->lastIndex - 1; i++) {
        *(array->array + i - 1) = *(array->array + i);
    }
    array->lastIndex--;
    return removed;
}

void dnar_toArray(DynArray array, void **arrayCopy) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(arrayCopy != NULL);
    arrayCopy = (void**) calloc(array->lastIndex, sizeof(void *));
    if (arrayCopy == NULL) {
        fprintf(stderr, "Memory for the additional array could not be allocated!");
        return;
    }
    int i;
    for (i = 0; i < array->lastIndex; i++) {
        *(arrayCopy + i) = (void *) *(array->array + i);
    }
}

void dnar_map(DynArray array, void (*func)(void *item, void *extra), const void *extra) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(func != NULL);
    for (int i = 0; i < array->lastIndex; i++) {
        (*func)(array->array + i, (void*) extra);
    }
}

void dnar_sort(DynArray array, int (*compareFunc)(const void *item1, const void *item2)) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(compareFunc != NULL);
    qsort(array, array->lastIndex, sizeof(double), compareFunc);
    dnar_print(array);
}

int dnar_search(DynArray array, void *searchCriteria, size_t *foundIndex, int (*compareFunc)(const void *item1, const void *item2)) {
    assert(array != NULL);
    assert(dnar_isValid(array));
    assert(searchCriteria != NULL);
    assert(foundIndex != NULL);
    assert(compareFunc != NULL);
    int i, same;
    for (i = 0; i < (int) array->lastIndex; i++) {
        same = (*compareFunc)((array->array + i), searchCriteria);
        if (!same) {
            *foundIndex = (size_t) i;
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
    while (lo >= hi) {
        cmp = (*compareFunc)(*(array->array + mid), searchCriteria);
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
    int i;
    printf("\n\n--------- DYNAMIC ARRAY ---------\nArray size ---> %i\nNo. of items ---> %i\n\n", (int) array->length, (int) array->lastIndex);
    for (i = 0; i < (int) array->lastIndex; i++) {
        printf("Item %i\nHeap address ---> %u\n", i, (unsigned int) (array->array + i));
        printf("\tStack address ---> %u\n", *(unsigned int *)(array->array + i));
        printf("\t\tValue ---> %.8f\n", **(double **) (array->array + i));
    }
    for (; i < (int) array->length; i++) {
        printf("Item %i\nHeap address ---> %u\n", i, (unsigned int) (array->array + i));
        printf("\tStack address ---> %u\n", 0);
        printf("\t\tValue ---> %.8f (NO VALUE ASSIGNED!)\n", 0.0);
    }
    printf("\n\n");
}

int main(int argc, char **argv) {

    size_t length = 2;
    int i;
    double d1 = 0.05;
    double d2 = 2.378;
    double d3 = 8.19;
    double d4 = 0.3656;
    double d5 = 4.11;
    double d6 = 2.008;
    double d7 = 3.39;
    double d8 = 1.97;
    double d9 = 5.526;
    void *ptr;
    DynArray array = dnar_new(length);
    dnar_print(array);
    dnar_add(array, &d1);
    dnar_add(array, &d2);
    dnar_add(array, &d3);
    dnar_add(array, &d4);
    dnar_print(array);
    ptr = dnar_get(array, 4);
    printf("ADDRESS_HEAP ---> %u\n\tADDRESS_STACK ---> %u\n\t\tCONTENT ---> %.8f\n", (unsigned int) ptr, *(unsigned int *) ptr, **(double **) ptr);
    /* ptr = dnar_set(array, 0, &d4);
    printf("ptr ---> %u\n\t*ptr ---> %u\n\t\t**ptr ---> %.8f\n", (unsigned int) ptr, *(unsigned int *)ptr, **(double **) ptr); */

    return(EXIT_SUCCESS);

}
