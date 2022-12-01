#include <iostream>
#include "Headers\DataGenerator.h"

void generateRandomData(int* arr, int InputSize)
{
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < InputSize; i++)
		arr[i] = rand() % InputSize;
}
void generateSortedData(int* arr, int InputSize)
{
	for (int i = 0; i < InputSize; i++)
		arr[i] = i;
}
void generateReverseData(int* arr, int InputSize)
{
	for (int i = 0; i < InputSize; i++)
		arr[i] = InputSize - 1 - i;
}
void generateNearlySortedData(int* arr, int InputSize)
{
	for (int i = 0; i < InputSize; i++)
		arr[i] = i;
	srand((unsigned int) time(nullptr));
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand() % InputSize;
		int r2 = rand() % InputSize;
		std::swap(arr[r1], arr[r2]);
	}
}

void GenerateData(int* &arr, int InputSize, int InputOrder)
{
	if (! arr)
		arr = new int[InputSize];
	switch (InputOrder)
	{
        case 0:
            generateRandomData(arr, InputSize);
            break;
        case 1:
            generateSortedData(arr, InputSize);
            break;
        case 2:
            generateReverseData(arr, InputSize);
            break;
        case 3:
            generateNearlySortedData(arr, InputSize);
            break;
	}
}