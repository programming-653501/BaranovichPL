#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

int **create_massiv(int n){
    int **a = new int *[n];
    for (int i = 0; i < n; ++i)
        a[i] = new int [n];

    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n ; ++j)
            a[i][j] = rand();

    return a;
}

void delete_massiv(int **a, int n){
    for (int i = 0; i < n; ++i)
        delete a[i];
    delete a;
}

int find_position(int **a, int n){
    int Max = a[0][0], positionMax = 0;
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n; ++j)
            if (a[i][j] > Max){
                Max = a[i][j];
                positionMax = i;
            }

    return positionMax + 1;
}

void write_massiv(int **a, int n, int m){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            cout << a[i][j] << "\t";
        cout << endl;
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");

    int n;

    cout << "Введите размер массива: ";
    cin >> n;

    int **a = create_massiv(n), positionMax = find_position(a, n);

    cout << "\nНачальный массив:\n";
    write_massiv(a, n - 1, n);

    for (int i = n - 1; i > positionMax; --i)
        for (int j = 0; j < n; ++j)
            a[i][j] = a[i - 1][j];
    for (int j = 0; j < n; ++j)
        a[positionMax][j] = 0;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j)
            swap(a[i][j], a[j][i]);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n - i; ++j)
            swap(a[i][j], a[n - j - 1][n - i - 1]);

    cout << "\nРезультирующий массив:\n";
    write_massiv(a, n, n);

    delete_massiv(a, n);

    return 0;
}
