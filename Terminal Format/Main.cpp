#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Course.hpp"
#include "Classes.hpp"
#include "Schedule.hpp"
#include <vector>
#include "BigClass.hpp"


int main() {

    string coursesFile = "Enter file direction for Courses";
    string classesFile = "Enter file direction for Classrooms";
    string serviceFile = "Enter file direction for Service";
    string busyFile = "Enter file direction for Busy";
    string exportFile = "Enter export file direction.";

   Schedule mySchedule = Schedule();
   vector<Course *> myCourses;
   try {

       myCourses = Course::readCoursesFile(coursesFile);
   }
   catch (int e) {
       cout << "Proper Courses file is not found! " << endl;
       cout << "Current Courses location: \"" + coursesFile +"\"\n";
       return 0;
   }

   Course::displayVec(myCourses);
   cout << "\n\n";

   try {
       mySchedule.myClasses = Classes::readClassesFile(classesFile);
   }
   catch (...) {
       cout << "Proper Classes file is not found! " << endl;
       cout << "Current Classes location: \"" + classesFile +"\"\n";
       return 0;
   }

   bool cont;
   try {
       cont = mySchedule.takeService(myCourses, serviceFile);
       if (!cont) {
           cout << "There is no way to make a perfect schedule for the department.\n";
           return 0;
       }
   }
   catch (int e) {
       cout << "services not found\n";
        cout << "Current service file location: \"" + serviceFile +"\"\n";
   }

   try{

        cont = mySchedule.takeBusy(myCourses, busyFile);
        if (!cont) {
            cout << "There is no way to make a perfect schedule for the department.\n";
        return 0;
        }
   }
   catch(...){
        cout << "Busy file not found\n";
        cout << "Current Busy file location: \"" + busyFile +"\"\n";
        return 0;
   }
   cont = mySchedule.putRest(myCourses);
   if (!cont) {
       cout << "There is no way to make a perfect schedule for the department.\n";
       return 0;
   }


   mySchedule.displayCourses();


   try{
        mySchedule.exportFile(exportFile);
   }
   catch(...){
        cout << "Export file error!\n";
        cout << "Current export location: \"" + exportFile +"\"\n";
   }

    return 0;
}
