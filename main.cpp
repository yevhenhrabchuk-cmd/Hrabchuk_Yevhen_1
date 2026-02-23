#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <future>

using namespace std;
using namespace chrono;


void printArray(const vector<int>& arr) {
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}


vector<int> generateArray(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 10000);

    for (int i = 0; i < n; i++)
        arr[i] = dist(gen);

    return arr;
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        swap(arr[i], arr[minIndex]);
    }
}

void shellSort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
}

void countingSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);

    for (int num : arr)
        count[num]++;

    int index = 0;
    for (int i = 0; i <= maxVal; i++)
        while (count[i]--)
            arr[index++] = i;
}

int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

long long measureSort(void(*sortFunc)(vector<int>&), vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto stop = high_resolution_clock::now();

    return duration_cast<microseconds>(stop - start).count();
}

int main() {

    vector<int> sizes = {18, 160, 1024, 4096, 32600, 128000};

    for (int n : sizes) {
        cout << "\nSize: " << n << endl;
        vector<int> arr = generateArray(n);

        long long t1 = measureSort(selectionSort, arr);
        long long t2 = measureSort(shellSort, arr);
        long long t3 = measureSort(countingSort, arr);

        cout << "Selection: " << t1 << " us\n";
        cout << "Shell:     " << t2 << " us\n";
        cout << "Counting:  " << t3 << " us\n";
    }

    cout << "\nAsync test (n = 128000)\n";
    vector<int> arr = generateArray(128000);

    auto f1 = async(launch::async, measureSort, selectionSort, arr);
    auto f2 = async(launch::async, measureSort, shellSort, arr);
    auto f3 = async(launch::async, measureSort, countingSort, arr);

    cout << "Selection async: " << f1.get() << " us\n";
    cout << "Shell async:     " << f2.get() << " us\n";
    cout << "Counting async:  " << f3.get() << " us\n";

    countingSort(arr);
    int target;
    cout << "\nEnter element to search: ";
    cin >> target;

    int result = binarySearch(arr, target);

    if (result != -1)
        cout << "Element found at index: " << result << endl;
    else
        cout << "Element not found\n";

    return 0;
}