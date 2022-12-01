#include "Headers\Commands.h"

int checkMode(char parameter[])
{
    if (parameter[0] != '-')
    {
        cerr << "Invalid parameter in the first mode.";
        exit(2);
    }
    if (parameter[1] == 'a')
        return 0;
    if (parameter[1] == 'c')
        return 1;
    cerr << "Can not find " << parameter << " in the first mode.";
    exit(2);
}
int checkAlgorithm(char parameter[])
{
    for (int i = 0; i < NumOfAl; i++)
        if (SortingList[i].compare(parameter) == 0)
            return i;
    cerr << "Cannot find " << parameter << " in algorithm list";
    exit(2);
}
int checkInputSize(char parameter[])
{
    for (int i = 1; i < strlen(parameter); i++)
        if (parameter[i] < 48 || parameter[i] > 57)
            return 0;
    return stoi(parameter);
}
int checkInputOrder(char parameter[])
{
    if (parameter[0] != '-')
    {
        cerr << "Invalid input order.";
        exit(2);
    }
    for (int i = 0; i < NumOfInOrder; i++)
        if (InputOrderList[i].compare(parameter + 1) == 0)
            return i;
    cerr << "Can not find " << parameter << " in input order modes.";
    exit(2);
}
int checkOutputParameters(char parameter[])
{
    if (parameter[0] != '-')
    {
        cerr << "Invalid output parameter(s).";
        exit(2);
    }
    for (int i = 0; i < NumOfOutPara; i++)
        if (OutputParameterList[i].compare(parameter + 1) == 0)
            return i;
    cerr << "Can not find " << parameter << " in output parameter(s) mode.";
    exit(2);
}

int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        cerr << "Too few parameter(s). Please check syntax again.";
        return 1;
    }
    if (argc > 6)
    {
        cerr << "Too much parameter(s). Please check syntax again.";
        return 1;
    }

    int mode = checkMode(argv[1]);
    int *PosAl = new int[mode + 1] {checkAlgorithm(argv[2])};
    if (mode == 0)
    {
        int InputSize = checkInputSize(argv[3]);
        int OutputParameters = checkOutputParameters(argv[argc - 1]);
        if (InputSize > 0 && InputSize <= 1000000)
        {
            if (argc == 5)
                Command3(PosAl[0], InputSize, OutputParameters);
            else
                Command2(PosAl[0], InputSize, checkInputOrder(argv[4]), OutputParameters);
        }
        else if (InputSize == 0)
        {
            if (argc == 5 && ! Command1(PosAl[0], argv[3], OutputParameters))
            {
                cerr << "Can not find " << argv[3] << ".";
                return 2;
            }
        }
        else
        {
            cerr << "Invalid parameter number " << 3 << ". Please check again.";
            return 2;
        }
    }
    else
    {
        PosAl[1] = checkAlgorithm(argv[3]);
        if (argc == 5)
        {
            if (! Command4(PosAl[0], PosAl[1], argv[4]))
            {
                cerr << "Can not find " << argv[4] << ".";
                return 2;
            }
        }
        else
        {
            int InputSize = checkInputSize(argv[4]);
            if (InputSize > 0 && InputSize <= 1000000)
                Command5(PosAl[0], PosAl[1], InputSize, checkInputOrder(argv[5]));
            else if (InputSize <= 0)
            {
                cerr << "Invalid input size.";
                return 2;
            }
        }
    }

    delete []PosAl;
    return 0;
}