#include "Headers\HandleFunctions.h"

void outputPara(int arr[], int InputSize, int Algorithm1, int OutputParameter, int Algorithm2 = -1, bool mode = 0)
{
    if (OutputParameter == 0)
    {
        cout << "Running time: ";
        timingAlgorithm(arr, InputSize, Algorithm1);
        if (mode)
        {
            cout << " | ";
            int* arr1 = new int[InputSize];
            for (int i = 0; i < InputSize; i++)
                arr1[i] = arr[i];
            timingAlgorithm(arr1, InputSize, Algorithm2);
        }
        cout << endl;
    }
    else if (OutputParameter == 1)
    {
        cout << "Comparisions: ";
        cout << countingCompAlgorithm(arr, InputSize, Algorithm1);
        if (mode)
        {
            cout << " | ";
            int* arr1 = new int[InputSize];
            for (int i = 0; i < InputSize; i++)
                arr1[i] = arr[i];
            cout << countingCompAlgorithm(arr1, InputSize, Algorithm2);
        }
        cout << endl;
    }
    else
    {
        outputPara(arr, InputSize, Algorithm1, 0, Algorithm2, mode);
        outputPara(arr, InputSize, Algorithm1, 1, Algorithm2, mode);
        cout << endl;
    }
}

void outputFile(string FileName, int arr[], int number)
{
    ofstream OFile;
    OFile.open(FileName);
    if (OFile.is_open())
    {
        OFile << number << endl;
        for (int i = 0; i < number; i++)
            OFile << arr[i] << ' ';
    }
    else
        cerr << "Can not write array into file " << FileName << "." << endl;
}

void outputAlgorithmMode(int Algorithm, int arr[], char* GivenInput, int InputSize, int InputOrder, int OutputParameter)
{
    cout << "ALGORITHM MODE" << endl;
    cout << "Algorithm: " << SortingAlgorithm[Algorithm] << endl;
    if (GivenInput)
        cout << "Input file: " << GivenInput << endl;
    cout << "Input size: " << InputSize << endl;
    if (InputOrder >= 0)
    {
        cout << "Input order: " << InputOrders[InputOrder] << endl;
        for (int i = 0; i < 20; i++)
            cout << '-';
        cout << endl;
        outputPara(arr, InputSize, Algorithm, OutputParameter);
    }
    else
    {
        for (int i = 0; i < NumOfInOrder; i++)
        {
            cout << endl;
            cout << "Input order: " << InputOrders[i] << endl;
            for (int i = 0; i < 20; i++)
                cout << '-';
            cout << endl;
            outputPara(arr, InputSize, Algorithm, OutputParameter);
        }
    }
}

void outputCompareMode(int Algorithm1, int Algorithm2, int arr[], char* GivenInput, int InputSize, int InputOrder)
{
    cout << "COMPARE MODE" << endl;
    cout << "Algorithm: " << SortingAlgorithm[Algorithm1] <<  " | " << SortingAlgorithm[Algorithm2] << endl;
    if (GivenInput)
        cout << "Input file: " << GivenInput << endl;
    cout << "Input size: " << InputSize << endl;
    if (InputOrder >= 0)
        cout << "Input order: " << InputOrders[InputOrder] << endl;
    for (int i = 0; i < 20; i++)
        cout << '-';
    cout << endl;
    outputPara(arr, InputSize, Algorithm1, 2, Algorithm2, 1);
}