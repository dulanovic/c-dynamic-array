
#include <stdlib.h>
#include <stdio.h>
#include "dynamic_array.h"
#include "quicksort_p.c"

static void printString(void *pvItem, void *pvFormat) {
    printf((char *) pvFormat, (char *) pvItem);
}

int main(int argc, char **argv) {

    size_t length = 2;
    int i, num, errorCheck;
    size_t j;
    void *ptr;
    void *searchCriteria;
    size_t *foundIndex = &length;

    FILE *file = fopen("../array_values_string.txt", "r");
    size_t arrayLength;
    size_t maxWordLength;
    fscanf(file, "%i, %i\n", &arrayLength, &maxWordLength);
    DynArray array = dnar_new(arrayLength);
    if (array == NULL) {
        fprintf(stderr, "Memory issues [array]...\n");
        exit(EXIT_FAILURE);
    }
    while (1) {
        char *ptrVal = (char *) malloc((maxWordLength + 1) * sizeof(char));
        if (ptrVal == NULL) {
            fprintf(stderr, "Memory issues [ptrVal]...\n");
            exit(EXIT_FAILURE);
        }
        ptrVal = fgets(ptrVal, (int) (maxWordLength + 1), file);
        if (ptrVal == NULL) {
            break;
        }
        if (ptrVal[strlen(ptrVal) - 1] == 10) {
            ptrVal[strlen(ptrVal) - 1] = 0;
        } else {
            fscanf(file, "\n");
        }
        dnar_add(array, ptrVal);
    }
    fclose(file);
    // dnar_sort(array, cmpString);

    errorCheck = dnar_search(array, "bmonskfmigb", foundIndex, cmpString);
    if (errorCheck) {
        printf("\n\nElement found at index %i\n", (int) *foundIndex);
        ptr = dnar_get(array, *foundIndex);
        printf("ELEMENT ---> %u -> %s\n", (unsigned int) ptr, (char *) ptr);
    } else {
        printf("\n\nELEMENT NOT FOUND BY PROVIDED CRITERIA!!!\n");
    }
    dnar_free(array);

    /* FILE *file = fopen("../array_values_double.txt", "r");
    size_t arrayLength;
    fscanf(file, " %i", &arrayLength);
    DynArray array = dnar_new(arrayLength);
    if (array == NULL) {
        fprintf(stderr, "Memory issues...\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; ; i++) {
        double *ptrVal = (double *) malloc(sizeof(double));
        num = fscanf(file, " %lf\n", ptrVal);
        if (num == 0) {
            fprintf(stderr, "Wrong input!\n");
            return(EXIT_FAILURE);
        }
        if (num == EOF) {
            break;
        }
        dnar_add(array, ptrVal);
    }
    fclose(file);

    double criteria = 0.45475141;
    searchCriteria = &criteria;
    errorCheck = dnar_bsearch(array, searchCriteria, foundIndex, cmpDouble);
    if (errorCheck) {
        printf("\n\nElement found at index %i\n", (int) *foundIndex);
        ptr = dnar_get(array, *foundIndex);
        printf("ELEMENT ---> %u -> %.8f\n", (unsigned int) ptr, *(double *) ptr);
    } else {
        printf("\n\nELEMENT NOT FOUND BY PROVIDED CRITERIA!!!\n");
    }
    dnar_free(array); */

    /* DynArray oDynArray;
    size_t uLength;
    char **ppcArray;
    size_t u;
    char *pcElement;
    size_t uIndex = 0;
    int iFound;

    printf("<<<--------- Demonstrate dnar_new() --------->>>\n\n");
    oDynArray = dnar_new(0);
    if (oDynArray == NULL) exit(EXIT_FAILURE);

    printf("<<<--------- Demonstrate dnar_add() --------->>>\n\n");
    if (!dnar_add(oDynArray, "Ruth")) exit(EXIT_FAILURE);
    if (!dnar_add(oDynArray, "Gehrig")) exit(EXIT_FAILURE);
    if (!dnar_add(oDynArray, "Mantle")) exit(EXIT_FAILURE);
    if (!dnar_add(oDynArray, "Jeter")) exit(EXIT_FAILURE);

    printf("<<<--------- Demonstrate dnar_getLength() --------->>>\n\n");
    printf("-----------------------------------------------------\n");
    uLength = dnar_getLength(oDynArray);
    printf("DynArray length:  %i\n\n\n", (int) uLength);

    printf("<<<--------- Demonstrate dnar_get() --------->>>\n\n");
    printf("-----------------------------------------------------\n");
    printf("This output should list 4 elements\n");
    printf("-----------------------------------------------------\n");
    uLength = dnar_getLength(oDynArray);
    for (u = 0; u < uLength; u++) {
        printf("%s\n", (char*) dnar_get(oDynArray, u));
    }
    printf("\n\n");

    printf("<<<--------- Demonstrate dnar_set() --------->>>\n\n");
    printf("-----------------------------------------------------\n");
    printf("This output should list 4 elements\n");
    printf("-----------------------------------------------------\n");
    dnar_set(oDynArray, 2, "Berra");
    uLength = dnar_getLength(oDynArray);
    for (u = 0; u < uLength; u++) {
        printf("%s\n", (char *) dnar_get(oDynArray, u));
    }
    printf("\n\n");

    printf("<<<--------- Demonstrate dnar_addAt() --------->>>\n\n");
    printf("-----------------------------------------------------\n");
    printf("This output should list 5 elements\n");
    printf("-----------------------------------------------------\n");
    if (!dnar_addAt(oDynArray, 1, "Maris")) {
        exit(EXIT_FAILURE);
    }
    uLength = dnar_getLength(oDynArray);
    for (u = 0; u < uLength; u++) {
        printf("%s\n", (char *) dnar_get(oDynArray, u));
    }
    printf("\n\n");

    printf("<<<--------- Demonstrate dnar_removeAt() --------->>>\n\n");
    printf("-----------------------------------------------------\n");
    printf("This output should list 4 elements\n");
    printf("-----------------------------------------------------\n");
    pcElement = (char *) dnar_removeAt(oDynArray, 1);
    uLength = dnar_getLength(oDynArray);
    for (u = 0; u < uLength; u++) {
        printf("%s\n", (char *) dnar_get(oDynArray, u));
    }
    printf("Removed element: %s\n\n\n", pcElement);

    printf("<<<--------- Demonstrate dnar_toArray() --------->>>\n\n");
    printf("-----------------------------------------------------\n");
    printf("This output should list 4 elements\n");
    printf("-----------------------------------------------------\n");
    uLength = dnar_getLength(oDynArray);
    ppcArray = (char **) calloc((size_t) uLength, sizeof(char *));
    if (ppcArray == NULL) {
        exit(EXIT_FAILURE);
    }
    dnar_toArray(oDynArray, (void **) ppcArray);
    for (u = 0; u < uLength; u++) {
        printf("%s\n", ppcArray[u]);
    }
    printf("\n\n");
    free(ppcArray);

    printf("<<<--------- Demonstrate dnar_map() --------->>>\n\n");
    printf("-----------------------------------------------------\n");
    printf("This output should list 4 elements\n");
    printf("-----------------------------------------------------\n");
    dnar_map(oDynArray, printString, "%s\n");
    printf("\n\n");

    printf("<<<--------- Demonstrate dnar_sort() --------->>>\n\n");
    printf("-----------------------------------------------------\n");
    printf("This output should list 4 elements in ascending order\n");
    printf("-----------------------------------------------------\n");
    dnar_sort(oDynArray, cmpString);
    dnar_map(oDynArray, printString, "%s\n");
    printf("\n\n");

    printf("<<<--------- Demonstrate dnar_search() --------->>>\n\n");
    printf("-----------------------------------------------------\n");
    printf("This output should list 1 element\n");
    printf("-----------------------------------------------------\n");
    iFound = dnar_search(oDynArray, "Ruth", &uIndex, cmpString);
    if (iFound) {
        printf("%s\n\n\n", (char *) dnar_get(oDynArray, uIndex));
    }

    printf("<<<--------- Demonstrate dnar_bsearch() --------->>>\n\n");
    printf("-----------------------------------------------------\n");
    printf("This output should list 1 element\n");
    printf("-----------------------------------------------------\n");
    iFound = dnar_bsearch(oDynArray, "Ruth", &uIndex, cmpString);
    if (iFound) {
        printf("%s\n", (char *) dnar_get(oDynArray, uIndex));
    }

    dnar_free(oDynArray); */

    return(EXIT_SUCCESS);

}