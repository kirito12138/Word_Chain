#pragma once
#include <string>
#include "ConstValues.h"
#include <vector>

using namespace std;

class PreProcess
{
public:
	static int ringNum;
	static int num;
	vector< vector<node> > ringGraph;
	vector< vector<node> > graph;
	PreProcess(string str);
	~PreProcess();
	void printGraph();
	void printRingGraph();

	

private:
	string path;
	int ifExist[26][26] = {};
	void GenGraph();
};

