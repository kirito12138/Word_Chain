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
	bool hasRing(int ring);
	
	vector<vector<node>> graph;
	
	
private:
	//int getMaxLen();
	//void DFSroute(int len, int start, int lastLetter, int endLetter);
	//vector<string> getResult();
	//vector<string> findMax();
	//vector<string> findMax(bool SorE, char letter);
	//void setEndLetter(int num);
	//void notDFS(int start);
	vector<string> result;
	int maxLen;
	int endLetter;
	vector<int> tellRepeat;           //judge if has ring ; len == ringnum
	PreProcess PreP;
	vector<string> route;
	int inDArray[26] = { 0 };
	
	vector<int> topoArray;
};
