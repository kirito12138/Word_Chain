#pragma once
#include <iostream>
#include <string>
#include "Error.h"

using namespace std;

class Input
{
private:
	string inputString;
	string path;
	int mode;
	int ifRing;
	int head;
	int tail;

	void ProcessInput();

public:
	Input(int num, char * paras[]);
	Input(string str);

	int getMode() 
	{
		return mode;
	}

	int getIfRing()
	{
		return ifRing;
	}

	int getHead()
	{
		return head;
	}

	int getTail()
	{
		return tail;
	}

	string getPath()
	{
		return path;
	}

	string getInput()
	{
		return inputString;
	}
};