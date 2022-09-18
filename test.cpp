// Cleaning.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
using namespace std;

double** CleaningCycle(double mu, double fi, int size)
{
    // вычислим значения, зависящие только от номера столбца,
    // (их size различных) и сохраним во временном массиве
    double* tmpArr = new double[size];
    for (int j = 0; j < size; j++)
        tmpArr[j] = (-2 - (j - 3) * (j - 3)) * (j - 5.7);
    // вычислим матрицу
    double** Matrix = new double* [size];
    long fact = 1;
    double arg = mu;
    for (int i = 0; i < size; i++)
    {
        double const_i = cos(arg) / fact;
        Matrix[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            // таким образом, n квадрат раз выполняется только единственная операция умножения
            Matrix[i][j] = const_i * tmpArr[j];
        }
        arg *= fi;
        fact *= (i + 1);
    }
    // освобождаем память, занятую временным массивом
    delete[] tmpArr;
    return Matrix;
}

int main()
{
    double** A = CleaningCycle(1.2, 0.85, 5);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << A[i][j] << ' ';
        }
        cout << endl;
    }
}
