#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ====================== STUDENT CLASS ======================

class Student {
public:
    string name;
    string indexNumber;

    Student(string n = "", string i = "") {
        name = n;
        indexNumber = i;
    }

    void saveToFile() {
        ofstream file("students.txt", ios::app);
        file << indexNumber << "," << name << endl;
        file.close();
    }
};

// ====================== GLOBAL FUNCTIONS ======================

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        size_t pos = line.find(",");
        string index = line.substr(0, pos);
        string name = line.substr(pos + 1);
        students.push_back(Student(name, index));
    }

    file.close();
    return students;
}

void registerStudent() {
    string name, index;
    cout << "Enter student name: ";
    getline(cin, name);
    cout << "Enter index number: ";
    getline(cin, index);

    Student s(name, index);
    s.saveToFile();

    cout << "Student registered successfully.\n";
}

void viewStudents() {
    vector<Student> students = loadStudents();
    cout << "\n--- Registered Students ---\n";
    for (auto s : students) {
        cout << s.indexNumber << " - " << s.name << endl;
    }
}

void searchStudent() {
    string searchIndex;
    cout << "Enter index number to search: ";
    getline(cin, searchIndex);

    vector<Student> students = loadStudents();
    for (auto s : students) {
        if (s.indexNumber == searchIndex) {
            cout << "Found: " << s.name << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

// ====================== ATTENDANCE SESSION ======================

void createSession() {
    string courseCode, date, startTime, duration;

    cout << "Enter course code: ";
    getline(cin, courseCode);
    cout << "Enter date (YYYY_MM_DD): ";
    getline(cin, date);
    cout << "Enter start time: ";
    getline(cin, startTime);
    cout << "Enter duration (hours): ";
    getline(cin, duration);

    string filename = "session_" + courseCode + "_" + date + ".txt";
    ofstream file(filename);

    file << "Course: " << courseCode << endl;
    file << "Date: " << date << endl;
    file << "Start Time: " << startTime << endl;
    file << "Duration: " << duration << endl;
    file << "---------------------------------\n";

    vector<Student> students = loadStudents();

    for (auto s : students) {
        file << s.indexNumber << "," << s.name << ",Absent\n";
    }

    file.close();
    cout << "Session created successfully.\n";
}

void markAttendance() {
    string filename;
    cout << "Enter session filename: ";
    getline(cin, filename);

    ifstream file(filename);
    if (!file) {
        cout << "Session file not found.\n";
        return;
    }

    vector<string> lines;
    string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    for (size_t i = 5; i < lines.size(); i++) {
        cout << lines[i] << endl;

        cout << "Enter status (Present/Late/Absent): ";
        string status;
        getline(cin, status);

        size_t lastComma = lines[i].rfind(",");
        lines[i] = lines[i].substr(0, lastComma + 1) + status;
    }

    ofstream outFile(filename);
    for (auto l : lines) {
        outFile << l << endl;
    }
    outFile.close();

    cout << "Attendance updated successfully.\n";
}

void displaySessionReport() {
    string filename;
    cout << "Enter session filename: ";
    getline(cin, filename);

    ifstream file(filename);
    if (!file) {
        cout << "Session file not found.\n";
        return;
    }

    string line;
    int present = 0, absent = 0, late = 0;

    cout << "\n--- Attendance Report ---\n";

    while (getline(file, line)) {
        cout << line << endl;

        if (line.find("Present") != string::npos) present++;
        if (line.find("Absent") != string::npos) absent++;
        if (line.find("Late") != string::npos) late++;
    }

    file.close();

    cout << "\nSummary:\n";
    cout << "Present: " << present << endl;
    cout << "Absent: " << absent << endl;
    cout << "Late: " << late << endl;
}

// ====================== MAIN MENU ======================

void menu() {
    cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
    cout << "1. Register Student\n";
    cout << "2. View Students\n";
    cout << "3. Search Student\n";
    cout << "4. Create Session\n";
    cout << "5. Mark Attendance\n";
    cout << "6. Session Report\n";
    cout << "0. Exit\n";
    cout << "Choose option: ";
}

int main() {
    int choice;

    do {
        menu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: createSession(); break;
            case 5: markAttendance(); break;
            case 6: displaySessionReport(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid option.\n";
        }

    } while (choice != 0);

    return 0;
}