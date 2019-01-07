
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

/* static void exchange(void **item1, void **item2) {
    double temp = **(double **) item1;
    **(double **) item1 = **(double **) item2;
    **(double **) item2 = temp;
} */

static void exchange(void **item1, void **item2) {
    char *temp = *(char **) item1;
    *(char **) item1 = *(char **) item2;
    *(char **) item2 = temp;
}

static void printState(const void **ptrLo, const void **ptrHi, const void **ptrPivot) {
    void **ptrTemp;
    printf("--------- ARRAY ---------\n");
    for (ptrTemp = (void **) ptrLo; ptrTemp < (void **) ptrHi; ptrTemp++) {
        printf("%u ---> %.8f", (unsigned int) ptrTemp, **(double **) ptrTemp);
        if (ptrTemp == (void **) ptrPivot) {
            printf(" ---> PIVOT <---\n");
        } else {
            printf("\n");
        }
    }
    printf("--------- ARRAY ---------\n\n\n");
}

static int cmpDouble(const void *item1, const void *item2) {
    if (*(double *) item1 > *(double *) item2) {
        return 1;
    }
    if (*(double *) item1 < *(double *) item2) {
        return -1;
    }
    return 0;
}

static int cmpString(const void *item1, const void *item2) {
    return strcmp((char *) item1, (char *) item2);
}

static void verifySort(const void **ptrLo, const void **ptrHi, int (*cmpFunc)(const void *, const void *)) {
    for (void **ptrTemp = (void **) ptrLo; ptrTemp < (void **) (ptrHi - 1); ptrTemp++) {
        // printf("ELEMENT ---> %u ---> %s (-> %s)", (unsigned int) ptrTemp, (char *) ptrTemp, (char *) (ptrTemp + 1));
        if (cmpFunc((const void *) *ptrTemp, (const void *) *(ptrTemp + 1)) <= 0) {
            // printf(" <--- CORRECT!\n");
        } else {
            // printf("\n\t -> SORT IS NOT CORRECT!!!\n");
            return;
        }
    }
    // printf("ELEMENT ---> %u ---> %s\n", (unsigned int) (ptrHi - 1), (char *) (ptrHi - 1));
    printf("\n<--- SORT IS 100%% CORRECT --->\n");
}

static void **partition(const void **ptrLo, const void **ptrHi, int (*cmpFunc)(const void *, const void *)) {
    void **ptrI = (void **) (ptrLo + 1);
    void **ptrJ = (void **) (ptrHi - 1);
    while (1) {
        if (ptrI < (void **) ptrHi) {
            while (cmpFunc(*ptrI, *ptrLo) < 0) {
                ptrI++;
                if (ptrI >= (void **) ptrHi) {
                    break;
                }
            }
        }
        if (ptrJ >= (void **) ptrLo) {
            while (cmpFunc(*ptrJ, *ptrLo) > 0) {
                ptrJ--;
                if (ptrJ < (void **) ptrLo) {
                    break;
                }
            }
        }
        if (ptrJ < ptrI) {
            break;
        }
        exchange(ptrI++, ptrJ--);
    }
    exchange(ptrJ, (void **) ptrLo);
    return ptrJ;
}

static void quicksort(const void **ptrLo, const void **ptrHi, int (*cmpFunc)(const void *, const void *)) {
    if (ptrLo >= (ptrHi - 1)) {
        return;
    }
    void **ptrPivot = partition(ptrLo, ptrHi, cmpFunc);
    quicksort(ptrLo, (const void **) ptrPivot, cmpFunc);
    quicksort((const void **) ptrPivot + 1, ptrHi, cmpFunc);
}

/* int main(int argc, char **argv) {

    int i, num;

    FILE *file = fopen("../array_double.txt", "r");
    size_t arrayLength;
    fscanf(file, " %i", &arrayLength);
    void **array = (void **) calloc(arrayLength, sizeof(double *));
    if (array == NULL) {
        fprintf(stderr, "Memory issues...\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; ; i++) {
        double *ptrVal = (double *) malloc(sizeof(double));
        num = fscanf(file, " %lf", ptrVal);
        if (num == 0) {
            fprintf(stderr, "Wrong input!\n");
            return (EXIT_FAILURE);
        }
        if (num == EOF) {
            break;
        }
        array[i] = ptrVal;
    }
    fclose(file);

    for (i = 0; i < arrayLength; i++) {
        printf("HEAP_ARRAY ---> %u\n", (unsigned int) &array[i]);
        printf("\tHEAP_VALUE ---> %u\n", (unsigned int) array[i]);
        printf("\t\tCONTENT ---> %.8f\n\n", *(double *) array[i]);
    }
    // printf("<--- SENT ARGUMENTS --->\nptrLo ---> %u ---> %u ---> %.8f\nptrHi ---> %u ---> %u ---> %.8f\n\n", (unsigned int)((const void **) &array[0]), *(unsigned int *)((const void **) &array[0]), **(double **)((const void **) &array[0]), (unsigned int) ((const void **) &array[arrayLength - 1]), *(unsigned int *)((const void **) &array[arrayLength - 1]), **(double **)((const void **) &array[arrayLength - 1]));
    quicksort((const void **) &array[0], (const void **) &array[arrayLength], cmpDouble);
    // printState((const void **) &array[0], (const void **) &array[arrayLength], 0);
    verifySort((const void **) &array[0], (const void **) &array[arrayLength], cmpDouble);

} */
