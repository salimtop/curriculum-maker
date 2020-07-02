#include "Classes.hpp"

class BigClass:public Classes
{	
public:
	static int bigClass;
	string className; //clasSize+num

	BigClass();
	~BigClass();
	string toString();
	string getName();
};

