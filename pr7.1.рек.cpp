// Lab_7_1_rec.cpp
// Соломія Клак
// Лабораторна робота № 7.1.рек
// Варіант 14

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Прототипи рекурсивних функцій
void CreateRow(int** z, const int rowNo, const int colCount, const int Low, const int High, int colNo);
void CreateRows(int** z, const int rowCount, const int colCount, const int Low, const int High, int rowNo);

void PrintRow(int** z, const int rowNo, const int colCount, int colNo);
void PrintRows(int** z, const int rowCount, const int colCount, int rowNo);

void Change(int** z, const int col1, const int col2, const int rowCount, int rowNo);
void SortCols(int** z, const int rowCount, const int colCount, int i0, int i1);

void CalcCol(int** z, const int rowCount, const int colNo, int& S, int& k, int rowNo);
void CalcCols(int** z, const int rowCount, const int colCount, int& S, int& k, int colNo);

int main()
{
    srand((unsigned)time(NULL));

    // Параметри варіанта 14
    const int Low = 18;
    const int High = 74;
    const int rowCount = 9;
    const int colCount = 6;

    // Виділення пам'яті для динамічної матриці Z(9x6)
    int** z = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        z[i] = new int[colCount];

    // 1. Рекурсивне формування та виведення початкової матриці
    CreateRows(z, rowCount, colCount, Low, High, 0);
    cout << "Initial matrix Z:" << endl;
    PrintRows(z, rowCount, colCount, 0);

    // 2. Рекурсивне впорядкування стовпчиків за ключами
    SortCols(z, rowCount, colCount, 0, 0);
    cout << "Sorted matrix Z (columns rearranged):" << endl;
    PrintRows(z, rowCount, colCount, 0);

    // 3. Рекурсивне обчислення та заміна нулями за критерієм
    int S = 0;
    int k = 0;
    CalcCols(z, rowCount, colCount, S, k, 0);

    // Виведення результатів та остаточної матриці
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified matrix Z (after Calc):" << endl;
    PrintRows(z, rowCount, colCount, 0);

    // Звільнення динамічної пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] z[i];
    delete[] z;

    return 0;
}

// Рекурсивне формування елементів рядка
void CreateRow(int** z, const int rowNo, const int colCount, const int Low, const int High, int colNo)
{
    z[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(z, rowNo, colCount, Low, High, colNo + 1);
}

// Рекурсивне формування рядків матриці
void CreateRows(int** z, const int rowCount, const int colCount, const int Low, const int High, int rowNo)
{
    CreateRow(z, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(z, rowCount, colCount, Low, High, rowNo + 1);
}

// Рекурсивне виведення елементів рядка
void PrintRow(int** z, const int rowNo, const int colCount, int colNo)
{
    cout << setw(5) << z[rowNo][colNo];
    if (colNo < colCount - 1)
    {
        PrintRow(z, rowNo, colCount, colNo + 1);
    }
    else
    {
        cout << endl;
    }
}

// Рекурсивне виведення рядків матриці
void PrintRows(int** z, const int rowCount, const int colCount, int rowNo)
{
    PrintRow(z, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
    {
        PrintRows(z, rowCount, colCount, rowNo + 1);
    }
    else
    {
        cout << endl;
    }
}

// Рекурсивний обмін елементів у двох стовпчиках рядок за рядком
void Change(int** z, const int col1, const int col2, const int rowCount, int rowNo)
{
    int tmp = z[rowNo][col1];
    z[rowNo][col1] = z[rowNo][col2];
    z[rowNo][col2] = tmp;

    if (rowNo < rowCount - 1)
        Change(z, col1, col2, rowCount, rowNo + 1);
}

// Рекурсивне сортування стовпчиків за ключами: -> <- <-
void SortCols(int** z, const int rowCount, const int colCount, int i0, int i1)
{
    if ((z[0][i1] > z[0][i1 + 1]) ||
        (z[0][i1] == z[0][i1 + 1] && z[1][i1] < z[1][i1 + 1]) ||
        (z[0][i1] == z[0][i1 + 1] && z[1][i1] == z[1][i1 + 1] && z[2][i1] < z[2][i1 + 1]))
    {
        Change(z, i1, i1 + 1, rowCount, 0);
    }

    if (i1 < colCount - i0 - 2)
    {
        SortCols(z, rowCount, colCount, i0, i1 + 1);
    }
    else if (i0 < colCount - 2)
    {
        SortCols(z, rowCount, colCount, i0 + 1, 0);
    }
}

// Рекурсивна обробка елементів стовпчика за критерієм
void CalcCol(int** z, const int rowCount, const int colNo, int& S, int& k, int rowNo)
{
    // Критерій Варіанта 14: "всі, крім: непарних або кратних 7"
    if (!(z[rowNo][colNo] % 2 != 0 || z[rowNo][colNo] % 7 == 0))
    {
        S += z[rowNo][colNo];
        k++;
        z[rowNo][colNo] = 0;
    }

    if (rowNo < rowCount - 1)
        CalcCol(z, rowCount, colNo, S, k, rowNo + 1);
}

// Рекурсивний перебір стовпчиків матриці
void CalcCols(int** z, const int rowCount, const int colCount, int& S, int& k, int colNo)
{
    CalcCol(z, rowCount, colNo, S, k, 0);

    if (colNo < colCount - 1)
        CalcCols(z, rowCount, colCount, S, k, colNo + 1);
}