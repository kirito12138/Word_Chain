#include "pch.h"
#include <iostream>
#include <string>
#include "Input.h"
#include "Error.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>
using namespace std;
Input::Input()
{

}
void Input::ProcessInput()
{
	int pt = 0;
	int len = inputString.size();
	int pathBeginI = 0;
	while (pt < len)
	{
		if (inputString[pt] == '-')
		{
			pt++;
			switch (inputString[pt])
			{
			case 'w':
				if (mode == 0)
				{
					mode = 1;
				}
				else 
				{
					Error("Chain Type Parameter Error");
				}
				break;

			case 'c':
				if (mode == 0)
				{
					mode = 2;
				}
				else
				{
					Error("Chain Type Parameter Error");
				}
				break;

			case 'h':
				if (head != 0)
				{
					Error("Head Duplicate Definition Error");
				}
				pt++;
				if (inputString[pt] != ' ')
				{
					Error("Lack Space Error");
				}
				pt++;
				if (isalpha(inputString[pt]) == 0)
				{
					Error("Head Letter Error");
				}
				head = tolower(inputString[pt]);
				break;

			case 't':
				if (tail != 0)
				{
					Error("Tail Duplicate Definition Error");
				}
				pt++;
				if (inputString[pt] != ' ')
				{
					Error("Lack Space Error");
				}
				pt++;
				if (isalpha(inputString[pt]) == 0)
				{
					Error("Tail Letter Error");
				}
				tail = tolower(inputString[pt]);
				break;

			case 'r':
				if (ifRing != 0)
				{
					Error("Ring Parameter Duplicate");
				}
				ifRing = 1;
				break;
			default:
				Error("Parameter Type Error");
				break;
			}
		}
		else
		{
			if (mode == 0)
			{
				Error("Lack Chain Type Parameter");
			}
			pathBeginI = pt;
			pt = len;
			break;
		}
		pt++;
		if (inputString[pt] != ' ')
		{
			Error("Lack Space Error");
		}
		pt++;
	}
	path = inputString.substr(pathBeginI, len - pathBeginI);
}

Input::Input(int num, char * paras[])
{
	int i = 2;
	inputString = paras[1];
	for (i; i < num; i++) {
		inputString = inputString + " ";
		inputString = inputString + paras[i];
	}
	//inputString = str;
	mode = 0;
	ifRing = 0;
	head = 0;
	tail = 0;
	ProcessInput();
	getTxt(path, 1);
}

Input::Input(string str)
{
	inputString = str;
	mode = 0;
	ifRing = 0;
	head = 0;
	tail = 0;
	ProcessInput();
	getTxt(path, 1);
}


void Input::getTxt(string str, int file)
{
	if (file == 1)
	{
		ifstream ifile(str);
		ostringstream oss;
		if (!ifile)
		{
			ofstream slt("solution.txt");
			slt << str << endl;
			slt.close();
			Error("File Doesnt Exist");
		}
		oss << ifile.rdbuf();
		longStr = oss.str();
	}

}

