#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <clocale>
#include <iomanip>

using namespace std;

// Опис структури об'єкта
struct Teacher {
    string lastName;
    string firstName;
    string degree;
    int birthYear;
    int publications;
    double salary;
};

// Функція для додавання нового викладача
void addTeacher(string filename) {
    ofstream fout(filename, ios::app);
    if (!fout.is_open()) return;

    Teacher t;
    cout << "Прiзвище: "; cin >> t.lastName;
    cout << "Iм'я: "; cin >> t.firstName;
    cout << "Наукова ступiнь: "; cin >> t.degree;
    cout << "Рiк народження: "; cin >> t.birthYear;
    cout << "Кiлькiсть публiкацiй: "; cin >> t.publications;
    cout << "Заробiтна плата: "; cin >> t.salary;

    // Запис у файл через пробiл
    fout << t.lastName << " " << t.firstName << " " << t.degree << " " 
         << t.birthYear << " " << t.publications << " " << t.salary << endl;

    fout.close();
    cout << "Дані про викладача додано успішно!\n";
}

// Функція для перегляду всіх викладачів у файлі
void showAll(string filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "База даних порожня.\n";
        return;
    }

    Teacher t;
    cout << "\n" << setfill('=') << setw(80) << "=" << endl;
    cout << left << setw(15) << "Прiзвище" << setw(12) << "Iм'я" << setw(15) << "Ступiнь" 
         << setw(10) << "Рiк" << setw(10) << "Публ." << setw(10) << "Зарплата" << endl;
    cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;

    while (fin >> t.lastName >> t.firstName >> t.degree >> t.birthYear >> t.publications >> t.salary) {
        cout << left << setw(15) << t.lastName << setw(12) << t.firstName << setw(15) << t.degree 
             << setw(10) << t.birthYear << setw(10) << t.publications << setw(10) << t.salary << endl;
    }
    fin.close();
}

// Індивідуальна функція: Викладачі з публікаціями > 10
void showActiveScientists(string filename) {
    ifstream fin(filename);
    if (!fin.is_open()) return;

    Teacher t;
    bool found = false;
    cout << "\n--- Викладачі, які мають більше 10 публікацій ---\n";

    while (fin >> t.lastName >> t.firstName >> t.degree >> t.birthYear >> t.publications >> t.salary) {
        if (t.publications > 10) {
            cout << "- " << t.lastName << " " << t.firstName << " (" << t.publications << " публ.)" << endl;
            found = true;
        }
    }

    if (!found) cout << "Таких викладачів не знайдено.\n";
    fin.close();
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    string dbName = "teachers_db.txt";
    int choice;

    do {
        cout << "\n======= ТЕРМIНАЛ: ВИКЛАДАЧІ =======";
        cout << "\n1. Додати нового викладача";
        cout << "\n2. Показати повний список";
        cout << "\n3. Вивести вчених (публiкацiї > 10)";
        cout << "\n0. Вихiд";
        cout << "\nВибiр: ";
        cin >> choice;

        switch (choice) {
            case 1: addTeacher(dbName); break;
            case 2: showAll(dbName); break;
            case 3: showActiveScientists(dbName); break;
            case 0: cout << "Програма завершена.\n"; break;
            default: cout << "Неправильний вибiр!\n";
        }
    } while (choice != 0);

    return 0;
}
