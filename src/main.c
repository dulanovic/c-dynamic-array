
#include <stdlib.h>
#include <stdio.h>
#include "dynamic_array.h"

static int comparatorDouble(void *item1, void *item2) {
    if (*(double*) item1 > *(double*) item2) {
        return 1;
    } else if (*(double*) item1 < *(double*) item2) {
        return -1;
    }
    return 0;
}

/* int main(int argc, char **argv) {

    DynArray array = dnar_new(3);
    dnar_print(array);
    double d1 = 0.05;
    double d2 = 2.378;
    double d3 = 8.19;
    double d4 = 0.3656;
    double d5 = 4.11;
    double d6 = 2.008;
    double d7 = 3.39;
    double d8 = 1.97;
    void *ptr;
    dnar_add(array, &d1);
    dnar_add(array, &d2);
    dnar_add(array, &d3);
    dnar_add(array, &d4);
    dnar_print(array);
    printf("getLength ---> %i\n", (int) dnar_getLength(array));
    ptr = dnar_get(array, 0);
    printf("\ndnar_get() ---> %g, %u (Address ---> %u)\n", **(double **) ptr, (double*) ptr, ptr);
    size_t *foundIndex;
    int i = dnar_search(array, &d4, foundIndex, (int(*)(const void *, const void*)) comparatorDouble);
    printf("i ---> %i\n*foundIndex ---> %i\n", i, (int) *foundIndex);
    dnar_sort(array, (int(*)(const void*, const void*)) comparatorDouble);

    return(EXIT_SUCCESS);

} */
