// Name: Prince Trump Appiah
// Student ID: 2526402735
// Date: 20th May 2026
// Description: Student Grade Management System for CS 101 project.
//              The program lets you enter student records, compute
//              grades and display a report. It uses arrays, functions
//              and pointers.

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX = 30;  // max number of students


// this function takes a total score and returns the letter grade
char assignGrade(float total)
{
    if (total >= 80)
        return 'A';
    else if (total >= 70)
        return 'B';
    else if (total >= 60)
        return 'C';
    else if (total >= 50)
        return 'D';
    else
        return 'F';
}


// this function reads all student data from the user
// it also validates the scores so they are in the right range
// studentCount is a pointer so i can update it from inside here
void inputStudents(string names[], int ids[], float quiz[],
                   float midSem[], float exam[], int* studentCount)
{
    *studentCount = 0;

    cout << "\n=== ENTER STUDENT RECORDS ===" << endl;
    cout << "You can enter up to " << MAX << " students." << endl;
    cout << "Type 'done' as the name when you want to stop." << endl;

    for (int i = 0; i < MAX; i++)
    {
        cout << "\n--- Student " << (i + 1) << " ---" << endl;
        cout << "Enter name (or done to stop): ";
        cin.ignore();
        getline(cin, names[i]);

        if (names[i] == "done" || names[i] == "Done")
            break;

        cout << "Enter student ID: ";
        cin >> ids[i];

        // quiz is out of 20
        cout << "Enter Quiz score (0-20): ";
        cin >> quiz[i];
        while (quiz[i] < 0 || quiz[i] > 20)
        {
            cout << "Score must be between 0 and 20. Try again: ";
            cin >> quiz[i];
        }

        // mid sem is out of 30
        cout << "Enter Mid-Semester score (0-30): ";
        cin >> midSem[i];
        while (midSem[i] < 0 || midSem[i] > 30)
        {
            cout << "Score must be between 0 and 30. Try again: ";
            cin >> midSem[i];
        }

        // exam is out of 50
        cout << "Enter Exam score (0-50): ";
        cin >> exam[i];
        while (exam[i] < 0 || exam[i] > 50)
        {
            cout << "Score must be between 0 and 50. Try again: ";
            cin >> exam[i];
        }

        *studentCount += 1;
    }

    cout << "\nDone. " << *studentCount << " student(s) entered." << endl;
}


// computes total, grade and remark for every student
// using float* instead of float[] to use pointer notation as required
void computeGrades(float* quiz, float* midSem, float* exam,
                   float* total, char* grades, string remarks[], int count)
{
    for (int i = 0; i < count; i++)
    {
        total[i] = quiz[i] + midSem[i] + exam[i];
        grades[i] = assignGrade(total[i]);

        if (grades[i] == 'F')
            remarks[i] = "Fail";
        else
            remarks[i] = "Pass";
    }

    cout << "\nGrades assigned for all " << count << " student(s)." << endl;
}


// prints the full class report as a table
void displayReport(string names[], int ids[], float* total,
                   char grades[], string remarks[], int count)
{
    if (count == 0)
    {
        cout << "\nNo records to show. Enter students first." << endl;
        return;
    }

    cout << "\n=========================================================" << endl;
    cout << "               FULL CLASS REPORT" << endl;
    cout << "=========================================================" << endl;

    cout << left
         << setw(10) << "ID"
         << setw(22) << "NAME"
         << setw(8)  << "TOTAL"
         << setw(7)  << "GRADE"
         << "REMARK" << endl;

    cout << "---------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << left
             << setw(10) << ids[i]
             << setw(22) << names[i]
             << setw(8)  << fixed << setprecision(1) << total[i]
             << setw(7)  << grades[i]
             << remarks[i] << endl;
    }

    cout << "=========================================================" << endl;
}


// finds the highest and lowest score using pointer arithmetic
// i pass pointers so the function can return more than one value
void findHighestLowest(float* total, int count,
                       float* highest, float* lowest,
                       int* highIdx, int* lowIdx)
{
    *highest = total[0];
    *lowest  = total[0];
    *highIdx = 0;
    *lowIdx  = 0;

    // using *(total + i) instead of total[i] for pointer arithmetic
    for (int i = 1; i < count; i++)
    {
        if (*(total + i) > *highest)
        {
            *highest = *(total + i);
            *highIdx = i;
        }
        if (*(total + i) < *lowest)
        {
            *lowest = *(total + i);
            *lowIdx = i;
        }
    }
}


// displays class statistics - highest, lowest, average, pass/fail count
void displayStatistics(string names[], float* total, char grades[], int count)
{
    if (count == 0)
    {
        cout << "\nNo records found. Enter students first." << endl;
        return;
    }

    float highest = 0, lowest = 0;
    int highIdx = 0, lowIdx = 0;

    findHighestLowest(total, count, &highest, &lowest, &highIdx, &lowIdx);

    float sum = 0;
    int passed = 0, failed = 0;

    for (int i = 0; i < count; i++)
    {
        sum += total[i];
        if (grades[i] == 'F')
            failed++;
        else
            passed++;
    }

    float avg = sum / count;

    cout << "\n=========================================================" << endl;
    cout << "                 CLASS STATISTICS" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << fixed << setprecision(1);
    cout << "  Highest Score  : " << highest << "  (" << names[highIdx] << ")" << endl;
    cout << "  Lowest Score   : " << lowest  << "  (" << names[lowIdx]  << ")" << endl;
    cout << "  Class Average  : " << avg << endl;
    cout << "  Students Passed: " << passed << endl;
    cout << "  Students Failed: " << failed << endl;
    cout << "=========================================================" << endl;
}


// searches for a student by ID using linear search
// returns the index if found or -1 if not found
int searchByID(int ids[], int count, int searchID)
{
    for (int i = 0; i < count; i++)
    {
        if (ids[i] == searchID)
            return i;
    }
    return -1;
}


// just prints the menu
void displayMenu()
{
    cout << "\n=========================================" << endl;
    cout << "   STUDENT GRADE MANAGEMENT SYSTEM" << endl;
    cout << "=========================================" << endl;
    cout << " 1. Enter Student Records" << endl;
    cout << " 2. Compute and Assign Grades" << endl;
    cout << " 3. Display Full Class Report" << endl;
    cout << " 4. Display Class Statistics" << endl;
    cout << " 5. Search Student by ID" << endl;
    cout << " 6. Exit" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Enter your choice: ";
}


int main()
{
    string names[MAX];
    int    ids[MAX];
    float  quiz[MAX];
    float  midSem[MAX];
    float  exam[MAX];
    float  totalScore[MAX];
    char   grades[MAX];
    string remarks[MAX];

    int studentCount = 0;
    bool gradesReady = false;  // to check if option 2 has been run

    int choice;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                inputStudents(names, ids, quiz, midSem, exam, &studentCount);
                gradesReady = false;  // reset because new data was entered
                break;

            case 2:
                if (studentCount == 0)
                    cout << "\nPlease enter students first (Option 1)." << endl;
                else
                {
                    computeGrades(quiz, midSem, exam, totalScore,
                                  grades, remarks, studentCount);
                    gradesReady = true;
                }
                break;

            case 3:
                if (!gradesReady)
                    cout << "\nPlease compute grades first (Option 2)." << endl;
                else
                    displayReport(names, ids, totalScore, grades, remarks, studentCount);
                break;

            case 4:
                if (!gradesReady)
                    cout << "\nPlease compute grades first (Option 2)." << endl;
                else
                    displayStatistics(names, totalScore, grades, studentCount);
                break;

            case 5:
                if (studentCount == 0)
                {
                    cout << "\nNo students in the system yet." << endl;
                }
                else
                {
                    int sid;
                    cout << "\nEnter Student ID to search: ";
                    cin >> sid;

                    int idx = searchByID(ids, studentCount, sid);

                    if (idx == -1)
                    {
                        cout << "Student with ID " << sid << " not found." << endl;
                    }
                    else
                    {
                        cout << "\n--- Student Found ---" << endl;
                        cout << "Name   : " << names[idx]  << endl;
                        cout << "ID     : " << ids[idx]    << endl;
                        cout << "Quiz   : " << quiz[idx]   << " / 20" << endl;
                        cout << "Mid-Sem: " << midSem[idx] << " / 30" << endl;
                        cout << "Exam   : " << exam[idx]   << " / 50" << endl;

                        if (gradesReady)
                        {
                            cout << fixed << setprecision(1);
                            cout << "Total  : " << totalScore[idx] << " / 100" << endl;
                            cout << "Grade  : " << grades[idx]     << endl;
                            cout << "Remark : " << remarks[idx]    << endl;
                        }
                        else
                        {
                            cout << "(Run Option 2 to see this student's grade)" << endl;
                        }
                    }
                }
                break;

            case 6:
                cout << "\nExiting... Goodbye!" << endl;
                break;

            default:
                cout << "\nInvalid choice. Enter a number from 1 to 6." << endl;
                break;
        }

    } while (choice != 6);

    return 0;
}
