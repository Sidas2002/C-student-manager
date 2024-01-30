#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <iomanip>
#include <cmath>


using namespace std;

class student{

public:
    string name, occupation;
    int age, course;
    bool isDebt;
    double average;

    student(string name, int age, int course, string occupation){

        this->name = name;
        this->age = age;
        this->course = course;
        this-> occupation = occupation;
        this-> isDebt = false;
        this-> average = 0.0;
    }

};

bool CheckDebt(double mark){
    return mark < 5.0;
}

double calculateAverage(student& stud) {
    double sum = 0.0;
    int subject;
    bool hasBelow5 = false;

    cout << "How many subjects did the student have this semester? :";
    cin >> subject;

    for (int i = 0; i < subject; i++) {
        double mark;
        cout << "Enter mark for subject " << i + 1 << ": ";
        cin >> mark;
        sum += mark;

        if (mark < 5.0) {
            hasBelow5 = true;
        }
    }

    stud.isDebt = hasBelow5;
    stud.average = sum / subject;

    return stud.average;
}



void displayStudents(const vector<student>& students){

    for (const auto& stud : students){
        cout << stud.name << " ";
        cout << stud.age << " ";
        cout << stud.occupation << " ";
        cout << stud.average << " ";
        cout << (stud.isDebt ? "in debt" : "") << endl;
        cout << "--------------------------------------" << endl;
    }

}

void addStudent(vector<student>& studs){
    string name, occupation;
    int age, course;

    cout << "Enter student details:"<< endl;
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);

    for (const auto& stud : studs){
        if (stud.name == name){
            cout << "Student with the same name already exists. Cannot add student" << endl;
            return;
        }
    }

    cout << endl;
    cout << "Age: ";
    cin >> age;
    cout << endl;
    cout << "Occupation: ";
    cin.ignore();
    getline(cin, occupation);
    cout << endl;
    cout << "Course: ";
    cin >> course;
    cout << endl;

    student stud(name, age, course, occupation);
    calculateAverage(stud);
    studs.push_back(stud);


}

void CheckAverage(const vector<student>& studs){
    string searchName;
    cout << "Enter the name of the student you wanna check: ";
    cin.ignore();
    getline(cin, searchName);
    cout <<endl;

    auto it = find_if(studs.begin(), studs.end(), [&searchName](const student& s){
                      return s.name == searchName;});

    if (it != studs.end()){
        cout << it-> name << " " << it->occupation << " " << it->average << endl;
    }else{
        cout << "Student with the given name not found." << endl;
    }
}

bool hasDebtByName (const vector<student>& studs, const string& searchName){
    auto it = find_if(studs.begin(), studs.end(), [&searchName](const student& s){
                      return s.name == searchName;
                      });

    if (it != studs.end()){
        return it->isDebt;
    }else{
        return false;
    }
}

void displaydebts(const vector<student>& studs){
    cout << "Students with debt: " << endl;
    int i = 1;
    for (const auto& stud : studs){
        cout << i << " " << stud.name << " " << stud.occupation << " " << (stud.isDebt ? "has debt" : "has no debt") << endl;
        i++;
    }
}

void displayStudentsByOccupation(const vector<student>& studs, const string& occupationToDisplay) {
    map<int, vector<string>> studentsByCourse;

    for (const auto& stud : studs) {
        if (stud.occupation == occupationToDisplay) {
            if (stud.course >= 1 && stud.course <= 4) {
                studentsByCourse[stud.course].push_back(stud.name);
            } else {
                cout << "Debug: Invalid course value: " << stud.course << endl;
            }
        }
    }

    cout << "Occupation: " << occupationToDisplay << endl;
    for (const auto& entry : studentsByCourse) {
        cout << entry.first << " course:" << endl;
        for (const auto& name : entry.second) {
            cout << name << endl;
        }
    }
}

void displayStudentsByAverage(const vector<student>& studs, int targetAverage) {
    cout << "Students with average rounded to " << targetAverage << ":" << endl;

    for (const auto& stud : studs) {
        // Round the average to the nearest integer
        int roundedAverage = static_cast<int>(round(stud.average));

        if (roundedAverage == targetAverage) {
            cout << stud.name << " (" << fixed << setprecision(2) << stud.average << " average)" << endl;
        }
    }
}


int main()
{
    vector <student> studs;

    while(true)
    {
        cout << "0. Exit" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Check if student is in debt" << endl;
        cout << "3. Check students avarage" << endl;
        cout << "4. Display all students" << endl;
        cout << "5. Get all students with your chosen mark as indicator" << endl;
        cout << "6. Display students by certain occupation" << endl;

        int mark;
        int choise;
        cin >> choise;

        switch(choise){
        default:
            cout << "Wrong input" << endl;
            break;
        case 0:
            cout << "Have a nice day";
            return 0;
            break;
        case 1:
            addStudent(studs);
            break;
        case 2:
            cout << "Do you wanna get list of all students with debts(1) or particular one(2)?";
            int debt;
            cin >> debt;
            if (debt == 1){
                displaydebts(studs);
            }else if (debt == 2){
                string searchName;
                cout << "Enter the name of the student to check for debt: ";
                cin.ignore();
                getline(cin, searchName);
                if (hasDebtByName(studs, searchName)){
                    cout << "The student has debt. "<< endl;
                }else {
                    cout << "The student does not have debt or the name was not found. " << endl;
                }
            }else{
                cout <<"Wrong input" << endl;
            }
            break;
        case 3:
            CheckAverage(studs);
            break;
        case 4:
            displayStudents(studs);
            break;
        case 5:
            cout << "Enter the mark: ";
            cin >> mark;
            displayStudentsByAverage(studs, mark);
            break;
        case 6:
            string occup;
            cout << "Enter the occupation to display students: ";
            cin.ignore();
            getline(cin, occup);
            displayStudentsByOccupation(studs, occup);
            break;

        }
    }


    return 0;
}
