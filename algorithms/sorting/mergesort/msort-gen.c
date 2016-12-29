/*
 *  Generic merge sort
 *  ==================
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memcpy()

/*
 *  Declarations
 */

typedef signed char (*compare_fun)(void*, void*);

void merge(void* array        ,
           size_t low         ,
           size_t mid         ,
           size_t high        ,
           size_t dataSize    ,
           compare_fun compare);

void msort(void* array        ,
           size_t low         ,
           size_t high        ,
           size_t dataSize    ,
           compare_fun compare);

// to be called by the user
void mergeSort(void* array        ,
               size_t low         ,
               size_t high        ,
               size_t dataSize    ,
               compare_fun compare);

/*
 *  The compare method has to be defined by the user for
 *  all the types they want to call mergeSort() on.
 */
signed char compareInt(void* t1, void* t2);
signed char compareFloat(void* t1, void* t2);
signed char compareChar(void* t1, void* t2);

/* Helpers */
void printIntArray(void* array, size_t low, size_t high);
void printFloatArray(void* array, size_t low, size_t high);
void printCharArray(void* array, size_t low, size_t high);

int main()
{
    // Demonstrate merge sort for various cases
    
    int size = 10;
    int iarr[] = { 90, 80, 10, 20, 50, 40, 60, 30, 70, 100 };
    float farr[] = { 9.0, 8.0, 1.0, 2.0, 5.0, 4.0, 6.0, 3.0, 7.0, 10.0 };
    char carr[] = { 'x', 'a', 'b', 'f', 'p', 'e', 'o', 'z', 'c', 'd' };

    printf("Test : Generic mergesort :-\n\n");
    printf("With integer array:-\n");
    printIntArray(iarr, 0, size - 1);
    mergeSort(iarr, 0, size-1, sizeof(int), compareInt);
    printIntArray(iarr, 0, size - 1);

    printf("\nWith floating point array:-\n");
    printFloatArray(farr, 0, size - 1);
    mergeSort(farr, 0, size-1, sizeof(float), compareFloat);
    printFloatArray(farr, 0, size - 1);
    
    printf("\nWith character array:-\n");
    printCharArray(carr, 0, size - 1);
    mergeSort(carr, 0, size-1, sizeof(char), compareChar);
    printCharArray(carr, 0, size - 1);
    
    return 0;
}

/*
 *  Definitions
 */

void merge(void* array        ,
           size_t low         ,
           size_t mid         ,
           size_t high        ,
           size_t dataSize    ,
           compare_fun compare)
{
    void* aux = malloc((high - low + 1) * dataSize);

    size_t i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high)
    {
        if (compare(array + i * dataSize, array + j * dataSize) < 0)
            memcpy(aux + k++ * dataSize, array + i++ * dataSize, dataSize);
        else if (compare(array + i * dataSize, array + j * dataSize) > 0)
            memcpy(aux + k++ * dataSize, array + j++ * dataSize, dataSize);
        else
        {
            memcpy(aux + k++ * dataSize, array + i++ * dataSize, dataSize);
            memcpy(aux + k++ * dataSize, array + j++ * dataSize, dataSize);
        }
    }

    while (i <= mid)
        memcpy(aux + k++ * dataSize, array + i++ * dataSize, dataSize);

    while (j <= high)
        memcpy(aux + k++ * dataSize, array + j++ * dataSize, dataSize);

    i = low;
    k = 0;

    while (i <= high)
        memcpy(array + i++ * dataSize, aux + k++ * dataSize, dataSize);

    free(aux);
}

void msort(void* array, size_t low, size_t high, size_t dataSize, compare_fun compare)
{
    if (low < high)
    {
        size_t mid = (low + high) / 2;

        msort(array, low, mid, dataSize, compare);
        msort(array, mid + 1, high, dataSize, compare);
        merge(array, low, mid, high, dataSize, compare);
    }

    return;
}

void mergeSort(void* array, size_t low, size_t high, size_t dataSize, compare_fun compare)
{
    msort(array, low, high, dataSize, compare);
}

signed char compareInt(void* t1, void* t2)
{
    int _t1 = *(int*)t1;
    int _t2 = *(int*)t2;

    if (_t1 < _t2)
        return -1;
    else if (_t1 > _t2)
        return 1;
    else
        return 0;
}

signed char compareFloat(void* t1, void* t2)
{
    float _t1 = *(float*)t1;
    float _t2 = *(float*)t2;

    if (_t1 < _t2)
        return -1;
    else if (_t1 > _t2)
        return 1;
    else
        return 0;
}

signed char compareChar(void* t1, void* t2)
{
    int _t1 = *(char*)t1;
    int _t2 = *(char*)t2;

    if (_t1 < _t2)
        return -1;
    else if (_t1 > _t2)
        return 1;
    else
        return 0;
}

void printIntArray(void* array, size_t low, size_t high)
{
    for (size_t i = low; i <= high; i++)
        printf("%d ", ((int*)array)[i]);
    printf("\n");
}

void printFloatArray(void* array, size_t low, size_t high)
{
    for (size_t i = low; i <= high; i++)
        printf("%.1f  ", ((float*)array)[i]);
    printf("\n");
}

void printCharArray(void* array, size_t low, size_t high)
{
    for (size_t i = low; i <= high; i++)
        printf("%c ", ((char*)array)[i]);
    printf("\n");
}
