
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

static void exchange(void **item1, void **item2) {
    // printf("\n\tEXCHANGE ---> %u (%.8f) and %u (%.8f)\n\n", (unsigned int) item1, **(double **) item1, (unsigned int) item2, **(double **) item2);
    double temp = **(double **) item1;
    **(double **) item1 = **(double **) item2;
    **(double **) item2 = temp;
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

/* static int cmpDouble(const void **item1, const void **item2) {
    // printf("\n\tCOMPARE ---> %u (%.8f) and %u (%.8f)\n\n", (unsigned int) item1, **(double **) item1, (unsigned int) item2, **(double **) item2);
    if (**(double **) item1 > **(double **) item2) {
        return 1;
    }
    if (**(double **) item1 < **(double **) item2) {
        return -1;
    }
    return 0;
} */

static int cmpDouble(const void *item1, const void *item2) {
    if (*(double *) item1 > *(double *) item2) {
        return 1;
    }
    if (*(double *) item1 < *(double *) item2) {
        return -1;
    }
    return 0;
}

static void verifySort(const void **ptrLo, const void **ptrHi, int (*cmpFunc)(const void *, const void *)) {
    for (void **ptrTemp = (void **) ptrLo; ptrTemp < (void **) (ptrHi - 1); ptrTemp++) {
        printf("ELEMENT ---> %u ---> %.8f (-> %.8f)", (unsigned int) ptrTemp, **(double **) ptrTemp, **(double **) (ptrTemp + 1));
        if (cmpFunc((const void *) *ptrTemp, (const void *) *(ptrTemp + 1)) <= 0) {
            printf(" <--- CORRECT!\n");
        } else {
            printf("\n\t -> SORT IS NOT CORRECT!!!\n");
            return;
        }
    }
    printf("\n<--- SORT IS 100%% CORRECT --->\n");
}

static void **partition(const void **ptrLo, const void **ptrHi, int (*cmpFunc)(const void *, const void *)) {
    void **ptrI = (void **) (ptrLo + 1);
    void **ptrJ = (void **) (ptrHi - 1);

    /* printf("\n<<<----------------------------------------------------->>>\n");
    printf("<<<------------------ PARTITION BEGIN ------------------>>>\n");
    printf("<<<----------------------------------------------------->>>\n\n");
    printState(ptrLo, ptrHi, ptrLo);
    printf("\nptrLo\tptrI\tptrJ\tptrHi\n%u %u %u %u\n%.8f %.8f %.8f\n", (unsigned int) ptrLo, (unsigned int) ptrI, (unsigned int ) ptrJ, (unsigned int) ptrHi, **(double **) ptrLo, **(double **) ptrI, **(double **) ptrJ); */

    while (1) {

        /* printf("\n------------------ ITERATION BEGIN ------------------\n");
        printf("\nptrLo\tptrI\tptrJ\tptrHi\n%u %u %u %u\n\n", (unsigned int) ptrLo, (unsigned int) ptrI,(unsigned int) ptrJ, (unsigned int) ptrHi);
        printf("cmpFunc(*ptrI -> %.8f, *ptrLo -> %.8f) |---> %i\n", **(double **) ptrI, **(double **) ptrLo, cmpFunc(*(const void **) ptrI, *ptrLo));
        printf("<>=(ptrI -> %u, ptrHi -> %u) |---> %s\n", (unsigned int) ptrI, (unsigned int) ptrHi, (ptrI < (void **) ptrHi) ? ">>> ptrI IS LESS <<<" : "<<< ptrI IS GREATER >>>"); */

        if (ptrI < (void **) ptrHi) {
            while (cmpFunc(*ptrI, *ptrLo) < 0) {

                // printf("\tptrI++\n");

                ptrI++;
                if (ptrI >= (void **) ptrHi) {
                    break;
                }

                /* printf("\t\tHERE, PROGRAM MIGHT STOP, BECAUSE OF THIS VALUE ---> %u", (unsigned int) ptrI);
                printf(" ---> %u", *(unsigned int *) ptrI);
                printf(" ---> %.8f!!!\n", **(double **) ptrI); */

            }
        }
        // printf("ptrI - STOP! (%u -> %.8f)\n\n", (unsigned int) ptrI, **(double **) ptrI);

        /* printf("ptrI - STOP! (%u)\n\n",(unsigned int) ptrI);
        printf("cmpFunc(*ptrJ -> %.8f, *ptrLo -> %.8f) |---> %i\n", **(double **) ptrJ, **(double **) ptrLo, cmpFunc(*(const void **) ptrJ, *ptrLo));
        printf("<>=(ptrJ -> %u, ptrLo -> %u) |---> %s\n", (unsigned int) ptrJ, (unsigned int) ptrLo, (ptrJ >= (void **) ptrLo) ? "<<< ptrJ IS GREATER >>>" : ">>> ptrJ IS LESS <<<"); */

        if (ptrJ >= (void **) ptrLo) {
            while (cmpFunc(*ptrJ, *ptrLo) > 0) {

                // printf("\tptrJ--\n");

                ptrJ--;
                if (ptrJ < (void **) ptrLo) {
                    break;
                }

                /* printf("\t\tHERE, PROGRAM MIGHT STOP, BECAUSE OF THIS VALUE ---> %u", (unsigned int) ptrJ);
                printf(" ---> %u", *(unsigned int *) ptrJ);
                printf(" ---> %.8f!!!\n", **(double **) ptrJ); */

            }
        }
        // printf("ptrJ - STOP! (%u -> %.8f)\n\n", (unsigned int) ptrJ, **(double **) ptrJ);

        /* printf("ptrJ - STOP! (%u)\n\n", (unsigned int) ptrJ);
        printf("\n------------------ ITERATION END ------------------\n"); */

        if (ptrJ < ptrI) {
            break;
        }
        exchange(ptrI++, ptrJ--);

        // printState(ptrLo, ptrHi, ptrLo);

    }
    exchange(ptrJ, (void **) ptrLo);

    /* printf("\n<<<--------------------------------------------------->>>\n");
    printf("<<<------------------ PARTITION END ------------------>>>\n");
    printf("<<<--------------------------------------------------->>>\n\n");
    printState(ptrLo, ptrHi, (const void **) ptrJ); */

    return ptrJ;
}

static void quicksort(const void **ptrLo, const void **ptrHi, int (*cmpFunc)(const void *, const void *)) {
    // printf("<--- RECEIVED ARGUMENTS --->\nptrLo ---> %u ---> %u ---> %.8f\nptrHi ---> %u ---> %u ---> %.8f\n\n", (unsigned int) ptrLo, *(unsigned int *) ptrLo, **(double **) ptrLo, (unsigned int) (ptrHi - 1), *(unsigned int *) (ptrHi - 1), **(double **) (ptrHi - 1));
    // printf("<--- BOUNDARIES --->\nptrLo ---> %u\nptrHi ---> %u\n", (unsigned int) ptrLo, (unsigned int) ptrHi);
    if (ptrLo >= (ptrHi - 1)) {
        // printf("\tBRANCH OVER!!! --->>> ptrLo >= ptrHi (%u >= %u)\n\n\n", (unsigned int) ptrLo, (unsigned int) (ptrHi - 1));
        return;
    }
    void **ptrPivot = partition(ptrLo, ptrHi, cmpFunc);
    // printf("PIVOT ---> %u\n\n", (unsigned int) ptrPivot);
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
