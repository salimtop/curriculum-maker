#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Course
{
public:
    string code;
    string name;
    int year;
    int credit;
    char faculty; //'D' department or 'S' service
    string instructor;

    bool empty;
    Course();
    ~Course();
    virtual string toString();
    static vector<Course *> readCoursesFile(string file) throw(int);
    static void displayVec(vector<Course *>& myVec);
    bool isElective();
    bool operator== (Course comp);
    static bool copareTo(Course *c1, Course *c2);
};

#endif // COURSE_H



