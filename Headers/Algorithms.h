#include <iostream>
using namespace std;

const int NumOfAl(12);
const int NumOfInOrder(4);
const int NumOfOutPara(3);

const string SortingList[NumOfAl] {
    "selection-sort", "insertion-sort", "bubble-sort", "shaker-sort",
    "shell-sort", "heap-sort", "merge-sort", "quick-sort",
    "counting-sort", "radix-sort", "flash-sort", "binary-insertion-sort"
};
const string SortingAlgorithm[NumOfAl] {
    "Selection Sort", "Insertion Sort", "Bubble Sort", "Shaker Sort",
    "Shell Sort", "Heap Sort", "Merge Sort", "Quick Sort",
    "Counting Sort", "Radix Sort", "Flash Sort", "Binary Insertion Sort"
};

const string InputOrderList[NumOfInOrder] = {"rand", "nsorted", "sorted", "rev"};
const string InputOrders[NumOfInOrder] = {"Randomize", "Nearly Sorted", "Sorted", "Reversed"};
const string OutputParameterList[NumOfOutPara] = {"time", "comp", "both"};

void timingAlgorithm(int arr[], int InputSize, int Algorithm);
int countingCompAlgorithm(int arr[], int InputSize, int Algorithm);