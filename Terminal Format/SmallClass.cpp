#include "SmallClass.hpp"


int SmallClass::smallClass = 0;


SmallClass::SmallClass() {
	this->initializeWeek();
	className = "Small Class" + to_string(++smallClass);
}

SmallClass::~SmallClass()
{
}

string SmallClass::toString(){
	string str = className+'\n';
	for (int i = 0; i < 10; i++) {
		str += to_string((i + 2) / 2) + ". Day Morning : " + weekdays[i / 2][i % 2]->toString() +'\n';
		i++;
		str += to_string((i + 2)/2) + ". Day Afternoon : " + weekdays[i / 2][i % 2]->toString() + "\n\n";
	}
	return str;
}

string SmallClass::getName()
{
	return className;
}

