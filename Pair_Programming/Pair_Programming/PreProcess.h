#pragma once
#include <string>
#include "ConstValues.h"
#include <vector>
#include <iostream>
#include "Error.h"

using namespace std;

class PreProcess
{
public:
	PreProcess();
	PreProcess(char* wordss[], int len);
	PreProcess(string str, int n, char* words[]);
	static int ringNum;
	static int num;
	vector< vector<node> > ringGraph;
	vector< vector<node> > graph;
	int wordn;
	PreProcess(string str);
	~PreProcess();
	void printGraph();
	void printRingGraph();
	int ifExist[26][26];
	void print(vector <string> ary);
	void VecToStr(char* result[], vector <string> ans);
	
private:
	string path;
	//bool cmpLen(const node &str1, const node &str2);
	void GenGraph();
	void strToVector(char* words[]);
	int strToWords(string temp, char* words[]);
};
