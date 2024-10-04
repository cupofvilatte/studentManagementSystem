#include <iostream>
#include <map>
#include <string>

using namespace std;

void studentMap()
{
    // load JSON file that is a map of students with additional data

    // return the map

}

void menu()
{
    // give a list of options for the user
    // menu should include:
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
            viewInfo();
            break;
        case 2:
            /*
            2. modify student
                a. (takes name input and adds a spot in the json file)
                b. or delete student
            */
            modifyStudentData();
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

void viewInfo()
{

}

void modifyStudentData()
{

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

int main()
{
    return 0;
}