#pragma once
#include <string>
#include<vector>
#include"ConstValues.h"
#include "PreProcess.h"

using namespace std;

class DFS
{
public:
	DFS();
	~DFS();
	DFS(PreProcess pp);
	void getGraph();
	void DFSroute(vector<string> route, int len, int start, int lastLetter);
	bool hasRing();
	int getMaxLen();
	vector<string> getResult();
	vector<vector<node>> graph;
	void setEndLetter(int num);
private:
	vector<string> result;
	int maxLen;
	int endLetter;
	vector<int> tellRepeat;           //judge if has ring ; len == ringnum
	PreProcess PreP;
};
