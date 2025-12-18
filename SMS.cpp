#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;

class Student {
public:
    int roll;
    string name;
    float cgpa;
};


//* Save Students to file
void saveStudents(const vector<Student>& students) {
    ofstream out("students.txt");
    for (const auto& s : students) {
        out << s.roll << "," << s.name << "," << s.cgpa << endl;
    }
    out.close();
}


//* Load Students from file
void loadStudents(vector<Student>& students) {
    ifstream in("students.txt");

    if (!in) return;

    Student s;
    string row;

    while (getline(in, row)) {
        stringstream ss(row);
        string roll, name, cgpa;

        getline(ss, roll, ',');
        getline(ss, name, ',');
        getline(ss, cgpa);


        s.roll = stoi(roll);
        s.name = name;
        s.cgpa = stof(cgpa);

        students.push_back(s);
    }
    in.close();
}


//? Add Student
void addStudent(vector<Student>& students) {
    Student s;

    cout << "Enter Roll No: ";
    cin >> s.roll;

    for (auto& it : students) {
        if (s.roll == it.roll) {
            cout << "\nRoll already exists!\n";
            return;
        }
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);

    cout << "Enter CGPA: ";
    cin >> s.cgpa;

    students.push_back(s);
    
    sort(students.begin(), students.end(), [](auto& s1, auto& s2) {
        return s1.roll < s2.roll;
        });
    saveStudents(students);
    cout << "Student added successfully!\n";
}

//? View Student
void viewStudent(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student found.\n";
        return;
    }

    cout << "\nRoll\tName\tCGPA\n";

    for (const auto& s : students) {
        cout << s.roll << "\t" << s.name << "\t" << s.cgpa << endl;
    }
}


//? Search Student
void searchStudent(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;

    for (const auto& s : students) {
        if (s.roll == roll) {
            cout << "\nStudent Found:\n";
            cout << "Roll: " << s.roll << endl;
            cout << "Name: " << s.name << endl;
            cout << "CGPA: " << s.cgpa << endl;
            return;
        }
    }
    cout << "\nStudent not found.\n";
}


//? Delete Student
void deleteStudent(vector<Student>& students) {
    if (students.empty()) {
        cout << "\nNo students available.\n";
        return;
    }

    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->roll == roll) {
            students.erase(it);
            saveStudents(students);
            cout << "\nStudent deleted successfully!\n";
            return;
        }
    }
    cout << "\nStudent not found.\n";
}


//? Update Student
void updateStudent(vector<Student>& students) {
    if (students.empty()) {
        cout << "\nNo students available.\n";
        return;
    }

    int roll;
    cout << "Enter roll number to update: ";
    cin >> roll;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->roll == roll) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, it->name);

            cout << "Enter new CGPA: ";
            cin >> it->cgpa;

            saveStudents(students);
            cout << "\nStudent updated successfully!\n";
            return;
        }
    }
    cout << "\nStudent not found.\n";
}


//? Sort Student
void sortStudents(vector<Student>& students) {
    int choice;
    cout << "\nSort By -\n";
    cout << "1. Roll\n";
    cout << "2. Name\n";
    cout << "3. CGPA\n";
    cout << "Enter your choice:";
    cin >> choice;

    switch (choice)
    {
    case 1:
        sort(students.begin(), students.end(), [](auto& s1, auto& s2) {
            return s1.roll < s2.roll;
            });
        cout << "\nStudents sorted successfully!\n";
        break;
    case 2:
        sort(students.begin(), students.end(), [](auto& s1, auto& s2) {
            return s1.name < s2.name;
            });
        cout << "\nStudents sorted successfully!\n";
        break;
    case 3:
        sort(students.begin(), students.end(), [](auto& s1, auto& s2) {
            return s1.cgpa < s2.cgpa;
            });
        cout << "\nStudents sorted successfully!\n";
        break;
    default:
        cout << "\nInvalid Choice!\n";
    }

}


//? Show Menu
void showMenu() {
    cout << "\n====== Student Management System ======\n";
    cout << "1. Add Student\n";
    cout << "2. View Student\n";
    cout << "3. Search Student\n";
    cout << "4. Delete Student\n";
    cout << "5. Update Student\n";
    cout << "6. Sort Students\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<Student> students;
    int choice;

    loadStudents(students);

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent(students);
            break;
        case 2:
            viewStudent(students);
            break;
        case 3:
            searchStudent(students);
            break;
        case 4:
            deleteStudent(students);
            break;
        case 5:
            updateStudent(students);
            break;
        case 6:
            sortStudents(students);
            break;
        case 7:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "invalid Choice! Try again.";
        }
    } while (choice != 7);

    return 0;
}