#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "include/json.hpp"

// shortcut to not add std in the code
using namespace std;
using json = nlohmann::json;

struct Assignment
{
    string assignment;
    int grade;
};

struct Class
{
    string className;
    string teacher;
    vector<Assignment> assignments;
};

struct Student
{
    string name;
    double gpa;
    vector<Class> classes;
};

// map<string, Student> studentMap();
void viewInfo(const map<string, Student>& studentData);
void modifyStudentData(map<string, Student>& students);
void updateStudentGrade();
void createAssignment();
void calculateGPA();
void exitProgram();
void writeDataToFile(const map<string, Student>& students);


map<string, Student> studentMap()
{
    map<string, Student> students;
    // load JSON file that is a map of students with additional data
    // open file
    ifstream inputFile("studentData.json");

    // checks for file not being able to open
    if (!inputFile.is_open()) {
        cerr << "File can't be opened." << endl;
        // return empty map
        return students;
    }

    json j;
    inputFile >> j;

    for (const auto& studentData : j["students"]) {
        Student student;
        student.name = studentData["name"];
        student.gpa = studentData["gpa"];

        for (const auto& classData : studentData["classes"]) {
            Class classInfo;
            classInfo.className = classData["className"];
            classInfo.teacher = classData["teacher"];

            for (const auto& assignmentData : classData["assignments"]) {
                Assignment assignment;
                assignment.assignment = assignmentData["assignment"];
                assignment.grade = assignmentData["grade"];
                classInfo.assignments.push_back(assignment);
            }
            student.classes.push_back(classInfo);
        }
        students[student.name] = student;
    }

    //close the file
    inputFile.close();

    // return the map
    return students;
}

void menu()
{
    // give a list of options for the user
    // menu should include:
    map<string, Student> students = studentMap();
    int choice;

    do
    {
        cout << "Menu Options:\n";
        cout << "1. View Student Info\n";
        cout << "2. Modify Student Data\n";
        cout << "3. Update Student Grade\n";
        cout << "4. Create Student Assignment\n";
        cout << "5. Calculate GPA\n";
        cout << "6. Exit\n";

        cout << "What would you like to do: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            /*
            1. viewing student info
            a. view total students with names and gpa
            b. view student by name with detailed info
            */
            viewInfo(students);
            break;
        case 2:
            /*
            2. modify student
                a. (takes name input and adds a spot in the json file)
                b. or delete student
            */
            modifyStudentData(students);
            break;

        case 3:
        // 3. updating student grade
            updateStudentGrade();

        // 4. create student assignment
            createAssignment();
            break;

        case 5:
        /*
        5. calculate gpa (by iterating through assignment grades). this also updates the json file
        */
            calculateGPA();
            break;

        case 6:
        /*
        6. exit (ends program)
            a. Do you want to save? (yes saves working file to json. no doesn't do a final save)
        */
            exitProgram();
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6); 
}

void viewInfo(const map<string, Student>& studentData)
{
    int choice;
    cout << "1. View all students" << endl;
    cout << "2. View individual student" << endl;
    cout << "Enter your choice: ";

    cin >> choice;

    if (choice == 1) {
        cout << "All Students:" << endl;
        for (const auto& student : studentData) {
            string name = student.first;
            double gpa = student.second.gpa;
            cout << "Name: " << name << "......." << "GPA: " << gpa << endl;
        }
    } else if (choice == 2) {
        cout << "Enter the student's name: ";
        string studentName;
        cin.ignore();
        getline(cin, studentName);

        if (studentData.find(studentName) != studentData.end()) {
            const Student& studentInfo = studentData.at(studentName);

            cout << studentInfo.name << endl;
            cout << "GPA: " << studentInfo.gpa << endl;
            cout << "Class Info:" << endl;

            for (const auto& course : studentInfo.classes) {
                cout << course.className << "|" << course.teacher << endl;
                cout << "Assignments: " << endl;

                for (const auto& assignment : course.assignments) {
                    cout << " > " << assignment.assignment << "........" << assignment.grade << endl;
                }
            }
        } else {
            cout << "The student could not be found." << endl;
        }
    } else {
        cout << "That is not a valid choice! Try again." << endl;
    }
}

void modifyStudentData(map<string, Student>& students)
{
    int choice;
    cout << "1. Add a new student" << endl;
    cout << "2. Delete a student" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        Student newStudent;
        cout << "Enter the student's name: ";
        cin.ignore();
        getline(cin, newStudent.name);
        cout << "Enter student's GPA: ";
        cin >> newStudent.gpa;

        students[newStudent.name] = newStudent;
        cout << "Student added!" << endl;
    } else if (choice == 2) {
        cout << "Enter the name of the student to delete: ";
        string studentName;
        cin.ignore();
        getline(cin, studentName);

        if (students.erase(studentName)) {
            cout << "Student has been deleted!" << endl;
        } else {
            cout << "Student could not be found." << endl;
        }
    } else {
        cout << "Invalid choice! Try again." << endl;
    }
    writeDataToFile(students);
}

void updateStudentGrade()
{

}

void createAssignment()
{

}

void calculateGPA()
{

}

void exitProgram()
{

}

void writeDataToFile(const map<string, Student>& students)
{
    json j;
    j["students"] = json::object();

    for (const auto& [name, student] : students) {
        json studentJson;
        studentJson["name"] = student.name;
        studentJson["gpa"] = student.gpa;

        studentJson["classes"] = json::object();
        for (const auto& course : student.classes) {
            json classJson;
            classJson["className"] = course.className;
            classJson["teacher"] = course.teacher;

            classJson["assignments"] = json::array();
            for (const auto& assignment : course.assignments) {
                json assignmentJson;
                assignmentJson["assignment"] = assignment.assignment;
                assignmentJson["grade"] = assignment.grade;
                classJson["assignments"].push_back(assignmentJson);
            }
            studentJson["classes"][course.className] = classJson;
        }
        j["students"][name] = studentJson;
    }
    ofstream outputFile("studentData.json");
    if (!outputFile.is_open()) {
        cerr << "Cannot open file for writing!" << endl;
        return;
    }
    outputFile << setw(4) << j << endl;
    outputFile.close();
}

int main()
{
    menu();
    return 0;
}