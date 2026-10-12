#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

// это лаба 2 по теме мапы и вектора
// пишу этот коммент чтобы сделать изменения в ветке main

// добавляю коммент чтобы сделать слияние веток

// коммент для конфликта с feature

struct Student {
    int id;                
    string name;           
    vector<double> grades; 

    void display() const {
        cout << "ID: " << id << " | Имя: " << name << " | Оценки: [ ";
        for (double grade : grades) {
            cout << grade << " ";
        }
        cout << "]";
    }

    double getAverageGrade() const {
        if (grades.empty()) return 0.0;

        double sum = 0.0;
        for (double g : grades) {
            sum += g;
        }
        return sum / grades.size();
    }
};

void addStudent(vector<Student>& students, map<int, Student>& studentMap) {
    Student newStudent;
    cout << "\nВведите ID студента: ";
    cin >> newStudent.id;

    if (studentMap.find(newStudent.id) != studentMap.end()) {
        cout << "Ошибка: Студент с ID " << newStudent.id << " уже существует!\n";
        return;
    }

    cout << "Введите имя студента: ";
    cin.ignore();
    getline(cin, newStudent.name);

    int gradesCount;
    cout << "Введите количество оценок: ";
    cin >> gradesCount;

    cout << "Введите оценки через пробел: ";
    for (int i = 0; i < gradesCount; ++i) {
        double g;
        cin >> g;
        newStudent.grades.push_back(g);
    }

    students.push_back(newStudent);
    studentMap[newStudent.id] = newStudent;

    cout << "Студент успешно добавлен!\n";
}

void printAllStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\nСписок студентов пуст.\n";
        return;
    }

    cout << "\n--- Список всех студентов ---\n";
    for (const auto& student : students) {
        student.display();
        cout << "\n";
    }
}

void calculateAverage(const map<int, Student>& studentMap) {
    int id;
    cout << "\nВведите ID студента для расчета средней оценки: ";
    cin >> id;

    auto it = studentMap.find(id);
    if (it != studentMap.end()) {
        double avg = it->second.getAverageGrade();
        cout << "Студент: " << it->second.name
            << " | Средняя оценка: " << fixed << setprecision(2) << avg << "\n";
    }
    else {
        cout << "Студент с ID " << id << " не найден.\n";
    }
}

void searchByGrade(const vector<Student>& students) {
    double targetGrade;
    cout << "\nВведите искомую оценку: ";
    cin >> targetGrade;

    bool found = false;
    cout << "\n--- Студенты с оценкой " << targetGrade << " ---\n";
    for (const auto& student : students) {
        bool hasGrade = false;

        for (double g : student.grades) {
            if (g == targetGrade) {
                hasGrade = true;
                break;
            }
        }

        if (hasGrade) {
            student.display();
            cout << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Студенты с такой оценкой не найдены.\n";
    }
}

void searchById(const map<int, Student>& studentMap) {
    int id;
    cout << "\nВведите ID студента для поиска: ";
    cin >> id;

    auto it = studentMap.find(id);
    if (it != studentMap.end()) {
        cout << "Студент найден: ";
        it->second.display();
        cout << "\n";
    }
    else {
        cout << "Студент с ID " << id << " не найден.\n";
    }
}

void addGradeToStudent(vector<Student>& students, map<int, Student>& studentMap) {
    int id;
    cout << "\nВведите ID студента для добавления оценки: ";
    cin >> id;

    auto it = studentMap.find(id);
    if (it != studentMap.end()) {
        double newGrade;
        cout << "Введите новую оценку: ";
        cin >> newGrade;

        it->second.grades.push_back(newGrade);

        for (auto& student : students) {
            if (student.id == id) {
                student.grades.push_back(newGrade);
                break;
            }
        }
        cout << "Оценка успешно добавлена!\n";
    }
    else {
        cout << "Студент с ID " << id << " не найден.\n";
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<Student> students;
    map<int, Student> studentMap;

    Student s1 = { 1, "Просто Парень", {8.5, 9.0, 7.5} };
    Student s2 = { 2, "Чисто Вася", {10.0, 9.5, 10.0} };

    students.push_back(s1);
    students.push_back(s2);

    studentMap[s1.id] = s1;
    studentMap[s2.id] = s2;

    int choice;
    do {
        cout << "МЕНЮ*****\n"
            << "1. Добавить студента\n"
            << "2. Просмотреть всех студентов\n"
            << "3. Рассчитать средний балл студента по ID\n"
            << "4. Найти студентов по конкретной оценке\n"
            << "5. Найти студента по ID\n"
            << "6. Добавить новую оценку студенту\n"
            << "0. Выйти из программы\n"
            << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent(students, studentMap);
            break;
        case 2:
            printAllStudents(students);
            break;
        case 3:
            calculateAverage(studentMap);
            break;
        case 4:
            searchByGrade(students);
            break;
        case 5:
            searchById(studentMap);
            break;
        case 6:
            addGradeToStudent(students, studentMap);
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}