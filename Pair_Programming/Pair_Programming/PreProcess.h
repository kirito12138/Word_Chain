#pragma once
#include <string>
#include "ConstValues.h"
#include <vector>
#include <iostream>
#include "Error.h"
#include "Input.h"

using namespace std;

class PreProcess
{
public:
	PreProcess();
	PreProcess(char* wordss[], int len, int r);
	PreProcess(string str, int n, char* words[], int r); //str: whole txt file, generate words and graph
	int ringNum = 0;
	int num = 0;
	vector< vector<node> > ringGraph;
	vector< vector<node> > graph;
	int wordn=0;
	PreProcess(string str, int r);   //str:path  r:ifRing  generate vector graph
	~PreProcess();
	void printGraph();
	void printRingGraph();
	int ifExist[26][26] = {};
	void print(vector <string> ary);
	void VecToStr(char* result[], vector <string> ans);
	
private:
	int ring = 0;
	string path;
	//bool cmpLen(const node &str1, const node &str2);
	void GenGraph();
	void strToVector(char* words[]);
	int strToWords(string temp, char* words[]);
	vector <vector < vector <string> > > checkR;
};
