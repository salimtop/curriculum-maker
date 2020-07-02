#include "ElectiveCourses.hpp"
#include "CompulsoryCourse.hpp"

ElectiveCourse::ElectiveCourse(string code, string name, int year, int credit, char faculty, string instruc)
{
    this->code = code;
    this->name = name;
    this->year = year;
    this->credit = credit;
    this->faculty = faculty;
    this->instructor = instruc;
    this->empty = true;

}

ElectiveCourse::ElectiveCourse()
{
    this->code = "----";
    this->name = " ";
    this->year = 0;
    this->credit = 0;
    this->faculty = 'b';
    this->instructor = " ";
    this->empty = true;
}

ElectiveCourse::~ElectiveCourse()
{
}

string ElectiveCourse::toString()
{
    if (code == "----")
        return "-----";
    string str = "";
    str = code + ',' + name + ',' + to_string(year) + ',' + to_string(credit) + ',' + "E" + ',' + faculty + ',' + instructor;
    return str;
}

bool ElectiveCourse::operator==(ElectiveCourse comp)
{
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
}
