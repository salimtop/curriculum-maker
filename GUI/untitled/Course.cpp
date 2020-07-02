#include "Course.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "CompulsoryCourse.hpp"
#include "ElectiveCourses.hpp"

using namespace std;



Course::Course() {
    this->code = "----";
    this->name = " ";
    this->year = 0;
    this->credit = 0;
    this->faculty = 'b';
    this->instructor = " ";
    this->empty = true;
}

Course::~Course()
{
}

string Course::toString()
{
    return "----";
}

vector<Course *> Course::readCoursesFile(string file)throw(int)
{
    vector<Course *> myCourses;
    ifstream fin;
    string code, name, instructor, str;
    int year, credit;
    char type, faculty;

    fin.open(file);
    if (!fin.good())
        throw(-1);

    try {
        while (!fin.eof()) {

            getline(fin, code, ';');
            if (code == "")
                break;
            getline(fin, name, ';');
            getline(fin, str, ';');
            year = stoi(str);
            getline(fin, str, ';');
            credit = stoi(str);
            getline(fin, str, ';');
            type = str.at(0);
            getline(fin, str, ';');
            faculty = str.at(0);
            getline(fin, instructor, '\n');
            if (type == 'C' || type == 'c') {
                CompulsoryCourse* cp = new CompulsoryCourse(code, name, year, credit, faculty, instructor);
                myCourses.push_back(cp);
            }
            else if (type == 'E' || type == 'e') {
                ElectiveCourse* et = new ElectiveCourse(code, name, year, credit, faculty, instructor);
                myCourses.push_back(et);
            }

        }
    }
    catch (...) {
        throw -2;
    }


    return myCourses;
}

void Course::displayVec(vector<Course *>& myVec)
{
    if (myVec.empty())
        cout << "Class vector is empty";
    for (int i = 0; i < myVec.size(); i++) {
        cout << myVec.at(i)->toString() << endl;
    }
}

bool Course::isElective()
{
    if (dynamic_cast<ElectiveCourse*>(this) != nullptr)
        return true;
    return false;
}

bool Course::operator==(Course comp)
{
    if (this->isElective() != comp.isElective())
        return false;
    if (comp.code != code)
        return false;
    if (comp.credit != credit)
        return false;
    if (comp.faculty != faculty)
        return false;
    if (comp.instructor != instructor)
        return false;
    if (comp.name != name)
        return false;
    if (comp.year != year)
        return false;
    return true;
    return false;
}

bool Course::copareTo(Course *c1, Course *c2)
{
    if (!c1->isElective() && c2->isElective())
        return true;
    return false;
}

