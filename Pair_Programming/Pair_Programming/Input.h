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
	int mode=0;   //0:default   1:word   2:letter
	int ifRing=0;
	int head=0;
	int tail=0;
	void ProcessInput();
	void getTxt(string str, int file);   // file==0 : str to words    file==1 : file from path str to words
public:
	Input(int num, char * paras[]);
	Input(string str);
	Input();
	string longStr;
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