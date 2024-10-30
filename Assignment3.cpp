// Assignment-3 Solution

/*
Implement four sorting algorithms (Bubble Sort, Selection Sort, Merge Sort, and Quick Sort) on three different arrays of equal size.
•	Array 1: at which best case scenario applies.
•	Array 2: at which average case scenario applies.
•	Array 3: at which worst case scenario applies.
For each sorting algorithm and array combination, measure the time taken to sort the array. You can use a built-in function or implement a custom function to calculate the execution time.
Analyze the results to compare the performance of the different sorting algorithms under various conditions.
Push the source code to a Git repository. Ensure that the repository is public and that you have added me as a collaborator.
In the PDF document, include the URL of the Git repository so that I can access and review the code.
*/ 
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

// Function to swap two elements in an array
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to measure execution time
double measureTime(function<void(vector<int>&)> sortFunction, vector<int>& arr) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count() / 1000.0; // Convert to milliseconds
}

int main() {
    const int arraySize = 10000;
    vector<int> bestCase(arraySize);
    vector<int> averageCase(arraySize);
    vector<int> worstCase(arraySize);

    // Populate the arrays
    for (int i = 0; i < arraySize; i++) {
        bestCase[i] = i;
        averageCase[i] = rand() % arraySize;
        worstCase[i] = arraySize - i;
    }

    vector<vector<int>> arrays = {bestCase, averageCase, worstCase};
    vector<function<void(vector<int>&)>> sortFunctions = {bubbleSort, selectionSort, mergeSort, quickSort};

    for (auto& arr : arrays) {
        for (auto& sortFunction : sortFunctions) {
            vector<int> tempArr = arr; // Create a copy to avoid modifying the original array
            double timeTaken = measureTime(sortFunction, tempArr);
            cout << "Sorting algorithm: " << sortFunction.target_type().name() << endl;
            cout << "Array type: " << (arr == bestCase ? "Best Case" : (arr == worstCase ? "Worst Case" : "Average Case")) << endl;
            cout << "Time taken: " << timeTaken << " milliseconds" << endl;
            cout << endl;
        }
    }
    return 0;
}
