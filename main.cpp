#include <iostream>
#include <vector>
#include <chrono>
#include <future>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// --- Крок 2: Власна функція для виведення масиву ---
void printArray(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Допоміжна функція генерації масиву випадкових чисел
vector<int> generateArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 1000 + 1; // Числа від 1 до 1000
    }
    return arr;
}

// --- Крок 3: Метод сортування (Бульбашка для прикладу) ---
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// --- Крок 6: Бінарний пошук ---
int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    // Ініціалізація генератора випадкових чисел
    srand(time(0)); 

    // --- Крок 4: Запуск не менше 5 разів для різних n ---
    vector<int> sizes = {1000, 2000, 5000, 10000, 20000};
    
    cout << "=== Таблиця часу сортування t=f(n) ===" << endl;
    cout << left << setw(15) << "К-сть (n)" 
         << setw(20) << "Бульбашка (мс)" 
         << setw(20) << "std::sort (мс)" << endl;
    cout << string(50, '-') << endl;

    for (int n : sizes) {
        vector<int> arr1 = generateArray(n);
        vector<int> arr2 = arr1; // Точна копія для іншого методу

        // Замір для Бульбашки
        auto start = high_resolution_clock::now();
        bubbleSort(arr1);
        auto stop = high_resolution_clock::now();
        auto durationBubble = duration_cast<milliseconds>(stop - start).count();

        // Замір для швидкого сортування C++ (QuickSort / IntroSort)
        start = high_resolution_clock::now();
        sort(arr2.begin(), arr2.end());
        stop = high_resolution_clock::now();
        auto durationQuick = duration_cast<milliseconds>(stop - start).count();

        cout << left << setw(15) << n 
             << setw(20) << durationBubble 
             << setw(20) << durationQuick << endl;
    }

    // --- Крок 5: Асинхронний код ---
    cout << "\n=== Крок 5: Асинхронне сортування ===" << endl;
    int asyncSize = 20000;
    vector<int> arrSync = generateArray(asyncSize);
    vector<int> arrAsync = arrSync;

    auto startSync = high_resolution_clock::now();
    bubbleSort(arrSync);
    auto stopSync = high_resolution_clock::now();
    cout << "Синхронно (" << asyncSize << " ел.): " 
         << duration_cast<milliseconds>(stopSync - startSync).count() << " мс\n";

    auto startAsync = high_resolution_clock::now();
    // Запускаємо сортування в окремому потоці
    future<void> result = async(launch::async, [&arrAsync]() {
        bubbleSort(arrAsync);
    });
    result.get(); // Чекаємо, поки потік завершить роботу
    auto stopAsync = high_resolution_clock::now();
    cout << "Асинхронно (" << asyncSize << " ел.): " 
         << duration_cast<milliseconds>(stopAsync - startAsync).count() << " мс\n";

    // --- Крок 6: Бінарний пошук ---
    cout << "\n=== Крок 6: Бінарний пошук ===" << endl;
    vector<int> searchArr = generateArray(20);
    sort(searchArr.begin(), searchArr.end()); // Масив має бути обов'язково відсортований!
    
    cout << "Згенерований відсортований масив:\n";
    printArray(searchArr);
    
    cout << "Введіть число для пошуку: ";
    int target;
    if (cin >> target) {
        int index = binarySearch(searchArr, target);
        if (index != -1)
            cout << "Елемент знайдено на індексі: " << index << endl;
        else
            cout << "Елемент не знайдено." << endl;
    }

    return 0;
}