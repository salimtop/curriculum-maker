#include "Course.hpp"
#include "CompulsoryCourse.hpp"
#include <string>

using namespace std;

class ElectiveCourse :public Course
{
public:
 
    ElectiveCourse(string code, string name, int year, int credit, char faculty, string instruc);

    ElectiveCourse();
    
    ~ElectiveCourse();

    string toString();

    bool operator==(ElectiveCourse comp);

};
