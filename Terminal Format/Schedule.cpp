#include "Schedule.hpp"
#include <fstream>
#include <algorithm>
#include "BigClass.hpp"
#include "SmallClass.hpp"

Schedule::Schedule() {

}

Schedule::~Schedule() {

}

bool Schedule::takeService(vector<Course*>& myCourses, string file)throw(int)
{
    ifstream fin;
    string code, day, time;
    int dayNum, timeNum;
    Course* pull;

    fin.open(file);
    if (!fin.good())
        throw - 1;

    try {
        while (!fin.eof()) {
            getline(fin, code, ';');
            if (code == "")
                break;
            getline(fin, day, ';');
            getline(fin, time, '\n');
            pull = pullCourse(myCourses, code);
            if (pull == nullptr)
                return false;
            dayNum = dayNumber(day);
            timeNum = timeNumber(time);
            if (!putService(pull, dayNum, timeNum))
                return false;
        }
    }
    catch (...) {
        throw -2;
    }

    return true;
}

bool Schedule::putService(Course* myCourse, int day, int time)
{
    for (int i = 0; i < myClasses.size(); i++) {
        if (myClasses.at(i)->weekdays[day][time]->empty == true) {
            if (insertInto(myCourse, i, day, time, myCourse->isElective()))
                return true;
        }

    }
    return false;
}

bool Schedule::takeBusy(vector<Course*>& myCourses, string file)throw(int)
{
    ifstream fin;
    string code, day, time;
    int dayNum, timeNum;
    Course* pull;

    fin.open(file);
    if (!fin.good())
        throw - 1;

    try {
        while (!fin.eof()) {
            getline(fin, code, ';');
            if (code == "")
                break;
            getline(fin, day, ';');
            getline(fin, time, '\n');
            pull = pullCourse(myCourses, code, false);
            if (pull == nullptr)
                return false;
            dayNum = dayNumber(day);
            timeNum = timeNumber(time);
            if (!putBusy(pull, dayNum, timeNum))//These are busy days' number
                return false;
        }
        fin.close();
        eraseBusies(myCourses, file);
    }
    catch (...) {
        throw -2;
    }

    return true;
}

bool Schedule::putBusy(Course* lect, int day, int time)
{
    int* arr;
    for (int i = 0; i < myClasses.size(); i++) {
        if (myClasses.at(i)->weekdays[day][time] == lect) {
            Course* empt = new Course();
            myClasses.at(i)->weekdays[day][time] = empt;
            myClasses.at(i)->weekdays[day][time]->empty = true;

        }
    }

    arr = findNextSlot(day, time, lect->isElective());
    while (!controlYear(arr[1], arr[2], lect->year))
        arr = findNextSlot(arr[1], arr[2], lect->isElective());
    if (insertInto(lect, arr[0], arr[1], arr[2], lect->isElective()))
        return true;
    return false;
}

bool Schedule::putRest(vector<Course*>& myCourses)
{
    Course* pull;
    std::sort(myCourses.begin(), myCourses.end(), Course::copareTo);
    for (int i = 0; i < myCourses.size(); i++) {

        if (!myCourses.at(i)->isElective()) {
            pull = pullCourse(myCourses, myCourses.at(i)->code);
            i--;
            if (!putMandatory(pull))
                return false;
        }
        else if (myCourses.at(i)->isElective()) {
            pull = pullCourse(myCourses, myCourses.at(i)->code);
            i--;
            if (!putElective(pull))
                return false;
        }
    }

    return true;
}

bool Schedule::exportFile(string file)throw(int)
{
    ofstream fout;
    try
    {
        fout.open(file);
        if (!fout.good())
            throw - 1;
        string name;
        string disp = "";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < myClasses.size(); k++) {
                    if (myClasses.at(k)->isBigClass())
                        name = ((BigClass*)myClasses.at(k))->className;
                    name = ((SmallClass*)myClasses.at(k))->className;

                    disp += convertDay(i) + " " + convertTime(j) + " " + name + " " + myClasses.at(k)->weekdays[i][j]->code + '\n';
                }
            }
            disp += "\n";
        }
        fout << disp;
        fout.close();
    }
    catch (...)
    {
        throw -1;
    }
    return true;
}

bool Schedule::controlYear(int day, int time, int year)
{
    for (int i = 0; i < myClasses.size(); i++) {
        if (myClasses.at(i)->weekdays[day][time]->year == year)
            return false;
    }
    return true;
}

int* Schedule::findNextSlot(int day, int time, bool isElective)
{

    for (int i = 1 + time; i < 10; i++) { // checks next days and time slots. 1 + time: 1 is for not check same slot, +time for passing next day if time is 1.
        for (int j = 0; j < myClasses.size(); j++) {//checks Classes
            if (isElective == false && !(myClasses.at(j))->isBigClass()) {
                //Controls big class or not for mandatory classes
            }
            else if ((myClasses.at(j))->weekdays[(day + (i / 2)) % 5][i % 2]->empty == true) {
                int* arr = new int[3];
                arr[0] = j;
                arr[1] = (day + (i / 2)) % 5;
                arr[2] = i % 2;
                return arr;
            }
        }
    }
    int* arr = new int[3];
    arr[0] = -1;
    arr[1] = -1;
    arr[2] = -1;
    return arr;
}

bool Schedule::putMandatory(Course* lect)
{
    int* arr;
    arr = findNextSlot(0, -1, false);
    while (!controlYear(arr[1], arr[2], lect->year)) {
        arr = findNextSlot(arr[1], arr[2], true);
        if (arr[0] == -1)
            return false;
    }

    if (insertInto(lect, arr[0], arr[1], arr[2], false))
        return true;
    return false;
}

bool Schedule::putElective(Course* lect)
{
    int* arr;
    arr = findNextSlot(0, -1, true);
    while (!controlYear(arr[1], arr[2], lect->year)) {
        arr = findNextSlot(arr[1], arr[2], true);
        if (arr[0] == -1)
            return false;
    }
    if (insertInto(lect, arr[0], arr[1], arr[2], true))
        return true;
    return false;
}

string Schedule::convertDay(int dayNum)
{
    if (dayNum == 0) {
        return "Monday";
    }
    else if (dayNum == 1) {
        return "Tuesday";
    }
    else if (dayNum == 2) {
        return "Wednesday";
    }
    else if (dayNum == 3) {
        return "Thursday";
    }
    else if (dayNum == 4) {
        return "Friday";
    }
    else
    {
        return "Invalid Day Number!";
    }
}

string Schedule::convertTime(int timeNum) {

    if (timeNum == 0) {
        return "Morning";
    }
    else if (timeNum == 1) {
        return "Afternoon";
    }
    else {
        return "Invalid Time Number!";
    }
}


int Schedule::dayNumber(string str)
{
    if (str == "Monday" || str == "monday")
        return 0;
    else if (str == "Tuesday" || str == "tuesday")
        return 1;
    else if (str == "Wednesday" || str == "wednesday")
        return 2;
    else if (str == "Thursday" || str == "thursday")
        return 3;
    else if (str == "Friday" || str == "friday")
        return 4;
    return -1;
}

int Schedule::timeNumber(string str)
{
    if (str == "Morning" || str == "morning")
        return 0;
    else if (str == "Afternoon" || str == "afternoon")
        return 1;
    return -1;
}

Course* Schedule::pullCourse(vector<Course*>& myCourses, string code, bool erase)
{
    for (int i = 0; i < myCourses.size(); i++) {
        if (myCourses.at(i)->code.compare(code) == 0) {
            Course* pull = myCourses.at(i);
            if (erase)
                myCourses.erase(myCourses.begin() + i);
            return pull;
        }
    }
    return nullptr;
}

void Schedule::displayClasses()
{
    for (int i = 0; i < myClasses.size(); i++) {
        cout << myClasses.at(i)->toString();
    }
}

void Schedule::displayCourses()
{
    string name;
    string disp = "";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < myClasses.size(); k++) {
                if (myClasses.at(k)->isBigClass())
                    name = ((BigClass*)myClasses.at(k))->className;
                name = ((SmallClass*)myClasses.at(k))->className;

                disp += convertDay(i) + " " + convertTime(j) + " " + name + " " + myClasses.at(k)->weekdays[i][j]->code + '\n';
            }
        }
        disp += "\n";
    }

    cout << disp << endl;
}

bool Schedule::insertInto(Course* myCourse, int classroom, int day, int time, bool isElective)
{
    if (!controlYear(day, time, myCourse->year))
        return false;
    if (!myCourse->isElective() && myClasses.at(classroom)->isBigClass() && myClasses.at(classroom)->weekdays[day][time]->empty == true) {
        myClasses.at(classroom)->weekdays[day][time] = myCourse;
        myClasses.at(classroom)->weekdays[day][time]->empty = false;
        return true;
    }
    else if (myCourse->isElective() && myClasses.at(classroom)->weekdays[day][time]->empty == true) {
        myClasses.at(classroom)->weekdays[day][time] = myCourse;
        myClasses.at(classroom)->weekdays[day][time]->empty = false;
        return true;
    }
    return false;
}

bool Schedule::eraseBusies(vector<Course*>& myCourses, string file)throw(int)
{
    ifstream fin;
    string code, str;

    fin.open(file);
    try {
        if (!fin.good())
            throw - 1;
    }
    catch (int e) {
        cout << "File not found for Classes";
    }

    try {
        while (!fin.eof()) {
            getline(fin, code, ';');
            if (code == "")
                break;
            getline(fin, str, ';');
            getline(fin, str, '\n');
            pullCourse(myCourses, code, true);
        }
        fin.close();
    }
    catch (...) {
        throw;
    }

    return true;
}
