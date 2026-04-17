#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>

using namespace std;

// Функція для виділення пам'яті
int** allocateMemory(int n) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    return matrix;
}

// Функція для звільнення пам'яті
void freeMemory(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Заповнення матриці випадковими числами [-10-V ... 10+V]
void fillMatrix(int** matrix, int n, int v) {
    int minRange = -10 - v;
    int maxRange = 10 + v;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % (maxRange - minRange + 1) + minRange;
        }
    }
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

// Пошук максимального значення по модулю у всій матриці
int findMaxAbs(int** matrix, int n) {
    int maxAbs = abs(matrix[0][0]);
    int actualVal = matrix[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (abs(matrix[i][j]) > maxAbs) {
                maxAbs = abs(matrix[i][j]);
                actualVal = matrix[i][j];
            }
        }
    }
    return actualVal;
}

// Частина 1: Сектор 4 (нижній трикутник без діагоналей)
int processSector4(int** matrix, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Умова сектора 4: нижче головної (i > j) ТА нижче побічної (i + j > n - 1)
            if (i > j && (i + j) > (n - 1)) {
                if (matrix[i][j] % 2 == 0) {
                    count++;
                }
            }
        }
    }
    return count;
}

// Частина 2: Сектор 7 (верхній трикутник включаючи діагоналі)
int processSector7(int** matrix, int n, int replacementValue) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Умова сектора 7: вище головної (i <= j) ТА вище побічної (i + j <= n - 1)
            if (i <= j && (i + j) <= (n - 1)) {
                count++;
                matrix[i][j] = replacementValue;
            }
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    srand(static_cast<unsigned>(time(0)));

    int n, v = 6; // Ваш варіант
    cout << "Введiть розмiр квадратної матрицi n: ";
    cin >> n;

    int** matrix = allocateMemory(n);
    fillMatrix(matrix, n, v);

    cout << "\nПочаткова матриця:\n";
    printMatrix(matrix, n);

    // Обробка сектора 4
    int evenCount = processSector4(matrix, n);
    cout << "\n1. Кiлькiсть парних чисел у секторi 4: " << evenCount << endl;

    // Обробка сектора 7
    int maxVal = findMaxAbs(matrix, n);
    cout << "Максимальне по модулю значення матрицi: " << maxVal << endl;
    
    int sector7Count = processSector7(matrix, n, maxVal);
    cout << "2. Кiлькiсть елементiв у секторi 7: " << sector7Count << " (замiнено на " << maxVal << ")" << endl;

    cout << "\nМатриця пiсля модифiкацiї сектора 7:\n";
    printMatrix(matrix, n);

    freeMemory(matrix, n);
    return 0;
}
