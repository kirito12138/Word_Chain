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
	void ringDFS(int beginI, int beginJ, vector <string> maxAns, vector <string> tempAns, int tempLen, int mode, int tail);
	vector <string> initDFS(int mode, int head, int tail, int ring);
	int letterLen;    //total letter num of current route
private:
	vector <int> ifCheck;
	PreProcess preP;
};

