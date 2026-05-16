// Name: Prince Trump Appiah
// Student ID: 2526402735
// Date: 20 May 2026
// Program: Student Grade Management System
// Description:
// This program stores student records, calculates grades,
// displays reports and statistics, and allows searching
// for students by ID using arrays, functions and pointers.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_STUDENTS = 30;


// function to return grade based on total score
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


// checks if an ID already exists
bool idExists(int ids[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (ids[i] == id)
            return true;
    }

    return false;
}


// function for entering student records
void inputStudents(string names[], int ids[],
                   float quiz[], float mid[],
                   float exam[], int *count)
{
    cin.ignore(1000, '\n');

    cout << "\n===== ENTER STUDENT RECORDS =====" << endl;

    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        cout << "\nEnter student name (or stop to finish): ";
        getline(cin, names[i]);

        if (names[i] == "stop" || names[i] == "STOP")
            break;

        cout << "Enter student ID: ";
        cin >> ids[i];

        while (idExists(ids, *count, ids[i]))
        {
            cout << "ID already exists. Enter another ID: ";
            cin >> ids[i];
        }

        // quiz score
        cout << "Enter quiz score (0 - 20): ";
        cin >> quiz[i];

        while (quiz[i] < 0 || quiz[i] > 20)
        {
            cout << "Invalid score. Enter again: ";
            cin >> quiz[i];
        }

        // mid-sem score
        cout << "Enter mid-sem score (0 - 30): ";
        cin >> mid[i];

        while (mid[i] < 0 || mid[i] > 30)
        {
            cout << "Invalid score. Enter again: ";
            cin >> mid[i];
        }

        // exam score
        cout << "Enter exam score (0 - 50): ";
        cin >> exam[i];

        while (exam[i] < 0 || exam[i] > 50)
        {
            cout << "Invalid score. Enter again: ";
            cin >> exam[i];
        }

        (*count)++;

        cin.ignore(1000, '\n');
    }

    cout << "\nStudent records entered successfully." << endl;
}


// calculates totals and grades
void computeGrades(float *quiz, float *mid,
                   float *exam, float *total,
                   char grades[], string remarks[],
                   int count)
{
    for (int i = 0; i < count; i++)
    {
        total[i] = quiz[i] + mid[i] + exam[i];

        grades[i] = assignGrade(total[i]);

        if (grades[i] == 'F')
            remarks[i] = "Fail";
        else
            remarks[i] = "Pass";
    }

    cout << "\nGrades computed successfully." << endl;
}


// displays full report
void displayReport(string names[], int ids[],
                   float quiz[], float mid[],
                   float exam[], float total[],
                   char grades[], string remarks[],
                   int count)
{
    if (count == 0)
    {
        cout << "\nNo records found." << endl;
        return;
    }

    cout << "\n================ CLASS REPORT ================" << endl;

    cout << left
         << setw(10) << "ID"
         << setw(20) << "NAME"
         << setw(8) << "QUIZ"
         << setw(8) << "MID"
         << setw(8) << "EXAM"
         << setw(8) << "TOTAL"
         << setw(8) << "GRADE"
         << "REMARK" << endl;

    cout << "-------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << left
             << setw(10) << ids[i]
             << setw(20) << names[i]
             << setw(8) << quiz[i]
             << setw(8) << mid[i]
             << setw(8) << exam[i]
             << setw(8) << total[i]
             << setw(8) << grades[i]
             << remarks[i] << endl;
    }
}


// function to find highest and lowest score
void findHighestLowest(float *total, int count,
                       float *highest, float *lowest)
{
    *highest = total[0];
    *lowest = total[0];

    for (int i = 1; i < count; i++)
    {
        if (*(total + i) > *highest)
            *highest = *(total + i);

        if (*(total + i) < *lowest)
            *lowest = *(total + i);
    }
}


// displays class statistics
void displayStatistics(float total[],
                       char grades[], int count)
{
    if (count == 0)
    {
        cout << "\nNo statistics available." << endl;
        return;
    }

    float highest, lowest;

    findHighestLowest(total, count, &highest, &lowest);

    float sum = 0;
    int pass = 0;
    int fail = 0;

    for (int i = 0; i < count; i++)
    {
        sum += total[i];

        if (grades[i] == 'F')
            fail++;
        else
            pass++;
    }

    float average = sum / count;

    cout << "\n============= CLASS STATISTICS =============" << endl;

    cout << fixed << setprecision(1);

    cout << "Highest Score : " << highest << endl;
    cout << "Lowest Score  : " << lowest << endl;
    cout << "Average Score : " << average << endl;
    cout << "Students Pass : " << pass << endl;
    cout << "Students Fail : " << fail << endl;
}


// searches student by ID
int searchByID(int ids[], int count, int searchID)
{
    for (int i = 0; i < count; i++)
    {
        if (ids[i] == searchID)
            return i;
    }

    return -1;
}


// menu function
void displayMenu()
{
    cout << "\n========== STUDENT GRADE SYSTEM ==========" << endl;
    cout << "1. Enter Student Records" << endl;
    cout << "2. Compute Grades" << endl;
    cout << "3. Display Full Report" << endl;
    cout << "4. Display Statistics" << endl;
    cout << "5. Search Student by ID" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter choice: ";
}


int main()
{
    string names[MAX_STUDENTS];
    int ids[MAX_STUDENTS];

    float quiz[MAX_STUDENTS];
    float mid[MAX_STUDENTS];
    float exam[MAX_STUDENTS];

    float total[MAX_STUDENTS];

    char grades[MAX_STUDENTS];

    string remarks[MAX_STUDENTS];

    int count = 0;
    int choice;

    bool gradesReady = false;

    do
    {
        displayMenu();

        cin >> choice;

        switch (choice)
        {
            case 1:
                inputStudents(names, ids, quiz,
                              mid, exam, &count);

                gradesReady = false;
                break;

            case 2:

                if (count == 0)
                {
                    cout << "\nEnter student records first." << endl;
                }
                else
                {
                    computeGrades(quiz, mid, exam,
                                  total, grades,
                                  remarks, count);

                    gradesReady = true;
                }

                break;

            case 3:

                if (!gradesReady)
                {
                    cout << "\nPlease compute grades first." << endl;
                }
                else
                {
                    displayReport(names, ids, quiz,
                                  mid, exam, total,
                                  grades, remarks, count);
                }

                break;

            case 4:

                if (!gradesReady)
                {
                    cout << "\nPlease compute grades first." << endl;
                }
                else
                {
                    displayStatistics(total, grades, count);
                }

                break;

            case 5:

                if (count == 0)
                {
                    cout << "\nNo student records available." << endl;
                }
                else
                {
                    int searchID;

                    cout << "\nEnter student ID: ";
                    cin >> searchID;

                    int index = searchByID(ids, count, searchID);

                    if (index == -1)
                    {
                        cout << "Student not found." << endl;
                    }
                    else
                    {
                        cout << "\nStudent Found" << endl;

                        cout << "Name   : " << names[index] << endl;
                        cout << "ID     : " << ids[index] << endl;
                        cout << "Quiz   : " << quiz[index] << endl;
                        cout << "Mid    : " << mid[index] << endl;
                        cout << "Exam   : " << exam[index] << endl;

                        if (gradesReady)
                        {
                            cout << "Total  : " << total[index] << endl;
                            cout << "Grade  : " << grades[index] << endl;
                            cout << "Remark : " << remarks[index] << endl;
                        }
                    }
                }

                break;

            case 6:
                cout << "\nProgram terminated." << endl;
                break;

            default:
                cout << "\nInvalid choice." << endl;
        }

    } while (choice != 6);

    return 0;
}
