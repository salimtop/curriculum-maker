#include "Classes.hpp"
#include <string>
#include "Course.hpp"
#include "BigClass.hpp"
#include "SmallClass.hpp"

using namespace std;


Classes::Classes()
{

}

Classes::~Classes()
{
    //dtor

}

void Classes::initializeWeek()
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++){
            Course* empt = new Course();
            weekdays[i][j] = empt;
        }

    }
}

vector<Classes *> Classes::readClassesFile(string file)throw(int)
{
    vector<Classes *> myClasses;

    ifstream fin;

    fin.open(file);
    if (!fin.good())
        throw - 1;

    string size, str;
    int num;
    try{
        while (!fin.eof()) {
            getline(fin, size, ';');
            if (size == "" || size == "\n")
                break;
            getline(fin, str, '\n');
            num = stoi(str);
            for (int i = 0; i < num; i++) {
                if (size == "bigClass") {
                    BigClass* bg = new BigClass();
                    myClasses.push_back(bg);
                }
                else {
                    SmallClass* sm = new SmallClass();
                    myClasses.push_back(sm);
                }
            }
        }
    }
    catch (...) {
        throw -1;
    }
    return myClasses;
}

bool Classes::isBigClass()
{
    if (dynamic_cast<BigClass *>(this) != nullptr)
        return true;
    return false;
}

string Classes::getName()
{
    return "----";
}

string Classes::toString()
{
    return "Parent Class";
}

void Classes::displayClasses(vector<Classes *>& myClasses)
{
    for (int i = 0; i < myClasses.size(); i++) {
        cout << myClasses.at(i)->toString();
    }
}
