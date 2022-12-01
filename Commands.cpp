#include "Headers\Commands.h"
#include <direct.h>

int *arr = nullptr;

bool Command1(int Algorithm, char* GivenInput, int OutputParameter)
{
    ifstream IFile;
    IFile.open(GivenInput);
    if (IFile.is_open())
    {
        int InputSize;
        IFile >> InputSize;
        arr = new int[InputSize];
        for (int i = 0; i < InputSize; i++)
            IFile >> arr[i];

        outputAlgorithmMode(Algorithm, arr, GivenInput, InputSize, -1, OutputParameter);
        
        mkdir("Files");
        string OFile = "Files/output.txt";
        outputFile(OFile, arr, InputSize);
        delete []arr;
        IFile.close();
        return true;
    }
    return false;
}

void Command2(int Algorithm, int InputSize, int InputOrder, int OutputParameter)
{
    GenerateData(arr, InputSize, InputOrder);
    mkdir("Files");
    string IFile = "Files/input.txt";
    outputFile(IFile, arr, InputSize);

    outputAlgorithmMode(Algorithm, arr, nullptr, InputSize, InputOrder, OutputParameter);
    
    string OFile = "Files/output.txt";
    outputFile(OFile, arr, InputSize);
    delete []arr;
}

void Command3(int Algorithm, int InputSize, int OutputParameter)
{
    mkdir("Files");
    for (int i = 0; i < 4; i++)
    {
        GenerateData(arr, InputSize, i);
        string IFile = "Files/input_" + to_string(i + 1) + ".txt";
        outputFile(IFile, arr, InputSize);
    }
    outputAlgorithmMode(Algorithm, arr, nullptr, InputSize, -1, OutputParameter);
    delete []arr;
}

bool Command4(int Algorithm1, int Algorithm2, char* GivenInput)
{
    ifstream IFile;
    IFile.open(GivenInput);
    if (IFile.is_open())
    {
        int InputSize;
        IFile >> InputSize;
        arr = new int[InputSize];
        for (int i = 0; i < InputSize; i++)
            IFile >> arr[InputSize];

        outputCompareMode(Algorithm1, Algorithm2, arr, GivenInput, InputSize, -1);

        delete []arr;
        IFile.close();
        return true;
    }
    return false;
}

void Command5(int Algorithm1, int Algorithm2, int InputSize, int InputOrder)
{
    GenerateData(arr, InputSize, InputOrder);
    mkdir("Files");
    string IFile = "Files/input.txt";
    outputFile(IFile, arr, InputSize);
    outputCompareMode(Algorithm1, Algorithm2, arr, nullptr, InputSize, InputOrder);
    delete []arr;
}