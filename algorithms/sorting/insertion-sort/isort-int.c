/*
 *   Insertion sort
 *   --------------
 *   (using integer data type)
 */

#include <stdio.h>
#include <stdlib.h>

void printArray(const int* array, const size_t size);
void isort(int* array, const size_t size);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("isort : Usage is 'isort [array]'\n");
        return 1;
    }

    size_t size = argc - 1;
    // allocate memory dynamically for the array
    int* array = (int* )calloc(size, sizeof(int));

    for (size_t i = 0; i < size; i++)
        array[i] = atoi(argv[i+1]);

    printf("Array before sorting :-\n");
    printArray(array, size);

    // sort using insertion sort
    isort(array, size);

    printf("\nArray after sorting :-\n");
    printArray(array, size);

    // release memory
    free(array);
    return 0;
}

void printArray(const int* array, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void isort(int* array, const size_t size)
{
    for (size_t j = 1; j < size; j++)
    {
        int key = array[j], i = j - 1;

        while (i >= 0 && array[i] > key)
        {
            array[i + 1] = array[i];
            i--;
        }

        array[i + 1] = key;
    }
}
