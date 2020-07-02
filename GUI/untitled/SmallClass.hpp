#include "Classes.hpp"

class SmallClass:public Classes
{
public:
	static int smallClass;
	string className; //clasSize+num

	SmallClass();
	~SmallClass();
	string toString();
    string getName();

};

