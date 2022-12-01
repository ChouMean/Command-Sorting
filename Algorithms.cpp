#include <chrono>
#include <cmath>
#include "Headers\Algorithms.h"

int countCompare = 0;

void T_SelectionSort(int arr[], int InputSize)
{
    for (int i = 0; i < InputSize - 1; i++)
        for (int j = i + 1; j < InputSize; j++)
            if (arr[i] > arr[j])
                swap(arr[i], arr[j]);
}
void T_InsertionSort(int arr[], int InputSize)
{
    for (int i = 1; i < InputSize; i++)
    {
        int value = arr[i];
        int idx = i - 1;
        while (value < arr[idx] && idx >= 0)
        {
            arr[idx + 1] = arr[idx];
            --idx;
        }
        arr[idx + 1] = value;
    }
}
void T_BubbleSort(int arr[], int InputSize)
{
    for (int i = 0; i < InputSize; i++)
        for (int j = 0; j < InputSize - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}
void T_ShakerSort(int arr[], int InputSize)
{
    int Left = 0;
	int Right = InputSize - 1;
	int k = 0;
	while (Left < Right)
	{
		for (int i = Left; i < Right; i++)
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				k = i;
			}
		Right = k;
		for (int i = Right; i > Left; i--)
			if (arr[i] < arr[i - 1])
			{
				swap(arr[i], arr[i - 1]);
				k = i;
			}
		Left = k;
	}
}
void T_ShellSort(int arr[], int InputSize)
{
    for (int interval = InputSize / 2; interval > 0; interval /= 2)
        for (int i = interval; i < InputSize; i += 1)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= interval && arr[j - interval] > temp; j -= interval)
                arr[j] = arr[j - interval];
            arr[j] = temp;
        }
}
void T_Heapify(int arr[], int InputSize, int pos)
{
    int largest = pos;
Flag:
    int left = 2*pos + 1;
    int right = 2*pos + 2;
    if (left < InputSize && arr[left] > arr[largest])
        largest = left;
    if (right < InputSize && arr[right] > arr[largest])
        largest = right;
    if (largest != pos)
    {
        swap(arr[pos], arr[largest]);
        pos = largest;
        goto Flag;
    }
}
void T_HeapSort(int arr[], int InputSize)
{
    for (int i = InputSize / 2 - 1; i >= 0; i--)
        T_Heapify(arr, InputSize, i);
    for (int i = InputSize - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        T_Heapify(arr, i, 0);
    }
}
void T_Merge(int arr[], int left, int mid, int right)
{
    int LeftLimit = mid - left + 1;
    int RightLimit = right - mid;
    int* LeftArr = new int[LeftLimit];
    int* RightArr = new int[RightLimit];

    for (int i = 0; i < LeftLimit; i++)
        LeftArr[i] = arr[left + i];
    for (int j = 0; j < RightLimit; j++)
        RightArr[j] = arr[mid + 1 + j];

    int IdxOLeftArr = 0, IdxORightArr = 0;
    int IdxOMergeArr = left;

    while (IdxOLeftArr < LeftLimit && IdxORightArr < RightLimit)
        if (LeftArr[IdxOLeftArr] <= RightArr[IdxORightArr])
            arr[IdxOMergeArr++] = LeftArr[IdxOLeftArr++];
        else
            arr[IdxOMergeArr++] = RightArr[IdxORightArr++];

    while (IdxOLeftArr < LeftLimit)
        arr[IdxOMergeArr++] = LeftArr[IdxOLeftArr++];
    while (IdxORightArr < RightLimit)
        arr[IdxOMergeArr++] = RightArr[IdxORightArr++];

    delete []LeftArr;
    delete []RightArr;
}
void T_MergeSort(int arr[], int first, int last)
{
    if (first >= last)
        return;
    int mid = first + (last - first) / 2;
    T_MergeSort(arr, first, mid);
    T_MergeSort(arr, mid + 1, last);
    T_Merge(arr, first, mid, last);
}
void T_QuickSort(int arr[], int left, int right)
{
    int pivot = arr[(left+right)/2];
    int i = left, j = right;
    while (i < j)
    {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j)
            swap(arr[i++], arr[j--]);
    }
    if (i < right)
        T_QuickSort(arr, i, right);
    if (left < j)
        T_QuickSort(arr, left, j);
}
void T_CountingSort(int arr[], int InputSize)
{
    int Max = arr[0];
    for (int i = 1; i < InputSize; i++)
        if (arr[i] > Max)
            Max = arr[i];

    int *Count = new int[Max + 1] {};

    for (int i = 0; i < InputSize; i++)
        Count[arr[i]]++;

    for (int i = 1; i <= Max; i++)
        Count[i] += Count[i - 1];

    int *output = new int[InputSize];
    for (int i = 0; i < InputSize; i++)
        output[--Count[arr[i]]] = arr[i];

    for (int i = 0; i < InputSize; i++)
        arr[i] = output[i];
    delete[] Count;
    delete[] output;
}
void T_RadixSort(int arr[], int InputSize)
{
    int *SubArr = new int[InputSize];
    int Max = arr[0], exp = 1;

    for (int i = 0; i < InputSize; i++)
        if (arr[i] > Max)
            Max = arr[i];

    while (Max / exp > 0)
    {
        int Bucket[10] {};
        for (int i = 0; i < InputSize; i++)
            Bucket[arr[i] / exp % 10]++;
        for (int i = 1; i < 10; i++)
            Bucket[i] += Bucket[i - 1];
        for (int i = InputSize - 1; i >= 0; i--)
            SubArr[--Bucket[arr[i] / exp % 10]] = arr[i];
        for (int i = 0; i < InputSize; i++)
            arr[i] = SubArr[i];
        exp *= 10;
    }
    delete []SubArr;
}
void T_FlashSort(int arr[], int InputSize)
{
    int Min = arr[0];
	int Max = 0;
	int NumOBuckets = int(0.45 * InputSize);
	int *Bucket = new int[NumOBuckets];
	for (int i = 0; i < NumOBuckets; i++)
		Bucket[i] = 0;
	for (int i = 1; i < InputSize; i++)
	{
		if (arr[i] < Min)
			Min = arr[i];
		if (arr[i] > arr[Max])
			Max = i;
	}
	if (arr[Max] == Min)
		return;
	double c1 = (double)(NumOBuckets - 1) / (arr[Max] - Min);
	for (int i = 0; i < InputSize; i++)
	{
		int k = int(c1 * (arr[i] - Min));
		++Bucket[k];
	}
	for (int i = 1; i < NumOBuckets; i++)
		Bucket[i] += Bucket[i - 1];
	swap(arr[Max], arr[0]);
	int pos = 0;
	int j = 0;
	int k = NumOBuckets - 1;
	int t = 0;
	int flash;
	while (pos < InputSize - 1)
	{
		while (j > Bucket[k] - 1)
			k = int(c1 * (arr[++j] - Min));
		flash = arr[j];
		if (k < 0)
			break;
		while (j != Bucket[k])
		{
			k = int(c1 * (flash - Min));
			int hold = arr[t = --Bucket[k]];
			arr[t] = flash;
			flash = hold;
			++pos;
		}
	}
	delete[] Bucket;
	T_InsertionSort(arr, InputSize);
}
int T_BinarySort(int arr[], int value, int low, int high)
{
    if (high <= low)
        return (value > arr[low]) ? (low + 1) : low;
    int mid = (low + high) / 2;
    if (value == arr[mid])
        return mid + 1;
    if (value > arr[mid])
        return T_BinarySort(arr, value, mid + 1, high);
    return T_BinarySort(arr, value, low, mid - 1);
}
void T_BinaryInsertionSort(int arr[], int InputSize)
{
    for (int i = 1; i < InputSize; ++i)
    {
        int j = i - 1;
        int value = arr[i];
        int pos = T_BinarySort(arr, value, 0, j);
        while (j >= pos)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = value;
    }
}


void C_SelectionSort(int arr[], int InputSize)
{
    for (int i = 0; ++countCompare && i < InputSize - 1; i++)
        for (int j = i + 1; ++countCompare && j < InputSize; j++)
            if (++countCompare && arr[i] > arr[j])
                swap(arr[i], arr[j]);
}
void C_InsertionSort(int arr[], int InputSize)
{
    for (int i = 1; ++countCompare && i < InputSize; i++)
    {
        int value = arr[i];
        int idx = i - 1;
        while (++countCompare && value < arr[idx] && ++countCompare && idx >= 0)
        {
            arr[idx + 1] = arr[idx];
            --idx;
        }
        arr[idx + 1] = value;
    }
}
void C_BubbleSort(int arr[], int InputSize)
{
    for (int i = 0; ++countCompare && i < InputSize; i++)
        for (int j = 0; ++countCompare && j < InputSize - i - 1; j++)
            if (++countCompare && arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}
void C_ShakerSort(int arr[], int InputSize)
{
    int Left = 0;
	int Right = InputSize - 1;
	int k = 0;
	while (++countCompare && Left < Right)
	{
		for (int i = Left; ++countCompare && i < Right; i++)
			if (++countCompare && arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				k = i;
			}
		Right = k;
		for (int i = Right; ++countCompare && i > Left; i--)
			if (++countCompare && arr[i] < arr[i - 1])
			{
				swap(arr[i], arr[i - 1]);
				k = i;
			}
		Left = k;
	}
}
void C_ShellSort(int arr[], int InputSize)
{
    for (int interval = InputSize / 2; ++countCompare && interval > 0; interval /= 2)
        for (int i = interval; ++countCompare && i < InputSize; i += 1)
        {
            int temp = arr[i];
            int j;
            for (j = i; ++countCompare && j >= interval && ++countCompare && arr[j - interval] > temp; j -= interval)
                arr[j] = arr[j - interval];
            arr[j] = temp;
        }
}
void C_Heapify(int arr[], int InputSize, int pos)
{
    int largest = pos;
Flag:
    int left = 2*pos + 1;
    int right = 2*pos + 2;
    if (++countCompare && left < InputSize && ++countCompare && arr[left] > arr[largest])
        largest = left;
    if (++countCompare && right < InputSize && ++countCompare && arr[right] > arr[largest])
        largest = right;
    if (++countCompare && largest != pos)
    {
        swap(arr[pos], arr[largest]);
        pos = largest;
        goto Flag;
    }
}
void C_HeapSort(int arr[], int InputSize)
{
    for (int i = InputSize / 2 - 1; ++countCompare && i >= 0; i--)
        C_Heapify(arr, InputSize, i);
    for (int i = InputSize - 1; ++countCompare && i > 0; i--)
    {
        swap(arr[0], arr[i]);
        C_Heapify(arr, i, 0);
    }
}
void C_Merge(int arr[], int left, int mid, int right)
{
    int LeftLimit = mid - left + 1;
    int RightLimit = right - mid;
    int* LeftArr = new int[LeftLimit];
    int* RightArr = new int[RightLimit];

    for (int i = 0; ++countCompare && i < LeftLimit; i++)
        LeftArr[i] = arr[left + i];
    for (int j = 0; ++countCompare && j < RightLimit; j++)
        RightArr[j] = arr[mid + 1 + j];

    int IdxOLeftArr = 0, IdxORightArr = 0;
    int IdxOMergeArr = left;

    while (++countCompare && IdxOLeftArr < LeftLimit && ++countCompare && IdxORightArr < RightLimit)
        if (++countCompare && LeftArr[IdxOLeftArr] <= RightArr[IdxORightArr])
            arr[IdxOMergeArr++] = LeftArr[IdxOLeftArr++];
        else
            arr[IdxOMergeArr++] = RightArr[IdxORightArr++];

    while (++countCompare && IdxOLeftArr < LeftLimit)
        arr[IdxOMergeArr++] = LeftArr[IdxOLeftArr++];
    while (++countCompare && IdxORightArr < RightLimit)
        arr[IdxOMergeArr++] = RightArr[IdxORightArr++];

    delete []LeftArr;
    delete []RightArr;
}
void C_MergeSort(int arr[], int first, int last)
{
    if (++countCompare && first >= last)
        return;
    int mid = first + (last - first) / 2;
    C_MergeSort(arr, first, mid);
    C_MergeSort(arr, mid + 1, last);
    C_Merge(arr, first, mid, last);
}
void C_QuickSort(int arr[], int left, int right)
{
    int pivot = arr[(left+right)/2];
    int i = left, j = right;
    while (++countCompare && i < j)
    {
        while (++countCompare && arr[i] < pivot)
            i++;
        while (++countCompare && arr[j] > pivot)
            j--;
        if (++countCompare && i <= j)
            swap(arr[i++], arr[j--]);
    }
    if (++countCompare && i < right)
        C_QuickSort(arr, i, right);
    if (++countCompare && left < j)
        C_QuickSort(arr, left, j);
}
void C_CountingSort(int arr[], int InputSize)
{
    int Max = arr[0];
    for (int i = 1; ++countCompare && i < InputSize; i++)
        if (++countCompare && arr[i] > Max)
            Max = arr[i];

    int *Count = new int[Max + 1] {};

    for (int i = 0; ++countCompare && i < InputSize; i++)
        Count[arr[i]]++;

    for (int i = 1; ++countCompare && i <= Max; i++)
        Count[i] += Count[i - 1];

    int *output = new int[InputSize];
    for (int i = 0; ++countCompare && i < InputSize; i++)
        output[--Count[arr[i]]] = arr[i];

    for (int i = 0; ++countCompare && i < InputSize; i++)
        arr[i] = output[i];
    delete[] Count;
    delete[] output;
}
void C_RadixSort(int arr[], int InputSize)
{
    int *SubArr = new int[InputSize];
    int Max = arr[0], exp = 1;

    for (int i = 0; ++countCompare && i < InputSize; i++)
        if (++countCompare && arr[i] > Max)
            Max = arr[i];

    while (++countCompare && Max / exp > 0)
    {
        int Bucket[10] {};
        for (int i = 0; ++countCompare && i < InputSize; i++)
            Bucket[arr[i] / exp % 10]++;
        for (int i = 1; ++countCompare && i < 10; i++)
            Bucket[i] += Bucket[i - 1];
        for (int i = InputSize - 1; ++countCompare && i >= 0; i--)
            SubArr[--Bucket[arr[i] / exp % 10]] = arr[i];
        for (int i = 0; ++countCompare && i < InputSize; i++)
            arr[i] = SubArr[i];
        exp *= 10;
    }
    delete []SubArr;
}
void C_FlashSort(int arr[], int InputSize)
{
    int Min = arr[0];
	int Max = 0;
	int NumOBuckets = int(0.45 * InputSize);
	int *Bucket = new int[NumOBuckets];
	for (int i = 0; ++countCompare && i < NumOBuckets; i++)
		Bucket[i] = 0;
	for (int i = 1; ++countCompare && i < InputSize; i++)
	{
		if (++countCompare && arr[i] < Min)
			Min = arr[i];
		if (++countCompare && arr[i] > arr[Max])
			Max = i;
	}
	if (++countCompare && arr[Max] == Min)
		return;
	double c1 = (double)(NumOBuckets - 1) / (arr[Max] - Min);
	for (int i = 0; ++countCompare && i < InputSize; i++)
	{
		int k = int(c1 * (arr[i] - Min));
		++Bucket[k];
	}
	for (int i = 1; ++countCompare && i < NumOBuckets; i++)
		Bucket[i] += Bucket[i - 1];
	swap(arr[Max], arr[0]);
	int pos = 0;
	int j = 0;
	int k = NumOBuckets - 1;
	int t = 0;
	int flash;
	while (++countCompare && pos < InputSize - 1)
	{
		while (++countCompare && j > Bucket[k] - 1)
			k = int(c1 * (arr[++j] - Min));
		flash = arr[j];
		if (++countCompare && k < 0)
			break;
		while (++countCompare && j != Bucket[k])
		{
			k = int(c1 * (flash - Min));
			int hold = arr[t = --Bucket[k]];
			arr[t] = flash;
			flash = hold;
			++pos;
		}
	}
	delete[] Bucket;
	C_InsertionSort(arr, InputSize);
}
int C_BinarySort(int arr[], int value, int low, int high)
{
    if (++countCompare && high <= low)
        return (++countCompare && value > arr[low]) ? (low + 1) : low;
    int mid = (low + high) / 2;
    if (++countCompare && value == arr[mid])
        return mid + 1;
    if (++countCompare && value > arr[mid])
        return C_BinarySort(arr, value, mid + 1, high);
    return C_BinarySort(arr, value, low, mid - 1);
}
void C_BinaryInsertionSort(int arr[], int InputSize)
{
    for (int i = 1; ++countCompare && i < InputSize; ++i)
    {
        int j = i - 1;
        int value = arr[i];
        int pos = C_BinarySort(arr, value, 0, j);
        while (++countCompare && j >= pos)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = value;
    }
}


void timingAlgorithm(int arr[], int InputSize, int Algorithm)
{
    using namespace chrono;
    high_resolution_clock::time_point TimeBegin = high_resolution_clock::now();
    switch (Algorithm)
    {
        case 0: T_SelectionSort(arr, InputSize); break;
        case 1: T_InsertionSort(arr, InputSize); break;
        case 2: T_BubbleSort(arr, InputSize); break;
        case 3: T_ShakerSort(arr, InputSize); break;
        case 4: T_ShellSort(arr, InputSize); break;
        case 5: T_HeapSort(arr, InputSize); break;
        case 6: T_MergeSort(arr, 0, InputSize - 1); break;
        case 7: T_QuickSort(arr, 0, InputSize - 1); break;
        case 8: T_CountingSort(arr, InputSize); break;
        case 9: T_RadixSort(arr, InputSize); break;
        case 10: T_FlashSort(arr, InputSize); break;
        case 11: T_BinaryInsertionSort(arr, InputSize); break;
    }

    long long time = duration_cast<microseconds>(high_resolution_clock::now() - TimeBegin).count();
    if (time < 10000)
        cout << time << " microseconds";
    else
        cout << time / 10000 << " milliseconds";
}
int countingCompAlgorithm(int arr[], int InputSize, int Algorithm)
{
    switch (Algorithm)
    {
        case 0: C_SelectionSort(arr, InputSize); break;
        case 1: C_InsertionSort(arr, InputSize); break;
        case 2: C_BubbleSort(arr, InputSize); break;
        case 3: C_ShakerSort(arr, InputSize); break;
        case 4: C_ShellSort(arr, InputSize); break;
        case 5: C_HeapSort(arr, InputSize); break;
        case 6: C_MergeSort(arr, 0, InputSize - 1); break;
        case 7: C_QuickSort(arr, 0, InputSize - 1); break;
        case 8: C_CountingSort(arr, InputSize); break;
        case 9: C_RadixSort(arr, InputSize); break;
        case 10: C_FlashSort(arr, InputSize); break;
        case 11: C_BinaryInsertionSort(arr, InputSize); break;
    }
    return countCompare;
}