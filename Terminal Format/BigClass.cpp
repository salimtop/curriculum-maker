#include "BigClass.hpp"
#include "Classes.hpp"

int BigClass::bigClass = 0;

BigClass::BigClass()
{
	this->initializeWeek();
	className = "Big Class" + to_string(++bigClass);
}

BigClass::~BigClass()
{
}



string BigClass::toString() {
	string str = className + '\n';
	for (int i = 0; i < 10; i++) {
		str += to_string((i + 2) / 2) + ". Day Morning : " + weekdays[i / 2][i % 2]->toString() + '\n';
		i++;
		str += to_string((i + 2) / 2) + ". Day Afternoon : " + weekdays[i / 2][i % 2]->toString() + "\n\n";
	}
	return str;
}

string BigClass::getName()
{
	return className;
}
