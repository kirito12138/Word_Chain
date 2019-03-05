#include "pch.h"
#include <iostream>
#include <string>

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

		void ProcessInput()
		{
			
		}

	public:
		Input(string str)
		{
			inputString = str;
			ProcessInput();
		}

};