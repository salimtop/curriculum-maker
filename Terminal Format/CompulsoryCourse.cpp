#include "CompulsoryCourse.hpp"

CompulsoryCourse::CompulsoryCourse(string code, string name, int year, int credit, char faculty, string instruc)
{
    this->code = code;
    this->name = name;
    this->year = year;
    this->credit = credit;
    this->faculty = faculty;
    this->instructor = instruc;
    this->empty = true;
}

CompulsoryCourse::CompulsoryCourse()
{
    this->code = "----";
    this->name = " ";
    this->year = 0;
    this->credit = 0;
    this->faculty = 'b';
    this->instructor = " ";
    this->empty = true;
}

CompulsoryCourse::~CompulsoryCourse()
{
}

string CompulsoryCourse::toString()
{
    if (code == "----")
        return "-----";
    string str = "";
    str = code + ',' + name + ',' + to_string(year) + ',' + to_string(credit) + ',' + "C" + ',' + faculty + ',' + instructor;
    return str;
}


bool CompulsoryCourse::operator==(CompulsoryCourse comp)
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
