#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

enum Speciality { ITIS, RE, KN, KI, PZ };
string speciality_str[] = { "Інформатика", "Радіоелектроніка", "Комп'ютерні науки", "Комп'ютерна інженерія", "Програмне забезпечення" };

struct Student {
    string surname;
    int course;
    Speciality speciality;
    int grade_math;
    int grade_profile;

    double average_grade() const {
        return grade_profile; // Використовуємо оцінку з профільного предмета для сортування
    }
};

void Create(Student* S, const int N);
void Print(const Student* S, const int N);
void sort_students(Student* S, int N);
int binary_search(const Student* S, int N, const string& surname, Speciality speciality, double average);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Student* S = new Student[N];
    Create(S, N);
    sort_students(S, N);
    Print(S, N);

    string search_surname;
    Speciality search_speciality;
    double search_average;

    cout << "Введіть прізвище для пошуку: "; cin >> search_surname;
    cout << "Введіть спеціальність (0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки, 3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): ";
    int speciality_input;
    cin >> speciality_input;
    search_speciality = (Speciality)speciality_input;
    cout << "Введіть середній бал: "; cin >> search_average;

    int index = binary_search(S, N, search_surname, search_speciality, search_average);

    if (index != -1) {
        cout << "Студент знайдений на позиції: " << index + 1 << endl;
    }
    else {
        cout << "Студент не знайдений." << endl;
    }

    delete[] S;
    return 0;
}

void Create(Student* S, const int N) {
    for (int i = 0; i < N; i++) {
        int speciality;
        cout << "Номер студента: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Прізвище: "; getline(cin, S[i].surname);
        cout << "Курс: "; cin >> S[i].course;
        cout << "Спеціальність (0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки, 3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): ";
        cin >> speciality;
        S[i].speciality = (Speciality)speciality;
        cout << "Оцінка з математики: "; cin >> S[i].grade_math;
        cout << "Оцінка з профільного предмета: "; cin >> S[i].grade_profile;
        cout << endl;
    }
}

void Print(const Student* S, const int N) {
    cout << "======================================================================" << endl;
    cout << "|  №  |   Прізвище   |  Курс  |     Спеціальність     |  Профільний  |" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "|" << setw(4) << left << i + 1 << " ";
        cout << "|" << setw(14) << left << S[i].surname;
        cout << "|" << setw(8) << left << S[i].course;
        cout << "|" << setw(23) << left << speciality_str[S[i].speciality];
        cout << "|" << setw(12) << left << S[i].grade_profile << "|" << endl;
    }
    cout << "======================================================================" << endl << endl;
}

void sort_students(Student* S, int N) {
    sort(S, S + N, [](const Student& a, const Student& b) {
        if (a.average_grade() != b.average_grade()) {
            return a.average_grade() > b.average_grade();  // більший середній бал йде першим
        }
        if (a.speciality != b.speciality) {
            return a.speciality < b.speciality;
        }
        return a.surname < b.surname;
        });
}

int binary_search(const Student* S, int N, const string& surname, Speciality speciality, double average) {
    int left = 0, right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        const Student& student = S[mid];

        if (student.speciality < speciality || (student.speciality == speciality && student.average_grade() < average) ||
            (student.speciality == speciality && student.average_grade() == average && student.surname < surname)) {
            left = mid + 1;
        }
        else if (student.speciality > speciality || (student.speciality == speciality && student.average_grade() > average) ||
            (student.speciality == speciality && student.average_grade() == average && student.surname > surname)) {
            right = mid - 1;
        }
        else {
            return mid;
        }
    }

    return -1; // не знайдений
}
