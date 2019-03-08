#pragma once
#include <string>
#include "ConstValues.h"
#include <vector>

using namespace std;

class PreProcess
{
public:
	PreProcess();
	static int ringNum;
	static int num;
	vector< vector<node> > ringGraph;
	vector< vector<node> > graph;
	PreProcess(string str);
	~PreProcess();
	void printGraph();
	void printRingGraph();
	void print(string* ary, int n);
	int ifExist[26][26] = {};

private:
	string path;
	//bool cmpLen(const node &str1, const node &str2);
	void GenGraph();
};

