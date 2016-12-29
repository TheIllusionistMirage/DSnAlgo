/*
 *    Insertion Sort
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// generic insertion sort
void isort(void* array, size_t num, size_t size, int (*comp)(void* a, void* b));

// compare and print function for int, float and char arrays
int compareInt(void* t1, void* t2);
int compareFloat(void* t1, void* t2);
int compareChar(void* t1, void* t2);

void printIntArray(int* array, size_t num);
void printFloatArray(float* array, size_t num);
void printCharArray(char* array, size_t num);

int main(int argc, char* argv[])
{
    // Demonstrate merge sort for various cases
    
    int size = 10;
    int iarr[] = { 90, 80, 10, 20, 50, 40, 60, 30, 70, 100 };
    float farr[] = { 9.0, 8.0, 1.0, 2.0, 5.0, 4.0, 6.0, 3.0, 7.0, 10.0 };
    char carr[] = { 'x', 'a', 'b', 'f', 'p', 'e', 'o', 'z', 'c', 'd' };

    printf("Test insertion sort :-\n\n");
    printf("With integer array:-\n");
    printIntArray(iarr, size);
    isort(iarr, size, sizeof(int), compareInt);
    printIntArray(iarr, size);

    printf("\nWith floating point array:-\n");
    printFloatArray(farr, size);
    isort(farr, size, sizeof(float), compareFloat);
    printFloatArray(farr, size);
    
    printf("\nWith character array:-\n");
    printCharArray(carr, size);
    isort(carr, size, sizeof(char), compareChar);
    printCharArray(carr, size);
    
    return 0;
}

// implementation

void isort(void* array, size_t num, size_t size, int (*comp)(void* a, void* b))
{
    for (size_t j = 1; j < num; j++)
    {
        void* key = malloc(size);
        memcpy(key, array + j * size, size);
        long int i = j - 1;

        while (i >= 0 && comp(array + i * size, key) > 0)
        {
            memcpy(array + (i+1) * size, array + i * size, size);
            i--;
        }
        memcpy(array + (i+1) * size, key, size);
        free(key);
    }
}

int compareInt(void* a, void* b)
{
    return *((int* )a) - *((int* )b);
}

int compareFloat(void* a, void* b)
{
    return *((float* )a) - *((float* )b);
}

int compareChar(void* a, void* b)
{
    return *((char* )a) - *((char* )b);
}

void printIntArray(int* array, size_t num)
{
    for (size_t i = 0; i < num; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void printFloatArray(float* array, size_t num)
{
    for (size_t i = 0; i < num; i++)
        printf("%.1f  ", array[i]);
    printf("\n");
}

void printCharArray(char* array, size_t num)
{
    for (size_t i = 0; i < num; i++)
        printf("%c ", array[i]);
    printf("\n");
}

