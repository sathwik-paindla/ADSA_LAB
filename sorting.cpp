#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_VAL 100

// (i) INSERTION SORT
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; j--; }
        arr[j + 1] = key;
    }
}

// (ii) BUBBLE SORT
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1]) { int tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp; }
}

// (iii) SELECTION SORT
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_i]) min_i = j;
        int tmp = arr[min_i]; arr[min_i] = arr[i]; arr[i] = tmp;
    }
}

// (iv) SHELL SORT
void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++)
            for (int j = i; j >= gap && arr[j] < arr[j-gap]; j -= gap) {
                int tmp = arr[j]; arr[j] = arr[j-gap]; arr[j-gap] = tmp;
            }
}

// (v) QUICK SORT
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot) { i++; int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp; }
    int tmp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = tmp;
    return i + 1;
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// (vi) MERGE SORT
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[MAX_SIZE], R[MAX_SIZE];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

// (vii) HEAP SORT
void heapify(int arr[], int n, int i) {
    int largest=i, l=2*i+1, r=2*i+2;
    if (l<n && arr[l]>arr[largest]) largest=l;
    if (r<n && arr[r]>arr[largest]) largest=r;
    if (largest!=i) {
        int tmp = arr[i]; arr[i]=arr[largest]; arr[largest]=tmp;
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n) {
    for (int i=n/2-1; i>=0; i--) heapify(arr, n, i);
    for (int i=n-1; i>0; i--) {
        int tmp=arr[0]; arr[0]=arr[i]; arr[i]=tmp;
        heapify(arr, i, 0);
    }
}

// (viii) RADIX SORT
int getMax(int arr[], int n) {
    int mx=arr[0];
    for (int i=1; i<n; i++) if(arr[i]>mx) mx=arr[i];
    return mx;
}
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    for (int exp=1; max/exp>0; exp*=10) {
        int output[MAX_SIZE]={0}, count[10]={0};
        for (int i=0; i<n; i++) count[(arr[i]/exp)%10]++;
        for (int i=1; i<10; i++) count[i]+=count[i-1];
        for (int i=n-1; i>=0; i--) output[--count[(arr[i]/exp)%10]] = arr[i];
        for (int i=0; i<n; i++) arr[i]=output[i];
    }
}

// (ix) COUNTING SORT
void countingSort(int arr[], int n) {
    int count[MAX_VAL+1]={0}, output[MAX_SIZE];
    for (int i=0; i<n; i++) if(arr[i]>=0 && arr[i]<=MAX_VAL) count[arr[i]]++;
    for (int i=1; i<=MAX_VAL; i++) count[i]+=count[i-1];
    for (int i=n-1; i>=0; i--) output[--count[arr[i]]] = arr[i];
    for (int i=0; i<n; i++) arr[i] = output[i];
}

// (x) bucket sort
void insertionSort(int arr[], int n);
void bucketSort(int arr[], int n) {
    int buckets[10][MAX_SIZE] = {0};
    int bucket_count[10] = {0};
    int min = arr[0], max = arr[0];
    for (int i=1; i<n; i++) { if(arr[i]>max) max=arr[i]; if(arr[i]<min) min=arr[i]; }
    for (int i=0; i<n; i++) {
        int bi = (arr[i]-min)*9/(max-min+1);
        buckets[bi][bucket_count[bi]++] = arr[i];
    }
    int idx=0;
    for(int i=0; i<10; i++) {
        insertionSort(buckets[i], bucket_count[i]);
        for (int j=0; j< bucket_count[i]; j++) arr[idx++] = buckets[i][j];
    }
}

// (xi) RADIX EXCHANGE SORT
// (x) RADIX EXCHANGE SORT
void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0)
        return;

    int i = left;
    int j = right;

    while (i <= j) {
        while (i <= j && ((arr[i] >> bit) & 1) == 0)
            i++;

        while (i <= j && ((arr[j] >> bit) & 1) == 1)
            j--;

        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}

void radixExchange(int arr[], int n) {
    radixExchangeSort(arr, 0, n - 1, 30);
}

// (xii) ADDRESS CALCULATION SORT (simple)
void addressCalculationSort(int arr[], int n) {
    int output[MAX_VAL+1];
    for (int i=0; i<=MAX_VAL; i++) output[i] = -1;
    for (int i=0; i<n; i++)
        if(arr[i]>=0 && arr[i]<=MAX_VAL) output[arr[i]]=arr[i];
    int idx=0;
    for (int i=0; i<=MAX_VAL; i++)
        if(output[i] != -1) arr[idx++]=output[i];
}



int main() {
    int n;
    int arr[MAX_SIZE];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nOriginal array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    // 1. Insertion Sort
    int temp[MAX_SIZE];
    memcpy(temp, arr, sizeof(int) * n);
    insertionSort(temp, n);

    printf("\nInsertion Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 2. Bubble Sort
    memcpy(temp, arr, sizeof(int) * n);
    bubbleSort(temp, n);

    printf("\nBubble Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 3. Selection Sort
    memcpy(temp, arr, sizeof(int) * n);
    selectionSort(temp, n);

    printf("\nSelection Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 4. Shell Sort
    memcpy(temp, arr, sizeof(int) * n);
    shellSort(temp, n);

    printf("\nShell Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 5. Quick Sort
    memcpy(temp, arr, sizeof(int) * n);
    quickSort(temp, 0, n - 1);

    printf("\nQuick Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 6. Merge Sort
    memcpy(temp, arr, sizeof(int) * n);
    mergeSort(temp, 0, n - 1);

    printf("\nMerge Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 7. Heap Sort
    memcpy(temp, arr, sizeof(int) * n);
    heapSort(temp, n);

    printf("\nHeap Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 8. Radix Sort
    memcpy(temp, arr, sizeof(int) * n);
    radixSort(temp, n);

    printf("\nRadix Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 9. Counting Sort
    memcpy(temp, arr, sizeof(int) * n);
    countingSort(temp, n);

    printf("\nCounting Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 10. Bucket Sort
    memcpy(temp, arr, sizeof(int) * n);
    bucketSort(temp, n);

    printf("\nBucket Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 11. Radix Exchange Sort
    memcpy(temp, arr, sizeof(int) * n);
    radixExchange(temp, n);

    printf("\nRadix Exchange Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    // 12. Address Calculation Sort
    memcpy(temp, arr, sizeof(int) * n);
    addressCalculationSort(temp, n);

    printf("\nAddress Calculation Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    printf("\n");

    return 0;
}
