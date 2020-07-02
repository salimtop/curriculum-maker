#ifndef COMPULSORYCOURSE_H
#define COMPULSORYCOURSE_H
#include "Course.hpp"

class CompulsoryCourse:public Course
{
public:

    CompulsoryCourse(string code, string name, int year, int credit, char faculty, string instruc);

    CompulsoryCourse();

    ~CompulsoryCourse();

    string toString();


    bool operator==(CompulsoryCourse comp);

};
#endif //COMPULSORYCOURSE_H