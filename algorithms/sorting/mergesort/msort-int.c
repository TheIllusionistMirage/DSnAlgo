/*
 *  Merge sort
 */

#include <stdio.h>
#include <stdlib.h>

void merge(int* array, int low, int mid, int high);
void msort(int* array, int low, int high);
void mergeSort(int* array, int low, int high);

void printIntArray(int* array, int low, int high);

/*int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("msort : Usage is 'msort [unsorted-array]'\n");
        return 0;
    }

    int arr[argc - 1];
    for (int i = 1; i < argc; i++)
        arr[i - 1] = atoi(argv[i]);
*/
int main()
{
    int size = 10;
    int arr[] = { 9, 10, 8, 5, 1, 2, 4, 3, 6, 7 };
    printIntArray(arr, 0, size - 1);
    mergeSort(arr, 0, size - 1);
    printIntArray(arr, 0, size - 1);

    return 0;
}

void merge(int* array, int low, int mid, int high)
{
    int aux[high - low + 1], i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high)
    {
        if (array[i] < array[j])
            aux[k++] = array[i++];
        else if (array[i] > array[j])
            aux[k++] = array[j++];
        else
        {
            aux[k++] = array[i++];
            aux[k++] = array[j++];
        }
    }

    while (i <= mid)
        aux[k++] = array[i++];

    while (j <= high)
        aux[k++] = array[j++];

    k = 0;
    i = low;
    
    while (i <= high)
        array[i++] = aux[k++];
}

void msort(int* array, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        msort(array, low, mid);
        msort(array, mid + 1, high);
        merge(array, low, mid, high);
    }

    return;
}

void mergeSort(int* array, int low, int high)
{
    msort(array, low, high);
}

void printIntArray(int* array, int low, int high)
{
    for (int i = low; i <= high; i++)
        printf("%d ", array[i]);
    printf("\n");
}
