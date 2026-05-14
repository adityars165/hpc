#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// ========================== BUBBLE SORT ==========================

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int> &arr) {

    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort (Odd-Even Transposition)
void parallelBubbleSort(vector<int> &arr) {

    int n = arr.size();

    for (int i = 0; i < n; i++) {

        // Even Phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }

        // Odd Phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ========================== MERGE SORT ==========================

// Merge two sorted halves
void merge(vector<int>& arr, int left, int mid, int right) {

    int n1 = mid - left + 1;

    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {

        if (L[i] <= R[j])
            arr[k++] = L[i++];

        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int left, int right) {

    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    sequentialMergeSort(arr, left, mid);

    sequentialMergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int left, int right, int depth) {

    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    // Limit recursion depth
    if (depth <= 0) {

        sequentialMergeSort(arr, left, right);

        return;
    }

    #pragma omp parallel sections
    {

        #pragma omp section
        parallelMergeSort(arr, left, mid, depth - 1);

        #pragma omp section
        parallelMergeSort(arr, mid + 1, right, depth - 1);
    }

    merge(arr, left, mid, right);
}

// ========================== MAIN FUNCTION ==========================

int main() {

    int n;

    cout << "Enter number of elements: ";

    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {

        cin >> arr[i];
    }

    // ================= BUBBLE SORT =================

    vector<int> bubbleSeq = arr;
    vector<int> bubblePar = arr;

    double start = omp_get_wtime();

    sequentialBubbleSort(bubbleSeq);

    double end = omp_get_wtime();

    cout << "\n===== BUBBLE SORT =====\n";

    cout << "\nSequential Bubble Sorted Array: ";

    for (int x : bubbleSeq)
        cout << x << " ";

    cout << "\nTime (Sequential Bubble Sort): "
         << (end - start) << " seconds\n";

    start = omp_get_wtime();

    parallelBubbleSort(bubblePar);

    end = omp_get_wtime();

    cout << "\nParallel Bubble Sorted Array: ";

    for (int x : bubblePar)
        cout << x << " ";

    cout << "\nTime (Parallel Bubble Sort): "
         << (end - start) << " seconds\n";

    // ================= MERGE SORT =================

    vector<int> mergeSeq = arr;
    vector<int> mergePar = arr;

    start = omp_get_wtime();

    sequentialMergeSort(mergeSeq, 0, n - 1);

    end = omp_get_wtime();

    cout << "\n\n===== MERGE SORT =====\n";

    cout << "\nSequential Merge Sorted Array: ";

    for (int x : mergeSeq)
        cout << x << " ";

    cout << "\nTime (Sequential Merge Sort): "
         << (end - start) << " seconds\n";

    start = omp_get_wtime();

    parallelMergeSort(mergePar, 0, n - 1, 3);

    end = omp_get_wtime();

    cout << "\nParallel Merge Sorted Array: ";

    for (int x : mergePar)
        cout << x << " ";

    cout << "\nTime (Parallel Merge Sort): "
         << (end - start) << " seconds\n";

    return 0;
}

/*

========================= SAMPLE INPUT =========================

Enter number of elements: 6

Enter elements:
5 3 4 1 2 6

========================= SAMPLE OUTPUT =========================

===== BUBBLE SORT =====

Sequential Bubble Sorted Array: 1 2 3 4 5 6
Time (Sequential Bubble Sort): ...

Parallel Bubble Sorted Array: 1 2 3 4 5 6
Time (Parallel Bubble Sort): ...

===== MERGE SORT =====

Sequential Merge Sorted Array: 1 2 3 4 5 6
Time (Sequential Merge Sort): ...

Parallel Merge Sorted Array: 1 2 3 4 5 6
Time (Parallel Merge Sort): ...

*/
