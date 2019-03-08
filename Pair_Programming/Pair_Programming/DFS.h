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
	void DFSroute(int len, int start, int lastLetter, int endLetter);
	bool hasRing();
	int getMaxLen();
	vector<string> getResult();
	vector<vector<node>> graph;
	void setEndLetter(int num);
	vector<string> findMax();
	vector<string> findMax(bool SorE, char letter);

	void notDFS(int start);
private:
	vector<string> result;
	int maxLen;
	int endLetter;
	vector<int> tellRepeat;           //judge if has ring ; len == ringnum
	PreProcess PreP;
	vector<string> route;
	int inDArray[26] = { 0 };
	
	vector<int> topoArray;
};
