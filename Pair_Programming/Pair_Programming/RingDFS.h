#pragma once

#include <string>
#include "ConstValues.h"
#include <vector>
#include "PreProcess.h"

using namespace std;

class RingDFS
{
public:
	RingDFS();
	~RingDFS();
	RingDFS(PreProcess pp);
	int ifExist[26][26] = {};
	
	vector <string> initDFS(int mode, int head, int tail, int ring);
	int letterLen;    //total letter num of current route
	void printCurGraph();
private:
	void ringDFS(int beginI, int beginJ, vector <string> &maxAns, vector <string> &tempAns, int tempLen, int mode, int tail);
	void optDFS(int beginI, int beginJ, int mode, int tail);
	vector <int> ifCheck;
	PreProcess preP;
	vector< vector<node> > curGraph;
	int fff = 0;
	int ifFindTail = 0;
	int maxRoute[26];
	int headLetter[26] = {};
	int selfRing[26] = {};
};

