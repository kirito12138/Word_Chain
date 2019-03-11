#include "pch.h"
#include <iostream>
#include <string>


using namespace std;

void Error(string str)
{
	throw(str);
	//cout << "Error:" << str << "!\n" << endl;
	//exit(0);
}