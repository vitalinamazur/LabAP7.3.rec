#include <iostream>
#include <iomanip>
#include <ctime>
#include <Windows.h>

using namespace std;

void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < N - 1)
        CreateRow(a, rowNo, N, Low, High, colNo + 1);
}

void CreateRows(int** a, const int K, const int N, const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, N, Low, High, 0);
    if (rowNo < K - 1)
        CreateRows(a, K, N, Low, High, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int N, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < N - 1)
        PrintRow(a, rowNo, N, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int K, const int N, int rowNo)
{
    PrintRow(a, rowNo, N, 0);
    if (rowNo < K - 1)
        PrintRows(a, K, N, rowNo + 1);
    else
        cout << endl;
}

int SumRowIfNoNegatives(int** a, const int N, int rowNo, int colNo, bool& hasNegative)
{
    if (a[rowNo][colNo] < 0)
        hasNegative = true;
    if (colNo < N - 1)
        return a[rowNo][colNo] + SumRowIfNoNegatives(a, N, rowNo, colNo + 1, hasNegative);
    return a[rowNo][colNo];
}

int SumRowsWithoutNegatives(int** a, const int K, const int N, int rowNo)
{
    bool hasNegative = false;
    int rowSum = SumRowIfNoNegatives(a, N, rowNo, 0, hasNegative);
    if (!hasNegative)
        rowSum += SumRowsWithoutNegatives(a, K, N, rowNo + 1);
    else if (rowNo < K - 1)
        return SumRowsWithoutNegatives(a, K, N, rowNo + 1);
    return rowSum;
}

int DiagonalSum(int** a, const int N, int diagStart, int i)
{
    int j = i + diagStart;
    if (j >= 0 && j < N)
        return a[i][j] + DiagonalSum(a, N, diagStart, i + 1);
    return 0;
}

void MinSumParallelDiagonals(int** a, const int N, int diagStart, int& minSum, bool isFirst = true)
{
    int diagSum = DiagonalSum(a, N, diagStart, 0);
    if (isFirst || diagSum < minSum)
        minSum = diagSum;
    if (diagStart < N - 1)
        MinSumParallelDiagonals(a, N, diagStart + 1, minSum, false);
}

int main()
{
    srand((unsigned)time(NULL));

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int Low = -10, High = 10, size;

    cout << " n= ";
    cin >> size;

    int** a = new int* [size];
    for (int i = 0; i < size; i++)
        a[i] = new int[size];

    CreateRows(a, size, size, Low, High, 0);
    PrintRows(a, size, size, 0);

    int sum = SumRowsWithoutNegatives(a, size, size, 0);
    cout << "SumPositiveRows: " << sum << endl;

    int minDiagonalSum;
    MinSumParallelDiagonals(a, size, 1 - size, minDiagonalSum);
    cout << "MinSumParallelDiagonals: " << minDiagonalSum << endl;

    for (int i = 0; i < size; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}