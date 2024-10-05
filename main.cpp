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
void updateStudentGrade(map<string, Student>& students);
void createAssignment(map<string, Student>& students);
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
            updateStudentGrade(students);

        case 4:
        // 4. create student assignment
            createAssignment(students);
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

void updateStudentGrade(map<string, Student>& students)
{
    cout << "Enter a student's name: ";
    string studentName;
    cin.ignore();
    getline(cin, studentName);

    if (students.find(studentName) == students.end()) {
        cout << "student could not be found!" << endl;
        return;
    }
    Student& student = students[studentName];

    cout << "--- Class List ---" << endl;
    for (size_t i = 0; i < student.classes.size(); ++i) {
        cout << i + 1 << ") " << student.classes[i].className << " | Teacher: " << student.classes[i].teacher << endl;
    }
    int classChoice;
    cout << "Enter your class choice: ";
    cin >> classChoice;

    Class& selectedClass = student.classes[classChoice - 1];

    cout << "Select an assignment to update: " << endl;
    for (size_t i = 0; i < selectedClass.assignments.size(); ++i) {
        cout << i + 1 << ") " << selectedClass.assignments[i].assignment << " | Grade: " << selectedClass.assignments[i].grade << endl;
    }
    int assignmentChoice;
    cout << "Enter your choice: ";
    cin >> assignmentChoice;

    Assignment& selectedAssignment = selectedClass.assignments[assignmentChoice - 1];

    cout << "Enter the new grade as a fraction: ";
    string fraction;
    cin >> fraction;

    size_t slashPos = fraction.find('/');
    if (slashPos == string::npos) {
        cout << "Invalid!" << endl;
        return;
    }

    int numerator = stoi(fraction.substr(0, slashPos));
    int denominator = stoi(fraction.substr(slashPos + 1));

    if (denominator == 0) {
        cout << "Cannot divide by zero!" << endl;
        return;
    }

    // calculate percentage
    double percentage = static_cast<double>(numerator) / denominator * 100;
    selectedAssignment.grade = static_cast<int>(percentage);
    cout << "Assignment changed to: " << selectedAssignment.grade << "%" << endl;

    double totalGrades = 0.0;
    int totalAssignments = 0;

    for (const auto& course : student.classes) {
        for (const auto& assignment : course.assignments) {
            totalGrades += assignment.grade;
            ++totalAssignments;
        }
    }

    student.gpa = totalAssignments > 0 ? totalGrades / totalAssignments / 25.0 : 0.0;
    cout << "GPA update to: " << student.gpa << endl;

    writeDataToFile(students);
}

void createAssignment(map<string, Student>& students)
{
    string studentName;
    cout << "Enter a student name: ";
    cin.ignore();
    getline(cin, studentName);

    if (students.find(studentName) == students.end()) {
        cout << "The student could not be found." << endl;
        return;
    }

    Student& student = students[studentName];

    string className;
    cout << "Enter the class name: ";
    getline(cin, className);

    auto classIt = find_if(student.classes.begin(), student.classes.end(),
                        [&className](const Class& c) {
                            return c.className == className;
                        });
    if (classIt == student.classes.end()) {
        cout << "The class could not be found." << endl;
        return;
    }

    string assignmentName;
    cout << "Enter the assignment name: ";
    getline(cin, assignmentName);

    string gradeFraction;
    cout << "Enter the grade as a fraction: ";
    getline(cin, gradeFraction);

    size_t delimiter = gradeFraction.find('/');
    if (delimiter == string::npos) {
        cout << "Invalid fraction format!" << endl;
        return;
    }

    int numerator = stoi(gradeFraction.substr(0, delimiter));
    int denominator = stoi(gradeFraction.substr(delimiter + 1));

    if (denominator == 0) {
        cout << "Cannot divide by zero!" << endl;
        return;
    }

    int gradePercentage = static_cast<int>((static_cast<double>(numerator) / denominator) * 100);

    Assignment newAssignment{assignmentName, gradePercentage};
    classIt->assignments.push_back(newAssignment);

    writeDataToFile(students);

    cout << "Assignment added!" << endl;
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