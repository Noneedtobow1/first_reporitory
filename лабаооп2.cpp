#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

// ýòî ëàáà 2 ïî òåìå ìàïû è âåêòîðà
// ïèøó ýòîò êîììåíò ÷òîáû ñäåëàòü èçìåíåíèÿ â âåòêå main

// äîáàâëÿþ êîììåíò ÷òîáû ñäåëàòü ñëèÿíèå âåòîê

// merge conflict решён

struct Student {
    int id;                
    string name;           
    vector<double> grades; 

    void display() const {
        cout << "ID: " << id << " | Èìÿ: " << name << " | Îöåíêè: [ ";
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
    cout << "\nÂâåäèòå ID ñòóäåíòà: ";
    cin >> newStudent.id;

    if (studentMap.find(newStudent.id) != studentMap.end()) {
        cout << "Îøèáêà: Ñòóäåíò ñ ID " << newStudent.id << " óæå ñóùåñòâóåò!\n";
        return;
    }

    cout << "Ââåäèòå èìÿ ñòóäåíòà: ";
    cin.ignore();
    getline(cin, newStudent.name);

    int gradesCount;
    cout << "Ââåäèòå êîëè÷åñòâî îöåíîê: ";
    cin >> gradesCount;

    cout << "Ââåäèòå îöåíêè ÷åðåç ïðîáåë: ";
    for (int i = 0; i < gradesCount; ++i) {
        double g;
        cin >> g;
        newStudent.grades.push_back(g);
    }

    students.push_back(newStudent);
    studentMap[newStudent.id] = newStudent;

    cout << "Ñòóäåíò óñïåøíî äîáàâëåí!\n";
}

void printAllStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\nÑïèñîê ñòóäåíòîâ ïóñò.\n";
        return;
    }

    cout << "\n--- Ñïèñîê âñåõ ñòóäåíòîâ ---\n";
    for (const auto& student : students) {
        student.display();
        cout << "\n";
    }
}

void calculateAverage(const map<int, Student>& studentMap) {
    int id;
    cout << "\nÂâåäèòå ID ñòóäåíòà äëÿ ðàñ÷åòà ñðåäíåé îöåíêè: ";
    cin >> id;

    auto it = studentMap.find(id);
    if (it != studentMap.end()) {
        double avg = it->second.getAverageGrade();
        cout << "Ñòóäåíò: " << it->second.name
            << " | Ñðåäíÿÿ îöåíêà: " << fixed << setprecision(2) << avg << "\n";
    }
    else {
        cout << "Ñòóäåíò ñ ID " << id << " íå íàéäåí.\n";
    }
}

void searchByGrade(const vector<Student>& students) {
    double targetGrade;
    cout << "\nÂâåäèòå èñêîìóþ îöåíêó: ";
    cin >> targetGrade;

    bool found = false;
    cout << "\n--- Ñòóäåíòû ñ îöåíêîé " << targetGrade << " ---\n";
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
        cout << "Ñòóäåíòû ñ òàêîé îöåíêîé íå íàéäåíû.\n";
    }
}

void searchById(const map<int, Student>& studentMap) {
    int id;
    cout << "\nÂâåäèòå ID ñòóäåíòà äëÿ ïîèñêà: ";
    cin >> id;

    auto it = studentMap.find(id);
    if (it != studentMap.end()) {
        cout << "Ñòóäåíò íàéäåí: ";
        it->second.display();
        cout << "\n";
    }
    else {
        cout << "Ñòóäåíò ñ ID " << id << " íå íàéäåí.\n";
    }
}

void addGradeToStudent(vector<Student>& students, map<int, Student>& studentMap) {
    int id;
    cout << "\nÂâåäèòå ID ñòóäåíòà äëÿ äîáàâëåíèÿ îöåíêè: ";
    cin >> id;

    auto it = studentMap.find(id);
    if (it != studentMap.end()) {
        double newGrade;
        cout << "Ââåäèòå íîâóþ îöåíêó: ";
        cin >> newGrade;

        it->second.grades.push_back(newGrade);

        for (auto& student : students) {
            if (student.id == id) {
                student.grades.push_back(newGrade);
                break;
            }
        }
        cout << "Îöåíêà óñïåøíî äîáàâëåíà!\n";
    }
    else {
        cout << "Ñòóäåíò ñ ID " << id << " íå íàéäåí.\n";
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<Student> students;
    map<int, Student> studentMap;

    Student s1 = { 1, "Ïðîñòî Ïàðåíü", {8.5, 9.0, 7.5} };
    Student s2 = { 2, "×èñòî Âàñÿ", {10.0, 9.5, 10.0} };

    students.push_back(s1);
    students.push_back(s2);

    studentMap[s1.id] = s1;
    studentMap[s2.id] = s2;

    int choice;
    do {
        cout << "ÌÅÍÞ*****\n"
            << "1. Äîáàâèòü ñòóäåíòà\n"
            << "2. Ïðîñìîòðåòü âñåõ ñòóäåíòîâ\n"
            << "3. Ðàññ÷èòàòü ñðåäíèé áàëë ñòóäåíòà ïî ID\n"
            << "4. Íàéòè ñòóäåíòîâ ïî êîíêðåòíîé îöåíêå\n"
            << "5. Íàéòè ñòóäåíòà ïî ID\n"
            << "6. Äîáàâèòü íîâóþ îöåíêó ñòóäåíòó\n"
            << "0. Âûéòè èç ïðîãðàììû\n"
            << "Âûáåðèòå äåéñòâèå: ";
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
            cout << "Íåâåðíûé âûáîð. Ïîïðîáóéòå ñíîâà.\n";
        }
    } while (choice != 0);

    return 0;
}