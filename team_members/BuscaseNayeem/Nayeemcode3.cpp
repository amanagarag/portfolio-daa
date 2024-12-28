#include <stdio.h>


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void heapify(int arr[], int n, int i) {
    int largest = i;       
    int left = 2 * i + 1;  
    int right = 2 * i + 2; 

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}


void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);


    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]); 
        heapify(arr, i, 0);     
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int maintenanceTasks[] = {35, 20, 50, 10, 60, 40};
    int n = sizeof(maintenanceTasks) / sizeof(maintenanceTasks[0]);

    printf("Original priorities of maintenance tasks:\n");
    printArray(maintenanceTasks, n);

    heapSort(maintenanceTasks, n);

    printf("\nPriorities of maintenance tasks after sorting:\n");
    printArray(maintenanceTasks, n);

    return 0;
}
