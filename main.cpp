#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip> // For std::setw
#include <cstdlib> // For std::exit

using namespace std;

// Class to handle student records
class Student {
public:
    string name;
    string admNo;
    string attendance;
    string grade; // Added field for grade

    // Method to display student data
    void display() const {
        cout << setw(25) << left << name
             << setw(25) << left << admNo
             << setw(25) << left << attendance
             << setw(25) << left << grade << endl;
    }
};

// Function declarations
void addData();
void viewData();
void searchData();
void adminFunction();
void mainMenu();
void adminVerification();

// Function for adding student data
void addData() {
    system("cls");
    ofstream file("data.txt", ios::app);
    if (!file) {
        cout << "Failed to open data.txt" << endl;
        return;
    }

    Student student;
    cout << "Enter Student's Name: ";
    getline(cin, student.name);
    cout << "Enter Student's Admission Number (max 25 characters): ";
    getline(cin, student.admNo);
    cout << "Enter Attendance: ";
    getline(cin, student.attendance);
    cout << "Enter Overall Grade: ";
    getline(cin, student.grade);

    file << student.name << ","
         << student.admNo << ","
         << student.attendance << ","
         << student.grade << endl;

    file.close();

    cout << "Record added successfully.\n";

    adminFunction();
}

// Function for viewing student data
void viewData() {
    system("cls");
    ifstream file("data.txt");
    if (!file) {
        cout << "Failed to open data.txt" << endl;
        return;
    }

    cout << setw(25) << left << "Name"
         << setw(25) << left << "AdmNo"
         << setw(25) << left << "Attendance"
         << setw(25) << left << "Grade" << endl;
    cout << "----------------------------------------------------------------------------------------------\n";

    Student student;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, student.name, ',');
        getline(ss, student.admNo, ',');
        getline(ss, student.attendance, ',');
        getline(ss, student.grade, ',');

        student.display();
    }

    file.close();
    cout << "\n1. Add Record\n2. Search Record\n3. Exit\nEnter choice: ";
    int choice;
    cin >> choice;
    cin.ignore(); // To ignore any leftover newline character in the buffer

    switch (choice) {
        case 1:
            addData();
            break;
        case 2:
            searchData();
            break;
        case 3:
            adminFunction();
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            adminFunction();
            break;
    }
}

// Function for searching student data
void searchData() {
    system("cls");
    ifstream file("data.txt");
    if (!file) {
        cout << "Failed to open data.txt" << endl;
        return;
    }

    string searchAdmNo;
    cout << "Enter Admission Number to Search: ";
    getline(cin, searchAdmNo);

    cout << setw(25) << left << "Name"
         << setw(25) << left << "AdmNo"
         << setw(25) << left << "Attendance"
         << setw(25) << left << "Grade" << endl;
    cout << "----------------------------------------------------------------------------------------------\n";

    Student student;
    string line;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, student.name, ',');
        getline(ss, student.admNo, ',');
        getline(ss, student.attendance, ',');
        getline(ss, student.grade, ',');

        if (student.admNo == searchAdmNo) {
            student.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with Admission Number " << searchAdmNo << " not found.\n";
    }

    file.close();
    cout << "\n1. Search Again\n2. View All Records\n3. Exit\nEnter choice: ";
    int choice;
    cin >> choice;
    cin.ignore(); // To ignore any leftover newline character in the buffer

    switch (choice) {
        case 1:
            searchData();
            break;
        case 2:
            viewData();
            break;
        case 3:
            adminFunction();
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            adminFunction();
            break;
    }
}

// Function for the admin interface
void adminFunction() {
    system("cls");
    cout << "\n\t\t\t\t\t| Logged In as Admin |\n";
    cout << "1. Add Student Record\n";
    cout << "2. View Records\n";
    cout << "3. Search Record\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";

    int option;
    cin >> option;
    cin.ignore(); // To ignore any leftover newline character in the buffer

    switch (option) {
        case 1:
            addData();
            break;
        case 2:
            viewData();
            break;
        case 3:
            searchData();
            break;
        case 4:
            system("cls");
            cout << "Exiting the Program..." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            adminFunction();
            break;
    }
}

// Function for admin verification
void adminVerification() {
    system("cls");

    string password;
    cout << "Enter Password: ";
    getline(cin, password);

    if (password == "password") {
        adminFunction();
    } else {
        cout << "Incorrect password. Try again.\n";
        adminVerification();
    }
}

// Main menu function
void mainMenu() {
    system("cls");

    cout << "Login As:\n";
    cout << "1. Admin\n";
    cout << "2. Exit\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;
    cin.ignore(); // To ignore any leftover newline character in the buffer

    switch (choice) {
        case 1:
            adminVerification();
            break;
        case 2:
            system("cls");
            cout << "Exiting the Program..." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            mainMenu();
            break;
    }
}

// Main function
int main() {
    mainMenu();
    return 0;
}

