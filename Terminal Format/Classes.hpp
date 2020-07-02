#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <fstream>
#include <string>
#include "Course.hpp"

using namespace std;

class Classes
{
public:

    Course* weekdays[5][2];
    Classes();
    ~Classes();

    void initializeWeek();

    static vector<Classes *> readClassesFile(string file) throw(int);

    bool isBigClass();

    virtual string getName();

    virtual string toString();

    static void displayClasses(vector<Classes *>& myClasses);

};

#endif // CLASSES_H
