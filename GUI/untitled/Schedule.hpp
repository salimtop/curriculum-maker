#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "Course.hpp"
#include "Classes.hpp"
#include <vector>
#include <string>

using namespace std;

class Schedule
{
public:
    vector<Classes *> myClasses;
    Schedule();
    ~Schedule();

    bool takeService(vector<Course *>& myCourses, string file) throw(int);

    bool takeBusy(vector<Course *>& myCourses, string file)throw(int);

    bool putRest(vector<Course *>& myCourses);

    bool exportFile(string file);

    void displayClasses();

    void displayCourses();


private:
    bool putService(Course* myCourse, int day, int time);

    bool putBusy(Course* lect, int day, int time);

    bool controlYear(int day, int time, int year);

    int* findNextSlot(int day, int time, bool isElective = true);

    bool putMandatory(Course* lect);

    bool putElective(Course* lect);

    string convertDay(int dayNum);

    string convertTime(int timeNum);

    static int dayNumber(string str);

    static int timeNumber(string str);

    static Course* pullCourse(vector<Course*>& myCourses, string code, bool erase = true);
    bool insertInto(Course *myCourse, int classroom, int day, int time, bool isElective = true);
    inline bool eraseBusies(vector<Course *>& myCourses, string file) throw(int);

};

#endif // SCHEDULE_H
