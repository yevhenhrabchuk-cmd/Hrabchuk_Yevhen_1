#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <windows.h> // Для кирилиці

using namespace std;

// Функція для очищення слова від знаків пунктуації та приведення до нижнього регістру
string cleanWord(string word) {
    string cleaned = "";
    for (char c : word) {
        if (!ispunct(static_cast<unsigned char>(c))) {
            cleaned += to_lower(c); // Спрощена логіка, для кирилиці краще залишати як є
        }
    }
    // Якщо працюєте з кирилицею, краще просто прибрати кому/крапку в кінці
    if (!word.empty() && ispunct(static_cast<unsigned char>(word.back()))) {
        word.pop_back();
    }
    return word;
}

int main() {
    // Налаштування кодування для української мови
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Помилка: файл input.txt не знайдено!" << endl;
        return 1;
    }

    map<string, int> wordFrequency;
    string word;

    // Зчитуємо кожне слово з файлу
    while (inputFile >> word) {
        word = cleanWord(word); // Очищуємо від знаків пунктуації
        if (!word.empty()) {
            wordFrequency[word]++;
        }
    }
    inputFile.close();

    // Пошук слова з максимальною частотою
    string mostFrequentWord = "";
    int maxCount = 0;

    for (auto const& [currentWord, count] : wordFrequency) {
        if (count > maxCount) {
            maxCount = count;
            mostFrequentWord = currentWord;
        }
    }

    // Запис результату у файл
    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        if (maxCount > 0) {
            outputFile << "Слово, що зустрічається найчастіше: " << mostFrequentWord << endl;
            outputFile << "Кількість повторень: " << maxCount << endl;
            cout << "Результат успішно записано в output.txt" << endl;
        } else {
            outputFile << "Файл порожній." << endl;
        }
        outputFile.close();
    }

    return 0;
}
